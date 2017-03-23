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

	void setHelloReceivedHandler(HelloReceivedHandler * handler);

	std::unique_ptr<OSCLib::Data::OSCP::OSCPConsumer> connect(const std::string & xaddr);
	std::unique_ptr<OSCLib::Data::OSCP::OSCPConsumer> discoverEndpointReference(const std::string & epr);
	std::vector<std::unique_ptr<OSCLib::Data::OSCP::OSCPConsumer>> discoverOSCP();

private:
	std::unique_ptr<OSCLib::Data::OSCP::OSCPConsumer> connectXAddress(const std::string & xaddress, const std::string & epr);

	std::unique_ptr<DPWS::MDPWSDiscoveryClientAdapter> _dpwsClient;
	// todo: kick this helloCallback. Supposedly it is not needed.
	std::unique_ptr<DPWS::HelloCallback> _helloCallback;
	mutable Poco::Mutex _mutex;
};

} /* namespace OSCP */
} /* namespace OSELib */

#endif /* OSELIB_OSCP_SERVICEMANAGER_H_ */
