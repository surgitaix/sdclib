/*
 * SoapInvoke.cpp
 *
 *  Created on: 11.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 */

#include "OSELib/SOAP/SoapInvoke.h"
#include "OSELib/HTTP/HTTPClientExchanger.h"
#include "OSELib/SOAP/CommonSoapPreprocessing.h"
#include "OSELib/SOAP/NormalizedMessageSerializer.h"
#include "SDCLib/SDCInstance.h"

#include "DataModel/NormalizedMessageModel.hxx"

#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/SSLException.h>

using namespace OSELib::SOAP;

SoapInvoke::SoapInvoke(const Poco::URI & p_requestURI, OSELib::Helper::XercesGrammarPoolProvider & p_grammarProvider)
 : OSELib::Helper::WithLogger(Log::SOAP)
 , m_requestURI(p_requestURI)
 , m_grammarProvider(p_grammarProvider)
{ }

std::unique_ptr<MESSAGEMODEL::Header> SoapInvoke::createHeader()
{
	std::unique_ptr<MESSAGEMODEL::Envelope::HeaderType> t_header(new MESSAGEMODEL::Envelope::HeaderType());
	using MessageIDType = MESSAGEMODEL::Envelope::HeaderType::MessageIDType;
	t_header->getMessageID().set(MessageIDType(SDCLib::SDCInstance::calcMSGID()));
	using ToType = MESSAGEMODEL::Envelope::HeaderType::ToType;
	t_header->getTo().set(ToType(m_requestURI.toString()));
	return t_header;
}

std::unique_ptr<MESSAGEMODEL::Body> SoapInvoke::createBody() {
	return std::unique_ptr<MESSAGEMODEL::Envelope::BodyType>(new MESSAGEMODEL::Envelope::BodyType());
}

std::unique_ptr<MESSAGEMODEL::Envelope> SoapInvoke::createMessage() {
	return std::unique_ptr<MESSAGEMODEL::Envelope>(new MESSAGEMODEL::Envelope(createHeader(), createBody()));
}

std::unique_ptr<MESSAGEMODEL::Envelope> SoapInvoke::invoke(std::unique_ptr<MESSAGEMODEL::Envelope> p_invokeMessage) {

	try {
		OSELib::SOAP::NormalizedMessageSerializer t_serializer;
		const auto t_request(t_serializer.serialize(*p_invokeMessage));

        HTTP::HTTPClientExchanger t_exchanger;
        log_trace([&] { return "Sending soap invoke: " + t_request; });
        Poco::Net::HTTPClientSession t_session(m_requestURI.getHost(), m_requestURI.getPort());
        const std::string t_responseContent = t_exchanger.exchangeHttp(t_session, m_requestURI.getPath(), t_request);
        log_trace([&] { return "Received soap response: " + t_request; });

        // Check the Response
		if (t_responseContent.length() > 0) {
			OSELib::SOAP::CommonSoapPreprocessing soapHandling(m_grammarProvider);
			soapHandling.parse(t_responseContent);
			return std::move(soapHandling.normalizedMessage);
		}
	} catch (const std::exception& e) {
		log_error([&] { return e.what(); });
	} catch (...) {
		// fixme add proper exception handling
		log_error([] { return "Invoke caused exception. "; });
	}

    return nullptr;
}
std::unique_ptr<MESSAGEMODEL::Envelope> SoapInvoke::invoke(std::unique_ptr<MESSAGEMODEL::Envelope> p_invokeMessage, Poco::Net::Context::Ptr p_context)
{
	try {
        OSELib::SOAP::NormalizedMessageSerializer t_serializer;
        const auto t_request(t_serializer.serialize(*p_invokeMessage));

        HTTP::HTTPClientExchanger t_exchanger;

        log_trace([&] { return "Sending SSL soap invoke: " + t_request; });
        Poco::Net::HTTPSClientSession t_SSLSession(m_requestURI.getHost(), m_requestURI.getPort(), p_context);
        auto t_responseContent = t_exchanger.exchangeHttp(t_SSLSession, m_requestURI.getPath(), t_request);
        log_trace([&] { return "Received soap response: " + t_request; });

        // Check the Response
		if (t_responseContent.length() > 0) {
			OSELib::SOAP::CommonSoapPreprocessing soapHandling(m_grammarProvider);
			soapHandling.parse(t_responseContent);
			return std::move(soapHandling.normalizedMessage);
		}
    } catch (const Poco::Net::SSLException& e) {
        log_error([&] { return e.what(); });
	} catch (const std::exception& e) {
		log_error([&] { return e.what(); });
    } catch (...) {
		// fixme add proper exception handling
		log_error([&] { return "Invoke caused exception. "; });
	}

    return nullptr;
}
