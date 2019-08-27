/*
 * HTTPRequestHandlerExceptionTrap.cpp
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#include "OSELib/SOAP/HTTPRequestHandlerExceptionTrap.h"
#include "OSELib/SOAP/Command.h"
#include "OSELib/SOAP/CommonSoapPreprocessing.h"
#include "OSELib/SOAP/NormalizedMessageSerializer.h"
#include "OSELib/SOAP/SoapFaultCommand.h"
#include "OSELib/SOAP/SoapHTTPResponseWrapper.h"

#include "DataModel/NormalizedMessageModel.hxx"

#include <xercesc/dom/DOMException.hpp>
#include <xercesc/util/XMLException.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/XMLException.hpp>

namespace OSELib {
namespace SOAP {

HTTPRequestHandlerExceptionTrap::HTTPRequestHandlerExceptionTrap()
: OSELib::Helper::WithLogger(Log::HTTP)
{ }

void HTTPRequestHandlerExceptionTrap::handleRequest(Poco::Net::HTTPServerRequest & p_httpRequest, Poco::Net::HTTPServerResponse & p_httpResponse) {

	std::unique_ptr<Command> t_faultCommand = nullptr;
	try {
		log_trace([] { return "Processing HTTP request ... "; });
		handleRequestImpl(p_httpRequest, p_httpResponse);
		log_trace([] { return "Processing HTTP request successful. "; });
	} catch (const CommonSoapPreprocessing::SoapFaultException & e) {
		log_error([&] { return "Processing HTTP request caused exception: " + std::string(e.what()); });
		t_faultCommand = std::unique_ptr<Command>(new SoapFaultCommand(p_httpResponse));
	} catch (const xml_schema::Exception & e) {
		log_error([&] { return "Processing HTTP request caused exception: " + std::string(e.what()); });
		t_faultCommand = std::unique_ptr<Command>(new SoapFaultCommand(p_httpResponse));
	} catch (const xercesc::XMLException & e) {
        char* t_msg(xercesc::XMLString::transcode(e.getMessage()));
		log_error([&] { return "Processing HTTP request caused exception: \nUnexpected Xerces-C++ exception with code: " + std::to_string(e.getCode()) + std::string(t_msg); });
        xercesc::XMLString::release(&t_msg);
        t_faultCommand = std::unique_ptr<Command>(new SoapFaultCommand(p_httpResponse));
	} catch (const xercesc::DOMException & e) {
        char* t_msg(xercesc::XMLString::transcode(e.getMessage()));
		log_error([&] { return "Processing HTTP request caused exception: \nUnexpected Xerces-C++ DOM exception with code: " + std::to_string(e.code) + std::string(t_msg); });
        xercesc::XMLString::release(&t_msg);
        t_faultCommand = std::unique_ptr<Command>(new SoapFaultCommand(p_httpResponse));
	} catch (const std::exception & e) {
		log_error([&] { return "Processing HTTP request caused exception: \nUnhandled exception: " + std::string(e.what()); });
		t_faultCommand = std::unique_ptr<Command>(new SoapFaultCommand(p_httpResponse));
	} catch (...) {
		log_error([] { return "Processing HTTP request caused exception: \nUnknown exception."; });
		t_faultCommand = std::unique_ptr<Command>(new SoapFaultCommand(p_httpResponse));
	}

	if (!t_faultCommand) {
		// Fixme: just return? Dont send anything?
		return;
	}
	std::unique_ptr<MESSAGEMODEL::Envelope> t_responseMessage(t_faultCommand->Run());

	SoapHTTPResponseWrapper t_response(p_httpResponse);
	t_response.send(NormalizedMessageSerializer::serialize(*t_responseMessage));
}

}
}
