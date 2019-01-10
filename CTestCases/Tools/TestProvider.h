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

#include "OSCLib/Data/SDC/MDIB/custom/MdibContainer.h"

#include "BICEPS_MessageModel-fwd.hxx"

#include "OSCLib/Util/DebugOut.h"
#include "OSCLib/Util/Task.h"


using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

namespace TestTools {

const std::string HANDLE_GET_NUMERIC_METRIC("handle_get_numeric_metric");
const std::string HANDLE_SET_NUMERIC_METRIC("handle_set_numeric_metric");

class TestProvider : public Util::Task{

	class TestNumericMetricStateGetHandler : public SDCProviderMDStateHandler<NumericMetricState>{
	public:
		TestNumericMetricStateGetHandler(std::string decriptorHandle) : SDCProviderMDStateHandler(decriptorHandle) {
		}

		//This Handler only allows to get a value not to set it.
		InvocationState onStateChangeRequest(const NumericMetricState &state, const OperationInvocationContext &oic) override {
			return InvocationState::Fail;
		}


		// Helper method
		NumericMetricState createState(double value) {
			NumericMetricState result(HANDLE_GET_NUMERIC_METRIC);
			result
				.setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(value))
				.setActivationState(ComponentActivation::On);
			return result;
		}

		// InitialValue of the NumericMetricState
		NumericMetricState getInitialState() override {
			NumericMetricState nms = createState(14.09);
			return nms;
		}

		// Change of NumericMetricStateValue
		void setNumericcMetricValue(double value) {
			NumericMetricState nms = createState(value);
			updateState(nms);
		}
	};

	class TestNumericMetricStateSetHandler : public SDCProviderMDStateHandler<NumericMetricState>
	{
	public:
		TestNumericMetricStateSetHandler(const std::string descriptorHandle) : SDCProviderMDStateHandler(descriptorHandle) {
			}

		InvocationState onStateChangeRequest(const NumericMetricState &state, const OperationInvocationContext &oic) {
			DebugOut(DebugOut::Default, "SettableNumericMetricState") << "Provider: received state cange request. State's value "
					<< state.getMetricValue().getValue() << std::endl;

	        notifyOperationInvoked(oic, InvocationState::Start);
	        return InvocationState::Fin;
	    }

		NumericMetricState createState() {
			NumericMetricState result(HANDLE_SET_NUMERIC_METRIC);
			result.setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(0.0))
				  .setActivationState(ComponentActivation::On);
			return result;
		}

		NumericMetricState getInitialState() override {
			NumericMetricState result = createState();
			return result;
		}
	};




public:
	TestProvider();
	virtual ~TestProvider();

	void setPort(int port);
	void setEndPointReference(std::string endpointRef);

	void startup();
	void shutdown();

	MdibContainer getMdib();
	MdDescription getMdDscription();
	MdState getMdState();

	virtual void runImpl() override;


private:
	SDCProvider sdcProvider;
	TestNumericMetricStateGetHandler nmsGetHandler;
	TestNumericMetricStateSetHandler nmsSetHandler;
	NumericMetricDescriptor nmsSetDescriptor;

};

} /* namespace TestTools */

#endif /* CTESTCASES_TOOLS_TESTPROVIDER_H_ */
