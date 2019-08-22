/*
 * SubscriptionClient.h
 *
 *  Created on: 14.12.2015, matthias
 *  Modified on: 22.08.2019, baumeister
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

#include "eventing.hxx"

namespace OSELib
{
	namespace DPWS
	{
		class SubscriptionClient : public OSELib::Helper::WithLogger
		{
		public:

			struct SubscriptionInformation
			{
				SubscriptionInformation(const Poco::URI & p_sinkURI, const Poco::URI & p_sourceURI, const WS::EVENTING::FilterType & p_actions)
				: m_sinkURI(p_sinkURI)
				, m_sourceURI(p_sourceURI)
				, m_actions(p_actions)
				{ }

				SubscriptionInformation(const SubscriptionInformation & p_source)
				: m_sinkURI(p_source.m_sinkURI)
				, m_sourceURI(p_source.m_sourceURI)
				, m_actions(p_source.m_actions)
				{ }

				const Poco::URI m_sinkURI;
				const Poco::URI m_sourceURI;
				const WS::EVENTING::FilterType m_actions;
			};

		private:
			Poco::Thread m_thread;
			Poco::RunnableAdapter<SubscriptionClient> m_runnableAdapter;
			std::map<std::string, WS::EVENTING::Identifier> m_subscriptionIdentifiers;
			std::map<std::string, SubscriptionInformation> m_subscriptions;
			Poco::Net::Context::Ptr m_SSLContext = nullptr; // != nullptr -> SSL Active!

		public:

			SubscriptionClient(const std::vector<SubscriptionInformation> & p_subscriptions, Poco::Net::Context::Ptr p_context);
			// Special Member Functions
			SubscriptionClient(const SubscriptionClient& p_obj) = delete;
			SubscriptionClient(SubscriptionClient&& p_obj) = delete;
			SubscriptionClient& operator=(const SubscriptionClient& p_obj) = delete;
			SubscriptionClient& operator=(SubscriptionClient&& p_obj) = delete;
			virtual ~SubscriptionClient();

		private:

			void run();
		};
	}
}

#endif
