/*
 * XercesGrammarPoolProvider.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef OSELIB_HELPER_XERCESGRAMMARPOOLPROVIDER_H_
#define OSELIB_HELPER_XERCESGRAMMARPOOLPROVIDER_H_

#include "OSELib/fwd.h"

namespace OSELib
{
    namespace Helper
    {

        class XercesGrammarPoolProvider {
        public:
            XercesGrammarPoolProvider() = default;
            virtual ~XercesGrammarPoolProvider() = default;

            virtual xercesc::XMLGrammarPool * getPool() const { return nullptr; }
        };

    } /* namespace Helper */
} /* namespace OSELib */

#endif /* HELPER_XERCESGRAMMARPOOLPROVIDER_H_ */
