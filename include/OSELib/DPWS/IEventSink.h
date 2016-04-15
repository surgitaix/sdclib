/*
 * IService.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef DPWS_IEVENTSINK_H_
#define DPWS_IEVENTSINK_H_

#include "OSELib/fwd.h"
#include "OSELib/DPWS/OperationTraits.h"

namespace OSELib {
namespace DPWS {

class IEventSink {
public:
	virtual ~IEventSink() = default;

	virtual std::string getBaseUri() const = 0;
};

} /* namespace DPWS */
} /* namespace OSELib */

#endif /* DPWS_IEVENTSINK_H_ */
