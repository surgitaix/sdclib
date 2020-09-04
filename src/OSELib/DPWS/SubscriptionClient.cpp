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
const double RENEW_FACTOR = 2.0;        // Multiplied with the RENEW_THRESHOLD = EXPIRATION_TIME for the subscription

using namespace OSELib;
using namespace OSELib::DPWS;

class RenewInvoke : public OSELib::SOAP::GenericSoapInvoke<OSELib::DPWS::RenewTraits>
{
private:
    const WS::EVENTING::Identifier m_identifier;

public:
    RenewInvoke(const Poco::URI& p_requestURI,
                const WS::EVENTING::Identifier& p_identifier,
                OSELib::Helper::XercesGrammarPoolProvider& p_grammarProvider)
        : OSELib::SOAP::GenericSoapInvoke<OSELib::DPWS::RenewTraits>(p_requestURI, p_grammarProvider)
        , m_identifier(p_identifier)
    {
    }

    virtual std::unique_ptr<MESSAGEMODEL::Header> createHeader() override
    {
        auto header{OSELib::SOAP::GenericSoapInvoke<OSELib::DPWS::RenewTraits>::createHeader()};
        header->setIdentifier(m_identifier);
        return header;
    }
};

class GetStatusInvoke : public OSELib::SOAP::GenericSoapInvoke<OSELib::DPWS::GetStatusTraits>
{
private:
    const WS::EVENTING::Identifier m_identifier;

public:
    GetStatusInvoke(const Poco::URI& p_requestURI,
                    const WS::EVENTING::Identifier& p_identifier,
                    OSELib::Helper::XercesGrammarPoolProvider& p_grammarProvider)
        : OSELib::SOAP::GenericSoapInvoke<OSELib::DPWS::GetStatusTraits>(p_requestURI, p_grammarProvider)
        , m_identifier(p_identifier)
    {
    }

    virtual std::unique_ptr<MESSAGEMODEL::Header> createHeader() override
    {
        auto header(OSELib::SOAP::GenericSoapInvoke<OSELib::DPWS::GetStatusTraits>::createHeader());
        header->setIdentifier(m_identifier);
        return header;
    }
};

class UnsubscribeInvoke : public OSELib::SOAP::GenericSoapInvoke<OSELib::DPWS::UnsubscribeTraits>
{
private:
    const WS::EVENTING::Identifier m_identifier;

public:
    UnsubscribeInvoke(const Poco::URI& p_requestURI,
                      const WS::EVENTING::Identifier& p_identifier,
                      OSELib::Helper::XercesGrammarPoolProvider& p_grammarProvider)
        : OSELib::SOAP::GenericSoapInvoke<OSELib::DPWS::UnsubscribeTraits>(p_requestURI, p_grammarProvider)
        , m_identifier(p_identifier)
    {
    }

    virtual std::unique_ptr<MESSAGEMODEL::Header> createHeader() override
    {
        auto header(OSELib::SOAP::GenericSoapInvoke<OSELib::DPWS::UnsubscribeTraits>::createHeader());
        header->setIdentifier(m_identifier);
        return header;
    }
};

SubscriptionClient::SubscriptionClient(const std::vector<SubscriptionInformation>& p_initialSubscriptions,
                                       Poco::Net::Context::Ptr p_context)
    : OSELib::Helper::WithLogger(Log::EVENTSINK)
    , m_runnableAdapter(*this, &SubscriptionClient::run)
    , m_SSLContext(p_context)
{
    for(const auto& subscriptionInfo : p_initialSubscriptions)
    {
        m_subscriptions.emplace(SDCLib::SDCInstance::calcUUID(), subscriptionInfo);
    }
    m_thread.start(m_runnableAdapter);
}

SubscriptionClient::~SubscriptionClient()
{
    // TODO: Cleanup / Restructure along with run() !
    m_thread.wakeUp();
    m_thread.join();
}

void SubscriptionClient::run()
{
    using namespace WS::ADDRESSING;
    using namespace WS::EVENTING;
    using namespace OSELib;

    // todo clean up and split method
    SDC::DefaultSDCSchemaGrammarProvider defaultSchemaGrammarProvider;

    auto renewThreshold = std::chrono::seconds{RENEW_THRESHOLD};
    auto expireString = "PT" + std::to_string(renewThreshold.count() * RENEW_FACTOR) + "S"; // Note: Factor on the renew threshold
    const ExpirationType defaultExpireTime{expireString};

    subscribeAll(defaultExpireTime, defaultSchemaGrammarProvider);


    std::size_t sleepQueryGetStatus_ms = 2000; // TODO: MAGIC NUMBER
    while(Poco::Thread::trySleep(sleepQueryGetStatus_ms))
    {
        std::vector<std::string> recentlyExpiredSubscriptions;

        // Query the status via GetStatus
        for(const auto& subscription : m_subscriptions)
        {
            Helper::DurationWrapper expireDuration{expireString};
            GetStatusInvoke getStatusInvoke(subscription.second.getSourceURI(),
                                            subscription.second.getIdentifier(),
                                            defaultSchemaGrammarProvider);

            DPWS::GetStatusTraits::Request getStatusRequest;
            auto getStatusResponse{getStatusInvoke.invoke(getStatusRequest, m_SSLContext)};

            if(getStatusResponse && getStatusResponse.get()->getExpires().present())
            {
                expireDuration = Helper::DurationWrapper{getStatusResponse.get()->getExpires().get()};
                log_debug([&] { return "GetStatus " + subscription.second.getIdentifier() + ": " + expireDuration.toString() + "."; });
            }
            else
            {
                log_fatal([] { return "GetStatus failed."; });
                // Init with 0 Duration - This will trigger a renew
                expireDuration = OSELib::Helper::DurationWrapper{std::chrono::seconds{0}};
                // FIXME: This might trigger many renews if GetStatus is not supported / anything goes wrong here
            }

            // Renew when under a threshold or duration convert error
            if((!expireDuration.toDuration_s().first) || (expireDuration.toDuration_s().second < renewThreshold)
               || expireDuration.toDuration_s().second == std::chrono::seconds{0})
            {
                log_debug([&] { return "Renewing " + subscription.second.getIdentifier() + " (" + expireDuration.toString() + "):..."; });

                RenewInvoke renewInvoke{subscription.second.getSourceURI(),
                                        subscription.second.getIdentifier(),
                                        defaultSchemaGrammarProvider};

                DPWS::RenewTraits::Request renewRequest;
                renewRequest.setExpires(defaultExpireTime);

                auto renewResponse{renewInvoke.invoke(renewRequest, m_SSLContext)};
                if(!renewResponse)
                {
                    log_fatal([] { return "Renew failed."; });
                    recentlyExpiredSubscriptions.push_back(subscription.first);
                }
            }
        }

        for(auto& expiredSubscription : recentlyExpiredSubscriptions)
        {
            auto foundIterator = m_subscriptions.find(expiredSubscription);
            if(m_subscriptions.end() != foundIterator)
            {
                m_subscriptions.erase(foundIterator);
                invokeUnsubscribe(foundIterator->second, defaultSchemaGrammarProvider);
            }
        }
    }

    unsubscribeAll(defaultSchemaGrammarProvider);
}

void SubscriptionClient::subscribeAll(const WS::EVENTING::ExpirationType p_defaultExpireTime,
                                      SDC::DefaultSDCSchemaGrammarProvider& p_defaultSchemaGrammarProvider)
{
    for(auto& subscription : m_subscriptions)
    {
        auto subscriptionResult = invokeSubscribe(subscription.second, p_defaultExpireTime, p_defaultSchemaGrammarProvider);
        if(subscriptionResult.first)
        {
            subscription.second.setIdentifier(subscriptionResult.second);
        }
        else
        {
            throw std::runtime_error("SubscriptionClient::run subscription failed for " + subscription.first);
        }
    }
}
void SubscriptionClient::unsubscribeAll(SDC::DefaultSDCSchemaGrammarProvider& p_defaultSchemaGrammarProvider)
{
    for(auto& subscription : m_subscriptions)
    {
        invokeUnsubscribe(subscription.second, p_defaultSchemaGrammarProvider);
    }
    m_subscriptions.clear();
}

std::pair<bool, WS::EVENTING::Identifier>
    SubscriptionClient::invokeSubscribe(SubscriptionInformation p_subscription,
                                        const WS::EVENTING::ExpirationType p_defaultExpireTime,
                                        SDC::DefaultSDCSchemaGrammarProvider& p_defaultSchemaGrammarProvider)
{
    using namespace WS::ADDRESSING;
    using namespace WS::EVENTING;
    using namespace OSELib;

    EndpointReferenceType endpointRef{AttributedURIType{p_subscription.getSinkURI().toString()}};
    EndpointReferenceType::ReferenceParametersType referenceParameters;
    referenceParameters.setIdentifier(p_subscription.getIdentifier());
    endpointRef.getReferenceParameters().set(referenceParameters);

    DPWS::SubscribeTraits::Request subscribeRequest{DeliveryType{endpointRef}};
    subscribeRequest.setExpires(p_defaultExpireTime);
    subscribeRequest.setFilter(p_subscription.getActions());

    SOAP::GenericSoapInvoke<DPWS::SubscribeTraits> subscribeInvoke{p_subscription.getSourceURI(), p_defaultSchemaGrammarProvider};
    auto subscribeResponse{subscribeInvoke.invoke(subscribeRequest, m_SSLContext)};

    if(!subscribeResponse || !subscribeResponse->getSubscriptionManager().getReferenceParameters().present()
       || !subscribeResponse->getSubscriptionManager().getReferenceParameters().get().getIdentifier().present())
    {
        log_fatal([] { return "Subscribing failed."; });
        return {false, {""}};
    }

    log_debug([] { return "Subscription accomplished"; });
    return {true, subscribeResponse->getSubscriptionManager().getReferenceParameters()->getIdentifier().get()};
}

bool SubscriptionClient::invokeUnsubscribe(SubscriptionInformation p_subscription,
                                           SDC::DefaultSDCSchemaGrammarProvider& p_defaultSchemaGrammarProvider)
{
    UnsubscribeInvoke unsubscribeInvoke(p_subscription.getSourceURI(), p_subscription.getIdentifier(), p_defaultSchemaGrammarProvider);

    DPWS::UnsubscribeTraits::Request unsubscribeRequest;
    auto unsubscribeResponse(unsubscribeInvoke.invoke(unsubscribeRequest, m_SSLContext));

    return (nullptr != unsubscribeResponse);
}
