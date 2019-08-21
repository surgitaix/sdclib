/*
 * SchemaGrammarProvider.cpp
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#include "OSELib/Helper/SchemaGrammarProvider.h"
#include "OSELib/Helper/XercesParserWrapper.h"

#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLUniDefs.hpp>
#include <xercesc/framework/Wrapper4InputSource.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/framework/XMLGrammarPoolImpl.hpp>
#include <xercesc/validators/common/Grammar.hpp>


namespace OSELib {
namespace Helper {

SchemaGrammarProvider::SchemaGrammarProvider()
: m_pool(new xercesc::XMLGrammarPoolImpl(xercesc::XMLPlatformUtils::fgMemoryManager))
{ }

SchemaGrammarProvider::~SchemaGrammarProvider()
{
	m_pool->unlockPool();
	m_pool->clear();
}

xercesc::XMLGrammarPool * SchemaGrammarProvider::getPool() const
{
	return m_pool.get();
}

bool SchemaGrammarProvider::addSchema(const std::string & p_name, const std::string & p_content)
{
	XercesParserWrapper parser(*this);

	xercesc::MemBufInputSource t_contentSource((const XMLByte*)p_content.c_str(), p_content.size(), p_name.c_str());
	xercesc::Wrapper4InputSource t_wrapextensionstream (&t_contentSource, false);

	if (!parser.getParser()->loadGrammar(&t_wrapextensionstream, xercesc::Grammar::SchemaGrammarType, true)) {
		return false;
	}
	return true;
}

void SchemaGrammarProvider::seal()
{
	m_pool->lockPool();
}

}
}
