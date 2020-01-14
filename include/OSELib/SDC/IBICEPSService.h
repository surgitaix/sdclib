/*
 * IBICEPSService.h
 *
 *  Created on: 24.09.2019, baumeister
 *
 */

#ifndef OSELIB_SDC_IBICEPSSERVICE_H_
#define OSELIB_SDC_IBICEPSSERVICE_H_

#include "OSELib/SDC/IEventReport.h"
#include "OSELib/SDC/IContextService.h"
#include "OSELib/SDC/IWaveformService.h"

namespace OSELib
{
	namespace SDC
	{
		class IBICEPSService : public IEventReport, public IContextService, public IWaveformService
		{
		public:
			// Special Member Functions
			IBICEPSService() = default;
			IBICEPSService(const IBICEPSService& p_obj) = default;
			IBICEPSService(IBICEPSService&& p_obj) = default;
			IBICEPSService& operator=(const IBICEPSService& p_obj) = default;
			IBICEPSService& operator=(IBICEPSService&& p_obj) = default;
			virtual ~IBICEPSService() = default;
		};
	}
}

#endif
