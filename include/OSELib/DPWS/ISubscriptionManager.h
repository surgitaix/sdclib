/*
 * ISubscriptionManager.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 01.09.2020, baumeister
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
            ISubscriptionManager(const ISubscriptionManager&) = delete;
            ISubscriptionManager(ISubscriptionManager&&) = delete;
            ISubscriptionManager& operator=(const ISubscriptionManager&) = delete;
            ISubscriptionManager& operator=(ISubscriptionManager&&) = delete;
            virtual ~ISubscriptionManager() = default;

            virtual std::unique_ptr<SubscribeTraits::Response> dispatch(const SubscribeTraits::Request&) = 0;
            virtual std::unique_ptr<RenewTraits::Response> dispatch(const RenewTraits::Request&, const RenewTraits::RequestIdentifier&) = 0;
            virtual std::unique_ptr<GetStatusTraits::Response> dispatch(const GetStatusTraits::Request&,
                                                                        const GetStatusTraits::RequestIdentifier&) = 0;
            virtual std::unique_ptr<UnsubscribeTraits::Response> dispatch(const UnsubscribeTraits::Request&,
                                                                          const UnsubscribeTraits::RequestIdentifier&) = 0;
        };
    }  // namespace DPWS
}  // namespace OSELib

#endif
