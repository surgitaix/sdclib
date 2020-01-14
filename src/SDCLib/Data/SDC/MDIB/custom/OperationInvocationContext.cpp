/*
 * OperationInvocationContext.cpp
 *
 *  Created on: 05.05.2015, roehser
 *  Modified on: 10.09.2019, baumeister
 *
 */

#include "SDCLib/Data/SDC/MDIB/custom/OperationInvocationContext.h"

namespace SDCLib {
namespace Data {
namespace SDC {

OperationInvocationContext::OperationInvocationContext(const std::string& p_operationHandle, const unsigned int p_transactionId)
: operationHandle(p_operationHandle)
, transactionId(p_transactionId)
{ }

}
}
}
