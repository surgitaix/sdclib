/*
 * XercesGrammarPoolProvider.cpp
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#include <xercesc/framework/XMLGrammarPool.hpp>
#include <xercesc/framework/XMLGrammarPoolImpl.hpp>

#include "OSELib/Helper/XercesGrammarPoolProvider.h"

namespace OSELib {
namespace Helper {

XercesGrammarPoolProvider::XercesGrammarPoolProvider() {
}

XercesGrammarPoolProvider::~XercesGrammarPoolProvider() = default;

xercesc::XMLGrammarPool * XercesGrammarPoolProvider::getPool() const {
	return nullptr;
}

} /* namespace Helper */
} /* namespace OSELib */
