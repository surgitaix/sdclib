/*
 * UnsubscribeActionCommand.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef SOAP_UNSUBSCRIBEACTIONCOMMAND_H_
#define SOAP_UNSUBSCRIBEACTIONCOMMAND_H_

#include "OSELib/fwd.h"
#include "OSELib/SOAP/GenericSoapActionCommand.h"

namespace OSELib {
namespace SOAP {

class UnsubscribeActionCommand : public SoapActionCommand {
public:
	UnsubscribeActionCommand(std::unique_ptr<MESSAGEMODEL::Envelope> requestMessage, DPWS::UnsubscribeTraits::Dispatcher & dispatcher);
	virtual ~UnsubscribeActionCommand();

protected:
	virtual std::unique_ptr<MESSAGEMODEL::Envelope> dispatch(const MESSAGEMODEL::Envelope & request) override;

	DPWS::UnsubscribeTraits::Dispatcher & _dispatcher;
};

} /* namespace SOAP */
} /* namespace OSELib */

#endif /* SOAP_UNSUBSCRIBEACTIONCOMMAND_H_ */
