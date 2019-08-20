/*
 * HTTPSessionManager.cpp
 *
 *  Created on: 15.12.2015
 *      Author: matthias
 */

#include <atomic>
#include <iostream>
#include <string>

#include <Poco/NotificationQueue.h>
#include <Poco/Runnable.h>
#include <Poco/URI.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/SocketNotification.h>
#include <Poco/Net/NetException.h>

#include "OSELib/DPWS/ActiveSubscriptions.h"
#include "OSELib/HTTP/HTTPClientExchanger.h"
#include "OSELib/HTTP/HTTPSessionManager.h"

#include "SDCLib/Config/SSLConfig.h"

namespace OSELib {
namespace HTTP {

class Message : public Poco::Notification {
public:
	Message(const std::string & message, const Poco::URI & destination, const xml_schema::Uri & myID) :
		_message(message),
		_destination(destination),
		_myID(myID)
	{
	}
	const std::string _message;
	const Poco::URI _destination;
	const xml_schema::Uri _myID;
};

class SendWorker : public Poco::Runnable, public OSELib::Helper::WithLogger {
public:
	SendWorker(const Poco::URI & destinationURI, std::shared_ptr<Poco::NotificationQueue> queue, DPWS::ActiveSubscriptions & subscriptions, Poco::Net::Context::Ptr p_context) :
		OSELib::Helper::WithLogger(Log::EVENTSOURCE),
		_running(true),
		_destinationURI(destinationURI),
		_queue(queue),
		_subscriptions(subscriptions)
		, m_context(p_context)
	{
	}

	virtual ~SendWorker() = default;

	virtual void run() override {

		struct ScopedFalseSetter {
			ScopedFalseSetter(std::atomic<bool> & value) : _value(value) { }
			~ScopedFalseSetter() { _value = false; }
		private:
			std::atomic<bool> & _value;
		};

		ScopedFalseSetter setter(_running);



		while (Poco::Notification * _n = _queue->waitDequeueNotification(10000)) {
			Poco::AutoPtr<Poco::Notification> n(_n);

			if (dynamic_cast<const Poco::Net::ShutdownNotification *>(n.get())) {
				return;
			} else if (auto message = dynamic_cast<const Message *>(n.get())) {
				HTTP::HTTPClientExchanger exchanger;
				try {

					// SSL or not
					if(m_context) {
						Poco::Net::HTTPSClientSession session(_destinationURI.getHost(), _destinationURI.getPort(), m_context);
						session.setTimeout(Poco::Timespan(5,0));
						session.setKeepAlive(true);

						exchanger.exchangeHttp(session, message->_destination.getPath(), message->_message);
					}
					else {
						Poco::Net::HTTPClientSession session(_destinationURI.getHost(), _destinationURI.getPort());
						session.setTimeout(Poco::Timespan(5,0));
						session.setKeepAlive(true);

						exchanger.exchangeHttp(session, message->_destination.getPath(), message->_message);
					}
				} catch (...) {
					log_error([&] { return "Delivering event failed."; });
					_subscriptions.unsubscribe(message->_myID);
					log_error([&] { return "Terminating subscription for sink: " + _destinationURI.toString(); });
					return;
				}
			}
		}
	}

	bool isRunning() const {
		return _running;
	}

private:
	std::atomic<bool> _running;
	const Poco::URI _destinationURI;
	std::shared_ptr<Poco::NotificationQueue> _queue;
	DPWS::ActiveSubscriptions & _subscriptions;
	Poco::Net::Context::Ptr m_context = nullptr;
};

HTTPSessionManager::HTTPSessionManager(DPWS::ActiveSubscriptions & subscriptions, SDCLib::Config::SSLConfig_shared_ptr p_SSLConfig)
: OSELib::Helper::WithLogger(Log::EVENTSOURCE)
, _subscriptions(subscriptions)
{
	assert(p_SSLConfig != nullptr);
	if(p_SSLConfig) {
		m_context = p_SSLConfig->getClientContext();
	}
}

HTTPSessionManager::~HTTPSessionManager()
{
	std::lock_guard<std::mutex> t_lock(m_mutex);
	for (const auto & item : _queues) {
		item.second->enqueueUrgentNotification(new Poco::Net::ShutdownNotification(nullptr));
	}
	_threadpool.joinAll();
}

void HTTPSessionManager::enqueMessage(const Poco::URI & destinationURI, const std::string & content, const xml_schema::Uri & myID)
{
	std::lock_guard<std::mutex> t_lock(m_mutex);


	{
		std::vector<std::string> toErase;
		for (const auto & item : _workers) {
			if (const auto worker = dynamic_cast<const SendWorker *>(item.second.get())) {
				if (!worker->isRunning()) {
					toErase.emplace_back(item.first);
				}
			}
		}
		for (const auto & item : toErase) {
			_queues.erase(item);
			_workers.erase(item);
		}
	}

	// SSL QND
	std::string ts_PROTOCOL = "http";
    if(m_context) {
        ts_PROTOCOL.append("s");
    }

    const std::string mapIndex(ts_PROTOCOL + "://" + destinationURI.getHost() + ":" + std::to_string(destinationURI.getPort()));

	auto matchQueue(_queues.find(mapIndex));
	if (matchQueue == _queues.end()) {
		auto queue = std::make_shared<Poco::NotificationQueue>();
		_queues.emplace(mapIndex, queue);
		if (static_cast<std::size_t>(_threadpool.capacity()) < _queues.size()) {
			_threadpool.addCapacity(_queues.size() - _threadpool.capacity() + 1);
		}
		std::unique_ptr<SendWorker> worker(new SendWorker(destinationURI, queue, _subscriptions, m_context));
		_threadpool.start(*worker);
		_workers.emplace(mapIndex, std::move(worker));
		queue->enqueueNotification(new Message(content, destinationURI, myID));
	} else {
		matchQueue->second->enqueueNotification(new Message(content, destinationURI, myID));
	}
}

} /* namespace HTTP */
} /* namespace OSELib */
