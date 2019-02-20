/*
 * test_ServiceProvider_HelloMessage_WS_Discovery.cpp
 *
 *  Created on: Nov 12, 2018
 *      Author: rosenau
 *
 *      Test against requirements from WS-Discovery 4.1 Hello for Hello Messages
 */

#include "OSCLib/SDCInstance.h"


#include "OSCLib/SDCInstance.h"


#include "OSCLib/SDCLibrary.h"
#include "OSCLib/Data/SDC/SDCProvider.h"

#include "OSCLib/Data/SDC/MDPWSTransportLayerConfiguration.h"

#include "OSELib/SOAP/CommonSoapPreprocessing.h"

#include "OSELib/SDC/ServiceManager.h"

#include "OSCLib/Util/DebugOut.h"
#include "OSCLib/Util/Task.h"

#include "Tools/MulticastHandler.h"
#include "Tools/test_schema.h"

#include "OSELib/WSDL/schema.h"

#include "OSELib/Helper/SchemaGrammarProvider.h"
#include "OSELib/Helper/WithLogger.h"
#include "OSELib/Helper/Message.h"
#include "OSELib/Helper/XercesDocumentWrapper.h"
#include "Tools/TestProvider.h"

#include "xercesc/parsers/XercesDOMParser.hpp"
#include "xercesc/sax/HandlerBase.hpp"
#include "xercesc/framework/MemBufInputSource.hpp"
#include "xercesc/sax/ErrorHandler.hpp"
#include "xercesc/dom/DOM.hpp"
#include "xercesc/util/XMLString.hpp"


using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

using namespace xercesc;


const std::string DEVICE_EPR("TestProvider");
typedef  std::vector<std::pair<std::string, std::string>> testCases_t;
static const testCases_t testCases = {
		{"wsa:To", "urn:docs-oasis-open-org:ws-dd:ns:discovery:2009:01"}
};


class helloTestHandler: public TestTools::MulticastHandler{

	class HelloSchemaGrammarProvider : public OSELib::Helper::SchemaGrammarProvider, public OSELib::WithLogger
	{
	public:
		HelloSchemaGrammarProvider() : OSELib::WithLogger(OSELib::Log::SCHEMA) {

			auto addSchemaWithErrorHandling([this](const std::string & name, const std::string & schema) {
				if (!addSchema(name, schema)) {
					log_error([&]{ return "Error loading schema: " + name + "\n" + schema; });
				}
			});

			addSchemaWithErrorHandling(OSELib::SCHEMA::SCHEMA_WSADDRESSING_NAME, OSELib::SCHEMA::SCHEMA_WSADDRESSING_CONTENT);
			addSchemaWithErrorHandling(OSELib::SCHEMA::SCHEMA_DISCOVERY_NAME, OSELib::SCHEMA::SCHEMA_DISCOVERY_CONTENT);
			addSchemaWithErrorHandling(OSELib::SCHEMA::SCHEMA_HELLLOMESSAGE_NAME, OSELib::SCHEMA::SCHEMA_HELLLOMESSAGE_CONTENT);
			seal();
		}

		virtual ~HelloSchemaGrammarProvider()
		{

		}

	};

public:

	helloTestHandler() {

	}

	virtual ~helloTestHandler() {

	}


	xercesc::DOMElement* getRootElement(std::string xmlString)
	{
		xercesc::DOMElement* root = nullptr;
		//Parse XML to DOMelement
		xercesc::XercesDOMParser* parser = new XercesDOMParser();
		xercesc::MemBufInputSource memBuffer((unsigned char*)xmlString.c_str(), xmlString.size(), "dummy");
		parser->setValidationScheme(XercesDOMParser::Val_Always);
		xercesc::ErrorHandler* errorHandler = (ErrorHandler*) new HandlerBase();
		parser->setErrorHandler(errorHandler);

		try {
			parser->parse(memBuffer);
		} catch(const XMLException& xmlException) {
			cerr << "unable to parse xml to dom" << xmlException.getMessage() << endl;
		} catch(const DOMException& domException) {
			cerr << "unable to parse xml to dom" << domException.getMessage() << endl;
		} catch (...) {
			cerr << "unable to parse xml to dom" << endl;
		}

		xercesc::DOMDocument* xmlDom = parser->getDocument();
		root = xmlDom->getDocumentElement();
		return root;
	}

	bool checkExpectedValue(xercesc::DOMElement* rootElement, std::string tag, std::string expectedValue)
	{
		bool passed = false;
		xercesc::DOMElement* root = rootElement;
		char *tagAsChar = &tag[0u];
		XMLCh* transcodedTag = XMLString::transcode(tagAsChar);
		xercesc::DOMNodeList* toChildren = root->getElementsByTagName(transcodedTag);
		XMLString::release(&transcodedTag);

		const XMLSize_t nodeCount = toChildren->getLength();

		if(nodeCount == 1) {
			xercesc::DOMNode* toNode = toChildren->item(0);
			char* temp = XMLString::transcode(toNode->getTextContent());
			std::string nodeValue(temp);
			XMLString::release(&temp);
			//check value against required value
			if(nodeValue != expectedValue) {
				cout << nodeValue << "unequal to " << expectedValue << endl;
				passed = false;
			}
			else {
				passed = true;
			}
		}
		else {
			cout << "Multiple nodes with Type wsa:To" << endl;
			passed = false;
		}
		return passed;
	}

	bool validateValues(TestTools::messagedata_t messagedata)	{
		xercesc::DOMElement* root = getRootElement(messagedata.socketData);
		if (root == nullptr) {
			return false;
		}
		for(auto test : testCases)
		{
			if (!checkExpectedValue(root, test.first, test.second))  {
				return false;
			}
		}
		return true;
	}

	void onHelloMessageReceived(TestTools::messagedata_t messagedata)
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
		helloReceived = true;
	}

	bool gotHello()
	{
		return helloReceived;
	}

private:
	HelloSchemaGrammarProvider _grammarProvider;
	bool helloReceived = false;

};


int main() {
	std::cout << "Test against requirements from WS-Discovery 4.1 Hello for outgoing hello messages :"
			  << std::endl;
	SDCLibrary::getInstance().startup(OSELib::LogLevel::Error);
	SDCLibrary::getInstance().setIP6enabled(false);
	SDCLibrary::getInstance().setIP4enabled(true);
	SDCLibrary::getInstance().setPortStart(12000);

	xercesc::XMLPlatformUtils::Initialize ();


	std::cout << "Listening for DPWS discovery messages ..." << std::endl;

	Poco::Net::SocketAddress ipv4MulticastAddress(UDP_MULTICAST_IP_V4, UPD_MULTICAST_DISCOVERY_PORT);
	Poco::Net::SocketAddress ipv4BindingAddress(Poco::Net::IPAddress(Poco::Net::IPAddress::Family::IPv4), ipv4MulticastAddress.port());
	Poco::Net::MulticastSocket ipv4Socket(ipv4BindingAddress.family());
	std::cout << "Binding ipv4 address " << ipv4BindingAddress.host().toString() << std::endl;
	ipv4Socket.bind(ipv4BindingAddress, true);
	std::cout << "Joining ipv4 group " << ipv4MulticastAddress.host().toString() << std::endl;
	ipv4Socket.joinGroup(ipv4MulticastAddress.host());
	ipv4Socket.setBlocking(false);


	OSELib::SDC::ServiceManager oscpsm;
	helloTestHandler multicastHandler;


	Poco::Net::SocketReactor reactor;
	reactor.addEventHandler(ipv4Socket, Poco::Observer<TestTools::MulticastHandler, Poco::Net::ReadableNotification>(multicastHandler, &TestTools::MulticastHandler::onMulticastSocketReadable));

	Poco::Thread reactorThread;
	reactorThread.start(reactor);

	TestTools::TestProvider provider;
	provider.startup();
	provider.start();

	int i = 0;

	while(i < 10)
	{
		sleep(1);
		if(multicastHandler.gotHello())
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


