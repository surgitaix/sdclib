/*
 * SubscriptionManager.cpp
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#include <atomic>
#include <iostream>

#include "Poco/NotificationQueue.h"
#include "Poco/Timestamp.h"
#include "Poco/Timespan.h"
#include "Poco/URI.h"
#include "Poco/UUIDGenerator.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/SocketNotification.h"

#include "eventing.hxx"
#include "NormalizedMessageModel.hxx"

#include "OSELib/DPWS/DPWS11Constants.h"
#include "OSELib/DPWS/OperationTraits.h"
#include "OSELib/DPWS/SubscriptionManager.h"
#include "OSELib/Helper/DurationWrapper.h"
#include "OSELib/HTTP/HTTPSessionManager.h"
#include "OSELib/SOAP/NormalizedMessageAdapter.h"
#include "OSELib/SOAP/NormalizedMessageSerializer.h"
#include "OSELib/SOAP/SoapActionCommand.h"
#include "OSELib/OSCP/OSCPConstants.h"
#include "OSELib/OSCP/ReportTraits.h"

namespace OSELib {
namespace DPWS {

SubscriptionManager::SubscriptionManager(const std::vector<xml_schema::Uri> & allowedEventActions) :
	WithLogger(Log::EVENTSOURCE),
	_allowedEventActions(allowedEventActions),
	_sessionManager(new HTTP::HTTPSessionManager(this->_subscriptions))
{
}

std::unique_ptr<SubscribeTraits::Response> SubscriptionManager::dispatch(const SubscribeTraits::Request & request) {

	using ResponseType = SubscribeTraits::Response;

	const std::string expiresString(request.Expires().present() ? request.Expires().get() : "PT60S");
	Helper::DurationWrapper expiresDuration(expiresString);
	const xml_schema::Duration zeroDuration(false, 0, 0, 0, 0, 0, 0.0);

	if (expiresDuration == zeroDuration || expiresDuration.negative()) {
		const xml_schema::Duration defaultDuration(false, 0, 0, 0, 0, 0, 61.0);
		expiresDuration = defaultDuration;
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

	ActiveSubscriptions::SubscriptionInformation info(request.Delivery().NotifyTo(), expiresDuration.toExpirationTimeStamp(), request.Filter().get());
	const auto mySubscriptionID(_subscriptions.subscribe(info));

	ResponseType::SubscriptionManagerType subscriptionManager(WS::ADDRESSING::AttributedURIType("To be defined by ServiceHandler"));
	ResponseType::SubscriptionManagerType::ReferenceParametersType::IdentifierType myID(mySubscriptionID);
	ResponseType::SubscriptionManagerType::ReferenceParametersType referenceParameters;
	referenceParameters.Identifier().set(myID);
	subscriptionManager.ReferenceParameters().set(referenceParameters);

	std::unique_ptr<ResponseType> response(new ResponseType(subscriptionManager, expiresDuration.toString()));

	log_debug([&] { return "Subscribing " + mySubscriptionID; });

	_subscriptions.printSubscriptions();

	return std::move(response);
}

std::unique_ptr<UnsubscribeTraits::Response> SubscriptionManager::dispatch(const UnsubscribeTraits::Request & , const UnsubscribeTraits::RequestIdentifier & identifier) {

	using ResponseType = UnsubscribeTraits::Response;

	std::unique_ptr<ResponseType> response(new ResponseType());

	log_debug([&] { return "Unsubscribing " + identifier; });
	_subscriptions.unsubscribe(identifier);

	_subscriptions.printSubscriptions();

	return std::move(response);
}

std::unique_ptr<RenewTraits::Response> SubscriptionManager::dispatch(const RenewTraits::Request & request, const RenewTraits::RequestIdentifier & identifier) {

	using ResponseType = RenewTraits::Response;

	const std::string expiresString(request.Expires().present() ? request.Expires().get() : "PT60S");
	Helper::DurationWrapper expiresDuration(expiresString);
	const xml_schema::Duration zeroDuration(false, 0, 0, 0, 0, 0, 0.0);

	if (expiresDuration == zeroDuration || expiresDuration.negative()) {
		const xml_schema::Duration defaultDuration(false, 0, 0, 0, 0, 0, 61.0);
		expiresDuration = defaultDuration;
	}

	std::unique_ptr<ResponseType> response(new ResponseType());
	response->Expires().set(expiresDuration.toString());

	log_debug([&] { return "Renewing " + identifier; });
	_subscriptions.renew(identifier, expiresDuration.toExpirationTimeStamp());

	_subscriptions.printSubscriptions();

	return std::move(response);
}

template <class TraitsType>
void SubscriptionManager::fireEvent(const typename TraitsType::ReportType & report) {
	std::unique_ptr<MESSAGEMODEL::Envelope::HeaderType> header(new MESSAGEMODEL::Envelope::HeaderType());
	using MessageIDType = MESSAGEMODEL::Envelope::HeaderType::MessageIDType;
	header->MessageID().set(MessageIDType(Poco::UUIDGenerator::defaultGenerator().create().toString()));
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

template void SubscriptionManager::fireEvent<OSELib::OSCP::EpisodicContextChangedReportTraits>(const OSELib::OSCP::EpisodicContextChangedReportTraits::ReportType & report);
template void SubscriptionManager::fireEvent<OSELib::OSCP::EpisodicAlertReportTraits>(const OSELib::OSCP::EpisodicAlertReportTraits::ReportType & report);
template void SubscriptionManager::fireEvent<OSELib::OSCP::EpisodicMetricReportTraits>(const OSELib::OSCP::EpisodicMetricReportTraits::ReportType & report);
template void SubscriptionManager::fireEvent<OSELib::OSCP::PeriodicAlertReportTraits>(const OSELib::OSCP::PeriodicAlertReportTraits::ReportType & report);
template void SubscriptionManager::fireEvent<OSELib::OSCP::PeriodicContextChangedReportTraits>(const OSELib::OSCP::PeriodicContextChangedReportTraits::ReportType & report);
template void SubscriptionManager::fireEvent<OSELib::OSCP::PeriodicMetricReportTraits>(const OSELib::OSCP::PeriodicMetricReportTraits::ReportType & report);
template void SubscriptionManager::fireEvent<OSELib::OSCP::OperationInvokedReportTraits>(const OSELib::OSCP::OperationInvokedReportTraits::ReportType & report);

} /* namespace DPWS */
} /* namespace OSELib */
