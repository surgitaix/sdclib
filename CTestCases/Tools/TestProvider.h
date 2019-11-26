/*
 * TestProvider.h
 *
 *  Created on: Jan 8, 2019
 *      Author: rosenau
 */

#ifndef CTESTCASES_TOOLS_TESTPROVIDER_H_
#define CTESTCASES_TOOLS_TESTPROVIDER_H_

#include "SDCLib/Data/SDC/SDCProvider.h"

#include "SDCLib/Data/SDC/SDCProviderComponentStateHandler.h"
#include "SDCLib/Data/SDC/SDCProviderAlertConditionStateHandler.h"
#include "SDCLib/Data/SDC/SDCProviderStateHandler.h"
#include "SDCLib/Data/SDC/SDCProviderMDStateHandler.h"
#include "SDCLib/Data/SDC/MDIB/MdsState.h"
#include "SDCLib/Data/SDC/MDIB/ChannelDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"
#include "SDCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "SDCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/LocalizedText.h"
#include "SDCLib/Data/SDC/MDIB/MdDescription.h"
#include "SDCLib/Data/SDC/MDIB/MetricQuality.h"
#include "SDCLib/Data/SDC/MDIB/Range.h"
#include "SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricState.h"
#include "SDCLib/Data/SDC/MDIB/SampleArrayValue.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricState.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricValue.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricState.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricValue.h"
#include "SDCLib/Data/SDC/MDIB/SystemContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/MetaData.h"
#include "SDCLib/Dev/DeviceCharacteristics.h"
#include "SDCLib/Data/SDC/MDIB/VmdDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/custom/OperationInvocationContext.h"
#include "SDCLib/Data/SDC/MDPWSTransportLayerConfiguration.h"
#include "SDCLib/Data/SDC/MDIB/AlertSystemDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "SDCLib/Data/SDC/MDIB/AlertConditionState.h"
#include "SDCLib/Data/SDC/MDIB/AlertSystemState.h"
#include "SDCLib/Data/SDC/MDIB/AlertSignalState.h"
#include "SDCLib/Data/SDC/MDIB/AlertSignalDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/AlertConditionDescriptor.h"

#include "SDCLib/Data/SDC/MDIB/custom/MdibContainer.h"

#include "BICEPS_MessageModel-fwd.hxx"

#include "SDCLib/Util/DebugOut.h"
#include "SDCLib/Util/Task.h"

#include "StateHandler/NumericMetricStateGetHandler.h"
#include "StateHandler/NumericMetricStateSetHandler.h"


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


		InvocationState onStateChangeRequest(const AlertConditionState &, const OperationInvocationContext & oic) override {
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

		void sourceHasChanged(const std::string &) override {
			//This technical alert is independent of any source represented in the MDIB and only gets directly set by the provider.
		}

		InvocationState onStateChangeRequest(const AlertConditionState &, const OperationInvocationContext & oic) override {
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
