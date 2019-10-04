/*
 * SubscriptionClient.cpp
 *
 *  Created on: 14.12.2015, matthias
 *  Mofiried on: 12.08.2019, baumeister
 */

#include "OSELib/DPWS/SubscriptionClient.h"


#include "ws-addressing.hxx"

#include "OSELib/SOAP/GenericSoapInvoke.h"
#include "OSELib/SDC/DefaultSDCSchemaGrammarProvider.h"
#include "OSELib/Helper/DurationWrapper.h"


#include "SDCLib/SDCInstance.h"

const std::size_t RENEW_THRESHOLD = 60;

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

class GetStatusInvoke : public OSELib::SOAP::GenericSoapInvoke<OSELib::DPWS::GetStatusTraits> {
public:
	GetStatusInvoke(const Poco::URI & requestURI,
			const WS::EVENTING::Identifier & identifier,
			OSELib::Helper::XercesGrammarPoolProvider & grammarProvider) :
			OSELib::SOAP::GenericSoapInvoke<OSELib::DPWS::GetStatusTraits>(requestURI, grammarProvider),
			_identifier(identifier)
		{
		}

	virtual std::unique_ptr<MESSAGEMODEL::Header> createHeader() override {
		auto header(OSELib::SOAP::GenericSoapInvoke<OSELib::DPWS::GetStatusTraits>::createHeader());
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

	auto t_renewThreshold = std::chrono::seconds(RENEW_THRESHOLD);

	auto t_expireString = "PT" + std::to_string(t_renewThreshold.count() * 2) + "S"; // Note: Double the factor
	const WS::EVENTING::ExpirationType t_defaultExpires(t_expireString);

	std::size_t t_sleepQueryGetStatus_ms = t_renewThreshold.count() * 1000 / 8;

	for (const auto & subscription : _subscriptions) {
		// get information
		const WS::ADDRESSING::AttributedURIType address(subscription.second._sinkURI.toString());
		WS::ADDRESSING::EndpointReferenceType epr(address);
		WS::ADDRESSING::EndpointReferenceType::ReferenceParametersType referenceParameters;
		referenceParameters.Identifier(WS::EVENTING::Identifier(subscription.first));
		epr.ReferenceParameters().set(referenceParameters);
		const WS::EVENTING::DeliveryType delivery(epr);


		OSELib::DPWS::SubscribeTraits::Request request(delivery);
		request.Expires(t_defaultExpires);
		request.Filter(subscription.second._actions);

		using SubscribeInvoke = OSELib::SOAP::GenericSoapInvoke<OSELib::DPWS::SubscribeTraits>;
		SubscribeInvoke subscribeInvoke(subscription.second._sourceURI, grammarProvider);
		auto response(subscribeInvoke.invoke(request, m_SSLContext));

		if (!response
			|| !response->SubscriptionManager().ReferenceParameters().present()
			|| !response->SubscriptionManager().ReferenceParameters().get().Identifier().present()) {
			log_fatal([&] { return "Subscribing failed."; });
			_subscriptionIdentifiers.erase(subscription.first);
		} else {
			log_information([] { return "Subscription accomplished"; });
			_subscriptionIdentifiers.emplace(subscription.first, response->SubscriptionManager().ReferenceParameters().get().Identifier().get());
		}
	}

	while (Poco::Thread::trySleep(t_sleepQueryGetStatus_ms)) {

		// Query the status via GetStatus
		for (const auto & subscription : _subscriptions) {
			if (_subscriptionIdentifiers.find(subscription.first) == _subscriptionIdentifiers.end())
				continue;

			OSELib::DPWS::GetStatusTraits::Request t_getStatusRequest;
			GetStatusInvoke t_getStatusInvoke(subscription.second._sourceURI, _subscriptionIdentifiers.at(subscription.first), grammarProvider);
			auto t_response(t_getStatusInvoke.invoke(t_getStatusRequest, m_SSLContext));
			bool needRenew = false;
			if (t_response)
			{
				auto t_expireDuration = OSELib::Helper::DurationWrapper(t_response.get()->Expires().get());
				log_debug([&] { return "GetStatus " + _subscriptionIdentifiers.at(subscription.first) + ": " + t_expireDuration.toString() + "."; });

				needRenew = ((!t_expireDuration.toDuration_s().first) || (t_expireDuration.toDuration_s().second < t_renewThreshold));
			}
			else
			{
				log_fatal([] { return "GetStatus failed."; });
				needRenew = true; //we try to renew (emergency renewing...)
				//subscription.second._consumerAdapter.onSubscriptionLost();	//ToDo Do we need some further clean up here?
			}

			// Renew when under a threshold or duration convert error
			if (needRenew)
			{
				log_debug([&] { return "Renewing " + _subscriptionIdentifiers.at(subscription.first) + "..."; });
				OSELib::DPWS::RenewTraits::Request request;
				request.Expires(t_defaultExpires);
				RenewInvoke renewInvoke(subscription.second._sourceURI, _subscriptionIdentifiers.at(subscription.first), grammarProvider);
				auto response(renewInvoke.invoke(request, m_SSLContext));

				if (!response) {
					log_fatal([&] { return "Renew " + _subscriptionIdentifiers.at(subscription.first) + " failed."; });
					_subscriptionIdentifiers.erase(subscription.first);
					subscription.second._consumerAdapter.onSubscriptionLost();	//ToDo Do we need some further clean up here?
					return;
				}
			}
		}
	}

	for (const auto & subscription : _subscriptions) {
		if (_subscriptionIdentifiers.find(subscription.first) == _subscriptionIdentifiers.end())
			continue;

		OSELib::DPWS::UnsubscribeTraits::Request request;

		UnsubscribeInvoke unsubscribeInvoke(subscription.second._sourceURI, _subscriptionIdentifiers.at(subscription.first), grammarProvider);
		auto response(unsubscribeInvoke.invoke(request, m_SSLContext));
	}
}
