/*
 * GetActionCommand.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef SOAP_GETACTIONCOMMAND_H_
#define SOAP_GETACTIONCOMMAND_H_

#include "OSELib/fwd.h"
#include "OSELib/SOAP/SoapActionCommand.h"

namespace OSELib {
namespace SOAP {

class GetActionCommand : public SoapActionCommand {
public:
	GetActionCommand(std::unique_ptr<MESSAGEMODEL::Envelope> requestMessage, const WS::MEX::Metadata & metadata);
	virtual ~GetActionCommand();

	std::unique_ptr<MESSAGEMODEL::Envelope> dispatch(const MESSAGEMODEL::Envelope & request) override;

private:
	std::unique_ptr<WS::MEX::Metadata> _metadata;
};

} /* namespace SOAP */
} /* namespace OSELib */

#endif /* SOAP_GETACTIONCOMMAND_H_ */
