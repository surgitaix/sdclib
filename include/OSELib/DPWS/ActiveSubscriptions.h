/*
 * ActiveSubscriptions.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 22.08.2019, baumeister
 *
 */

#ifndef OSELIB_DPWS_ACTIVESUBSCRIPTIONS_H_
#define OSELIB_DPWS_ACTIVESUBSCRIPTIONS_H_

#include <mutex>
#include <chrono>

#include <Poco/Thread.h>
#include <Poco/RunnableAdapter.h>

#include "eventing.hxx"
#include "ws-addressing.hxx"

#include "OSELib/fwd.h"
#include "OSELib/Helper/WithLogger.h"

namespace OSELib
{
	namespace DPWS
	{
		class ActiveSubscriptions : public Helper::WithLogger
		{
		public:

			struct SubscriptionInformation
			{
				explicit SubscriptionInformation(
						WS::ADDRESSING::EndpointReferenceType p_notifyTo,
						std::chrono::system_clock::time_point p_expirationTime,
						WS::EVENTING::FilterType p_actions) :
					m_notifyTo(p_notifyTo),
					m_expirationTime(p_expirationTime),
					m_actions(p_actions)
				{ }
				const WS::ADDRESSING::EndpointReferenceType m_notifyTo;
				std::chrono::system_clock::time_point m_expirationTime;
				const WS::EVENTING::FilterType m_actions;
			};

			using GetStatusResult = std::pair <bool, SubscriptionInformation>;

		private:

			mutable std::mutex m_mutex;
			std::mutex m_mutex_houseKeeping;

			Poco::RunnableAdapter<ActiveSubscriptions> m_runnableAdapter;
			std::map<xml_schema::Uri, SubscriptionInformation> ml_subscriptions;
			Poco::Thread m_thread;

		public:
			ActiveSubscriptions();
			// Special Member Functions
			ActiveSubscriptions(const ActiveSubscriptions& p_obj) = delete;
			ActiveSubscriptions(ActiveSubscriptions&& p_obj) = delete;
			ActiveSubscriptions& operator=(const ActiveSubscriptions& p_obj) = delete;
			ActiveSubscriptions& operator=(ActiveSubscriptions&& p_obj) = delete;
			~ActiveSubscriptions();

			void printSubscriptions() const;

			void unsubscribe(const WS::EVENTING::Identifier & p_identifier);
			std::string subscribe(const SubscriptionInformation & p_subscription);
			bool renew(const WS::EVENTING::Identifier & p_identifier, std::chrono::system_clock::time_point p_timestamp);

			GetStatusResult getStatus(const WS::EVENTING::Identifier & p_identifier) const;

			std::map<xml_schema::Uri, WS::ADDRESSING::EndpointReferenceType> getSubscriptions(const std::string & p_action);

		private:

			void houseKeeping();
			void run();
		};

	}
}

#endif
