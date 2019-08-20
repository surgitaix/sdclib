/*
 * SubscriptionManager.cpp
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 26.07.2019, baumeister
 */

#include "OSELib/DPWS/SubscriptionManager.h"

#include "eventing.hxx"

#include "OSELib/DPWS/OperationTraits.h"
#include "OSELib/Helper/DurationWrapper.h"
#include "OSELib/HTTP/HTTPSessionManager.h"
#include "OSELib/SOAP/NormalizedMessageAdapter.h"
#include "OSELib/SOAP/NormalizedMessageSerializer.h"
#include "OSELib/SOAP/SoapActionCommand.h"

#include "SDCLib/SDCInstance.h"

#include <Poco/URI.h>
#include <Poco/Net/HTTPClientSession.h>


namespace OSELib {
namespace DPWS {

const std::chrono::seconds DEFAULT_DURATION_S = std::chrono::seconds(60);

SubscriptionManager::SubscriptionManager(const std::vector<xml_schema::Uri> & allowedEventActions, SDCLib::Config::SSLConfig_shared_ptr p_SSLConfig)
: OSELib::Helper::WithLogger(Log::EVENTSOURCE)
, _allowedEventActions(allowedEventActions)
, _sessionManager(new HTTP::HTTPSessionManager(this->_subscriptions, p_SSLConfig))
{
}

std::unique_ptr<SubscribeTraits::Response> SubscriptionManager::dispatch(const SubscribeTraits::Request & request) {

	using ResponseType = SubscribeTraits::Response;

	const std::string expiresString(request.Expires().present() ? request.Expires().get() : "PT60S");
	Helper::DurationWrapper t_expiresDuration(expiresString);

	if (t_expiresDuration.toDuration_s().second == std::chrono::seconds(0) || t_expiresDuration.negative()) {
		if(request.Expires().present()) {
			// NOTE: THIS MUST FAIL! See WS-Eventing wse:InvalidExpirationTime ?
		}
		// Falling back to default
		t_expiresDuration = Helper::DurationWrapper(DEFAULT_DURATION_S);
	}

	if (request.Delivery().Mode().present() && request.Delivery().Mode().get() != OSELib::WS_EVENTING_DELIVERYMODE_PUSH) {
		throw SOAP::SoapActionCommand::DispatchingFailed("Delivery mode not supported: " + request.Delivery().Mode().get());
	}

	if (!request.Filter().present()) {
		throw SOAP::SoapActionCommand::DispatchingFailed("No filter specified");
	}

	if (request.Filter().get().Dialect() != OSELib::WS_EVENTING_FILTER_ACTION) {
		throw SOAP::SoapActionCommand::DispatchingFailed("Filter mode not supported: " + request.Filter().get().Dialect());
	}
	for (const auto & filterAction : request.Filter().get()) {
		if (std::find(_allowedEventActions.begin(), _allowedEventActions.end(), filterAction) == _allowedEventActions.end()) {
			throw SOAP::SoapActionCommand::DispatchingFailed("Unknown event action: " + filterAction);
		}
	}

	auto t_result_TimePoint = t_expiresDuration.toExpirationTimePoint();
	if(!t_result_TimePoint.first) {
		log_error([&] { return "Subscribe: TimePoint conversion failed!"; });
		throw SOAP::SoapActionCommand::DispatchingFailed("Subscribe: Timepoint / Duration parse Error!");
	}


	ActiveSubscriptions::SubscriptionInformation info(request.Delivery().NotifyTo(), t_result_TimePoint.second, request.Filter().get());
	const auto mySubscriptionID(_subscriptions.subscribe(info));

	log_debug([&] { return "Subscribing " + mySubscriptionID; });

	// Build the response
	ResponseType::SubscriptionManagerType subscriptionManager(WS::ADDRESSING::AttributedURIType("To be defined by ServiceHandler"));
	ResponseType::SubscriptionManagerType::ReferenceParametersType::IdentifierType myID(mySubscriptionID);
	ResponseType::SubscriptionManagerType::ReferenceParametersType referenceParameters;
	referenceParameters.Identifier().set(myID);
	subscriptionManager.ReferenceParameters().set(referenceParameters);
	std::unique_ptr<ResponseType> response(new ResponseType(subscriptionManager, t_expiresDuration.toString()));

	_subscriptions.printSubscriptions();

	return response;
}

std::unique_ptr<UnsubscribeTraits::Response> SubscriptionManager::dispatch(const UnsubscribeTraits::Request & , const UnsubscribeTraits::RequestIdentifier & identifier) {

	using ResponseType = UnsubscribeTraits::Response;

	std::unique_ptr<ResponseType> response(new ResponseType());

	log_debug([&] { return "Unsubscribing " + identifier; });
	_subscriptions.unsubscribe(identifier);

	_subscriptions.printSubscriptions();

	return std::move(response);
}

std::unique_ptr<RenewTraits::Response> SubscriptionManager::dispatch(const RenewTraits::Request & request, const RenewTraits::RequestIdentifier & identifier)
{
	// Check if the subscription already exists
	auto t_subscription = _subscriptions.getStatus(identifier);
	if(!t_subscription.first) {
		// FIXME: Create a new Subscription! https://www.w3.org/Submission/WS-Eventing/#Renew
	}

	using ResponseType = RenewTraits::Response;

	const std::string expiresString(request.Expires().present() ? request.Expires().get() : "PT60S");
	Helper::DurationWrapper t_expiresDuration(expiresString);

	auto t_duration = t_expiresDuration.toDuration_s();
	if ((t_duration.second == std::chrono::seconds(0)) || t_expiresDuration.negative()) {
		t_expiresDuration = Helper::DurationWrapper(DEFAULT_DURATION_S);
	}

	std::unique_ptr<ResponseType> response(new ResponseType());
	response->Expires().set(t_expiresDuration.toString());

	auto t_result_TimePoint = t_expiresDuration.toExpirationTimePoint();
	if(t_result_TimePoint.first) {
		log_debug([&] { return "Renewing " + identifier; });
		_subscriptions.renew(identifier, t_result_TimePoint.second);
	}
	else {
		// TODO Fallback? Error response?
		log_error([&] { return "Renew: TimePoint conversion failed! No renewing!"; });
	}

	_subscriptions.printSubscriptions();

	return response;
}

std::unique_ptr<GetStatusTraits::Response> SubscriptionManager::dispatch(const GetStatusTraits::Request & request, const GetStatusTraits::RequestIdentifier & identifier)
{
	auto t_subscription = _subscriptions.getStatus(identifier);
	if(!t_subscription.first) {
		log_debug([] { return "GetStatus: Unknown Identifier!"; });
		throw SOAP::SoapActionCommand::DispatchingFailed("### GETSTATUS: Unknown Identifier: " + identifier + "!");
	}

	auto t_expiresDuration = Helper::DurationWrapper(std::chrono::duration_cast<std::chrono::seconds>(t_subscription.second.m_expirationTime-std::chrono::system_clock::now()));

	auto t_duration = t_expiresDuration.toDuration_s();
	if ((t_duration.second == std::chrono::seconds(0)) || t_expiresDuration.negative()) {
		// NOTE: EXPIRED! WHAT TO DO HERE? -> Copied from renew...
		t_expiresDuration = Helper::DurationWrapper(DEFAULT_DURATION_S);
	}

	// Create the Response
	using ResponseType = GetStatusTraits::Response;
	std::unique_ptr<ResponseType> t_response(new ResponseType());
	t_response->Expires().set(t_expiresDuration.toString());

	_subscriptions.printSubscriptions();
	return t_response;
}

template <class TraitsType>
void SubscriptionManager::fireEvent(const typename TraitsType::ReportType & report) {
	std::unique_ptr<MESSAGEMODEL::Envelope::HeaderType> header(new MESSAGEMODEL::Envelope::HeaderType());
	using MessageIDType = MESSAGEMODEL::Envelope::HeaderType::MessageIDType;
	header->MessageID().set(MessageIDType(SDCLib::SDCInstance::calcMSGID()));
	using ActionType = MESSAGEMODEL::Envelope::HeaderType::ActionType;
	header->Action().set(ActionType(TraitsType::Action()));

	std::unique_ptr<MESSAGEMODEL::Envelope::BodyType> body(new MESSAGEMODEL::Envelope::BodyType());

	std::unique_ptr<MESSAGEMODEL::Envelope> eventMessage(new MESSAGEMODEL::Envelope(std::move(header), std::move(body)));

	SOAP::NormalizedMessageAdapter<typename TraitsType::ReportType> adapter;
	adapter.set(*eventMessage, std::unique_ptr<typename TraitsType::ReportType>(new typename TraitsType::ReportType(report)));

	SOAP::NormalizedMessageSerializer serializer;
	for (const auto & epr : _subscriptions.getSubscriptions(TraitsType::Action())) {

		eventMessage->Header().To(epr.second.Address());
		eventMessage->Header().Identifier().reset();

		if (epr.second.ReferenceParameters().present() && epr.second.ReferenceParameters().get().Identifier().present()) {
			eventMessage->Header().Identifier(epr.second.ReferenceParameters().get().Identifier().get());
		}

		const Poco::URI uri(epr.second.Address());

		log_trace([&] { return "Enqueuing event for " + epr.first; });

		_sessionManager->enqueMessage(uri, serializer.serialize(*eventMessage), epr.first);
	}
}

template void SubscriptionManager::fireEvent<OSELib::SDC::EpisodicContextReportTraits>(const OSELib::SDC::EpisodicContextReportTraits::ReportType & report);
template void SubscriptionManager::fireEvent<OSELib::SDC::EpisodicAlertReportTraits>(const OSELib::SDC::EpisodicAlertReportTraits::ReportType & report);
template void SubscriptionManager::fireEvent<OSELib::SDC::EpisodicMetricReportTraits>(const OSELib::SDC::EpisodicMetricReportTraits::ReportType & report);
template void SubscriptionManager::fireEvent<OSELib::SDC::PeriodicAlertReportTraits>(const OSELib::SDC::PeriodicAlertReportTraits::ReportType & report);
template void SubscriptionManager::fireEvent<OSELib::SDC::PeriodicContextReportTraits>(const OSELib::SDC::PeriodicContextReportTraits::ReportType & report);
template void SubscriptionManager::fireEvent<OSELib::SDC::PeriodicMetricReportTraits>(const OSELib::SDC::PeriodicMetricReportTraits::ReportType & report);
template void SubscriptionManager::fireEvent<OSELib::SDC::OperationInvokedReportTraits>(const OSELib::SDC::OperationInvokedReportTraits::ReportType & report);

} /* namespace DPWS */
} /* namespace OSELib */
