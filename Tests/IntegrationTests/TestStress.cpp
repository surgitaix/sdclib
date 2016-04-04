/*
 * TestStress.cpp
 *
 *  Created on: 30.01.2013
 *      Author: roehser
 */

#include "OSCLib/OSCL.h"
#include "OSCLib/Comm/DPWS/DPWS11Constants.h"
#include "OSCLib/Data/Parameter.h"
#include "OSCLib/Util/DebugOut.h"
#include "../AbstractOSCLibFixture.h"
#include "../UnitTest++/src/UnitTest++.h"
#include "Poco/Thread.h"

using namespace OSCLib;
using namespace OSCLib::Data;

namespace OSCLib {
namespace Tests {
namespace Stress {

const std::string DEFAULT_NAMESPACE("http://www.surgitaix.com/example");
const std::string MDP_NAMESPACE("http://www.smartOR.de/2012/MedicalDeviceProfile");

class DiscoveryClient : public Cli::Client {
public:

	DiscoveryClient() : Client()
	{
		addDeviceTypeSearchParam(Data::QName("TestDevice", DEFAULT_NAMESPACE));
		search();
	}

    size_t getDeviceListSize() {
        return getClients().size() + 1;
    }

};

class OSCBIdentOperation : public Data::Operation {
public:

	OSCBIdentOperation() {
	    setName("getIdentification");
	    Data::QName pType("DeviceIdentification", MDP_NAMESPACE);
	    setPortType(pType);
		Parameter pOutDef("MedicalDevice");
		pOutDef["FriendlyName"].setType(Parameter::Type::STRING).setMaxOccurs(-1);
		pOutDef["SerialNumber"].setType(Parameter::Type::STRING);
		pOutDef["FirmwareVersion"].setType(Parameter::Type::STRING);
		pOutDef["HardwareVersion"].setType(Parameter::Type::STRING);
		pOutDef["SoftwareVersion"].setType(Parameter::Type::STRING);
		addOutputParameter(pOutDef);
	}

	Parameters invoke(Parameters & ) {
		Parameters returnParams;
		Parameter pOut("MedicalDevice");
		pOut["FriendlyName"].setValue("OSCB Test Device");
		pOut["SerialNumber"].setValue("12345ABDC");
		pOut["FirmwareVersion"].setValue("1.0");
		pOut["HardwareVersion"].setValue("1.1");
		pOut["SoftwareVersion"].setValue("1.2");
		returnParams.push_back(pOut);
		return returnParams;
	}
};

}
}
}

struct FixtureStress : Tests::AbstractOSCLibFixture {
	FixtureStress() : AbstractOSCLibFixture("FixtureStress", Util::DebugOut::Error, 7000) {}
};

SUITE(Advanced){
TEST_FIXTURE(FixtureStress, stress)
{
	try
	{
		size_t numberOfDevices = 8;
		size_t numberOfServices = 4;

		std::vector<std::shared_ptr<Dev::Device>> devices;
		
		for (size_t i = 0; i < numberOfDevices; i++)
		{
			// Create device
			std::shared_ptr<Dev::Device> device(new Dev::Device());
			devices.push_back(device);
			// Add custom endpoint reference
			std::ostringstream ssd;
			ssd << "urn:uuid:1234";
			ssd << i;
			device->setEPRAddress(ssd.str());
			// Create binding for device
			std::shared_ptr<Comm::Binding> deviceBinding(new Comm::Binding(OSCLibrary::getInstance()->getBindInterface(), OSCLibrary::getInstance()->extractNextPort() + 100, "TestDevice"));
			device->addBinding(Comm::DPWS::DPWS11, deviceBinding);
			// Add type and scope
			device->addType(Data::QName("TestDevice", OSCLib::Tests::Stress::DEFAULT_NAMESPACE));
			device->addScope("http://www.surgitaix.com");

			for (size_t j = 0; j < numberOfServices; j++)
			{
				// Create ID service for device;
				std::shared_ptr<Dev::Service> service(new Dev::Service());
				// Create HTTP binding for service
				std::shared_ptr<Comm::Binding> serviceBinding(new Comm::Binding(OSCLibrary::getInstance()->getBindInterface(), OSCLibrary::getInstance()->extractNextPort(), "TestService"));
				service->addBinding(Comm::DPWS::DPWS11, serviceBinding);
				std::shared_ptr<Tests::Stress::OSCBIdentOperation> idOp(new Tests::Stress::OSCBIdentOperation());
				service->addOperation(idOp);
				// Add service ID
				std::ostringstream ssid;
				ssid << "TestServiceId";
				ssid << i << "." << j;
				service->setServiceId(ssid.str());
				device->addService(service);
			}

			device->start();
		}
       
        // Find all
		Tests::Stress::DiscoveryClient discoveryClient;
		Poco::Thread::sleep(10000);
		CHECK_EQUAL(numberOfDevices, discoveryClient.getDeviceListSize());
		discoveryClient.close(true);

        // Find one
        Cli::Client client;
        client.setServiceIDSearchParam("TestServiceId4.2");
        client.search();
        Poco::Thread::sleep(5000);
        CHECK_EQUAL(true, client.foundAny());

        client.close(true);

		for (unsigned int i = 0; i < devices.size(); i++)
			devices[i]->stop();
	}
	catch (char const* exc)
	{
		Util::DebugOut(Util::DebugOut::Default, std::cerr, "stress") << exc;
	}
	catch (...)
	{
		Util::DebugOut(Util::DebugOut::Default, std::cerr, "stress") << "Unknown exception occurred!";
	}
}
}
