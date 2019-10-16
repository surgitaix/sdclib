/*
 * GenericSoapActionCommand.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#ifndef OSELIB_SOAP_GENERICSOAPACTIONCOMMAND_H_
#define OSELIB_SOAP_GENERICSOAPACTIONCOMMAND_H_


#include "OSELib/SOAP/SoapActionCommand.h"
#include "OSELib/SOAP/NormalizedMessageAdapter.h"

namespace OSELib
{
	namespace SOAP
	{
		template<class TraitsType>
		class GenericSoapActionCommand : public SoapActionCommand
		{
		protected:

			typename TraitsType::Dispatcher & m_dispatcher;

		public:
			GenericSoapActionCommand(std::unique_ptr<MESSAGEMODEL::Envelope> p_requestMessage, typename TraitsType::Dispatcher & p_dispatcher)
			: SoapActionCommand(std::move(p_requestMessage))
			, m_dispatcher(p_dispatcher)
			{ }
			// Special Member Functions
			GenericSoapActionCommand(const GenericSoapActionCommand& p_obj) = default;
			GenericSoapActionCommand(GenericSoapActionCommand&& p_obj) = default;
			GenericSoapActionCommand& operator=(const GenericSoapActionCommand& p_obj) = default;
			GenericSoapActionCommand& operator=(GenericSoapActionCommand&& p_obj) = default;
			virtual ~GenericSoapActionCommand() = default;

		protected:

			std::unique_ptr<MESSAGEMODEL::Envelope> checkDispatchPreconditions(std::unique_ptr<MESSAGEMODEL::Envelope> p_request) override
			{
				NormalizedMessageAdapter<typename TraitsType::Request> t_requestAdapter;
				if (!t_requestAdapter.present(*p_request)) {
					throw SoapActionCommand::MissingRequestBody("Request body missing for " + TraitsType::RequestAction());
				}
				return p_request;
			}

			std::unique_ptr<MESSAGEMODEL::Envelope> dispatch(const MESSAGEMODEL::Envelope & request) override
			{
				NormalizedMessageAdapter<typename TraitsType::Request> t_requestAdapter;
				const typename TraitsType::Request & requestBody(t_requestAdapter.get(request));
				std::unique_ptr<typename TraitsType::Response> t_responseBody(dispatchDelegate(requestBody));
				if (!t_responseBody) {
					throw DispatchingFailed("Internal error. Dispatching failed for " + TraitsType::RequestAction());
				}

				std::unique_ptr<MESSAGEMODEL::Envelope> t_responseMessage(createResponseMessageFromRequestMessage(request));
				if(nullptr == t_responseMessage) {
					return nullptr;
				}
				t_responseMessage->Header().Action().set(WS::ADDRESSING::AttributedURIType(TraitsType::ResponseAction()));

				insertResponseBodyIntoMessage(*t_responseMessage, std::move(t_responseBody));

				return t_responseMessage;
			}

			virtual std::unique_ptr<typename TraitsType::Response> dispatchDelegate(const typename TraitsType::Request & p_requestBody) {
				return TraitsType::dispatch(m_dispatcher, p_requestBody);
			}

			virtual void insertResponseBodyIntoMessage(MESSAGEMODEL::Envelope & p_responseMessage, std::unique_ptr< typename TraitsType::Response > p_body) {
				NormalizedMessageAdapter<typename TraitsType::Response> t_responseAdapter;
				t_responseAdapter.set(p_responseMessage, std::move(p_body));
			}
		};

	}
}

#endif
