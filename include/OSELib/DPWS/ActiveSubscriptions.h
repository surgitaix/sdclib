/*
 * ActiveSubscriptions.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef DPWS_ACTIVESUBSCRIPTIONS_H_
#define DPWS_ACTIVESUBSCRIPTIONS_H_

#include "Poco/Mutex.h"
#include "Poco/Thread.h"
#include "Poco/Timestamp.h"
#include "Poco/RunnableAdapter.h"

#include "eventing.hxx"
#include "ws-addressing.hxx"

#include "OSELib/fwd.h"
#include "OSELib/Helper/WithLogger.h"

namespace OSELib {
namespace DPWS {

class ActiveSubscriptions : public WithLogger {
public:
	ActiveSubscriptions();
	~ActiveSubscriptions();

	struct SubscriptionInformation {
		SubscriptionInformation(
				const WS::ADDRESSING::EndpointReferenceType & notifyTo,
				const Poco::Timestamp & expirationTime,
				const WS::EVENTING::FilterType & actions) :
			_notifyTo(notifyTo),
			_expirationTime(expirationTime),
			_actions(actions)
		{
		}
		const WS::ADDRESSING::EndpointReferenceType _notifyTo;
		Poco::Timestamp _expirationTime;
		const WS::EVENTING::FilterType _actions;
	};

	void printSubscriptions() const;

	void unsubscribe(const WS::EVENTING::Identifier & identifier);
	std::string subscribe(const SubscriptionInformation & subscription);
	bool renew(const WS::EVENTING::Identifier & identifier, const Poco::Timestamp & timestamp);

	std::map<xml_schema::Uri, WS::ADDRESSING::EndpointReferenceType> getSubscriptions(const std::string & action);

private:

	void houseKeeping();
	void run();

	mutable Poco::Mutex _mutex;

	Poco::Thread _thread;
	Poco::RunnableAdapter<ActiveSubscriptions> _runnableAdapter;
	std::map<xml_schema::Uri, SubscriptionInformation> _subscriptions;
};

} /* namespace DPWS */
} /* namespace OSELib */

#endif /* DPWS_ACTIVESUBSCRIPTIONS_H_ */
