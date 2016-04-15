/*
 * IService.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef DPWS_ISERVICE_H_
#define DPWS_ISERVICE_H_

#include "OSELib/fwd.h"
#include "OSELib/DPWS/OperationTraits.h"

namespace OSELib {
namespace DPWS {

class IService {
public:
	virtual ~IService() = default;

	virtual std::string getBaseUri() const = 0;
	virtual std::string getWSDL() = 0;
	virtual GetMetadataTraits::Response getMetadata(const std::string & serverAddress) = 0;
};

} /* namespace DPWS */
} /* namespace OSELib */

#endif /* DPWS_ISERVICE_H_ */
