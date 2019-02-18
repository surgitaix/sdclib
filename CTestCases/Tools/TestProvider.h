/*
 * TestProvider.h
 *
 *  Created on: Jan 8, 2019
 *      Author: rosenau
 */

#ifndef CTESTCASES_TOOLS_TESTPROVIDER_H_
#define CTESTCASES_TOOLS_TESTPROVIDER_H_

#include "OSCLib/Data/SDC/SDCProvider.h"

#include "OSCLib/Data/SDC/SDCProviderComponentStateHandler.h"
#include "OSCLib/Data/SDC/SDCProviderAlertConditionStateHandler.h"
#include "OSCLib/Data/SDC/SDCProviderStateHandler.h"
#include "OSCLib/Data/SDC/SDCProviderMDStateHandler.h"
#include "OSCLib/Data/SDC/MDIB/MdsState.h"
#include "OSCLib/Data/SDC/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/CodedValue.h"
#include "OSCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/LocalizedText.h"
#include "OSCLib/Data/SDC/MDIB/MdDescription.h"
#include "OSCLib/Data/SDC/MDIB/MetricQuality.h"
#include "OSCLib/Data/SDC/MDIB/Range.h"
#include "OSCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricState.h"
#include "OSCLib/Data/SDC/MDIB/SampleArrayValue.h"
#include "OSCLib/Data/SDC/MDIB/NumericMetricState.h"
#include "OSCLib/Data/SDC/MDIB/NumericMetricValue.h"
#include "OSCLib/Data/SDC/MDIB/NumericMetricDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/StringMetricDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/StringMetricState.h"
#include "OSCLib/Data/SDC/MDIB/StringMetricValue.h"
#include "OSCLib/Data/SDC/MDIB/SystemContextDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/MetaData.h"
#include "OSCLib/Dev/DeviceCharacteristics.h"
#include "OSCLib/Data/SDC/MDIB/VmdDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/custom/OperationInvocationContext.h"
#include "OSCLib/Data/SDC/MDPWSTransportLayerConfiguration.h"
#include "OSCLib/Data/SDC/MDIB/AlertSystemDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/SDC/MDIB/AlertConditionState.h"
#include "OSCLib/Data/SDC/MDIB/AlertSystemState.h"
#include "OSCLib/Data/SDC/MDIB/AlertSignalState.h"
#include "OSCLib/Data/SDC/MDIB/AlertSignalDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/AlertConditionDescriptor.h"

#include "OSCLib/Data/SDC/MDIB/custom/MdibContainer.h"

#include "BICEPS_MessageModel-fwd.hxx"

#include "OSCLib/Util/DebugOut.h"
#include "OSCLib/Util/Task.h"

#include "TestProviderStateHandler/NumericMetricStateGetHandler.h"
#include "TestProviderStateHandler/NumericMetricStateSetHandler.h"


using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

namespace TestTools {

class TestProvider : public Util::Task{
	class PhysicalAlertConditionStateHandler : public SDCProviderAlertConditionStateHandler<AlertConditionState>
	{
	public:

		PhysicalAlertConditionStateHandler(std::string descriptorHandle) : SDCProviderAlertConditionStateHandler(descriptorHandle) {
		}

		void sourceHasChanged(const std::string & sourceHandle) override {
			std::cout << "source changed";
			std::unique_ptr<NumericMetricState> pSourceState(getParentProvider().getMdState().findState<NumericMetricState>(sourceHandle));
			if (pSourceState->getDescriptorHandle() != sourceHandle) {
				return;
			}
			if (!pSourceState->hasMetricValue()) {
				return;
			}
			const auto sourceValue(pSourceState->getMetricValue());
			if (!sourceValue.hasValue()) {
				return;
			}
			if (sourceValue.getValue() == 20){
				setPresent(true);
			}
		}

		void setPresent(bool present) {
			AlertConditionState newState = createState();
			newState.setPresence(present);
			updateState(newState);
		}


		InvocationState onStateChangeRequest(const AlertConditionState & state, const OperationInvocationContext & oic) override {
			notifyOperationInvoked(oic, InvocationState::Start);
			// Do something if a state change is requested
			// return Finished if successful
			return InvocationState::Fin;
		}

		AlertConditionState createState() {
			AlertConditionState result(getDescriptorHandle(), AlertActivation::On);
			return result;
		}

		AlertConditionState getInitialState() override {
			AlertConditionState initialState = createState();
			return initialState;
		}
	};

	class TechnicalAlertConditionStateHandler : public SDCProviderAlertConditionStateHandler<AlertConditionState>
	{
	public:
		TechnicalAlertConditionStateHandler(std::string descriptorHandle) : SDCProviderAlertConditionStateHandler(descriptorHandle) {
		}

		void sourceHasChanged(const std::string & sourceHandle) override {
			//This technical alert is independent of any source represented in the MDIB and only gets directly set by the provider.
		}

		InvocationState onStateChangeRequest(const AlertConditionState & state, const OperationInvocationContext & oic) override {
			notifyOperationInvoked(oic, InvocationState::Start);
			// Do something if a state change is requested
			// return Finished if successful
			return InvocationState::Fin;
		}

		AlertConditionState getInitialState() override {
			AlertConditionState result(getDescriptorHandle(), AlertActivation::On);
			return result;
		}

	};



	class AlertSystemStateHandler : public SDCProviderMDStateHandler<AlertSystemState> {
	public:
		AlertSystemStateHandler(const std::string descriptorHandle) : SDCProviderMDStateHandler(descriptorHandle) {
		}

		InvocationState onStateChangeRequest(const AlertSystemState &, const OperationInvocationContext & oic) override {
			notifyOperationInvoked(oic, InvocationState::Start);
			// Do something if a state change is requested
			// return Finished if successful
			return InvocationState::Fin;
		}

		AlertSystemState getInitialState() override {
			AlertSystemState result(getDescriptorHandle(), AlertActivation::On);
			return result;
		}

		void setActivationState(AlertActivation alertActivationState) {
			AlertSystemState result(getDescriptorHandle(), alertActivationState);
			updateState(result);
		}
	};

	class AlertSignalStateHandler : public SDCProviderMDStateHandler<AlertSignalState> {
	public:
		AlertSignalStateHandler(std::string descriptorHandle) : SDCProviderMDStateHandler(descriptorHandle) {
		}

		AlertSignalState getInitialState() override {
			AlertSignalState initState(getDescriptorHandle(), AlertActivation::On);
			return initState;
		}

		InvocationState onStateChangeRequest(const AlertSignalState &, const OperationInvocationContext & oic) override {
			notifyOperationInvoked(oic, InvocationState::Start);
			// Do something if a state change is requested
			// return Finished if successful
			return InvocationState::Fin;
		}

	};

public:
	TestProvider();
	virtual ~TestProvider();

	TestProvider(const TestProvider &) = delete;
	TestProvider operator=(const TestProvider &) = delete;

	void setPort(int port);
	void setEndPointReference(std::string endpointRef);

	void startup();
	void shutdown();

	MdibContainer getMdib();
	MdDescription getMdDscription();
	MdState getMdState();

	void setOperationMode(std::string descriptorHandle, OperatingMode mode);

	virtual void runImpl() override;

	void setNumericMetricValue(double val);

    void setAlertConditionPresence(const std::string & alertConditionHandle, bool conditionPresence, const OperationInvocationContext & oic);

    void setAlertSystemActivationState(AlertActivation AlertAcitvationState);

private:
	void addAlertSystem(VmdDescriptor & vmdDesc);


	SDCProvider sdcProvider;
	NumericMetricStateSetHandler nmsSetHandler;
	NumericMetricStateGetHandler nmsGetHandler;
    PhysicalAlertConditionStateHandler phyAlertConditionStateHandler;
    AlertSignalStateHandler phyAlertSignalHandler;
    TechnicalAlertConditionStateHandler techAlertConditionStateHandler;
    AlertSignalStateHandler techAlertSignalHandler;
    AlertSystemStateHandler alertSystemStateHandler;
    NumericMetricDescriptor nmsSetDescriptor;
	NumericMetricDescriptor nmsGetDescriptor;
    AlertSystemDescriptor alertSystemDescriptor;
};

} /* namespace TestTools */

#endif /* CTESTCASES_TOOLS_TESTPROVIDER_H_ */
