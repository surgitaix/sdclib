/*
 * XercesParserWrapper.cpp
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#include "OSELib/Helper/XercesParserWrapper.h"
#include <xercesc/dom/DOM.hpp>

namespace OSELib {
namespace Helper {

XercesParserWrapper::XercesParserWrapper(const XercesGrammarPoolProvider & p_grammarPoolProvider)
{
	using namespace xercesc;
	const XMLCh t_ls_id [] = { chLatin_L, chLatin_S, chNull };

	// Get an implementation of the Load-Store (LS) interface.
	DOMImplementation* t_impl (DOMImplementationRegistry::getDOMImplementation (t_ls_id));

	std::unique_ptr<xercesc::DOMLSParser, ParserDeleter> t_parser(
			t_impl->createLSParser(
					DOMImplementationLS::MODE_SYNCHRONOUS,
					0,
					XMLPlatformUtils::fgMemoryManager,
					p_grammarPoolProvider.getPool())
			);

	DOMConfiguration * t_conf (t_parser->getDomConfig ());

	// Discard comment nodes in the document.
	t_conf->setParameter (XMLUni::fgDOMComments, false);

	// Enable datatype normalization.
	t_conf->setParameter (XMLUni::fgDOMDatatypeNormalization, true);

	// Do not create EntityReference nodes in the DOM tree. No
	// EntityReference nodes will be created, only the nodes
	// corresponding to their fully expanded substitution text
	// will be created.
	t_conf->setParameter (XMLUni::fgDOMEntities, false);
	// Perform namespace processing.
	t_conf->setParameter (XMLUni::fgDOMNamespaces, true);
	// Do not include ignorable whitespace in the DOM tree.
	t_conf->setParameter (XMLUni::fgDOMElementContentWhitespace, false);

	// Enable validation.
	t_conf->setParameter (XMLUni::fgDOMValidate, p_grammarPoolProvider.getPool() != nullptr);
	t_conf->setParameter (XMLUni::fgXercesSchema, p_grammarPoolProvider.getPool() != nullptr);
	t_conf->setParameter (XMLUni::fgXercesSchemaFullChecking, p_grammarPoolProvider.getPool() != nullptr);

	t_conf->setParameter (XMLUni::fgXercesHandleMultipleImports, true);

	t_conf->setParameter (XMLUni::fgXercesUserAdoptsDOMDocument, true);

	t_conf->setParameter(XMLUni::fgXercesValidationErrorAsFatal, true);

	// Use the loaded grammar during parsing.
	t_conf->setParameter (XMLUni::fgXercesUseCachedGrammarInParse, true);
	// Disable loading schemas via other means (e.g., schemaLocation).
	t_conf->setParameter (XMLUni::fgXercesLoadSchema, false);

	m_parser.swap(t_parser);
}

xercesc::DOMLSParser * XercesParserWrapper::getParser()
{
	return m_parser.get();
}

}
}
