/*
 * test_DPWSDiscoveryClientSocketImpl.cpp
 *
 *  Created on: Nov 23, 2018
 *      Author: rosenau
 */

#include <chrono>
#include <iostream>

#include "NormalizedMessageModel.hxx"

#include "OSELib/DPWS/DPWSDiscoveryClientSocketImpl.h"
#include "OSELib/DPWS/Types.h"
#include "OSELib/DPWS/DPWS11Constants.h"

#include "OSCLib/SDCLibrary.h"
#include "OSCLib/Util/Task.h"
#include "OSCLib/Data/SDC/SDCProvider.h"

#include "Tools/TestSOAPMessageProvider.h"


#include "Poco/Net/HTTPServer.h"


using namespace OSELib;
using namespace DPWS;
using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

const std::string DEVICE_EPR("TestProvider");

class OSCPStreamProvider : public Util::Task {
public:

    OSCPStreamProvider() :
    	sdcProvider()
    	{

    	MDPWSTransportLayerConfiguration providerConfig = MDPWSTransportLayerConfiguration();
		providerConfig.setPort(6466);
		sdcProvider.setConfiguration(providerConfig);
		sdcProvider.setEndpointReference(DEVICE_EPR);


    }

    void startup() {
    	sdcProvider.startup();
    }

    void shutdown() {
    	sdcProvider.shutdown();
    }

private:

    TestTools::TestSOAPMessageProvider sdcProvider;


public:
    virtual void runImpl() override {
		while (!isInterrupted()) {
			{
			}
			Poco::Thread::sleep(1000);
		}
    }
};

class dummyByeDispatcher :
	public ByeNotificationDispatcher
{
public:
	dummyByeDispatcher() {

	}
	virtual ~dummyByeDispatcher() {

	}

private:
	virtual void dispatch(const ByeType & notification) override {

	}
};

class dummyHelloDispatcher :
	public HelloNotificationDispatcher
{
public:
	dummyHelloDispatcher() {
		std::cout << "test";
	}
	virtual ~dummyHelloDispatcher() {

	}

private:
	virtual void dispatch(const HelloType & notification) override {

	}
};

class dummyProbeMatchDispatcher :
	public ProbeMatchNotificationDispatcher
{
public:
	dummyProbeMatchDispatcher() {

	}
	virtual ~dummyProbeMatchDispatcher() {

	}

private:
	virtual void dispatch(const ProbeMatchType & notification) override {

	}
};


class dummyResolveMatchDispatcher :
	public ResolveMatchNotificationDispatcher
{
public:
	dummyResolveMatchDispatcher() {

	}
	virtual ~dummyResolveMatchDispatcher() {

	}

private:
	virtual void dispatch(const ResolveMatchType & notification) override {

	}
};


int main()
{
	SDCLibrary::getInstance().startup(OSELib::LogLevel::Error);
	SDCLibrary::getInstance().setIP6enabled(false);
	SDCLibrary::getInstance().setIP4enabled(true);
	SDCLibrary::getInstance().setPortStart(12000);

	//setting up DPWSDiscoveryClientSocketImpl for Testing
	dummyByeDispatcher myDummyByeDispatcher;
	dummyHelloDispatcher myDummyHelloDispatcher;
	dummyResolveMatchDispatcher myDummyResolveMatchDispatcher;
	dummyProbeMatchDispatcher myDummyProbeMatchDispatcher;
	Impl::DPWSDiscoveryClientSocketImpl DPWSDiscoveryClientSocketImplUnderTest(myDummyByeDispatcher, myDummyHelloDispatcher, myDummyProbeMatchDispatcher, myDummyResolveMatchDispatcher);




	return 0;
}

