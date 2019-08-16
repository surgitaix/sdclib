/*
 * GetStatusActionCommand.h
 *
 *  Created on: 05.08.2019
 *      Author: baumeister
 */

#ifndef SOAP_GETSTATUSACTIONCOMMAND_H_
#define SOAP_GETSTATUSACTIONCOMMAND_H_

#include "OSELib/fwd.h"
#include "OSELib/DPWS/OperationTraits.h"
#include "OSELib/SOAP/SoapActionCommand.h"

namespace OSELib
{
    namespace SOAP
    {

        class GetStatusActionCommand : public SoapActionCommand
        {
        public:
            GetStatusActionCommand(std::unique_ptr<MESSAGEMODEL::Envelope> requestMessage, DPWS::GetStatusTraits::Dispatcher & dispatcher);
            virtual ~GetStatusActionCommand();

        protected:
            std::unique_ptr<MESSAGEMODEL::Envelope> dispatch(const MESSAGEMODEL::Envelope & request) override;

            DPWS::GetStatusTraits::Dispatcher & _dispatcher;
        };

    }
}

#endif
