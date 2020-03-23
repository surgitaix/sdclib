/*
 * ReferenceProviderSSL.cpp
 *
 *  @Copyright (C) 2016, SurgiTAIX AG
 *  Author: baumeister, rosenau
 *
 *  This Program implements the Reference Provider defined in: "SDC_Reference.docx"
 */



#include "SDCLib/Data/SDC/SDCProvider.h"

#include "SDCLib/SDCLibrary.h"
#include "SDCLib/SDCInstance.h"

#include "SDCLib/Data/SDC/SDCProviderStateHandler.h"
#include "SDCLib/Data/SDC/SDCProviderMDStateHandler.h"
#include "SDCLib/Data/SDC/SDCProviderAlertConditionStateHandler.h"
#include "SDCLib/Data/SDC/SDCProviderActivateOperationHandler.h"
#include "SDCLib/Data/SDC/MDIB/MdsState.h"
#include "SDCLib/Data/SDC/MDIB/AlertConditionState.h"
#include "SDCLib/Data/SDC/MDIB/AlertSignalState.h"
#include "SDCLib/Data/SDC/MDIB/AlertSystemState.h"
#include "SDCLib/Data/SDC/MDIB/ChannelDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"
#include "SDCLib/Data/SDC/MDIB/EnumStringMetricState.h"
#include "SDCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "SDCLib/Data/SDC/MDIB/LocalizedText.h"
#include "SDCLib/Data/SDC/MDIB/LocationContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/LocationContextState.h"
#include "SDCLib/Data/SDC/MDIB/LocationDetail.h"
#include "SDCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/MdDescription.h"
#include "SDCLib/Data/SDC/MDIB/MetricQuality.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricState.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricValue.h"
#include "SDCLib/Data/SDC/MDIB/PatientContextState.h"
#include "SDCLib/Data/SDC/MDIB/Range.h"
#include "SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricState.h"
#include "SDCLib/Data/SDC/MDIB/SampleArrayValue.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricState.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricValue.h"
#include "SDCLib/Data/SDC/MDIB/SystemContextState.h"

#include "SDCLib/Data/SDC/MDIB/custom/OperationInvocationContext.h"

#include "SDCLib/Util/DebugOut.h"
#include "SDCLib/Util/Task.h"

#include <thread>


using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

const std::string FILE_CACHED_MDIB{"referenceMDIB.xml"};

const std::string DEVICE_EPR("UDI-1234567890-SSL");

const std::string VMD_DESCRIPTOR_HANDLE("holdingDevice_vmd");
const std::string CHANNEL_DESCRIPTOR_HANDLE("holdingDevice_channel");
const std::string MDS_DESCRIPTOR_HANDLE("holdingDevice_mds");
const std::string LOCATION_CONTEXT_HANDLE("location_context");
const std::string SYSTEM_CONTEXT_HANDLE("system_context");

const std::string HANDLE_STATIC_GET_NM{"numeric.ch0.vmd0"};
const std::string HANDLE_DYNAMIC_GET_NM{"numeric.ch1.vmd0"};
const std::string HANDLE_SET_NM{"numeric.ch0.vmd1"};
const std::string HANDLE_STATIC_GET_STRM{"string.ch0.vmd0"};
const std::string HANDLE_DYNAMIC_GET_STRM{"dummy"};
const std::string HANDLE_SET_STRM{"string.ch0.vmd1"};
const std::string HANDLE_STATIC_GET_ESTRM{"enumstring.ch0.vmd0"};
const std::string HANDLE_DYNAMIC_GET_ESTRM{"enumstring2.ch0.vmd0"};
const std::string HANDLE_SET_ESTRM{"enumstring.ch0.vmd1"};
const std::string HANDLE_ACTIVATE_MDS{"actop.mds0_sco_0"};
const std::string HANDLE_ACTIVATE_VMD{"actop.vmd1_sco_0"};
const std::string HANDLE_STREAM{"dummy"};

const std::string HANDLE_LOCATION_CONTEXT_STATE{"LC.mds0"};
const std::string HANDLE_SYSTEM_CONTEXT_STATE{"SC.mds0"};
const std::string HANDLE_PATIENT_CONTEXT_STATE{"PC.mds0"};

const std::string HANDLE_ALERT_SYSTEM_MDS_STATE{"asy.mds0"};
const std::string HANDLE_ALERT_SYSTEM_VMD_STATE{"asy.vmd0"};

const std::string HANDLE_ALERTSIGNAL_MDS{"as0.mds0"};
const std::string HANDLE_ALERTSIGNAL_VMD{"as0.vmd0.mds0"};
const std::string HANDLE_ALERTCONDITION_MDS{"ac0.mds0"};
const std::string HANDLE_ALERTCONDITION_VMD{"ac0.vmd0.mds0"};




class NumericProviderStateHandler : public SDCProviderMDStateHandler<NumericMetricState>
{
public:

	NumericProviderStateHandler(const std::string p_descriptorHandle, bool settable) :
	SDCProviderMDStateHandler(p_descriptorHandle),
	m_settable{settable}
	{ }

	// Helper method
	NumericMetricState createState(double p_initialValue)
	{
		NumericMetricState t_newState{getDescriptorHandle()};
		t_newState
			.setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(p_initialValue))
			.setActivationState(ComponentActivation::On);
		return t_newState;
	}

	// define how to react on a request for a state change. This handler should not be set, thus always return Fail.
	InvocationState onStateChangeRequest(const NumericMetricState& p_state, const OperationInvocationContext& p_oic) override
	{
		if(!m_settable)
		{
			// extract information from the incoming operation
			DebugOut(DebugOut::Default, "ReferenceProvider") << "Operation invoked. Handle: " << p_oic.operationHandle << std::endl;
			return InvocationState::Fail;
		}
		else
		{
	    	// Invocation has been fired as WAITING when entering this method
	    	notifyOperationInvoked(p_oic, InvocationState::Start);
	    	// Do stuff
	        DebugOut(DebugOut::Default, "ReferenceProvider") << "Provider: handle_set received state change request. State's value: " << p_state.getMetricValue().getValue() << std::endl;
	        // extract information from the incoming operation
	        DebugOut(DebugOut::Default, "ReferenceProvider") << "Operation invoked. Handle: " << p_oic.operationHandle << std::endl;
	        // if success return Finished
	        return InvocationState::Fin;  // Framework will update internal MDIB with the state's value and increase MDIB version
		}
	}


	NumericMetricState getInitialState() override
	{
		return createState(0.0);
	}

	void setNumericValue(double p_newValue)
	{
		auto t_newState{createState(p_newValue)};
		updateState(t_newState);
	}
private:
	bool m_settable{false};
};


class StreamProviderStateHandler : public SDCProviderMDStateHandler<RealTimeSampleArrayMetricState>
{
public:

    StreamProviderStateHandler(const std::string p_descriptorHandle)
	: SDCProviderMDStateHandler(p_descriptorHandle)
	{ }

    // Helper method
    RealTimeSampleArrayMetricState createState()
	{
    	RealTimeSampleArrayMetricState t_newState{getDescriptorHandle()};
        t_newState.setActivationState(ComponentActivation::On);
        return t_newState;
    }

    RealTimeSampleArrayMetricState getInitialState() override
    {
        return createState();
    }

    // disallow set operation for this state
    InvocationState onStateChangeRequest(const RealTimeSampleArrayMetricState&, const OperationInvocationContext& p_oic) override
    {
    	// extract information from the incoming operation
    	DebugOut(DebugOut::Default, "ReferenceProvider") << "Operation invoked. Handle: " << p_oic.operationHandle << std::endl;
    	return InvocationState::Fail;
    }

    // convenient update method
    void updateStateValue(const SampleArrayValue& p_newValue)
	{
        auto t_newState{createState()};
        t_newState.setMetricValue(p_newValue);

        updateState(t_newState);
    }
};

class StringProviderStateHandler : public SDCProviderMDStateHandler<StringMetricState>
{
public:
	StringProviderStateHandler(const std::string p_descriptorHandle, bool settable) :
	SDCProviderMDStateHandler(p_descriptorHandle),
	m_settable{settable}
	{ }

	InvocationState onStateChangeRequest(const StringMetricState& p_changedState, const OperationInvocationContext& p_oic) override
	{
		notifyOperationInvoked(p_oic, InvocationState::Start);
		// Do something if a state change is requested
		DebugOut(DebugOut::Default, "ReferenceProvider") << "String state of provider state changed to " << p_changedState.getMetricValue().getValue() << std::endl;
		// return Finished if successful
		return InvocationState::Fin;
	}

	// Helper method
	StringMetricState createState()
	{
		StringMetricState t_newState{getDescriptorHandle()};
		t_newState.setMetricValue(StringMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue("StringMetricValueInit"));
	    return t_newState;
	}

	StringMetricState getInitialState() override
	{
		return createState();
	}
private:
	bool m_settable{false};
};

class EnumStringProviderStateHandler : public SDCProviderMDStateHandler<EnumStringMetricState>
{
public:
	EnumStringProviderStateHandler(const std::string p_descriptorHandle, bool settable) :
	SDCProviderMDStateHandler(p_descriptorHandle),
	m_settable{settable}
	{ }

	InvocationState onStateChangeRequest(const EnumStringMetricState& p_changedState, const OperationInvocationContext& p_oic) override
	{
		notifyOperationInvoked(p_oic, InvocationState::Start);
		// Do something if a state change is requested
		DebugOut(DebugOut::Default, "ReferenceProvider") << "String state of provider state changed to " << p_changedState.getMetricValue().getValue() << std::endl;
		// return Finished if successful
		return InvocationState::Fin;
	}

	//Helper Method
	EnumStringMetricState getInitialState()
	{
		EnumStringMetricState t_newState{getDescriptorHandle()};
	    return t_newState;
	}

private:
	bool m_settable{false};
};

class LocationContextStateHandler : public SDCProviderMDStateHandler<LocationContextState>
{
public:
	LocationContextStateHandler(const std::string p_descriptorHandle, bool settable = false) :
	SDCProviderMDStateHandler(p_descriptorHandle),
	m_settable{settable}
	{ }

	InvocationState onStateChangeRequest(const LocationContextState& , const OperationInvocationContext& ) override
	{
		return InvocationState::Fin;
	}

	LocationContextState getInitialState()
	{
		LocationContextState t_newState{getDescriptorHandle(), getDescriptorHandle()};
		return t_newState;
	}
private:
	bool m_settable{false};
};

class SystemContextStateHandler : public SDCProviderMDStateHandler<SystemContextState>
{
public:
	SystemContextStateHandler(const std::string p_descriptorHandle, bool settable = false) :
	SDCProviderMDStateHandler(p_descriptorHandle),
	m_settable{settable}
	{ }

	InvocationState onStateChangeRequest(const SystemContextState& , const OperationInvocationContext& ) override
	{
		return InvocationState::Fin;
	}

	SystemContextState getInitialState()
	{
		SystemContextState t_newState{getDescriptorHandle()};
		return t_newState;
	}

private:
	bool m_settable{false};
};

class PatientContextStateHandler : public SDCProviderMDStateHandler<PatientContextState>
{
public:
	PatientContextStateHandler(const std::string p_descriptorHandle):
	SDCProviderMDStateHandler(p_descriptorHandle)
	{ }

	InvocationState onStateChangeRequest(const PatientContextState& , const OperationInvocationContext& ) override
	{
		return InvocationState::Fin;
	}

	PatientContextState getInitialState()
	{
		PatientContextState t_newState{getDescriptorHandle(), getDescriptorHandle()};
		return t_newState;
	}
};

class AlertConditionStateHandler : public SDCProviderAlertConditionStateHandler<AlertConditionState>
{
public:
	AlertConditionStateHandler(const std::string& p_descriptorHandle) :
	SDCProviderAlertConditionStateHandler(p_descriptorHandle)
	{ }

	InvocationState onStateChangeRequest(const AlertConditionState&, const OperationInvocationContext& ) override
	{
		return InvocationState::Fin;
	}

	AlertConditionState getInitialState()
	{
		AlertConditionState t_newState{getDescriptorHandle(), AlertActivation::Off};
		return t_newState;
	}

	void toggleAlertPresence()
	{
		AlertConditionState t_newState{getDescriptorHandle(), AlertActivation::On};
		m_presence = !m_presence;
		t_newState.setPresence(m_presence);
		updateState(t_newState);
	}

	void sourceHasChanged(const std::string & sourceHandle) override
	{
		DebugOut(DebugOut::Default, "ReferenceProvider") << "Source " << sourceHandle << " of " << getDescriptorHandle() << " changed: \n";
	}


private:
	bool m_presence{false};
};

class AlertSignalStateHandler : public SDCProviderMDStateHandler<AlertSignalState>
{
public:
	AlertSignalStateHandler(const std::string& p_descriptorHandle, bool settable = false) :
	SDCProviderMDStateHandler(p_descriptorHandle),
	m_settable{settable}
	{ }

	InvocationState onStateChangeRequest(const AlertSignalState&, const OperationInvocationContext& ) override
	{
		return InvocationState::Fin;
	}

	void toggleAlertPresence()
	{
		AlertSignalState t_newState{getDescriptorHandle(), AlertActivation::Off};
		m_presence = !m_presence;
		m_presence ? t_newState.setPresence(AlertSignalPresence::On) : t_newState.setPresence(AlertSignalPresence::Off);
		updateState(t_newState);
	}

	AlertSignalState getInitialState()
	{
		AlertSignalState t_newState{getDescriptorHandle(), AlertActivation::Off};
		return t_newState;
	}
private:
	bool m_settable{false};
	bool m_presence{false};
};

class AlertSystemStateHandler : public SDCProviderMDStateHandler<AlertSystemState>
{
public:
	AlertSystemStateHandler(const std::string& p_descriptorHandle, bool settable = false) :
	SDCProviderMDStateHandler(p_descriptorHandle),
	m_settable{settable}
	{}

	InvocationState onStateChangeRequest(const AlertSystemState&, const OperationInvocationContext& ) override
	{
		return InvocationState::Fin;
	}
	AlertSystemState getInitialState()
	{
		AlertSystemState t_newState{getDescriptorHandle(), AlertActivation::Off};
		return t_newState;
	}
private:
	bool m_settable{false};
};


class ActivateOperationStateHandler : public SDCProviderActivateOperationHandler
{
public:
	ActivateOperationStateHandler(const std::string& p_descriptorHandle) :
	SDCProviderActivateOperationHandler(p_descriptorHandle)
	{}

	InvocationState onActivateRequest(const OperationInvocationContext & ) override
	{
		DebugOut(DebugOut::Default, "ReferenceProvider") << getDescriptorHandle() << " got activated \n";
		return InvocationState::Fin;
	}
};


class SDCStreamProvider : public Util::Task
{
public:

    SDCStreamProvider(SDCInstance_shared_ptr p_SDCInstance, std::ifstream& p_stream)
	: m_sdcProvider(p_SDCInstance)
    {

		m_sdcProvider.setEndpointReferenceByName(DEVICE_EPR);

		std::stringstream buffer;
		buffer << p_stream.rdbuf();
		std::string mdDesciption_xml = buffer.str();
        p_stream.close();

		// set DPWS metadata, e.g. for the displayed friendly name
		Dev::DeviceCharacteristics devChar;
		devChar.addFriendlyName("en", "SDCLib ReferenceProvider");
		m_sdcProvider.setDeviceCharacteristics(devChar);

		m_sdcProvider.setMdDescription(mdDesciption_xml);

        // Add handler
		m_sdcProvider.addMdStateHandler(&m_getStaticStrStateHandler);
		m_sdcProvider.addMdStateHandler(&m_getDynamicStrStateHandler);
		m_sdcProvider.addMdStateHandler(&m_setStrStateHandler);
		m_sdcProvider.addMdStateHandler(&m_getStaticNumStateHandler);
		m_sdcProvider.addMdStateHandler(&m_getDynamicNumStateHandler);
		m_sdcProvider.addMdStateHandler(&m_setNumStateHandler);
		m_sdcProvider.addMdStateHandler(&m_getStaticEnumStateHandler);
		m_sdcProvider.addMdStateHandler(&m_getDynamicEnumStateHandler);
		m_sdcProvider.addMdStateHandler(&m_setEnumStateHandler);

		m_sdcProvider.addMdStateHandler(&m_systemContextHandler);
		m_sdcProvider.addMdStateHandler(&m_locationContextStateHandler);
		m_sdcProvider.addMdStateHandler(&m_patientContextStateHandler);

		m_sdcProvider.addMdStateHandler(&m_alertSystemMDSStateHandler);
		m_sdcProvider.addMdStateHandler(&m_alertConditionMDSStateHandler);
		m_sdcProvider.addMdStateHandler(&m_alertSignalMDSStateHandler);

		m_sdcProvider.addMdStateHandler(&m_alertSystemVMDStateHandler);
		m_sdcProvider.addMdStateHandler(&m_alertConditionVMDStateHandler);
		m_sdcProvider.addMdStateHandler(&m_alertSignalVMDStateHandler);

		m_sdcProvider.addMdStateHandler(&m_activateOperationMDSHandler);
		m_sdcProvider.addMdStateHandler(&m_activateOperationVMDHandler);
    }

    void startup()
    {
    	m_sdcProvider.startup();
    }

private:

    SDCProvider m_sdcProvider;

    //StringMetrics
    StringProviderStateHandler m_getStaticStrStateHandler{HANDLE_STATIC_GET_STRM, false};
    StringProviderStateHandler m_getDynamicStrStateHandler{HANDLE_DYNAMIC_GET_STRM, false};
    StringProviderStateHandler m_setStrStateHandler{HANDLE_SET_STRM, true};

    //NumericMetrics
    NumericProviderStateHandler m_getStaticNumStateHandler{HANDLE_STATIC_GET_NM, false};
    NumericProviderStateHandler m_getDynamicNumStateHandler{HANDLE_DYNAMIC_GET_NM, false};
    NumericProviderStateHandler m_setNumStateHandler{HANDLE_SET_NM, true};

    //EnumStringMetrics
    EnumStringProviderStateHandler m_getStaticEnumStateHandler{HANDLE_STATIC_GET_ESTRM, false};
    EnumStringProviderStateHandler m_getDynamicEnumStateHandler{HANDLE_DYNAMIC_GET_ESTRM, false};
    EnumStringProviderStateHandler m_setEnumStateHandler{HANDLE_SET_ESTRM, true};

    SystemContextStateHandler m_systemContextHandler{HANDLE_SYSTEM_CONTEXT_STATE};
    LocationContextStateHandler m_locationContextStateHandler{HANDLE_LOCATION_CONTEXT_STATE};
    PatientContextStateHandler m_patientContextStateHandler{HANDLE_PATIENT_CONTEXT_STATE};

    AlertSystemStateHandler m_alertSystemMDSStateHandler{HANDLE_ALERT_SYSTEM_MDS_STATE};
    AlertConditionStateHandler m_alertConditionMDSStateHandler{HANDLE_ALERTCONDITION_MDS};
    AlertSignalStateHandler m_alertSignalMDSStateHandler{HANDLE_ALERTSIGNAL_MDS};

    AlertSystemStateHandler m_alertSystemVMDStateHandler{HANDLE_ALERT_SYSTEM_VMD_STATE};
    AlertConditionStateHandler m_alertConditionVMDStateHandler{HANDLE_ALERTCONDITION_VMD};
    AlertSignalStateHandler m_alertSignalVMDStateHandler{HANDLE_ALERTSIGNAL_VMD};

    ActivateOperationStateHandler m_activateOperationVMDHandler{HANDLE_ACTIVATE_VMD};
    ActivateOperationStateHandler m_activateOperationMDSHandler{HANDLE_ACTIVATE_MDS};




public:

    // Produce stream values
    // runImpl() gets called when starting the provider thread by the inherited function start()
    void runImpl() override
    {
		double val = 1.0;

		while (!isInterrupted())
		{
			// Update the NumericMetricState's value using the state handler's method
			m_getDynamicNumStateHandler.setNumericValue(val);
			DebugOut(DebugOut::Default, "ReferenceProvider") << "NumericMetric: value changed to " << val << std::endl;
			val++;
			m_alertConditionMDSStateHandler.toggleAlertPresence();
			m_alertConditionVMDStateHandler.toggleAlertPresence();
			m_alertSignalMDSStateHandler.toggleAlertPresence();
			m_alertSignalVMDStateHandler.toggleAlertPresence();
			std::this_thread::sleep_for(std::chrono::milliseconds(5000));
		}
    }
};

int main(int argc, char *argv[])
{
	DebugOut::DEBUG_LEVEL = DebugOut::Default;
	bool useTLS{false};

	if(argc == 2)
	{
		useTLS = (std::string{argv[1]} == "-tls");
	}

    // Load cached Mdib from file system
    // Mdib is specified in xml
    std::ifstream t_mdibFilestream{FILE_CACHED_MDIB};
    // Found?
    if(!t_mdibFilestream.is_open()) {
        DebugOut(DebugOut::Default, "ReferenceProvider") << "Could not open " << FILE_CACHED_MDIB << "\n";
        return -1;
    }

	// Startup
	DebugOut(DebugOut::Default, "ReferenceProviderSSL") << "Startup" << std::endl;
    SDCLibrary::getInstance().startup(OSELib::LogLevel::Warning);

    // Create a new SDCInstance (no flag will auto init)
    auto t_SDCInstance = std::make_shared<SDCInstance>(true);
 
    // Some restriction
    t_SDCInstance->setIP6enabled(false);
    t_SDCInstance->setIP4enabled(true);
    // Bind it to interface that matches the internal criteria (usually the first enumerated)
    if(!t_SDCInstance->bindToDefaultNetworkInterface()) {
        DebugOut(DebugOut::Default, "ReferenceProviderSSL") << "Failed to bind to default network interface! Exit..." << std::endl;
        return -1;
    }

    if(useTLS)
    {
		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// <SSL> ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

		// Init SSL (Default Params should be fine)
		if(!t_SDCInstance->initSSL()) {
			DebugOut(DebugOut::Default, "ReferenceProviderSSL") << "Failed to init SSL!" << std::endl;
			return -1;
		}

		// Configure SSL
		auto t_SSLConfig{t_SDCInstance->getSSLConfig()};
		t_SSLConfig->addCertificateAuthority("ca.pem");
		t_SSLConfig->useCertificate("sdccert.pem");
		t_SSLConfig->useKeyFiles(/*Public Key*/"", "userkey.pem", ""/* Password for Private Keyfile */);

		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// </SSL> +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    }

    SDCStreamProvider t_provider{t_SDCInstance, t_mdibFilestream};
    t_provider.startup();
    t_provider.start();

	DebugOut(DebugOut::Default, "ReferenceProvider") << "Press key to exit program.";
	std::cin.get();

	// Shutdown
	DebugOut(DebugOut::Default, "ReferenceProvider") << "Shutdown." << std::endl;

	return 0;
}
