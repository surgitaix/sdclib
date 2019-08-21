/*
 * SubscribeActionCommand.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 */

#ifndef OSELIB_SOAP_SUBSCRIBEACTIONCOMMAND_H_
#define OSELIB_SOAP_SUBSCRIBEACTIONCOMMAND_H_

#include "OSELib/DPWS/OperationTraits.h"
#include "OSELib/SOAP/GenericSoapActionCommand.h"

namespace OSELib
{
	namespace SOAP
	{
		class SubscribeActionCommand : public GenericSoapActionCommand<DPWS::SubscribeTraits>
		{
		private:
			const WS::ADDRESSING::AttributedURIType m_subscriptionManagerAddress;
		public:
			SubscribeActionCommand(std::unique_ptr<MESSAGEMODEL::Envelope> p_requestMessage,
					DPWS::SubscribeTraits::Dispatcher & p_dispatcher,
					const std::string & p_subscriptionManagerAddress);
			// Special Member Functions
			SubscribeActionCommand(const SubscribeActionCommand& p_obj) = delete;
			SubscribeActionCommand(SubscribeActionCommand&& p_obj) = delete;
			SubscribeActionCommand& operator=(const SubscribeActionCommand& p_obj) = delete;
			SubscribeActionCommand& operator=(SubscribeActionCommand&& p_obj) = delete;
            virtual ~SubscribeActionCommand() = default;

			std::unique_ptr<MESSAGEMODEL::Envelope> postprocessResponse(std::unique_ptr<MESSAGEMODEL::Envelope> p_response) override;
		};
	}
}

#endif
