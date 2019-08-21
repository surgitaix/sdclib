/*
 * RenewActionCommand.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 */

#ifndef OSELIB_SOAP_RENEWACTIONCOMMAND_H_
#define OSELIB_SOAP_RENEWACTIONCOMMAND_H_

#include "OSELib/DPWS/OperationTraits.h"
#include "OSELib/SOAP/SoapActionCommand.h"

namespace OSELib
{
	namespace SOAP
	{
		class RenewActionCommand : public SoapActionCommand
		{
		protected:
			DPWS::RenewTraits::Dispatcher & m_dispatcher;

		public:
			RenewActionCommand(std::unique_ptr<MESSAGEMODEL::Envelope> p_requestMessage, DPWS::RenewTraits::Dispatcher & p_dispatcher);
			// Special Member Functions
			RenewActionCommand(const RenewActionCommand& p_obj) = default;
			RenewActionCommand(RenewActionCommand&& p_obj) = default;
            RenewActionCommand& operator=(const RenewActionCommand& p_obj) = default;
            RenewActionCommand& operator=(RenewActionCommand&& p_obj) = default;
			virtual ~RenewActionCommand() = default;

		protected:
			std::unique_ptr<MESSAGEMODEL::Envelope> dispatch(const MESSAGEMODEL::Envelope & p_request) override;
		};
	}
}

#endif
