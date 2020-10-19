/*
 * HTTPSessionManager.h
 *
 *  Created on: 15.12.2015, matthias
 *  Modified on: 02.09.2020, baumeister
 *
 */

#ifndef OSELIB_DPWS_HTTPSESSIONMANAGER_H_
#define OSELIB_DPWS_HTTPSESSIONMANAGER_H_

#include "OSELib/fwd.h"
#include "OSELib/Helper/WithLogger.h"
#include "SDCLib/Prerequisites.h"

#include <Poco/ThreadPool.h>
#include <Poco/Net/Context.h>

#include <memory>
#include <mutex>

namespace OSELib
{
    namespace HTTP
    {
        // todo maybe generalize and also use for other client connections in the SDCConsumerAdapter.

        class HTTPSessionManager : public OSELib::Helper::WithLogger
        {
        private:
            DPWS::SubscriptionManager* m_subscriptionManager{nullptr};
            Poco::Net::Context::Ptr m_context{nullptr};
            Poco::ThreadPool m_threadpool;

            std::mutex m_mutex;
            std::map<std::string, std::shared_ptr<Poco::NotificationQueue>> m_queues;
            std::map<std::string, std::unique_ptr<Poco::Runnable>> m_workers;

        public:
            HTTPSessionManager(DPWS::SubscriptionManager*, SDCLib::Config::SSLConfig_shared_ptr);
            // Special Member Functions
            HTTPSessionManager(const HTTPSessionManager&) = delete;
            HTTPSessionManager(HTTPSessionManager&&) = delete;
            HTTPSessionManager& operator=(const HTTPSessionManager&) = delete;
            HTTPSessionManager& operator=(HTTPSessionManager&&) = delete;
            ~HTTPSessionManager();

            void enqueMessage(const Poco::URI&, const std::string&, const xml_schema::Uri&);
        };

    } // namespace HTTP
} // namespace OSELib

#endif
