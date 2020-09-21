/*
 * SubscriptionClient.h
 *
 *  Created on: 14.12.2015, matthias
 *  Modified on: 21.09.2020, baumeister
 *
 */

#ifndef OSELIB_DPWS_SUBSCRIPTIONCLIENT_H_
#define OSELIB_DPWS_SUBSCRIPTIONCLIENT_H_

#include "OSELib/fwd.h"
#include "OSELib/Helper/WithLogger.h"

#include <Poco/RunnableAdapter.h>
#include <Poco/Thread.h>
#include <Poco/URI.h>
#include <Poco/Net/Context.h>

#include "DataModel/eventing.hxx"

namespace OSELib
{
    namespace DPWS
    {
        class SubscriptionClient : public OSELib::Helper::WithLogger
        {
        public:
            class SubscriptionInformation
            {
            public:
                SubscriptionInformation(const Poco::URI& p_sinkURI, const Poco::URI& p_sourceURI, const WS::EVENTING::FilterType& p_actions)
                    : m_sinkURI(p_sinkURI)
                    , m_sourceURI(p_sourceURI)
                    , m_actions(p_actions)
                {
                }

                SubscriptionInformation(const SubscriptionInformation& p_source)
                    : m_sinkURI(p_source.m_sinkURI)
                    , m_sourceURI(p_source.m_sourceURI)
                    , m_actions(p_source.m_actions)
                {
                }


                Poco::URI getSinkURI() const
                {
                    return m_sinkURI;
                }
                Poco::URI getSourceURI() const
                {
                    return m_sourceURI;
                }
                WS::EVENTING::FilterType getActions() const
                {
                    return m_actions;
                }

                void setIdentifier(WS::EVENTING::Identifier p_newIdentifier)
                {
                    m_identifier = p_newIdentifier;
                }
                WS::EVENTING::Identifier getIdentifier() const
                {
                    return m_identifier;
                }


            private:
                const Poco::URI m_sinkURI;
                const Poco::URI m_sourceURI;
                const WS::EVENTING::FilterType m_actions;

                WS::EVENTING::Identifier m_identifier{""};

                std::lconv* m_lconv{std::localeconv()};
            };

        private:
            std::map<std::string, SubscriptionInformation> m_subscriptions;

            Poco::RunnableAdapter<SubscriptionClient> m_runnableAdapter;
            Poco::Thread m_thread;

            Poco::Net::Context::Ptr m_SSLContext{nullptr};  // != nullptr -> SSL Active!

        public:
            SubscriptionClient(const std::vector<SubscriptionInformation>&, Poco::Net::Context::Ptr);
            SubscriptionClient(const SubscriptionClient&) = delete;
            SubscriptionClient(SubscriptionClient&&) = delete;
            SubscriptionClient& operator=(const SubscriptionClient&) = delete;
            SubscriptionClient& operator=(SubscriptionClient&&) = delete;
            virtual ~SubscriptionClient();

        private:
            void run();

            std::pair<bool, WS::EVENTING::Identifier>
                invokeSubscribe(SubscriptionInformation, const WS::EVENTING::ExpirationType, SDC::DefaultSDCSchemaGrammarProvider&);
            bool invokeUnsubscribe(SubscriptionInformation, SDC::DefaultSDCSchemaGrammarProvider&);

            void subscribeAll(const WS::EVENTING::ExpirationType, SDC::DefaultSDCSchemaGrammarProvider&);
            void unsubscribeAll(SDC::DefaultSDCSchemaGrammarProvider&);
        };
    }  // namespace DPWS
}  // namespace OSELib

#endif
