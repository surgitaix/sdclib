/*
 * HTTPSessionManager.h
 *
 *  Created on: 15.12.2015, matthias
 *  Modified on: 20.08.2019, baumeister
 *
 */

#ifndef OSELIB_DPWS_HTTPSESSIONMANAGER_H_
#define OSELIB_DPWS_HTTPSESSIONMANAGER_H_

#include <memory>
#include <mutex>

#include <Poco/ThreadPool.h>
#include <Poco/Net/Context.h>

#include "OSELib/fwd.h"
#include "OSELib/Helper/WithLogger.h"
#include "SDCLib/Prerequisites.h"

namespace OSELib
{
	namespace HTTP
	{
		class SendWorker;
		// todo maybe generalize and also use for other client connections in the SDCConsumerAdapter.

		class HTTPSessionManager : public OSELib::Helper::WithLogger
		{
		private:

			DPWS::ActiveSubscriptions & m_subscriptions;
			Poco::Net::Context::Ptr m_context = nullptr;
			Poco::ThreadPool m_threadpool;

			std::mutex m_mutex;
			std::map<std::string, std::shared_ptr<Poco::NotificationQueue>> ml_queues;
			std::map<std::string, std::unique_ptr<Poco::Runnable>> ml_workers;
		public:

			HTTPSessionManager(DPWS::ActiveSubscriptions & p_subscriptions, SDCLib::Config::SSLConfig_shared_ptr p_SSLConfig);
			// Special Member Functions
			HTTPSessionManager(const HTTPSessionManager& p_obj) = delete;
			HTTPSessionManager(HTTPSessionManager&& p_obj) = delete;
			HTTPSessionManager& operator=(const HTTPSessionManager& p_obj) = delete;
			HTTPSessionManager& operator=(HTTPSessionManager&& p_obj) = delete;
			~HTTPSessionManager();

			void enqueMessage(const Poco::URI & p_destinationURI, const std::string & p_content, const xml_schema::Uri & p_myID);

		};

	}
}

#endif
