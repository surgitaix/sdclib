/*
 * test_ServiceProvider_AlertSystemState_11073_10207_R0116.cpp
 *
 *  Created on: Dec 3, 2018
 *      Author: rosenau
 */

#include <iostream>

#include "OSCLib/SDCInstance.h"

#include "OSCLib/SDCLibrary.h"
#include "OSCLib/Data/SDC/SDCProvider.h"
#include "OSCLib/Data/SDC/SDCConsumer.h"
#include "OSELib/SDC/ServiceManager.h"

#include "OSCLib/Util/Task.h"

#include "OSCLib/Data/SDC/SDCConsumerConnectionLostHandler.h"
#include "OSCLib/Data/SDC/MDIB/AlertSystemDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/SDC/MDIB/AlertConditionState.h"
#include "OSCLib/Data/SDC/MDIB/AlertSystemState.h"
#include "OSCLib/Data/SDC/MDIB/AlertSignalState.h"
#include "OSCLib/Data/SDC/MDIB/AlertConditionDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/MdDescription.h"
#include "OSCLib/Data/SDC/SDCProviderAlertConditionStateHandler.h"
#include "OSCLib/Data/SDC/SDCConsumerMDStateHandler.h"

#include "OSCLib/Data/SDC/MDPWSTransportLayerConfiguration.h"

#include "BICEPS_MessageModel-fwd.hxx"

#include "OSCLib/Util/DebugOut.h"



const std::string DEVICE_EPR("AlertProvider");
const std::string HANDLE_ALERT_CONDITION("handle_alert");
const std::string HANDLE_SYSTEM_ALERT_STATE("handle_system_alert_state");
const std::string ALERT_SYSTEM_HANDLE("handle_alert_system");
const std::string MDS_HANDLE ("mds_handle");


using namespace SDCLib;
using namespace SDCLib::Data;
using namespace SDCLib::Data::SDC;

template <typename Enumeration>
auto as_integer(Enumeration const value)
    -> typename std::underlying_type<Enumeration>::type
{
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

class AlertProviderStateHandler : public SDCProviderAlertConditionStateHandler<AlertConditionState>
{
public:

	AlertProviderStateHandler(std::string decriptorHandle) : SDCProviderAlertConditionStateHandler(decriptorHandle) {
	}

	void sourceHasChanged(const std::string & sourceHandle) override {
		std::cout << sourceHandle;
	}


	void setAlert(const AlertActivation & alertActivation) {
		AlertConditionState newAlertState(HANDLE_ALERT_CONDITION, alertActivation);
		updateState(newAlertState);
	}

	InvocationState onStateChangeRequest(const AlertConditionState & state, const OperationInvocationContext & oic) override {
		notifyOperationInvoked(oic, InvocationState::Start);
		// Do something if a state change is requested
		// return Finished if successful
		return InvocationState::Fin;
	}


	AlertConditionState getInitialState() override {
		AlertConditionState result(HANDLE_ALERT_CONDITION, AlertActivation::Off);
		return result;
	}

private:
	std::string descriptorHandle;

};


class AlertConsumerStateHandler : public SDCConsumerMDStateHandler<AlertConditionState> {
public:
	AlertConsumerStateHandler(const std::string descriptorHandle) : SDCConsumerMDStateHandler(descriptorHandle)
	{

	}

	void onStateChanged(const AlertConditionState &) override {
		Util::DebugOut(Util::DebugOut::Default, "PeriodicEvents") << "Consumer: Received alert condition change of " << descriptorHandle << std::endl;

	}
};


class SystemAlertProviderStateHandler : public SDCProviderAlertConditionStateHandler<AlertSystemState> {
public:
	SystemAlertProviderStateHandler(const std::string descriptorHandle) : SDCProviderAlertConditionStateHandler(descriptorHandle)
	{

	}

	void sourceHasChanged(const std::string & sourceHandle) override {
		std::cout << sourceHandle;
	}

	InvocationState onStateChangeRequest(const AlertSystemState &, const OperationInvocationContext & oic) override {
		notifyOperationInvoked(oic, InvocationState::Start);
		// Do something if a state change is requested
		// return Finished if successful
		return InvocationState::Fin;
	}

	AlertSystemState getInitialState() override {
		AlertSystemState result(HANDLE_SYSTEM_ALERT_STATE, AlertActivation::Off);
		return result;
	}

	void setAlert(const AlertActivation & alertActivation) {
		AlertSystemState newAlertState(HANDLE_SYSTEM_ALERT_STATE, alertActivation);
		updateState(newAlertState);
	}

};



class SystemAlertConsumerStateHandler : public SDCConsumerMDStateHandler<AlertSystemState> {
public:
	SystemAlertConsumerStateHandler(const std::string descriptorHandle) : SDCConsumerMDStateHandler(descriptorHandle)
	{

	}

	void onStateChanged(const AlertSystemState &) override {
		Util::DebugOut(Util::DebugOut::Default, "PeriodicEvents") << "Consumer: Received alert condition change of " << descriptorHandle << std::endl;
	}
};


class OSCPStreamProvider : public Util::Task {
public:

    OSCPStreamProvider() :
    	sdcProvider(),
		alertProviderStateHandler(HANDLE_ALERT_CONDITION),
		alertConditionDescriptor(HANDLE_ALERT_CONDITION,
								 AlertConditionKind::Phy,
								 AlertConditionPriority::Hi),
		systemAlertProviderStateHandler(HANDLE_SYSTEM_ALERT_STATE),
		systemAlertCondtionDescriptor(HANDLE_SYSTEM_ALERT_STATE)
    {

    	MDPWSTransportLayerConfiguration providerConfig = MDPWSTransportLayerConfiguration();
		providerConfig.setPort(6472);
		sdcProvider.setConfiguration(providerConfig);
		sdcProvider.setEndpointReference(DEVICE_EPR);

		sdcProvider.addHandleForPeriodicEvent(HANDLE_ALERT_CONDITION);
		sdcProvider.addMdStateHandler(&alertProviderStateHandler);
		sdcProvider.addHandleForPeriodicEvent(ALERT_SYSTEM_HANDLE);
		sdcProvider.addMdStateHandler(&systemAlertProviderStateHandler);

    }

    void startup() {
    	sdcProvider.startup();
    }

    void shutdown() {
    	sdcProvider.shutdown();
    }

private:

    SDCProvider sdcProvider;
    AlertProviderStateHandler alertProviderStateHandler;
    SystemAlertProviderStateHandler systemAlertProviderStateHandler;
    AlertConditionDescriptor alertConditionDescriptor;
    AlertSystemDescriptor systemAlertCondtionDescriptor;


public:
    virtual void runImpl() override {
		while (!isInterrupted()) {
			{
			}
			alertProviderStateHandler.setAlert(AlertActivation::Off);
			Poco::Thread::sleep(1000);
		}
    }
};



int main()
{
	std::cout << "Test against requirement R0116 from IEEE 11073-10207";
	SDCLibrary::getInstance().startup(OSELib::LogLevel::Error);
	SDCLibrary::getInstance().setIP6enabled(false);
	SDCLibrary::getInstance().setIP4enabled(true);
	SDCLibrary::getInstance().setPortStart(12000);

	class MyConnectionLostHandler : public Data::SDC::SDCConsumerConnectionLostHandler {
	    public:
	    	MyConnectionLostHandler(Data::SDC::SDCConsumer & consumer) : consumer(consumer) {
	    	}
	    	void onConnectionLost() override {
	    		std::cerr << "Connection lost, disconnecting... ";
	    		consumer.disconnect();
	    		std::cerr << "disconnected." << std::endl;
	    	}
	    private:
	    	Data::SDC::SDCConsumer & consumer;
	    };

	OSCPStreamProvider provider;
	provider.startup();
	provider.start();

	// Discovery
	OSELib::SDC::ServiceManager oscpsm;
	// binding to a custom port
	MDPWSTransportLayerConfiguration config = MDPWSTransportLayerConfiguration();
	config.setPort(6473);

	std::unique_ptr<Data::SDC::SDCConsumer> c(oscpsm.discoverEndpointReference(DEVICE_EPR, config));

	if (c != nullptr) {
		Data::SDC::SDCConsumer & consumer = *c;
		std::unique_ptr<MyConnectionLostHandler> myHandler(new MyConnectionLostHandler(consumer));
		consumer.setConnectionLostHandler(myHandler.get());

		AlertConsumerStateHandler alertConditionConsumerHandler(HANDLE_ALERT_CONDITION);

		consumer.registerStateEventHandler(&alertConditionConsumerHandler);

		Poco::Thread::sleep(2000);

		consumer.unregisterStateEventHandler(&alertConditionConsumerHandler);

		consumer.disconnect();
	}

	provider.shutdown();
	SDCLibrary::getInstance().shutdown();
	Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Shutdown." << std::endl;

	std::cout << "Test failed";
}
