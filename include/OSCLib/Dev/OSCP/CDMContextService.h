/*
 * CDMPhiService.h
 *
 *  Created on: 26.05.2015
 *      Author: roehser
 */

#ifndef DEV_OSCP_CDMCONTEXTSERVICE_H_
#define DEV_OSCP_CDMCONTEXTSERVICE_H_

#include "OSCLib/Dev/Service.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"

namespace OSCLib {
namespace Dev {
namespace OSCP {

class CDMContextService : public Service {
public:
	CDMContextService(OSCLib::Data::OSCP::OSCPProvider & provider);
	virtual ~CDMContextService();
};

} /* namespace OSCP */
} /* namespace Dev */
} /* namespace OSCLib */

#endif /* DEV_OSCP_CDMCONTEXTSERVICE_H_ */
