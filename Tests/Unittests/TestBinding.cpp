/*
 * TestBinding.cpp
 *
 *  Created on: 31.01.2013
 *      Author: roehser
 */

#include "OSCLib/OSCL.h"
#include "../UnitTest++/src/UnitTest++.h"

using namespace OSCLib;

SUITE(Basics) {
	TEST(binding) {
		Util::DebugOut(Util::DebugOut::Default, "binding") << "Testing Binding ...";
		{
			Comm::Binding * binding = new Comm::Binding("192.168.0.1", 100);
			binding->setType(Comm::Binding::TCP_HTTP);
			CHECK_EQUAL(std::string("100"), binding->getPortStr());
			CHECK_EQUAL(std::string("http://192.168.0.1:100/"), binding->toString());

			binding->setType(Comm::Binding::UDP);
			CHECK_EQUAL(std::string("soap.udp://192.168.0.1:100/"), binding->toString());

			binding->setType(Comm::Binding::UDP_MULTICAST);
			CHECK_EQUAL(std::string("soap.udp://192.168.0.1:100/"), binding->toString());

			delete binding;
		}

		{
			Comm::Binding * binding = new Comm::Binding("soap.udp://192.168.0.1:100/takeThisPath");
			CHECK_EQUAL(std::string("192.168.0.1"), binding->getIp());
			CHECK_EQUAL(std::string("100"), binding->getPortStr());
			CHECK_EQUAL(Comm::Binding::UDP, binding->getType());
			CHECK_EQUAL(std::string("takeThisPath"), binding->getPath());

			binding->setPath("someOtherPath");
			CHECK_EQUAL(std::string("soap.udp://192.168.0.1:100/someOtherPath"), binding->toString());

			binding->setType(Comm::Binding::TCP_HTTP);
			CHECK_EQUAL(std::string("http://192.168.0.1:100/someOtherPath"), binding->toString());

			delete binding;
		}

		{
			Comm::Binding * binding = new Comm::Binding("soap.udp://192.168.0.1:100");
			CHECK_EQUAL(std::string(""), binding->getPath());
			delete binding;
		}

		{
			Comm::Binding * binding = new Comm::Binding("soap.udp://192.168.0.1:100/");
			CHECK_EQUAL(std::string(""), binding->getPath());
			delete binding;
		}
	}
}

