/*
 * GenericSoapActionCommand.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef SOAP_GENERICSOAPACTIONCOMMAND_H_
#define SOAP_GENERICSOAPACTIONCOMMAND_H_

#include "OSELib/fwd.h"
#include "OSELib/SOAP/NormalizedMessageAdapter.h"
#include "OSELib/SOAP/SoapActionCommand.h"

namespace OSELib {
namespace SOAP {

template<class TraitsType>
class GenericSoapActionCommand : public SoapActionCommand {
public:
	GenericSoapActionCommand(std::unique_ptr<MESSAGEMODEL::Envelope> requestMessage, typename TraitsType::Dispatcher & dispatcher) :
		SoapActionCommand(std::move(requestMessage)),
		_dispatcher(dispatcher)
	{
	}

	virtual ~GenericSoapActionCommand() = default;

protected:
	virtual std::unique_ptr<MESSAGEMODEL::Envelope> checkDispatchPreconditions(std::unique_ptr<MESSAGEMODEL::Envelope> request) override {
		NormalizedMessageAdapter<typename TraitsType::Request> requestAdapter;
		if (!requestAdapter.present(*request)) {
			throw SoapActionCommand::MissingRequestBody("Request body missing for " + TraitsType::RequestAction());
		}
		return std::move(request);
	}

	virtual std::unique_ptr<MESSAGEMODEL::Envelope> dispatch(const MESSAGEMODEL::Envelope & request) override {

		NormalizedMessageAdapter<typename TraitsType::Request> requestAdapter;
		const typename TraitsType::Request & requestBody(requestAdapter.get(request));
		std::unique_ptr<typename TraitsType::Response> responseBody(dispatchDelegate(requestBody));
		if (!responseBody) {
			throw DispatchingFailed("Internal error. Dispatching failed for " + TraitsType::RequestAction());
		}

		std::unique_ptr<MESSAGEMODEL::Envelope> responseMessage(createResponseMessageFromRequestMessage(request));
		responseMessage->Header().Action().set(WS::ADDRESSING::AttributedURIType(TraitsType::ResponseAction()));

		insertResponseBodyIntoMessage(*responseMessage, std::move(responseBody));

		return std::move(responseMessage);
	}

	virtual std::unique_ptr<typename TraitsType::Response> dispatchDelegate(const typename TraitsType::Request & requestBody) {
		return TraitsType::dispatch(_dispatcher, requestBody);
	}

	virtual void insertResponseBodyIntoMessage(MESSAGEMODEL::Envelope & responseMessage, std::unique_ptr< typename TraitsType::Response > body) {
		NormalizedMessageAdapter<typename TraitsType::Response> responseAdapter;
		responseAdapter.set(responseMessage, std::move(body));
	}

	typename TraitsType::Dispatcher & _dispatcher;
};

} /* namespace SOAP */
} /* namespace OSELib */

#endif /* SOAP_GENERICSOAPACTIONCOMMAND_H_ */
