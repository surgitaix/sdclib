/*
 * NormalizedMessageSerializer.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef SOAP_NORMALIZEDMESSAGESERIALIZER_H_
#define SOAP_NORMALIZEDMESSAGESERIALIZER_H_

#include "OSELib/fwd.h"

namespace OSELib {
namespace SOAP {

class NormalizedMessageSerializer {
public:
	class SoapFaultException : public std::exception {
	};

	static std::string serialize(const MESSAGEMODEL::Envelope & message);
};

} /* namespace SOAP */
} /* namespace OSELib */

#endif /* SOAP_NORMALIZEDMESSAGESERIALIZER_H_ */
