/*
 * IGetService.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#ifndef OSELIB_SDC_IGETSERVICE_H_
#define OSELIB_SDC_IGETSERVICE_H_

#include "OSELib/DPWS/IService.h"
#include "OSELib/SDC/OperationTraits.h"

namespace OSELib
{
	namespace SDC
	{
		class IGetService : public DPWS::IService
		{
		public:
			// Special Member Functions
			IGetService() = default;
			IGetService(const IGetService& p_obj) = default;
			IGetService(IGetService&& p_obj) = default;
			IGetService& operator=(const IGetService& p_obj) = default;
			IGetService& operator=(IGetService&& p_obj) = default;
			virtual ~IGetService() = default;

			virtual std::unique_ptr<GetMDDescriptionTraits::Response> dispatch(const GetMDDescriptionTraits::Request & request) = 0;
			virtual std::unique_ptr<GetMDIBTraits::Response> dispatch(const GetMDIBTraits::Request & request) = 0;
			virtual std::unique_ptr<GetMdStateTraits::Response> dispatch(const GetMdStateTraits::Request & request) = 0;
		};
	}
}

#endif
