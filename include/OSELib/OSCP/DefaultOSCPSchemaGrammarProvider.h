/*
 * DefaultOSCPSchemaGrammarProvider.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef OSCP_DEFAULTOSCPSCHEMAGRAMMARPROVIDER_H_
#define OSCP_DEFAULTOSCPSCHEMAGRAMMARPROVIDER_H_

#include "OSELib/Helper/SchemaGrammarProvider.h"
#include "OSELib/Helper/WithLogger.h"

namespace OSELib {
namespace OSCP {

class DefaultOSCPSchemaGrammarProvider : public Helper::SchemaGrammarProvider, public WithLogger {
public:
	DefaultOSCPSchemaGrammarProvider();
	virtual ~DefaultOSCPSchemaGrammarProvider();
};

} /* namespace Helper */
} /* namespace OSELib */

#endif /* OSCP_DEFAULTOSCPSCHEMAGRAMMARPROVIDER_H_ */
