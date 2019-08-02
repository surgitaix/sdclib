
#include "SDCLib/SDCLibrary.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/custom/MdibContainer.h"
#include "SDCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/AlertConditionDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/AlertConditionState.h"
#include "SDCLib/Data/SDC/MDIB/AlertSignalDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/AlertSignalState.h"
#include "SDCLib/Data/SDC/MDIB/AlertSystemDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/AlertSystemState.h"
#include "SDCLib/Data/SDC/MDIB/ChannelDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ClockDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ClockState.h"
#include "SDCLib/Data/SDC/MDIB/EnumStringMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/EnumStringMetricState.h"
#include "SDCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/MdsState.h"
#include "SDCLib/Data/SDC/MDIB/LimitAlertConditionDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/LimitAlertConditionState.h"
#include "SDCLib/Data/SDC/MDIB/MdDescription.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricState.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricValue.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricState.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricValue.h"
#include "SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricState.h"
#include "SDCLib/Data/SDC/SDCConsumer.h"
#include "SDCLib/Data/SDC/SDCProvider.h"
#include "SDCLib/Util/DebugOut.h"

#include "OSELib/SDC/ServiceManager.h"

#include "osdm.hxx"

#include "Poco/Thread.h"
#include "Poco/Timestamp.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"

using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

std::string stateTypeAsString(const AlertConditionState & ) {
	return "AlertConditionState";
}

std::string stateTypeAsString(const AlertSignalState & ) {
	return "AlertSignalState";
}

std::string stateTypeAsString(const EnumStringMetricState & ) {
	return "EnumStringMetricState";
}

std::string stateTypeAsString(const LimitAlertConditionState & ) {
	return "LimitAlertConditionState";
}

std::string stateTypeAsString(const NumericMetricState & ) {
	return "NumericMetricState";
}

std::string stateTypeAsString(const RealTimeSampleArrayMetricState & ) {
	return "RealTimeSampleArrayMetricState";
}

std::string stateTypeAsString(const StringMetricState & ) {
	return "StringMetricState";
}

template<class State>
std::string printPayload(const State & state) {
	return "Printing payload not implemented for " + stateTypeAsString(state);
}

template<>
std::string printPayload(const EnumStringMetricState & state) {
	if (!state.hasObservedValue()) {
		return "no observed value";
	}

	const StringMetricValue value(state.getObservedValue());
	if (!value.hasValue()) {
		return "no value";
	}

	return "Value: " + value.getValue();
}

template<>
std::string printPayload(const NumericMetricState & state) {
	if (!state.hasObservedValue()) {
		return "no observed value";
	}

	const NumericMetricValue value(state.getObservedValue());
	if (!value.hasValue()) {
		return "no value";
	}

	return "Value: " + std::to_string(value.getValue());
}

template<>
std::string printPayload(const StringMetricState & state) {
	if (!state.hasObservedValue()) {
		return "no observed value";
	}

	const StringMetricValue value(state.getObservedValue());
	if (!value.hasValue()) {
		return "no value";
	}

	return "Value: " + value.getValue();
}

template<>
std::string printPayload(const RealTimeSampleArrayMetricState & state) {
	if (!state.hasObservedValue()) {
		return "no observed value";
	}

	const RealTimeSampleArrayValue value(state.getObservedValue());
	if (!value.hasSamples()) {
		return "no samples";
	}

	std::string result("Values: ");
	for (const auto & v : value.getSamples().getValues()) {
		result += std::to_string(v) + " ";
	}
	return result;
}

template<class ConsumerHandlerType>
class Handler : public ConsumerHandlerType {
public:
	Handler(const std::string & handle) :
		_handle(handle)
	{
	}

    virtual ~Handler() {
    }

    void onStateChanged(const typename ConsumerHandlerType::StateType & state) override {
        DebugOut(DebugOut::Default, "GenericSubscription")
        		<< "Metric event for " << stateTypeAsString(state) << " with handle " << _handle << " and payload:" << std::endl
				<< printPayload(state);
    }

    std::string getHandle() override {
        return _handle;
    }

private:
    const std::string _handle;
};

int main (int argc, char * argv[])
{
	std::string epr;
	std::vector<std::string> handles;

	try {
		TC_LAP::CmdLine cmd("Generic subscription tool for various value types.", ' ', "0.01");
		TC_LAP::ValueArg<std::string> eprArg("e", "epr", "EndpointReference of target SDC Device.", true, "UDI_EXAMPLE_1234", "string");
		cmd.add(eprArg);
		TC_LAP::UnlabeledMultiArg<std::string> handlesArg("handle", "Handle of metric that should be subscribed to.", true, "string");
		cmd.add(handlesArg);

		cmd.parse( argc, argv );

		epr = eprArg.getValue();
		handles = handlesArg.getValue();

		if (epr.empty()) {
			std::cerr << "EPR must not be empty. " << std::endl;
			std::exit(0);
		}

	} catch (TC_LAP::ArgException & e) {
		std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
		std::exit(0);
	}

	DebugOut(DebugOut::Default, "GenericSubscription") << std::endl << "Startup";
	SDCLibrary::getInstance().startup();

	OSELib::SDC::ServiceManager t_serviceManager;
	std::unique_ptr<SDCConsumer> consumer(t_serviceManager.discoverEndpointReference(epr));
	if (consumer) {
		DebugOut(DebugOut::Default, "GenericSubscription") << "Connected to device with epr: " << epr;
		const MDDescription mdd(consumer->getMdDescription());

		std::vector<std::unique_ptr<SDCConsumerOperationInvokedHandler>> handlers;

		for (const auto & handle : handles) {
			bool match(false);
			{
				AlertConditionDescriptor descriptor;
				if (mdd.findDescriptor(handle, descriptor)) {
					match = true;
					std::unique_ptr<SDCConsumerOperationInvokedHandler> handler(new Handler<SDCConsumerAlertConditionStateHandler>(handle));
					consumer->registerStateEventHandler(handler.get());
					handlers.push_back(std::move(handler));
				}
			}
			{
				AlertSignalDescriptor descriptor;
				if (mdd.findDescriptor(handle, descriptor)) {
					match = true;
					std::unique_ptr<SDCConsumerOperationInvokedHandler> handler(new Handler<SDCConsumerAlertSignalStateHandler>(handle));
					consumer->registerStateEventHandler(handler.get());
					handlers.push_back(std::move(handler));
				}
			}
			{
				EnumStringMetricDescriptor descriptor;
				if (mdd.findDescriptor(handle, descriptor)) {
					match = true;
					std::unique_ptr<SDCConsumerOperationInvokedHandler> handler(new Handler<SDCConsumerEnumStringMetricStateHandler>(handle));
					consumer->registerStateEventHandler(handler.get());
					handlers.push_back(std::move(handler));
				}
			}
			{
				LimitAlertConditionDescriptor descriptor;
				if (mdd.findDescriptor(handle, descriptor)) {
					match = true;
					std::unique_ptr<SDCConsumerOperationInvokedHandler> handler(new Handler<SDCConsumerLimitAlertConditionStateHandler>(handle));
					consumer->registerStateEventHandler(handler.get());
					handlers.push_back(std::move(handler));
				}
			}
			{
				NumericMetricDescriptor descriptor;
				if (mdd.findDescriptor(handle, descriptor)) {
					match = true;
					std::unique_ptr<SDCConsumerOperationInvokedHandler> handler(new Handler<SDCConsumerNumericMetricStateHandler>(handle));
					consumer->registerStateEventHandler(handler.get());
					handlers.push_back(std::move(handler));
				}
			}
			{
				RealTimeSampleArrayMetricDescriptor descriptor;
				if (mdd.findDescriptor(handle, descriptor)) {
					match = true;
					std::unique_ptr<SDCConsumerOperationInvokedHandler> handler(new Handler<SDCConsumerRealTimeSampleArrayMetricStateHandler>(handle));
					consumer->registerStateEventHandler(handler.get());
					handlers.push_back(std::move(handler));
				}
			}
			{
				StringMetricDescriptor descriptor;
				if (mdd.findDescriptor(handle, descriptor)) {
					match = true;
					std::unique_ptr<SDCConsumerOperationInvokedHandler> handler(new Handler<SDCConsumerStringMetricStateHandler>(handle));
					consumer->registerStateEventHandler(handler.get());
					handlers.push_back(std::move(handler));
				}
			}
			if (!match) {
				DebugOut(DebugOut::Default, "GenericSubscription") << "Could not finde descriptor for handle : " << handle << epr;
			}
		}

		std::string temp;
		std::cin >> temp;

		for (auto & handler : handlers) {
			consumer->unregisterStateEventHandler(handler.get());
		}
	} else {
		DebugOut(DebugOut::Default, "GenericSubscription") << "Connection failed for epr: " << epr;
	}

	SDCLibrary::getInstance().shutdown();
	DebugOut(DebugOut::Default, "GenericSubscription") << "Shutdown" << std::endl;
}

