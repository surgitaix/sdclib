/*
 * TestOrchestratorConsumer.cpp
 *
 *  Created on: Jul 31, 2019
 *      Author: rosenau
 */

#include <TestOrchestratorConsumer.h>

#include "SDCLib/Data/SDC/MDIB/StringMetricState.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricValue.h"
#include "SDCLib/Data/SDC/MDIB/MetricQuality.h"
#include "SDCLib/Data/SDC/FutureInvocationState.h"

#include "SDCLib/Util/DebugOut.h"


namespace SDCLib {
namespace Data {
namespace SDC {
namespace ACS {

TestOrchestratorConsumer::TestOrchestratorConsumer() {
	// TODO Auto-generated constructor stub

}

TestOrchestratorConsumer::~TestOrchestratorConsumer() {
	// TODO Auto-generated destructor stub
}


void TestOrchestratorConsumer::discoverDiscoveryProvider() {
    auto t_SDCInstance = createDefaultSDCInstance();

    if(t_SDCInstance == nullptr)
    {
    	std::cout << "discoveryProvider not found" << std::endl;
    	return;
    }

    OSELib::SDC::ServiceManager oscpsm(t_SDCInstance);
    auto c(oscpsm.discoverEndpointReference(DEFAULT_ENDPOINTREFERENCE_DISCOVERY_PROVIDER));
	try {
		if (c != nullptr) {
			consumer = std::move(c);
	    	std::cout << "discoveryProvider found" << std::endl;
			return;
		}
		else {
			Util::DebugOut(Util::DebugOut::Default, "TestOrchestratorConsumer") << "Discovery failed."; //Not debug out but inform orchestrator
			return;
		}
	} catch (std::exception & e) {
	Util::DebugOut(Util::DebugOut::Default, "TestOrchestratorConsumer") << "Exception: " << e.what() << std::endl; //Not debug out but inform orchestrator
		return;
	}

	return;
}

void TestOrchestratorConsumer::updateAvailableEndpointReferences() {
	FutureInvocationState fis;
	consumer->activate(DISCOVER_AVAILABLE_ENDPOINT_REFERENCES, fis);
	Util::DebugOut(Util::DebugOut::Default, "TestOrchestratorConsumer") << "Discovering available Devices... " << fis.waitReceived(InvocationState::Fin, 10000) << std::endl;

	auto availableEndpointReferences = getAvailableEndpointReferences();
	for(auto availaleEndpointRef : availableEndpointReferences)
	{
		std::cout << availaleEndpointRef << std::endl;
	}
}

void TestOrchestratorConsumer::setDUTEndpointRef(const std::string& EndpointRef) {
	DUTEndpointRef = EndpointRef;
	HandleRef ref = SET_DEVICE_UNDER_TEST_ENDPOINT_REF;
	StringMetricState strMS(SET_DEVICE_UNDER_TEST_ENDPOINT_REF);
	strMS.setMetricValue(StringMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(EndpointRef));
	this->sendSetRequest<StringMetricState>(ref, strMS);

}

void TestOrchestratorConsumer::discoverDUT() {
	FutureInvocationState fis;
	consumer->activate(DISCOVER_DEVICE_UNDER_TEST, fis);
	Util::DebugOut(Util::DebugOut::Default, "TestOrchestratorConsumer") << "Discovering Device Under Test... " << fis.waitReceived(InvocationState::Fin, 10000) << std::endl;
}

void TestOrchestratorConsumer::setMirrorProviderEndpointRef(const std::string& EndpointRef) {
	DUTMirrorProviderRef = EndpointRef;
	HandleRef ref = SET_MIRROR_PROVIDER_ENDPOINT_REF;
	StringMetricState strMS(SET_MIRROR_PROVIDER_ENDPOINT_REF);
	strMS.setMetricValue(StringMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(EndpointRef));
	this->sendSetRequest<StringMetricState>(ref, strMS);
}

void TestOrchestratorConsumer::setupMirrorProvider() {
	FutureInvocationState fis;
	consumer->activate(SETUP_MIRROR_PROVIDER, fis);
	Util::DebugOut(Util::DebugOut::Default, "TestOrchestratorConsumer") << "Setting Up MirrorProvider... " << fis.waitReceived(InvocationState::Fin, 10000) << std::endl;
}

void TestOrchestratorConsumer::discoverMirrorProvider() {
    auto t_SDCInstance = createDefaultSDCInstance();

    if(t_SDCInstance == nullptr)
    {
    	std::cout << "Mirror Provider not found" << std::endl;
    	return;
    }

    OSELib::SDC::ServiceManager oscpsm(t_SDCInstance);
    auto c(oscpsm.discoverEndpointReference(DUTMirrorProviderRef));
	try {
		if (c != nullptr) {
			consumer.release();
			consumer = std::move(c);
	    	std::cout << "Mirror Provider found" << std::endl;
			return;
		}
		else {
			Util::DebugOut(Util::DebugOut::Default, "TestOrchestratorConsumer") << "Discovery failed."; //Not debug out but inform orchestrator
			return;
		}
	} catch (std::exception & e) {
	Util::DebugOut(Util::DebugOut::Default, "TestOrchestratorConsumer") << "Exception: " << e.what() << std::endl; //Not debug out but inform orchestrator
		return;
	}

	return;
}

std::string TestOrchestratorConsumer::getProviderMDIB() {
	return "";
}

template <typename TState>
void TestOrchestratorConsumer::sendSetRequest(HandleRef& descriptorHandle, TState state) {
	FutureInvocationState fis;
	consumer->commitState(state, fis);
	Util::DebugOut(Util::DebugOut::Default, "TestOrchestratorConsumer") << "Setting: " << descriptorHandle << " " << fis.waitReceived(InvocationState::Fin, 5000) << std::endl;
}


template <typename TState>
std::unique_ptr<TState> TestOrchestratorConsumer::requestState(HandleRef& descriptorHandle) {
	return std::move(consumer->requestState<TState>(descriptorHandle));
}

SDCInstance_shared_ptr TestOrchestratorConsumer::createDefaultSDCInstance()
{
    auto t_SDCInstance = std::make_shared<SDCInstance>();
    t_SDCInstance->setIP6enabled(false);
	t_SDCInstance->setIP4enabled(true);
	// Bind it to interface that matches the internal criteria (usually the first enumerated)
	if(!t_SDCInstance->bindToDefaultNetworkInterface()) {
		std::cout << "Failed to bind to default network interface! Exit..." << std::endl;
		return nullptr;
	}
	return t_SDCInstance;
}

std::vector<std::string> TestOrchestratorConsumer::getAvailableEndpointReferences()
{
	HandleRef ref = GET_AVAILABLE_ENDPOINT_REFERENCES;
	auto availableEndpointReferencesState = this->requestState<StringMetricState>(ref);
	auto EndpointReferencesString = availableEndpointReferencesState->getMetricValue().getValue();
	std::istringstream iss(EndpointReferencesString);
	std::vector<std::string> EndpointReferences(std::istream_iterator<std::string>{iss},
	                                 std::istream_iterator<std::string>());
	return EndpointReferences;
}


} //ACS
} //SDC
} //Data
} //SDCLib
