/*
 * UnsubscribeActionCommand.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#ifndef OSELIB_SOAP_UNSUBSCRIBEACTIONCOMMAND_H_
#define OSELIB_SOAP_UNSUBSCRIBEACTIONCOMMAND_H_

#include "OSELib/DPWS/OperationTraits.h"
#include "OSELib/SOAP/GenericSoapActionCommand.h"

namespace OSELib
{
	namespace SOAP
	{
		class UnsubscribeActionCommand : public SoapActionCommand
		{
		protected:
			DPWS::UnsubscribeTraits::Dispatcher & m_dispatcher;

		public:
			UnsubscribeActionCommand(std::unique_ptr<MESSAGEMODEL::Envelope> p_requestMessage, DPWS::UnsubscribeTraits::Dispatcher & p_dispatcher);
			// Special Member Functions
			UnsubscribeActionCommand(const UnsubscribeActionCommand& p_obj) = delete;
			UnsubscribeActionCommand(UnsubscribeActionCommand&& p_obj) = delete;
			UnsubscribeActionCommand& operator=(const UnsubscribeActionCommand& p_obj) = delete;
			UnsubscribeActionCommand& operator=(UnsubscribeActionCommand&& p_obj) = delete;
			virtual ~UnsubscribeActionCommand() = default;

		protected:
			std::unique_ptr<MESSAGEMODEL::Envelope> dispatch(const MESSAGEMODEL::Envelope & p_request) override;
		};
	}
}

#endif
