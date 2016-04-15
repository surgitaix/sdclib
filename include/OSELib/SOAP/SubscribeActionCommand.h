/*
 * SubscribeActionCommand.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef SOAP_SUBSCRIBEACTIONCOMMAND_H_
#define SOAP_SUBSCRIBEACTIONCOMMAND_H_

#include "OSELib/fwd.h"
#include "OSELib/SOAP/GenericSoapActionCommand.h"

namespace OSELib {
namespace SOAP {

class SubscribeActionCommand : public GenericSoapActionCommand<DPWS::SubscribeTraits> {
public:
	SubscribeActionCommand(std::unique_ptr<MESSAGEMODEL::Envelope> requestMessage, DPWS::SubscribeTraits::Dispatcher & dispatcher, const std::string & subscriptionManagerAddress);

	virtual std::unique_ptr<MESSAGEMODEL::Envelope> postprocessResponse(std::unique_ptr<MESSAGEMODEL::Envelope> response) override;

private:
	const WS::ADDRESSING::AttributedURIType _subscriptionManagerAddress;
};


} /* namespace SOAP */
} /* namespace OSELib */

#endif /* SOAP_SUBSCRIBEACTIONCOMMAND_H_ */
