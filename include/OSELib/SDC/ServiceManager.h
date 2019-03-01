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
#include "OSELib/DPWS/DeviceDescription.h"

namespace OSELib {
namespace SDC {

class HelloReceivedHandler {
public:
    HelloReceivedHandler() = default;
    virtual ~HelloReceivedHandler() = default;

	virtual void helloReceived(const std::string & epr);
};

class ServiceManager final: public WithLogger {
public:
	ServiceManager();
	~ServiceManager();

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
	std::unique_ptr<SDCLib::Data::SDC::SDCConsumer> connect(const std::string & xaddr);

    /**
    * @brief Create a consumer and try to discover provider using endpointreference (EPR).
    *
    * @param epr The endpointreference
    * @return The consumer or null
    */
	std::unique_ptr<SDCLib::Data::SDC::SDCConsumer> discoverEndpointReference(const std::string & epr);

    /**
    * @brief Like discoverEndpointReference(const std::string & epr), but with a custom configuration
    *
    * @param epr The endpointreference configuration the custom configuration
    * @return The consumer or null
    */
	std::unique_ptr<SDCLib::Data::SDC::SDCConsumer> discoverEndpointReference(const std::string & epr, SDCLib::Data::SDC::MDPWSTransportLayerConfiguration ConsumerConfig);

    /**
    * @brief Discover all SDC providers currently available
    *
    * @return List of all providers
    */
	std::vector<std::unique_ptr<SDCLib::Data::SDC::SDCConsumer>> discoverOSCP();

private:
	std::unique_ptr<SDCLib::Data::SDC::SDCConsumer> connectXAddress(const std::list<std::string> xaddress, const std::string & epr);
	void resolveServiceURIsFromMetadata(const WS::MEX::MetadataSection & metadata,	OSELib::DPWS::DeviceDescription & deviceDescription);
	std::unique_ptr<DPWS::MDPWSDiscoveryClientAdapter> _dpwsClient;
	// todo: kick this helloCallback. Supposedly it is not needed.
	std::unique_ptr<DPWS::HelloCallback> _helloCallback;
	mutable Poco::Mutex _mutex;
	SDCLib::Data::SDC::MDPWSTransportLayerConfiguration configuration;
};

} /* namespace SDC */
} /* namespace OSELib */

#endif /* OSELIB_OSCP_SERVICEMANAGER_H_ */
