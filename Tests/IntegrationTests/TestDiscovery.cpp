/*
 * TestDiscovery.cpp
 *
 *  Created on: 30.01.2013
 *      Author: roehser
 */

#include "OSCLib/OSCL.h"
#include "OSCLib/Comm/DPWS/DPWS11Constants.h"
#include "OSCLib/Data/Parameter.h"
#include "../AbstractOSCLibFixture.h"
#include "../UnitTest++/src/UnitTest++.h"

using namespace OSCLib;
using namespace OSCLib::Data;

namespace OSCLib {
namespace Tests {
namespace Discovery {

const std::string MDP_NAMESPACE("http://www.smartOR.de/2012/MedicalDeviceProfile");

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

struct FixtureIdentification : Tests::AbstractOSCLibFixture {
	FixtureIdentification() : AbstractOSCLibFixture("FixtureIdentification", Util::DebugOut::Error, 4000) {}
};

SUITE(Basics) {
TEST_FIXTURE(FixtureIdentification, identification)
{
	try
	{
		// Create device
		Dev::Device device;
		// Add custom endpoint reference
		device.setEPRAddress("urn:uuid:1234");
		// Create TCP binding for device
		std::shared_ptr<Comm::Binding> deviceBinding(new Comm::Binding(OSCLibrary::getInstance()->getBindInterface(), 4500, "ExampleDevice"));
		device.addBinding(Comm::DPWS::DPWS11, deviceBinding);
		// Add type and scope
		device.addType(Data::QName("MedicalDevice", OSCLib::Tests::Discovery::MDP_NAMESPACE));
		device.addScope("http://www.surgitaix.com");

		// Create 1st ID service for device;
		std::shared_ptr<Dev::Service> idService1(new Dev::Service);
		// Create TCP binding for service
		std::shared_ptr<Comm::Binding> serviceBinding1(new Comm::Binding(OSCLibrary::getInstance()->getBindInterface(), 4501, "DeviceIdentification1"));
		idService1->addBinding(Comm::DPWS::DPWS11, serviceBinding1);
		// Add service ID
		idService1->setServiceId("smartORIdentificationService1");

		// Create operations for the service
		std::shared_ptr<Tests::Discovery::OSCBIdentOperation> idOp1(new Tests::Discovery::OSCBIdentOperation);
		idService1->addOperation(idOp1);

		// Add service to device, start service (restarts device)
		device.addService(idService1);
		idService1->start();

		// Create 2nd ID service for device;
		std::shared_ptr<Dev::Service> idService2(new Dev::Service);
		// Create TCP binding for service
		std::shared_ptr<Comm::Binding> serviceBinding2(new Comm::Binding(OSCLibrary::getInstance()->getBindInterface(), 4502, "DeviceIdentification2"));
		idService2->addBinding(Comm::DPWS::DPWS11, serviceBinding2);
		// Add service ID
		idService2->setServiceId("smartORIdentificationService2");

		// Create operations for the service
		std::shared_ptr<Tests::Discovery::OSCBIdentOperation> idOp2(new Tests::Discovery::OSCBIdentOperation);
		idService2->addOperation(idOp2);

		// Add service to device, start service (restarts device)
		device.addService(idService2);
		idService2->start();

		// Start device
		device.start();

		// Create client and search device (no binding)
		Cli::Client client;

		// Simplest method, get all by device EPR
		client.setDeviceEPRAdrSearchParam("urn:uuid:1234");
		client.addDeviceScopeSearchParam("http://www.surgitaix.com");
		bool found = client.searchSync(5000);
		CHECK_EQUAL(true, found);
        CHECK_EQUAL(unsigned(2), client.getRemoteDevice()->getServiceCount());

		client.clearSearchParams();

		// Search for service ID directly
		client.setServiceIDSearchParam("smartORIdentificationService1");
		// Narrow down search by adding additional parameters
		client.addDeviceScopeSearchParam("http://www.surgitaix.com");
		client.addDeviceTypeSearchParam(Data::QName("MedicalDevice", OSCLib::Tests::Discovery::MDP_NAMESPACE));
		client.addServiceTypeSearchParam(Data::QName("DeviceIdentification", OSCLib::Tests::Discovery::MDP_NAMESPACE));
		found = client.searchSync(5000);
		CHECK_EQUAL(true, found);

		if (found)
		{
			// Invoke method two times
			Data::QName portType("DeviceIdentification", OSCLib::Tests::Discovery::MDP_NAMESPACE);
			Parameters params;
			Parameters out;
			bool invokeReturned = client.invokeSync(portType, "getIdentification", params, &out);
			CHECK_EQUAL(true, invokeReturned);
			invokeReturned = client.invokeSync(portType, "getIdentification", params, &out);
			CHECK_EQUAL(true, invokeReturned);

			// Check output parameter
			Parameter friendlyName = out[0];
			CHECK_EQUAL("OSCB Test Device", friendlyName["FriendlyName"].getValue());
			client.close();
		}

		// Create new search, wrong ID
		client.setServiceIDSearchParam("smartORIdentificationServiceWrongId");
		// Narrow down search by adding additional parameters
		client.addDeviceScopeSearchParam("http://www.surgitaix.com");
		client.addDeviceTypeSearchParam(Data::QName("MedicalDevice", OSCLib::Tests::Discovery::MDP_NAMESPACE));
		client.addServiceTypeSearchParam(Data::QName("DeviceIdentification", OSCLib::Tests::Discovery::MDP_NAMESPACE));
		found = client.searchSync(5000);
		CHECK_EQUAL(false, found);

		client.clearSearchParams();

		// Create new search, wrong scopes
		client.setServiceIDSearchParam("smartORIdentificationService1");
		// Narrow down search by adding additional parameters
		client.addDeviceScopeSearchParam("http://www.surgitaix.com");
		client.addDeviceScopeSearchParam("http://www.surgitaix.com/wrongscope");
		client.addDeviceTypeSearchParam(Data::QName("MedicalDevice", OSCLib::Tests::Discovery::MDP_NAMESPACE));
		client.addServiceTypeSearchParam(Data::QName("DeviceIdentification", OSCLib::Tests::Discovery::MDP_NAMESPACE));
		found = client.searchSync(5000);
		CHECK_EQUAL(false, found);

		client.clearSearchParams();

		// Create new search, wrong device types
		client.setServiceIDSearchParam("smartORIdentificationService1");
		// Narrow down search by adding additional parameters
		client.addDeviceScopeSearchParam("http://www.surgitaix.com");
		client.addDeviceTypeSearchParam(Data::QName("MedicalDevice", OSCLib::Tests::Discovery::MDP_NAMESPACE));
		client.addDeviceTypeSearchParam(Data::QName("MedicalDeviceWrongType", OSCLib::Tests::Discovery::MDP_NAMESPACE));
		client.addServiceTypeSearchParam(Data::QName("DeviceIdentification", OSCLib::Tests::Discovery::MDP_NAMESPACE));
		found = client.searchSync(5000);
		CHECK_EQUAL(false, found);

		client.clearSearchParams();

		// Create new search, wrong service types
		client.setServiceIDSearchParam("smartORIdentificationService1");
		// Narrow down search by adding additional parameters
		client.addDeviceScopeSearchParam("http://www.surgitaix.com");
		client.addDeviceTypeSearchParam(Data::QName("MedicalDevice", OSCLib::Tests::Discovery::MDP_NAMESPACE));
		client.addServiceTypeSearchParam(Data::QName("DeviceIdentification", OSCLib::Tests::Discovery::MDP_NAMESPACE));
		client.addServiceTypeSearchParam(Data::QName("DeviceIdentificationWrongType", OSCLib::Tests::Discovery::MDP_NAMESPACE));
		found = client.searchSync(5000);
		CHECK_EQUAL(false, found);

		// Stop client, device and service
		client.close();
		device.stop();
	}
	catch (char const* exc)
	{
		Util::DebugOut(Util::DebugOut::Default, std::cerr, "identification") << exc;
	}
	catch (...)
	{
		Util::DebugOut(Util::DebugOut::Default, std::cerr, "identification") << "Unknown exception occurred!";
	}
}
}
