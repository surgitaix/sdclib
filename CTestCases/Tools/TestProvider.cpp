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
#include "TestProviderHandleNames.h"

const int DEFAULT_PORT(6464);

namespace TestTools {

TestProvider::TestProvider():
	sdcProvider(),
	nmsSetHandler(HANDLE_SET_NUMERIC_METRIC),
	nmsGetHandler(HANDLE_GET_NUMERIC_METRIC),
	phyAlertConditionStateHandler(HANDLE_PHYSICAL_ALERT_CONDITION),
	phyAlertSignalHandler(HANDLE_PHYSICAL_ALERT_SIGNAL),
	techAlertConditionStateHandler(HANDLE_TECHNICAL_ALERT_CONDITION),
	techAlertSignalHandler(HANDLE_TECHNICAL_ALERT_SIGNAL),
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
	sdcProvider.addMdStateHandler(&phyAlertConditionStateHandler);
	sdcProvider.addMdStateHandler(&phyAlertSignalHandler);
	sdcProvider.addMdStateHandler(&techAlertConditionStateHandler);
	sdcProvider.addMdStateHandler(&techAlertSignalHandler);
	sdcProvider.addMdStateHandler(&alertSystemStateHandler);
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
	AlertConditionDescriptor phyAlertConditionDescriptor(HANDLE_PHYSICAL_ALERT_CONDITION,
		AlertConditionKind::Phy,
		AlertConditionPriority::Hi
	);
	phyAlertConditionDescriptor.addSource(HANDLE_PHYSICAL_ALERT_CONDITION);
	AlertSignalDescriptor phyAlertSignalDescriptor(HANDLE_PHYSICAL_ALERT_SIGNAL,
		AlertSignalManifestation::Aud,
		true);
	phyAlertSignalDescriptor.setConditionSignaled(HANDLE_PHYSICAL_ALERT_CONDITION);

	AlertConditionDescriptor techAlertConditionDescriptor(HANDLE_TECHNICAL_ALERT_CONDITION,
		AlertConditionKind::Tec,
		AlertConditionPriority::Me
	);
	AlertSignalDescriptor techAlertSignalDescriptor(HANDLE_TECHNICAL_ALERT_SIGNAL,
		AlertSignalManifestation::Aud,
		true);
	techAlertSignalDescriptor.setConditionSignaled(HANDLE_TECHNICAL_ALERT_CONDITION);


	alertSystemDescriptor.addAlertCondition(phyAlertConditionDescriptor);
	alertSystemDescriptor.addAlertSignal(phyAlertSignalDescriptor);
	alertSystemDescriptor.addAlertCondition(techAlertConditionDescriptor);
	alertSystemDescriptor.addAlertSignal(techAlertSignalDescriptor);
	vmdDesc.setAlertSystem(alertSystemDescriptor);
}


void TestProvider::setNumericMetricValue(double val) {
	nmsGetHandler.setNumericcMetricValue(val);
	auto metricValue = sdcProvider.getMdState().findState<NumericMetricState>(HANDLE_GET_NUMERIC_METRIC);
}

void TestProvider::setAlertConditionPresence(const std::string & alertConditionHandle, bool conditionPresence, const OperationInvocationContext & oic) {
	sdcProvider.setAlertConditionPresence(alertConditionHandle, conditionPresence, oic);
}

void TestProvider::setAlertSystemActivationState(AlertActivation AlertActivationState) {
	alertSystemStateHandler.setActivationState(AlertActivationState);
}

} /* namespace TestTools */
