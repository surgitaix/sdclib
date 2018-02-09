/*
 * IContextService.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef OSCP_ICONTEXTSERVICE_H_
#define OSCP_ICONTEXTSERVICE_H_

#include "OSELib/fwd.h"
#include "OSELib/DPWS/IService.h"
#include "OSELib/DPWS/ISubscriptionManager.h"
#include "OSELib/OSCP/OperationTraits.h"

namespace OSELib {
namespace SDC {

class IContextService : public DPWS::IService, public DPWS::ISubscriptionManager {
public:
	virtual ~IContextService() = default;

	using DPWS::ISubscriptionManager::dispatch;
	virtual std::unique_ptr<GetContextStatesTraits::Response> dispatch(const GetContextStatesTraits::Request & request) = 0;
	virtual std::unique_ptr<SetContextStateTraits::Response> dispatch(const SetContextStateTraits::Request & request) = 0;
};

} /* namespace SDC */
} /* namespace OSELib */

#endif /* OSCP_ICONTEXTSERVICE_H_ */
