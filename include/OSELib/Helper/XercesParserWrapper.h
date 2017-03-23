/*
 * XercesParserWrapper.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef HELPER_XERCESPARSERWRAPPER_H_
#define HELPER_XERCESPARSERWRAPPER_H_

#include <memory>

#include "OSELib/Helper/AutoRelease.h"
#include "OSELib/Helper/XercesGrammarPoolProvider.h"

namespace OSELib {
namespace Helper {

class XercesParserWrapper {
public:
	XercesParserWrapper(const XercesGrammarPoolProvider & grammarPoolProvider);

	xercesc::DOMLSParser * getParser();

private:
	using ParserDeleter = AutoRelease<xercesc::DOMLSParser>;

	std::unique_ptr<xercesc::DOMLSParser, ParserDeleter> _parser;
};

} /* namespace Helper */
} /* namespace OSELib */

#endif /* HELPER_XERCESPARSERWRAPPER_H_ */
