/*
 * test_ServiceProvider_UniqueLocationContext_11073_10207_R0133.cpp
 *
 *  Created on: Jan 22, 2019
 *      Author: rosenau
 */

#include <iostream>
#include "OSCLib/Data/SDC/SDCProvider.h"
#include "OSCLib/Data/SDC/MDIB/LocationContextDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/LocationContextState.h"
#include "OSCLib/Data/SDC/MDIB/SystemContextDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/MdDescription.h"

#include "OSCLib/Data/SDC/SDCProviderMDStateHandler.h"

#include "Tools/HelperMethods.h"

using namespace SDCLib;
using namespace SDCLib::Data::SDC;

const std::string LOCATION_CONTEXT_DESCRIPTOR_HANDLE("location_context_descriptor_handle");
const std::string LOCATION_CONTEXT_STATE_HANDLE1("location_context_state_handle1");
const std::string LOCATION_CONTEXT_STATE_HANDLE2("location_context_state_handle2");
const std::string SYSTEM_CONTEXT_DESCRIPTOR_HANDLE("system_context_descriptor_handle");
const std::string MDS_DESCRIPTOR_HANDLE("mds_descriptor_handle");

class LocationContextStateHandler : public SDCProviderMDStateHandler<LocationContextState> {
public:
	LocationContextStateHandler(std::string descriptorHandle, std::string handle) : SDCProviderMDStateHandler(descriptorHandle), handle(handle) {

	}

	LocationContextState createLocationContextState() {
		LocationContextState locationContextState(descriptorHandle, handle);
		return locationContextState;
	}

	LocationContextState getInitialState() override {
		LocationContextState locationContextState(descriptorHandle, handle);
		locationContextState.setContextAssociation(ContextAssociation::No);
		return locationContextState;
	}

	void updateLocationContextState(ContextAssociation associated) {
		LocationContextState locationContextState = createLocationContextState();
		locationContextState.setContextAssociation(associated);
		updateState(locationContextState);
	}

	InvocationState onStateChangeRequest(const LocationContextState &state, const OperationInvocationContext &oic)	{
		return InvocationState::Fail;
	}
private:
	std::string handle;
};


int main() {
	std::cout << "Test against requirement 11073-10207-R0133 A service provider shall be associated with a maximum of "
			  << "a particular context descriptor at a time:"
			  << std::endl;

	LocationContextDescriptor locationContextDesc(LOCATION_CONTEXT_DESCRIPTOR_HANDLE);
	LocationContextStateHandler locationContextStateHandler1(LOCATION_CONTEXT_DESCRIPTOR_HANDLE, LOCATION_CONTEXT_STATE_HANDLE1);
	LocationContextStateHandler locationContextStateHandler2(LOCATION_CONTEXT_DESCRIPTOR_HANDLE, LOCATION_CONTEXT_STATE_HANDLE2);

	SystemContextDescriptor sysContextDesc(SYSTEM_CONTEXT_DESCRIPTOR_HANDLE);
	sysContextDesc.setLocationContext(locationContextDesc);

	MdsDescriptor mds(MDS_DESCRIPTOR_HANDLE);
	mds.setSystemContext(sysContextDesc);

	MdDescription mdDescription;
	mdDescription.addMds(mds);

	SDCProvider provider;
	provider.setMdDescription(mdDescription);
	provider.addMdStateHandler(&locationContextStateHandler1);
	provider.addMdStateHandler(&locationContextStateHandler2);
	provider.startup();

	locationContextStateHandler1.updateLocationContextState(ContextAssociation::Assoc);
	locationContextStateHandler2.updateLocationContextState(ContextAssociation::Assoc);
	std::cout << TestTools::getStringRepresentationOfMDIB(provider.getMdib());

	int associatedStatesCounter = 0;
	for (auto locationState : provider.getMdib().getMdState().findLocationContextStates()) {
		if (locationState.getContextAssociation() == ContextAssociation::Assoc) {
			associatedStatesCounter++;
		}
	}

	if(associatedStatesCounter == 1) {
		std::cout << "Test passed";
	}
	else {
		std::cout << "Test failed";
	}

}

