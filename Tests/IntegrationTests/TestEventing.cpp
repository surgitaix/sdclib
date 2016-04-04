/*
 * TestEventing.cpp
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
namespace Eventing {

const std::string DEFAULT_NAMESPACE("http://www.surgitaix.com/example");

class NotificationEventSource : public Data::EventSource {
public:

	NotificationEventSource() : responseOk(false)
	{
		// The event's name
		setName("SendNotification");
		// The port type
		Data::QName pType("NotificationPort", DEFAULT_NAMESPACE);
		setPortType(pType);

		// The output parameter (fire)
		Parameter p1("NotificationValue", Parameter::Type::STRING);
		addOutputParameter(p1);

		// The input parameter (solicit response)
		Parameter p2("ResponseValue", Parameter::Type::STRING);
		addInputParameter(p2);
	}

	void responseReceived(Parameters & p) {
        if (p[0].getValue().compare("Response Test") == 0)
        {
            setResponseOk(true);
        }
    }

	bool getResponseOk() {
		Poco::Mutex::ScopedLock lock(mutex);
		return responseOk;
	}

private:
	void setResponseOk(bool value) {
		Poco::Mutex::ScopedLock lock(mutex);
		responseOk = value;
	}

    bool responseOk;
    Poco::Mutex mutex;
};

class NotificationEventSink : public Data::EventSink {
public:

	NotificationEventSink() : eventOk(false)
	{
	}

    Parameters eventReceived(Parameters& p)
    {
    	if (p[0].getValue().compare("Event Test") == 0)
    		setEventOk(true);
        Parameters returnParams;
        returnParams.push_back(Parameter("ResponseValue", Parameter::Type::STRING, "Response Test"));
        return returnParams;
    }

	bool getEventOk() {
		Poco::Mutex::ScopedLock lock(mutex);
		return eventOk;
	}

private:
	void setEventOk(bool value) {
		Poco::Mutex::ScopedLock lock(mutex);
		eventOk = value;
	}

    bool eventOk;
    Poco::Mutex mutex;
};

}
}
}

struct FixtureEventing : Tests::AbstractOSCLibFixture {
	FixtureEventing() : AbstractOSCLibFixture("FixtureEventing", Util::DebugOut::Error, 5000) {}
};

SUITE(Advanced) {
TEST_FIXTURE(FixtureEventing, eventing)
{
	try
	{
		// Create device
		Dev::Device device;
		// Add custom endpoint reference
		device.setEPRAddress("urn:uuid:1234");
		// Create binding for device
		std::shared_ptr<Comm::Binding> deviceBinding(new Comm::Binding(OSCLibrary::getInstance()->getBindInterface(), 5500, "EventingDevice"));
		device.addBinding(Comm::DPWS::DPWS11, deviceBinding);
		// Add type and scope
		device.addType(Data::QName("EventingTest", OSCLib::Tests::Eventing::DEFAULT_NAMESPACE));
		device.addScope("http://www.surgitaix.com");

		// Create eventing service
		std::shared_ptr<Dev::Service> service(new Dev::Service);
		// Create HTTP binding for service
		std::shared_ptr<Comm::Binding> serviceBinding(new Comm::Binding(OSCLibrary::getInstance()->getBindInterface(), 5501, "EventingService"));
		service->addBinding(Comm::DPWS::DPWS11, serviceBinding);
		// Add service ID
		service->setServiceId("EventingServiceId");

		// Create operations for the service
		std::shared_ptr<Tests::Eventing::NotificationEventSource> source(new Tests::Eventing::NotificationEventSource);
		service->addEvent(source);

		// Add service to device, start device (autostart service)
		device.addService(service);
		device.start();

		Cli::Client client;
		client.setServiceIDSearchParam("EventingServiceId");
		CHECK_EQUAL(true, client.searchSync());

        Data::QName pType("NotificationPort", OSCLib::Tests::Eventing::DEFAULT_NAMESPACE);
        std::shared_ptr<OSCLib::Tests::Eventing::NotificationEventSink> nes(new OSCLib::Tests::Eventing::NotificationEventSink);
		CHECK_EQUAL(true, client.subscribeSync(pType, "SendNotification", 10000, nes));

        CHECK_EQUAL(true, client.renewSync(pType, "SendNotification", 10000, nes));

        Poco::Thread::sleep(1000);

		// Fire event
		Parameters params;
		params.push_back(Parameter("NotificationValue").setValue("Event Test"));

		CHECK_EQUAL(unsigned(1), source->fire(params));

		Poco::Thread::sleep(5000);

        CHECK_EQUAL(true, nes->getEventOk());
        CHECK_EQUAL(true, source->getResponseOk());

        Poco::Thread::sleep(5000);

		// Subscription should be expired now
		CHECK_EQUAL(unsigned(0), source->fire(params));

		client.close();
		device.stop();
	}
	catch (char const* exc)
	{
		Util::DebugOut(Util::DebugOut::Default, std::cerr, "eventing") << exc;
	}
	catch (...)
	{
		Util::DebugOut(Util::DebugOut::Default, std::cerr, "eventing") << "Unknown exception occurred!";
	}
}
}
