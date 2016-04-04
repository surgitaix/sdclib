/*
 * OperationInvocationContext.cpp
 *
 *  Created on: 05.05.2015
 *      Author: roehser
 */

#include "OSCLib/Data/OSCP/MDIB/OperationInvocationContext.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

OperationInvocationContext::OperationInvocationContext(const std::string & operationHandle, const unsigned int transactionId) :
	operationHandle(operationHandle),
	transactionId(transactionId)
{

}

OperationInvocationContext::~OperationInvocationContext() {

}

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
