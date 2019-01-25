/*
 * TestConsumer.cpp
 *
 *  Created on: Jan 17, 2019
 *      Author: sebastian
 */

#include <algorithm>
#include <memory>
#include "TestConsumer.h"


const std::string HANDLE_SET_NUMERICMETRIC("handle_set_numeric_metric");


namespace TestTools {

TestConsumer::TestConsumer() :
	consumer(nullptr),
	setHandler(nullptr)
{

}

TestConsumer::~TestConsumer() {

}

void TestConsumer::setConsumer(std::unique_ptr<SDCConsumer> sdcConsumer) {
	consumer = std::move(sdcConsumer);
}

std::shared_ptr<SDCConsumer> TestConsumer::getConsumer() {
	return consumer;
}

void TestConsumer::setConnectionLostHandler(SDCConsumerConnectionLostHandler *handler) {
	consumer->setConnectionLostHandler(handler);
}

void TestConsumer::runImpl() {
	while(!isInterrupted()) {

	}
}

void TestConsumer::disconnect() {
	consumer->disconnect();
	interrupt();
}

void TestConsumer::shutdown() {
	if(consumer == nullptr) {
		return;
	}
	disconnect();
}

void TestConsumer::setNumericMetricStateValue(double val)
{
	if(setHandler == nullptr) {
		return;
	}
	std::unique_ptr<NumericMetricState> setNumericMetricState(consumer->requestState<NumericMetricState>(HANDLE_SET_NUMERICMETRIC));
	setNumericMetricState->setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(val));
	FutureInvocationState fis;
	consumer->commitState(*setNumericMetricState, fis);
	Util::DebugOut(Util::DebugOut::Default, "Consumer") << "Commit result: " << fis.waitReceived(InvocationState::Fin, 10000);
}

void TestConsumer::registerNumericMetricStateSetHandler()
{
	if(consumer == nullptr) {
		return;
	}
	else {
		setHandler = std::make_shared<SettableConsumerNumericMetricStateHandler>(HANDLE_SET_NUMERICMETRIC);
		consumer->registerStateEventHandler(setHandler.get());
	}
}

void TestConsumer::unregisterNumericMetricStateSetHandler()
{
	if((consumer == nullptr) || (setHandler == nullptr)) {
		return;
	}
	else {
		consumer->unregisterStateEventHandler(setHandler.get());
	}
}

} /* namespace TestTools */
