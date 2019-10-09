/*
 * IBICEPSServiceEventSink.h
 *
 *  Created on: 26.09.2019, baumeister
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
		class IBICEPSServiceEventSink : public IDescriptionEventServiceEventSink, public IStateEventServiceEventSink, public IContextServiceEventSink
		{
		public:
			// Special Member Functions
			IBICEPSServiceEventSink() = default;
			IBICEPSServiceEventSink(const IBICEPSServiceEventSink& p_obj) = default;
			IBICEPSServiceEventSink(IBICEPSServiceEventSink&& p_obj) = default;
			IBICEPSServiceEventSink& operator=(const IBICEPSServiceEventSink& p_obj) = default;
			IBICEPSServiceEventSink& operator=(IBICEPSServiceEventSink&& p_obj) = default;
			virtual ~IBICEPSServiceEventSink() = default;
		};
	}
}

#endif
