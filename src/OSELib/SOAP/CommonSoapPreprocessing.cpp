/*
 * CommonSoapPreprocessing.cpp
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#include "OSELib/SOAP/CommonSoapPreprocessing.h"
#include "OSELib/Helper/Message.h"
#include "OSELib/Helper/XercesDocumentWrapper.h"
#include "OSELib/Helper/XercesGrammarPoolProvider.h"
#include "OSELib/SOAP/NormalizeMessageFilter.h"
#include "OSELib/TCP/TCPBroadcastServerHandler.h"


#include "DataModel/NormalizedMessageModel.hxx"

namespace OSELib {
namespace SOAP {

CommonSoapPreprocessing::CommonSoapPreprocessing(Helper::XercesGrammarPoolProvider & p_grammarProvider)
: OSELib::Helper::WithLogger(Log::SOAP)
, m_grammarProvider(p_grammarProvider)
{ }

void CommonSoapPreprocessing::parse(const std::string & p_request)
{
	rawMessage = Helper::Message::create(p_request);
	if (!rawMessage) {
		log_error([] { return "Extracting raw message failed. "; });
	}
	commonParsing();
}

void CommonSoapPreprocessing::parse(std::istream & p_request)
{
	rawMessage = Helper::Message::create(p_request);

	if (!rawMessage) {
		log_error([] { return "Extracting raw message from HTTP stream failed. "; });
	}

	if(Network::TCPBroadcastServerHandler::getInstance("127.0.0.1", 8000)->isStarted())
	{
			Network::TCPBroadcastServerHandler::getInstance("127.0.0.1", 5000)->broadcastMessage(rawMessage->getContent());
	}
	commonParsing();
}

void CommonSoapPreprocessing::commonParsing()
{
	if (!rawMessage) {
		throw SoapFaultException();
	}

	//log_trace([&] { return "Processing message: \n" + rawMessage->getContent(); });

	xercesDocument = Helper::XercesDocumentWrapper::create(*rawMessage, m_grammarProvider);

	if (!xercesDocument) {
		log_error([] { return "XML parsing failed."; });
		throw SoapFaultException();
	} else {
		log_trace([] { return "XML parsing successful."; });
	}

	normalizedMessage = NormalizeMessageFilter::apply(*xercesDocument);

	if (!normalizedMessage) {
		log_error([] { return "Building object model failed."; });
		throw SoapFaultException();
	} else {
		log_trace([] { return "Building object model successful."; });
	}

	if (!normalizedMessage->getHeader().getAction().present()) {
		log_error([] { return "No action."; });
		throw SoapFaultException();
	} else {
		log_debug([&] { return "Message action: " + normalizedMessage->getHeader().getAction().get(); });
	}
}

}
}
