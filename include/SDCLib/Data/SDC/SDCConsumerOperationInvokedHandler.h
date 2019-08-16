/**
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  *
  */

/*
 * SDCConsumerEventHandler.h
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: roehser, besting, buerger
 *
 *  This handler provides the function onOpertionInvoked, which is called each time an incoming message is called each time some operation, like a state change, is invoked by the provider by an incoming message.
 *  It is state independed. Use this one if only information about the invoked operation is needed. To recieve a changed state use: SDCConsumer
 *
 */

#ifndef SDCCONSUMEROPERATIONINVOKEDHANDLER_H_
#define SDCCONSUMEROPERATIONINVOKEDHANDLER_H_

#include <string>
#include "SDCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "SDCLib/Data/SDC/MDIB/MDIB-fwd.h"
#include "SDCLib/Data/SDC/SDCConsumer.h"


namespace SDCLib
{
	namespace Data
	{
		namespace SDC
		{

			class SDCConsumerOperationInvokedHandler
			{
				friend class SDCConsumer;


			protected:
				const std::string descriptorHandle;

				SDCConsumer* parentConsumer = nullptr;


			public:
				SDCConsumerOperationInvokedHandler(std::string handle);

				// Special Member Functions
				SDCConsumerOperationInvokedHandler(const SDCConsumerOperationInvokedHandler& p_obj) = delete;
				SDCConsumerOperationInvokedHandler(SDCConsumerOperationInvokedHandler&& p_obj) = delete;
				SDCConsumerOperationInvokedHandler& operator=(const SDCConsumerOperationInvokedHandler& p_obj) = delete;
				SDCConsumerOperationInvokedHandler& operator=(SDCConsumerOperationInvokedHandler&& p_obj) = delete;
				virtual ~SDCConsumerOperationInvokedHandler() = default;

				/**
				* @brief Receive notifications about the invocation state.
				*
				* @param transactionId The transaction id.
				* @param is The invocation state.
				*/
				virtual void onOperationInvoked(const OperationInvocationContext & oic, InvocationState is) { }

				/**
				* @brief Define the descriptor handle.
				*
				* @return The handle
				*/
				std::string getDescriptorHandle() { return descriptorHandle; }


			    SDCConsumer & getParentConsumer();

			};

		} /* namespace SDC */
	} /* namespace Data */
} /* namespace SDCLib */

#endif /* SDCCONSUMEROPERATIONINVOKEDHANDLER_H_ */
