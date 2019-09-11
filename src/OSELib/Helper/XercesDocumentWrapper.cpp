/*
 * XercesDocumentWrapper.cpp
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#include "OSELib/Helper/XercesDocumentWrapper.h"
#include "OSELib/Helper/Message.h"
#include "OSELib/Helper/XercesGrammarPoolProvider.h"
#include "OSELib/Helper/XercesParserWrapper.h"
#include "OSELib/Helper/WithLogger.h"

#include <sstream>

#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/framework/Wrapper4InputSource.hpp>

#include <xsd/cxx/xml/dom/bits/error-handler-proxy.hxx>
#include <xsd/cxx/tree/error-handler.hxx>

namespace OSELib {
namespace Helper {

XercesDocumentWrapper::XercesDocumentWrapper(std::unique_ptr<xercesc::DOMDocument, DocumentDeleter> p_document)
: m_document(std::move(p_document))
{ }

std::unique_ptr<XercesDocumentWrapper> XercesDocumentWrapper::create(const Message & p_msg)
{
	return create(p_msg, XercesGrammarPoolProvider());
}

std::unique_ptr<XercesDocumentWrapper> XercesDocumentWrapper::create(const Message & p_msg, const XercesGrammarPoolProvider & p_grammarPoolProvider)
{
	auto t_document = parseAndValidate(p_msg.getContent(), p_grammarPoolProvider);
	if (nullptr != t_document) {
		return std::unique_ptr<XercesDocumentWrapper>(new XercesDocumentWrapper(std::move(t_document)));
	}
	return nullptr;
}

const xercesc::DOMDocument & XercesDocumentWrapper::getDocument() const
{
	// fixme: What happens when document is nullptr?!
	return *m_document;
}

std::unique_ptr<xercesc::DOMDocument, XercesDocumentWrapper::DocumentDeleter> XercesDocumentWrapper::parseAndValidate(const std::string & p_source, const XercesGrammarPoolProvider & p_grammarPoolProvider) {

	auto logMessage([&](const std::string & p_explanation) {
		WithLogger(Log::SCHEMA).log_error([&] { return p_explanation + "\nOffending message: " + p_source;});
	});

	xsd::cxx::tree::error_handler<char> t_eh;
	xsd::cxx::xml::dom::bits::error_handler_proxy<char> t_ehp (t_eh);

	XercesParserWrapper t_parser(p_grammarPoolProvider);
	t_parser.getParser()->getDomConfig ()->setParameter (xercesc::XMLUni::fgDOMErrorHandler, &t_ehp);

	try {
		xercesc::MemBufInputSource t_contentSource((const XMLByte*)p_source.c_str(), p_source.size(), "");
		xercesc::Wrapper4InputSource t_wrap (&t_contentSource, false);

		std::unique_ptr<xercesc::DOMDocument, DocumentDeleter> t_doc (t_parser.getParser()->parse (&t_wrap));
		t_eh.throw_if_failed<xml_schema::Parsing> ();
		return t_doc;
	} catch (const xml_schema::Exception & e) {
		std::stringstream t_ss;
		t_ss << e;
		logMessage("Schema validation failed with error: " +t_ss.str());
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

}
}
