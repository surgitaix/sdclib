/*
 * CommonSoapPreprocessing.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef SOAP_COMMONSOAPPREPROCESSING_H_
#define SOAP_COMMONSOAPPREPROCESSING_H_

#include "OSELib/fwd.h"
#include "OSELib/Helper/WithLogger.h"

namespace OSELib {
namespace SOAP {

class CommonSoapPreprocessing : public WithLogger {
public:

	// fixme move all exception definitions to a common file so the are not scattered around the classes
	// fixme catch all exceptions in the HTTPRequestHandlerExceptionTrap appropriately (use inheritance of exceptions)
	class SoapFaultException : public std::exception {
	};

	CommonSoapPreprocessing(Helper::XercesGrammarPoolProvider & grammarProvider);

	void parse(std::istream & request);
	void parse(const std::string & request);

	std::unique_ptr<const Helper::Message> rawMessage;
	std::unique_ptr<const Helper::XercesDocumentWrapper> xercesDocument;
	std::unique_ptr<MESSAGEMODEL::Envelope> normalizedMessage;

private:
	void commonParsing();

	Helper::XercesGrammarPoolProvider & _grammarProvider;
};

} /* namespace SOAP */
} /* namespace OSELib */

#endif /* SOAP_COMMONSOAPPREPROCESSING_H_ */
