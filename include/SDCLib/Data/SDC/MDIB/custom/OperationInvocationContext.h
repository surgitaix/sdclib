/*
 * OperationInvocationContext.h
 *
 *  Created on: 05.05.2015, roehser
 *  Modified on: 10.09.2019, baumeister
 *
 */

#ifndef SDCLIB_DATA_SDC_OPERATIONINVOCATIONCONTEXT_H_
#define SDCLIB_DATA_SDC_OPERATIONINVOCATIONCONTEXT_H_

#include <string>

namespace SDCLib
{
	namespace Data
	{
		namespace SDC
		{
			class OperationInvocationContext
			{
			public: // TODO: Make private and implement getter
				const std::string operationHandle;
				const unsigned int transactionId = 0;

			public:

				static OperationInvocationContext none() {
					return OperationInvocationContext("", 0);
				}

				OperationInvocationContext(const std::string& p_operationHandle, const unsigned int p_transactionId);
				// Special Member Functions
				OperationInvocationContext(const OperationInvocationContext& p_obj) = default;
				OperationInvocationContext(OperationInvocationContext&& p_obj) = default;
				OperationInvocationContext& operator=(const OperationInvocationContext& p_obj) = delete;
				OperationInvocationContext& operator=(OperationInvocationContext&& p_obj) = delete;
				~OperationInvocationContext() = default;
			};
		}
	}
}

#endif
