/*
 * OperationInvocationContext.h
 *
 *  Created on: 05.05.2015
 *      Author: roehser
 */

#ifndef SDCLIB_DATA_SDC_OPERATIONINVOCATIONCONTEXT_H_
#define SDCLIB_DATA_SDC_OPERATIONINVOCATIONCONTEXT_H_

#include <string>

namespace SDCLib {
namespace Data {
namespace SDC {

class OperationInvocationContext {
public:

	static OperationInvocationContext none() {
		return OperationInvocationContext("", 0);
	}

	OperationInvocationContext(const std::string & operationHandle, const unsigned int transactionId);
	virtual ~OperationInvocationContext();

	const std::string operationHandle;
	const unsigned int transactionId;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

#endif /* SDCLIB_DATA_SDC_OPERATIONINVOCATIONCONTEXT_H_ */
