/*
 * GenericSoapInvoke.h
 *
 *  Created on: 11.12.2015
 *      Author: matthias
 */

#ifndef OSELIB_SOAP_GENERICSOAPINVOKE_H_
#define OSELIB_SOAP_GENERICSOAPINVOKE_H_

#include "OSELib/fwd.h"
#include "OSELib/SOAP/NormalizedMessageAdapter.h"
#include "OSELib/SOAP/SoapInvoke.h"

namespace OSELib {
namespace SOAP {

template<class TraitsType>
class GenericSoapInvoke : public SoapInvoke {
public:
	GenericSoapInvoke(const Poco::URI & requestURI, OSELib::Helper::XercesGrammarPoolProvider & grammarProvider) :
		SoapInvoke(requestURI, grammarProvider)
	{
	}
	virtual ~GenericSoapInvoke() = default;

	std::unique_ptr<MESSAGEMODEL::Header> createHeader() override {
		auto header(SoapInvoke::createHeader());
		header->Action().set(MESSAGEMODEL::Envelope::HeaderType::ActionType(TraitsType::RequestAction()));
		return header;
	}

	using SoapInvoke::invoke;

	virtual std::unique_ptr<typename TraitsType::Response> invoke(const typename TraitsType::Request & request, Poco::Net::Context::Ptr p_context) {
		std::unique_ptr<MESSAGEMODEL::Envelope> invokeMessage(createMessage());

		OSELib::SOAP::NormalizedMessageAdapter<typename TraitsType::Request> adapter;
		adapter.set(*invokeMessage, std::unique_ptr<typename TraitsType::Request>(new typename TraitsType::Request(request)));

        // QND - Distinguish between SSL and plain SOAP invoke by Poco::Net::Context::Ptr.
        std::unique_ptr<MESSAGEMODEL::Envelope> t_responseMessage = nullptr;
        // SSL
        if(!p_context.isNull()) {
            t_responseMessage = SoapInvoke::invoke(std::move(invokeMessage), p_context);
        }
        else {
            t_responseMessage = SoapInvoke::invoke(std::move(invokeMessage));
        }

		if (!t_responseMessage) {
			// todo throw somehting
			log_error([&] {return "Soap invoke failed: Empty response message.";});
			return nullptr;
		}

		const auto soapAction(t_responseMessage->Header().Action().get());
		if (soapAction == TraitsType::ResponseAction()) {

			OSELib::SOAP::NormalizedMessageAdapter<typename TraitsType::Response> adapter;
			if (!adapter.present(*t_responseMessage)) {
				return nullptr;
			}

			std::unique_ptr<typename TraitsType::Response> response(new typename TraitsType::Response(adapter.get(*t_responseMessage)));
			return response;
		} else {
			// throw something?
		}

		return nullptr;
	}

};

} /* namespace SOAP */
} /* namespace OSELib */

#endif /* OSELIB_SOAP_GENERICSOAPINVOKE_H_ */
