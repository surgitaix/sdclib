/**
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  *
  */

/*
 * OSCPServiceManager.cpp
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: roehser, besting
 */

#include "OSCLib/Cli/Client.h"
#include "OSCLib/Cli/HelloReceivedHandler.h"
#include "OSCLib/Comm/Binding.h"
#include "Poco/Thread.h"
#include "OSCLib/Data/OSCP/OSCPConstants.h"
#include "OSCLib/Data/OSCP/OSCPConsumer.h"
#include "OSCLib/Data/OSCP/OSCPServiceManager.h"
#include "OSCLib/Dev/Device.h"
#include "OSCLib/OSCLibrary.h"
#include "OSCLib/Util/DebugOut.h"

#include <string>

using namespace OSCLib::Cli;

namespace OSCLib {
namespace Data {
namespace OSCP {

void OSCPHelloReceivedHandler::helloReceived(const std::string & ) {
	Util::DebugOut(Util::DebugOut::Error, "OSCPHelloReceivedHandler") << "Method 'helloReceived' must be overridden!";
}

OSCPServiceManager::OSCPServiceManager() : helloHandler(nullptr) {
    class MyHandler : public HelloReceivedHandler {
    public:
    	MyHandler(OSCPServiceManager & sm) : sm(sm) {
    	}
    	void helloReceived(const std::string & epr) override {
    		sm.helloReceived(epr);
    	}
    private:
    	OSCPServiceManager & sm;
    };
    internalHelloHandler = std::make_shared<MyHandler>(*this);
    internalClient = std::make_shared<Client>();
    internalClient->setHelloReceivedHandler(internalHelloHandler);
}

OSCPServiceManager::~OSCPServiceManager() {
	internalClient->close();
    helloHandler = nullptr;
}

std::shared_ptr<OSCPConsumer> OSCPServiceManager::connect(const std::string & xaddr)
{
	std::shared_ptr<Client> client = std::make_shared<Client>();
    client->setDeviceXAddrSearchParam(xaddr);
    return executeSearch(client);
}

std::shared_ptr<OSCPConsumer> OSCPServiceManager::discoverEndpointReference(const std::string & epr)
{
	std::shared_ptr<Client> client(std::make_shared<Client>());
	client->setDeviceEPRAdrSearchParam(epr);
	return executeSearch(client);
}

std::shared_ptr<OSCPConsumer> OSCPServiceManager::executeSearch(std::shared_ptr<Client> client)
{
    if (client->searchSync())
    {
    	std::shared_ptr<OSCPConsumer> oc(new OSCPConsumer(client));
        OSCLibrary::getInstance()->registerConsumer(oc.get());
		if (!oc->requestMDIB()) {
			oc->disconnect();
			client->close();
			return nullptr;
		}
        return oc;
    }
    else
    {
        client->close();
    }
    return nullptr;
}

std::vector<std::shared_ptr<OSCPConsumer>> OSCPServiceManager::discoverOSCP()
{
	std::vector<std::shared_ptr<OSCPConsumer>> consumers;
    std::vector<std::shared_ptr<Client>> clients;

	std::shared_ptr<Cli::Client> client = std::make_shared<Client>();
    clients.push_back(client);
	client->addDeviceTypeSearchParam(QName("MedicalDevice", Data::OSCP::NS_MESSAGE_MODEL));

	client->search();
	Poco::Thread::sleep(5000);

	int continueSearchTimeout = 0;
	while (continueSearchTimeout < 15000 && client->isAnySearchRunning()) {
		Poco::Thread::sleep(100);
		continueSearchTimeout += 100;
	}

    clients = client->getClients();
    clients.push_back(client);

    for (size_t td = 0; td < clients.size(); ++td) {
		std::shared_ptr<OSCPConsumer> oc (new OSCPConsumer(clients[td]));
		OSCLibrary::getInstance()->registerConsumer(oc.get());
		if (!oc->requestMDIB()) {
			oc->disconnect();
			continue;
		}
		consumers.push_back(oc);
	}

    client->getClients().clear();
	return consumers;
}

void OSCPServiceManager::setHelloReceivedHandler(OSCPHelloReceivedHandler * handler) {
	helloHandler = handler;
}

void OSCPServiceManager::helloReceived(std::string epr) {
	if (helloHandler) {
		helloHandler->helloReceived(epr);
	}
}

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
