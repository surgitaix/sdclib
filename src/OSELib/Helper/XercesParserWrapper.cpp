/*
 * XercesParserWrapper.cpp
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#include <xercesc/dom/DOM.hpp>

#include "OSELib/Helper/XercesParserWrapper.h"

namespace OSELib {
namespace Helper {

XercesParserWrapper::XercesParserWrapper(const XercesGrammarPoolProvider & grammarPoolProvider) {
	using namespace xercesc;
	const XMLCh ls_id [] = { chLatin_L, chLatin_S, chNull };

	// Get an implementation of the Load-Store (LS) interface.
	DOMImplementation* impl (DOMImplementationRegistry::getDOMImplementation (ls_id));

	std::unique_ptr<xercesc::DOMLSParser, ParserDeleter> parser(
			impl->createLSParser(
					DOMImplementationLS::MODE_SYNCHRONOUS,
					0,
					XMLPlatformUtils::fgMemoryManager,
					grammarPoolProvider.getPool())
			);

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
	conf->setParameter (XMLUni::fgDOMValidate, grammarPoolProvider.getPool() != nullptr);
	conf->setParameter (XMLUni::fgXercesSchema, grammarPoolProvider.getPool() != nullptr);
	conf->setParameter (XMLUni::fgXercesSchemaFullChecking, grammarPoolProvider.getPool() != nullptr);

	conf->setParameter (XMLUni::fgXercesHandleMultipleImports, true);

	conf->setParameter (XMLUni::fgXercesUserAdoptsDOMDocument, true);

	conf->setParameter(XMLUni::fgXercesValidationErrorAsFatal, true);

	// Use the loaded grammar during parsing.
	conf->setParameter (XMLUni::fgXercesUseCachedGrammarInParse, true);
	// Disable loading schemas via other means (e.g., schemaLocation).
	conf->setParameter (XMLUni::fgXercesLoadSchema, false);

	_parser.swap(parser);
}

xercesc::DOMLSParser * XercesParserWrapper::getParser() {
	return _parser.get();
}

} /* namespace Helper */
} /* namespace OSELib */
