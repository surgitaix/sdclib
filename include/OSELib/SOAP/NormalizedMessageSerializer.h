/*
 * NormalizedMessageSerializer.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#ifndef OSELIB_SOAP_NORMALIZEDMESSAGESERIALIZER_H_
#define OSELIB_SOAP_NORMALIZEDMESSAGESERIALIZER_H_

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
}
}

#endif
