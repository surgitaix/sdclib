/*
 * TestProvider.cpp
 *
 *  Created on: Jan 8, 2019
 *      Author: rosenau
 */

#include "TestProvider.h"
#include "HelperMethods.h"
#include "OSCLib/Data/SDC/MDIB/MdState.h"
#include "OSCLib/Data/SDC/MDIB/SetMetricStateOperationState.h"

const int DEFAULT_PORT(6464);

namespace TestTools {

const std::string DEFAULT_TEST_DEVICE_EPR("TestProvider");
const std::string CHANNEL_DESCRIPTOR_HANDLE("channel_descriptor_handle");
const std::string VMD_DESCRIPTOR_HANDLE("vmd_descriptor_handle");
const std::string MDS_DESCRIPTOR_HANDLE("mds_descriptor_handle");

TestProvider::TestProvider():
	sdcProvider(),
	nmsSetHandler(HANDLE_SET_NUMERIC_METRIC),
	nmsGetHandler(HANDLE_GET_NUMERIC_METRIC),
	alertConditionStateHandler(HANDLE_ALERT_CONDITION),
	alertSystemStateHandler(HANDLE_ALERT_SYSTEM),
	nmsSetDescriptor(HANDLE_SET_NUMERIC_METRIC,
	CodedValue("MDCX_EXAMPLE_SET"),
	MetricCategory::Set,
	MetricAvailability::Cont,
	1.0),
	nmsGetDescriptor(HANDLE_GET_NUMERIC_METRIC,
	CodedValue("MDCX_EXMAPLE_GET"),
	MetricCategory::Msrmt,
	MetricAvailability::Cont,
	1.0),
	alertSystemDescriptor(HANDLE_ALERT_SYSTEM)
{
	//Configuration of sdcProvider according to the specification of the TestProvider
	//Channel
	ChannelDescriptor deviceParameters(CHANNEL_DESCRIPTOR_HANDLE);
	deviceParameters.setSafetyClassification(SafetyClassification::MedC)
					.addMetric(nmsSetDescriptor)
					.addMetric(nmsGetDescriptor);

	//VMD
	VmdDescriptor deviceModule(VMD_DESCRIPTOR_HANDLE);
	deviceModule.addChannel(deviceParameters);

	//AlertSystem
	addAlertSystem(deviceModule);


	//MDS
	MdsDescriptor deviceSystem(MDS_DESCRIPTOR_HANDLE);
	deviceSystem.addVmd(deviceModule);

	sdcProvider.createSetOperationForDescriptor(nmsSetDescriptor, deviceSystem);

	MdDescription mdDescription;
	mdDescription.addMdsDescriptor(deviceSystem);

	sdcProvider.setMdDescription(mdDescription);

	sdcProvider.addMdStateHandler(&nmsSetHandler);
	sdcProvider.addMdStateHandler(&nmsGetHandler);
	sdcProvider.addMdStateHandler(&alertConditionStateHandler);
	sdcProvider.addHandleForPeriodicEvent(HANDLE_SET_NUMERIC_METRIC);

	//Endpoint Name
	setEndPointReference(DEFAULT_TEST_DEVICE_EPR);
	setPort(DEFAULT_PORT);
}


TestProvider::~TestProvider() {
	shutdown();
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


void TestProvider::setOperationMode(std::string descriptorHandle, OperatingMode operatingMode) {
//	SetMetricStateOperationState OperationState(*sdcProvider.getMdState().findState<SetMetricStateOperationState>(descriptorHandle));
//	OperationState.setOperatingMode(operatingMode);
}


void TestProvider::addAlertSystem(VmdDescriptor & vmdDesc) {
	AlertConditionDescriptor alertConditionDescriptor(HANDLE_ALERT_CONDITION,
		AlertConditionKind::Phy,
		AlertConditionPriority::Hi
	);
	alertConditionDescriptor.addSource(HANDLE_GET_NUMERIC_METRIC);
	alertSystemDescriptor.addAlertCondition(alertConditionDescriptor);
	vmdDesc.setAlertSystem(alertSystemDescriptor);
}


void TestProvider::setNumericMetricValue(double val) {
	nmsGetHandler.setNumericcMetricValue(val);
	auto metricValue = sdcProvider.getMdState().findState<NumericMetricState>(HANDLE_GET_NUMERIC_METRIC);
}

} /* namespace TestTools */
