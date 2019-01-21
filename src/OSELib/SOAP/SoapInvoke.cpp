/*
 * SoapInvoke.cpp
 *
 *  Created on: 11.12.2015
 *      Author: matthias
 */

#include <iostream>

#include "Poco/UUIDGenerator.h"
#include "Poco/Net/HTTPClientSession.h"

#include "NormalizedMessageModel.hxx"

#include "OSELib/Helper/Message.h"
#include "OSELib/Helper/XercesDocumentWrapper.h"
#include "OSELib/HTTP/HTTPClientExchanger.h"
#include "OSELib/SOAP/CommonSoapPreprocessing.h"
#include "OSELib/SOAP/NormalizedMessageAdapter.h"
#include "OSELib/SOAP/NormalizedMessageSerializer.h"
#include "OSELib/SOAP/SoapInvoke.h"

namespace OSELib {
namespace SOAP {

SoapInvoke::SoapInvoke(const Poco::URI & requestURI, OSELib::Helper::XercesGrammarPoolProvider & grammarProvider) :
	WithLogger(Log::SOAP),
	_requestURI(requestURI),
	_grammarProvider(grammarProvider)
{
}

SoapInvoke::~SoapInvoke() {
}

std::unique_ptr<MESSAGEMODEL::Header> SoapInvoke::createHeader() {
	std::unique_ptr<MESSAGEMODEL::Envelope::HeaderType> header(new MESSAGEMODEL::Envelope::HeaderType());
	using MessageIDType = MESSAGEMODEL::Envelope::HeaderType::MessageIDType;
	header->MessageID().set(MessageIDType(Poco::UUIDGenerator::defaultGenerator().create().toString()));
	using ToType = MESSAGEMODEL::Envelope::HeaderType::ToType;
	header->To().set(ToType(_requestURI.toString()));
	return header;
}

std::unique_ptr<MESSAGEMODEL::Body> SoapInvoke::createBody() {
	return std::unique_ptr<MESSAGEMODEL::Envelope::BodyType>(new MESSAGEMODEL::Envelope::BodyType());
}

std::unique_ptr<MESSAGEMODEL::Envelope> SoapInvoke::createMessage() {
	return std::unique_ptr<MESSAGEMODEL::Envelope>(new MESSAGEMODEL::Envelope(createHeader(), createBody()));
}

std::unique_ptr<MESSAGEMODEL::Envelope> SoapInvoke::invoke(std::unique_ptr<MESSAGEMODEL::Envelope> invokeMessage) {

	try {
		OSELib::SOAP::NormalizedMessageSerializer serializer;
		const auto request(serializer.serialize(*invokeMessage));

		log_trace([&] { return "Sending soap invoke: " + request; });
		Poco::Net::HTTPClientSession session(_requestURI.getHost(), _requestURI.getPort());
		HTTP::HTTPClientExchanger exchanger;
		const std::string responseContent(exchanger.exchangeHttp(session, _requestURI.getPath(), request));
		log_trace([&] { return "Received soap response: " + request; });

		if (responseContent.length() > 0) {
			OSELib::SOAP::CommonSoapPreprocessing soapHandling(_grammarProvider);
			soapHandling.parse(responseContent);
			return std::move(soapHandling.normalizedMessage);
		}
	} catch (const std::exception e) {
		log_error([&] { return e.what(); });
	} catch (...) {
		// fixme add proper exception handling
		log_error([&] { return "Invoke caused exception. "; });
	}

	return nullptr;
}

} /* namespace SOAP */
} /* namespace OSELib */
