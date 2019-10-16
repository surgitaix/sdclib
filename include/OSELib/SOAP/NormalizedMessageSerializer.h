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

namespace OSELib
{
	namespace SOAP
	{
		class NormalizedMessageSerializer
		{
		public:
			class SoapFaultException : public std::exception {
			};

			static std::string serialize(const MESSAGEMODEL::Envelope & p_message);
		};
	}
}

#endif
