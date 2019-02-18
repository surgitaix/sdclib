/*
 * test_SDCProvider_MdsDescriptor_Versioning_11073_10207_R0034.cpp
 *
 *  Created on: Dec 03, 2018
 *      Author: rosenau
 */
/*
 * Test against requirement R0034 from IEEE 11073-10207 A SERVICE PROVIDER SHALL increment pm:AbstractDescriptor/@DescriptorVersion by
 * 1 if the content of a child ELEMENT or an ATTRIBUTE of the descriptor have changed and if the
 * child ELEMENT itself is not derived from pm:AbstractDescriptor.
 */

#include <iostream>

#include "OSCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/VmdDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/ProductionSpecification.h"
#include "OSCLib/Data/SDC/MDIB/BatteryDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/CodedValue.h"


using namespace SDCLib;
using namespace SDCLib::Data;
using namespace SDCLib::Data::SDC;


int main() {
	std::cout << "Test against requirement 11073-10207-R0034: A SERVICE PROVIDER SHALL increment "
			  << "pm:AbstractDescriptor/@DescriptorVersion by 1 if the content of a child Element "
			  << "or an ATTRIBUTE of the descriptor have changed and if the child Element itself "
			  << "is not derived from pm:AbstractDescriptor."
			  << std::endl;
	MdsDescriptor mdsdescriptor("testMDSDescriptor");
	mdsdescriptor.setDescriptorVersion(0);
	VmdDescriptor vmddescriptor("testVMDDescriptor");
	mdsdescriptor.addVmd(vmddescriptor);
	BatteryDescriptor batterDescriptor("testBatteryDescriptor");
	mdsdescriptor.addBattery(batterDescriptor);
	ProductionSpecification specification(CodedValue("testValue"), "testProductSpecifiactio");
	mdsdescriptor.addProductionSpecification(specification);
	if(mdsdescriptor.getDescriptorVersion() != 3) {
		std::cout << "Version did not increase on adding sub descriptor, Version count: "
				  << mdsdescriptor.getDescriptorVersion()  << std::endl;
		std::cout << "Test failed" << std::endl;
	}
	else {
		mdsdescriptor.clearVmdList();
		mdsdescriptor.clearBatteryList();
		mdsdescriptor.clearProductionSpecificationList();
		if (mdsdescriptor.getDescriptorVersion() == 6) {
			std::cout << "Version did not increase on removing sub descriptor, Version count: "
					  << mdsdescriptor.getDescriptorVersion() << std::endl;
			std::cout << "Test failed" << std::endl;
		}
		else
		{
			std::cout << "Test passed";
		}
	}


}
