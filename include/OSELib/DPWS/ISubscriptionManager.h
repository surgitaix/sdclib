/*
 * ISubscriptionManager.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 23.08.2019, baumeister
 *
 */

#ifndef OSELIB_DPWS_ISUBSCRIPTIONMANAGER_H_
#define OSELIB_DPWS_ISUBSCRIPTIONMANAGER_H_

#include "OSELib/fwd.h"
#include "OSELib/DPWS/OperationTraits.h"

namespace OSELib
{
	namespace DPWS
	{
		class ISubscriptionManager
		{
		public:
			// Special Member Functions
			ISubscriptionManager() = default;
			ISubscriptionManager(const ISubscriptionManager& p_obj) = default;
			ISubscriptionManager(ISubscriptionManager&& p_obj) = default;
			ISubscriptionManager& operator=(const ISubscriptionManager& p_obj) = default;
			ISubscriptionManager& operator=(ISubscriptionManager&& p_obj) = default;
			virtual ~ISubscriptionManager() = default;

			virtual std::unique_ptr<SubscribeTraits::Response> dispatch(const SubscribeTraits::Request & p_request) = 0;
			virtual std::unique_ptr<UnsubscribeTraits::Response> dispatch(const UnsubscribeTraits::Request & p_request, const UnsubscribeTraits::RequestIdentifier & p_identifier) = 0;
			virtual std::unique_ptr<RenewTraits::Response> dispatch(const RenewTraits::Request & p_request, const RenewTraits::RequestIdentifier & p_identifier) = 0;
			virtual std::unique_ptr<GetStatusTraits::Response> dispatch(const GetStatusTraits::Request & p_request, const GetStatusTraits::RequestIdentifier & p_identifier) = 0;
		};
	}
}

#endif
