/*
 * TestProvider.cpp
 *
 *  Created on: Jan 8, 2019
 *      Author: rosenau
 */

#include "TestProvider.h"

const int DEFAULT_PORT(6464);

namespace TestTools {

const std::string DEFAULT_TEST_DEVICE_EPR("Test_Provider");
const std::string CHANNEL_DESCRIPTOR_HANDLE("channel_descriptor_handle");
const std::string VMD_DESCRIPTOR_HANDLE("vmd_descriptor_handle");
const std::string MDS_DESCRIPTOR_HANDLE("mds_descriptor_handle");


TestProvider::TestProvider():
	sdcProvider(),
	nmsSetHandler(HANDLE_SET_NUMERIC_METRIC),
	nmsGetHandler(HANDLE_GET_NUMERIC_METRIC),
	nmsSetDescriptor(HANDLE_SET_NUMERIC_METRIC,
	CodedValue("MDCX_EXAMPLE_SET"),
	MetricCategory::Set,
	MetricAvailability::Cont,
	1.0)
{
	//Configuration of sdcProvider according to the specification of the TestProvider
	//Channel
	ChannelDescriptor deviceParameters(CHANNEL_DESCRIPTOR_HANDLE);
	deviceParameters.setSafetyClassification(SafetyClassification::MedC)
					.addMetric(nmsSetDescriptor);

	//VMD
	VmdDescriptor deviceModule(VMD_DESCRIPTOR_HANDLE);
	deviceModule.addChannel(deviceParameters);

	//MDS
	MdsDescriptor deviceSystem(MDS_DESCRIPTOR_HANDLE);
	deviceSystem.addVmd(deviceModule);

	sdcProvider.createSetOperationForDescriptor(nmsSetDescriptor, deviceSystem);

	MdDescription mdDescription;
	mdDescription.addMdsDescriptor(deviceSystem);

	sdcProvider.addMdStateHandler(&nmsSetHandler);
	sdcProvider.addHandleForPeriodicEvent(HANDLE_SET_NUMERIC_METRIC);


	//Endpoint Name
	setEndPointReference(DEFAULT_TEST_DEVICE_EPR);
	setPort(DEFAULT_PORT);
}


TestProvider::~TestProvider() {

}

void TestProvider::setEndPointReference(std::string endpointRef)
{
	sdcProvider.setEndpointReference(endpointRef);
}

void TestProvider::setPort(int port) {
	//Network configuration
	MDPWSTransportLayerConfiguration providerConfig = MDPWSTransportLayerConfiguration();
	providerConfig.setPort(port);
	sdcProvider.setConfiguration(providerConfig);
}

void TestProvider::startup() {
	//forwarding of the startup function
	sdcProvider.startup();
}


void TestProvider::shutdown() {
	//forwarding of the shutdown function
	sdcProvider.shutdown();
}

MdibContainer TestProvider::getMdib() {
	return sdcProvider.getMdib();
}

MdDescription TestProvider::getMdDscription()
{
	return sdcProvider.getMdDescription();
}

MdState TestProvider::getMdState()
{
	return sdcProvider.getMdState();
}


void TestProvider::runImpl() {
	while (!isInterrupted()) {
		{
		}
		Poco::Thread::sleep(1000);
	}
}


} /* namespace TestTools */
