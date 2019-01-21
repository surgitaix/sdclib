/*
 * TestClass.h
 *
 *  Created on: Jan 17, 2019
 *      Author: rosenau
 */

#ifndef CTESTCASES_TOOLS_PULSEOXIMETERCONSUMER_H_
#define CTESTCASES_TOOLS_PULSEOXIMETERCONSUMER_H_

#include <map>

#include "OSCLib/Data/SDC/SDCConsumerMDStateHandler.h"

#include "OSCLib/Data/SDC/MDIB/NumericMetricState.h"
#include "OSCLib/Data/SDC/MDIB/NumericMetricValue.h"
#include "OSCLib/Data/SDC/MDIB/AlertConditionState.h"
#include "OSCLib/Data/SDC/MDIB/AlertSignalState.h"
#include "OSCLib/Data/SDC/MDIB/LimitAlertConditionState.h"
#include "OSCLib/Data/SDC/MDIB/AlertSystemState.h"

#include "OSCLib/Util/Task.h"
#include "OSCLib/Util/DebugOut.h"
#include "OSCLib/Data/SDC/SDCConsumer.h"

using namespace SDCLib;
using namespace SDCLib::Data;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

class PulseOximeterConsumer : public Util::Task {
public:
	//Handler for O2 saturation
	class PulseOximeterSatO2ConsumerGetHandler : public SDCConsumerMDStateHandler<NumericMetricState>{
	public:
		PulseOximeterSatO2ConsumerGetHandler(std::string descriptorHandle) : SDCConsumerMDStateHandler(descriptorHandle) {
		}

		//sets the current value of the satO2 as received from the provider
		void onStateChanged(const NumericMetricState &state) override {
			double val = state.getMetricValue().getValue();
			DebugOut(DebugOut::Default, "PulseOximeterConsumer") << "Consumer: Received value changed of " << this->getDescriptorHandle() << ": " << val << std::endl;
			currentSatO2 = val;
		}

		void onOperationInvoked(const OperationInvocationContext &oic, InvocationState is) override {

		}

		double getCurretnSatO2() {
			return currentSatO2;
		}

	private:
		double currentSatO2 = 0;
	};

//		Handle for pulse rate
	class PulseOximeterPulseRateConsumerGetHandler : public SDCConsumerMDStateHandler<NumericMetricState>
	{
	public:
		PulseOximeterPulseRateConsumerGetHandler(std::string descriptorHandle) : SDCConsumerMDStateHandler(descriptorHandle){

		}

		//sets the current value of the pulseRate as received from the provider
		void onStateChanged(const NumericMetricState &state) override {
			double val = state.getMetricValue().getValue();
			DebugOut(DebugOut::Default, "PulseOximeterConsumer") << "Consumer: Received value changed of " << this->getDescriptorHandle() << ": " << val << std::endl;
			currentPulseRate = val;
		}

		void onOperationInvoked(const OperationInvocationContext &oic, InvocationState is) override {

		}

		double getCurrentPulseRate() {
			return currentPulseRate;
		}

	private:
		double currentPulseRate = 0;
	};

	//Handle for pulse rate alert
	class PulseOximeterPulseRateAlertConditionConsumerHandle : public SDCConsumerMDStateHandler<LimitAlertConditionState> {
	public:
		PulseOximeterPulseRateAlertConditionConsumerHandle(std::string descriptorHandle) : SDCConsumerMDStateHandler(descriptorHandle) {
		}

		void onStateChanged(const LimitAlertConditionState & state) override {
			std::cout << "ALERT!!";
			//alertPresence == state.getPresence();
		}

		void onOperationInvoked(const OperationInvocationContext & oic, InvocationState is) override {
				//DebugOut(DebugOut::Default, "SimpleSDC") << "Consumer: Received operation invoked (ID, STATE) of " << descriptorHandle << ": " << oic.transactionId << ", " << EnumToString::convert(is) << std::endl;
		}
	};



		//Handle for satO2 alert condition
		class PulseOximeterSatO2AlertConditionConsumerHandle : public SDCConsumerMDStateHandler<AlertConditionState> {
		public:
			PulseOximeterSatO2AlertConditionConsumerHandle(std::string descriptorHandle) : SDCConsumerMDStateHandler(descriptorHandle) {
			}

			void onStateChanged(const AlertConditionState & state) override {
				std::cout << "ALERT!!";
				alertPresence = state.getPresence();
			}

			void onOperationInvoked(const OperationInvocationContext & oic, InvocationState is) override {
			        //DebugOut(DebugOut::Default, "SimpleSDC") << "Consumer: Received operation invoked (ID, STATE) of " << descriptorHandle << ": " << oic.transactionId << ", " << EnumToString::convert(is) << std::endl;
			}
		private:
			bool alertPresence;
		};

		//Handle for satO2 alert singal
		class PulseOximeterAlertSignalConsumerHandle : public SDCConsumerMDStateHandler<AlertSignalState> {
		public:
			PulseOximeterAlertSignalConsumerHandle(std::string descriptorHandle) : SDCConsumerMDStateHandler(descriptorHandle) {
			}

			void onStateChanged(const AlertSignalState & state) override {
				std::cout << "ALERT!!";
				alertPresence == state.getPresence();
			}

			void onOperationInvoked(const OperationInvocationContext & oic, InvocationState is) override {
			        //DebugOut(DebugOut::Default, "SimpleSDC") << "Consumer: Received operation invoked (ID, STATE) of " << descriptorHandle << ": " << oic.transactionId << ", " << EnumToString::convert(is) << std::endl;
			}
		private:
			AlertSignalPresence alertPresence;

		};


		class PulseOximeterAlertSystemConsumerHandle : public SDCConsumerMDStateHandler<AlertSystemState> {
		public:
			PulseOximeterAlertSystemConsumerHandle(std::string descriptorHandle) : SDCConsumerMDStateHandler(descriptorHandle) {
			}

			void onStateChanged(const AlertSystemState & state) override {
				std::cout << "ALERT!!";

			}

			void onOperationInvoked(const OperationInvocationContext & oic, InvocationState is) override {
			        //DebugOut(DebugOut::Default, "SimpleSDC") << "Consumer: Received operation invoked (ID, STATE) of " << descriptorHandle << ": " << oic.transactionId << ", " << EnumToString::convert(is) << std::endl;
			}
		private:

		};



public:
	PulseOximeterConsumer();
	virtual ~PulseOximeterConsumer();

	void setConsumer(std::unique_ptr<SDCConsumer> consumer);

	std::shared_ptr<SDCConsumer> getConsumer();

	void registerSatO2Handler();
	void registerPulseRateHandler();
	void registerPulseRateAlertHandler();
	void registerPulseRateAlertSignalHandler();
	void registerSatO2AlertHandler();
	void registerSatO2AlertSignalHandler();
	void registerOximeterAlertSystemHandler();

	void unregisterSatO2Handler();
	void unregisterPulseRateHandler();
	void unregisterPulseRateAlertHanlder();
	void unregisterPulseRateAlertSignalHandler();
	void unregisterSatO2AlertHandler();
	void unregisterSatO2AlertSignalHandler();
	void unregisterOximeterAlertSystemHandler();

	void runImpl();

	void disconnect();

	void shutdown();

private:
	std::shared_ptr<SDCConsumer> consumer;
	std::shared_ptr<PulseOximeterPulseRateConsumerGetHandler> pulseRateGetHandler;
	std::shared_ptr<PulseOximeterSatO2ConsumerGetHandler> satO2GetHandler;
	std::shared_ptr<PulseOximeterPulseRateAlertConditionConsumerHandle> pulseRateAlertHandler;
	std::shared_ptr<PulseOximeterSatO2AlertConditionConsumerHandle> satO2AlertHandler;
	std::shared_ptr<PulseOximeterAlertSignalConsumerHandle> pulseRateAlertSignalHandler;
	std::shared_ptr<PulseOximeterAlertSignalConsumerHandle> satO2AlertSignalHandler;
	std::shared_ptr<PulseOximeterAlertSystemConsumerHandle> oximeterAlertSystemHandler;
};

#endif /* CTESTCASES_TOOLS_PULSEOXIMETERCONSUMER_H_ */
