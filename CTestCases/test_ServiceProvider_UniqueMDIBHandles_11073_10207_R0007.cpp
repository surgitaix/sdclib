/*
 * test_ServiceProvider_UniqueMDIBHandles_11073_10207_R0007.cpp
 *
 *  Created on: Dec 5, 2018
 *      Author: rosenau
 */

#include <iostream>
#include "OSCLib/SDCLibrary.h"
#include "OSCLib/Data/SDC/SDCProvider.h"
#include "OSCLib/Data/SDC/MDIB/NumericMetricDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/NumericMetricState.h"
#include "OSCLib/Data/SDC/SDCProviderMDStateHandler.h"
#include "OSCLib/Data/SDC/MDIB/MdDescription.h"
#include "OSCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/VmdDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/CodedValue.h"

using namespace SDCLib;
using namespace SDCLib::Data::SDC;

const std::string HANDLE_NUMERICMETRIC("handle_numericmetric");
const std::string CHANNEL_DESCRIPTOR_HANDLE("channel_descriptor_handle");
const std::string VMD_DESCRIPTOR_HANDLE("vmd_descriptor_handle");
const std::string MDS_DESCRIPTOR_HANDLE("mds_descriptor_handle");

class NumericMetricStateHandler : public SDCProviderMDStateHandler<NumericMetricState>
{
public:
	NumericMetricStateHandler(const std::string descriptorHandle) : SDCProviderMDStateHandler(descriptorHandle) {
		}

	InvocationState onStateChangeRequest(const NumericMetricState &, const OperationInvocationContext &) override {
		return InvocationState::Fail;
	}

	NumericMetricState getInitialState() override {
		NumericMetricState result(HANDLE_NUMERICMETRIC);
		return result;
	}
};

int main()
{
	std::cout << "All HANDLEs SHALL be unique within one MDIB sequence of a SERVICE PROVIDER"
			  << std::endl;
	SDCLibrary::getInstance().startup(OSELib::LogLevel::Error);
	NumericMetricStateHandler nmsHandler1(HANDLE_NUMERICMETRIC);
	NumericMetricStateHandler nmsHandler2(HANDLE_NUMERICMETRIC);

	NumericMetricDescriptor nmd1(HANDLE_NUMERICMETRIC,
			CodedValue("MDCX_EXAMPLE_GET"),
			MetricCategory::Msrmt,
			MetricAvailability::Cont,
			1.0);

	NumericMetricDescriptor nmd2(HANDLE_NUMERICMETRIC,
			CodedValue("MDCX_EXAMPLE_GET"),
			MetricCategory::Msrmt,
			MetricAvailability::Cont,
			1.0);

	ChannelDescriptor deviceParameters(CHANNEL_DESCRIPTOR_HANDLE);

	try {
		deviceParameters.setSafetyClassification(SafetyClassification::MedC)
						.addMetric(nmd1).addMetric(nmd2);

	}
	catch(...) {
		std::cout << "Test passed";
	}
	VmdDescriptor deviceModule(VMD_DESCRIPTOR_HANDLE);
	deviceModule.addChannel(deviceParameters);
	MdsDescriptor deviceSystem(MDS_DESCRIPTOR_HANDLE);
	deviceSystem.addVmd(deviceModule);

	MdDescription mdDescription;
	mdDescription.addMdsDescriptor(deviceSystem);

	SDCProvider sdcProvider;
	sdcProvider.setMdDescription(mdDescription);
	sdcProvider.addMdStateHandler(&nmsHandler1);
	sdcProvider.addMdStateHandler(&nmsHandler2);
	SDCLibrary::getInstance().shutdown();
	std::cout << "Test failed";
}


