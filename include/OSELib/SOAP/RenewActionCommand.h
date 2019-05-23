/*
 * RenewActionCommand.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef SOAP_RENEWACTIONCOMMAND_H_
#define SOAP_RENEWACTIONCOMMAND_H_

#include "OSELib/fwd.h"
#include "OSELib/DPWS/OperationTraits.h"
#include "OSELib/SOAP/SoapActionCommand.h"

namespace OSELib {
namespace SOAP {

class RenewActionCommand : public SoapActionCommand {
public:
	RenewActionCommand(std::unique_ptr<MESSAGEMODEL::Envelope> requestMessage, DPWS::RenewTraits::Dispatcher & dispatcher);
	virtual ~RenewActionCommand();

protected:
	std::unique_ptr<MESSAGEMODEL::Envelope> dispatch(const MESSAGEMODEL::Envelope & request) override;

	DPWS::RenewTraits::Dispatcher & _dispatcher;
};

} /* namespace SOAP */
} /* namespace OSELib */

#endif /* SOAP_RENEWACTIONCOMMAND_H_ */
