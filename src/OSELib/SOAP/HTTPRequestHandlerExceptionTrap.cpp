/*
 * HTTPRequestHandlerExceptionTrap.cpp
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#include <iostream>

#include <xercesc/dom/DOMException.hpp>
#include <xercesc/util/XMLException.hpp>

#include "NormalizedMessageModel.hxx"

#include "OSELib/SOAP/Command.h"
#include "OSELib/SOAP/CommonSoapPreprocessing.h"
#include "OSELib/SOAP/HTTPRequestHandlerExceptionTrap.h"
#include "OSELib/SOAP/NormalizedMessageSerializer.h"
#include "OSELib/SOAP/SoapFaultCommand.h"
#include "OSELib/SOAP/SoapHTTPResponseWrapper.h"

#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/XMLException.hpp>

namespace OSELib {
namespace SOAP {

HTTPRequestHandlerExceptionTrap::HTTPRequestHandlerExceptionTrap() :
	WithLogger(Log::HTTP)
{
}

HTTPRequestHandlerExceptionTrap::~HTTPRequestHandlerExceptionTrap() = default;

void HTTPRequestHandlerExceptionTrap::handleRequest(Poco::Net::HTTPServerRequest & httpRequest, Poco::Net::HTTPServerResponse & httpResponse) {

	std::unique_ptr<Command> faultCommand;

	try {
		log_trace([&] { return "Processing HTTP request ... "; });
		handleRequestImpl(httpRequest, httpResponse);
		log_trace([&] { return "Processing HTTP request successful. "; });
	} catch (const CommonSoapPreprocessing::SoapFaultException & e) {
		log_error([&] { return "Processing HTTP request caused exception: " + std::string(e.what()); });
		faultCommand = std::unique_ptr<Command>(new SoapFaultCommand(httpResponse));
	} catch (const xml_schema::Exception & e) {
		log_error([&] { return "Processing HTTP request caused exception: " + std::string(e.what()); });
		faultCommand = std::unique_ptr<Command>(new SoapFaultCommand(httpResponse));
	} catch (const std::exception & e) {
		log_error([&] { return "Processing HTTP request caused exception: \nUnhandled exception: " + std::string(e.what()); });
		faultCommand = std::unique_ptr<Command>(new SoapFaultCommand(httpResponse));
	} catch (const xercesc::XMLException & e) {
        char* t_msg(xercesc::XMLString::transcode(e.getMessage()));
		log_error([&] { return "Processing HTTP request caused exception: \nUnexpected Xerces-C++ exception with code: " + std::to_string(e.getCode()) + std::string(t_msg); });
        xercesc::XMLString::release(&t_msg);
		faultCommand = std::unique_ptr<Command>(new SoapFaultCommand(httpResponse));
	} catch (const xercesc::DOMException & e) {
        char* t_msg(xercesc::XMLString::transcode(e.getMessage()));
		log_error([&] { return "Processing HTTP request caused exception: \nUnexpected Xerces-C++ DOM exception with code: " + std::to_string(e.code) + std::string(t_msg); });
        xercesc::XMLString::release(&t_msg);
		faultCommand = std::unique_ptr<Command>(new SoapFaultCommand(httpResponse));
	} catch (...) {
		log_error([] { return "Processing HTTP request caused exception: \nUnknown exception."; });
		faultCommand = std::unique_ptr<Command>(new SoapFaultCommand(httpResponse));
	}

	if (!faultCommand) {
		return;
	}
	std::unique_ptr<MESSAGEMODEL::Envelope> responseMessage(faultCommand->Run());

	SoapHTTPResponseWrapper response(httpResponse);
	response.send(NormalizedMessageSerializer::serialize(*responseMessage));
}

} /* namespace SOAP */
} /* namespace OSELib */
