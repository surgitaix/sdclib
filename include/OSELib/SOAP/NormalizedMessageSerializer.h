/*
 * NormalizedMessageSerializer.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef SOAP_NORMALIZEDMESSAGESERIALIZER_H_
#define SOAP_NORMALIZEDMESSAGESERIALIZER_H_

#include "OSELib/fwd.h"
#include "OSELib/TCP/TCPClientEventHandler.h"

namespace OSELib {
namespace SOAP {

class NormalizedMessageSerializer {
public:
	class SoapFaultException : public std::exception {
	};

	static std::string serialize(const MESSAGEMODEL::Envelope & message);

private:
	static std::string manipulateMessage(const std::string& originalMessage);
	static std::mutex _mtx;

};

} /* namespace SOAP */
} /* namespace OSELib */

#endif /* SOAP_NORMALIZEDMESSAGESERIALIZER_H_ */
