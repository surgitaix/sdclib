/*
 * AbstractConsumerSimulator.cpp
 *
 *  Created on: Apr 5, 2019
 *      Author: rosenau
 */

/*
 * AbstractConsumerSiumulator that provides all Set-Operation, Activation-Operation and Subscription-Capabilities
 * to control, request and process all information it gets from the Provider Under Test.
 *
 */


#include "OSELib/DPWS/DPWS11Constants.h"

#include "SDCLib/SDCLibrary.h"
#include "SDCLib/SDCInstance.h"

#include "SDCLib/Data/SDC/SDCConsumer.h"
#include "SDCLib/Data/SDC/SDCConsumerConnectionLostHandler.h"
#include "SDCLib/Data/SDC/SDCConsumerMDStateHandler.h"
#include "SDCLib/Data/SDC/SDCProviderMDStateHandler.h"
#include "SDCLib/Data/SDC/SDCProvider.h"
#include "SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricState.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricState.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricValue.h"
#include "SDCLib/Data/SDC/MDIB/SampleArrayValue.h"
#include "SDCLib/Data/SDC/MDIB/MdState.h"
#include "SDCLib/Data/SDC/MDIB/custom/MdibContainer.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/MdDescription.h"
#include "SDCLib/Data/SDC/MDIB/ScoDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/SetAlertStateOperationDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/SetContextStateOperationDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/SetStringOperationDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/SetValueOperationDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ActivateOperationDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/VmdDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/EnumStringMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ChannelDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/MetricQuality.h"
#include "SDCLib/Data/SDC/MDIB/ActivateOperationDescriptor.h"
#include "SDCLib/Data/SDC/FutureInvocationState.h"



#include "SDCParticipantMDStateForwarder.h"
#include "MirrorProvider.h"

#include "SDCLib/Util/DebugOut.h"

#include "OSELib/SDC/ServiceManager.h"
#include "OSELib/TCP/TCPClientEventHandler.h"
#include "OSELib/TCP/TCPBroadcastServerHandler.h"
#include "AbstractConsumer.h"

using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;
using namespace SDCLib::Data::SDC::ACS;

const std::string deviceEPR("UDI-1234567890"); //needs to be configured

//class SDCParticipantStreamStateForwarder : public SDCParticipantMDStateForwarder<RealTimeSampleArrayMetricState> {
//public:
//	SDCParticipantStreamStateForwarder(const std::string descriptorHandle) : SDCParticipantMDStateForwarder(descriptorHandle) {}
//
//	RealTimeSampleArrayMetricState getInitialState() override {
//		RealTimeSampleArrayMetricState realTimeSampleArrayState(SDCProviderMDStateHandler::descriptorHandle);
//		realTimeSampleArrayState.setActivationState(ComponentActivation::On);
//		return realTimeSampleArrayState;
//	}
//
//};
//
//
//class SDCParticipantNumericStateForwarder : public SDCParticipantMDStateForwarder<NumericMetricState> {
//public:
//	SDCParticipantNumericStateForwarder(std::string descriptorHandle) : SDCParticipantMDStateForwarder(descriptorHandle) {}
//
//	NumericMetricState getInitialState() override {
//		NumericMetricState numericMetricState(SDCProviderMDStateHandler::descriptorHandle);
//		numericMetricState.setActivationState(ComponentActivation::On);
//		numericMetricState.setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Vld)));
//		return numericMetricState;
//	}
//	void onStateChanged(const NumericMetricState & state)  {
//        double val = state.getMetricValue().getValue();
//        DebugOut(DebugOut::Default, "ExampleConsumer") << "Consumer: Received value changed of " << this->SDCProviderStateHandler::getDescriptorHandle() << ": " << val << std::endl;
//		SDCProviderStateHandler::updateState(state);
//	}
//
//    InvocationState onStateChangeRequest(const NumericMetricState & state , const OperationInvocationContext & oic) override {
//    	// extract information from the incoming operation
//    	SDCProviderStateHandler::notifyOperationInvoked(oic, InvocationState::Start);
//    	FutureInvocationState fis;
//    	getParentConsumer().commitState(state, fis);
//    	Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer") << "Commit result metric state: " << fis.waitReceived(InvocationState::Fin, 10000);
//    	auto providerUpdatedState = getParentConsumer().requestState<NumericMetricState>(state.getDescriptorHandle());
//    	if(state.getMetricValue().getValue() == providerUpdatedState->getMetricValue().getValue())
//    	{
//    		std::cout << "SUCCESS!!!!" << std::endl;
//        	return InvocationState::Fin;
//    	}
//    	return InvocationState::Fail;
//    }
//};

//class SDCParticipantAlertConditionStateForwarder : public SDCParticipantMDStateForwarder<AlertConditionState> {
//	SDCParticipantAlertConditionStateForwarder(std::string descriptorHandle) : SDCParticipantMDStateForwarder(descriptroHandle) {}
//
//	AlertConditionState getInitialState() override {
//		AlertConditionState alertConditionState(SDCProviderMDStateHandler::descriptorHandle);
//		return alertConditionState;
//	}
//};


void waitForUserInput() {
	std::string temp;
	Util::DebugOut(Util::DebugOut::Default, "") << "Press key to proceed.";
	std::cin >> temp;
}




int main() {
    SDCLibrary::getInstance().startup(OSELib::LogLevel::Error);

	Network::TCPClientEventHandler::getInstance("127.0.0.1", 7001)->startup();
	Network::TCPBroadcastServerHandler::getInstance("127.0.0.1", 8000)->startup();

	AbstractConsumer consumer;
	consumer.setupDiscoveryProvider();
	waitForUserInput();

}
