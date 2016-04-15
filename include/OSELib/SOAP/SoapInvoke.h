/*
 * SoapInvoke.h
 *
 *  Created on: 11.12.2015
 *      Author: matthias
 */

#ifndef OSELIB_SOAP_SOAPINVOKE_H_
#define OSELIB_SOAP_SOAPINVOKE_H_

#include "Poco/URI.h"

#include "OSELib/fwd.h"
#include "OSELib/Helper/WithLogger.h"

namespace OSELib {
namespace SOAP {

class SoapInvoke : public WithLogger {
public:
	SoapInvoke(const Poco::URI & requestURI, OSELib::Helper::XercesGrammarPoolProvider &_grammarProvider);
	virtual ~SoapInvoke();

	virtual std::unique_ptr<MESSAGEMODEL::Header> createHeader();
	virtual std::unique_ptr<MESSAGEMODEL::Body> createBody();
	virtual std::unique_ptr<MESSAGEMODEL::Envelope> createMessage();

	virtual std::unique_ptr<MESSAGEMODEL::Envelope> invoke(std::unique_ptr<MESSAGEMODEL::Envelope> invokeMessage);

private:
	const Poco::URI _requestURI;
	OSELib::Helper::XercesGrammarPoolProvider &_grammarProvider;
};

} /* namespace SOAP */
} /* namespace OSELib */

#endif /* OSELIB_SOAP_SOAPINVOKE_H_ */
