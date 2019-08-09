/*
 * ActiveSubscriptions.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 01.08.2019, baumeister
 */

#ifndef DPWS_ACTIVESUBSCRIPTIONS_H_
#define DPWS_ACTIVESUBSCRIPTIONS_H_

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
		class ActiveSubscriptions : public WithLogger
		{
		public:

			struct SubscriptionInformation
			{
				explicit SubscriptionInformation(
						WS::ADDRESSING::EndpointReferenceType notifyTo,
						std::chrono::system_clock::time_point expirationTime,
						WS::EVENTING::FilterType actions) :
					m_notifyTo(notifyTo),
					m_expirationTime(expirationTime),
					m_actions(actions)
				{ }
				const WS::ADDRESSING::EndpointReferenceType m_notifyTo;
				std::chrono::system_clock::time_point m_expirationTime;
				const WS::EVENTING::FilterType m_actions;
			};

			using GetStatusResult = std::pair <bool, SubscriptionInformation>;

		private:

			mutable std::mutex m_mutex;

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

			void unsubscribe(const WS::EVENTING::Identifier & identifier);
			std::string subscribe(const SubscriptionInformation & subscription);
			bool renew(const WS::EVENTING::Identifier & identifier, std::chrono::system_clock::time_point p_timestamp);

			GetStatusResult getStatus(const WS::EVENTING::Identifier & identifier) const;

			std::map<xml_schema::Uri, WS::ADDRESSING::EndpointReferenceType> getSubscriptions(const std::string & p_action);

		private:

			void houseKeeping();
			void run();
		};

	} /* namespace DPWS */
} /* namespace OSELib */

#endif /* DPWS_ACTIVESUBSCRIPTIONS_H_ */
