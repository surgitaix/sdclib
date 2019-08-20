/*
 * DefaultSDCSchemaGrammarProvider.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef OSELIB_SDC_DEFAULTSDCSCHEMAGRAMMARPROVIDER_H_
#define OSELIB_SDC_DEFAULTSDCSCHEMAGRAMMARPROVIDER_H_

#include "OSELib/Helper/SchemaGrammarProvider.h"
#include "OSELib/Helper/WithLogger.h"

namespace OSELib {
namespace SDC {

class DefaultSDCSchemaGrammarProvider : public Helper::SchemaGrammarProvider, public OSELib::Helper::WithLogger {
public:
	DefaultSDCSchemaGrammarProvider();
	virtual ~DefaultSDCSchemaGrammarProvider();
};

} /* namespace Helper */
} /* namespace OSELib */

#endif /* OSELIB_SDC_DEFAULTSDCSCHEMAGRAMMARPROVIDER_H_ */
