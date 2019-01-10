/*
 * test_ServiceProvider_ChangingContextDescribtorDuringRuntime_11073_20701_R0106.cpp
 *
 *  Created on: Dec 7, 2018
 *      Author: rosenau
 */

#include <iostream>

#include "OSCLib/Data/SDC/SDCProvider.h"
#include "OSCLib/Data/SDC/MDIB/PatientContextDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/SystemContextDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/LocationContextDescriptor.h"
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
const std::string CHANNEL_DESCRIPTOR_HANDLE("channel_descriptor_handle");
const std::string VMD_DESCRIPTOR_HANDLE("vmd_descriptor_handle");
const std::string MDS_DESCRIPTOR_HANDLE("mds_descriptor_handle");
const std::string LOCATION_CONTEXT_DESCRIPTOR_HANDLE("location_context_descriptor_handle");


int main()
{
	SDCProvider sdcProvider;

	PatientContextDescriptor patientContextDesc(PATIENT_CONTEXT_DESCRIPTOR_HANDLE);
	SystemContextDescriptor systemContextDesc(SYSTEM_CONTEXT_DESCRIPTOR_HANDLE);
	systemContextDesc.setPatientContext(patientContextDesc);

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

	LocationContextDescriptor locationContextDesc(LOCATION_CONTEXT_DESCRIPTOR_HANDLE);
	systemContextDesc.setLocationContext(locationContextDesc);


	// Shutdown
	DebugOut(DebugOut::Default, "TestProvider") << "Shutdown." << std::endl;

}
