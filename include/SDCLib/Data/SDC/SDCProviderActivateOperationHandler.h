/*
 * SDCProviderActivateOperationHandler.h
 *
 *  Created on: 23.01.18
 *      Author: buerger, besting, roehser
 *
 *      Use this state hander to implement callbacks from the consumer, i.e. when a switch is pressed / activated.
 *      Use the parents provider findState<>() and findDescriptor<>() functions to get information out of the mdib.
 */

#ifndef SDCPROVIDERACTIVATETOPERATIONSTATEHANDLER_H_
#define SDCPROVIDERACTIVATETOPERATIONSTATEHANDLER_H_

#include "SDCLib/Data/SDC/SDCProviderStateHandler.h"

namespace SDCLib
{
    namespace Data
    {
        namespace SDC
        {
            class SDCProviderActivateOperationHandler : public SDCProviderStateHandler
            {
            public:
                /**
				* @brief The constructor gets a handle as an argument referencing the regarding descriptor of the state
				*/
                explicit SDCProviderActivateOperationHandler(const HandleRef& p_descriptorHandle)
                    : SDCProviderStateHandler(p_descriptorHandle, p_descriptorHandle)
                {
                }

                virtual ~SDCProviderActivateOperationHandler() = default;

                /**
				* @brief Called on incoming consumer request for activation
				*
				* Notes:
				* - The consumer will wait for this method to complete.
				*
				* @return invocation state
				*/
                virtual InvocationState onActivateRequest(const OperationInvocationContext&) = 0;
            };

        }  // namespace SDC
    }      // namespace Data
}  // namespace SDCLib

#endif
