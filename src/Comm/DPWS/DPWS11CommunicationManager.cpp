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
*  @file DPWS11CommunicationManager.cpp
*  @project OSCLib
*  @date 24.08.2011
*  @author besting
*  @copyright (c) SurgiTAIX AG
*/

#include "OSCLib/OSCLibrary.h"
#include "OSCLib/Comm/Binding.h"
#include "OSCLib/Comm/HTTPClientExchanger.h"
#include "OSCLib/Comm/NetworkInterface.h"
#include "OSCLib/Comm/Soap/SoapEnvelope.h"
#include "OSCLib/Comm/DPWS/DPWS11CommunicationManager.h"
#include "OSCLib/Comm/DPWS/DPWS11Constants.h"
#include "OSCLib/Comm/DPWS/DPWS11Message.h"
#include "OSCLib/Comm/DPWS/DPWS11ActionHandler.h"
#include "OSCLib/Data/QName.h"
#include "OSCLib/Dev/Device.h"
#include "OSCLib/Dev/EndpointReference.h"
#include "OSCLib/Dev/Service.h"
#include "OSCLib/Util/DebugOut.h"
#include "OSCLib/Util/Task.h"
#include "Poco/Event.h"
#include "Poco/Notification.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/ScopedLock.h"
#include "Poco/Thread.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/NetException.h"

#include <iterator>
#include <sstream>
#include <string>
#include <algorithm>

using namespace OSCLib::Comm::Soap;
using namespace OSCLib::Dev;
using namespace OSCLib::Data;
using namespace OSCLib::Util;

namespace OSCLib {
namespace Comm {
namespace DPWS {

class DPWSHttpRequestHandler : public Poco::Net::HTTPRequestHandler {

public:

    DPWSHttpRequestHandler(DPWS11CommunicationManager & dm) : dm(dm) {
    }

    virtual ~DPWSHttpRequestHandler() {
    }

    virtual void handleRequest(Poco::Net::HTTPServerRequest & request, Poco::Net::HTTPServerResponse & response) override {
        try {
            std::string content;
            if (!getContentFromStream(request.stream(), content))
                return;
            if (content.empty())
                content = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
            content += "<httpinfo><url>" + request.getURI() + "</url><type>" + request.getMethod() + "</type></httpinfo>";
            Poco::Net::SocketAddress clientAddr = request.clientAddress();
            Poco::Net::SocketAddress serverAddr = request.serverAddress();
            Message msg;
            msg.setRawBuffer(content);
            msg.setSource(std::shared_ptr<IPBinding>(new IPBinding(clientAddr)));
            msg.setDispatcher(std::shared_ptr<IPBinding>(new IPBinding(serverAddr)));
            msg.setReceiveProtocol(Message::TCP_HTTP);
            msg.setRouting(Message::UNICAST);
            if (!OSCLibrary::getInstance()->getNetInterface()->isValidUnicastCallback(&dm)) {
                DebugOut(DebugOut::Error, "DPWSHttpRequestHandler") << "Callback invalid, message discarded (in). ";
                return;
            }
            std::shared_ptr<DPWS11Message> retMsg = std::dynamic_pointer_cast<DPWS11Message>(dm.unicastCallback(msg));
            if (!retMsg) {
                response.setStatusAndReason(Poco::Net::HTTPResponse::HTTPStatus::HTTP_NOT_FOUND);
                response.setContentLength(0);
                response.send();
                return;
            }
            response.setStatus(Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_OK);
            retMsg->setSendProtocol(Message::TCP_HTTP_BODY);
            DPWS11Message::generateRawBuffer(*retMsg);
            if (retMsg->getRawBuffer().empty()) {
                response.setStatusAndReason(Poco::Net::HTTPResponse::HTTPStatus::HTTP_ACCEPTED);
                response.setContentLength(0);
            }
            std::string sendStr = retMsg->getRawBuffer();
            response.setContentType("application/soap+xml");
            response.setContentLength(sendStr.length());
            //std::cout << retMsg->getShortName() << std::endl << std::flush;
            response.send() << sendStr << std::flush;
        }
        catch (Poco::Exception & e) {
            DebugOut(DebugOut::Error, "DPWSHttpRequestHandler") << "DPWSHttpRequestHandler::handleRequest() caused exception: " << e.message();
        }
        catch (...) {
            DebugOut(DebugOut::Error, "DPWSHttpRequestHandler") << "DPWSHttpRequestHandler::handleRequest() caused exception.";
        }
    }

private:

    bool getContentFromStream(std::istream & req, std::string & result) {
        std::string tmp;
        tmp.reserve(16384);
        while (!req.eof()) {
            if (req.fail())
                return false;
            getline(req, tmp);
            result += tmp;
        }
        return true;
    }

    DPWS11CommunicationManager & dm;

};

class DPWSHttpFactory : public Poco::Net::HTTPRequestHandlerFactory {

public:

    DPWSHttpFactory(DPWS11CommunicationManager & dm) : dm(dm) {
    }

    virtual ~DPWSHttpFactory() = default;

    virtual Poco::Net::HTTPRequestHandler * createRequestHandler(const Poco::Net::HTTPServerRequest & request) override {
    	Poco::Mutex::ScopedLock lock(mutex);
        return new DPWSHttpRequestHandler(dm);
    }

private:
    DPWS11CommunicationManager & dm;
    Poco::Mutex mutex;

};

DPWS11CommunicationManager::DPWS11CommunicationManager()
{
}

DPWS11CommunicationManager::~DPWS11CommunicationManager()
{
}

void DPWS11CommunicationManager::handleAction_invoke(std::shared_ptr<DPWS11Message> msg, int index) {
    // Invoke request, try invoking service method
    if (index >= 0)
    {
        msg->createInvokeResponse(*device, (unsigned int)index);
    }
}

void DPWS11CommunicationManager::removeKnownCustomAction(const std::string & action) {
    Poco::Mutex::ScopedLock lock(mutexCustomActions);
	knownCustomActions.erase(action);
}

bool DPWS11CommunicationManager::sendMessage(DPWS11Message & msg)
{
    if (msg.getSendProtocol() == Message::UNKNOWN_PROTOCOL)
    {
        DebugOut(DebugOut::Error, "DPWS11CommunicationManager") << "Unknown send protocol.";
        return false;
    }
    else if (msg.getRouting() == Message::UNKNOWN_ROUTING)
    {
        DebugOut(DebugOut::Error, "DPWS11CommunicationManager") << "Unknown routing method.";
        return false;
    }

    DPWS11Message::generateRawBuffer(msg);

    if (msg.getSendProtocol() == Message::UDP_MULTICAST && msg.getId().length() > 0) {
        trackMsgId(msg.getId());
    }

    // TCP / HTTP message
    if (msg.getSendProtocol() == Message::TCP_HTTP) {
        DebugOut(DebugOut::Full, "DPWS11CommunicationManager") << "Sending message (TCP unicast).";
        //DebugOut(DebugOut::Verbose, "DefaultNetworkInterface") << msg;
        std::shared_ptr<Comm::DPWS::DPWS11Message> response;
        if (msg.getShortName() == "FireEvent")
        	response = cmHttpExchanger->exchangeHttp(msg, -1);  // One-way message
        else
        	response = cmHttpExchanger->exchangeHttp(msg);
        if (response && !response->parseXML(response->getRawBuffer(), getKnownCustomActions()))
        {
            Util::DebugOut(Util::DebugOut::Error, "DPWS11CommunicationManager") << "XML parse error has been triggered in processing HTTP response.";
            response.reset();  // Error, do not evaluate
        }
        if (response) {  // Response from DPWS client
            if (!OSCLibrary::getInstance()->getNetInterface()->isValidUnicastCallback(this))
                DebugOut(DebugOut::Error, "DPWS11CommunicationManager") << "Callback invalid, message discarded (in). ";
            else
                std::dynamic_pointer_cast<Comm::DPWS::DPWS11Message>(unicastCallback(*response));
        }
        return true;
    }

    // UDP message
    if (OSCLibrary::getInstance()->getNetInterface()->sendMessage(this, msg, msg.getShortName()))
    {
        if (msg.getSendProtocol() != Message::TCP_HTTP)
            device->incMessageNumber();
        return true;
    }
    return false;
}

std::shared_ptr<Message> DPWS11CommunicationManager::udpMulticastCallback(const Message & msg)
{
	Poco::Mutex::ScopedLock lock(mutexCallback);
	std::shared_ptr<DPWS11Message> dpws11Msg(new DPWS11Message());
    dpws11Msg->copyRaw(msg);
    if (!dpws11Msg->parseXML(dpws11Msg->getRawBuffer(), getKnownCustomActions())) {
        DebugOut(DebugOut::Info, "DPWS11CommunicationManager") << "XML parse error has been triggered in udpMulticastCallback.";
        return nullptr;
    }
    // Check for duplicate or own messages
    if (!validateMsgId(dpws11Msg->getIncomingId()))
    {
        DebugOut(DebugOut::Info, "DPWS11CommunicationManager") << "Message discarded (duplicate or own). Id: " << dpws11Msg->getIncomingId();
        return nullptr;
    }
    // track message id
    trackMsgId(dpws11Msg->getIncomingId());

    const std::string & action(dpws11Msg->getIncomingAction());

    if (action.compare(WS_ACTION_RESOLVE) == 0) {
        handleAction_WS_ACTION_RESOLVE(dpws11Msg.get());
    }
    else if (action.compare(WS_ACTION_PROBE) == 0) {
        handleAction_WS_ACTION_PROBE(dpws11Msg.get());
    }

	for (auto & it : actionHandlers) {
		if (action == it.first && !it.second->isUnicast()) {
			it.second->handleAction(dpws11Msg.get());
		}
	}

    return dpws11Msg;
}

void DPWS11CommunicationManager::handleAction_WS_ACTION_GET_METADATA_REQUEST(DPWS11Message* dpws11Msg) {
    // Try to find the right service for the request
    int index = getRequestedServiceIndex(*dpws11Msg);
    if (index >= 0)
    {
        // Create metadata response
        dpws11Msg->createGetMetadataResponse(*device, index);
        //sendMessage(*dpws11Msg);
    }
    else
    {
        DebugOut(DebugOut::Error, "DPWS11CommunicationManager") << "Unable to find requested service.";
    }
}

void DPWS11CommunicationManager::handleAction_WS_ACTION_SUBSCRIBE(DPWS11Message* dpws11Msg) {
    // Try to find the right service for the request
    int index = getRequestedServiceIndex(*dpws11Msg);
    if (index >= 0)
    {
        // Handle subscription request, create subscribe response
        dpws11Msg->createSubscribeResponse(*device, index);
        //sendMessage(*dpws11Msg);
    }
    else
    {
        DebugOut(DebugOut::Error, "DPWS11CommunicationManager") << "Unable to find the right service.";
    }
}

void DPWS11CommunicationManager::handleAction_WS_ACTION_RENEW(DPWS11Message* dpws11Msg) {
    // Try to find the right service for the request
    int index = getRequestedServiceIndex(*dpws11Msg);
    if (index >= 0)
    {
        // Handle subscription request, create subscribe response
        dpws11Msg->createRenewResponse(*device, index);
        //sendMessage(*dpws11Msg);
    }
    else
    {
        DebugOut(DebugOut::Error, "DPWS11CommunicationManager") << "Unable to find the right service.";
    }
}

void DPWS11CommunicationManager::handleAction_WS_ACTION_UNSUBSCRIBE(DPWS11Message* dpws11Msg) {
    // Try to find the right service for the request
    int index = getRequestedServiceIndex(*dpws11Msg);
    if (index >= 0)
    {
        // Handle subscription request, create subscribe response
        dpws11Msg->createUnsubscribeResponse(*device, index);
        //sendMessage(*dpws11Msg);
    }
    else
    {
        DebugOut(DebugOut::Error, "DPWS11CommunicationManager") << "Unable to find the right service.";
    }
}

std::shared_ptr<Message> DPWS11CommunicationManager::unicastCallback(const Message & msg)
{
	Poco::Mutex::ScopedLock lock(mutexCallback);
	std::shared_ptr<DPWS11Message> dpws11Msg(new DPWS11Message());
    dpws11Msg->copyRaw(msg);

    if (!dpws11Msg->parseXML(dpws11Msg->getRawBuffer(), getKnownCustomActions()))
    {
        DebugOut(DebugOut::Info, "DPWS11CommunicationManager") << "XML parse error has been triggered in unicastCallback.";
        return nullptr;
    }

    const std::string httpUrl(dpws11Msg->getHttpUrl());
    const std::string httpRequestType(dpws11Msg->getHttpRequestType());
    if (httpRequestType.compare("GET") == 0 && httpUrl.length() > 0) {

        if (httpUrl.find("description.wsdl") != std::string::npos) {
            // WSDL GET request
            handleAction_HTTP_GET_WSDL(dpws11Msg.get(), httpUrl);
        }
        else {
            // request for some other file. Maybe a schema file?
        	handleAction_HTTP_GET_FILE(dpws11Msg.get(), httpUrl);
        }
        return dpws11Msg;
    }

    // Check for duplicate or own messages
    if (!validateMsgId(dpws11Msg->getIncomingId()))
    {
        DebugOut(DebugOut::Info, "DPWS11CommunicationManager") << "Message discarded (duplicate or own).";
        return nullptr;
    }
    if (dpws11Msg->getReceiveProtocol() == Message::UDP_UNICAST) {
        trackMsgId(dpws11Msg->getIncomingId());
    }

    const std::string action(dpws11Msg->getIncomingAction());
    const StringVector & customActions = getKnownCustomActions();

    // Analyze message action and generate a response
    if (action.compare(WS_ACTION_GET) == 0) {
        handleAction_WS_ACTION_GET(dpws11Msg.get());
        return dpws11Msg;
    }
    else if (action.compare(WS_ACTION_RESOLVE) == 0) {
        handleAction_WS_ACTION_RESOLVE(dpws11Msg.get());
        return dpws11Msg;
    }
    else if (action.compare(WS_ACTION_PROBE) == 0) {
        handleAction_WS_ACTION_PROBE(dpws11Msg.get());
        return dpws11Msg;
    }
    else if (action.compare(WS_ACTION_GET_METADATA_REQUEST) == 0) {
        handleAction_WS_ACTION_GET_METADATA_REQUEST(dpws11Msg.get());
        return dpws11Msg;
    }
    else if (action.compare(WS_ACTION_SUBSCRIBE) == 0) {
        handleAction_WS_ACTION_SUBSCRIBE(dpws11Msg.get());
        return dpws11Msg;
    }
    else if (action.compare(WS_ACTION_RENEW) == 0) {
        handleAction_WS_ACTION_RENEW(dpws11Msg.get());
        return dpws11Msg;
    }
    else if (action.compare(WS_ACTION_UNSUBSCRIBE) == 0) {
        handleAction_WS_ACTION_UNSUBSCRIBE(dpws11Msg.get());
        return dpws11Msg;
    }
    else if (find(customActions.begin(), customActions.end(), action) != customActions.end()) {
        int index = getRequestedServiceIndex(*dpws11Msg);
        if (index >= 0) {
            handleAction_invoke(dpws11Msg, index);
            return dpws11Msg;
        }
    }
    
    for (auto & it : actionHandlers) {
		if (action == it.first && it.second->isUnicast()) {
			it.second->handleAction(dpws11Msg.get());
            return dpws11Msg;
		}
	}
    
    return nullptr;
}

void DPWS11CommunicationManager::handleAction_HTTP_GET_FILE(DPWS11Message * dpws11Msg, const std::string & path) {
	int index = getRequestedServiceIndex(*dpws11Msg, path);
	if (index >= 0) {
		std::shared_ptr<Service> s(device->getService(index));
		const std::map<std::string, std::string> schemaFiles(s->getSchemaFiles());

		for (const auto & file : schemaFiles) {
			if (path.find(file.first) != std::string::npos) {
				dpws11Msg->setShortName("WSDL");
				dpws11Msg->setSkipGenerateRawBuffer(true);

                dpws11Msg->setRawBuffer(file.second);

				if (!dpws11Msg->configureUnicast()) {
					dpws11Msg->setRouting(dpws11Msg->UNKNOWN_ROUTING);
					dpws11Msg->setSendProtocol(dpws11Msg->UNKNOWN_PROTOCOL);
				}

				//sendMessage(*dpws11Msg);
				return;
			}
		}
	}
}

void DPWS11CommunicationManager::handleAction_HTTP_GET_WSDL(DPWS11Message * dpws11Msg, const std::string & path) {

    int index = getRequestedServiceIndex(*dpws11Msg, path);
    if (index >= 0)
    {
        bool nsFound = false;
        // Find requested namespace (porttype)
        std::shared_ptr<Service> s(device->getService(index));
        const std::string staticWSDL(s->getStaticWSDL());
        if (staticWSDL.length() > 0)
        {
            dpws11Msg->createStaticWSDL(staticWSDL);
            //sendMessage(*dpws11Msg);
            return;
        }
        const OperationVector & ov = s->getOperations();
        OperationVector::const_iterator oIt;
        for (oIt = ov.begin(); oIt != ov.end(); ++oIt)
        {
        	const std::string oNs((*oIt)->getPortType().getNamespace());
            if (path.find(oNs) != std::string::npos)
            {
                nsFound = true;
                // Create WSDL with the right target namespace
                dpws11Msg->createWSDL(*s, oNs);
                //sendMessage(*dpws11Msg);
                break;
            }
        }
        if (!nsFound)
        {
            DebugOut(DebugOut::Error, "DPWS11CommunicationManager") << "No matching porttype namespace found in WSDL.";
        }
    }
    else
    {
        DebugOut(DebugOut::Error, "DPWS11CommunicationManager") << "No service found in WSDL.";
    }
}

void DPWS11CommunicationManager::handleAction_WS_ACTION_GET(DPWS11Message* dpws11Msg) {
    dpws11Msg->createGetResponse(*device);
    //sendMessage(*dpws11Msg);
}

void DPWS11CommunicationManager::handleAction_WS_ACTION_RESOLVE(DPWS11Message* dpws11Msg) {
    if (device->getEndpointReference().getAddress() == dpws11Msg->getIncomingDeviceEPRAddress().getAddress())
    {
        dpws11Msg->createMatchResponse(*device);
		if (dpws11Msg->getSendProtocol() != Message::TCP_HTTP) {
            for (unsigned int i = 0; i < UDP_UNICAST_UDP_REPEAT; ++i) {
                sendMessage(*dpws11Msg);
                if (i > 0) {
                    Poco::Thread::sleep(i * 10);
                }
            }
        }
	}
}

void DPWS11CommunicationManager::handleAction_WS_ACTION_PROBE(DPWS11Message* dpws11Msg) {
    QVector types = dpws11Msg->getIncomingTypes();
    const std::string scopes(dpws11Msg->getIncomingScopes());
    bool match = true;
    if (types.size() != 0)
    {
        QVector::const_iterator tItlocal;
        const QVector & remoteTypes(types);
        const QVector & localTypes = device->getTypes();
        for (const auto & qnRemote : remoteTypes) {
            match = false;
            for (const auto & qnLocal : localTypes) {
                // TODO: Implement matching rules!
                if (qnLocal == qnRemote) {
                    match = true;
                }
            }
            // All have to match
            if (!match)
                break;
        }
        // Note: do not match service types, check these on client side!
    }
    if (scopes.compare("") != 0 && (match || types.size() == 0))
    {
        const StringVector & deviceScopes = device->getScopes();
        StringVector::const_iterator sIt;
        std::vector<std::string> clientScopes;
        // Convert string to vector
        std::istringstream iss(scopes);
        std::copy(std::istream_iterator<std::string>(iss),
        		std::istream_iterator<std::string>(),
				std::back_inserter<std::vector<std::string> >(clientScopes));
        for (unsigned int i = 0; i<clientScopes.size(); ++i)
        {
            match = false;
            for (sIt = deviceScopes.begin(); sIt != deviceScopes.end(); ++sIt)
            {
                // TODO: Implement matching rules!
                if (clientScopes[i].compare(*sIt) == 0)
                {
                    match = true;
                }
            }
            // All have to match
            if (!match)
                break;
        }
    }
    if (types.size() == 0 && scopes.compare("") == 0)
        match = true;
    if (match)
    {
        dpws11Msg->createMatchResponse(*device, true);
		if (dpws11Msg->getSendProtocol() != Message::TCP_HTTP) {
            for (unsigned int i = 0; i < UDP_UNICAST_UDP_REPEAT; ++i) {
                sendMessage(*dpws11Msg);
                if (i > 0) {
                    Poco::Thread::sleep(i * 10);
                }
            }
        }
    }
    else
        DebugOut(DebugOut::Info, std::cout, "DPWS11CommunicationManager") << "OK, no match for probe." << std::endl;
}


int DPWS11CommunicationManager::getRequestedServiceIndex(DPWS11Message& dpws11Msg, const std::string& getPath)
{
    // Try incoming "To" tag
    size_t sSize = device->getServiceCount();
    for (size_t i = 0; i < sSize; ++i) {
        auto & service = device->getService(i);
        const std::vector<std::shared_ptr<AbstractBinding>> serviceBindings = service->getProtocolBindings().find(DPWS11)->second;
        for (const auto & binding : serviceBindings)
        {
        	std::shared_ptr<Binding> httpBnd(std::dynamic_pointer_cast<Binding>(binding));
            if (httpBnd != nullptr)
            {
            	// Use dispatcher's IP and http binding's port as 'real' service address
            	Binding httpReal(*httpBnd);
            	std::shared_ptr<IPBinding> dispatcherBinding = dpws11Msg.getDispatcher();
                if (!dispatcherBinding)
                    continue;
            	httpReal.setSocketAddress(Poco::Net::SocketAddress(dispatcherBinding->getIp(), httpBnd->getPort()));
                const std::string to(dpws11Msg.getIncomingTo());
                if (httpReal.toString().compare(to) == 0)
                    return i;
                else if (getPath.length() > 0) {
                	if (httpBnd->getPort() == dispatcherBinding->getPort() && getPath.find(httpBnd->getPath()) != std::string::npos)
                		return i;
                }
            }
        }
    }
    // Try SOAP action
    if (dpws11Msg.getIncomingAction().compare("") != 0) {
        return getServiceIndexByActionString(dpws11Msg.getIncomingAction());
    }
    return -1;
}

int DPWS11CommunicationManager::getServiceIndexByActionString(std::string action) {

    size_t sSize = device->getServiceCount();
    for (size_t i = 0; i < sSize; ++i) {
        auto & service = device->getService(i);

        const OperationVector & ops = service->getOperations();
        OperationVector::const_iterator opIt;

        for (opIt = ops.begin(); opIt != ops.end(); ++opIt) {
            if (action.compare((*opIt)->getInputAction()) == 0) {
                return (int)i;
            }
        }
    }

    return -1;
}

void DPWS11CommunicationManager::registerListener(std::shared_ptr<AbstractBinding> b)
{
    if (b->getType() == AbstractBinding::UDP_MULTICAST)
    {
        std::shared_ptr<IPBinding> ipb = std::dynamic_pointer_cast<IPBinding>(b);
        OSCLibrary::getInstance()->getNetInterface()->addUDPMulticastListener(this, ipb->getIp(), ipb->getPort());
    }
    else if (b->getType() == AbstractBinding::TCP_HTTP)
    {
    	try {
    		Poco::Mutex::ScopedLock lock(mutexHttpServer);
    		std::shared_ptr<Binding> hpb = std::dynamic_pointer_cast<Binding>(b);
			const Poco::Net::IPAddress saAll(Poco::Net::IPAddress::Family::IPv4);
			Poco::Net::SocketAddress sa(saAll, hpb->getPort());
			if (hpb->getIp() != "0.0.0.0")
				sa = Poco::Net::SocketAddress(hpb->getIp(), hpb->getPort());
			Poco::Net::ServerSocket ss;
			ss.bind(sa);
			ss.listen();
			//ss.setReceiveBufferSize(1000000);
			//ss.setSendBufferSize(1000000);
			Poco::Net::HTTPServerParams * sp = new Poco::Net::HTTPServerParams;
			sp->setKeepAlive(true);
			//sp->setTimeout(Poco::Timespan(2L, 0L));
			//sp->setKeepAliveTimeout(Poco::Timespan(2L, 0L));
			std::shared_ptr<Poco::Net::HTTPServer> server = std::make_shared<Poco::Net::HTTPServer>(new DPWSHttpFactory(*this), *threadPool, ss, sp);
			server->start();
			httpServers[hpb->toString()] = server;
		}
		catch (Poco::Exception & e) {
			DebugOut(DebugOut::Error, "DPWS11CommunicationManager") << "Initializing HTTP server caused exception: " << e.message();
		}
		catch (...) {
			DebugOut(DebugOut::Error, "DPWS11CommunicationManager") << "Initializing HTTP server caused exception.";
		}
    }
    else if (b->getType() == AbstractBinding::UDP)
    {
    	std::shared_ptr<IPBinding> ipb = std::dynamic_pointer_cast<IPBinding>(b);
        OSCLibrary::getInstance()->getNetInterface()->addUDPListener(this, ipb->getIp(), ipb->getPort());
    }
}

void DPWS11CommunicationManager::unregisterListener(std::shared_ptr<AbstractBinding> b)
{
    if (b->getType() == AbstractBinding::UDP_MULTICAST)
    {
    	std::shared_ptr<IPBinding> ipb = std::dynamic_pointer_cast<IPBinding>(b);
        OSCLibrary::getInstance()->getNetInterface()->removeUDPMulticastListener(this, ipb->getIp(), ipb->getPort());
    }
    else if (b->getType() == AbstractBinding::TCP_HTTP)
    {
    	Poco::Mutex::ScopedLock lock(mutexHttpServer);
    	std::shared_ptr<Binding> hpb = std::dynamic_pointer_cast<Binding>(b);
    	if (httpServers.find(hpb->toString()) == httpServers.end()) {
    		throw std::runtime_error("No HTTP server found for given binding!");
    		return;
    	}
        httpServers[hpb->toString()]->stop();
        //httpServers.erase(hpb->toString());
    }
    else
    {
        std::shared_ptr<IPBinding> ipb = std::dynamic_pointer_cast<IPBinding>(b);
        OSCLibrary::getInstance()->getNetInterface()->removeListener(this, ipb->getIp(), ipb->getPort());
    }
}

void DPWS11CommunicationManager::injectBinding(std::shared_ptr<AbstractBinding> binding) {
    if (find(bindings.begin(), bindings.end(), binding) != bindings.end())
        return;
	bindings.push_back(binding);
	registerListener(binding);
}

void DPWS11CommunicationManager::withdrawBinding(std::shared_ptr<AbstractBinding> binding) {
    if (find(bindings.begin(), bindings.end(), binding) == bindings.end())
        return;
	bindings.erase(find(bindings.begin(), bindings.end(), binding));
	unregisterListener(binding);
}

void DPWS11CommunicationManager::injectService(std::shared_ptr<OSCLib::Dev::Service> s) {
    for (const auto &nextBinding : s->getProtocolBindings().find(DPWS11)->second) {
    	injectBinding(nextBinding);
    }

    for (const auto &nextOperation : s->getOperations()) {
        addKnownCustomAction(nextOperation->getInputAction());
        addKnownCustomAction(nextOperation->getOutputAction());
    }
}

void DPWS11CommunicationManager::withdrawService(std::shared_ptr<OSCLib::Dev::Service> s) {
    for (const auto &nextBinding : s->getProtocolBindings().find(DPWS11)->second) {
        withdrawBinding(nextBinding);
    }

    for (const auto &nextOperation : s->getOperations()) {
        removeKnownCustomAction(nextOperation->getInputAction());
        removeKnownCustomAction(nextOperation->getOutputAction());
    }
}

void DPWS11CommunicationManager::startManager()
{
	OSCLibrary::getInstance()->getNetInterface()->addValidUnicastCallback(this);
    OSCLibrary::getInstance()->getNetInterface()->addValidMulticastCallback(this);
    threadPool = std::make_shared<Poco::ThreadPool>(2, 100);
    cmHttpExchanger = std::make_shared<HTTPClientExchanger>();

    // Get device bindings (create copy)
    // DPWS
    bindings = device->getProtocolBindings().find(DPWS11)->second;
    // MDPWS (UDP multicast)
    //auto pbmIt = device->getProtocolBindings().find(MDPWS);
	//if (pbmIt != device->getProtocolBindings().end()) {
	//    for (const auto & next : pbmIt->second) {
	//		bindings.push_back(next);
	//	}
	//}

    // Get hosted services bindings and add to list of bindings
    {
        size_t sSize = device->getServiceCount();
        for (size_t i = 0; i < sSize; ++i) {
            auto & service = device->getService(i);
            if (service->isRunning())
            {
                for (const auto &nextBinding : service->getProtocolBindings().find(DPWS11)->second)
                {
                    bindings.push_back(nextBinding);
                }
            }

            for (const auto &nextOperation : service->getOperations()) {
                addKnownCustomAction(nextOperation->getInputAction());
                addKnownCustomAction(nextOperation->getOutputAction());
            }

        }
    }
    // Add network listeners for devices and services
    for (auto &nextBinding : bindings)
    {
        registerListener(nextBinding);
    }

    if (device->isRunning())
    {
        // Send hello
        DPWS11Message msg;
        msg.createHelloMessage(*device);
        sendMessage(msg);
    }

    DebugOut(DebugOut::Info, "DPWS11CommunicationManager") << "DPWS11 CommunicationManager started.";
}

void DPWS11CommunicationManager::stopManager()
{
    OSCLibrary::getInstance()->getNetInterface()->removeValidUnicastCallback(this);
    OSCLibrary::getInstance()->getNetInterface()->removeValidMulticastCallback(this);

    if (device->isRunning()) {
        // Send bye
		DPWS11Message msg;
        msg.createByeMessage(*device);
		sendMessage(msg);
    }

    // Remove network listeners
    for (const auto &next : bindings)
    {
        unregisterListener(next);
    }
    Poco::Mutex::ScopedLock lock(mutexTrackedMsgIds);
    trackedMsgIds.clear();
    bindings.clear();

    DebugOut(DebugOut::Info, "DPWS11CommunicationManager") << "DPWS11 CommunicationManager stopped.";
}

bool DPWS11CommunicationManager::validateMsgId(const std::string & id) {
    bool valid;
    if (id.compare("") == 0) {
        valid = true;
    }
    else {
        Poco::Mutex::ScopedLock lock(mutexTrackedMsgIds);
        valid = (id.compare("") != 0 && find(trackedMsgIds.begin(), trackedMsgIds.end(), id) == trackedMsgIds.end());
    }

    if (!valid) {
        DebugOut(DebugOut::Info, "DPWS11CommunicationManager") << "Invalid id: " << id;
    }
    return valid;
}

void DPWS11CommunicationManager::trackMsgId(const std::string & id) {
    if (id.compare("") == 0) {
        return;
    }
    Poco::Mutex::ScopedLock lock(mutexTrackedMsgIds);
    trackedMsgIds.push_back(std::string(id));
    while (trackedMsgIds.size() > 100) {
        trackedMsgIds.pop_front();
    }
}

std::string DPWS11CommunicationManager::getProtocolDomain() const {
    return DPWS11;
}

void DPWS11CommunicationManager::addDPWSActionHandler(const std::string & action, std::shared_ptr<DPWS11ActionHandler> handler) {
    actionHandlers[action] = handler;
}

std::shared_ptr<DPWS11ActionHandler> DPWS11CommunicationManager::getDPWSActionHandler(const std::string & action) {
    return actionHandlers[action];
}

void DPWS11CommunicationManager::addKnownCustomAction(const std::string & action) {
    Poco::Mutex::ScopedLock lock(mutexCustomActions);
    knownCustomActions.insert(action);
}

StringVector DPWS11CommunicationManager::getKnownCustomActions() const {
    Poco::Mutex::ScopedLock lock(mutexCustomActions);
	StringVector sv;
	for (auto &nextAction : knownCustomActions)
		sv.push_back(nextAction);
    return sv;
}

} /* namespace DPWS */
} /* namespace Comm */
} /* namespace OSCLib */
