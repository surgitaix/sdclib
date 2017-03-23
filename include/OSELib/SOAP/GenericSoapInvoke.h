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

	virtual std::unique_ptr<MESSAGEMODEL::Header> createHeader() override {
		auto header(SoapInvoke::createHeader());
		using ActionType = MESSAGEMODEL::Envelope::HeaderType::ActionType;
		header->Action().set(ActionType(TraitsType::RequestAction()));
		return std::move(header);
	}

	using SoapInvoke::invoke;

	virtual std::unique_ptr<typename TraitsType::Response> invoke(const typename TraitsType::Request & request) {
		std::unique_ptr<MESSAGEMODEL::Envelope> invokeMessage(createMessage());

		OSELib::SOAP::NormalizedMessageAdapter<typename TraitsType::Request> adapter;
		adapter.set(*invokeMessage, std::unique_ptr<typename TraitsType::Request>(new typename TraitsType::Request(request)));

		auto responseMessage(SoapInvoke::invoke(std::move(invokeMessage)));

		if (!responseMessage) {
			// todo throw somehting
			return nullptr;
		}

		const auto soapAction(responseMessage->Header().Action().get());
		if (soapAction == TraitsType::ResponseAction()) {

			OSELib::SOAP::NormalizedMessageAdapter<typename TraitsType::Response> adapter;
			if (!adapter.present(*responseMessage)) {
				return nullptr;
			}

			std::unique_ptr<typename TraitsType::Response> response(new typename TraitsType::Response(adapter.get(*responseMessage)));
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
