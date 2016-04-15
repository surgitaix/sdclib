/*
 * IEventReport.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef OSCP_IEVENTREPORT_H_
#define OSCP_IEVENTREPORT_H_

#include "OSELib/fwd.h"
#include "OSELib/DPWS/IService.h"
#include "OSELib/DPWS/ISubscriptionManager.h"

namespace OSELib {
namespace OSCP {

class IEventReport : public DPWS::IService, public DPWS::ISubscriptionManager {
public:
	virtual ~IEventReport() = default;
};

} /* namespace OSCP */
} /* namespace OSELib */

#endif /* OSCP_IEVENTREPORT_H_ */
