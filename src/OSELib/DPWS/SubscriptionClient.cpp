/*
 * SubscriptionClient.cpp
 *
 *  Created on: 14.12.2015, matthias
 */

#include "OSELib/DPWS/SubscriptionClient.h"


#include "ws-addressing.hxx"

#include "OSELib/SOAP/GenericSoapInvoke.h"
#include "OSELib/SDC/DefaultSDCSchemaGrammarProvider.h"

#include "SDCLib/SDCInstance.h"


using namespace OSELib;
using namespace OSELib::DPWS;

class RenewInvoke : public OSELib::SOAP::GenericSoapInvoke<OSELib::DPWS::RenewTraits> {
public:
	RenewInvoke(const Poco::URI & requestURI,
			const WS::EVENTING::Identifier & identifier,
			OSELib::Helper::XercesGrammarPoolProvider & grammarProvider) :
			OSELib::SOAP::GenericSoapInvoke<OSELib::DPWS::RenewTraits>(requestURI, grammarProvider),
			_identifier(identifier)
		{
		}

	virtual std::unique_ptr<MESSAGEMODEL::Header> createHeader() override {
		auto header(OSELib::SOAP::GenericSoapInvoke<OSELib::DPWS::RenewTraits>::createHeader());
		header->Identifier(_identifier);
		return header;
	}

private:
	const WS::EVENTING::Identifier _identifier;
};

class UnsubscribeInvoke : public OSELib::SOAP::GenericSoapInvoke<OSELib::DPWS::UnsubscribeTraits> {
public:
	UnsubscribeInvoke(const Poco::URI & requestURI,
			const WS::EVENTING::Identifier & identifier,
			OSELib::Helper::XercesGrammarPoolProvider & grammarProvider) :
			OSELib::SOAP::GenericSoapInvoke<OSELib::DPWS::UnsubscribeTraits>(requestURI, grammarProvider),
			_identifier(identifier)
		{
		}

	virtual std::unique_ptr<MESSAGEMODEL::Header> createHeader() override {
		auto header(OSELib::SOAP::GenericSoapInvoke<OSELib::DPWS::UnsubscribeTraits>::createHeader());
		header->Identifier(_identifier);
		return header;
	}

private:
	const WS::EVENTING::Identifier _identifier;
};

SubscriptionClient::SubscriptionClient(const std::vector<SubscriptionInformation> & subscriptions, Poco::Net::Context::Ptr p_context) :
	WithLogger(Log::EVENTSINK),
	_runnableAdapter(*this, &SubscriptionClient::run),
    m_SSLContext(p_context) // Can be nullptr!
{
	for (const auto & item : subscriptions) {
		_subscriptions.emplace(SDCLib::SDCInstance::calcUUID(), item);
	}
	_thread.start(_runnableAdapter);
}

SubscriptionClient::~SubscriptionClient() {
	_thread.wakeUp();
	_thread.join();
}

void SubscriptionClient::run() {

	// todo clean up and split method
	SDC::DefaultSDCSchemaGrammarProvider grammarProvider;

	const WS::EVENTING::ExpirationType defaultExpires("PT10S");
	const WS::EVENTING::ExpirationType defaultRenew(defaultExpires);

	int defaultWaitBeforeRenew (5000);

	for (const auto & subscription : _subscriptions) {
		// get information
		const WS::ADDRESSING::AttributedURIType address(subscription.second._sinkURI.toString());
		WS::ADDRESSING::EndpointReferenceType epr(address);
		WS::ADDRESSING::EndpointReferenceType::ReferenceParametersType referenceParameters;
		referenceParameters.Identifier(WS::EVENTING::Identifier(subscription.first));
		epr.ReferenceParameters().set(referenceParameters);
		const WS::EVENTING::DeliveryType delivery(epr);


		OSELib::DPWS::SubscribeTraits::Request request(delivery);
		request.Expires(defaultExpires);
		request.Filter(subscription.second._actions);

		using SubscribeInvoke = OSELib::SOAP::GenericSoapInvoke<OSELib::DPWS::SubscribeTraits>;
		SubscribeInvoke subscribeInvoke(subscription.second._sourceURI, grammarProvider);
		auto response(subscribeInvoke.invoke(request, m_SSLContext));

		if (!response
			|| !response->SubscriptionManager().ReferenceParameters().present()
			|| !response->SubscriptionManager().ReferenceParameters().get().Identifier().present()) {
			log_fatal([&] { return "Subscribing failed."; });
		} else {
			log_information([&] { return "Subscription accomplished"; });
		}

		_subscriptionIdentifiers.emplace(subscription.first, response->SubscriptionManager().ReferenceParameters().get().Identifier().get());
	}

	while (Poco::Thread::trySleep(defaultWaitBeforeRenew)) {
		log_debug([&] { return "Renewing ..."; });

		for (const auto & subscription : _subscriptions) {
			OSELib::DPWS::RenewTraits::Request request;
			request.Expires(defaultRenew);

			RenewInvoke renewInvoke(subscription.second._sourceURI, _subscriptionIdentifiers.at(subscription.first), grammarProvider);
			auto response(renewInvoke.invoke(request, m_SSLContext));

			if (!response) {
				log_fatal([&] { return "Renew failed."; });
			}
		}
	}

	for (const auto & subscription : _subscriptions) {
		OSELib::DPWS::UnsubscribeTraits::Request request;

		UnsubscribeInvoke unsubscribeInvoke(subscription.second._sourceURI, _subscriptionIdentifiers.at(subscription.first), grammarProvider);
		auto response(unsubscribeInvoke.invoke(request, m_SSLContext));
	}
}
