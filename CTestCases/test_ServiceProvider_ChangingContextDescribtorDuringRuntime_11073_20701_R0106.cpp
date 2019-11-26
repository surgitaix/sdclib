/*
 * test_ServiceProvider_ChangingContextDescribtorDuringRuntime_11073_10207_R0106.cpp
 *
 *  Created on: Dec 7, 2018
 *      Author: rosenau
 */

#include <iostream>

#include "OSCLib/Data/SDC/SDCProvider.h"
#include "OSCLib/Data/SDC/MDIB/PatientContextDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/SystemContextDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/LocationContextDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/WorkflowContextDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/EnsembleContextDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/OperatorContextDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/MeansContextDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/VmdDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/MdDescription.h"
#include "OSCLib/Data/SDC/MDIB/MdsDescriptor.h"

#include "OSCLib/Util/DebugOut.h"


using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

const std::string SYSTEM_CONTEXT_DESCRIPTOR_HANDLE("system_descriptor_handle");
const std::string PATIENT_CONTEXT_DESCRIPTOR_HANDLE("channel_descriptor_handle");
const std::string MEANS_CONTEXT_DESCRIPTOR_HANDLE("means_context_descriptor_handle");
const std::string ENSEMBLE_CONTEXT_DESCRIPTOR_HANDLE("ensemble_context_descripor_handle");
const std::string WORKFLOW_CONTEXT_DESCRIPTOR_HANDLE("workflow_context_descriptor_handle");
const std::string OPERATOR_CONTEXT_DESCRIPTOR_HANDLE("operator_context_descriptor_handle");
const std::string CHANNEL_DESCRIPTOR_HANDLE("channel_descriptor_handle");
const std::string VMD_DESCRIPTOR_HANDLE("vmd_descriptor_handle");
const std::string MDS_DESCRIPTOR_HANDLE("mds_descriptor_handle");
const std::string LOCATION_CONTEXT_DESCRIPTOR_HANDLE("location_context_descriptor_handle");


int main()
{
	std::cout << "Test against requirement 11073-10207-R0106: "
			  << "Any context descriptor SHALL NOT be removed "
			  << "from or added to the MDIB during runtime, "
			  << "except if the hosting MDS is removed or added "
			  << "to the MDIB"
			  << std::endl;

	SDCProvider sdcProvider;
	SystemContextDescriptor systemContextDesc(SYSTEM_CONTEXT_DESCRIPTOR_HANDLE);

	ChannelDescriptor deviceParameters(CHANNEL_DESCRIPTOR_HANDLE);
	deviceParameters.setSafetyClassification(SafetyClassification::MedC);


	VmdDescriptor deviceModule(VMD_DESCRIPTOR_HANDLE);
	deviceModule.addChannel(deviceParameters);

	MdsDescriptor deviceSystem(MDS_DESCRIPTOR_HANDLE);
	deviceSystem.addVmd(deviceModule);
	deviceSystem.setSystemContext(systemContextDesc);

	MdDescription mdDescription;
	mdDescription.addMdsDescriptor(deviceSystem);


	sdcProvider.setMdDescription(mdDescription);
	sdcProvider.startup();

	bool passed = true;

	LocationContextDescriptor locationContextDesc(LOCATION_CONTEXT_DESCRIPTOR_HANDLE);
	systemContextDesc.setLocationContext(locationContextDesc);
	if(sdcProvider.getMdDescription().getMdsList().front().getSystemContext().hasLocationContext()) {
		std::cout << "Test failed: LocationContextDescriptor could be set while the provider is running.";
		passed = false;
	}

	PatientContextDescriptor patientContextDesc(PATIENT_CONTEXT_DESCRIPTOR_HANDLE);
	systemContextDesc.setPatientContext(patientContextDesc);
	if(sdcProvider.getMdDescription().getMdsList().front().getSystemContext().hasPatientContext()) {
		std::cout << "Test failed: PatientContextDescriptor could be set while the provider is running.";
		passed = false;
	}

	WorkflowContextDescriptor workflowContextDesc(WORKFLOW_CONTEXT_DESCRIPTOR_HANDLE);
	systemContextDesc.addWorkflowContext(workflowContextDesc);
	if(!sdcProvider.getMdDescription().getMdsList().front().getSystemContext().getWorkflowContextList().empty()) {
		std::cout << "Test failed: WorkflowContextDescriptor could be set while the provider is running.";
		passed = false;
	}

	OperatorContextDescriptor operatorContextDesc(OPERATOR_CONTEXT_DESCRIPTOR_HANDLE);
	systemContextDesc.addOperatorContext(operatorContextDesc);
	if(!sdcProvider.getMdDescription().getMdsList().front().getSystemContext().getOperatorContextList().empty()) {
		std::cout << "Test failed: OperatorContextDescriptor could be set while the provider is running.";
		passed = false;
	}

	MeansContextDescriptor meansContextDesc(MEANS_CONTEXT_DESCRIPTOR_HANDLE);
	systemContextDesc.addMeansContext(meansContextDesc);
	if(!sdcProvider.getMdDescription().getMdsList().front().getSystemContext().getMeansContextList().empty()) {
		std::cout << "Test failed: MeansContextDescriptor could be set while the provider is running.";
		passed = false;
	}

	EnsembleContextDescriptor ensembleContextDesc(ENSEMBLE_CONTEXT_DESCRIPTOR_HANDLE);
	systemContextDesc.addEnsembleContext(ensembleContextDesc);
	if(!sdcProvider.getMdDescription().getMdsList().front().getSystemContext().getEnsembleContextList().empty()) {
		std::cout << "Test failed: EnsembleContextDescriptor could be set while the provider is running.";
		passed = false;
	}

	if (passed) {
		std::cout << "Test passed";
	}
}
