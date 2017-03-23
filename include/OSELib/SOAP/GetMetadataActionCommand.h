/*
 * GetMetadataActionCommand.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef SOAP_GETMETADATAACTIONCOMMAND_H_
#define SOAP_GETMETADATAACTIONCOMMAND_H_

#include "OSELib/fwd.h"
#include "OSELib/SOAP/SoapActionCommand.h"

namespace OSELib {
namespace SOAP {

class GetMetadataActionCommand : public SoapActionCommand {
public:
	GetMetadataActionCommand(std::unique_ptr<MESSAGEMODEL::Envelope> requestMessage, const WS::MEX::Metadata & metadata);
	virtual ~GetMetadataActionCommand();

	virtual std::unique_ptr<MESSAGEMODEL::Envelope> dispatch(const MESSAGEMODEL::Envelope & request) override;
	virtual std::unique_ptr<MESSAGEMODEL::Envelope> checkDispatchPreconditions(std::unique_ptr<MESSAGEMODEL::Envelope> request) override;

private:
	std::unique_ptr<WS::MEX::Metadata> _metadata;
};

} /* namespace SOAP */
} /* namespace OSELib */

#endif /* SOAP_GETMETADATAACTIONCOMMAND_H_ */
