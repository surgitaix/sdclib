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


	const std::string getConsumerStringRepresentationOfMDIB();
	const std::string getMirrorProviderStringRepresentationOfMDIB();

private:
	const std::string getStringRepresentationOfMDIB(const MdibContainer MDIB);

	std::unique_ptr<MirrorProvider> DUTMirrorProvider;
	std::unique_ptr<SDCConsumer> consumer;

//	std::map<std::string, std::shared_ptr<SDCParticipantNumericStateForwarder>> registeredNumericConsumerStateHandlers;
//	std::map<std::string, std::shared_ptr<SDCParticipantStreamStateForwarder>> registeredStreamConsumerStateHandlers;
//	std::map<std::string, std::shared_ptr<SDCParticipantMDStateGetForwarder<NumericMetricState>>> registeredActivateGetConsumerStateHandler;
//	std::map<std::string, std::shared_ptr<ActivateOperationDescriptor>> registeredActivateDescriptors;

	std::unique_ptr<MyConnectionLostHandler> connectionLostHandler;
	std::shared_ptr<SDCParticipantTriggerStringFunctionActivateHandler> setDUTEndpointReferenceHandler;
	std::shared_ptr<SDCParticipantTriggerFunctionActivateHandler> discoverDUTFunctionTriggerHandler;
	std::shared_ptr<SDCParticipantTriggerStringFunctionActivateHandler> setMirrorProviderEndpointReferenceHandler;
	std::shared_ptr<SDCParticipantTriggerFunctionActivateHandler> setupMirrorProviderHandler;
	std::shared_ptr<SDCParticipantTriggerFunctionActivateHandler> startMirrorProviderHandler;
	std::map<std::string, std::shared_ptr<SDCParticipantTriggerFunctionActivateHandler>> addGetTriggerHandlers;
	std::map<std::string, std::shared_ptr<SDCParticipantTriggerFunctionActivateHandler>> addSetTriggerHandlers;
	std::map<std::string, std::shared_ptr<SDCParticipantTriggerFunctionActivateHandler>> addSubscribeTriggerHandlers;
};
} //ACS
} //SDC
} //Data
} //SDCLib

#endif /* EXAMPLES_ABSTRACTCONSUMERSIMULATOR_ABSTRACTCONSUMER_H_ */
