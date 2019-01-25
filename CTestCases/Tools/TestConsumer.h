/*
 * TestConsumer.h
 *
 *  Created on: Jan 17, 2019
 *      Author: rosenau
 */

#ifndef CTESTCASES_TOOLS_TESTCONSUMER_H_
#define CTESTCASES_TOOLS_TESTCONSUMER_H_

#include "OSCLib/Util/Task.h"
#include "OSCLib/Util/DebugOut.h"
#include "OSCLib/Data/SDC/SDCConsumer.h"
#include "OSCLib/Data/SDC/SDCConsumerMDStateHandler.h"
#include "OSCLib/Data/SDC/MDIB/NumericMetricState.h"
#include "OSCLib/Data/SDC/MDIB/NumericMetricValue.h"
#include "OSCLib/Data/SDC/MDIB/MetricQuality.h"
#include "OSCLib/Data/SDC/FutureInvocationState.h"
#include "OSCLib/Data/SDC/SDCConsumerConnectionLostHandler.h"


using namespace SDCLib;
using namespace SDCLib::Data;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

namespace TestTools {

class TestConsumer : public Util::Task {
public:

	class SettableConsumerNumericMetricStateHandler : public SDCConsumerMDStateHandler<NumericMetricState>
	{
	public:
		SettableConsumerNumericMetricStateHandler(std::string descriptionHandler) : SDCConsumerMDStateHandler(descriptionHandler) {
		}

		void onStateChanged(const NumericMetricState &state) override{
			Util::DebugOut(Util::DebugOut::Default, "PeriodicEvents") << "Received periodic state of " << descriptorHandle << " " <<  state.getMetricValue().getValue() << std::endl;
		}

	};


	class SystemAlertConsumerStateHandler : public SDCConsumerMDStateHandler<AlertSystemState> {
	public:
		SystemAlertConsumerStateHandler(const std::string descriptorHandle) : SDCConsumerMDStateHandler(descriptorHandle)
		{

		}

		void onStateChanged(const AlertSystemState &) override {
			Util::DebugOut(Util::DebugOut::Default, "PeriodicEvents") << "Consumer: Received alert condition change of " << descriptorHandle << std::endl;
		}
	};

	class AlertConsumerStateHandler : public SDCConsumerMDStateHandler<AlertConditionState> {
	public:
		AlertConsumerStateHandler(const std::string descriptorHandle) : SDCConsumerMDStateHandler(descriptorHandle)
		{

		}

		void onStateChanged(const AlertConditionState &) override {
			Util::DebugOut(Util::DebugOut::Default, "PeriodicEvents") << "Consumer: Received alert condition change of " << descriptorHandle << std::endl;

		}
	};

	TestConsumer();
	virtual ~TestConsumer();

	void setConsumer(std::unique_ptr<SDCConsumer> consumer);

	std::shared_ptr<SDCConsumer> getConsumer();

	void setConnectionLostHandler(SDCConsumerConnectionLostHandler *handler);

	void runImpl();

	void disconnect();

	void shutdown();

	void registerNumericMetricStateSetHandler();

	void unregisterNumericMetricStateSetHandler();

	void setNumericMetricStateValue(double val);

private:
	std::shared_ptr<SDCConsumer> consumer;
	std::shared_ptr<SettableConsumerNumericMetricStateHandler> setHandler;
};

} /* namespace TestTools */

#endif /* CTESTCASES_TOOLS_TESTCONSUMER_H_ */
