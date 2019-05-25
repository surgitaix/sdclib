/*
 * SubscriptionClient.h
 *
 *  Created on: 14.12.2015
 *      Author: matthias
 */

#ifndef OSELIB_DPWS_SUBSCRIPTIONCLIENT_H_
#define OSELIB_DPWS_SUBSCRIPTIONCLIENT_H_

#include <atomic>
#include <tuple>

#include "Poco/Mutex.h"
#include "Poco/RunnableAdapter.h"
#include "Poco/Thread.h"
#include "Poco/UUID.h"
#include "Poco/URI.h"

#include "OSELib/fwd.h"
#include "OSELib/Helper/WithLogger.h"

#include "SDCLib/Data/SDC/SDCConsumerAdapter.h"

namespace OSELib {
namespace DPWS {

class SubscriptionClient : public WithLogger {
public:
	struct SubscriptionInformation {
		SubscriptionInformation(
				const Poco::URI & sinkURI,
				const Poco::URI & sourceURI,
				const WS::EVENTING::FilterType & actions, 
				SDCLib::Data::SDC::SDCConsumerAdapter& consumer) :
					_sinkURI(sinkURI),
					_sourceURI(sourceURI),
					_actions(actions),
					_consumerAdapter(consumer)
		{
		}

		SubscriptionInformation(const SubscriptionInformation & source) :
			_sinkURI(source._sinkURI),
			_sourceURI(source._sourceURI),
			_actions(source._actions),
			_consumerAdapter(source._consumerAdapter)
		{
		}

		const Poco::URI _sinkURI;
		const Poco::URI _sourceURI;
		const WS::EVENTING::FilterType _actions;
		SDCLib::Data::SDC::SDCConsumerAdapter& _consumerAdapter;	//needed for subscription lost handling
	};

	SubscriptionClient(const std::vector<SubscriptionInformation> & subscriptions);
	virtual ~SubscriptionClient();

private:
	void run();
	mutable Poco::Mutex _mutex;

	Poco::Thread _thread;
	Poco::RunnableAdapter<SubscriptionClient> _runnableAdapter;
	std::map<Poco::UUID, WS::EVENTING::Identifier> _subscriptionIdentifiers;
	std::map<Poco::UUID, SubscriptionInformation> _subscriptions;
};

} /* namespace DPWS */
} /* namespace OSELib */

#endif /* OSELIB_DPWS_SUBSCRIPTIONCLIENT_H_ */
