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

#include "SDCLib/Prerequisites.h"

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
	ServiceManager(SDCLib::SDCInstance_shared_ptr p_SDCInstance);
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
    * @brief Discover all SDC providers currently available
    *
    * @return List of all providers
    */
    using DiscoverResults = std::vector<std::unique_ptr<SDCLib::Data::SDC::SDCConsumer>>;
	DiscoverResults discoverOSCP();

    /**
     * @brief Discover all SDC providers currently available in an async manner
     * 
     * @return std::future of a list of all providers (DiscoverResults)
     */
    using AsyncDiscoverResults  = std::future<DiscoverResults>;
    AsyncDiscoverResults async_discoverOSCP();

	/**
	* @brief Discover all SDC providers currently available
	*
	* @return List of all provider eprs
	*/
	std::vector<std::string> discoverEndpointReferences();


private:

    SDCLib::SDCInstance_shared_ptr m_SDCInstance = nullptr;
    std::unique_ptr<DPWS::MDPWSDiscoveryClientAdapter> _dpwsClient;

    // todo: kick this helloCallback. Supposedly it is not needed.
	std::unique_ptr<DPWS::HelloCallback> _helloCallback;
	mutable Poco::Mutex _mutex;


    //  DONT MIX MEMBER FUNCTIONS AND DATA...
    std::unique_ptr<SDCLib::Data::SDC::SDCConsumer> connectXAddress(const std::list<std::string> xaddress, const std::string & epr);
    void resolveServiceURIsFromMetadata(const WS::MEX::MetadataSection & metadata, OSELib::DPWS::DeviceDescription & deviceDescription);
};

} /* namespace SDC */
} /* namespace OSELib */

#endif /* OSELIB_OSCP_SERVICEMANAGER_H_ */
