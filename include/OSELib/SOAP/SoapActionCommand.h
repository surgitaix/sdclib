/*
 * SoapActionCommand.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef SOAP_SOAPACTIONCOMMAND_H_
#define SOAP_SOAPACTIONCOMMAND_H_

#include "OSELib/fwd.h"
#include "OSELib/SOAP/Command.h"

namespace OSELib {
namespace SOAP {

class SoapActionCommand : public Command {
public:

	class MissingRequestBody : public std::runtime_error {
	public:
		MissingRequestBody(const std::string & what_arg) :
			std::runtime_error(what_arg)
		{
		}
	};

	class DispatchingFailed : public std::runtime_error {
	public:
		DispatchingFailed(const std::string & what_arg) :
			std::runtime_error(what_arg)
		{
		}
	};

	SoapActionCommand(std::unique_ptr<MESSAGEMODEL::Envelope> request);
	virtual ~SoapActionCommand();

	std::unique_ptr<MESSAGEMODEL::Envelope> Run() override;

protected:
	virtual std::unique_ptr<MESSAGEMODEL::Envelope> RunWithExceptionTrap();
	virtual std::unique_ptr<MESSAGEMODEL::Envelope> RunImpl();

	virtual std::unique_ptr<MESSAGEMODEL::Envelope> preprocessRequest(std::unique_ptr<MESSAGEMODEL::Envelope> request);
	virtual std::unique_ptr<MESSAGEMODEL::Envelope> postprocessResponse(std::unique_ptr<MESSAGEMODEL::Envelope> response);
	virtual std::unique_ptr<MESSAGEMODEL::Envelope> checkDispatchPreconditions(std::unique_ptr<MESSAGEMODEL::Envelope> request);
	virtual std::unique_ptr<MESSAGEMODEL::Envelope> checkDispatchPostConditions(std::unique_ptr<MESSAGEMODEL::Envelope> response);
	virtual std::unique_ptr<MESSAGEMODEL::Envelope> dispatch(const MESSAGEMODEL::Envelope & request) = 0;
	virtual std::unique_ptr<MESSAGEMODEL::Envelope> createResponseMessageFromRequestMessage(const MESSAGEMODEL::Envelope & request);

protected:
	std::unique_ptr<MESSAGEMODEL::Envelope> _request;
	std::unique_ptr<MESSAGEMODEL::Envelope> _response;
};

} /* namespace SOAP */
} /* namespace OSELib */

#endif /* SOAP_SOAPACTIONCOMMAND_H_ */
