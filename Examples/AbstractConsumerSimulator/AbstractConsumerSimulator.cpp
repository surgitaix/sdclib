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

#include "osdm.hxx"

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

	Network::TCPClientEventHandler::getInstance("127.0.0.1", 5000)->startup();

	AbstractConsumer consumer;
	consumer.setupDiscoveryProvider();
	waitForUserInput();


//	Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer") << "Startup";
//    SDCLibrary::getInstance().startup(OSELib::LogLevel::None);
//	SDCLibrary::getInstance().setPortStart(6000);
//
//	//On connection loss inform Test orchestrator
//    class MyConnectionLostHandler : public Data::SDC::SDCConsumerConnectionLostHandler {
//    public:
//    	MyConnectionLostHandler(Data::SDC::SDCConsumer & consumer) : consumer(consumer) {
//    	}
//    	void onConnectionLost() override {
//    		std::cerr << "Connection lost, disconnecting... ";
//    		consumer.disconnect();
//    		std::cerr << "disconnected." << std::endl;
//    	}
//    private:
//    	Data::SDC::SDCConsumer & consumer;
//    };
//
//    // Create a new SDCInstance (no flag will auto init) for Consumer
//    auto t_SDCInstance = std::make_shared<SDCInstance>();
//	// Some restriction
//	t_SDCInstance->setIP6enabled(false);
//	t_SDCInstance->setIP4enabled(true);
//	// Bind it to interface that matches the internal criteria (usually the first enumerated)
//	if(!t_SDCInstance->bindToDefaultNetworkInterface()) {
//		std::cout << "Failed to bind to default network interface! Exit..." << std::endl;
//		return -1;
//	}
//
//
//	//Discovery of Device under Test
//	OSELib::SDC::ServiceManager oscpsm(t_SDCInstance);
//
//	std::unique_ptr<Data::SDC::SDCConsumer> c(oscpsm.discoverEndpointReference(deviceEPR));
//
//
//	try {
//		if (c != nullptr) {
//			Data::SDC::SDCConsumer & consumer = *c;
//			std::unique_ptr<MyConnectionLostHandler> myHandler(new MyConnectionLostHandler(consumer));
//			consumer.setConnectionLostHandler(myHandler.get());
//
//			Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer") << "Discovery succeeded." << std::endl << std::endl << "Waiting 5 sec. for the subscriptions to beeing finished";
//
//
//		    // Create a new SDCInstance (no flag will auto init) for Consumer
//			auto t_SDCInstanceProvider = std::make_shared<SDCInstance>();		    // Some restriction
//		    t_SDCInstanceProvider->setIP6enabled(false);
//		    t_SDCInstanceProvider->setIP4enabled(true);
//		    // Bind it to interface that matches the internal criteria (usually the first enumerated)
//		    if(!t_SDCInstanceProvider->bindToDefaultNetworkInterface()) {
//		        std::cout << "Failed to bind to default network interface! Exit..." << std::endl;
//		        return -1;
//		    }
//
//			//initialize Mirror Provider which mirrors the behavior of the DUT
//			MirrorProvider mirrorProvider(t_SDCInstanceProvider);
//			mirrorProvider.setEndpointReference("DUTMirrorProvider");
//			Dev::DeviceCharacteristics devChar;
//			devChar.addFriendlyName("en", "DUTMirrorProvider");
//			mirrorProvider.setDeviceCharacteristics(devChar);
//			mirrorProvider.setMdDescription(getStringRepresentationOfMDIB(consumer.getMdib()));


			//std::cout << getStringRepresentationOfMDIB(consumer.getMdib()) << std::endl;

			// create handler register them to the provider under test and connect them to the "mirror provider"
//			//should be triggered???
//			for (auto RealTimeSampleArrayMetricState :
//					consumer.getMdib().getMdState().findRealTimeSampleArrayMetricStates())
//			{
//				std::string handleStreamMetric = RealTimeSampleArrayMetricState.getDescriptorHandle();
//				Util::DebugOut(Util::DebugOut::Default, "AbstractConsumerSimulator") << "Adding Stream Metric " << handleStreamMetric << std::endl;
//				std::shared_ptr<SDCParticipantStreamStateForwarder> eh_stream(new SDCParticipantStreamStateForwarder(handleStreamMetric));
//				mirrorProvider.addMdStateHandler(eh_stream.get());
//				consumer.registerStateEventHandler(eh_stream.get());
//				registeredStreamConsumerStateHandlers.insert(std::make_pair(handleStreamMetric, eh_stream));
//			}
//
//
//			// create handler register them to the provider under test and connect them to the "mirror provider"
//			for (auto NumericMetricState :
//					consumer.getMdib().getMdState().findNumericMetricStates())
//			{
//				std::string handleNumericMetric = NumericMetricState.getDescriptorHandle();
//				Util::DebugOut(Util::DebugOut::Default, "AbstractConsumerSimulator") << "Adding Numeric Metric " <<  handleNumericMetric << std::endl;
//				std::shared_ptr<SDCParticipantNumericStateForwarder> eh_numeric(new SDCParticipantNumericStateForwarder(handleNumericMetric));
//				mirrorProvider.addMdStateHandler(eh_numeric.get());
//				consumer.registerStateEventHandler(eh_numeric.get());
//				registeredNumericConsumerStateHandlers.insert(std::make_pair(handleNumericMetric, eh_numeric));
//				for (auto Mds : consumer.getMdDescription().getMdsList())
//					for (setValueOperationDescriptor = Mds.getSco().collectAllSetValueOperationDescriptors()):
//				createSetOperationForDescriptor(eh_numeric.get, )
//			}

//			std::map<std::string, std::shared_ptr<SDCParticipantNumericStateForwarder>> registeredNumericConsumerStateHandlers;
//			std::map<std::string, std::shared_ptr<SDCParticipantStreamStateForwarder>> registeredStreamConsumerStateHandlers;
//			std::map<std::string, std::shared_ptr<SDCParticipantMDStateGetForwarder<NumericMetricState>>> registeredActivateGetConsumerStateHandler;
//			std::map<std::string, std::shared_ptr<ActivateOperationDescriptor>> registeredActivateDescriptors;
//
//
//
//			for (auto Mds : consumer.getMdDescription().getMdsList())
//			{
//				for(auto Vmd : Mds.getVmdList())
//				{
//					for (auto Channel : Vmd.getChannelList())
//					{
//						for (auto MetricDescriptor : Channel.getStringMetricDescriptorList())
//						{
//
//						}
//						for (auto MetricDescriptor : Channel.getNumericMetricDescriptorList())
//						{
//							auto handleNumericMetric = MetricDescriptor.getHandle();
//							std::shared_ptr<SDCParticipantNumericStateForwarder> efh_numeric(new SDCParticipantNumericStateForwarder(handleNumericMetric));
//							mirrorProvider.addMdStateHandler(efh_numeric.get());
//							mirrorProvider.createSetOperationForDescriptor(MetricDescriptor, Mds);
//							consumer.registerStateEventHandler(efh_numeric.get());
//							registeredNumericConsumerStateHandlers.insert(std::make_pair(handleNumericMetric, efh_numeric));
//							std::shared_ptr<SDCParticipantMDStateGetForwarder<NumericMetricState>> afh_numeric(new SDCParticipantMDStateGetForwarder<NumericMetricState>(handleNumericMetric + ACTIVATE_FOR_GET_OPERATION_ON_DUT_POSTFIX));
//							mirrorProvider.addMdStateHandler(afh_numeric.get());
//							std::shared_ptr<ActivateOperationDescriptor> getNumericMetricRequestDescriptor(new ActivateOperationDescriptor(handleNumericMetric + ACTIVATE_FOR_GET_OPERATION_ON_DUT_POSTFIX, handleNumericMetric));
//							mirrorProvider.addActivateOperationForDescriptor(*getNumericMetricRequestDescriptor.get(), Mds);
//							registeredActivateGetConsumerStateHandler.insert(std::make_pair(handleNumericMetric, afh_numeric));
//							registeredActivateDescriptors.insert(std::make_pair(handleNumericMetric + ACTIVATE_FOR_GET_OPERATION_ON_DUT_POSTFIX, getNumericMetricRequestDescriptor));
//						}
//						for (auto MetricDescriptor : Channel.getEnumStringMetricDescriptorList())
//						{
//
//						}
//						for (auto MetricDescriptor : Channel.getRealTimeSampleArrayMetricDescriptorList())
//						{
//							auto handleStreamMetric = MetricDescriptor.getHandle();
//							std::shared_ptr<SDCParticipantStreamStateForwarder> eh_stream(new SDCParticipantStreamStateForwarder(handleStreamMetric));
//							mirrorProvider.addMdStateHandler(eh_stream.get());
//							consumer.registerStateEventHandler(eh_stream.get());
//							registeredStreamConsumerStateHandlers.insert(std::make_pair(handleStreamMetric, eh_stream));
//						}
//					}
//				}
//			}

//			for (auto MDs : consumer.getMdDescription().getMdsList())
//			{
//				ScoDescriptor sco = MDs.getSco();
//				for (auto setStringOperationDescriptors : sco.collectAllSetStringOperationDescriptors())
//				{
//					mirrorProvider.addMdStateHandler(setStringOperationDescriptors);
//				}
//			}



//			std::map<std::string, std::shared_ptr<SDCParticipantAlertConditionStateForwarder>> registeredAlertConditionStateForwarder;
//			for (auto AlertConditionState : consumer.getMdib().getMdState().findAlertConditionStates())
//			{
//				std::string handleAlertConditionState = AlertConditionState.getDescriptorHandle();
//				Util::DebugOut(Util::DebugOut::Default, "AbstractConsumerSimulator") << handleAlertConditionState << std::endl;
//				std::shared_ptr<SDCParticipantAlertConditionStateForwarder> eh_numeric(new SDCParticipantAlertConditionStateForwarder(handleNumericMetric));
//				mirrorProvider.addMdStateHandler(eh_numeric.get());
//				consumer.registerStateEventHandler(eh_numeric.get());
//				registeredAlertConditionStateForwarder.insert(std::make_pair(handleAlertConditionState, eh_numeric));
//			}
//
//			mirrorProvider.startup();
//			mirrorProvider.start();
//
//
//			std::cout << "MirrorProvider Mdib: " << getStringRepresentationOfMDIB(mirrorProvider.getMdib());
//
//			std::cout << "MirrorProvider Endpoint: " << mirrorProvider.getEndpointReference();
//
//			waitForUserInput(); // wait for finish from Test orchestrator
//			// unregister all handler
//			consumer.disconnect();
//			mirrorProvider.shutdown();
//		} else {
//			Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer") << "Discovery failed."; //Not debug out but inform orchestrator
//		}
//
//} catch (std::exception & e){
//		Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer") << "Exception: " << e.what() << std::endl; //Not debug out but inform orchestrator
//	}
//    SDCLibrary::getInstance().shutdown();
//    Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer") << "Shutdown." << std::endl; //Not debug out but inform orchestrator

}
