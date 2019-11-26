/*
 * test_ServiceProvider_UniquePatientContextDescriptor_11073_10207_5.3.7.cpp
 *
 *  Created on: Jan 22, 2019
 *      Author: rosenau
 */

#include <iostream>
#include "OSCLib/Data/SDC/MDIB/PatientContextDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/SystemContextDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/MdDescription.h"
#include "OSCLib/Data/SDC/MDIB/custom/MdibContainer.h"
#include "OSCLib/Data/SDC/SDCProvider.h"

using namespace SDCLib;
using namespace SDCLib::Data::SDC;

const std::string PATIENT_CONTEXT_DESCRIPTOR_HANDLE1("patient_context_descriptor_handle1");
const std::string PATIENT_CONTEXT_DESCRIPTOR_HANDLE2("patient_context_descriptor_handle2");
const std::string SYSTEM_CONTEXT_DESCRIPTOR_HANDLE("system_context_descriptor");
const std::string MDS_DESCRIPTOR_HANDLE("mds_descriptor_handle");

int main() {
	std::cout << "Test against requirement 11073-10207-5.2.7 SystemContext pm:PatientContextDescriptor and "
			  << "pm:LocationContextDesriptor SHALL be appear once or never within the SystemContextDescriptor. "
			  << "Other ContextDescriptors may appear multiple times and have multiple states."
			  << std::endl;

	PatientContextDescriptor patientContextDesc1(PATIENT_CONTEXT_DESCRIPTOR_HANDLE1);
	PatientContextDescriptor patientContextDesc2(PATIENT_CONTEXT_DESCRIPTOR_HANDLE2);

	SystemContextDescriptor sysContextDesc(SYSTEM_CONTEXT_DESCRIPTOR_HANDLE);
	sysContextDesc.setPatientContext(patientContextDesc1);
	try {
		sysContextDesc.setPatientContext(patientContextDesc2);
	}
	catch (...) {
		std::cout << "PatientContext can't be overwritten" << std::endl;
		std::cout << "Test passed";
	}

	MdsDescriptor mds(MDS_DESCRIPTOR_HANDLE);
	mds.setSystemContext(sysContextDesc);

	MdDescription mdDescription;
	mdDescription.addMds(mds);

	SDCProvider provider;
	provider.setMdDescription(mdDescription);

	if(provider.getMdib().getMdDescription().getMdsList().front().getSystemContext().getPatientContext(patientContextDesc1) &&
			provider.getMdib().getMdDescription().getMdsList().front().getSystemContext().getPatientContext(patientContextDesc2)) {
		std::cout << "Test failed";
		exit(0);
	}
	else
	{
		if(provider.getMdib().getMdDescription().getMdsList().front().getSystemContext().getPatientContext().getHandle() == PATIENT_CONTEXT_DESCRIPTOR_HANDLE2) {
			std::cout << "PatientContext was overwritten" << std::endl;
			std::cout << "Test passed";
		}
	}
}


