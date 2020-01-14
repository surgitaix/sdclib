#include "OSELib/HTTP/HTTPServer.h"

#include "OSELib/HTTP/HTTPRequestHandlerFactory.h"

#include "SDCLib/Config/NetworkConfig.h"
#include "SDCLib/Config/SSLConfig.h"

#include <Poco/Net/NetworkInterface.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/IPAddress.h>
#include <Poco/Net/SecureServerSocket.h>

using namespace OSELib;
using namespace OSELib::HTTP;

HTTPServer::HTTPServer(SDCLib::Config::NetworkConfig_shared_ptr p_networkConfig, SDCLib::Config::SSLConfig_shared_ptr p_SSLConfig)
: m_networkConfig(p_networkConfig)
, m_SSLConfig(p_SSLConfig)
{
	assert(nullptr != m_networkConfig);
	assert(nullptr != m_SSLConfig);
}

HTTPServer::~HTTPServer()
{
	_cleanup();
}

void HTTPServer::_cleanup()
{
	// stop?

	if(m_httpServer) {
		m_httpServer.reset();
	}
}

bool HTTPServer::init(HTTPRequestHandlerFactory_shared_ptr p_factory)
{
	assert(nullptr != p_factory);

	// Necessary Parameter
	m_threadPool = std::unique_ptr<Poco::ThreadPool>(new Poco::ThreadPool());

    auto t_interface = getNetworkConfig()->getMDPWSInterface();
    if(!t_interface) {
    	OSELib::Helper::WithLogger(OSELib::Log::sdcProvider).log_error([] { return "Failed to init HTTPServer: Set MDPWSInterface first!";});
        return false;
    }

    // todo: right now only binding to one interface is possible -> implementation for more than one interface is needed!
    auto t_bindingAddress = t_interface->m_if.address();
    auto t_port = getNetworkConfig()->getMDPWSPort();

	const Poco::Net::SocketAddress t_socketAddress(t_bindingAddress, t_port);

	auto t_serverParams = new Poco::Net::HTTPServerParams;
	auto t_timeout_us = SDCLib::Config::SDC_CONNECTION_TIMEOUT_MS*1000; // Convert to microseconds
	t_serverParams->setTimeout(Poco::Timespan(t_timeout_us));
	t_serverParams->setKeepAliveTimeout(Poco::Timespan(t_timeout_us * 2));


    bool USE_SSL = getSSLConfig()->isInit();
	// Use SSL
	if(USE_SSL)
	{
		// SecureServerSocket
		Poco::Net::SecureServerSocket t_sslSocket(getSSLConfig()->getServerContext());
		t_sslSocket.bind(t_socketAddress);
		t_sslSocket.listen();

		// Create the Server
		m_httpServer = std::unique_ptr<Poco::Net::HTTPServer>(new Poco::Net::HTTPServer(p_factory->getFactory(), *m_threadPool, t_sslSocket, t_serverParams));
	}
	else {
		// ServerSocket
		Poco::Net::ServerSocket t_socket;
		t_socket.bind(t_socketAddress);
		t_socket.listen();

		// Create the Server
		m_httpServer = std::unique_ptr<Poco::Net::HTTPServer>(new Poco::Net::HTTPServer(p_factory->getFactory(), *m_threadPool, t_socket, t_serverParams));
	}

	m_init = true;
	return true;
}

bool HTTPServer::start()
{
	if(!isInit()) {
		return false;
	}

	// Forward
	m_httpServer->start();
	return true;
}

bool HTTPServer::stop()
{
	if(!isInit()) {
		return false;
	}

	// Forward
	m_httpServer->stop();
	return true;
}
bool HTTPServer::stopAll(bool p_abortCurrent)
{
	if(!isInit()) {
		return false;
	}

	// Forward
	m_httpServer->stopAll(p_abortCurrent);
	return true;
}

int HTTPServer::currentConnections() const
{
	if(!isInit()) {
		return 0;
	}

	// Forward
	return m_httpServer->currentConnections();
}
