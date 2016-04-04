/*
 * FromString.cpp
 *
 *  Created on: 13.10.2014
 *      Author: roehser
 */

#include <sstream>

#include "Poco/Timespan.h"

#include "OSCLib/OSCLibrary.h"
#include "OSCLib/Util/DebugOut.h"
#include "OSCLib/Util/FromString.h"
#include "osdm.hxx"

#include <xercesc/validators/common/Grammar.hpp> // xercesc::Grammar
#include <xercesc/framework/Wrapper4InputSource.hpp>

#include <xsd/cxx/xml/dom/auto-ptr.hxx>
#include <xsd/cxx/xml/dom/bits/error-handler-proxy.hxx>
#include <xsd/cxx/xml/sax/std-input-source.hxx>

#include <xsd/cxx/tree/error-handler.hxx>

namespace CDM {

FromString::FromString() {

}

FromString::~FromString() {

}

xercesc::DOMLSParser * FromString::createParser() {
	using namespace xercesc;
	const XMLCh ls_id [] = { chLatin_L, chLatin_S, chNull };

	// Get an implementation of the Load-Store (LS) interface.
	DOMImplementation* impl (DOMImplementationRegistry::getDOMImplementation (ls_id));
	xercesc::DOMLSParser * parser(
			impl->createLSParser (DOMImplementationLS::MODE_SYNCHRONOUS, 0, XMLPlatformUtils::fgMemoryManager,
					OSCLib::OSCLibrary::getInstance()->pool));

	DOMConfiguration * conf (parser->getDomConfig ());

	// Discard comment nodes in the document.
	conf->setParameter (XMLUni::fgDOMComments, false);

	// Enable datatype normalization.
	conf->setParameter (XMLUni::fgDOMDatatypeNormalization, true);

	// Do not create EntityReference nodes in the DOM tree. No
	// EntityReference nodes will be created, only the nodes
	// corresponding to their fully expanded substitution text
	// will be created.
	conf->setParameter (XMLUni::fgDOMEntities, false);
	// Perform namespace processing.
	conf->setParameter (XMLUni::fgDOMNamespaces, true);
	// Do not include ignorable whitespace in the DOM tree.
	conf->setParameter (XMLUni::fgDOMElementContentWhitespace, false);

	// Enable validation.
	conf->setParameter (XMLUni::fgDOMValidate, true);
	conf->setParameter (XMLUni::fgXercesSchema, true);
	conf->setParameter (XMLUni::fgXercesSchemaFullChecking, true);

	conf->setParameter (XMLUni::fgXercesHandleMultipleImports, true);

	conf->setParameter (XMLUni::fgXercesUserAdoptsDOMDocument, true);

	conf->setParameter(XMLUni::fgXercesValidationErrorAsFatal, true);

	// Use the loaded grammar during parsing.
	conf->setParameter (XMLUni::fgXercesUseCachedGrammarInParse, true);
	// Disable loading schemas via other means (e.g., schemaLocation).
	conf->setParameter (XMLUni::fgXercesLoadSchema, false);

	return parser;
}

std::unique_ptr<xercesc::DOMDocument, FromString::DocDeleter> FromString::parseAndValidate(const std::string & source) {
	std::unique_ptr<xercesc::DOMLSParser, ParserDeleter> parser(createParser());

	std::istringstream sstream(source);
	xsd::cxx::xml::sax::std_input_source isrc (sstream, "Incoming Message");
	xercesc::Wrapper4InputSource wrap (&isrc, false);

	xsd::cxx::tree::error_handler<char> eh;
    xsd::cxx::xml::dom::bits::error_handler_proxy<char> ehp (eh);
    parser->getDomConfig ()->setParameter (xercesc::XMLUni::fgDOMErrorHandler, &ehp);

	try {
		std::unique_ptr<xercesc::DOMDocument, DocDeleter> doc (parser->parse (&wrap));
	    eh.throw_if_failed<xml_schema::Parsing> ();
	    return doc;
	} catch (const xml_schema::Exception& e) {
		OSCLib::Util::DebugOut(OSCLib::Util::DebugOut::Default, "FromString") << "Schema validation failed with error: " << e << std::endl << source << std::endl;
	} catch (const xml_schema::Properties::argument&) {
		OSCLib::Util::DebugOut(OSCLib::Util::DebugOut::Default, "FromString") << "Schema validation failed with error: Invalid property argument (empty namespace or location)" << std::endl;
	} catch (const xsd::cxx::xml::invalid_utf16_string&) {
		OSCLib::Util::DebugOut(OSCLib::Util::DebugOut::Default, "FromString") << "Schema validation failed with error: Invalid UTF-16 text in DOM model" << std::endl;
	} catch (const xsd::cxx::xml::invalid_utf8_string&) {
		OSCLib::Util::DebugOut(OSCLib::Util::DebugOut::Default, "FromString") << "Schema validation failed with error: Invalid UTF-8 text in object model" << std::endl;
	} catch (...) {
		OSCLib::Util::DebugOut(OSCLib::Util::DebugOut::Default, "FromString") << "Schema validation failed with unknown error." << std::endl;
	}

	OSCLib::Util::DebugOut(OSCLib::Util::DebugOut::Full, "FromString") << "Offending message: " << source;
	return nullptr;
}

template <>
std::unique_ptr<CDM::Activate> FromString::convert(const xercesc::DOMDocument & source) {
	return CDM::Activate_(source);
}

template <>
std::unique_ptr<CDM::ActivateResponse> FromString::convert(const xercesc::DOMDocument & source) {
	return CDM::ActivateResponse_(source);
}

template <>
std::unique_ptr<CDM::EpisodicAlertReport> FromString::convert(const xercesc::DOMDocument & source) {
	return CDM::EpisodicAlertReport_(source);
}

template <>
std::unique_ptr<CDM::EpisodicContextChangedReport> FromString::convert(const xercesc::DOMDocument & source) {
	return CDM::EpisodicContextChangedReport_(source);
}

template <>
std::unique_ptr<CDM::EpisodicMetricReport> FromString::convert(const xercesc::DOMDocument & source) {
	return CDM::EpisodicMetricReport_(source);
}

template <>
std::unique_ptr<CDM::GetContextStates> FromString::convert(const xercesc::DOMDocument & source) {
	return CDM::GetContextStates_(source);
}

template <>
std::unique_ptr<CDM::GetMDDescription> FromString::convert(const xercesc::DOMDocument & source) {
	return CDM::GetMDDescription_(source);
}

template <>
std::unique_ptr<CDM::GetMDDescriptionResponse> FromString::convert(const xercesc::DOMDocument & source) {
	return CDM::GetMDDescriptionResponse_(source);
}

template <>
std::unique_ptr<CDM::GetMDIB> FromString::convert(const xercesc::DOMDocument & source) {
	return CDM::GetMDIB_(source);
}

template <>
std::unique_ptr<CDM::GetMDIBResponse> FromString::convert(const xercesc::DOMDocument & source) {
	return CDM::GetMDIBResponse_(source);
}

template <>
std::unique_ptr<CDM::GetMDState> FromString::convert(const xercesc::DOMDocument & source) {
	return CDM::GetMDState_(source);
}

template <>
std::unique_ptr<CDM::GetMDStateResponse> FromString::convert(const xercesc::DOMDocument & source) {
	return CDM::GetMDStateResponse_(source);
}

template <>
std::unique_ptr<CDM::MDSCreatedReport> FromString::convert(const xercesc::DOMDocument & source) {
	return CDM::MDSCreatedReport_(source);
}

template <>
std::unique_ptr<CDM::MDSDeletedReport> FromString::convert(const xercesc::DOMDocument & source) {
	return CDM::MDSDeletedReport_(source);
}

template <>
std::unique_ptr<CDM::ObjectCreatedReport> FromString::convert(const xercesc::DOMDocument & source) {
	return CDM::ObjectCreatedReport_(source);
}

template <>
std::unique_ptr<CDM::ObjectDeletedReport> FromString::convert(const xercesc::DOMDocument & source) {
	return CDM::ObjectDeletedReport_(source);
}

template <>
std::unique_ptr<CDM::OperationalStateChangedReport> FromString::convert(const xercesc::DOMDocument & source) {
	return CDM::OperationalStateChangedReport_(source);
}

template <>
std::unique_ptr<CDM::OperationCreatedReport> FromString::convert(const xercesc::DOMDocument & source) {
	return CDM::OperationCreatedReport_(source);
}

template <>
std::unique_ptr<CDM::OperationDeletedReport> FromString::convert(const xercesc::DOMDocument & source) {
	return CDM::OperationDeletedReport_(source);
}

template <>
std::unique_ptr<CDM::OperationInvokedReport> FromString::convert(const xercesc::DOMDocument & source) {
	return CDM::OperationInvokedReport_(source);
}

template <>
std::unique_ptr<CDM::PeriodicAlertReport> FromString::convert(const xercesc::DOMDocument & source) {
	return CDM::PeriodicAlertReport_(source);
}

template <>
std::unique_ptr<CDM::PeriodicContextChangedReport> FromString::convert(const xercesc::DOMDocument & source) {
	return CDM::PeriodicContextChangedReport_(source);
}

template <>
std::unique_ptr<CDM::PeriodicMetricReport> FromString::convert(const xercesc::DOMDocument & source) {
	return CDM::PeriodicMetricReport_(source);
}

template <>
std::unique_ptr<CDM::SetAlertState> FromString::convert(const xercesc::DOMDocument & source) {
	return CDM::SetAlertState_(source);
}

template <>
std::unique_ptr<CDM::SetAlertStateResponse> FromString::convert(const xercesc::DOMDocument & source) {
	return CDM::SetAlertStateResponse_(source);
}

template <>
std::unique_ptr<CDM::SetContextState> FromString::convert(const xercesc::DOMDocument & source) {
	return CDM::SetContextState_(source);
}

template <>
std::unique_ptr<CDM::SetContextStateResponse> FromString::convert(const xercesc::DOMDocument & source) {
	return CDM::SetContextStateResponse_(source);
}

template <>
std::unique_ptr<CDM::SetString> FromString::convert(const xercesc::DOMDocument & source) {
	return CDM::SetString_(source);
}

template <>
std::unique_ptr<CDM::SetStringResponse> FromString::convert(const xercesc::DOMDocument & source) {
	return CDM::SetStringResponse_(source);
}

template <>
std::unique_ptr<CDM::SetValue> FromString::convert(const xercesc::DOMDocument & source) {
	return CDM::SetValue_(source);
}

template <>
std::unique_ptr<CDM::SetValueResponse> FromString::convert(const xercesc::DOMDocument & source) {
	return CDM::SetValueResponse_(source);
}

template <>
std::unique_ptr<CDM::SystemErrorReport> FromString::convert(const xercesc::DOMDocument & source) {
	return CDM::SystemErrorReport_(source);
}

template <>
std::unique_ptr<CDM::WaveformStream> FromString::convert(const xercesc::DOMDocument & source) {
	return CDM::WaveformStream_(source);
}

template <>
std::unique_ptr<CDM::MDIB> FromString::convert(const xercesc::DOMDocument & source) {
	return CDM::MDIBContainer(source);
}

} /* namespace OSCLib */
