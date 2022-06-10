/*
 * IBICEPSServiceEventSink.h
 *
 *  Created on: 10.06.2022, baumeister
 *
 */

#ifndef OSELIB_SDC_IBICEPSSERVICEEVENTSINK_H_
#define OSELIB_SDC_IBICEPSSERVICEEVENTSINK_H_

#include "OSELib/SDC/IDescriptionEventServiceEventSink.h"
#include "OSELib/SDC/IStateEventServiceEventSink.h"
#include "OSELib/SDC/IContextServiceEventSink.h"

namespace OSELib
{
    namespace SDC
    {
        class IBICEPSServiceEventSink : public IDescriptionEventServiceEventSink,
                                        public IStateEventServiceEventSink,
                                        public IContextServiceEventSink
        {
        public:
            IBICEPSServiceEventSink() = default;
            virtual ~IBICEPSServiceEventSink() = default;
        };
    }  // namespace SDC
}  // namespace OSELib

#endif
