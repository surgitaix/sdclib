/*
 * HTTPSessionManager.h
 *
 *  Created on: 15.12.2015
 *      Author: matthias
 */

#ifndef OSELIB_DPWS_HTTPSESSIONMANAGER_H_
#define OSELIB_DPWS_HTTPSESSIONMANAGER_H_

#include <memory>

#include "Poco/Mutex.h"
#include "Poco/ThreadPool.h"

#include "OSELib/fwd.h"
#include "OSELib/Helper/WithLogger.h"

namespace OSELib {
namespace HTTP {

class SendWorker;

// todo maybe generalize and also use for other client connections in the SDCConsumerAdapter.

class HTTPSessionManager : public WithLogger {
public:
	HTTPSessionManager(DPWS::ActiveSubscriptions & subscriptions);
	~HTTPSessionManager();

	void enqueMessage(const Poco::URI & destinationURI, const std::string & content, const xml_schema::Uri & myID);

private:
	DPWS::ActiveSubscriptions & _subscriptions;
	Poco::ThreadPool _threadpool;
	Poco::Mutex _mutex;
	std::map<std::string, std::shared_ptr<Poco::NotificationQueue>> _queues;
	std::map<std::string, std::unique_ptr<Poco::Runnable>> _workers;
};

} /* namespace HTTP */
} /* namespace OSELib */

#endif /* OSELIB_DPWS_HTTPSESSIONMANAGER_H_ */
