/*
 * DefaultSDCSchemaGrammarProvider.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#ifndef OSELIB_SDC_DEFAULTSDCSCHEMAGRAMMARPROVIDER_H_
#define OSELIB_SDC_DEFAULTSDCSCHEMAGRAMMARPROVIDER_H_

#include "OSELib/Helper/SchemaGrammarProvider.h"
#include "OSELib/Helper/WithLogger.h"

namespace OSELib
{
	namespace SDC
	{

		class DefaultSDCSchemaGrammarProvider : public Helper::SchemaGrammarProvider, public OSELib::Helper::WithLogger
		{
		public:
			DefaultSDCSchemaGrammarProvider();
			// Special Member Functions
			DefaultSDCSchemaGrammarProvider(const DefaultSDCSchemaGrammarProvider& p_obj) = delete;
			DefaultSDCSchemaGrammarProvider(DefaultSDCSchemaGrammarProvider&& p_obj) = delete;
			DefaultSDCSchemaGrammarProvider& operator=(const DefaultSDCSchemaGrammarProvider& p_obj) = delete;
			DefaultSDCSchemaGrammarProvider& operator=(DefaultSDCSchemaGrammarProvider&& p_obj) = delete;
			virtual ~DefaultSDCSchemaGrammarProvider() = default;
		};
	}
}

#endif
