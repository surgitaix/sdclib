/*
 * SchemaGrammarProvider.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef HELPER_SCHEMAGRAMMARPROVIDER_H_
#define HELPER_SCHEMAGRAMMARPROVIDER_H_

#include <memory>

#include <xercesc/framework/XMLGrammarPool.hpp>

#include "OSELib/fwd.h"
#include "OSELib/Helper/XercesGrammarPoolProvider.h"

namespace OSELib {
namespace Helper {

class SchemaGrammarProvider : public XercesGrammarPoolProvider {
public:
	SchemaGrammarProvider();
	virtual ~SchemaGrammarProvider();

	virtual xercesc::XMLGrammarPool * getPool() const override;

	bool addSchema(const std::string & name, const std::string & content);

	void seal();

private:
	std::unique_ptr<xercesc::XMLGrammarPool> _pool;
};

} /* namespace Helper */
} /* namespace OSELib */

#endif /* HELPER_SCHEMAGRAMMARPROVIDER_H_ */
