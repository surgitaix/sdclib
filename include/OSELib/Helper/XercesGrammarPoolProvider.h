/*
 * XercesGrammarPoolProvider.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#ifndef OSELIB_HELPER_XERCESGRAMMARPOOLPROVIDER_H_
#define OSELIB_HELPER_XERCESGRAMMARPOOLPROVIDER_H_

#include "OSELib/fwd.h"

namespace OSELib
{
    namespace Helper
    {
        class XercesGrammarPoolProvider
		{
        public:
            XercesGrammarPoolProvider() = default;
            // Special Member Functions
            XercesGrammarPoolProvider(const XercesGrammarPoolProvider& p_obj) = delete;
            XercesGrammarPoolProvider(XercesGrammarPoolProvider&& p_obj) = delete;
            XercesGrammarPoolProvider& operator=(const XercesGrammarPoolProvider& p_obj) = delete;
            XercesGrammarPoolProvider& operator=(XercesGrammarPoolProvider&& p_obj) = delete;
            virtual ~XercesGrammarPoolProvider() = default;

            virtual xercesc::XMLGrammarPool * getPool() const { return nullptr; }
        };
    }
}

#endif
