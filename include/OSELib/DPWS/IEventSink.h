/*
 * IService.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef OSELIB_DPWS_IEVENTSINK_H_
#define OSELIB_DPWS_IEVENTSINK_H_

#include "OSELib/fwd.h"

namespace OSELib {
namespace DPWS {

class IEventSink {
public:
	virtual ~IEventSink() = default;

	virtual std::string getBaseUri() const = 0;
};

} /* namespace DPWS */
} /* namespace OSELib */

#endif /* OSELIB_DPWS_IEVENTSINK_H_ */
