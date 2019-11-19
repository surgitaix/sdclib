/*
 * SubscriptionClient.cpp
 *
 *  Created on: 14.12.2015, matthias
 *  Modified on: 22.08.2019, baumeister
 *
 */

#include "OSELib/DPWS/SubscriptionClient.h"
#include "OSELib/SOAP/GenericSoapInvoke.h"
#include "OSELib/SDC/DefaultSDCSchemaGrammarProvider.h"
#include "OSELib/Helper/DurationWrapper.h"
#include "SDCLib/SDCInstance.h"

#include "DataModel/ws-addressing.hxx"
#include "DataModel/eventing.hxx"

// Note: Configure these values later?
const std::size_t RENEW_THRESHOLD = 60; // Time in sec a renew will be needed
const double RENEW_FACTOR = 2.0; // Multiplied with the RENEW_THRESHOLD = EXPIRATION_TIME for the subscription

using namespace OSELib;
using namespace OSELib::DPWS;

class RenewInvoke : public OSELib::SOAP::GenericSoapInvoke<OSELib::DPWS::RenewTraits>
{
private:
	const WS::EVENTING::Identifier m_identifier;
public:
	RenewInvoke(const Poco::URI & p_requestURI, const WS::EVENTING::Identifier & p_identifier, OSELib::Helper::XercesGrammarPoolProvider & p_grammarProvider)
	: OSELib::SOAP::GenericSoapInvoke<OSELib::DPWS::RenewTraits>(p_requestURI, p_grammarProvider)
	, m_identifier(p_identifier)
	{ }

	virtual std::unique_ptr<MESSAGEMODEL::Header> createHeader() override {
		auto t_header(OSELib::SOAP::GenericSoapInvoke<OSELib::DPWS::RenewTraits>::createHeader());
		t_header->Identifier(m_identifier);
		return t_header;
	}
};

class GetStatusInvoke : public OSELib::SOAP::GenericSoapInvoke<OSELib::DPWS::GetStatusTraits>
{
private:
	const WS::EVENTING::Identifier m_identifier;
public:
	GetStatusInvoke(const Poco::URI & p_requestURI, const WS::EVENTING::Identifier & p_identifier, OSELib::Helper::XercesGrammarPoolProvider & p_grammarProvider)
	: OSELib::SOAP::GenericSoapInvoke<OSELib::DPWS::GetStatusTraits>(p_requestURI, p_grammarProvider)
	, m_identifier(p_identifier)
	{ }

	virtual std::unique_ptr<MESSAGEMODEL::Header> createHeader() override {
		auto t_header(OSELib::SOAP::GenericSoapInvoke<OSELib::DPWS::GetStatusTraits>::createHeader());
		t_header->Identifier(m_identifier);
		return t_header;
	}
};

class UnsubscribeInvoke : public OSELib::SOAP::GenericSoapInvoke<OSELib::DPWS::UnsubscribeTraits>
{
private:
	const WS::EVENTING::Identifier m_identifier;
public:
	UnsubscribeInvoke(const Poco::URI & p_requestURI, const WS::EVENTING::Identifier & p_identifier, OSELib::Helper::XercesGrammarPoolProvider & p_grammarProvider)
	: OSELib::SOAP::GenericSoapInvoke<OSELib::DPWS::UnsubscribeTraits>(p_requestURI, p_grammarProvider)
	, m_identifier(p_identifier)
	{ }

	virtual std::unique_ptr<MESSAGEMODEL::Header> createHeader() override {
		auto t_header(OSELib::SOAP::GenericSoapInvoke<OSELib::DPWS::UnsubscribeTraits>::createHeader());
		t_header->Identifier(m_identifier);
		return t_header;
	}
};

SubscriptionClient::SubscriptionClient(const std::vector<SubscriptionInformation> & p_subscriptions, Poco::Net::Context::Ptr p_context)
: OSELib::Helper::WithLogger(Log::EVENTSINK)
, m_runnableAdapter(*this, &SubscriptionClient::run)
, m_SSLContext(p_context) // Can be nullptr!
{
	for (const auto & item : p_subscriptions) {
		m_subscriptions.emplace(SDCLib::SDCInstance::calcUUID(), item);
	}
	m_thread.start(m_runnableAdapter);
}

SubscriptionClient::~SubscriptionClient()
{
	// TODO: Cleanup / Restructure along with run() !
	m_thread.wakeUp();
	m_thread.join();
}

void SubscriptionClient::run() {

	// todo clean up and split method
	SDC::DefaultSDCSchemaGrammarProvider t_grammarProvider;

	auto t_renewThreshold = std::chrono::seconds(RENEW_THRESHOLD);

	auto t_expireString = "PT" + std::to_string(t_renewThreshold.count() * RENEW_FACTOR) + "S"; // Note: Factor on the renew threshold
	const WS::EVENTING::ExpirationType t_defaultExpires(t_expireString);

	std::size_t t_sleepQueryGetStatus_ms = 2000; // TODO: MAGIC NUMBER

	for (const auto & t_subscription : m_subscriptions) {
		// get information
		const WS::ADDRESSING::AttributedURIType t_address(t_subscription.second.m_sinkURI.toString());
		WS::ADDRESSING::EndpointReferenceType t_epr(t_address);
		WS::ADDRESSING::EndpointReferenceType::ReferenceParametersType t_referenceParameters;
		t_referenceParameters.Identifier(WS::EVENTING::Identifier(t_subscription.first));
		t_epr.ReferenceParameters().set(t_referenceParameters);
		const WS::EVENTING::DeliveryType t_delivery(t_epr);


		OSELib::DPWS::SubscribeTraits::Request t_request(t_delivery);
		t_request.Expires(t_defaultExpires);
		t_request.Filter(t_subscription.second.m_actions);

		using SubscribeInvoke = OSELib::SOAP::GenericSoapInvoke<OSELib::DPWS::SubscribeTraits>;
		SubscribeInvoke t_subscribeInvoke(t_subscription.second.m_sourceURI, t_grammarProvider);
		auto t_response(t_subscribeInvoke.invoke(t_request, m_SSLContext));

		if (!t_response
			|| !t_response->SubscriptionManager().ReferenceParameters().present()
			|| !t_response->SubscriptionManager().ReferenceParameters().get().Identifier().present()) {
			log_fatal([&] { return "Subscribing failed."; });
			continue;
		} else {
			log_information([] { return "Subscription accomplished"; });
		}

		m_subscriptionIdentifiers.emplace(t_subscription.first, t_response->SubscriptionManager().ReferenceParameters().get().Identifier().get());
	}

	while (Poco::Thread::trySleep(t_sleepQueryGetStatus_ms)) {

		// Query the status via GetStatus
		for (const auto & subscription : m_subscriptions) {

			OSELib::DPWS::GetStatusTraits::Request t_getStatusRequest;

			OSELib::Helper::DurationWrapper t_expireDuration(t_expireString); // Init to default

			GetStatusInvoke t_getStatusInvoke(subscription.second.m_sourceURI, m_subscriptionIdentifiers.at(subscription.first), t_grammarProvider);
			auto t_response(t_getStatusInvoke.invoke(t_getStatusRequest, m_SSLContext));

			// Valid response - Init
			if (t_response != nullptr) {
				t_expireDuration = OSELib::Helper::DurationWrapper(t_response.get()->Expires().get());
				log_debug([&] { return "GetStatus " + m_subscriptionIdentifiers.at(subscription.first) + ": " + t_expireDuration.toString() + "."; });
			}
			else {
				log_fatal([] { return "GetStatus failed."; });
				// Init with 0 Duration - This will trigger a renew
				t_expireDuration = OSELib::Helper::DurationWrapper(std::chrono::seconds(0));
			}
			// FIXME: This might trigger many renews if GetStatus is not supported / anything goes wrong here
			// Renew when under a threshold or duration convert error
			if((!t_expireDuration.toDuration_s().first) || (t_expireDuration.toDuration_s().second < t_renewThreshold) || t_expireDuration.toDuration_s().second == std::chrono::seconds(0))
			{
				log_debug([&] { return "Renewing " + m_subscriptionIdentifiers.at(subscription.first) + " (" + t_expireDuration.toString() + "):..."; });
				OSELib::DPWS::RenewTraits::Request t_request;
				t_request.Expires(t_defaultExpires);
				RenewInvoke t_renewInvoke(subscription.second.m_sourceURI, m_subscriptionIdentifiers.at(subscription.first), t_grammarProvider);
				auto t_response(t_renewInvoke.invoke(t_request, m_SSLContext));

				if (!t_response) {
					log_fatal([] { return "Renew failed."; });
				}
			}
		}
	}

	for (const auto & t_subscription : m_subscriptions) {
		OSELib::DPWS::UnsubscribeTraits::Request t_request;

		UnsubscribeInvoke t_unsubscribeInvoke(t_subscription.second.m_sourceURI, m_subscriptionIdentifiers.at(t_subscription.first), t_grammarProvider);
		auto t_response(t_unsubscribeInvoke.invoke(t_request, m_SSLContext));
	}
}
