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
 * SDCConsumerEventHandler.cpp
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: roehser, besting, buerger
 */

#include "SDCLib/Data/SDC/SDCConsumerOperationInvokedHandler.h"

namespace SDCLib {
namespace Data {
namespace SDC {

SDCConsumerOperationInvokedHandler::SDCConsumerOperationInvokedHandler(const std::string handle):
		descriptorHandle(handle),
		parentConsumer(nullptr)
{

}

SDCConsumerOperationInvokedHandler::~SDCConsumerOperationInvokedHandler() {

}

void SDCConsumerOperationInvokedHandler::onOperationInvoked(const OperationInvocationContext &, InvocationState ) {

}


std::string SDCConsumerOperationInvokedHandler::getDescriptorHandle() {
	return descriptorHandle;
}

SDCConsumer & SDCConsumerOperationInvokedHandler::getParentConsumer() {
	return *parentConsumer;
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */
