/*
 * XercesDocumentWrapper.cpp
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#include <iostream>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/framework/Wrapper4InputSource.hpp>

#include "NormalizedMessageModel.hxx"

#include <xsd/cxx/xml/dom/bits/error-handler-proxy.hxx>
#include <xsd/cxx/tree/error-handler.hxx>

#include "OSELib/Helper/Message.h"
#include "OSELib/Helper/XercesDocumentWrapper.h"
#include "OSELib/Helper/XercesGrammarPoolProvider.h"
#include "OSELib/Helper/XercesParserWrapper.h"
#include "OSELib/Helper/WithLogger.h"

namespace OSELib {
namespace Helper {

XercesDocumentWrapper::XercesDocumentWrapper(std::unique_ptr<xercesc::DOMDocument, DocumentDeleter> document) :
	_document(std::move(document))
{
}

std::unique_ptr<XercesDocumentWrapper> XercesDocumentWrapper::create(const Message & msg) {
	return create(msg, XercesGrammarPoolProvider());
}

std::unique_ptr<XercesDocumentWrapper> XercesDocumentWrapper::create(const Message & msg, const XercesGrammarPoolProvider & grammarPoolProvider) {
	std::unique_ptr<xercesc::DOMDocument, DocumentDeleter> document(parseAndValidate(msg.getContent(), grammarPoolProvider));
	if (document) {
		return std::unique_ptr<XercesDocumentWrapper>(new XercesDocumentWrapper(std::move(document)));
	} else {
		return nullptr;
	}
}

const xercesc::DOMDocument & XercesDocumentWrapper::getDocument() const {
	return *_document;
}

std::unique_ptr<xercesc::DOMDocument, XercesDocumentWrapper::DocumentDeleter> XercesDocumentWrapper::parseAndValidate(const std::string & source, const XercesGrammarPoolProvider & grammarPoolProvider) {

	auto logMessage([&](const std::string & explanation) {
		WithLogger(Log::SCHEMA).log_error([&] { return explanation + "\nOffending message: " + source;});
	});

	xsd::cxx::tree::error_handler<char> eh;
	xsd::cxx::xml::dom::bits::error_handler_proxy<char> ehp (eh);

	XercesParserWrapper parser(grammarPoolProvider);
	parser.getParser()->getDomConfig ()->setParameter (xercesc::XMLUni::fgDOMErrorHandler, &ehp);

	try {
		xercesc::MemBufInputSource contentSource((const XMLByte*)source.c_str(), source.size(), "");
		xercesc::Wrapper4InputSource wrap (&contentSource, false);

		std::unique_ptr<xercesc::DOMDocument, DocumentDeleter> doc (parser.getParser()->parse (&wrap));
		eh.throw_if_failed<xml_schema::Parsing> ();
		return doc;
	} catch (const xml_schema::Exception & e) {
		std::stringstream ss;
		ss << e;
		logMessage("Schema validation failed with error: " +ss.str());
	} catch (const xml_schema::Properties::argument &) {
		logMessage("Schema validation failed with error: Invalid property argument (empty namespace or location)");
	} catch (const xsd::cxx::xml::invalid_utf16_string &) {
		logMessage("Schema validation failed with error: Invalid UTF-16 text in DOM model");
	} catch (const xsd::cxx::xml::invalid_utf8_string &) {
		logMessage("Schema validation failed with error: Invalid UTF-8 text in object model");
	} catch (...) {
		logMessage("Schema validation failed with unknown error.");
	}

	return nullptr;
}

} /* namespace Helper */
} /* namespace OSELib */
