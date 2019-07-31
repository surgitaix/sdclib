/*
 * TestOrchestratorConsumer.cpp
 *
 *  Created on: Jul 31, 2019
 *      Author: rosenau
 */

#include <TestOrchestratorConsumer.h>

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
    	return;

    OSELib::SDC::ServiceManager oscpsm(t_SDCInstance);
    auto c(oscpsm.discoverEndpointReference(DEFAULT_ENDPOINTREFERENCE_DISCOVERY_PROVIDER));
	try {
		if (c != nullptr) {
			consumer = std::move(c);
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
	consumer->activate(DISCOVER_AVAILABLE_ENDPOINT_REFERENCES);
}

void TestOrchestratorConsumer::setDUTEndpointRef(const std::string& EndpointRef) {
	DUTEndpointRef = EndpointRef;

}

void TestOrchestratorConsumer::discoverDUT() {

}

void TestOrchestratorConsumer::setMirrorProviderEndpointRef(const std::string& EndpointRef) {

}

void TestOrchestratorConsumer::setupMirrorProvider() {

}

std::string TestOrchestratorConsumer::getProviderMDIB() {
	return "";
}

template <typename TState>
void TestOrchestratorConsumer::sendSetRequest(HandleRef& descriptorHandle, TState state) {
	FutureInvocationState fis;
	consumer->commitState(*state, fis);
	Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer") << "Commit result metric state: " << fis.waitReceived(InvocationState::Fin, 5000);
}


template <typename TState>
TState TestOrchestratorConsumer::requestState(HandleRef& descriptorHandle) {
	return consumer->requestState<TState>(descriptorHandle);
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



} //ACS
} //SDC
} //Data
} //SDCLib
