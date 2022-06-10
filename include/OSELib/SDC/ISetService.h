/*
 * ISetService.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#ifndef OSELIB_SDC_ISETSERVICE_H_
#define OSELIB_SDC_ISETSERVICE_H_

#include "OSELib/fwd.h"
#include "OSELib/DPWS/IService.h"
#include "OSELib/SDC/OperationTraits.h"
#include "OSELib/DPWS/ISubscriptionManager.h"

namespace OSELib
{
	namespace SDC
	{
		class ISetService : public DPWS::IService, public DPWS::ISubscriptionManager
		{
		public:
			ISetService() = default;
			ISetService(const ISetService& p_obj) = delete;
			ISetService(ISetService&& p_obj) = delete;
			ISetService& operator=(const ISetService& p_obj) = delete;
			ISetService& operator=(ISetService&& p_obj) = delete;
			virtual ~ISetService() = default;

			using ISubscriptionManager::dispatch;

			virtual std::unique_ptr<SetValueTraits::Response> dispatch(const SetValueTraits::Request & request) = 0;
			virtual std::unique_ptr<SetStringTraits::Response> dispatch(const SetStringTraits::Request & request) = 0;
			virtual std::unique_ptr<ActivateTraits::Response> dispatch(const ActivateTraits::Request & request) = 0;
			virtual std::unique_ptr<SetAlertStateTraits::Response> dispatch(const SetAlertStateTraits::Request & request) = 0;
			virtual std::unique_ptr<SetComponentStateTraits::Response> dispatch(const SetComponentStateTraits::Request & request) = 0;

		};
	}
}

#endif
