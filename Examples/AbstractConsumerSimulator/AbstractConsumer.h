/*
 * AbstractConsumer.h
 *
 *  Created on: Jul 23, 2019
 *      Author: rosenau
 */

#ifndef EXAMPLES_ABSTRACTCONSUMERSIMULATOR_ABSTRACTCONSUMER_H_
#define EXAMPLES_ABSTRACTCONSUMERSIMULATOR_ABSTRACTCONSUMER_H_

#include <iostream>
#include "OSELib/DPWS/DPWS11Constants.h"
#include "OSELib/SDC/SDCConstants.h"


#include "SDCLib/Data/SDC/SDCConsumer.h"
#include "SDCLib/Data/SDC/SDCConsumerConnectionLostHandler.h"
#include "SDCLib/Data/SDC/MDIB/custom/MdibContainer.h"
#include "SDCLib/Data/SDC/MDIB/ActivateOperationDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/MdDescription.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/EnumStringMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ChannelDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricState.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricDescriptor.h"



#include "MirrorProvider.h"
#include "SDCParticipantMDStateForwarder.h"

#include "OSELib/SDC/ServiceManager.h"

namespace SDCLib {
namespace Data {
namespace SDC {
namespace ACS {

class SDCParticipantNumericStateForwarder;
class SDCParticipantStreamStateForwarder;
class SDCParticipantActivateFunctionCaller;
class SDCParticipantStringFunctionCaller;
class SDCProviderStringMetricHandler;
class SDCParticipantGetMDIBCaller;
template <typename TState>
class SDCParticipantMDStateGetForwarder;
class SDCParticipantNumericMetricStateForwarder;
class SDCParticipantNumericMetricSetStateForwarder;
class SDCParticipantRealTimeSampleArrayMetricStateForwarder;
class SDCParticipantStringMetricStateForwarder;
class SDCParticipantActivateForwarder;
class SDCParticipantStringMetricStateSetForwarder;
class BackBoneTestCaseEnum;


class MyConnectionLostHandler : public Data::SDC::SDCConsumerConnectionLostHandler {
public:
	MyConnectionLostHandler(Data::SDC::SDCConsumer & p_consumer) : m_consumer(p_consumer) {
	}
	void onConnectionLost() override {
		std::cerr << "Connection lost, disconnecting... ";
		m_consumer.disconnect();
		std::cerr << "disconnected." << std::endl;
	}
private:
	Data::SDC::SDCConsumer& m_consumer;
};


class AbstractConsumer {
public:
	AbstractConsumer();

	bool discoverDUT();
	bool setupMirrorProvider();
	void startMirrorProvider();

	void subscribeState(SDCConsumerOperationInvokedHandler * handler);
	void unsubscribeState(SDCConsumerOperationInvokedHandler * handler);

	void setDUTEndpointRef(const std::string& EndpointRef);
	const std::string& getDUTEndpointRef();

	void setMirrorProviderEndpointRef(const std::string& EndpointRef);
	const std::string& getMirrorProviderEndpointRef();

	void updateAvailableEndpointReferences();

	const std::string getConsumerStringRepresentationOfMDIB();
	const std::string getMirrorProviderStringRepresentationOfMDIB();

	/*
	 * @brief Creates a SDCProvider to be discovered by the test orchestrator SDCConsumer.
	 * Providing services to discover the DUT and setting the MirrorProviders EndpointReference.
	 */
	void setupDiscoveryProvider();


private:
	const std::string getStringRepresentationOfMDIB(const MdibContainer MDIB);

	MdsDescriptor getMessageManipulatorControlInterfaceMds();

	/*
	 * @brief Creates a new SDCInstance with IP6 enabled and bound to a free port.
	 *
	 * @return Returns the new SDCInstance if successful or a null_ptr if not.
	 */
	SDCInstance_shared_ptr createDefaultSDCInstance();

	std::string DUTMirrorProviderEndpointRef;
	std::string DUTEndpointRef;

	std::vector<std::string> availableEndpointReferences;

	std::unique_ptr<MirrorProvider> DiscoveryProvider;
	std::unique_ptr<MirrorProvider> DUTMirrorProvider;
	std::unique_ptr<SDCConsumer> consumer;
	std::unique_ptr<OSELib::SDC::ServiceManager> serviceManager;
	std::unique_ptr<MyConnectionLostHandler> connectionLostHandler;

	//DiscoveryProvider Descriptors
	std::shared_ptr<ActivateOperationDescriptor> discoverAvailableEndpointReferencesDesc;
	std::shared_ptr<StringMetricDescriptor> availableEndpointReferencesDesc;
	std::shared_ptr<StringMetricDescriptor> setDUTEndpointReferncesDesc;
	std::shared_ptr<ActivateOperationDescriptor> discoverDUTFunctionDesc;
	std::shared_ptr<StringMetricDescriptor> setMirrorProviderEndpointReferenceDesc;
	std::shared_ptr<ActivateOperationDescriptor> setupMirrorProviderDesc;

	//DiscoveryProvider State/Function Handler
	std::shared_ptr<SDCParticipantActivateFunctionCaller> discoverAvailableEndpointReferencesCaller;
	std::shared_ptr<SDCProviderStringMetricHandler> availableEndpointReferencesHandler;
	std::shared_ptr<SDCParticipantStringFunctionCaller> setDUTEndpointReferenceCaller;
	std::shared_ptr<SDCParticipantActivateFunctionCaller> discoverDUTFunctionCaller;
	std::shared_ptr<SDCParticipantStringFunctionCaller> setMirrorProviderEndpointReferenceCaller;
	std::shared_ptr<SDCParticipantActivateFunctionCaller> setupMirrorProviderCaller;

	//AbstractConsumer Descriptors
	std::shared_ptr<ActivateOperationDescriptor> getDUTMDIBCallerDesc;
	std::shared_ptr<StringMetricDescriptor> getDUTMDIBDesc;

	//AbstractConsumer State/Function Handler
	std::shared_ptr<SDCParticipantGetMDIBCaller> getDUTMDIBCaller;
	std::shared_ptr<SDCProviderStringMetricHandler> getDUTMDIBHandler;

	std::map<std::string, std::shared_ptr<SDCParticipantMDStateGetForwarder<NumericMetricState>>> registeredNumericMetricStateActivateGetCaller;
	std::map<std::string, std::shared_ptr<ActivateOperationDescriptor>> numericMetricStateActivateGetCallerDescriptors;
	std::map<std::string, std::shared_ptr<SDCParticipantNumericMetricStateForwarder>> numericMetricStateForwarder;
	std::map<std::string, std::shared_ptr<SDCParticipantNumericMetricSetStateForwarder>>numericMetricStateSetForwarder;
	std::map<std::string, std::shared_ptr<SDCParticipantActivateFunctionCaller>> numericMetricStateActivateSubscribeCaller;
	std::map<std::string, std::shared_ptr<ActivateOperationDescriptor>> numericMetricStateSubscribeCallerDescriptors;
	std::map<std::string, std::shared_ptr<SDCParticipantActivateFunctionCaller>> numericMetricStateActivateUnsubscribeCaller;
	std::map<std::string, std::shared_ptr<ActivateOperationDescriptor>> numericMetricStateUnsubscribeCallerDescriptors;


	std::map<std::string, std::shared_ptr<SDCParticipantMDStateGetForwarder<StringMetricState>>> registeredStringMetricStateActivateGetCaller;
	std::map<std::string, std::shared_ptr<ActivateOperationDescriptor>> stringMetricStateActivateGetCallerDescriptors;
	std::map<std::string, std::shared_ptr<SDCParticipantStringMetricStateForwarder>> stringMetricStateForwarder;
	std::map<std::string, std::shared_ptr<SDCParticipantStringMetricStateSetForwarder>> stringMetricStateSetForwarder;
	std::map<std::string, std::shared_ptr<SDCParticipantActivateFunctionCaller>> stringMetricStateActivateSubscribeCaller;
	std::map<std::string, std::shared_ptr<ActivateOperationDescriptor>> stringMetricStateSubscribeCallerDescriptors;
	std::map<std::string, std::shared_ptr<SDCParticipantActivateFunctionCaller>> stringMetricStateActivateUnsubscribeCaller;
	std::map<std::string, std::shared_ptr<ActivateOperationDescriptor>> stringMetricStateUnsubscribeCallerDescriptors;


	std::map<std::string, std::shared_ptr<SDCParticipantMDStateGetForwarder<RealTimeSampleArrayMetricState>>> registeredRealTimeSampleArrayMetricStateActivateGetCaller;
	std::map<std::string, std::shared_ptr<ActivateOperationDescriptor>> realTimeSampleArrayMetricStateActivateGetCallerDescriptors;
	std::map<std::string, std::shared_ptr<SDCParticipantRealTimeSampleArrayMetricStateForwarder>> realTimeSampleArrayMetricStateForwarder;
	std::map<std::string, std::shared_ptr<SDCParticipantActivateFunctionCaller>> realTimeSampleArrayMetricStateActivateSubscribeCaller;
	std::map<std::string, std::shared_ptr<ActivateOperationDescriptor>> realTimeSampleArrayMetricStateSubscribeCallerDescriptors;
	std::map<std::string, std::shared_ptr<SDCParticipantActivateFunctionCaller>> realTimeSampleArrayMetricStateActivateUnsubscribeCaller;
	std::map<std::string, std::shared_ptr<ActivateOperationDescriptor>> realTimeSampleArrayMetricStateUnsubscribeCallerDescriptors;

	std::map<std::string, std::shared_ptr<SDCParticipantActivateForwarder>> activateForwarder;

	std::map<std::string, std::shared_ptr<BackBoneTestCaseEnum>> bbTestCaseEnumHandles;
	std::map<std::string, std::shared_ptr<EnumStringMetricDescriptor>> bbTestCaseEnumDescriptors;




	//	std::map<std::string, std::shared_ptr<SDCParticipantNumericStateForwarder>> registeredNumericConsumerStateHandlers;
	//	std::map<std::string, std::shared_ptr<SDCParticipantStreamStateForwarder>> registeredStreamConsumerStateHandlers;
	//	std::map<std::string, std::shared_ptr<ActivateOperationDescriptor>> registeredActivateDescriptors;
};
} //ACS
} //SDC
} //Data
} //SDCLib

#endif /* EXAMPLES_ABSTRACTCONSUMERSIMULATOR_ABSTRACTCONSUMER_H_ */
