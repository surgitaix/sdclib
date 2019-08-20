/*
 * SchemaGrammarProvider.cpp
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLUniDefs.hpp>
#include <xercesc/framework/Wrapper4InputSource.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/framework/XMLGrammarPoolImpl.hpp>
#include <xercesc/validators/common/Grammar.hpp>

#include "OSELib/Helper/SchemaGrammarProvider.h"
#include "OSELib/Helper/XercesParserWrapper.h"

namespace OSELib {
namespace Helper {

SchemaGrammarProvider::SchemaGrammarProvider() :
	_pool(new xercesc::XMLGrammarPoolImpl(xercesc::XMLPlatformUtils::fgMemoryManager))
{
}

SchemaGrammarProvider::~SchemaGrammarProvider() {
	_pool->unlockPool();
	_pool->clear();
}

xercesc::XMLGrammarPool * SchemaGrammarProvider::getPool() const {
	return _pool.get();
}

bool SchemaGrammarProvider::addSchema(const std::string & name, const std::string & content) {
	XercesParserWrapper parser(*this);

	xercesc::MemBufInputSource contentSource((const XMLByte*)content.c_str(), content.size(), name.c_str());
	xercesc::Wrapper4InputSource wrapextensionstream (&contentSource, false);

	if (!parser.getParser()->loadGrammar (&wrapextensionstream, xercesc::Grammar::SchemaGrammarType, true)) {
		return false;
	}

	return true;
}

void SchemaGrammarProvider::seal() {
	_pool->lockPool();
}

} /* namespace Helper */
} /* namespace OSELib */
