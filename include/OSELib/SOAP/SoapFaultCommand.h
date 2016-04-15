/*
 * SoapFaultCommand.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef SOAP_SOAPFAULTCOMMAND_H_
#define SOAP_SOAPFAULTCOMMAND_H_

#include "OSELib/fwd.h"
#include "OSELib/SOAP/Command.h"

namespace OSELib {
namespace SOAP {

class SoapFaultCommand : public Command {
public:
	SoapFaultCommand(Poco::Net::HTTPServerResponse & httpResponse);
	virtual ~SoapFaultCommand();

	virtual std::unique_ptr<MESSAGEMODEL::Envelope> Run() override;

private:
	Poco::Net::HTTPServerResponse & _httpResponse;
};

} /* namespace SOAP */
} /* namespace OSELib */

#endif /* SOAP_SOAPFAULTCOMMAND_H_ */
