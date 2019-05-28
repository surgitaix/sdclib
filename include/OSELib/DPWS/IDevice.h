/*
 * IDevice.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef OSELIB_DPWS_IDEVICE_H_
#define OSELIB_DPWS_IDEVICE_H_

#include "OSELib/fwd.h"
#include "OSELib/DPWS/OperationTraits.h"

namespace OSELib {
namespace DPWS {

class IDevice {
public:
	virtual ~IDevice() = default;

	virtual std::string getBaseUri() const = 0;
	virtual GetTraits::Response getMetadata(const std::string & serverAddress) = 0;
	virtual std::unique_ptr<ProbeTraits::Response> dispatch(const ProbeTraits::Request & request) = 0;
};

} /* namespace DPWS */
} /* namespace OSELib */

#endif /* OSELIB_DPWS_IDEVICE_H_ */
