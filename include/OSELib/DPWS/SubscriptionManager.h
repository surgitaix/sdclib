/*
 * SubscriptionManager.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef OSELIB_DPWS_SUBSCRIPTIONMANAGER_H_
#define OSELIB_DPWS_SUBSCRIPTIONMANAGER_H_

#include "OSELib/fwd.h"
#include "OSELib/DPWS/ActiveSubscriptions.h"
#include "OSELib/DPWS/ISubscriptionManager.h"
#include "OSELib/Helper/WithLogger.h"

namespace OSELib {
namespace DPWS {

class SubscriptionManager : public ISubscriptionManager, public WithLogger {
public:
	SubscriptionManager(const std::vector<xml_schema::Uri> & allowedEventActions, bool p_SSL);

	template <class TraitsType>
	void fireEvent(const typename TraitsType::ReportType & report);

	std::unique_ptr<SubscribeTraits::Response> dispatch(const SubscribeTraits::Request & request) override;
	std::unique_ptr<UnsubscribeTraits::Response> dispatch(const UnsubscribeTraits::Request & request, const UnsubscribeTraits::RequestIdentifier & identifier) override;
	std::unique_ptr<RenewTraits::Response> dispatch(const RenewTraits::Request & request, const RenewTraits::RequestIdentifier & identifier) override;

private:
	ActiveSubscriptions _subscriptions;
	const std::vector<xml_schema::Uri> _allowedEventActions;
	std::unique_ptr<HTTP::HTTPSessionManager> _sessionManager;
};

} /* namespace DPWS */
} /* namespace OSELib */

#endif /* OSELIB_DPWS_SUBSCRIPTIONMANAGER_H_ */
