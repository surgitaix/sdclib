/*
 * OperationInvocationContext.h
 *
 *  Created on: 05.05.2015
 *      Author: roehser
 */

#ifndef DATA_OSCP_MDIB_OPERATIONINVOCATIONCONTEXT_H_
#define DATA_OSCP_MDIB_OPERATIONINVOCATIONCONTEXT_H_

#include <string>

namespace OSCLib {
namespace Data {
namespace OSCP {

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

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

#endif /* DATA_OSCP_MDIB_OPERATIONINVOCATIONCONTEXT_H_ */
