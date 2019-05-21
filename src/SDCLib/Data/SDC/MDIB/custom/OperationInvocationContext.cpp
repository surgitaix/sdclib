/*
 * OperationInvocationContext.cpp
 *
 *  Created on: 05.05.2015
 *      Author: roehser
 */

#include "SDCLib/Data/SDC/MDIB/custom/OperationInvocationContext.h"

namespace SDCLib {
namespace Data {
namespace SDC {

OperationInvocationContext::OperationInvocationContext(const std::string & operationHandle, const unsigned int transactionId) :
	operationHandle(operationHandle),
	transactionId(transactionId)
{

}

OperationInvocationContext::~OperationInvocationContext() {

}

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */
