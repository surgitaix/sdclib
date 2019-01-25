/*
 * test_ServiceProvider_UniquePatientContextAssociation_11073_10207_R0124.cpp
 *
 *  Created on: Jan 22, 2019
 *      Author: rosenau
 */


#include <iostream>
#include "OSCLib/Data/SDC/SDCProvider.h"
#include "OSCLib/Data/SDC/MDIB/PatientContextDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/PatientContextState.h"
#include "OSCLib/Data/SDC/MDIB/SystemContextDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/MdDescription.h"

#include "OSCLib/Data/SDC/SDCProviderMDStateHandler.h"

#include "Tools/HelperMethods.h"

using namespace SDCLib;
using namespace SDCLib::Data::SDC;

const std::string PATIENT_CONTEXT_DESCRIPTOR_HANDLE("patient_context_descriptor_handle");
const std::string PATIENT_CONTEXT_STATE_HANDLE1("patient_context_state_handle1");
const std::string PATIENT_CONTEXT_STATE_HANDLE2("patient_context_state_handle2");
const std::string SYSTEM_CONTEXT_DESCRIPTOR_HANDLE("system_context_descriptor_handle");
const std::string MDS_DESCRIPTOR_HANDLE("mds_descriptor_handle");

class PatientContextStateHandler : public SDCProviderMDStateHandler<PatientContextState> {
public:
	PatientContextStateHandler(std::string descriptorHandle, std::string handle) : SDCProviderMDStateHandler(descriptorHandle), handle(handle) {

	}

	PatientContextState createPatientContextState() {
		PatientContextState PatientContextState(descriptorHandle, handle);
		return PatientContextState;
	}

	PatientContextState getInitialState() override {
		PatientContextState PatientContextState(descriptorHandle, handle);
		PatientContextState.setContextAssociation(ContextAssociation::No);
		return PatientContextState;
	}

	void updatePatientContextState(ContextAssociation associated) {
		PatientContextState PatientContextState = createPatientContextState();
		PatientContextState.setContextAssociation(associated);
		updateState(PatientContextState);
	}

	InvocationState onStateChangeRequest(const PatientContextState &state, const OperationInvocationContext &oic)	{
		return InvocationState::Fail;
	}
private:
	std::string handle;
};


int main() {
	std::cout << "Test against requirement 11073-10207-R0133 A service provider shall be associated with a maximum of "
			  << "a particular context descriptor at a time:" << std::endl;

	PatientContextDescriptor patientContextDesc(PATIENT_CONTEXT_DESCRIPTOR_HANDLE);
	PatientContextStateHandler patientContextStateHandler1(PATIENT_CONTEXT_DESCRIPTOR_HANDLE, PATIENT_CONTEXT_STATE_HANDLE1);
	PatientContextStateHandler patientContextStateHandler2(PATIENT_CONTEXT_DESCRIPTOR_HANDLE, PATIENT_CONTEXT_STATE_HANDLE2);

	SystemContextDescriptor sysContextDesc(SYSTEM_CONTEXT_DESCRIPTOR_HANDLE);
	sysContextDesc.setPatientContext(patientContextDesc);

	MdsDescriptor mds(MDS_DESCRIPTOR_HANDLE);
	mds.setSystemContext(sysContextDesc);

	MdDescription mdDescription;
	mdDescription.addMds(mds);

	SDCProvider provider;
	provider.setMdDescription(mdDescription);
	provider.addMdStateHandler(&patientContextStateHandler1);
	//provider.addMdStateHandler(&patientContextStateHandler2);
	provider.startup();

	patientContextStateHandler1.updatePatientContextState(ContextAssociation::Assoc);
	//PatientContextStateHandler2.updatePatientContextState(ContextAssociation::Assoc);
	//std::cout << TestTools::getStringRepresentationOfMDIB(provider.getMdib());

	int associatedStatesCounter = 0;
	std::cout << provider.getMdib().getMdState().findPatientContextStates().size();
	for (auto PatientState : provider.getMdib().getMdState().findPatientContextStates()) {
		if (PatientState.getContextAssociation() == ContextAssociation::Assoc) {
			associatedStatesCounter++;
		}
		else
			std::cout << int(PatientState.getContextAssociation());
	}

	if(associatedStatesCounter == 1) {
		std::cout << "Test passed";
	}
	else {
		std::cout << "Test failed";
	}

}

