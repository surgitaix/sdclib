/*
 * IContextService.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 24.09.2019, baumeister
 *
 */

#ifndef OSELIB_SDC_ICONTEXTSERVICE_H_
#define OSELIB_SDC_ICONTEXTSERVICE_H_

#include "OSELib/fwd.h"
#include "OSELib/DPWS/IService.h"
#include "OSELib/DPWS/ISubscriptionManager.h"
#include "OSELib/SDC/OperationTraits.h"

namespace OSELib
{
	namespace SDC
	{
		class IContextService : public virtual DPWS::IService, public virtual DPWS::ISubscriptionManager
		{
		public:
			// Special Member Functions
			IContextService() = default;
			IContextService(const IContextService& p_obj) = delete;
			IContextService(IContextService&& p_obj) = delete;
			IContextService& operator=(const IContextService& p_obj) = delete;
			IContextService& operator=(IContextService&& p_obj) = delete;
			virtual ~IContextService() = default;

			using DPWS::ISubscriptionManager::dispatch;
			virtual std::unique_ptr<GetContextStatesTraits::Response> dispatch(const GetContextStatesTraits::Request & request) = 0;
			virtual std::unique_ptr<SetContextStateTraits::Response> dispatch(const SetContextStateTraits::Request & request) = 0;
		};
	}
}

#endif
