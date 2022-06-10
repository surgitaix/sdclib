/*
 * SoapFaultCommand.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 10.06.2022, baumeister
 *
 */

#ifndef OSELIB_SOAP_SOAPFAULTCOMMAND_H_
#define OSELIB_SOAP_SOAPFAULTCOMMAND_H_

#include "OSELib/fwd.h"
#include "OSELib/SOAP/Command.h"

#include "DataModel/NormalizedMessageModel.hxx"

namespace OSELib
{
    namespace SOAP
    {
        class SoapFaultCommand : public Command
        {
        private:
            Poco::Net::HTTPServerResponse &m_httpResponse;

        public:
            SoapFaultCommand(Poco::Net::HTTPServerResponse &);
            virtual ~SoapFaultCommand() = default;

            std::unique_ptr<MESSAGEMODEL::Envelope> Run() override;
        };
    }  // namespace SOAP
}  // namespace OSELib

#endif
