/*
 * SoapActionCommand.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#ifndef OSELIB_SOAP_SOAPACTIONCOMMAND_H_
#define OSELIB_SOAP_SOAPACTIONCOMMAND_H_

#include "OSELib/fwd.h"
#include "OSELib/SOAP/Command.h"

namespace OSELib {
namespace SOAP {

class SoapActionCommand : public Command
{
protected:

	std::unique_ptr<MESSAGEMODEL::Envelope> m_request = nullptr;
	std::unique_ptr<MESSAGEMODEL::Envelope> m_response = nullptr;

public:

	class MissingRequestBody : public std::runtime_error {
	public:
		MissingRequestBody(const std::string & what_arg) :
			std::runtime_error(what_arg)
		{ }
	};

	class DispatchingFailed : public std::runtime_error {
	public:
		DispatchingFailed(const std::string & what_arg) :
			std::runtime_error(what_arg)
		{ }
	};


	SoapActionCommand(std::unique_ptr<MESSAGEMODEL::Envelope> p_request);
	// Special Member Functions
	SoapActionCommand(const SoapActionCommand& p_obj) = default;
	SoapActionCommand(SoapActionCommand&& p_obj) = default;
	SoapActionCommand& operator=(const SoapActionCommand& p_obj) = default;
	SoapActionCommand& operator=(SoapActionCommand&& p_obj) = default;
	virtual ~SoapActionCommand() = default;

	std::unique_ptr<MESSAGEMODEL::Envelope> Run() override;

protected:

	virtual std::unique_ptr<MESSAGEMODEL::Envelope> RunWithExceptionTrap();
	virtual std::unique_ptr<MESSAGEMODEL::Envelope> RunImpl();

	virtual std::unique_ptr<MESSAGEMODEL::Envelope> preprocessRequest(std::unique_ptr<MESSAGEMODEL::Envelope> p_request);
	virtual std::unique_ptr<MESSAGEMODEL::Envelope> postprocessResponse(std::unique_ptr<MESSAGEMODEL::Envelope> p_response);
	virtual std::unique_ptr<MESSAGEMODEL::Envelope> checkDispatchPreconditions(std::unique_ptr<MESSAGEMODEL::Envelope> p_request);
	virtual std::unique_ptr<MESSAGEMODEL::Envelope> checkDispatchPostConditions(std::unique_ptr<MESSAGEMODEL::Envelope> p_response);
	virtual std::unique_ptr<MESSAGEMODEL::Envelope> dispatch(const MESSAGEMODEL::Envelope & p_request) = 0;
	virtual std::unique_ptr<MESSAGEMODEL::Envelope> createResponseMessageFromRequestMessage(const MESSAGEMODEL::Envelope & p_request);
};

}
}

#endif
