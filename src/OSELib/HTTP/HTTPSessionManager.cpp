/*
 * HTTPSessionManager.cpp
 *
 *  Created on: 15.12.2015
 *      Author: matthias
 */

#include <atomic>
#include <iostream>
#include <string>

#include "Poco/NotificationQueue.h"
#include "Poco/Runnable.h"
#include "Poco/URI.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/SocketNotification.h"

#include "OSELib/DPWS/ActiveSubscriptions.h"
#include "OSELib/HTTP/HTTPClientExchanger.h"
#include "OSELib/HTTP/HTTPSessionManager.h"

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

class SendWorker : public Poco::Runnable, public WithLogger {
public:
	SendWorker(const Poco::URI & destinationURI, std::shared_ptr<Poco::NotificationQueue> queue, DPWS::ActiveSubscriptions & subscriptions) :
		WithLogger(Log::EVENTSOURCE),
		_running(true),
		_destinationURI(destinationURI),
		_queue(queue),
		_subscriptions(subscriptions)
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

		Poco::Net::HTTPClientSession session(_destinationURI.getHost(), _destinationURI.getPort());
		session.setTimeout(Poco::Timespan(5,0));
		session.setKeepAlive(true);

		while (Poco::Notification * _n = _queue->waitDequeueNotification(10000)) {
			Poco::AutoPtr<Poco::Notification> n(_n);

			if (dynamic_cast<const Poco::Net::ShutdownNotification *>(n.get())) {
				return;
			} else if (auto message = dynamic_cast<const Message *>(n.get())) {
				HTTP::HTTPClientExchanger exchanger;
				try {
					const std::string responseContent(exchanger.exchangeHttp(session, message->_destination.getPath(), message->_message));
				} catch (...) {
					log_error([&] { return "Delivering event failed. Terminating subscription for sink: " + _destinationURI.toString(); });
					_subscriptions.unsubscribe(message->_myID);
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
};

HTTPSessionManager::HTTPSessionManager(DPWS::ActiveSubscriptions & subscriptions) :
	WithLogger(Log::EVENTSOURCE),
	_subscriptions(subscriptions)
{
}

HTTPSessionManager::~HTTPSessionManager() {
	Poco::Mutex::ScopedLock lock(_mutex);
	for (const auto & item : _queues) {
		item.second->enqueueUrgentNotification(new Poco::Net::ShutdownNotification(nullptr));
	}
	_threadpool.joinAll();
}

void HTTPSessionManager::enqueMessage(const Poco::URI & destinationURI, const std::string & content, const xml_schema::Uri & myID) {
	Poco::Mutex::ScopedLock lock(_mutex);

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

	const std::string mapIndex("http://" + destinationURI.getHost() + ":" + std::to_string(destinationURI.getPort()));

	auto matchQueue(_queues.find(mapIndex));
	if (matchQueue == _queues.end()) {
		auto queue = std::make_shared<Poco::NotificationQueue>();
		_queues.emplace(mapIndex, queue);
		if (_threadpool.capacity() < _queues.size()) {
			_threadpool.addCapacity(_queues.size() - _threadpool.capacity() + 1);
		}
		std::unique_ptr<SendWorker> worker(new SendWorker(destinationURI, queue, _subscriptions));
		_threadpool.start(*worker);
		_workers.emplace(mapIndex, std::move(worker));
		queue->enqueueNotification(new Message(content, destinationURI, myID));
	} else {
		matchQueue->second->enqueueNotification(new Message(content, destinationURI, myID));
	}
}

} /* namespace HTTP */
} /* namespace OSELib */
