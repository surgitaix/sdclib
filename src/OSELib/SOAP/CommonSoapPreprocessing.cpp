/*
 * CommonSoapPreprocessing.cpp
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#include "Poco/Net/HTTPServerRequest.h"

#include "NormalizedMessageModel.hxx"

#include "OSELib/Helper/Message.h"
#include "OSELib/Helper/XercesDocumentWrapper.h"
#include "OSELib/Helper/XercesGrammarPoolProvider.h"
#include "OSELib/SOAP/CommonSoapPreprocessing.h"
#include "OSELib/SOAP/NormalizeMessageFilter.h"

namespace OSELib {
namespace SOAP {

CommonSoapPreprocessing::CommonSoapPreprocessing(Helper::XercesGrammarPoolProvider & grammarProvider) :
	WithLogger(Log::SOAP),
	_grammarProvider(grammarProvider)
{
}

void CommonSoapPreprocessing::parse(const std::string & request) {
	rawMessage = Helper::Message::create(request);
	if (!rawMessage) {
		log_error([&] { return "Extracting raw message failed. "; });
	}
	commonParsing();
}

void CommonSoapPreprocessing::parse(std::istream & request) {
	rawMessage = Helper::Message::create(request);

	if (!rawMessage) {
		log_error([&] { return "Extracting raw message from http stream failed. "; });
	}

	commonParsing();
}

void CommonSoapPreprocessing::commonParsing() {
	if (!rawMessage) {
		throw SoapFaultException();
	}

	log_trace([&] { return "Processing message: \n" + rawMessage->getContent(); });

	xercesDocument = Helper::XercesDocumentWrapper::create(*rawMessage, _grammarProvider);

	if (!xercesDocument) {
		log_error([&] { return "XML parsing failed."; });
		throw SoapFaultException();
	} else {
		log_trace([&] { return "XML parsing successful."; });
	}

	normalizedMessage = NormalizeMessageFilter::apply(*xercesDocument);

	if (!normalizedMessage) {
		log_error([&] { return "Building object model failed."; });
		throw SoapFaultException();
	} else {
		log_trace([&] { return "Building object model successful."; });
	}

	if (!normalizedMessage->Header().Action().present()) {
		log_error([&] { return "No action."; });
		throw SoapFaultException();
	} else {
		log_debug([&] { return "Message action: " + normalizedMessage->Header().Action().get(); });
	}
}

} /* namespace SOAP */
} /* namespace OSELib */
