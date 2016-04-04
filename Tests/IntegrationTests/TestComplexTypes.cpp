/*
 * TestComplexTypes.cpp
 *
 *  Created on: 30.01.2013
 *      Author: roehser
 */

#include "OSCLib/OSCL.h"
#include "OSCLib/Comm/DPWS/DPWS11Constants.h"
#include "OSCLib/Data/Parameter.h"
#include "../AbstractOSCLibFixture.h"
#include "../UnitTest++/src/UnitTest++.h"

#include "Poco/Mutex.h"
#include "Poco/ScopedLock.h"
#include "Poco/Thread.h"

using namespace OSCLib;
using namespace OSCLib::Data;

namespace OSCLib {
namespace Tests {
namespace ComplexTypes {

const std::string DEFAULT_NAMESPACE("http://www.surgitaix.com/example");

class ComplexOperation : public Data::Operation {
public:

	ComplexOperation() {
		// The operation's name
		setName("GetComplexResult");
		// The port type
		Data::QName pType("ComplexServicePort", DEFAULT_NAMESPACE);
		setPortType(pType);

		// Input parameters definition
		Parameter p1("SimpleInParam1", Parameter::Type::INT);
		addInputParameter(p1);
		Parameter complexIn("ComplexInParam1");
		complexIn.setCompositor(Parameter::Compositor::SEQUENCE);
		complexIn["InParam11"].setType(Parameter::Type::INT);
		complexIn["InParam12"].setType(Parameter::Type::STRING);
		// Embed another complex container (unbounded)
		complexIn["ComplexInParam2"].setMaxOccurs(-1);
		complexIn["ComplexInParam2.InParam21"].setType(Parameter::Type::BYTE);
		complexIn["ComplexInParam2.InParam22"].setType(Parameter::Type::FLOAT);
		addInputParameter(complexIn);

		// Output parameters definition
		Parameter p2("SimpleOutValue1", Parameter::Type::STRING);
		addOutputParameter(p2);
		Parameter complexOut("ComplexOutParam1");
		complexOut.setCompositor(Parameter::Compositor::SEQUENCE);
		complexOut["OutParam11"].setType(Parameter::Type::INT);
		complexOut["OutParam12"].setType(Parameter::Type::STRING);
		// Embed another complex container (unbounded)
		complexOut["ComplexOutParam2"].setMaxOccurs(-1);
		complexOut["ComplexOutParam2.OutParam21"].setType(Parameter::Type::BYTE);
		complexOut["ComplexOutParam2.OutParam22"].setType(Parameter::Type::FLOAT);
		complexOut["ComplexOutParam2.ComplexOutParam3"].setMaxOccurs(-1);
		complexOut["ComplexOutParam2.ComplexOutParam3.OutParam31"].setType(Parameter::Type::BYTE);
		complexOut["ComplexOutParam2.ComplexOutParam3.OutParam32"].setType(Parameter::Type::FLOAT);
		addOutputParameter(complexOut);
	}

	Data::Parameters invoke(Parameters & p)	{
		Parameter& complexIn1 = *(&p[1]);
		float f = atof(complexIn1["ComplexInParam2.InParam22"].getValue().c_str());
		f += 1.5f;
		Parameters returnParams(getOutput());
		Parameter* simpleOutValue1 = &returnParams[0];
		Parameter* complexOutParam1 = &returnParams[1];
		simpleOutValue1->setValue("TestOut1");
		(*complexOutParam1)["OutParam11"].setValue("1");
		(*complexOutParam1)["OutParam12"].setValue("TestOut2");
		(*complexOutParam1)["ComplexOutParam2.OutParam21"].setValue("1");
		std::ostringstream s;
		s << f;
		(*complexOutParam1)["ComplexOutParam2.OutParam22"].setValue(s.str());
		(*complexOutParam1)["ComplexOutParam2(0).OutParam21"].setValue("1.23");
		float f2 = f + 5;
		std::ostringstream s2;
		s2 << f2;
		(*complexOutParam1)["ComplexOutParam2(0).OutParam22"].setValue(s2.str());
		Parameter& cParam3 = (*complexOutParam1)["ComplexOutParam2(0).ComplexOutParam3"];
		cParam3["OutParam31"].setValue("128");
		return returnParams;
	}
};

class ComplexClient : public Cli::Client {
public:

	ComplexClient() : Client(), searchOk(false), invokeOk(false),
		result1(""), result2(""), result3("")
	{
		setServiceIDSearchParam("ComplexServiceId");
		search();
	}

    void searchComplete() {
		Data::QName portType("ComplexServicePort", DEFAULT_NAMESPACE);
		Parameters params;
		Parameter p1("SimpleInParam1", Parameter::Type::INT);
		params.push_back(p1);
		Parameter complexIn("ComplexInParam1");
		complexIn.setCompositor(Parameter::Compositor::SEQUENCE);
		complexIn["InParam11"].setType(Parameter::Type::INT);
		complexIn["InParam12"].setType(Parameter::Type::STRING);
		// Embed another complex container
		complexIn["ComplexInParam2.InParam21"].setType(Parameter::Type::BYTE);
		complexIn["ComplexInParam2.InParam22"].setType(Parameter::Type::FLOAT).setValue("1.2");
		params.push_back(complexIn);
		searchOk = true;
		// Invoke method
		Parameters out;
		Poco::Mutex::ScopedLock lock(mutex);
		invokeOk = invokeSync(portType, "GetComplexResult", params, &out);
		if (!invokeOk)
			return;
		// Get output parameters
		result1 = out[1]["ComplexOutParam2.OutParam22"].getValue();
		result2 = out[1]["ComplexOutParam2(0).OutParam22"].getValue();
		result3 = out[1]["ComplexOutParam2(0).ComplexOutParam3.OutParam31"].getValue();
    }

	bool getSearchOk() {
		Poco::Mutex::ScopedLock lock(mutex);
		return searchOk;
	}

	bool getInvokeOk() {
		Poco::Mutex::ScopedLock lock(mutex);
		return invokeOk;
	}

	std::string getResult1() {
		Poco::Mutex::ScopedLock lock(mutex);
		return result1;
	}

	std::string getResult2() {
		Poco::Mutex::ScopedLock lock(mutex);
		return result2;
	}

	std::string getResult3() {
		Poco::Mutex::ScopedLock lock(mutex);
		return result3;
	}

private:
	Poco::Mutex mutex;

	bool searchOk, invokeOk;
	std::string result1;
	std::string result2;
	std::string result3;
};

}
}
}

struct FixtureComplex : Tests::AbstractOSCLibFixture {
	FixtureComplex() : AbstractOSCLibFixture("FixtureComplex", Util::DebugOut::Error, 2000) {}
};

SUITE(Advanced){
TEST_FIXTURE(FixtureComplex, complex)
{
	try
	{
		// Create device
		Dev::Device device;
		// Add custom endpoint reference
		device.setEPRAddress("urn:uuid:1234");
		// Create binding for device
		std::shared_ptr<Comm::Binding> deviceBinding(new Comm::Binding(OSCLibrary::getInstance()->getBindInterface(), 2500, "ExampleDevice"));
		device.addBinding(Comm::DPWS::DPWS11, deviceBinding);
		// Add type and scope
		device.addType(Data::QName("MedicalDevice", OSCLib::Tests::ComplexTypes::DEFAULT_NAMESPACE));
		device.addScope("http://www.surgitaix.com");

		// Create ID service for device;
		std::shared_ptr<Dev::Service> service(new Dev::Service());
		// Create HTTP binding for service
		std::shared_ptr<Comm::Binding> serviceBinding(new Comm::Binding(OSCLibrary::getInstance()->getBindInterface(), 2501, "ExampleService"));
		service->addBinding(Comm::DPWS::DPWS11, serviceBinding);
		// Add service ID
		service->setServiceId("ComplexServiceId");

		// Create operations for the service
		std::shared_ptr<Tests::ComplexTypes::ComplexOperation> cOp(new Tests::ComplexTypes::ComplexOperation);
		service->addOperation(cOp);

		// Add service to device, start device (autostart service)
		device.addService(service);
		device.start();
		Tests::ComplexTypes::ComplexClient client;
		Poco::Thread::sleep(10000);
		CHECK_EQUAL(true, client.getSearchOk());
		CHECK_EQUAL(true, client.getInvokeOk());
		CHECK_EQUAL("2.7", client.getResult1());
		CHECK_EQUAL("7.7", client.getResult2());
		CHECK_EQUAL("128", client.getResult3());
		device.stop();
		client.close();
	}
	catch (char const* exc)
	{
		Util::DebugOut(Util::DebugOut::Default, std::cerr, "complex") << exc;
	}
	catch (...)
	{
		Util::DebugOut(Util::DebugOut::Default, std::cerr, "complex") << "Unknown exception occurred!";
	}
}
}
