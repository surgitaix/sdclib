/*
 * SubscriptionClient.h
 *
 *  Created on: 14.12.2015
 *      Author: matthias
 */

#ifndef OSELIB_DPWS_SUBSCRIPTIONCLIENT_H_
#define OSELIB_DPWS_SUBSCRIPTIONCLIENT_H_

#include <Poco/RunnableAdapter.h>
#include <Poco/Thread.h>
#include <Poco/URI.h>
#include <Poco/Net/Context.h>

#include "OSELib/fwd.h"
#include "OSELib/Helper/WithLogger.h"

#include "eventing.hxx"

namespace OSELib {
namespace DPWS {

class SubscriptionClient : public OSELib::Helper::WithLogger {
public:
	struct SubscriptionInformation {
		SubscriptionInformation(
				const Poco::URI & sinkURI,
				const Poco::URI & sourceURI,
				const WS::EVENTING::FilterType & actions) :
					_sinkURI(sinkURI),
					_sourceURI(sourceURI),
					_actions(actions)
		{
		}

		SubscriptionInformation(const SubscriptionInformation & source) :
			_sinkURI(source._sinkURI),
			_sourceURI(source._sourceURI),
			_actions(source._actions)
		{
		}

		const Poco::URI _sinkURI;
		const Poco::URI _sourceURI;
		const WS::EVENTING::FilterType _actions;
	};

	SubscriptionClient(const std::vector<SubscriptionInformation> & subscriptions, Poco::Net::Context::Ptr p_context);
	virtual ~SubscriptionClient();

private:
	void run();

	Poco::Thread _thread;
	Poco::RunnableAdapter<SubscriptionClient> _runnableAdapter;
	std::map<std::string, WS::EVENTING::Identifier> _subscriptionIdentifiers;
	std::map<std::string, SubscriptionInformation> _subscriptions;
    Poco::Net::Context::Ptr m_SSLContext = nullptr; // != nullptr -> SSL Active!
};

} /* namespace DPWS */
} /* namespace OSELib */

#endif /* OSELIB_DPWS_SUBSCRIPTIONCLIENT_H_ */
