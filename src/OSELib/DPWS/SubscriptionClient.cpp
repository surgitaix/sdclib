/*
 * SubscriptionClient.cpp
 *
 *  Created on: 14.12.2015
 *      Author: matthias
 */

#include <iostream>

#include "Poco/UUIDGenerator.h"

#include "eventing.hxx"
#include "ws-addressing.hxx"

#include "OSELib/DPWS/SubscriptionClient.h"
#include "OSELib/SOAP/GenericSoapInvoke.h"
#include "OSELib/SDC/DefaultOSCPSchemaGrammarProvider.h"

namespace OSELib {
namespace DPWS {

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
		return std::move(header);
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
		return std::move(header);
	}

private:
	const WS::EVENTING::Identifier _identifier;
};

SubscriptionClient::SubscriptionClient(const std::vector<SubscriptionInformation> & subscriptions) :
	WithLogger(Log::EVENTSINK),
	_runnableAdapter(*this, &SubscriptionClient::run)
{
	for (const auto & item : subscriptions) {
		_subscriptions.emplace(Poco::UUIDGenerator::defaultGenerator().create(), item);
	}
	_thread.start(_runnableAdapter);
}

SubscriptionClient::~SubscriptionClient() {
	_thread.wakeUp();
	_thread.join();
}

void SubscriptionClient::run() {

	// todo clean up and split method
	SDC::DefaultOSCPSchemaGrammarProvider grammarProvider;

	const WS::EVENTING::ExpirationType defaultExpires("PT10S");
	const WS::EVENTING::ExpirationType defaultRenew(defaultExpires);

	CONSTEXPR_MACRO int defaultWaitBeforeRenew (5000);

	for (const auto & subscription : _subscriptions) {
		// get information
		const WS::ADDRESSING::AttributedURIType address(subscription.second._sinkURI.toString());
		WS::ADDRESSING::EndpointReferenceType epr(address);
		WS::ADDRESSING::EndpointReferenceType::ReferenceParametersType referenceParameters;
		referenceParameters.Identifier(WS::EVENTING::Identifier(subscription.first.toString()));
		epr.ReferenceParameters().set(referenceParameters);
		const WS::EVENTING::DeliveryType delivery(epr);


		OSELib::DPWS::SubscribeTraits::Request request(delivery);
		request.Expires(defaultExpires);
		request.Filter(subscription.second._actions);

		using SubscribeInvoke = OSELib::SOAP::GenericSoapInvoke<OSELib::DPWS::SubscribeTraits>;
		SubscribeInvoke subscribeInvoke(subscription.second._sourceURI, grammarProvider);
		auto response(subscribeInvoke.invoke(request));

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
			auto response(renewInvoke.invoke(request));

			if (!response) {
				log_fatal([&] { return "Renew failed."; });
			}
		}
	}

	for (const auto & subscription : _subscriptions) {
		OSELib::DPWS::UnsubscribeTraits::Request request;

		UnsubscribeInvoke unsubscribeInvoke(subscription.second._sourceURI, _subscriptionIdentifiers.at(subscription.first), grammarProvider);
		auto response(unsubscribeInvoke.invoke(request));
	}
}

} /* namespace DPWS */
} /* namespace OSELib */
