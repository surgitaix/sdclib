/*
 * GenericSoapEventCommand.h
 *
 *  Created on: 10.12.2015
 *      Author: matthias
 */

#ifndef OSELIB_SOAP_GENERICSOAPEVENTCOMMAND_H_
#define OSELIB_SOAP_GENERICSOAPEVENTCOMMAND_H_

#include "OSELib/fwd.h"
#include "OSELib/SOAP/NormalizedMessageAdapter.h"
#include "OSELib/SOAP/SoapActionCommand.h"

namespace OSELib {
namespace SOAP {

template<class TraitsType>
class GenericSoapEventCommand : public SoapActionCommand {
public:
	GenericSoapEventCommand(std::unique_ptr<MESSAGEMODEL::Envelope> requestMessage, typename TraitsType::Dispatcher & dispatcher) :
		SoapActionCommand(std::move(requestMessage)),
		_dispatcher(dispatcher)
	{
	}

	virtual ~GenericSoapEventCommand() = default;

protected:
	std::unique_ptr<MESSAGEMODEL::Envelope> checkDispatchPreconditions(std::unique_ptr<MESSAGEMODEL::Envelope> request) override {
		NormalizedMessageAdapter<typename TraitsType::ReportType> requestAdapter;
		if (!requestAdapter.present(*request)) {
			throw SoapActionCommand::MissingRequestBody("Request body missing for " + TraitsType::Action());
		}
		return std::move(request);
	}

	std::unique_ptr<MESSAGEMODEL::Envelope> dispatch(const MESSAGEMODEL::Envelope & request) override {

		NormalizedMessageAdapter<typename TraitsType::ReportType> requestAdapter;
		const typename TraitsType::ReportType & requestBody(requestAdapter.get(request));
		dispatchDelegate(requestBody);

		return nullptr;
	}

	virtual void dispatchDelegate(const typename TraitsType::ReportType & requestBody) {
		TraitsType::dispatch(_dispatcher, requestBody);
	}

	typename TraitsType::Dispatcher & _dispatcher;
};

} /* namespace SOAP */
} /* namespace OSELib */

#endif /* OSELIB_SOAP_GENERICSOAPEVENTCOMMAND_H_ */
