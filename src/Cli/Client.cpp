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

/**
 * @file Client.cpp
 * @project OSCLib
 * @date 27.02.2012
 * @author Besting
 * @copyright (c) SurgiTAIX AG
 *
 */

#include "OSCLib/OSCLibrary.h"
#include "OSCLib/Cli/HelloReceivedHandler.h"
#include "OSCLib/Cli/Client.h"
#include "OSCLib/Dev/Device.h"
#include "OSCLib/Comm/HTTPClientExchanger.h"
#include "OSCLib/Comm/Binding.h"
#include "OSCLib/Comm/DPWS/DPWS11ActionHandler.h"
#include "OSCLib/Comm/DPWS/DPWS11Constants.h"
#include "OSCLib/Comm/DPWS/DPWS11Message.h"
#include "OSCLib/Comm/DPWS/DPWS11MetadataSoapParserHandler.h"
#include "OSCLib/Comm/DPWS/DPWS11WSDLParser.h"
#include "OSCLib/Data/EventSink.h"
#include "OSCLib/Data/Operation.h"
#include "OSCLib/Data/OperationHelpers.h"
#include "OSCLib/Dev/EndpointReference.h"
#include "OSCLib/Util/DebugOut.h"
#include "OSCLib/Util/DefaultUUIDGenerator.h"
#include "OSCLib/Util/TypeConversion.h"
#include "Poco/Event.h"
#include "Poco/Thread.h"
#include "Poco/URI.h"
#include "Poco/Notification.h"
#include "Poco/Net/HTTPClientSession.h"

#include <algorithm>
#include <string>
#include <memory>

#include "Poco/ScopedLock.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketAddress.h"

using namespace OSCLib::Comm;
using namespace OSCLib::Comm::DPWS;
using namespace OSCLib::Data;
using namespace OSCLib::Dev;

namespace OSCLib {
namespace Cli {

const int Client::DEFAULT_TIMEOUT = 10000;

class WSDLNotification : public Poco::Notification {
public:

    WSDLNotification(Util::StringVector wsdls) : wsdlAddrs(wsdls) {
    }

    Util::StringVector getWSDLAddrs() const {
        return wsdlAddrs;
    }

private:
    Util::StringVector wsdlAddrs;
};
class HTTPNotification : public Poco::Notification {
public:

    HTTPNotification(std::shared_ptr<Comm::DPWS::DPWS11Message> m) : msg(m) {
        this->msg->setSendProtocol(Message::TCP_HTTP_BODY);
        DPWS11Message::generateRawBuffer(*this->msg);
    }

    std::shared_ptr<Comm::DPWS::DPWS11Message> getMsg() {
        return msg;
    }

private:
    std::shared_ptr<Comm::DPWS::DPWS11Message> msg;
};
class HTTPRequester : public Util::Task {
public:
    HTTPRequester(Client & cli,
        Poco::Mutex & mtx,
        Poco::Event & evt,
        Poco::NotificationQueue & notQueue) :
        client(cli),
        mutex(mtx),
        event(evt),
        queue(notQueue){
    }

    ~HTTPRequester() {
    }

    void runImpl() {
        if (!client.isInitialized() && !client.isClosed())
            client.init();
        Poco::AutoPtr<Poco::Notification> pNf;
        for (int i = 0; i < 20; i++) {
            pNf = queue.waitDequeueNotification(100);
            if (pNf)
                break;
        }
        if (client.isClosed()) {
            return;
        }
        if (!pNf)
            return;
        HTTPNotification * diNf = dynamic_cast<HTTPNotification*>(pNf.get());
        if (diNf != nullptr) {
            std::shared_ptr<Comm::DPWS::DPWS11Message> response = ce.exchangeHttp(*diNf->getMsg());
            if (response && !response->parseXML(response->getRawBuffer(), client.getKnownCustomActions()))
            {
                Util::DebugOut(Util::DebugOut::Error, "Client") << "XML parse error has been triggered in processing HTTP response.";
                response.reset();  // Error, do not evaluate
            }
            if (response)
                client.evaluateResponseMessage(response);
        }
        else {
            // Fetch WSDLs at the end of a (single device) discovery process
            WSDLNotification * loadNf = dynamic_cast<WSDLNotification*>(pNf.get());
            Util::StringVector wsdlAddrs = loadNf->getWSDLAddrs();
            for (auto &nextAddr : wsdlAddrs) {
                try {
                    if (client.isClosed())
                        break;
                    const Poco::URI uri(nextAddr);
                    Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());

                    std::string wsdlContent = ce.exchangeHttp(session, uri.getPathAndQuery(), "", true);
                    if (!wsdlContent.empty())
                        client.addWSDL(wsdlContent);
                    else
                        continue;

                    Poco::Mutex::ScopedLock lock(mutex);
                    Comm::DPWS::DPWS11WSDLParser wsdlparser;
                    std::vector<std::shared_ptr<Service>> remoteServices = client.getRemoteDevice()->getServices();
                    const std::string serviceAddr = "http://" + uri.getHost() + ":" + std::to_string(uri.getPort()) + uri.getPath();

                    if (!wsdlparser.parseWSDL(wsdlContent, serviceAddr, remoteServices)) {
                        Util::DebugOut(Util::DebugOut::Error, "Client") << "WSDL request failed due to parse error.";
                    }
                }
                catch (...) {
                    Util::DebugOut(Util::DebugOut::Error, "Client") << "WSDL request failed due to Exception.";
                }
            }
            if (!client.isClosed() && client.isSearchRunning() && queue.size() == 0) {
                Poco::Mutex::ScopedLock lock(mutex);
                std::vector<std::shared_ptr<Service>> remoteServices(client.getRemoteDevice()->getServices());
                for (auto &nextService : remoteServices) {
                    for (auto &nextOperation : nextService->getOperations()) {
                        client.addKnownCustomAction(nextOperation->getInputAction());
                        client.addKnownCustomAction(nextOperation->getOutputAction());
                    }
                }
                client.setSearchMode(SearchMode::NONE);
                // Signal event
                event.set();
                client.searchComplete();
            }
        }
    }

private:
    Client & client;
    HTTPClientExchanger ce;
    Poco::Mutex & mutex;
    Poco::Event & event;
    Poco::NotificationQueue & queue;

};
Client::Client()
{
    setSearchMode(SearchMode::NONE);
    initMembers();
	init();
    httpRequester.reset(new HTTPRequester(*this, mutex, waitSearch, httpExchangeQueue));
    httpRequester->start();
    clHttpExchanger = std::make_shared<HTTPClientExchanger>();
}

Client::Client(const Client & client) {
    setSearchMode(SearchMode::NONE);
    initMembers();
    init();
    this->remoteDevice = client.remoteDevice;
    addRemoteDeviceActions(this->remoteDevice);
    httpRequester.reset(new HTTPRequester(*this, mutex, waitSearch, httpExchangeQueue));
    httpRequester->start();
    clHttpExchanger = std::make_shared<HTTPClientExchanger>();
}

Client::Client(std::shared_ptr<Dev::Device> remote)
{
    setSearchMode(SearchMode::NONE);
    initMembers();
    init();
    this->remoteDevice = remote;
    addRemoteDeviceActions(this->remoteDevice);
    httpRequester.reset(new HTTPRequester(*this, mutex, waitSearch, httpExchangeQueue));
    httpRequester->start();
    clHttpExchanger = std::make_shared<HTTPClientExchanger>();
}

void Client::addRemoteDeviceActions(std::shared_ptr<Dev::Device> remote) {
    Poco::Mutex::ScopedLock lock(mutex);
    std::vector<std::shared_ptr<Service>> remoteServices(remote->getServices());
    for (auto &nextService : remoteServices) {
        for (auto &nextOperation : nextService->getOperations()) {
            addKnownCustomAction(nextOperation->getInputAction());
            addKnownCustomAction(nextOperation->getOutputAction());
        }
    }
}

Client::~Client()
{
	httpRequester->interrupt();
	if (!closed) {
		Util::DebugOut(Util::DebugOut::Error, "Client") << "Client deleted before closed!";
	}
	cleanRemoteReferences();
	helloHandler.reset();
}

bool Client::evaluateResponseMessage(const std::shared_ptr<DPWS11Message> dpws11Msg) {
	Poco::Mutex::ScopedLock lock(mutexCallback);
	const std::string& action(dpws11Msg->getIncomingAction());
	if (action.compare(WS_ACTION_PROBE_MATCHES) == 0) {
		handleAction_WS_ACTION_PROBE_MATCHES(dpws11Msg);
        return true;
	} else if (action.compare(WS_ACTION_RESOLVE_MATCHES) == 0) {
		handleAction_WS_ACTION_RESOLVE_MATCHES(dpws11Msg);
        return true;
	}
    return false;
}

void Client::downloadWSDLs(const Util::StringVector & wsdlAddrs) {
    httpExchangeQueue.enqueueNotification(new WSDLNotification(wsdlAddrs));
}

void Client::initMembers()
{
	closed = false;
    closing = false;
    initialized = false;
    xaddrSearchParam = "";
}

void Client::init() {
	if(CommunicationManager::device != nullptr) {
		// Clear list of manager (this) because stop deletes otherwise
		CommunicationManager::device->clearManagersWithoutDelete();
		CommunicationManager::device->stop();
	}
    localDevice.reset(new Device());
    std::shared_ptr<Service> service(new Service());
    service->setServiceId("N/A");
    localDevice->addService(service);
    localDevice->addManager(this);

    CommunicationManager::device = localDevice.get();
    
    // Start (device not running, no hello)
	startManager();
    initialized = true;
}

void Client::addDeviceTypeSearchParam(const Data::QName & type) {
	Poco::Mutex::ScopedLock lock(mutex);

	localDevice->addType(type);
}

Data::QVector Client::getDeviceTypeSearchParams() const {
    Poco::Mutex::ScopedLock lock(mutex);

    return localDevice->getTypes();
}

void Client::addDeviceScopeSearchParam(const std::string & scope) {
	Poco::Mutex::ScopedLock lock(mutex);

	localDevice->addScope(scope);
}

Util::StringVector Client::getDeviceScopeSearchParams() const {
    Poco::Mutex::ScopedLock lock(mutex);

    return localDevice->getScopes();
}

void Client::setDeviceEPRAdrSearchParam(const std::string & eprAdr) {
	Poco::Mutex::ScopedLock lock(mutex);
	localDevice->setEPRAddress(eprAdr);
}

std::string Client::getDeviceEPRAdrSearchParam()
{
    Poco::Mutex::ScopedLock lock(mutex);
    return localDevice->getEndpointReference().getAddress();
}

void Client::setDeviceXAddrSearchParam(const std::string & xaddr) {
    Poco::Mutex::ScopedLock lock(mutex);
    Binding adr(xaddr);
    xaddrSearchParam = xaddr;
}

void Client::addServiceTypeSearchParam(const Data::QName & type) {
	Poco::Mutex::ScopedLock lock(mutex);

	localDevice->getService(0)->addType(type);
}

Data::QVector Client::getServiceTypeSearchParams() const {
    Poco::Mutex::ScopedLock lock(mutex);

    return localDevice->getService(0)->getTypes();
}

std::string Client::getServiceIDSearchParam() const {
    Poco::Mutex::ScopedLock lock(mutex);

    return localDevice->getService(0)->getServiceId();
}

void Client::setServiceIDSearchParam(const std::string & id) {
	Poco::Mutex::ScopedLock lock(mutex);

    localDevice->getService(0)->setServiceId(id);
}

void Client::clearSearchParams() {
	Poco::Mutex::ScopedLock lock(mutex);

	localDevice->setEPRAddress("N/A");
	localDevice->clearTypes();
	localDevice->clearScopes();
    localDevice->getService(0)->clearTypes();
    localDevice->getService(0)->setServiceId("N/A");
    xaddrSearchParam = "";
}

void Client::reset() {
	localDevice->stop();
	cleanRemoteReferences();
	init();
}

bool Client::foundAny() {
    Poco::Mutex::ScopedLock lock(mutex);

    if (isSearchComplete())
        return true;

    for (auto & next : clients)
        if (next->isSearchComplete())
            return true;
    return false;
}

void Client::search() {
	Poco::Mutex::ScopedLock lock(mutex);

	// Clean up
	cleanRemoteReferences();
	DPWS11Message msg;
    if (xaddrSearchParam.length() > 0) {
        // Create directed probe to trigger metadata request (unicast)
        msg.createProbeMessage(*localDevice, xaddrSearchParam);
        setSearchMode(SearchMode::PROBE);
    }
	else if (localDevice->getEndpointReference().getAddress().compare("N/A") != 0) {
		// Create multicast resolve (search by EPR)
        msg.createResolveMessage(*localDevice);
        setSearchMode(SearchMode::RESOLVE);
	} else {
		// Create multicast probe
        msg.createProbeMessage(*localDevice);
        setSearchMode(SearchMode::PROBE);
	}
    if (xaddrSearchParam.length() > 0) {
        sendMessage(msg);
    }
    else for (unsigned int i = 0; i < (UDP_MULTICAST_UDP_REPEAT + 1); ++i) {
        sendMessage(msg);
        if (i > 0) {
        	Poco::Thread::sleep(i * 10);
        }
    }
}

bool Client::pingSync(int timeout)
{
	Poco::Mutex::ScopedLock lock(mutex);
    return pingSync(timeout, *remoteDevice, remoteDevice->getDefaultTransportAddr(DPWS11));
}

bool Client::pingSync(int timeout, const Device & dev, const std::string & xaddr)
{
	if (closed)
		return false;
    std::shared_ptr<DPWS11Message> msg = std::make_shared<DPWS11Message>();
    // Create directed probe
    msg->createProbeMessage(dev, xaddr);
    setSearchMode(SearchMode::NONE);
    //httpExchangeQueue.enqueueNotification(new HTTPNotification(msg));
	// HTTP exchange
	std::shared_ptr<DPWS11Message> response = exchangeMessage(msg, timeout);
	if (response == nullptr)
		return false;
	return true;
}

bool Client::searchSync(int timeout) {
	search();
	if (timeout == 0)
		timeout = 86400000;
	bool signaled = waitSearch.tryWait(timeout);
	return signaled;
}

int Client::getRemoteServiceIndex(const std::string& action, Device*& outDev) {
    int serviceIndex = -1;
    outDev = nullptr;

    size_t sSize = remoteDevice->getServiceCount();
    for (size_t i = 0; i < sSize; ++i) {
        auto & nextService = remoteDevice->getService(i);
		std::shared_ptr<Data::Operation> o(nextService->getOperation(action));

		if (o != nullptr) {
			serviceIndex = i;
			outDev = nextService->getParentDevice();
			break;
		}
	}

    return serviceIndex;
}

bool Client::isActionAvailable(std::string action) {
    Device * dev = nullptr;
    return (getRemoteServiceIndex(action, dev) != -1 && dev != nullptr);
}

bool Client::invokeSync(const std::string & action, Parameters & input, Parameters * output, int timeout) {
	Poco::Mutex::ScopedLock lock(mutex);
	if(!remoteDevice)
		return false;

	Device * dev = nullptr;

	int serviceIndex = getRemoteServiceIndex(action, dev);
	if (serviceIndex == -1 || dev == nullptr) {
		return false;
	}

    std::string invokedOperation = dev->getService(serviceIndex)->getOperation(action)->getName();

	// Create invoke message
    std::shared_ptr<DPWS11Message> msg = std::make_shared<DPWS11Message>();
	msg->createInvokeMessage(*dev, serviceIndex, action, input);

	// HTTP exchange
	std::shared_ptr<DPWS11Message> response = exchangeMessage(msg, timeout);
	if (response == nullptr)
		return false;

	// Evaluate response
	Parameters & parametersInMessage = response->parameters;

	if (parametersInMessage.size() > 0 && output != nullptr) {
		const std::string pName(parametersInMessage.at(0).getName());

		if (pName.find(invokedOperation) != std::string::npos) {
			Parameters children = parametersInMessage.at(0).getCopyChildren();
			output->insert(output->end(), children.begin(), children.end());
		} else {
			output->insert(output->end(), parametersInMessage.begin(), parametersInMessage.end());
		}
		// Last parameter contains raw content
		output->emplace_back("BodyRawContent", Parameter::Type::CDM, response->bodyRawContent);
	}

	return true;
}

bool Client::invokeSync(const QName & portType, const std::string & operation, Parameters & input, Parameters * output, int timeout) {
    return invokeSync(Data::OperationHelpers::getDefaultInputAction(operation, portType), input, output, timeout);
}

void Client::handleAction_WS_ACTION_HELLO(Comm::DPWS::DPWS11Message & dpws11Msg) {
	const std::string & incomingEPR(dpws11Msg.getIncomingDeviceEPRAddress().getAddress());
	if (helloHandler) {
		helloHandler->helloReceived(incomingEPR);
	}
	// Check if current remote device matches endpoint address, check metadata version
	if (!remoteDevice)
		return;

    const std::string & remoteDeviceEPR(remoteDevice->getEndpointReference().getAddress());

    int versionRemote = remoteDevice->getMetaDataVersion();
	int versionNew = dpws11Msg.getIncomingMetadataVersion();

	if ((remoteDeviceEPR.compare(incomingEPR) == 0)
            && (versionNew > versionRemote)
			&& (dpws11Msg.getIncomingXAddrs().compare("") != 0)) {
		// Found match. Update discovery info.
        storeBasicDiscoveryInfo(remoteDevice, dpws11Msg);
	}
}

void Client::handleAction_WS_ACTION_BYE(Comm::DPWS::DPWS11Message & ) {

	// TODO: handle 'Bye' message

}

std::shared_ptr<Message> Client::udpMulticastCallback(const Message & msg) {
	if (closed || closing) {
		return nullptr;
	}
	// Call base method to parse message content
	std::shared_ptr<Message> message(DPWS11CommunicationManager::udpMulticastCallback(msg));

	Poco::Mutex::ScopedLock lock(mutexCallback);

	if(message == nullptr) {
		return nullptr;
	}

	std::shared_ptr<DPWS11Message> dpws11Msg(std::dynamic_pointer_cast<DPWS11Message>(message));
	const std::string & action(dpws11Msg->getIncomingAction());

	if (action.compare(WS_ACTION_HELLO) == 0) {
		handleAction_WS_ACTION_HELLO(*dpws11Msg);
	} else if (action.compare(WS_ACTION_BYE) == 0) {
		handleAction_WS_ACTION_BYE(*dpws11Msg);
	}
    
	//for (auto & it : actionHandlers) {
	//	if (action == it.first && !it.second->isUnicast()) {
	//		it.second->handleAction(dpws11Msg.get());
	//	}
	//}

	return message;
}

void Client::cleanRemoteReferences() {
    Poco::Mutex::ScopedLock lock(mutex);
    
    remoteDevice.reset();
}

void Client::storeBasicDiscoveryInfo(std::shared_ptr<Device> dev, const Comm::DPWS::DPWS11Message & dpws11Msg) {
    Poco::Mutex::ScopedLock lock(mutex);
    // Save basic discovery info in device
	Dev::EndpointReference epr = dev->getEndpointReference();
	epr.setAddress(dpws11Msg.getIncomingDeviceEPRAddress().getAddress());
    dev->setEndpointReference(epr);

    dev->setMetaDataVersion(dpws11Msg.getIncomingMetadataVersion());

    if(dpws11Msg.getIncomingScopes().compare("") != 0) {
        dev->clearScopes();
        dev->addScopes(Util::splitString(dpws11Msg.getIncomingScopes(), ' '));
    }

    if(!dpws11Msg.getIncomingTypes().empty()) {
        dev->clearTypes();
        dev->addTypes(dpws11Msg.getIncomingTypes());
    }

    if (dpws11Msg.getIncomingXAddrs().compare("") != 0) {
		Util::StringVector xAddrs = Util::splitString(dpws11Msg.getIncomingXAddrs(), ' ');
		for (unsigned int i = 0; i < xAddrs.size(); ++i) {
			// ipv6 not supported
			if (xAddrs[i].find('[') == std::string::npos && xAddrs[i].find(']') == std::string::npos) {
				// Check if device is reachable using this xaddr
				try{
					Poco::Net::StreamSocket ss;
					std::shared_ptr<Binding> discoveryBinding = std::make_shared<Binding>(xAddrs[i]);
					Poco::Net::SocketAddress socketAdr (discoveryBinding->getIp(), discoveryBinding->getPort());
					ss.connect(socketAdr, 1000000);
					// Found suitable connection (no exception)
					dev->addBinding(DPWS11, discoveryBinding);
					dev->setLocalAdapterAddress(ss.address().host().toString());
					ss.close();
					break;
				} catch(Poco::Exception& ) {
					// continue
				}
			}
		}
	}
}

std::vector<std::shared_ptr<Client>> Client::getClients() {
    Poco::Mutex::ScopedLock lock(mutex);
    return clients;
}

bool Client::isInitialized() {
    return initialized;
}

std::shared_ptr<DPWS11Message> Client::exchangeMessage(const std::shared_ptr<DPWS11Message> dpws11Msg, int timeout) {
    dpws11Msg->setSendProtocol(Message::TCP_HTTP_BODY);
    DPWS11Message::generateRawBuffer(*dpws11Msg);
    std::shared_ptr<DPWS11Message> response = clHttpExchanger->exchangeHttp(*dpws11Msg, timeout);
    if (response && !response->parseXML(response->getRawBuffer(), getKnownCustomActions()))
    {
        Util::DebugOut(Util::DebugOut::Error, "Client") << "XML parse error has been triggered in processing HTTP response.";
        response.reset();  // Error, do not evaluate
    }
    return response;
}

void Client::discoverRemoteDevice(std::shared_ptr<Device> rmDev, SearchMode sm) {
    setSearchMode(sm);
    Poco::Mutex::ScopedLock lock(mutex);
    this->remoteDevice = rmDev;
    std::shared_ptr<DPWS11Message> newMsg = std::make_shared<DPWS11Message>();
    newMsg->createGetMessage(*this->remoteDevice);
    std::shared_ptr<DPWS11Message> response = exchangeMessage(newMsg);
    if (response)
    	handleAction_WS_ACTION_GET_RESPONSE(response);
    //httpExchangeQueue.enqueueNotification(new HTTPNotification(newMsg));
}

void Client::createRemoteDevice(const std::shared_ptr<DPWS11Message> dpws11Msg, SearchMode sm) {
    // Check for duplicates
    if (remoteDevice && remoteDevice->getEndpointReference().getAddress().compare(dpws11Msg->getIncomingDeviceEPRAddress().getAddress()) == 0)
        return;
    for (auto &nextClient : clients) {
        std::shared_ptr<Device> nextDevice = nextClient->getRemoteDevice();
        const std::string & knownDeviceEPR(nextDevice->getEndpointReference().getAddress());
        if ((knownDeviceEPR.compare(dpws11Msg->getIncomingDeviceEPRAddress().getAddress()) == 0))
            return;
    }

    std::shared_ptr<Device> rmDev = std::make_shared<Device>();
    if (!remoteDevice) {
        Poco::Mutex::ScopedLock lock(mutex);
        remoteDevice = rmDev;
        storeBasicDiscoveryInfo(remoteDevice, *dpws11Msg);
        discoverRemoteDevice(remoteDevice, sm);
    }
    else {
        std::shared_ptr<Client> newClient(new Client(rmDev));
        for (auto & next : getDeviceTypeSearchParams()) 
            newClient->addDeviceTypeSearchParam(next);
        for (auto & next : getDeviceScopeSearchParams())
            newClient->addDeviceScopeSearchParam(next);
        for (auto & next : getServiceTypeSearchParams())
            newClient->addServiceTypeSearchParam(next);
        newClient->setServiceIDSearchParam(getServiceIDSearchParam());
        clients.push_back(newClient);
        newClient->storeBasicDiscoveryInfo(rmDev, *dpws11Msg);
        newClient->discoverRemoteDevice(rmDev, sm);
    }
}

void Client::handleAction_WS_ACTION_PROBE_MATCHES(const std::shared_ptr<DPWS11Message> dpws11Msg) {
	if (dpws11Msg->getIncomingXAddrs().compare("") != 0) {
        createRemoteDevice(dpws11Msg, SearchMode::PROBE);
	}
}

void Client::handleAction_WS_ACTION_RESOLVE_MATCHES(const std::shared_ptr<DPWS11Message> dpws11Msg) {
	if (dpws11Msg->getIncomingXAddrs().compare("") != 0)
	{
        createRemoteDevice(dpws11Msg, SearchMode::RESOLVE);
	}
}

void Client::handleAction_WS_ACTION_GET_RESPONSE(const std::shared_ptr<DPWS11Message> dpws11Msg) {
	// Get basic device characteristics and physical addresses of services (if available) from GET response
    remoteDevice->setDeviceCharacteristics(dpws11Msg->getIncomingDeviceCharacteristics());
	std::vector<std::shared_ptr<Service>> hostedServices(dpws11Msg->getHostedServices());
	std::vector<std::shared_ptr<Service>>::iterator serviceIt;

	const Data::QVector & localTypes = localDevice->getService(0)->getTypes();
	// Evaluate hosted section
	for (serviceIt = hostedServices.begin(); serviceIt != hostedServices.end(); ++serviceIt) {
		bool match = true;

		std::shared_ptr<Service> s(*serviceIt);

		// match types
		const Data::QVector & remoteTypes = s->getTypes();
		Data::QVector::const_iterator localIt;
		for (localIt = localTypes.begin(); localIt != localTypes.end(); ++localIt) {
			match &= (find(remoteTypes.begin(), remoteTypes.end(), *localIt) != remoteTypes.end());
		}

		// match service id
		const std::string localId(localDevice->getService(0)->getServiceId());
		const std::string remoteServiceId(s->getServiceId());
		if (localId.compare("N/A") != 0) {
			match &= (localId.compare(remoteServiceId) == 0);
		}

		if (!match)
			continue;

        addRemoteService(s);
        std::shared_ptr<DPWS11Message> newMsg = std::make_shared<DPWS11Message>();
        newMsg->copyRaw(*dpws11Msg);
        newMsg->setReceiveProtocol(Message::UNKNOWN_PROTOCOL);

		// Request metadata of service
        newMsg->createGetMetadataMessage(*remoteDevice, remoteDevice->getServiceCount() - 1);
        std::shared_ptr<DPWS11Message> response = exchangeMessage(newMsg);
        if (response)
        	handleAction_WS_ACTION_GET_METADATA_RESPONSE(response);
        //httpExchangeQueue.enqueueNotification(new HTTPNotification(newMsg));
	}
}

void Client::handleAction_WS_ACTION_GET_METADATA_RESPONSE(const std::shared_ptr<DPWS11Message> dpws11Msg) {
    // MDPWS streaming
	std::shared_ptr<DPWS11SoapParserHandler> ph(dpws11Msg->getMessageParser().getParseHandler(WS_ACTION_GET_METADATA_RESPONSE));
	std::shared_ptr<DPWS11MetadataSoapParserHandler> mdsph(std::dynamic_pointer_cast<DPWS11MetadataSoapParserHandler>(ph));
	const std::vector<std::string> & oscpStreamAddresses = mdsph->getStreamingAddresses();
    for (const auto & nextAdr : oscpStreamAddresses)
    {
        std::shared_ptr<Binding> streamBinding(new Binding(nextAdr));
        streamBinding->setType(AbstractBinding::UDP_MULTICAST);
        streamBindings.push_back(streamBinding);
    }

	// Request WSDL data
	const Util::StringVector & wsdlAddrs = dpws11Msg->getIncomingWSDLLocations();
	downloadWSDLs(wsdlAddrs);
}

void Client::enableStreaming() {
    for (const auto & nextBnd : streamBindings) {
        injectBinding(nextBnd);
    }
}

void Client::setClosing(bool closing) {
	Poco::Mutex::ScopedLock lock(mutexCallback);
    this->closing = closing;
}

std::shared_ptr<Message> Client::unicastCallback(const Message & msg) {
	Poco::Mutex::ScopedLock lock(mutexCallback);
	if (closed || closing) {
		Util::DebugOut(Util::DebugOut::Error, "Client") << "Unicast callback on closed client: " << msg;
        return nullptr;
    }
    std::shared_ptr<DPWS11Message> message;
    if ((message = std::dynamic_pointer_cast<DPWS11Message>(DPWS11CommunicationManager::unicastCallback(msg))) != nullptr) {
        return message;
    }

    message.reset(new DPWS11Message());
    message->copyRaw(msg);

    if (!message->parseXML(message->getRawBuffer(), getKnownCustomActions()))
    {
        Util::DebugOut(Util::DebugOut::Info, "Client") << "XML parse error has been triggered in unicastCallback.";
        return nullptr;
    }

    if (message == nullptr) {
        return nullptr;
    }

    if (evaluateResponseMessage(message))
        return message;
    return nullptr;
}

void Client::setHelloReceivedHandler(std::shared_ptr<HelloReceivedHandler> handler) {
	Poco::Mutex::ScopedLock lock(mutex);
	helloHandler = handler;
}

bool Client::subscribeSync(const std::string & action, long duration, std::shared_ptr<EventSink> sink, std::shared_ptr<AbstractBinding> newBinding, int timeout) {
    Poco::Mutex::ScopedLock lock(mutex);
	if (!remoteDevice)
		return false;
    if (sink == nullptr)
    {
        Util::DebugOut(Util::DebugOut::Error, "Client") << "Subscribe failed, event sink is missing!";
        return false;
    }
	if (sink->getName().length() == 0)
		sink->setName("DefaultSink");
	// The source service (remote)
	Device* dev = nullptr;
	int serviceIndex = getRemoteServiceIndex(action, dev);
	if (serviceIndex == -1 || dev == nullptr)
	{
		return false;
	}
	std::shared_ptr<AbstractBinding> sinkBinding(newBinding);
	if (newBinding == nullptr)
	{
		std::string bi = OSCLibrary::getInstance()->getBindInterface();
		const std::string & bindingIp(bi == "0.0.0.0" ? dev->getLocalAdapterAddress() : bi);
		const std::string & bindingPath(sink->getName());
		sinkBinding.reset(new Binding(bindingIp,
			OSCLibrary::getInstance()->extractNextPort(),
			bindingPath));
		const std::string bindingString(sinkBinding->toString());
		Util::DebugOut(Util::DebugOut::Info, "Client") << "Autobinding event sink to: " << bindingString;
	}
	std::shared_ptr<Service> sourceService(dev->getService(serviceIndex));
	std::shared_ptr<Data::Operation> sourceOp(sourceService->getOperation(action));
	if (serviceIndex == -1 || sourceOp == nullptr)
	{
		return false;
	}
	// The sink service (local, create new)
	std::shared_ptr<Service> sinkService(new Service());
    sinkServices.push_back(sinkService);
	sinkService->setServiceId("DefaultEventSink");
	sinkService->addBinding(DPWS11, sinkBinding);
	// Use the same port type as the source
	QName sourcePortType = sourceOp->getPortType();
	sink->setPortType(sourcePortType);
	// Use also the same actions as the source, only switch input and output to connect the two
	sink->setInputAction(sourceOp->getOutputAction());
	sink->setOutputAction(sourceOp->getInputAction());
	// Add unique identifier to sink service
	const std::string sinkIdentifier(Util::DefaultUUIDGenerator::getUUID());
	Dev::EndpointReference sinkEpr;
	sinkEpr.setReferenceParameters(sinkIdentifier);
	sinkEpr.setAddress(sinkService->getDefaultTransportAddr(DPWS11));
	sinkService->setEndpointReference(sinkEpr);
	// Finish up
	sinkService->addOperation(sink);
	localDevice->addService(sinkService);
	sinkService->start();
    injectService(sinkService);
	// Events can now be received, create subscribe message
	std::shared_ptr<DPWS11Message> msg = std::make_shared<DPWS11Message>();
	msg->createSubscribeMessage(action, duration, *localDevice, localDevice->getServiceCount() - 1, *dev, serviceIndex);
    //httpExchangeQueue.enqueueNotification(new HTTPNotification(msg));

	// HTTP exchange
	std::shared_ptr<DPWS11Message> response = exchangeMessage(msg, timeout);
	if (response == nullptr)
		return false;

	// Subscribe response
	const Dev::EndpointReference & subManEpr = response->getIncomingSubManEPRAddress();
    sinkService->setEndpointReference(subManEpr);

    return true;
}

bool Client::subscribeSync(Data::QName& portType, const std::string& source, long duration, std::shared_ptr<EventSink> sink, std::shared_ptr<AbstractBinding> newBinding, int timeout) {
	return subscribeSync(Data::OperationHelpers::getDefaultOutputActionForEventSource(source, portType), duration, sink, newBinding, timeout);
}

bool Client::renewSync(Data::QName & portType, const std::string & source, long duration, std::shared_ptr<EventSink> sink, int timeout) {
	return renewSync(Data::OperationHelpers::getDefaultOutputActionForEventSource(source, portType), duration, sink, timeout);
}

bool Client::renewSync(const std::string & action, long duration, std::shared_ptr<EventSink> sink, int timeout) {
    {
        Poco::Mutex::ScopedLock lock(mutex);
        if (!remoteDevice)
            return false;
        if (sink == nullptr)
        {
            Util::DebugOut(Util::DebugOut::Error, "Client") << "Renew failed, event sink is missing!";
            return false;
        }
        std::shared_ptr<DPWS11Message> msg = std::make_shared<DPWS11Message>();
        std::shared_ptr<Dev::Service> localSinkService;
        {
            size_t sSize = localDevice->getServiceCount();
            for (size_t i = 0; i < sSize; ++i) {
                auto & nextService = localDevice->getService(i);
                std::shared_ptr<Data::Operation> o(nextService->getOperation(action));
                if (o != nullptr) {
                    localSinkService = nextService;
                    break;
                }
            }
        }
        if (localSinkService == nullptr)
        {
            Util::DebugOut(Util::DebugOut::Error, "Client") << "Renew failed, local sink service is missing!";
            return false;
        }
        Device * dev = nullptr;
        int serviceIndex = getRemoteServiceIndex(action, dev);
        if (serviceIndex == -1 || dev == nullptr)
        {
            return false;
        }
        std::shared_ptr<Dev::Service> remoteSourceService(dev->getService(serviceIndex));
        msg->createRenewMessage(*localSinkService, *remoteSourceService, duration);
        //httpExchangeQueue.enqueueNotification(new HTTPNotification(msg));

    	// HTTP exchange
    	std::shared_ptr<DPWS11Message> response = exchangeMessage(msg, timeout);
    	if (response == nullptr)
    		return false;
    }
    return true;
}

bool Client::unsubscribeSync(Data::QName& portType, const std::string& source, std::shared_ptr<EventSink> sink, int timeout)
{
	return unsubscribeSync(Data::OperationHelpers::getDefaultOutputActionForEventSource(source, portType), sink, timeout);
}

bool Client::unsubscribeSync(const std::string& action, std::shared_ptr<EventSink> sink, int timeout)
{
    {
        Poco::Mutex::ScopedLock lock(mutex);
        if (!remoteDevice)
            return false;
        if (sink == nullptr)
        {
            Util::DebugOut(Util::DebugOut::Error, "Client") << "Unsubscribe failed, event sink is missing!";
            return false;
        }
        std::shared_ptr<DPWS11Message> msg = std::make_shared<DPWS11Message>();
        std::shared_ptr<Service> localSinkService;
        size_t sSize = localDevice->getServiceCount();
        for (size_t i = 0; i < sSize; ++i) {
            auto & nextService = localDevice->getService(i);
            std::shared_ptr<Data::Operation> o = nextService->getOperation(action);
            if (o != nullptr) {
                localSinkService = nextService;
                break;
            }
        }
        if (localSinkService == nullptr)
        {
            Util::DebugOut(Util::DebugOut::Error, "Client") << "Unsubscribe failed, local sink service is missing!";
            return false;
        }
        Device* dev = nullptr;
        int serviceIndex = getRemoteServiceIndex(action, dev);
        if (serviceIndex == -1 || dev == nullptr)
        {
            return false;
        }
        std::shared_ptr<Dev::Service> remoteSourceService(dev->getService(serviceIndex));
        msg->createUnsubscribeMessage(*localSinkService, *remoteSourceService);
        localSinkService->stop();
        localDevice->removeService(localSinkService);
        withdrawService(localSinkService);
        //httpExchangeQueue.enqueueNotification(new HTTPNotification(msg));

    	// HTTP exchange
    	std::shared_ptr<DPWS11Message> response = exchangeMessage(msg, timeout);
    	if (response == nullptr)
    		return false;
    }
	return true;
}

void Client::close(bool all) {
	closed = true;
    httpRequester->interrupt();
    localDevice->stop();
    if (all) {
        for (auto & next : getClients()) {
            next->close();
        }
    }
}

void Client::handleAction_WS_ACTION_PROBE(Comm::DPWS::DPWS11Message * ) {

}

void Client::handleAction_WS_ACTION_RESOLVE(Comm::DPWS::DPWS11Message * ) {

}

void Client::addRemoteService(std::shared_ptr<Dev::Service> service) {
    Poco::Mutex::ScopedLock lock(mutex);

    remoteDevice->addService(service);

	const Data::OperationVector & ov = service->getOperations();
	Data::OperationVector::const_iterator oIt;
	for (oIt = ov.begin(); oIt != ov.end(); ++oIt) {
		addKnownCustomAction((*oIt)->getInputAction());
		addKnownCustomAction((*oIt)->getOutputAction());
	}
}

std::shared_ptr<Dev::Device> Client::getRemoteDevice() {
    return remoteDevice;
}

void Client::addKnownCustomAction(const std::string & action) {
	Poco::Mutex::ScopedLock lock(mutex);

	DPWS11CommunicationManager::addKnownCustomAction(action);
}

void Client::initWSDLCollector() {
	Poco::Mutex::ScopedLock lock(mutex);
	this->wsdlCollector.reset(new std::vector<std::string>);
}

std::vector<std::string> Client::getWSDL() {
	Poco::Mutex::ScopedLock lock(mutex);
	std::vector<std::string> res = *wsdlCollector;
	return res;
}

void Client::addWSDL(std::string wsdl) {
	Poco::Mutex::ScopedLock lock(mutex);
	if (wsdlCollector) {
		wsdlCollector->push_back(wsdl);
	}
}

bool Client::isClosed() {
	return closed;
}

bool Client::isSearchRunning() {
	Poco::Mutex::ScopedLock lock(mutex);

    return searchMode == SearchMode::PROBE || searchMode == SearchMode::RESOLVE;
}

bool Client::isAnySearchRunning() {
    Poco::Mutex::ScopedLock lock(mutex);
    for (auto& next : clients) {
        if (next->getSearchMode() == SearchMode::PROBE || next->getSearchMode() == SearchMode::RESOLVE)
            return true;
    }

    return searchMode == SearchMode::PROBE || searchMode == SearchMode::RESOLVE;
}


void Client::setSearchMode(SearchMode mode) {
	Poco::Mutex::ScopedLock lock(mutex);

    this->searchMode = mode;
}

SearchMode Client::getSearchMode() {
    Poco::Mutex::ScopedLock lock(mutex);

    return this->searchMode;
}

void Client::invokeResponse() {
}

void Client::searchComplete() {
    searchCompleted = true;
}

bool Client::isSearchComplete() {
    return searchCompleted;
}

} /* namespace Cli */
} /* namespace OSCLib */
