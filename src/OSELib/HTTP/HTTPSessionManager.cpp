/*
 * HTTPSessionManager.cpp
 *
 *  Created on: 15.12.2015, matthias
 *  Modified on: 22.08.2019, baumeister
 *
 */

#include "OSELib/HTTP/HTTPSessionManager.h"
#include "OSELib/DPWS/ActiveSubscriptions.h"
#include "OSELib/HTTP/HTTPClientExchanger.h"
#include "SDCLib/Config/SSLConfig.h"

#include <atomic>
#include <string>

#include <Poco/NotificationQueue.h>
#include <Poco/Runnable.h>
#include <Poco/URI.h>
#include <Poco/Net/SocketNotification.h>


namespace OSELib {
namespace HTTP {

class Message : public Poco::Notification
{
public:
	Message(const std::string & p_message, const Poco::URI & p_destination, const xml_schema::Uri & p_myID)
	: m_message(p_message)
	, m_destination(p_destination)
	, m_myID(p_myID)
	{ }
	const std::string m_message;
	const Poco::URI m_destination;
	const xml_schema::Uri m_myID;
};

class SendWorker : public Poco::Runnable, public OSELib::Helper::WithLogger
{
public:
	SendWorker(const Poco::URI & p_destinationURI, std::shared_ptr<Poco::NotificationQueue> p_queue, DPWS::ActiveSubscriptions & p_subscriptions, Poco::Net::Context::Ptr p_context)
	: OSELib::Helper::WithLogger(Log::EVENTSOURCE)
	, m_running(true)
	, m_destinationURI(p_destinationURI)
	, m_queue(p_queue)
	, m_subscriptions(p_subscriptions)
	, m_context(p_context)
	{ }

	virtual ~SendWorker() = default;

	virtual void run() override {

		struct ScopedFalseSetter {
			ScopedFalseSetter(std::atomic<bool> & value) : m_value(value) { }
			~ScopedFalseSetter() { m_value = false; }
		private:
			std::atomic<bool> & m_value;
		};

		ScopedFalseSetter setter(m_running);

		while (Poco::Notification * t_loopN = m_queue->waitDequeueNotification(10000)) {
			Poco::AutoPtr<Poco::Notification> t_notification(t_loopN);

			if (dynamic_cast<const Poco::Net::ShutdownNotification *>(t_notification.get())) {
				return;
			} else if (auto t_message = dynamic_cast<const Message *>(t_notification.get())) {
				HTTP::HTTPClientExchanger t_exchanger;
				try {

					// SSL or not
					if(m_context) {
						Poco::Net::HTTPSClientSession t_session(m_destinationURI.getHost(), m_destinationURI.getPort(), m_context);
						t_session.setTimeout(Poco::Timespan(SDCLib::Config::SDC_CONNECTION_TIMEOUT_MS*1000)); // Convert to microseconds

						t_exchanger.exchangeHttp(t_session, t_message->m_destination.getPath(), t_message->m_message);
					}
					else {
						Poco::Net::HTTPClientSession t_session(m_destinationURI.getHost(), m_destinationURI.getPort());
						t_session.setTimeout(Poco::Timespan(SDCLib::Config::SDC_CONNECTION_TIMEOUT_MS*1000)); // Convert to microseconds

						t_exchanger.exchangeHttp(t_session, t_message->m_destination.getPath(), t_message->m_message);
					}
				} catch (...) {
					log_error([] { return "Delivering event failed."; });
					m_subscriptions.unsubscribe(t_message->m_myID);
					log_error([&] { return "Terminating subscription for sink: " + m_destinationURI.toString(); });
					return;
				}
			}
		}
	}

	bool isRunning() const {
		return m_running;
	}

private:
	std::atomic<bool> m_running = ATOMIC_VAR_INIT(false);
	const Poco::URI m_destinationURI;
	std::shared_ptr<Poco::NotificationQueue> m_queue;
	DPWS::ActiveSubscriptions & m_subscriptions;
	Poco::Net::Context::Ptr m_context = nullptr;
};

HTTPSessionManager::HTTPSessionManager(DPWS::ActiveSubscriptions & p_subscriptions, SDCLib::Config::SSLConfig_shared_ptr p_SSLConfig)
: OSELib::Helper::WithLogger(Log::EVENTSOURCE)
, m_subscriptions(p_subscriptions)
{
	assert(p_SSLConfig != nullptr);
	if(p_SSLConfig) {
		m_context = p_SSLConfig->getClientContext();
	}
}

HTTPSessionManager::~HTTPSessionManager()
{
	std::lock_guard<std::mutex> t_lock(m_mutex);
	for (const auto & t_item : ml_queues) {
		t_item.second->enqueueUrgentNotification(new Poco::Net::ShutdownNotification(nullptr));
	}
	m_threadpool.joinAll();
}

void HTTPSessionManager::enqueMessage(const Poco::URI & p_destinationURI, const std::string & p_content, const xml_schema::Uri & p_myID)
{
	std::lock_guard<std::mutex> t_lock(m_mutex);
	{
		std::vector<std::string> tl_toErase;
		for (const auto & t_item : ml_workers) {
			if (const auto t_worker = dynamic_cast<const SendWorker *>(t_item.second.get())) {
				if (!t_worker->isRunning()) {
					tl_toErase.emplace_back(t_item.first);
				}
			}
		}
		for (const auto & t_item : tl_toErase) {
			ml_queues.erase(t_item);
			ml_workers.erase(t_item);
		}
	}

	// SSL QND
	std::string ts_PROTOCOL = "http";
    if(m_context) {
        ts_PROTOCOL.append("s");
    }

    const std::string t_mapIndex(ts_PROTOCOL + "://" + p_destinationURI.getHost() + ":" + std::to_string(p_destinationURI.getPort()));

	auto t_matchQueue(ml_queues.find(t_mapIndex));
	if (t_matchQueue == ml_queues.end()) {
		auto t_queue = std::make_shared<Poco::NotificationQueue>();
		ml_queues.emplace(t_mapIndex, t_queue);
		if (static_cast<std::size_t>(m_threadpool.capacity()) < ml_queues.size()) {
			m_threadpool.addCapacity(ml_queues.size() - m_threadpool.capacity() + 1);
		}
		std::unique_ptr<SendWorker> t_worker(new SendWorker(p_destinationURI, t_queue, m_subscriptions, m_context));
		m_threadpool.start(*t_worker);
		ml_workers.emplace(t_mapIndex, std::move(t_worker));
		t_queue->enqueueNotification(new Message(p_content, p_destinationURI, p_myID));
	} else {
		t_matchQueue->second->enqueueNotification(new Message(p_content, p_destinationURI, p_myID));
	}
}

}
}
