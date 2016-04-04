/*
 * TestDiscovery.cpp
 *
 *  Created on: 30.01.2013
 *      Author: roehser
 */

#include "OSCLib/OSCLibrary.h"
#include "OSCLib/Comm/DPWS/DPWS11Constants.h"
#include "OSCLib/Dev/Device.h"
#include "OSCLib/Dev/Service.h"
#include "OSCLib/Util/DebugOut.h"
#include "../AbstractOSCLibFixture.h"
#include "../UnitTest++/src/UnitTest++.h"

using namespace OSCLib;
using namespace OSCLib::Comm::DPWS;

struct FixtureAutobinding : Tests::AbstractOSCLibFixture {
	FixtureAutobinding() : AbstractOSCLibFixture("FixtureAutobinding", Util::DebugOut::Error, 1024) {}
};

SUITE(Basics) {
TEST_FIXTURE(FixtureAutobinding, autobinding)
{
	const std::string MDP_NAMESPACE("http://www.smartOR.de/2012/MedicalDeviceProfile");

	try
	{
		// Create device
		Dev::Device device;
		// Add custom endpoint reference
		device.setEPRAddress("TestDeviceId1");
		device.addType(Data::QName("MedicalDevice", MDP_NAMESPACE));
		device.addScope("http://www.surgitaix.com");

		// Create service for device;
		std::shared_ptr<Dev::Service> service(new Dev::Service);
		// Add service ID
		service->setServiceId("TestServiceId1");
		device.addService(service);
		// Start device
		device.start();
		CHECK_EQUAL(size_t(2), device.getProtocolBindings().find(DPWS11)->second.size());
		CHECK_EQUAL(size_t(1), service->getProtocolBindings().find(DPWS11)->second.size());
		// Stop device
		device.stop();
	}
	catch (char const * exc)
	{
		Util::DebugOut(Util::DebugOut::Default, std::cerr, "autobinding") << exc;
	}
	catch (...)
	{
		Util::DebugOut(Util::DebugOut::Default, std::cerr, "autobinding") << "Unknown exception occurred!";
	}
}
}
