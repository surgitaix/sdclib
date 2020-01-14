/*
 * GetStatusActionCommand.h
 *
 *  Created on: 05.08.2019
 *      Author: baumeister
 */

#ifndef OSELIB_SOAP_GETSTATUSACTIONCOMMAND_H_
#define OSELIB_SOAP_GETSTATUSACTIONCOMMAND_H_

#include "OSELib/fwd.h"
#include "OSELib/DPWS/OperationTraits.h"
#include "OSELib/SOAP/SoapActionCommand.h"

namespace OSELib
{
    namespace SOAP
    {
        class GetStatusActionCommand : public SoapActionCommand
        {
        protected:
        	DPWS::GetStatusTraits::Dispatcher & m_dispatcher;

        public:
            GetStatusActionCommand(std::unique_ptr<MESSAGEMODEL::Envelope> p_requestMessage, DPWS::GetStatusTraits::Dispatcher & p_dispatcher);
            // Special Member Functions
            GetStatusActionCommand(const GetStatusActionCommand& p_obj) = default;
            GetStatusActionCommand(GetStatusActionCommand&& p_obj) = default;
            GetStatusActionCommand& operator=(const GetStatusActionCommand& p_obj) = default;
            GetStatusActionCommand& operator=(GetStatusActionCommand&& p_obj) = default;
            virtual ~GetStatusActionCommand() = default;

        protected:
            std::unique_ptr<MESSAGEMODEL::Envelope> dispatch(const MESSAGEMODEL::Envelope & p_request) override;

        };
    }
}

#endif
