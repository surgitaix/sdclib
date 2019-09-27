/*
 * IEventReport.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 26.09.2019, baumeister
 *
 */

#ifndef OSELIB_SDC_IEVENTREPORT_H_
#define OSELIB_SDC_IEVENTREPORT_H_

#include "OSELib/DPWS/IService.h"
#include "OSELib/DPWS/ISubscriptionManager.h"

namespace OSELib
{
	namespace SDC
	{
		class IEventReport : public virtual DPWS::IService, public virtual DPWS::ISubscriptionManager
		{
		public:
			// Special Member Functions
			IEventReport() = default;
			IEventReport(const IEventReport& p_obj) = delete;
			IEventReport(IEventReport&& p_obj) = delete;
			IEventReport& operator=(const IEventReport& p_obj) = delete;
			IEventReport& operator=(IEventReport&& p_obj) = delete;
			virtual ~IEventReport() = default;
		};
	}
}

#endif
