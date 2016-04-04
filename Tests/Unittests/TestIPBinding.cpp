/*
 * TestIPBinding.cpp
 *
 *  Created on: 30.01.2013
 *      Author: roehser
 */

#include "OSCLib/OSCL.h"
#include "../UnitTest++/src/UnitTest++.h"

using namespace OSCLib;

SUITE(Basics) {
	TEST(ipbinding) {
		Util::DebugOut(Util::DebugOut::Default, "ipbinding") << "Testing IPBinding ...";
		{
			Comm::IPBinding * binding = new Comm::IPBinding("192.168.0.1", 100);
			binding->setType(Comm::IPBinding::TCP_HTTP);
			CHECK_EQUAL(std::string("100"), binding->getPortStr());
			CHECK_EQUAL(std::string("http://192.168.0.1:100"), binding->toString());

			binding->setType(Comm::IPBinding::UDP);
			CHECK_EQUAL(std::string("soap.udp://192.168.0.1:100"), binding->toString());

			binding->setType(Comm::IPBinding::UDP_MULTICAST);
			CHECK_EQUAL(std::string("soap.udp://192.168.0.1:100"), binding->toString());
			delete binding;
		}
	}
}

