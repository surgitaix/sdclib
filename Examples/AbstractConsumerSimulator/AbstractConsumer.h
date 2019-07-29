/*
 * AbstractConsumer.h
 *
 *  Created on: Jul 23, 2019
 *      Author: rosenau
 */

#ifndef EXAMPLES_ABSTRACTCONSUMERSIMULATOR_ABSTRACTCONSUMER_H_
#define EXAMPLES_ABSTRACTCONSUMERSIMULATOR_ABSTRACTCONSUMER_H_

#include "osdm.hxx"
#include "OSELib/DPWS/DPWS11Constants.h"


#include "SDCLib/Data/SDC/SDCConsumer.h"
#include "SDCLib/Data/SDC/SDCConsumerConnectionLostHandler.h"
#include "SDCLib/Data/SDC/MDIB/custom/MdibContainer.h"

#include "MirrorProvider.h"
#include "SDCParticipantMDStateForwarder.h"

#include "OSELib/SDC/ServiceManager.h"

namespace SDCLib {
namespace Data {
namespace SDC {
namespace ACS {

class SDCParticipantNumericStateForwarder;
class SDCParticipantStreamStateForwarder;
class MyConnectionLostHandler;
class SDCParticipantActivateFunctionCaller;
class SDCParticipantStringFunctionCaller;
class SDCParticipantStringMetricHandler;


class AbstractConsumer {
public:
	AbstractConsumer();
	virtual ~AbstractConsumer() = default;

	bool discoverDUT(const std::string& deviceEPR);
	bool setupMirrorProvider(const std::string& MirrorProviderEndpointReference="DUTMirrorProvider");
	void startMirrorProvider();
	bool addGetHandler(HandleRef descriptionHandler);
	bool addSubscriptionHandler(HandleRef descriptionHandler);
	bool addSetHandler(HandleRef descriptionHandler);

	void setDUTEndpointRef(const std::string& EndpointRef);
	const std::string& getDUTEndpointRef();

	void setMirrorProviderEndpointRef(const std::string& EndpointRef);
	const std::string& getMirrorProviderEndpointRef();

	void updateAvailableEndpointReferences();

	const std::string getConsumerStringRepresentationOfMDIB();
	const std::string getMirrorProviderStringRepresentationOfMDIB();

private:
	const std::string getStringRepresentationOfMDIB(const MdibContainer MDIB);

	/*
	 * @brief Creates a SDCProvider to be discovered by the test orchestrator SDCConsumer.
	 * Providing services to discover the DUT and setting the MirrorProviders EndpointReference.
	 */
	void setupDiscoveryProvider();

	/*
	 * @brief Creates a new SDCInstance with IP6 enabled and bound to a free port.
	 *
	 * @return Returns the new SDCInstance if successful or a null_ptr if not.
	 */
	SDCInstance_shared_ptr createDefaultSDCInstance();

	std::string DUTMirrorProviderEndpointRef;
	std::string DUTEndpointRef;

	std::vector<std::string> availableEndpointReferences;

	std::unique_ptr<MirrorProvider> DUTMirrorProvider;
	std::unique_ptr<SDCConsumer> consumer;
	std::unique_ptr<OSELib::SDC::ServiceManager> serviceManager;


	std::shared_ptr<ActivateOperationDescriptor> discoverAvailableEndpointReferencesDesc;
	std::shared_ptr<StringMetricDescriptor> availableEndpointReferencesDesc;
	std::shared_ptr<StringMetricDescriptor> setDUTEndpointReferncesDesc;
	std::shared_ptr<ActivateOperationDescriptor> discoverDUTFunctionDesc;
	std::shared_ptr<StringMetricDescriptor> setMirrorProviderEndpointReferenceDesc;
	std::shared_ptr<ActivateOperationDescriptor> setupMirrorProviderDesc;

	std::unique_ptr<MyConnectionLostHandler> connectionLostHandler;
	std::shared_ptr<SDCParticipantActivateFunctionCaller> discoverAvailableEndpointReferencesCaller;
	std::shared_ptr<SDCParticipantStringMetricHandler> availableEndpointReferencesHandler;
	std::shared_ptr<SDCParticipantStringFunctionCaller> setDUTEndpointReferenceCaller;
	std::shared_ptr<SDCParticipantActivateFunctionCaller> discoverDUTFunctionCaller;
	std::shared_ptr<SDCParticipantStringFunctionCaller> setMirrorProviderEndpointReferenceCaller;
	std::shared_ptr<SDCParticipantActivateFunctionCaller> setupMirrorProviderCaller;
	std::map<std::string, std::shared_ptr<SDCParticipantActivateFunctionCaller>> addGetCallers;
	std::map<std::string, std::shared_ptr<SDCParticipantActivateFunctionCaller>> addSetCallers;
	std::map<std::string, std::shared_ptr<SDCParticipantActivateFunctionCaller>> addSubscribeCallers;


	//	std::map<std::string, std::shared_ptr<SDCParticipantNumericStateForwarder>> registeredNumericConsumerStateHandlers;
	//	std::map<std::string, std::shared_ptr<SDCParticipantStreamStateForwarder>> registeredStreamConsumerStateHandlers;
	//	std::map<std::string, std::shared_ptr<SDCParticipantMDStateGetForwarder<NumericMetricState>>> registeredActivateGetConsumerStateHandler;
	//	std::map<std::string, std::shared_ptr<ActivateOperationDescriptor>> registeredActivateDescriptors;
};
} //ACS
} //SDC
} //Data
} //SDCLib

#endif /* EXAMPLES_ABSTRACTCONSUMERSIMULATOR_ABSTRACTCONSUMER_H_ */
