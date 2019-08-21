/*
 * SoapFaultCommand.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 */

#ifndef OSELIB_SOAP_SOAPFAULTCOMMAND_H_
#define OSELIB_SOAP_SOAPFAULTCOMMAND_H_

#include "OSELib/fwd.h"
#include "OSELib/SOAP/Command.h"

namespace OSELib
{
	namespace SOAP
	{
		class SoapFaultCommand : public Command
		{
		private:
			Poco::Net::HTTPServerResponse & m_httpResponse;

		public:
			SoapFaultCommand(Poco::Net::HTTPServerResponse & p_httpResponse);
			// Special Member Functions
			SoapFaultCommand(const SoapFaultCommand& p_obj) = default;
			SoapFaultCommand(SoapFaultCommand&& p_obj) = default;
			SoapFaultCommand& operator=(const SoapFaultCommand& p_obj) = default;
			SoapFaultCommand& operator=(SoapFaultCommand&& p_obj) = default;
			virtual ~SoapFaultCommand() = default;

			std::unique_ptr<MESSAGEMODEL::Envelope> Run() override;
		};
	}
}

#endif
