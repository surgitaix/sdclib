/*
 * IGetService.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef OSELIB_SDC_IGETSERVICE_H_
#define OSELIB_SDC_IGETSERVICE_H_

#include "OSELib/fwd.h"
#include "OSELib/DPWS/IService.h"
#include "OSELib/SDC/OperationTraits.h"

namespace OSELib {
namespace SDC {

class IGetService : public DPWS::IService {
public:
	virtual ~IGetService() = default;

	virtual std::unique_ptr<GetMDDescriptionTraits::Response> dispatch(const GetMDDescriptionTraits::Request & request) = 0;
	virtual std::unique_ptr<GetMDIBTraits::Response> dispatch(const GetMDIBTraits::Request & request) = 0;
	virtual std::unique_ptr<GetMdStateTraits::Response> dispatch(const GetMdStateTraits::Request & request) = 0;
};

} /* namespace SDC */
} /* namespace OSELib */

#endif /* OSELIB_SDC_IGETSERVICE_H_ */
