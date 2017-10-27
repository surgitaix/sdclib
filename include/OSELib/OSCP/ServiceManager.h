/*
 * ServiceManager.h
 *
 *  Created on: 11.12.2015
 *      Author: matthias
 */

#ifndef OSELIB_OSCP_SERVICEMANAGER_H_
#define OSELIB_OSCP_SERVICEMANAGER_H_

#include "Poco/Mutex.h"

#include "OSELib/fwd.h"
#include "OSELib/Helper/WithLogger.h"

namespace OSELib {
namespace OSCP {

class HelloReceivedHandler {
public:
    HelloReceivedHandler() = default;
    virtual ~HelloReceivedHandler() = default;

	virtual void helloReceived(const std::string & epr);
};

class ServiceManager final: public WithLogger {
public:
	ServiceManager();
	virtual ~ServiceManager();

    /**
    * @brief Set a handler that will be called when device send DPWS hello.
    *
    * @param handler The handler
    */
	void setHelloReceivedHandler(HelloReceivedHandler * handler);

    /**
    * @brief Create a consumer and connect to Xaddr.
    *
    * @param xaddr The address
    * @return The consumer or null
    */
	std::unique_ptr<OSCLib::Data::OSCP::OSCPConsumer> connect(const std::string & xaddr);

    /**
    * @brief Create a consumer and try to discover provider using EPR.
    *
    * @param epr The EPR
    * @return The consumer or null
    */
	std::unique_ptr<OSCLib::Data::OSCP::OSCPConsumer> discoverEndpointReference(const std::string & epr);

    /**
    * @brief Discover all SDC providers currently available
    *
    * @return List of all providers
    */
	std::vector<std::unique_ptr<OSCLib::Data::OSCP::OSCPConsumer>> discoverOSCP();

private:
	std::unique_ptr<OSCLib::Data::OSCP::OSCPConsumer> connectXAddress(const std::list<std::string> xaddress, const std::string & epr);
	std::unique_ptr<DPWS::MDPWSDiscoveryClientAdapter> _dpwsClient;
	// todo: kick this helloCallback. Supposedly it is not needed.
	std::unique_ptr<DPWS::HelloCallback> _helloCallback;
	mutable Poco::Mutex _mutex;
};

} /* namespace OSCP */
} /* namespace OSELib */

#endif /* OSELIB_OSCP_SERVICEMANAGER_H_ */
