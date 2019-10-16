/*
 * HTTPServer.h
 *
 *  Created on: 26.09.2019, baumeister
 *
 */

#ifndef OSELIB_HTTP_HTTPSERVER_H_
#define OSELIB_HTTP_HTTPSERVER_H_


#include "OSELib/fwd.h"
#include "SDCLib/Prerequisites.h"

#include <Poco/Net/HTTPServer.h>
#include <Poco/ThreadPool.h>

namespace OSELib
{
	namespace HTTP
	{
		class HTTPServer
		{
		private:
			
			SDCLib::Config::NetworkConfig_shared_ptr m_networkConfig = nullptr;
			SDCLib::Config::SSLConfig_shared_ptr m_SSLConfig = nullptr;

			std::atomic<bool> m_init = ATOMIC_VAR_INIT(false);

			std::unique_ptr<Poco::Net::HTTPServer> m_httpServer = nullptr;
			std::unique_ptr<Poco::ThreadPool> m_threadPool = nullptr;

		public:
			HTTPServer(SDCLib::Config::NetworkConfig_shared_ptr p_networkConfig, SDCLib::Config::SSLConfig_shared_ptr p_SSLConfig);
			// Special Member Functions
			HTTPServer(const HTTPServer& p_obj) = delete;
			HTTPServer(HTTPServer&& p_obj) = delete;
			HTTPServer& operator=(const HTTPServer& p_obj) = delete;
			HTTPServer& operator=(HTTPServer&& p_obj) = delete;
			~HTTPServer();

			bool init(HTTPRequestHandlerFactory_shared_ptr p_factory);
			bool isInit() const { return m_init; }

			bool start();
			bool stop();
			bool stopAll(bool p_abortCurrent);

			int currentConnections() const;

			//Poco::Net::HTTPRequestHandler * createRequestHandler(const Poco::Net::HTTPServerRequest & request, bool p_SSL);
			
		private:
			
			void _cleanup();

			SDCLib::Config::NetworkConfig_shared_ptr getNetworkConfig() { return m_networkConfig; }
			SDCLib::Config::SSLConfig_shared_ptr getSSLConfig() { return m_SSLConfig; }
		};
	}
}

#endif
