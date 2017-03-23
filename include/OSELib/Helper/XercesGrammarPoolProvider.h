/*
 * XercesGrammarPoolProvider.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef HELPER_XERCESGRAMMARPOOLPROVIDER_H_
#define HELPER_XERCESGRAMMARPOOLPROVIDER_H_

#include "OSELib/fwd.h"

namespace OSELib {
namespace Helper {

class XercesGrammarPoolProvider {
public:
	XercesGrammarPoolProvider();
	virtual ~XercesGrammarPoolProvider();

	virtual xercesc::XMLGrammarPool * getPool() const;
};

} /* namespace Helper */
} /* namespace OSELib */

#endif /* HELPER_XERCESGRAMMARPOOLPROVIDER_H_ */
