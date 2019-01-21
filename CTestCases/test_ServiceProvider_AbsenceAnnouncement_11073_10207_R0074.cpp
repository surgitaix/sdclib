/*
 * test_ServiceProvider_AbsenceAnnouncement_11073_10207_R0074.cpp
 *
 *  Created on: Nov 7, 2018
 *      Author: rosenau
 *
 *      Test against requirement R0074 from IEEE 11073-10207 A SERVICE PROVIDER SHOULD announce its upcoming absence if it is switching to a mode where it is not ready to exchange MESSAGEs with a SERVICE CONSUMER temporarily.
 */

#include "Tools/MulticastHandler.h"
#include "OSCLib/SDCInstance.h"
#include "OSCLib/SDCLibrary.h"
#include "OSCLib/Data/SDC/SDCProvider.h"

#include "OSCLib/Data/SDC/MDPWSTransportLayerConfiguration.h"

#include "OSELib/SDC/ServiceManager.h"

#include "OSCLib/Util/DebugOut.h"
#include "OSCLib/Util/Task.h"

#include "OSELib/SOAP/CommonSoapPreprocessing.h"
#include "Tools/test_schema.h"
#include "OSELib/WSDL/schema.h"
#include "OSELib/Helper/SchemaGrammarProvider.h"
#include "OSELib/Helper/WithLogger.h"
#include "OSELib/Helper/Message.h"
#include "OSELib/Helper/XercesDocumentWrapper.h"
#include "Tools/TestProvider.h"

using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

using namespace xercesc;


const std::string DEVICE_EPR("TestProvider");
typedef  std::vector<std::pair<std::string, std::string>> testCases_t;
static const testCases_t testCases = {
		{"wsa:To", "urn:docs-oasis-open-org:ws-dd:ns:discovery:2009:01"},
		{"p2:Types", "dpws:MedicalDevice mdpws:MedicalDevice"}
};



class ByeTestHandler : public TestTools::MulticastHandler{

	class ByeSchemaGrammarProvider : public OSELib::Helper::SchemaGrammarProvider, public OSELib::WithLogger
	{
	public:
		ByeSchemaGrammarProvider() : OSELib::WithLogger(OSELib::Log::SCHEMA) {
			auto addSchemaWithErrorHandling([this](const std::string & name, const std::string & schema) {
				if (!addSchema(name, schema)) {
					log_error([&]{ return "Error loading schema: " + name + "\n" + schema; });
				}
			});

			addSchemaWithErrorHandling(OSELib::SCHEMA::SCHEMA_WSADDRESSING_NAME, OSELib::SCHEMA::SCHEMA_WSADDRESSING_CONTENT);
			addSchemaWithErrorHandling(OSELib::SCHEMA::SCHEMA_DISCOVERY_NAME, OSELib::SCHEMA::SCHEMA_DISCOVERY_CONTENT);
			addSchemaWithErrorHandling(OSELib::SCHEMA::SCHEMA_BYEMESSAGE_NAME, OSELib::SCHEMA::SCHEMA_BYEMESSAGE_CONTENT);
			seal();
		}

		virtual ~ByeSchemaGrammarProvider() {
		}

	};

public:

	ByeTestHandler() {
	}

	virtual ~ByeTestHandler() {
	}

	bool validateValues(TestTools::messagedata_t messagedata)	{
		xercesc::DOMElement* root = getRootElement(messagedata.socketData);
		if (root == nullptr) {
			return false;
		}
		for(auto test : testCases)
		{
			if (!checkExpectedValue(root, test.first, test.second))
				return false;
		}
		return true;
	}

	void onByeMessageReceived(TestTools::messagedata_t messagedata)
	{
		if(!validateValues(messagedata)) {
			std::cout << "Test failed" << endl;
			return;
		}

		OSELib::SOAP::CommonSoapPreprocessing soapHandling(_grammarProvider);
		try {
			soapHandling.parse(messagedata.socketData);
		}
		catch (std::exception &e) {
			std::cout << e.what();
			std::cout << "Test failed";
			return;
		}

		std::cout << "Test passed" << endl;
		ByeReceived = true;
	}

	bool gotBye()
	{
		return ByeReceived;
	}

private:
	ByeSchemaGrammarProvider _grammarProvider;
	bool ByeReceived = false;


};


int main() {
	std::cout << "Test against requirement R0074 from IEEE 11073-10207 A SERVICE PROVIDER SHOULD announce its upcoming absence if it is switching to a mode where it is not ready to exchange MESSAGEs with a SERVICE CONSUMER temporarily:";
	SDCLibrary::getInstance().startup(OSELib::LogLevel::None);
	SDCLibrary::getInstance().setIP6enabled(false);
	SDCLibrary::getInstance().setIP4enabled(true);
	SDCLibrary::getInstance().setPortStart(12000);

	xercesc::XMLPlatformUtils::Initialize ();

	Poco::Net::SocketAddress ipv4MulticastAddress(UDP_MULTICAST_IP_V4, UPD_MULTICAST_DISCOVERY_PORT);
	Poco::Net::SocketAddress ipv4BindingAddress(Poco::Net::IPAddress(Poco::Net::IPAddress::Family::IPv4), ipv4MulticastAddress.port());
	Poco::Net::MulticastSocket ipv4Socket(ipv4BindingAddress.family());
	std::cout << "Binding ipv4 address " << ipv4BindingAddress.host().toString() << std::endl;
	ipv4Socket.bind(ipv4BindingAddress, true);
	std::cout << "Joining ipv4 group " << ipv4MulticastAddress.host().toString() << std::endl;
	ipv4Socket.joinGroup(ipv4MulticastAddress.host());
	ipv4Socket.setBlocking(false);

	OSELib::SDC::ServiceManager oscpsm;
	ByeTestHandler multicastHandler;

	TestTools::TestProvider provider;
	provider.setPort(6470);
	provider.startup();
	provider.start();
	Poco::Net::SocketReactor reactor;

	reactor.addEventHandler(ipv4Socket, Poco::Observer<TestTools::MulticastHandler, Poco::Net::ReadableNotification>(multicastHandler, &TestTools::MulticastHandler::onMulticastSocketReadable));

	Poco::Thread reactorThread;
	reactorThread.start(reactor);
	provider.shutdown();

	int i = 0;

	while(i < 10)
	{
		sleep(1);
		if(multicastHandler.gotBye())
			break;
		i++;
	}
	if(i >= 10)
	{
		cout << "Time out" << std::endl;
		cout << "Test failed" << std::endl;
	}


	reactor.removeEventHandler(ipv4Socket, Poco::Observer<TestTools::MulticastHandler, Poco::Net::ReadableNotification>(multicastHandler, &TestTools::MulticastHandler::onMulticastSocketReadable));	reactor.stop();
	reactorThread.join();

	xercesc::XMLPlatformUtils::Terminate ();

	provider.shutdown();
	SDCLibrary::getInstance().shutdown();

	SDCLibrary::getInstance().shutdown();
	Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Shutdown." << std::endl;
}


