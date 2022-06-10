/*
 * IBICEPSService.h
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
            IBICEPSService() = default;
            virtual ~IBICEPSService() = default;
        };
    }  // namespace SDC
}  // namespace OSELib

#endif
