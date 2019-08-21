/*
 * IEventReport.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
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
		class IEventReport : public DPWS::IService, public DPWS::ISubscriptionManager
		{
		public:
			// Special Member Functions
			IEventReport() = default;
			IEventReport(const IEventReport& p_obj) = default;
			IEventReport(IEventReport&& p_obj) = default;
			IEventReport& operator=(const IEventReport& p_obj) = default;
			IEventReport& operator=(IEventReport&& p_obj) = default;
			virtual ~IEventReport() = default;
		};
	}
}

#endif
