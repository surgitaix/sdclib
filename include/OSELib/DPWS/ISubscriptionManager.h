/*
 * ISubscriptionManager.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef DPWS_ISUBSCRIPTIONMANAGER_H_
#define DPWS_ISUBSCRIPTIONMANAGER_H_

#include "OSELib/fwd.h"
#include "OSELib/DPWS/OperationTraits.h"

namespace OSELib {
namespace DPWS {

class ISubscriptionManager {
public:
	virtual ~ISubscriptionManager() = default;

	virtual std::unique_ptr<SubscribeTraits::Response> dispatch(const SubscribeTraits::Request & request) = 0;
	virtual std::unique_ptr<UnsubscribeTraits::Response> dispatch(const UnsubscribeTraits::Request & request, const UnsubscribeTraits::RequestIdentifier & identifier) = 0;
	virtual std::unique_ptr<RenewTraits::Response> dispatch(const RenewTraits::Request & request, const RenewTraits::RequestIdentifier & identifier) = 0;
};

} /* namespace DPWS */
} /* namespace OSELib */

#endif /* DPWS_ISUBSCRIPTIONMANAGER_H_ */
