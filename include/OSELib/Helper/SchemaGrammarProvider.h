/*
 * SchemaGrammarProvider.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#ifndef OSELIB_HELPER_SCHEMAGRAMMARPROVIDER_H_
#define OSELIB_HELPER_SCHEMAGRAMMARPROVIDER_H_

#include "OSELib/fwd.h"
#include "OSELib/Helper/XercesGrammarPoolProvider.h"

#include <memory>

#include <xercesc/framework/XMLGrammarPool.hpp>

namespace OSELib
{
	namespace Helper
	{

		class SchemaGrammarProvider : public XercesGrammarPoolProvider
		{
		private:
			std::unique_ptr<xercesc::XMLGrammarPool> m_pool = nullptr;

		public:
			SchemaGrammarProvider();
			// Special Member Functions
			SchemaGrammarProvider(const SchemaGrammarProvider& p_obj) = delete;
			SchemaGrammarProvider(SchemaGrammarProvider&& p_obj) = delete;
			SchemaGrammarProvider& operator=(const SchemaGrammarProvider& p_obj) = delete;
			SchemaGrammarProvider& operator=(SchemaGrammarProvider&& p_obj) = delete;
			virtual ~SchemaGrammarProvider();

			xercesc::XMLGrammarPool * getPool() const override;

			bool addSchema(const std::string & p_name, const std::string & p_content);

			void seal();

		};
	}
}

#endif
