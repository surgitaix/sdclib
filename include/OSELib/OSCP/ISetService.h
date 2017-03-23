/*
 * ISetService.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef OSCP_ISETSERVICE_H_
#define OSCP_ISETSERVICE_H_

#include "OSELib/fwd.h"
#include "OSELib/DPWS/IService.h"
#include "OSELib/OSCP/OperationTraits.h"

namespace OSELib {
namespace OSCP {

class ISetService : public DPWS::IService {
public:
	virtual ~ISetService() = default;

	virtual std::unique_ptr<ActivateTraits::Response> dispatch(const ActivateTraits::Request & request) = 0;
	virtual std::unique_ptr<SetAlertStateTraits::Response> dispatch(const SetAlertStateTraits::Request & request) = 0;
	virtual std::unique_ptr<SetStringTraits::Response> dispatch(const SetStringTraits::Request & request) = 0;
	virtual std::unique_ptr<SetValueTraits::Response> dispatch(const SetValueTraits::Request & request) = 0;
};

} /* namespace OSCP */
} /* namespace OSELib */

#endif /* OSCP_ISETSERVICE_H_ */
