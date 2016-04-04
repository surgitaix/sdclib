/*
 * TestServiceInvoke.cpp
 *
 *  Created on: 30.01.2013
 *      Author: roehser
 */

#include "OSCLib/OSCL.h"
#include "OSCLib/Comm/DPWS/DPWS11Constants.h"
#include "OSCLib/Data/Parameter.h"
#include "../AbstractOSCLibFixture.h"
#include "../UnitTest++/src/UnitTest++.h"

#include <ctime>

#include "Poco/Mutex.h"
#include "Poco/ScopedLock.h"
#include "Poco/Thread.h"

using namespace OSCLib;
using namespace OSCLib::Data;

namespace OSCLib {
namespace Tests {
namespace ServiceInvoke {

const std::string DEFAULT_NAMESPACE("http://www.surgitaix.com/example");
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

class SumOperation : public Data::Operation {
public:

	SumOperation() {
		// The operation's name
		setName("GetSum");
		// The port type
		Data::QName pType("MedicalService1", DEFAULT_NAMESPACE);
		setPortType(pType);
		// Input parameters
		Parameter p1("InValue1", Parameter::Type::INT);
		Parameter p2("InValue2", Parameter::Type::INT);
		addInputParameter(p1);
		addInputParameter(p2);
		// Output parameter
		Parameter p3("OutValue", Parameter::Type::INT);
		addOutputParameter(p3);
	}

	Parameters invoke(Parameters & p) {
		// Convert input parameters to int
		int i1 = atoi(p[0].getValue().c_str());
		int i2 = atoi(p[1].getValue().c_str());
		// Sum up
		int r = i1 + i2;
		// Convert int result back to string
		Parameter result("OutValue");
		std::ostringstream s;
		s << r;
		// Set output
		Parameters returnParams(getOutput());
		(&returnParams[0])->setValue(s.str());
		return returnParams;
	}
};

class SubOperation : public Data::Operation {
public:

	SubOperation() {
		// The operation's name
		setName("GetSub");
		// The port type
		Data::QName pType("MedicalService2", DEFAULT_NAMESPACE);
		setPortType(pType);
		// Input parameters
		Parameter p1("InValue1", Parameter::Type::INT);
		Parameter p2("InValue2", Parameter::Type::INT);
		addInputParameter(p1);
		addInputParameter(p2);
		// Output parameter
		Parameter p3("OutValue", Parameter::Type::INT);
		addOutputParameter(p3);
	}

	Parameters invoke(Parameters & p) {
		// Convert input parameters to int
		int i1 = atoi(p[0].getValue().c_str());
		int i2 = atoi(p[1].getValue().c_str());
		// Subtract
		int r = i1 - i2;
		// Convert int result back to string
		Parameter result("OutValue");
		std::ostringstream s;
		s << r;
		// Set output
		Parameters returnParams(getOutput());
		(&returnParams[0])->setValue(s.str());
		return returnParams;
	}
};

class CustomClient : public Cli::Client {
public:

	CustomClient() : Client(), searchOk(false), invokeOk(false), result(""),
		start(0), finish(0)
	{
		setServiceIDSearchParam("ExampleServiceId");
	}

    void searchComplete() {
    	{
			Poco::Mutex::ScopedLock lock(mutex);
			// Invoke method
			searchOk = true;
			start = clock();
			if (invokeOk)
				return;
    	}

    	Data::QName portType("MedicalService1", DEFAULT_NAMESPACE);
		Parameters params;
		params.push_back(Parameter("InValue1", Parameter::Type::INT, "1"));
		params.push_back(Parameter("InValue2", Parameter::Type::INT, "2"));
		Poco::Mutex::ScopedLock lock(mutex);
		Parameters out;
		invokeOk = invokeSync(portType, "GetSum", params, &out);
		finish = clock();
		if (!invokeOk)
			return;
		result = out[0].getValue();
    }

	bool getSearchOk() {
		Poco::Mutex::ScopedLock lock(mutex);
		return searchOk;
	}

	bool getInvokeOk() {
		Poco::Mutex::ScopedLock lock(mutex);
		return invokeOk;
	}

	std::string getResult() {
		Poco::Mutex::ScopedLock lock(mutex);
		return result;
	}

	double getElapsedTime() {
		Poco::Mutex::ScopedLock lock(mutex);
		return (double)(finish - start) / CLOCKS_PER_SEC;
	}

private:
	Poco::Mutex mutex;

	bool searchOk, invokeOk;
	std::string result;
	clock_t start, finish;
};

}
}
}

struct FixtureInvoke : Tests::AbstractOSCLibFixture {
	FixtureInvoke() : AbstractOSCLibFixture("FixtureInvoke", Util::DebugOut::Error, 6000) {}
};

SUITE(Basics) {
TEST_FIXTURE(FixtureInvoke, invoke)
{
	try
	{
		// Create device
		Dev::Device device;
		// Add custom endpoint reference
		device.setEPRAddress("urn:uuid:1234");
		// Create binding for device
		std::shared_ptr<Comm::Binding> deviceBinding(new Comm::Binding(OSCLibrary::getInstance()->getBindInterface(), 6500, "ExampleDevice"));
		device.addBinding(Comm::DPWS::DPWS11, deviceBinding);
		// Add type and scope
		device.addType(Data::QName("MedicalDevice", OSCLib::Tests::ServiceInvoke::DEFAULT_NAMESPACE));
		device.addScope("http://www.surgitaix.com");

		// Create service for device;
		std::shared_ptr<Dev::Service> service(new Dev::Service);
		// Create HTTP binding for service
		std::shared_ptr<Comm::Binding> serviceBinding(new Comm::Binding(OSCLibrary::getInstance()->getBindInterface(), 6501, "ExampleService"));
		service->addBinding(Comm::DPWS::DPWS11, serviceBinding);
		// Add service ID
		service->setServiceId("ExampleServiceId");

		// Create operations for the service
		std::shared_ptr<Tests::ServiceInvoke::SumOperation> sumOp(new Tests::ServiceInvoke::SumOperation);
		service->addOperation(sumOp);
		std::shared_ptr<Tests::ServiceInvoke::SubOperation> subOp(new Tests::ServiceInvoke::SubOperation);
		service->addOperation(subOp);
		std::shared_ptr<Tests::ServiceInvoke::OSCBIdentOperation> idOp(new Tests::ServiceInvoke::OSCBIdentOperation);
		service->addOperation(idOp);

		// Add service to device, start device (autostart service)
		device.addService(service);
		device.start();

		// Check primary operation
		Tests::ServiceInvoke::CustomClient client;
		client.search();
		Poco::Thread::sleep(5000);
		CHECK_EQUAL(true, client.getSearchOk());
		CHECK_EQUAL(3, int(client.getRemoteDevice()->getService(0)->getOperations().size()));
		CHECK_EQUAL(true, client.getInvokeOk());
		CHECK_EQUAL("3", client.getResult());
		const std::string timeString(std::to_string(client.getElapsedTime()));
		Util::DebugOut(Util::DebugOut::Default, "invoke") << "TIME, invoke -> return: " << timeString << std::endl;

		// Check secondary operation with different local part in namespace
		Data::QName portType("MedicalService2", OSCLib::Tests::ServiceInvoke::DEFAULT_NAMESPACE);
		Parameters params;
		params.push_back(Parameter("InValue1", Parameter::Type::INT, "1"));
		params.push_back(Parameter("InValue2", Parameter::Type::INT, "2"));
		// Invoke subtraction method
		Parameters out;
		CHECK_EQUAL(true, client.invokeSync(portType, "GetSub", params, &out));
		std::string result = out[0].getValue();
		CHECK_EQUAL("-1", result);

		// Stop client, device and service
		client.close();
		device.stop();
	}
	catch (char const* exc)
	{
		Util::DebugOut(Util::DebugOut::Default, std::cerr, "invoke") << exc;
	}
	catch (...)
	{
		Util::DebugOut(Util::DebugOut::Default, std::cerr, "invoke") << "Unknown exception occurred!";
	}
}
}


