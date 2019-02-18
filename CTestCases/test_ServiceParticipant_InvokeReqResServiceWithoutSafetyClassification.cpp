/*
 * test_ServiceParticipant_InvokeReqResServiceWithoutSafetyClassification.cpp
 *
 *  Created on: Feb 12, 2019
 *      Author: rosenau
 */

#include <iostream>
#include "OSCLib/SDCLibrary.h"
#include "OSCLib/Data/SDC/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/MdDescription.h"
#include "OSCLib/Data/SDC/MDIB/MdState.h"
#include "OSCLib/Data/SDC/MDIB/Mdib.h"

#include "OSCLib/Data/SDC/SDCConsumer.h"
#include "OSCLib/Data/SDC/SDCProvider.h"

using namespace SDCLib;
using namespace SDCLib::Data::SDC;

int main() {
	std::cout << "Test against requirement 11073-20701-R0029: An SDC SERVICE CONSUMER SHALL "
			  << "not invoke a REQUEST-RESPONSE SERVICE OPERATION associated with a "
			  << "pm:AbstractOperationDescriptor that does not contain specific "
			  << "pm:AbstractOperationDescriptor/@SafetyClassification."
			  << std::endl;

	SDCLibrary::getInstance().startup(OSELib::LogLevel::Error);
	SDCLibrary::getInstance().setIP6enabled(false);
	SDCLibrary::getInstance().setIP4enabled(true);

	SDCProvider provider();

	ChannelDescriptor deviceParameters("d");

}

