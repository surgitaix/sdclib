/*
 * GenericSoapInvoke.h
 *
 *  Created on: 11.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#ifndef OSELIB_SOAP_GENERICSOAPINVOKE_H_
#define OSELIB_SOAP_GENERICSOAPINVOKE_H_

#include "OSELib/SOAP/NormalizedMessageAdapter.h"
#include "OSELib/SOAP/SoapInvoke.h"

namespace OSELib
{
	namespace SOAP
	{
		template<class TraitsType>
		class GenericSoapInvoke : public SoapInvoke
		{
		public:
			GenericSoapInvoke(const Poco::URI & p_requestURI, OSELib::Helper::XercesGrammarPoolProvider & p_grammarProvider)
			: SoapInvoke(p_requestURI, p_grammarProvider)
			{ }
			// Special Member Functions
			GenericSoapInvoke(const GenericSoapInvoke& p_obj) = default;
			GenericSoapInvoke(GenericSoapInvoke&& p_obj) = default;
			GenericSoapInvoke& operator=(const GenericSoapInvoke& p_obj) = default;
			GenericSoapInvoke& operator=(GenericSoapInvoke&& p_obj) = default;
			virtual ~GenericSoapInvoke() = default;

			std::unique_ptr<MESSAGEMODEL::Header> createHeader() override {
				auto t_header(SoapInvoke::createHeader());
				t_header->getAction().set(MESSAGEMODEL::Envelope::HeaderType::ActionType(TraitsType::RequestAction()));
				return t_header;
			}

			using SoapInvoke::invoke;

			virtual std::unique_ptr<typename TraitsType::Response> invoke(const typename TraitsType::Request & p_request, Poco::Net::Context::Ptr p_context)
			{
				std::unique_ptr<MESSAGEMODEL::Envelope> t_invokeMessage(createMessage());

				OSELib::SOAP::NormalizedMessageAdapter<typename TraitsType::Request> t_adapterRequest;
				t_adapterRequest.set(*t_invokeMessage, std::unique_ptr<typename TraitsType::Request>(new typename TraitsType::Request(p_request)));

				// QND - Distinguish between SSL and plain SOAP invoke by Poco::Net::Context::Ptr.
				std::unique_ptr<MESSAGEMODEL::Envelope> t_responseMessage = nullptr;
				// SSL
				if(!p_context.isNull()) {
					t_responseMessage = SoapInvoke::invoke(std::move(t_invokeMessage), p_context);
				}
				else {
					t_responseMessage = SoapInvoke::invoke(std::move(t_invokeMessage));
				}

				if (!t_responseMessage) {
					// todo throw something
					log_error([&] {return "Soap invoke failed: Empty response message.";});
					return nullptr;
				}

				const auto soapAction(t_responseMessage->getHeader().getAction().get());
				if (soapAction == TraitsType::ResponseAction()) {

					OSELib::SOAP::NormalizedMessageAdapter<typename TraitsType::Response> t_adapterResponse;
					if (!t_adapterResponse.present(*t_responseMessage)) {
						return nullptr;
					}

					std::unique_ptr<typename TraitsType::Response> t_response(new typename TraitsType::Response(t_adapterResponse.get(*t_responseMessage)));
					return t_response;
				} else {
					// throw something? // FIXME
				}
				return nullptr;
			}
		};
	}
}

#endif
