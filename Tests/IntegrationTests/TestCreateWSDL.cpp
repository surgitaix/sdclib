/*
 * TestCreateWSDL.cpp
 *
 *  Created on: 30.01.2013
 *      Author: roehser
 */

#include "OSCLib/OSCL.h"
#include "OSCLib/Comm/DPWS/DPWS11Constants.h"
#include "OSCLib/Comm/DPWS/DPWS11Message.h"
#include "OSCLib/Data/Parameter.h"
#include "../AbstractOSCLibFixture.h"
#include "../UnitTest++/src/UnitTest++.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace OSCLib;
using namespace OSCLib::Data;

namespace OSCLib {
namespace Tests {
namespace CreateWSDL {

const std::string MDP_NAMESPACE("http://www.smartOR.de/2012/MedicalDeviceProfile");

std::vector<std::string> incomingWSDLs;
std::vector<std::string> requiredWSDLs;

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

struct FixtureWSDL : Tests::AbstractOSCLibFixture {
	FixtureWSDL() : AbstractOSCLibFixture("FixtureWSDL", Util::DebugOut::Error, 3000)
	{
		Data::QName::autoPrefix = 1;
		// These WSDLS are substrings (soap:address location stripped)
		Tests::CreateWSDL::requiredWSDLs.push_back("<wsdl:definitions targetNamespace=\"http://www.smartOR.de/2012/MedicalDeviceProfile\" xmlns=\"http://schemas.xmlsoap.org/wsdl/\" xmlns:tns=\"http://www.smartOR.de/2012/MedicalDeviceProfile\" xmlns:wsdl=\"http://schemas.xmlsoap.org/wsdl/\" xmlns:s12=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:xs=\"http://www.w3.org/2001/XMLSchema\" xmlns:wsa=\"http://www.w3.org/2005/08/addressing\" xmlns:wse=\"http://schemas.xmlsoap.org/ws/2004/08/eventing\" xmlns:soap=\"http://schemas.xmlsoap.org/wsdl/soap12/\"><wsdl:types><xs:schema targetNamespace=\"http://www.smartOR.de/2012/MedicalDeviceProfile\" elementFormDefault=\"qualified\" attributeFormDefault=\"unqualified\" xmlns:xs=\"http://www.w3.org/2001/XMLSchema\"><xs:complexType name=\"MedicalDeviceType\"><xs:sequence><xs:element name=\"FriendlyName\" maxOccurs=\"unbounded\" type=\"xs:string\"/><xs:element name=\"SerialNumber\" type=\"xs:string\"/><xs:element name=\"FirmwareVersion\" type=\"xs:string\"/><xs:element name=\"HardwareVersion\" type=\"xs:string\"/><xs:element name=\"SoftwareVersion\" type=\"xs:string\"/></xs:sequence></xs:complexType><xs:element name=\"MedicalDevice\" type=\"xs:MedicalDeviceType\"/></xs:schema></wsdl:types><wsdl:message name=\"getIdentificationMessage\"/><wsdl:message name=\"getIdentificationResponseMessage\" xmlns:i3=\"http://www.smartOR.de/2012/MedicalDeviceProfile\"><wsdl:part name=\"parameters\" element=\"i3:MedicalDevice\"/></wsdl:message><wsdl:portType name=\"DeviceIdentification\"><wsdl:operation name=\"getIdentification\"><wsdl:input message=\"tns:getIdentificationMessage\" wsa:Action=\"http://www.smartOR.de/2012/MedicalDeviceProfile/DeviceIdentification/getIdentification\"/><wsdl:output message=\"tns:getIdentificationResponseMessage\" wsa:Action=\"http://www.smartOR.de/2012/MedicalDeviceProfile/DeviceIdentification/getIdentificationResponse\"/></wsdl:operation></wsdl:portType><wsdl:binding name=\"DeviceIdentificationBinding1\" type=\"tns:DeviceIdentification\"><soap:binding style=\"document\" transport=\"http://schemas.xmlsoap.org/soap/http\"/><wsdl:operation name=\"getIdentification\"><soap:operation soapAction=\"\"/><wsdl:input><soap:body use=\"literal\"/></wsdl:input><wsdl:output><soap:body use=\"literal\"/></wsdl:output></wsdl:operation></wsdl:binding><wsdl:service name=\"smartORIdentificationService1\"><wsdl:port name=\"DeviceIdentificationPort\" binding=\"tns:DeviceIdentificationBinding1\">");
		Tests::CreateWSDL::requiredWSDLs.push_back("<wsdl:definitions targetNamespace=\"http://www.smartOR.de/2012/MedicalDeviceProfile\" xmlns=\"http://schemas.xmlsoap.org/wsdl/\" xmlns:tns=\"http://www.smartOR.de/2012/MedicalDeviceProfile\" xmlns:wsdl=\"http://schemas.xmlsoap.org/wsdl/\" xmlns:s12=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:xs=\"http://www.w3.org/2001/XMLSchema\" xmlns:wsa=\"http://www.w3.org/2005/08/addressing\" xmlns:wse=\"http://schemas.xmlsoap.org/ws/2004/08/eventing\" xmlns:soap=\"http://schemas.xmlsoap.org/wsdl/soap12/\"><wsdl:types><xs:schema targetNamespace=\"http://www.smartOR.de/2012/MedicalDeviceProfile\" elementFormDefault=\"qualified\" attributeFormDefault=\"unqualified\" xmlns:xs=\"http://www.w3.org/2001/XMLSchema\"><xs:complexType name=\"MedicalDeviceType\"><xs:sequence><xs:element name=\"FriendlyName\" maxOccurs=\"unbounded\" type=\"xs:string\"/><xs:element name=\"SerialNumber\" type=\"xs:string\"/><xs:element name=\"FirmwareVersion\" type=\"xs:string\"/><xs:element name=\"HardwareVersion\" type=\"xs:string\"/><xs:element name=\"SoftwareVersion\" type=\"xs:string\"/></xs:sequence></xs:complexType><xs:element name=\"MedicalDevice\" type=\"xs:MedicalDeviceType\"/></xs:schema></wsdl:types><wsdl:message name=\"getIdentificationMessage\"/><wsdl:message name=\"getIdentificationResponseMessage\" xmlns:i17=\"http://www.smartOR.de/2012/MedicalDeviceProfile\"><wsdl:part name=\"parameters\" element=\"i17:MedicalDevice\"/></wsdl:message><wsdl:portType name=\"DeviceIdentification\"><wsdl:operation name=\"getIdentification\"><wsdl:input message=\"tns:getIdentificationMessage\" wsa:Action=\"http://www.smartOR.de/2012/MedicalDeviceProfile/DeviceIdentification/getIdentification\"/><wsdl:output message=\"tns:getIdentificationResponseMessage\" wsa:Action=\"http://www.smartOR.de/2012/MedicalDeviceProfile/DeviceIdentification/getIdentificationResponse\"/></wsdl:operation></wsdl:portType><wsdl:binding name=\"DeviceIdentificationBinding1\" type=\"tns:DeviceIdentification\"><soap:binding style=\"document\" transport=\"http://schemas.xmlsoap.org/soap/http\"/><wsdl:operation name=\"getIdentification\"><soap:operation soapAction=\"\"/><wsdl:input><soap:body use=\"literal\"/></wsdl:input><wsdl:output><soap:body use=\"literal\"/></wsdl:output></wsdl:operation></wsdl:binding><wsdl:service name=\"smartORIdentificationService2\"><wsdl:port name=\"DeviceIdentificationPort\" binding=\"tns:DeviceIdentificationBinding1\">");
	}
};

SUITE(Basics) {
TEST_FIXTURE(FixtureWSDL, createwsdl)
{
	try
	{
		// Create device
		Dev::Device device;
		// Add custom endpoint reference
		device.setEPRAddress("urn:uuid:1234");
		// Create TCP binding for device
		std::shared_ptr<Comm::Binding> deviceBinding(new Comm::Binding(OSCLibrary::getInstance()->getBindInterface(), 3500, "ExampleDevice"));
		//deviceBinding.setType(Binding::UDP);
		device.addBinding(Comm::DPWS::DPWS11, deviceBinding);
		// Add type and scope
		device.addType(Data::QName("MedicalDevice", OSCLib::Tests::CreateWSDL::MDP_NAMESPACE));
		device.addScope("http://www.surgitaix.com");

		// Create 1st ID service for device;
		std::shared_ptr<Dev::Service> idService1(new Dev::Service);
		// Create TCP binding for service
		std::shared_ptr<Comm::Binding> serviceBinding1(new Comm::Binding(OSCLibrary::getInstance()->getBindInterface(), 3501, "DeviceIdentification1"));
		//serviceBinding.setType(Binding::UDP);
		idService1->addBinding(Comm::DPWS::DPWS11, serviceBinding1);
		// Add service ID
		idService1->setServiceId("smartORIdentificationService1");

		// Create operations for the service
		std::shared_ptr<Tests::CreateWSDL::OSCBIdentOperation> idOp1(new Tests::CreateWSDL::OSCBIdentOperation);
		idService1->addOperation(idOp1);

		// Add service to device, start service (restarts device)
		device.addService(idService1);
		idService1->start();

		// Create 2nd ID service for device;
		std::shared_ptr<Dev::Service> idService2(new Dev::Service);
		// Create TCP binding for service
		std::shared_ptr<Comm::Binding> serviceBinding2(new Comm::Binding(OSCLibrary::getInstance()->getBindInterface(), 3502, "DeviceIdentification2"));
		//serviceBinding.setType(Binding::UDP);
		idService2->addBinding(Comm::DPWS::DPWS11, serviceBinding2);
		// Add service ID
		idService2->setServiceId("smartORIdentificationService2");

		// Create operations for the service
		std::shared_ptr<Tests::CreateWSDL::OSCBIdentOperation> idOp2(new Tests::CreateWSDL::OSCBIdentOperation);
		idService2->addOperation(idOp2);

		// Add service to device, start service (restarts device)
		device.addService(idService2);
		idService2->start();

		// Start device
		device.start();

		// Create client and search device (no binding)
		Cli::Client client;
		client.initWSDLCollector();

		// Simplest method, get all by device EPR
		client.setDeviceEPRAdrSearchParam("urn:uuid:1234");
		client.addDeviceScopeSearchParam("http://www.surgitaix.com");
		bool found = client.searchSync(5000);
		CHECK_EQUAL(true, found);
		CHECK_EQUAL(unsigned(2), client.getRemoteDevice()->getServiceCount());

		// Check for correct WSDLs substring
		std::vector<std::string> recWSDLs = client.getWSDL();
		for (auto &nextWSDL : recWSDLs) {
			size_t addrPos = nextWSDL.find("<soap:address location");
			if (addrPos != std::string::npos) {
				Tests::CreateWSDL::incomingWSDLs.push_back(nextWSDL.substr(0, addrPos));
			}
		}

		std::vector<std::string>::iterator requiredIt;
		bool failedTest = false;
		for (requiredIt = Tests::CreateWSDL::requiredWSDLs.begin(); requiredIt != Tests::CreateWSDL::requiredWSDLs.end(); ++requiredIt) {
			std::string requiredString = *requiredIt;
			bool testResult = std::find(Tests::CreateWSDL::incomingWSDLs.begin(), Tests::CreateWSDL::incomingWSDLs.end(), requiredString) != Tests::CreateWSDL::incomingWSDLs.end();
			CHECK_EQUAL(true, testResult);
			failedTest |= !testResult;
		}

		// Verbose output
		if (failedTest) {
			Util::DebugOut(Util::DebugOut::Default, std::cerr, "createwsdl") << "WSDL mismatch. Expected WSDLs: ";
			std::vector<std::string>::iterator it;
			for (it = Tests::CreateWSDL::requiredWSDLs.begin(); it != Tests::CreateWSDL::requiredWSDLs.end(); ++it) {
				Util::DebugOut(Util::DebugOut::Default, std::cerr, "createwsdl") << *it;
			}

			Util::DebugOut(Util::DebugOut::Default, std::cerr, "createwsdl") << "Received WSDLs: ";
			for (it = Tests::CreateWSDL::incomingWSDLs.begin(); it != Tests::CreateWSDL::incomingWSDLs.end(); ++it) {
				Util::DebugOut(Util::DebugOut::Default, std::cerr, "createwsdl") << *it;
			}
		}

		// Stop client, device and service
		client.close();
		device.stop();
	}
	catch (char const* exc)
	{
		Util::DebugOut(Util::DebugOut::Default, std::cerr, "createwsdl") << exc;
	}
	catch (...)
	{
		Util::DebugOut(Util::DebugOut::Default, std::cerr, "createwsdl") << "Unknown exception occurred!";
	}
}
}
