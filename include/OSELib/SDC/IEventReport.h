/*
 * IEventReport.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef OSELIB_SDC_IEVENTREPORT_H_
#define OSELIB_SDC_IEVENTREPORT_H_

#include "OSELib/fwd.h"
#include "OSELib/DPWS/IService.h"
#include "OSELib/DPWS/ISubscriptionManager.h"

namespace OSELib {
namespace SDC {

class IEventReport : public DPWS::IService, public DPWS::ISubscriptionManager {
public:
	virtual ~IEventReport() = default;
};

} /* namespace SDC */
} /* namespace OSELib */

#endif /* OSELIB_SDC_IEVENTREPORT_H_ */
