/*
 * TestClass.cpp
 *
 *  Created on: Jan 17, 2019
 *      Author: rosenau
 */

#include "PulseOximeterConsumer.h"

#include <algorithm>
#include <memory>

#include "PulseOximeterHandleNames.h"


PulseOximeterConsumer::PulseOximeterConsumer() :
	consumer(nullptr),
	pulseRateGetHandler(nullptr),
	satO2GetHandler(nullptr),
	pulseRateAlertHandler(nullptr),
	pulseRateAlertSignalHandler(nullptr),
	satO2AlertSignalHandler(nullptr),
	oximeterAlertSystemHandler(nullptr)
{}

PulseOximeterConsumer::~PulseOximeterConsumer() {}

std::shared_ptr<SDCConsumer> PulseOximeterConsumer::getConsumer() {
	return consumer;
}



void PulseOximeterConsumer::setConsumer(std::unique_ptr<SDCConsumer> sdcConsumer) {
	consumer = std::move(sdcConsumer);
}

void PulseOximeterConsumer::runImpl() {
	while (!isInterrupted()) {

	}
}

void PulseOximeterConsumer::registerSatO2Handler() {
	if (consumer == nullptr) {
		return;
	}
	satO2GetHandler = std::make_shared<PulseOximeterSatO2ConsumerGetHandler>(PULSE_OXIMETER_SAT_O2_GET_HANDLE);
	consumer->registerStateEventHandler(satO2GetHandler.get());
}

void PulseOximeterConsumer::registerPulseRateHandler() {
	if (consumer == nullptr) {
		return;
	}
	pulseRateGetHandler = std::make_shared<PulseOximeterPulseRateConsumerGetHandler>(PULSE_OXIMETER_PULSE_RATE_GET_HANDLE);
	consumer->registerStateEventHandler(pulseRateGetHandler.get());
}

void PulseOximeterConsumer::registerPulseRateAlertHandler() {
	if (consumer == nullptr) {
		return;
	}
	pulseRateAlertHandler = std::make_shared<PulseOximeterPulseRateAlertConditionConsumerHandle>(PULSE_OXIMETER_PULSE_RATE_LIMIT_ALERT_HANDLE);
	consumer->registerStateEventHandler(pulseRateAlertHandler.get());
}

void PulseOximeterConsumer::registerPulseRateAlertSignalHandler() {
	if (consumer == nullptr) {
		return;
	}
	pulseRateAlertSignalHandler = std::make_shared<PulseOximeterAlertSignalConsumerHandle>(PULSE_OXIMETER_PULSE_RATE_LIMIT_ALERT_SIGNAL_HANDLE);
	consumer->registerStateEventHandler(pulseRateAlertSignalHandler.get());
}

void PulseOximeterConsumer::registerSatO2AlertHandler() {
	if (consumer == nullptr) {
		return;
	}
	satO2AlertHandler = std::make_shared<PulseOximeterSatO2AlertConditionConsumerHandle>(PULSE_OXIMETER_SAT_O2_LIMIT_ALERT_HANDLE);
	consumer->registerStateEventHandler(satO2AlertHandler.get());
}

void PulseOximeterConsumer::registerSatO2AlertSignalHandler() {
	if (consumer == nullptr) {
		return;
	}
	pulseRateAlertSignalHandler = std::make_shared<PulseOximeterAlertSignalConsumerHandle>(PULSE_OXIMETER_SAT_O2_LIMIT_ALERT_SIGNAL_HANDLE);
	consumer->registerStateEventHandler(pulseRateAlertSignalHandler.get());
}

void PulseOximeterConsumer::registerOximeterAlertSystemHandler() {
	if (consumer == nullptr) {
		return;
	}
	oximeterAlertSystemHandler = std::make_shared<PulseOximeterAlertSystemConsumerHandle>(PULSE_OXIMETER_ALERT_SYSTEM_HANDLE);
	consumer->registerStateEventHandler(oximeterAlertSystemHandler.get());
}

void PulseOximeterConsumer::unregisterSatO2Handler() {
	if((consumer == nullptr) || (satO2GetHandler == nullptr)) {
		return;
	}
	else {
		consumer->unregisterStateEventHandler(satO2GetHandler.get());
	}
}

void PulseOximeterConsumer::unregisterPulseRateHandler() {
	if((consumer == nullptr) || (pulseRateGetHandler == nullptr)) {
		return;
	}
	else {
		consumer->unregisterStateEventHandler(pulseRateGetHandler.get());
	}
}

void PulseOximeterConsumer::unregisterPulseRateAlertHanlder() {
	if((consumer == nullptr) || (pulseRateAlertHandler == nullptr)) {
		return;
	}
	else {
		consumer->unregisterStateEventHandler(pulseRateAlertHandler.get());
	}
}

void PulseOximeterConsumer::unregisterOximeterAlertSystemHandler() {
	if((consumer == nullptr) || (oximeterAlertSystemHandler == nullptr)) {
		return;
	}
	else {
		consumer->unregisterStateEventHandler(oximeterAlertSystemHandler.get());
	}
}

void PulseOximeterConsumer::unregisterPulseRateAlertSignalHandler() {
	if((consumer == nullptr) || (pulseRateAlertSignalHandler == nullptr)) {
		return;
	}
	else {
		consumer->unregisterStateEventHandler(pulseRateAlertSignalHandler.get());
	}
}

void PulseOximeterConsumer::unregisterSatO2AlertHandler() {
	if((consumer == nullptr) || (satO2AlertHandler ==nullptr)) {
		return;
	}
	else {
		consumer->unregisterStateEventHandler(satO2AlertHandler.get());
	}
}

void PulseOximeterConsumer::unregisterSatO2AlertSignalHandler() {
	if((consumer == nullptr) || (satO2AlertSignalHandler == nullptr)) {
		return;
	}
	else {
		consumer->unregisterStateEventHandler(satO2AlertSignalHandler.get());
	}
}


void PulseOximeterConsumer::disconnect() {
	consumer->disconnect();
}

void PulseOximeterConsumer::shutdown() {
	if(consumer == nullptr) {
		return;
	}
	unregisterPulseRateHandler();
	unregisterSatO2Handler();
	unregisterPulseRateAlertHanlder();
	unregisterOximeterAlertSystemHandler();
	unregisterPulseRateAlertSignalHandler();
	unregisterSatO2AlertHandler();
	unregisterSatO2AlertSignalHandler();
	disconnect();
}

