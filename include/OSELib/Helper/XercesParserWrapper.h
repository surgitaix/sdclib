/*
 * XercesParserWrapper.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#ifndef OSELIB_HELPER_XERCESPARSERWRAPPER_H_
#define OSELIB_HELPER_XERCESPARSERWRAPPER_H_

#include "OSELib/Helper/AutoRelease.h"
#include "OSELib/Helper/XercesGrammarPoolProvider.h"

#include <memory>

namespace OSELib
{
	namespace Helper
	{
		class XercesParserWrapper
		{
		private:
			using ParserDeleter = AutoRelease<xercesc::DOMLSParser>;
			std::unique_ptr<xercesc::DOMLSParser, ParserDeleter> m_parser = nullptr;

		public:
			XercesParserWrapper(const XercesGrammarPoolProvider & p_grammarPoolProvider);
			// Special Member Functions
			XercesParserWrapper(const XercesParserWrapper& p_obj) = default;
			XercesParserWrapper(XercesParserWrapper&& p_obj) = default;
			XercesParserWrapper& operator=(const XercesParserWrapper& p_obj) = default;
			XercesParserWrapper& operator=(XercesParserWrapper&& p_obj) = default;
            ~XercesParserWrapper() = default;

			xercesc::DOMLSParser * getParser();
		};
	}
}

#endif
