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
 *  @file DPWS11Message.cpp
 *  @project OSCLib
 *  @date 24.08.2011
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 */

#include "OSCLib/Comm/DPWS/DPWS11Constants.h"
#include "OSCLib/Comm/DPWS/DPWS11Message.h"
#include "OSCLib/Comm/DPWS/DPWS11MessageXMLBuilder.h"
#include "OSCLib/Comm/DPWS/DPWS11WSDLBuilder.h"
#include "OSCLib/Comm/DPWS/DPWS11MetadataSoapParserHandler.h"
#include "OSCLib/Comm/Binding.h"
#include "OSCLib/Comm/Soap/SoapBody.h"
#include "OSCLib/Comm/Soap/SoapEnvelope.h"
#include "OSCLib/Comm/Soap/SoapHeader.h"
#include "OSCLib/Data/Operation.h"
#include "OSCLib/Data/QName.h"
#include "OSCLib/Data/Subscription.h"
#include "OSCLib/Data/SubscriptionVector.h"
#include "OSCLib/Data/OSCP/OSCPConstants.h"
#include "OSCLib/Dev/Device.h"
#include "OSCLib/Dev/Service.h"
#include "OSCLib/Util/DebugOut.h"
#include "OSCLib/Util/DefaultUUIDGenerator.h"
#include <algorithm>
#include <map>
#include <stdexcept>

using namespace OSCLib::Comm::Soap;
using namespace OSCLib::Dev;
using namespace OSCLib::Data;
using namespace OSCLib::Data::OSCP;
using namespace rapidxml;
using namespace OSCLib::Util;

namespace OSCLib {
namespace Comm {
namespace DPWS {

std::string createExpirationString(long duration) {
	std::ostringstream s;
	s << "PT";
	s << (duration / 1000);
	s << "S";
	return s.str();
}

DPWS11Message::DPWS11Message() :
		incRenewResponseSucceeded(false),
		incMetadataVersion(0),
		incSubscription(nullptr),
		shortName("Unknown"),
		skipGenerateRawBuffer(false),
		request(false),
		envelope(nullptr),
		rawXML(nullptr),
        cdmBuf(1)
{
    std::shared_ptr<DPWS11MetadataSoapParserHandler> mdsph(new DPWS11MetadataSoapParserHandler);
    xmlparser.registerParseHandler(WS_ACTION_GET_RESPONSE, mdsph);
    xmlparser.registerParseHandler(WS_ACTION_GET_METADATA_RESPONSE, mdsph);
}

DPWS11Message::~DPWS11Message()
{

}

std::string DPWS11Message::getMsgXml(int flags)
{
	std::string xmlStr;
	if (envelope != nullptr)
        xmlStr = "<?xml version=\"1.0\"?>" + envelope->toString(flags);
	else if (rawXML != nullptr)
		xmlStr = rawXML->toString(flags);
	return xmlStr;
}

bool DPWS11Message::isRequest() const
{
	return request;
}

void DPWS11Message::setRequest(bool request)
{
	this->request = request;
}

void DPWS11Message::generateRawBuffer(DPWS11Message & msg)
{
	if (msg.isSkipGenerateRawBuffer())
		return;

    msg.setRawBuffer(msg.getMsgXml(1));
}


void DPWS11Message::addReplyTo(const std::string & replyTo) {
	this->getEnvelope()->getHeader()->addReplyTo(replyTo);
}

void DPWS11Message::createHelloMessage(const Dev::Device & device)
{
	initMessage("Hello");

	// Add discovery namespace
	getEnvelope()->addNamespace("wsd", WS_NS_DISCOVERY);

	// Header
	SoapHeader* h = getEnvelope()->getHeader();
	h->addTo(WS_DISCOVERY_URN);
	h->addAction(WS_ACTION_HELLO);
	h->addAppSequence(device);

	// Body
	// Hello
	XMLEntity* helloEntity = getEnvelope()->getBody()->appendChild("wsd:Hello");

	DPWS11MessageXMLBuilder::addBasicDiscoveryInfo(helloEntity, device);

	configureMulticast();
}

void DPWS11Message::createByeMessage(const Dev::Device & device)
{
	initMessage("Bye");

	// Add discovery namespace
	getEnvelope()->addNamespace("wsd", WS_NS_DISCOVERY);

	// Header
	SoapHeader* h = getEnvelope()->getHeader();
	h->addTo(WS_DISCOVERY_URN);
	h->addAction(WS_ACTION_BYE);
	h->addAppSequence(device);

	// Body
	// Bye
	XMLEntity* byeEntity = getEnvelope()->getBody()->appendChild("wsd:Bye");

	// Endpoint reference
	DPWS11MessageXMLBuilder::appendEndpointReferenceTo(byeEntity, device.getEndpointReference());

	// Add metadata version
	byeEntity->addTextNode("wsd:MetadataVersion", std::to_string(device.getMetaDataVersion()));

	configureMulticast();
}

void DPWS11Message::initMessage(const std::string & shortName)
{
	envelope = std::shared_ptr<SoapEnvelope>(new SoapEnvelope());
	// Add addressing namespace
	getEnvelope()->addNamespace("wsa", WS_NS_ADDRESSING);
	setId(getEnvelope()->getHeader()->addMessageID());
	setShortName(shortName);
}

void DPWS11Message::createGetMessage(const Dev::Device & device)
{
	initMessage("Get");
	// Add dpws namespace
	getEnvelope()->addNamespace("dpws", WS_NS_DPWS);

	// Header
	SoapHeader* h = getEnvelope()->getHeader();
	h->addAction(WS_ACTION_GET);
	h->addTo(device.getEndpointReference().getAddress());

	// Send explicitly to device address!
	std::shared_ptr<Binding> deviceAdr(new Binding(device.getDefaultTransportAddr(DPWS11)));
	setRequest(true);
	configureUnicast(deviceAdr);
}

void DPWS11Message::createGetMetadataMessage(const Dev::Device & device, unsigned int serviceIndex)
{
	initMessage("GetMetadata");
	// Add dpws namespace
	getEnvelope()->addNamespace("dpws", WS_NS_DPWS);
	// Add metadata exchange namespace
	getEnvelope()->addNamespace("wsx", WS_NS_METADATA_EXCHANGE);
	if (serviceIndex >= device.getServiceCount())
		throw std::runtime_error("Valid service index needed!");
	std::shared_ptr<Service> service(device.getService(serviceIndex));

	// Header
	SoapHeader* h = getEnvelope()->getHeader();
	h->addAction(WS_ACTION_GET_METADATA_REQUEST);
	h->addTo(service->getEndpointReference().getAddress());
	getEnvelope()->getBody()->addTextNode("wsx:GetMetadata", "");

	// Send explicitly to service address!
	std::shared_ptr<Binding> serviceAdr(new Binding(service->getEndpointReference().getAddress()));
	setRequest(true);
	configureUnicast(serviceAdr);
}

void DPWS11Message::createGetResponse(const Dev::Device & device, int wsdlIndex)
{
	initMessage("GetResponse");

	// Header
	SoapHeader* h = getEnvelope()->getHeader();

	// Add metadata exchange namespace
	getEnvelope()->addNamespace("wsx", WS_NS_METADATA_EXCHANGE);
	// Add dpws namespace
	getEnvelope()->addNamespace("dpws", WS_NS_DPWS);

	h->addTo(getIncomingReplyToAddr().compare("") != 0 ? getIncomingReplyToAddr() : "");  // If omitted (equals 0), anonymous tag is used
	if (!configureUnicast()) {
		setRouting(UNKNOWN_ROUTING);
		setSendProtocol(UNKNOWN_PROTOCOL);
	}

	if (getIncomingId().compare("") != 0)
		h->addRelatesTo(getIncomingId());
	h->addAction(WS_ACTION_GET_RESPONSE);

	// Add body with metadata info
	XMLEntity* metaDataNode = getEnvelope()->getBody()->appendChild("wsx:Metadata");

	// Model
	DPWS11MessageXMLBuilder::addMetadataModel(metaDataNode, device);
	// Device
	DPWS11MessageXMLBuilder::addMetadataDevice(metaDataNode, device);

	// Relationship
	DPWS11MessageXMLBuilder::addMetadataRelationship(*this, metaDataNode, device, wsdlIndex);
}

void DPWS11Message::createGetMetadataResponse(const Dev::Device & device, int wsdlIndex)
{
	initMessage("GetMetadataResponse");

	// Header
	SoapHeader* h = getEnvelope()->getHeader();

	// Add metadata exchange namespace
	getEnvelope()->addNamespace("wsx", WS_NS_METADATA_EXCHANGE);
	// Add dpws namespace
	getEnvelope()->addNamespace("dpws", WS_NS_DPWS);
	getEnvelope()->addNamespace("wsdl", WS_NS_WSDL_SOAP);

	h->addTo(getIncomingReplyToAddr().compare("") != 0 ? getIncomingReplyToAddr() : "");  // If omitted (equals 0), anonymous tag is used
	if (!configureUnicast()) {
		setRouting(UNKNOWN_ROUTING);
		setSendProtocol(UNKNOWN_PROTOCOL);
	}

	if (getIncomingId().compare("") != 0)
		h->addRelatesTo(getIncomingId());
	h->addAction(WS_ACTION_GET_METADATA_RESPONSE);

	// Add body with metadata info
	XMLEntity* metaDataNode = getEnvelope()->getBody()->appendChild("wsx:Metadata");

	// WSDL link
	if (wsdlIndex >= 0 && device.getServiceCount() > 0)
	{
		DPWS11WSDLBuilder wsdlbuilder;
        wsdlbuilder.addWSDLLink(*this, metaDataNode, *device.getService(wsdlIndex));
	}
    else if (wsdlIndex <= int(device.getServiceCount()))
	{
		DebugOut(DebugOut::Error, "DPWS11Message") << "No services found for WSDL metadata!";
	}

	// Relationship
	DPWS11MessageXMLBuilder::addMetadataRelationship(*this, metaDataNode, device, wsdlIndex);
	// MDPWS streaming
	DPWS11MessageXMLBuilder::addMetadataStreaming(metaDataNode, device, wsdlIndex);
}

void DPWS11Message::createProbeMessage(const Dev::Device & device, const std::string & xaddr)
{
    initMessage(xaddr.length() > 0? "DirectedProbe" : "Probe");

	// Add required namespaces
	getEnvelope()->addNamespace("wsd", WS_NS_DISCOVERY);

	// Header
	SoapHeader * h = getEnvelope()->getHeader();
	h->addTo(WS_DISCOVERY_URN);
	h->addAction(WS_ACTION_PROBE);
	h->addAppSequence(device);

	// Body
	SoapBody* b = getEnvelope()->getBody();

	// Probe
	XMLEntity* probeEntity = b->appendChild("wsd:Probe");

	// Types
	DPWS11MessageXMLBuilder::addTypesAttributes(getEnvelope().get(), device);
	DPWS11MessageXMLBuilder::addTypesNode(probeEntity, "wsd:Types", device);

	// Scopes
	DPWS11MessageXMLBuilder::addScopes(probeEntity, device);

	setRequest(true);
    if (xaddr.length() == 0)
	{
		configureMulticast();
	}
	else
	{
		std::shared_ptr<Binding> deviceAdr(new Binding(xaddr));
		configureUnicast(deviceAdr);
	}
}

void DPWS11Message::createResolveMessage(const Dev::Device & device)
{
	initMessage("Resolve");

	// Add required namespaces
	getEnvelope()->addNamespace("wsd", WS_NS_DISCOVERY);

	// Header
	SoapHeader * h = getEnvelope()->getHeader();
	h->addTo(WS_DISCOVERY_URN);
	h->addAction(WS_ACTION_RESOLVE);
	h->addAppSequence(device);

	// Body
	// Resolve
	XMLEntity * resolveEntity = getEnvelope()->getBody()->appendChild("wsd:Resolve");

	// Endpoint reference
	DPWS11MessageXMLBuilder::appendEndpointReferenceTo(resolveEntity, device.getEndpointReference());

	setRequest(true);
	configureMulticast();
}

void DPWS11Message::createMatchResponse(const Dev::Device & device, bool probe)
{
	const std::string matchType(probe? "Probe" : "Resolve");
	initMessage(matchType + "Matches");

	// Header
	SoapHeader * h = getEnvelope()->getHeader();

	// Add discovery namespace
	getEnvelope()->addNamespace("wsd", WS_NS_DISCOVERY);
	// Add dpws namespace
	getEnvelope()->addNamespace("dpws", WS_NS_DPWS);

	h->addTo(WS_DISCOVERY_URN);
	if (!configureUnicast())
	{
		setRouting(UNKNOWN_ROUTING);
		setSendProtocol(UNKNOWN_PROTOCOL);
	}

	h->addRelatesTo(getIncomingId());
	if (probe)
		h->addAction(WS_ACTION_PROBE_MATCHES);
	else
		h->addAction(WS_ACTION_RESOLVE_MATCHES);
	h->addAppSequence(device);

	// Add body with metadata info
	XMLEntity* matches = getEnvelope()->getBody()->appendChild("wsd:" + matchType + "Matches");
	XMLEntity* match = matches->appendChild("wsd:" + matchType + "Match");

	// Add relevant information
	DPWS11MessageXMLBuilder::addBasicDiscoveryInfo(match, device);
}

void DPWS11Message::createStaticWSDL(const std::string & wsdl)
{
    setShortName("WSDL");
    setSkipGenerateRawBuffer(true);
    setRawBuffer(wsdl);

    if (!configureUnicast())
    {
        setRouting(UNKNOWN_ROUTING);
        setSendProtocol(UNKNOWN_PROTOCOL);
    }
}

void DPWS11Message::createWSDL(const Service & service, std::string targetNamespace)
{
	if(service.getOperations().size() == 0) {
		DebugOut(DebugOut::Error, "DPWS11Message") << "No operations in service!";
		return;
	}

	setShortName("WSDL");

	// Init new raw XML document
	rawXML.reset(new XMLEntity());

	DPWS11WSDLBuilder wsdlbuilder;
	wsdlbuilder.createWSDL(*this, service, rawXML.get(), targetNamespace);

	if (!configureUnicast())
	{
		setRouting(UNKNOWN_ROUTING);
		setSendProtocol(UNKNOWN_PROTOCOL);
	}
}

bool DPWS11Message::attachCDMStringToSoapBody(const std::string & xmlStr, Soap::SoapBody * b) {
	cdmBuf.resize(xmlStr.size() + 1);
	xmlStr.copy(cdmBuf.begin(), xmlStr.size(), 0);
	cdmBuf[xmlStr.size()] = '\0';

	cdmDoc.parse<0>(cdmBuf.begin());
	if (cdmDoc.first_node() != nullptr) {
		rapidxml::xml_node<char> * cloned = b->getDoc()->clone_node(cdmDoc.first_node());
		b->getNode()->append_node(cloned);
		return true;
	} else {
		return false;
	}
}

void DPWS11Message::createInvokeMessage(const Dev::Device & remoteDevice, unsigned int serviceIndex, const std::string& action, Data::Parameters& inputParams) {
	initMessage("Invoke");

	// Add dpws namespace
	getEnvelope()->addNamespace("dpws", WS_NS_DPWS);
    if (serviceIndex >= remoteDevice.getServiceCount())
		throw std::runtime_error("Valid service index needed!");
	std::shared_ptr<Service> remoteService = remoteDevice.getService(serviceIndex);
	std::shared_ptr<Operation> op = remoteService->getOperation(action);
	if (op == nullptr)
	{
		DebugOut(DebugOut::Error, "DPWS11Message") << "Operation not found by given name and porttype!";
		return;
	}

	// Header
	SoapHeader * h = getEnvelope()->getHeader();
	// Create special invoke action
	h->addAction(action);
	h->addTo(remoteService->getEndpointReference().getAddress());

	// Body
	SoapBody* b = getEnvelope()->getBody();

    // Add input (CDM case)
    if (inputParams.size() == 1 && inputParams[0].getType() == Parameter::Type::CDM)
    {
        try {
        	if (!attachCDMStringToSoapBody(inputParams[0].getValue(), getEnvelope()->getBody())) {
        		DebugOut(DebugOut::Error, "DPWS11Message") << "Invoke: Error parsing CDM structure.";
        	}
        } catch (...) {
            DebugOut(DebugOut::Error, "DPWS11Message") << "Invoke: Error parsing CDM structure.";
        }
    }
    else
    {
        XMLEntity* parent = b;
        QName qn = op->getPortType();
        parent->addNamespace(qn.getPrefix(), qn.getNamespace());
        if (inputParams.size() > 1)
        {
            // Additional node encapsulates parameters
            XMLEntity* inNode = b->appendChild(qn.getPrefix() + ":" + op->getName());
            parent = inNode;
        }
        parent->addNamespace("xsi", WS_NS_WSDL_XML_SCHEMA_INSTANCE)->addNamespace("xs", WS_NS_WSDL_XML_SCHEMA);

        for (const auto & next : inputParams) {
            next.addToNode(parent, qn);
        }
    }

	// Send explicitly to service address!
    auto serviceAdr = std::make_shared<Binding>(remoteService->getEndpointReference().getAddress());
	setRequest(true);
	configureUnicast(serviceAdr);
}

bool DPWS11Message::createInvokeResponse(const Dev::Device & device, unsigned int serviceIndex)
{
	auto genErrorNoResponse = [this]() {
		setRouting(UNKNOWN_ROUTING);
		setSendProtocol(UNKNOWN_PROTOCOL);
		DebugOut(DebugOut::Error, "DPWS11Message") << "Invoke: Routing or protocol error.";
		return false;
	};
	auto genCDMResponse = [this, &genErrorNoResponse](Parameters & output, SoapBody * b) {
		try {
			if (!attachCDMStringToSoapBody(output[0].getValue(), b)) {
				DebugOut(DebugOut::Error, "DPWS11Message") << "InvokeResponse: Error parsing CDM structure.";
				return genErrorNoResponse();
			}
		} catch (...) {
			DebugOut(DebugOut::Error, "DPWS11Message") << "InvokeResponse: Error parsing CDM structure.";
			return genErrorNoResponse();
		}
		if (!configureUnicast())
			return genErrorNoResponse();
		DebugOut(DebugOut::Info, "DPWS11Message") << "Invoke: Successful.";
		return true;
	};
	auto genErrorResponse = [this, &genErrorNoResponse, &genCDMResponse](Parameters & output, SoapBody * b) {
		DebugOut(DebugOut::Error, "DPWS11Message") << "Invoke: Error in handling invoke, sending fault.";
		// Create fake error when there is an invalid request.
		// This should be a soap fault.
		output.clear();
		output.emplace_back("CDMResponse", OSCLib::Data::Parameter::Type::CDM, "<Error />");
		if (!configureUnicast())
		{
			return genErrorNoResponse();
		}
		return genCDMResponse(output, b);
	};
	std::shared_ptr<Service> s = device.getService(serviceIndex);
	const OperationVector ov(s->getOperations());
	for (const auto & op : ov) {
		if (op->getInputAction() != getIncomingAction()) {
			continue;
		}
		Parameters input;

		const Parameters & parametersInMessage = this->parameters;
		if (parametersInMessage.size() > 0) {
			// First node is either operation name dummy node or parameter node
			if (op->getInput().size() > 1) {
				// Operation node in case of multiple first level parameters
				input = parametersInMessage.front().getCopyChildren();
			} else {
				input = parametersInMessage;
			}
		}

		// Add additional raw content parameter (CDM case)
		input.emplace_back("BodyRawContent", Parameter::Type::CDM, bodyRawContent);

		// Invoke, get output params
		Parameters output(op->invoke(input));

		if (output.empty()) {
			// In case of no return values, send HTTP accepted response
			setRawBuffer("");
			if (configureUnicast()) {
				setSkipGenerateRawBuffer(true);
				setShortName("ACCEPTED");
				return true;
			}
			return genErrorNoResponse();
		}

		const std::string & opName(op->getName());
		initMessage(opName + "Response");
		SoapHeader* h = getEnvelope()->getHeader();
		h->addAction(op->getOutputAction());
		h->addRelatesTo(getIncomingId());
		// Add dpws namespace
		getEnvelope()->addNamespace("dpws", WS_NS_DPWS);
		SoapBody * b = getEnvelope()->getBody();

		// Check for error case
		if (output.size() == 1 && output[0].getType() == Parameter::Type::ERR)
		{
			return genErrorResponse(output, b);
		}

		// Add output (CDM case)
		if (output.size() == 1 && output[0].getType() == Parameter::Type::CDM)
		{
			return genCDMResponse(output, b);
		}
		else
		{
			// Add output params
			XMLEntity* outParent = b;
			const QName & qn(op->getPortType());
			outParent->addNamespace(qn.getPrefix(), qn.getNamespace());
			if (output.size() > 1)
			{
				// Additional out response node encapsulates parameters
				XMLEntity* outNode = b->appendChild(qn.getPrefix() + ":" + opName + "Out");
				outParent = outNode;
			}

			outParent->addNamespace("xsi", WS_NS_WSDL_XML_SCHEMA_INSTANCE)->addNamespace("xs", WS_NS_WSDL_XML_SCHEMA);
			for (const auto & next : output) {
				next.addToNode(outParent, qn);
			}
		}
		if (!configureUnicast())
			return genErrorNoResponse();
		DebugOut(DebugOut::Info, "DPWS11Message") << "Invoke: Successful.";
		return true;
	}
	DebugOut(DebugOut::Error, "DPWS11Message") << "Invoke: No matching operation found.";
	return false;
}

void DPWS11Message::createEventMessage(const Data::Subscription & subscription, const Data::Parameters & params, const std::string & eventName, const Data::QName & portType)
{
	initMessage("FireEvent");
	// Add dpws namespace
	getEnvelope()->addNamespace("dpws", WS_NS_DPWS);

	// Header
	SoapHeader* h = getEnvelope()->getHeader();
	// Create special invoke action
	h->addAction(subscription.getFilterAction());
	const EndpointReference & notifyTo(subscription.getNotifyTo());
	h->addTo(notifyTo.getAddress());

	if (notifyTo.getReferenceParameters().length() > 0) {
		XMLEntity* idNode = h->appendChild("wse:Identifier");
		idNode->addAttribute("wsa:IsReferenceParameter", "true");
		idNode->addNamespace("wse", WS_NS_EVENTING);
		idNode->setValue(notifyTo.getReferenceParameters());
	}

	// Body
	SoapBody* b = getEnvelope()->getBody();

    // Add input (CDM case)
    if (params.size() == 1 && params[0].getType() == Parameter::Type::CDM)
    {
        try {
        	if (!attachCDMStringToSoapBody(params[0].getValue(), b)) {
        		DebugOut(DebugOut::Error, "DPWS11Message") << "Event: Error parsing CDM structure.";
			}
        } catch (...) {
            DebugOut(DebugOut::Error, "DPWS11Message") << "Event: Error parsing CDM structure.";
            return;
        }
    }
    else
    {
        XMLEntity* parent = b;
        parent->addNamespace(portType.getPrefix(), portType.getNamespace());
        if (params.size() > 1)
        {
            // Additional node encapsulates parameters
            XMLEntity* inNode = b->appendChild(portType.getPrefix() + ":" + eventName);
            parent = inNode;
        }
        parent->addNamespace("xsi", WS_NS_WSDL_XML_SCHEMA_INSTANCE)->addNamespace("xs", WS_NS_WSDL_XML_SCHEMA);

        for (const auto & next : params) {
            next.addToNode(parent, portType);
        }
    }

	// Send explicitly to event sink address
    auto notifyToAddr = std::make_shared<Binding>(notifyTo.getAddress());
	setRequest(true);
	configureUnicast(notifyToAddr);
}

void DPWS11Message::createStreamMessage(const Data::Parameters & params, const std::string from, const std::string mcastTo, const Dev::Device & device) {
    initMessage("FireStream");
    // Add dpws namespace
    getEnvelope()->addNamespace("dpws", WS_NS_DPWS);
    getEnvelope()->addNamespace("wsd", WS_NS_DISCOVERY);

    // Header
    SoapHeader* h = getEnvelope()->getHeader();
    h->addAction(ACTION_ORNET_STREAM);
    h->addTo(mcastTo);
    //h->addFrom(from);
    h->addAppSequence(device);

    // Body
    SoapBody* b = getEnvelope()->getBody();

    // Add input (CDM case)
    if (params.size() == 1 && params[0].getType() == Parameter::Type::CDM)
    {
        try {
            if (!attachCDMStringToSoapBody(params[0].getValue(), b)) {
                DebugOut(DebugOut::Error, "DPWS11Message") << "Event: Error parsing CDM structure.";
            }
        }
        catch (...) {
            DebugOut(DebugOut::Error, "DPWS11Message") << "Event: Error parsing CDM structure.";
            return;
        }
    }

    std::shared_ptr<Binding> toBnd = std::make_shared<Binding>(mcastTo);
    setDestination(toBnd);
    setSendProtocol(UDP_MULTICAST);
    setRouting(MULTICAST);
    setRequest(true);
}

void DPWS11Message::createSubscribeMessage(const std::string & action, long duration, const Device & localDevice, unsigned int localIndex, const Device & remoteDevice, unsigned int remoteIndex)
{
	initMessage("Subscribe");
	// Add eventing namespace
	getEnvelope()->addNamespace("wse", WS_NS_EVENTING);

	if (localIndex >= localDevice.getServiceCount())
		throw std::runtime_error("Valid local service index needed!");
    if (remoteIndex >= remoteDevice.getServiceCount())
		throw std::runtime_error("Valid remote service index needed!");
	std::shared_ptr<Service> sinkService = localDevice.getService(localIndex);
	std::shared_ptr<Service> sourceService = remoteDevice.getService(remoteIndex);
	std::shared_ptr<Operation> sourceOp = sourceService->getOperation(action);
	if (sourceOp == nullptr)
	{
		DebugOut(DebugOut::Error, "DPWS11Message") << "Remote event source operation not found using source name and port type!";
		return;
	}

	// Header
	SoapHeader* h = getEnvelope()->getHeader();
	h->addAction(WS_ACTION_SUBSCRIBE);
	h->addTo(sourceService->getEndpointReference().getAddress());

	// Body
	SoapBody* b = getEnvelope()->getBody();

	XMLEntity* subscribe = b->appendChild("wse:Subscribe");
	XMLEntity* delivery = subscribe->appendChild("wse:Delivery");
	delivery->addAttribute("Mode", WS_EVENTING_PUSH);
	XMLEntity* notifyTo = delivery->appendChild("wse:NotifyTo");
	notifyTo->addTextNode("wsa:Address", sinkService->getEndpointReference().getAddress());
	notifyTo->appendChild("wsa:ReferenceParameters")
		->addTextNode("wse:Identifier", sinkService->getEndpointReference().getReferenceParameters());
	if (duration != 0) {
		subscribe->addTextNode("wse:Expires", createExpirationString(duration));
	}
	XMLEntity* filter = subscribe->appendChild("wse:Filter");
	filter->addAttribute("Dialect", WS_ACTION);
	filter->setValue(sourceOp->getOutputAction());

	// Send explicitly to event source address
	auto sourceAddr = std::make_shared<Binding>(sourceService->getEndpointReference().getAddress());
	setRequest(true);
	configureUnicast(sourceAddr);
}

void DPWS11Message::createSubscribeResponse(const Dev::Device & device, unsigned int serviceIndex)
{
	initMessage("SubscribeResponse");
	// Add eventing namespace
	getEnvelope()->addNamespace("wse", WS_NS_EVENTING);

	if (serviceIndex >= device.getServiceCount())
		throw std::runtime_error("Valid service index needed!");
	std::shared_ptr<Service> eventingService = device.getService(serviceIndex);

	// Header
	SoapHeader* h = getEnvelope()->getHeader();
	h->addAction(WS_ACTION_SUBSCRIBE_RESPONSE);
	h->addRelatesTo(getIncomingId());

	std::shared_ptr<Subscription> incSub = getIncomingSubscription();
    //// Set 'real' notify-to address using source IP
    //EndpointReference notTo = incSub->getNotifyTo();
    //std::string notToAddr = notTo.getAddress();
    //Binding notToBnd(notToAddr);
    //notToBnd.setSocketAddress(Poco::Net::SocketAddress(getSource()->getIp(), notToBnd.getPort()));
    //notTo.setAddress(notToBnd.toString());
    //incSub->setNotifyTo(notTo);

	// Add subscription to eventing service
	eventingService->addSubscription(incSub);
	// Mark current time to check whether subscription is expired later
	incSub->setTimeStamp();

	const EndpointReference & endTo = incSub->getEndTo();
	if (endTo.getAddress().length() > 0)
		h->addTo(endTo.getAddress());

	// Body
	SoapBody* b = getEnvelope()->getBody();

	XMLEntity* subscribeResponse = b->appendChild("wse:SubscribeResponse");

	// Add subscription manager address
	XMLEntity* subscriptionManager = subscribeResponse->appendChild("wse:SubscriptionManager");
	XMLEntity* subscriptionAddress = subscriptionManager->appendChild("wsa:Address");
	subscriptionAddress->setValue(eventingService->getDefaultTransportAddr(DPWS11, getDispatcher()));
	if (incSub->getNotifyTo().getReferenceParameters().length() > 0)
	{
		// Use reference parameters sent by the client
		XMLEntity* refParams = subscriptionManager->appendChild("wsa:ReferenceParameters");
		XMLEntity* identifier = refParams->appendChild("wse:Identifier");
		identifier->setValue(incSub->getNotifyTo().getReferenceParameters());
	}
	else
	{
		// Create new reference parameters
		const std::string sourceIdentifier = Util::DefaultUUIDGenerator::getUUID();
		XMLEntity* refParams = subscriptionManager->appendChild("wsa:ReferenceParameters");
		XMLEntity* identifier = refParams->appendChild("wse:Identifier");
		identifier->setValue(sourceIdentifier);
	}

	if (incSub->getExpires().length() > 0)
	{
		XMLEntity* expires = subscribeResponse->appendChild("wse:Expires");
		expires->setValue(incSub->getExpires());
	}

	if (!configureUnicast())
	{
		setRouting(UNKNOWN_ROUTING);
		setSendProtocol(UNKNOWN_PROTOCOL);
	}
}

void DPWS11Message::createRenewMessage(const Dev::Service & localSinkService, const Dev::Service & remoteSourceService, long duration)
{
	initMessage("Renew");
	// Add eventing namespace
	getEnvelope()->addNamespace("wse", WS_NS_EVENTING);
	// Header
	SoapHeader* h = getEnvelope()->getHeader();
	h->addAction(WS_ACTION_RENEW);
	h->addTo(remoteSourceService.getEndpointReference().getAddress());
	h->addTextNode("wse:Identifier", localSinkService.getEndpointReference().getReferenceParameters());
	// Body
	getEnvelope()->getBody()
		->appendChild("wse:Renew")
		->addTextNode("wse:Expires", createExpirationString(duration));

	// Send explicitly to event source address
	auto sourceAddr = std::make_shared<Binding>(remoteSourceService.getEndpointReference().getAddress());
	setRequest(true);
	configureUnicast(sourceAddr);
}

void DPWS11Message::createRenewResponse(const Dev::Device & device, unsigned int serviceIndex)
{
	initMessage("RenewResponse");
	// Add eventing namespace
	getEnvelope()->addNamespace("wse", WS_NS_EVENTING);

	if (serviceIndex >= device.getServiceCount())
		throw std::runtime_error("Valid service index needed!");
	std::shared_ptr<Service> eventingService = device.getService(serviceIndex);

	// Header
	SoapHeader* h = getEnvelope()->getHeader();
	h->addAction(WS_ACTION_RENEW_RESPONSE);
	h->addRelatesTo(getIncomingId());

	std::string expires = getIncomingRenewExpires();
	std::string ident = getIncomingEventSourceIdent();

	bool success = eventingService->renewSubscription(ident, expires);
	
	// Body
	SoapBody* b = getEnvelope()->getBody();
    XMLEntity* renewResponse = b->appendChild("wse:RenewResponse");
    if (success)
    {
        renewResponse->addTextNode("wse:Expires", expires);
    }

	if (!configureUnicast())
	{
		setRouting(UNKNOWN_ROUTING);
		setSendProtocol(UNKNOWN_PROTOCOL);
	}
}

void DPWS11Message::createUnsubscribeMessage(const Dev::Service & localSinkService, const Dev::Service & remoteSourceService)
{
	initMessage("Unsubscribe");
	// Add eventing namespace
	getEnvelope()->addNamespace("wse", WS_NS_EVENTING);
	// Header
	SoapHeader * h = getEnvelope()->getHeader();
	h->addAction(WS_ACTION_UNSUBSCRIBE);
	h->addTo(remoteSourceService.getEndpointReference().getAddress());
	XMLEntity * ident = h->addTextNode("wse:Identifier", localSinkService.getEndpointReference().getReferenceParameters());
	ident->addAttribute("wsa:IsReferenceParameter", "true");
	// Body
	SoapBody* b = getEnvelope()->getBody();
	b->addTextNode("wse:Unsubscribe");
	// Send explicitly to event source address
	auto sourceAddr = std::make_shared<Binding>(remoteSourceService.getEndpointReference().getAddress());
	setRequest(true);
	configureUnicast(sourceAddr);
}

void DPWS11Message::createUnsubscribeResponse(const Dev::Device & device, unsigned int serviceIndex)
{
	initMessage("UnsubscribeResponse");
	// Add eventing namespace
	getEnvelope()->addNamespace("wse", WS_NS_EVENTING);

	if (serviceIndex >= device.getServiceCount())
		throw std::runtime_error("Valid service index needed!");
	std::shared_ptr<Service> eventingService = device.getService(serviceIndex);

	// Unsubscribe

	std::string ident = getIncomingEventSourceIdent();
	eventingService->cancelSubscription(ident);

	// Header
	SoapHeader * h = getEnvelope()->getHeader();
	h->addAction(WS_ACTION_UNSUBSCRIBE_RESPONSE);
	h->addRelatesTo(getIncomingId());

	if (!configureUnicast())
	{
		setRouting(UNKNOWN_ROUTING);
		setSendProtocol(UNKNOWN_PROTOCOL);
	}
}

bool DPWS11Message::configureUnicast(std::shared_ptr<Binding> destination)
{
	if (destination != nullptr || (getIncomingReplyToAddr().compare("") != 0
			&& getIncomingReplyToAddr().compare(WS_ADDRESSING_ANONYMOUS) != 0))
	{
		// Send to given destination
		if (destination != nullptr)
			setDestination(destination);
		else
		{
			// Explicit request to send a reply to an address
			auto replyBinding = std::make_shared<Binding>(getIncomingReplyToAddr());
			if (replyBinding->getIp().compare("") != 0) {
				setDestination(replyBinding);
			}
			else
				return false;
		}
		// Set send protocol with respect to destination type
		if (getDestination()->getType() == AbstractBinding::TCP_HTTP)
			setSendProtocol(TCP_HTTP);
		else
			setSendProtocol(UDP_UNICAST);
	}
	else  // replyTo omitted, default case
	{
		// Direct reply, set destination address to source address
		setDestination(std::make_shared<Binding>(getSource()->getIp(), getSource()->getPort()));
		// Send to address the way it was received unless it was received via multicast
		if (getReceiveProtocol() == UDP_MULTICAST)
			setSendProtocol(UDP_UNICAST);
		else
			setSendProtocol(getReceiveProtocol());
	}
	setRouting(UNICAST);
	return true;
}

bool DPWS11Message::configureMulticast()
{
	setSendProtocol(UDP_MULTICAST);
	setRouting(MULTICAST);
	setDestination(std::shared_ptr<Binding>(new Binding(UDP_MULTICAST_IP_V4, UPD_MULTICAST_DISCOVERY_PORT)));
	return true;
}

void DPWS11Message::copyRaw(const Message& msg)
{
	setRawBuffer(msg.getRawBuffer());
	if (msg.getSource())
		setSource(std::make_shared<IPBinding>(*msg.getSource()));
	if (msg.getDispatcher())
		setDispatcher(std::make_shared<IPBinding>(*msg.getDispatcher()));
	if (msg.getDestination())
		setDestination(std::make_shared<Binding>(*msg.getDestination()));
	setReceiveProtocol(msg.getReceiveProtocol());
	setRouting(msg.getRouting());
    //if (const DPWS11Message * dpwsMsg = dynamic_cast<const DPWS11Message *>(&msg)) {
    //    if (dpwsMsg->rawXML)
    //        this->rawXML = std::make_shared<XMLEntity>(*dpwsMsg->rawXML);
    //    if (dpwsMsg->envelope)
    //        this->envelope = std::make_shared<SoapEnvelope>(*dpwsMsg->envelope);
    //}
}

bool DPWS11Message::parseXML(const std::string& str, const StringVector & customActions) {
	return xmlparser.parse(this, str, customActions);
}

const std::string DPWS11Message::getId() const {
	return id;
}

const std::string & DPWS11Message::getIncomingAction() const {
    return incAction;
}

void DPWS11Message::setIncomingAction(const std::string & newValue) {
	this->incAction.assign(newValue);
}

const std::string & DPWS11Message::getIncomingTo() const {
    return incTo;
}

void DPWS11Message::setIncomingTo(const std::string & newValue) {
	this->incTo.assign(newValue);
}

const std::string & DPWS11Message::getIncomingRelatesTo() const {
    return incRelatesTo;
}

void DPWS11Message::setIncomingRelatesTo(const std::string & newValue) {
	this->incRelatesTo.assign(newValue);
}

const std::string & DPWS11Message::getIncomingReplyToAddr() const {
    return incReplyToAddr;
}

void DPWS11Message::setIncomingReplyToAddr(const std::string & newValue) {
	this->incReplyToAddr.assign(newValue);
}

const std::string & DPWS11Message::getIncomingId() const {
    return incId;
}

void DPWS11Message::setIncomingId(const std::string & newValue) {
	this->incId.assign(newValue);
}

const Dev::EndpointReference & DPWS11Message::getIncomingDeviceEPRAddress() const {
    return incDeviceEPRAddress;
}

void DPWS11Message::setIncomingDeviceEPRAddress(const Dev::EndpointReference & newValue) {
	this->incDeviceEPRAddress = newValue;
}

const Dev::EndpointReference & DPWS11Message::getIncomingSubManEPRAddress() const {
    return incSubManEPRAddress;
}

void DPWS11Message::setIncomingSubManEPRAddress(const Dev::EndpointReference & newValue) {
	this->incSubManEPRAddress = newValue;
}

const std::string & DPWS11Message::getIncomingScopes() const {
    return incScopes;
}

void DPWS11Message::setIncomingScopes(const std::string & newValue) {
	this->incScopes.assign(newValue);
}

const std::vector<std::string> & DPWS11Message::getIncomingWSDLLocations() {
    return incWSDLLocations;
}

void DPWS11Message::addIncomingWSDLLocation(const std::string & newValue) {
	this->incWSDLLocations.push_back(newValue);
}

const Data::QVector & DPWS11Message::getIncomingTypes() const {
	return incTypes;
}

void DPWS11Message::setIncomingTypes(const Data::QVector & newValue) {
	this->incTypes = newValue;
}

int DPWS11Message::getIncomingMetadataVersion() const {
    return incMetadataVersion;
}

void DPWS11Message::setIncomingMetadataVersion(int newValue) {
	this->incMetadataVersion = newValue;
}

OSCLib::Dev::DeviceCharacteristics & DPWS11Message::getIncomingDeviceCharacteristics() {
    return incDeviceCharacteristics;
}

const std::string & DPWS11Message::getIncomingXAddrs() const {
    return incXAddrs;
}

void DPWS11Message::setIncomingXAddrs(const std::string & newValue) {
	this->incXAddrs.assign(newValue);
}

std::shared_ptr<Data::Subscription> DPWS11Message::getIncomingSubscription() const {
	return incSubscription;
}

void DPWS11Message::setIncomingSubscription(std::shared_ptr<Data::Subscription> newValue) {
	this->incSubscription = newValue;
}

const std::string & DPWS11Message::getIncomingRenewExpires() const {
	return incRenewExpires;
}

void DPWS11Message::setIncomingRenewExpires(const std::string & newValue) {
	this->incRenewExpires.assign(newValue);
}

bool DPWS11Message::getIncomingRenewResponseSucceeded() const
{
    return this->incRenewResponseSucceeded;
}

void DPWS11Message::setIncomingRenewResponseSucceeded(bool newValue)
{
    this->incRenewResponseSucceeded = newValue;
}

const std::string & DPWS11Message::getIncomingEventSourceIdent() const {
	return incEventSourceIdentifier;
}

void DPWS11Message::setIncomingEventSourceIdent(const std::string & newValue) {
	this->incEventSourceIdentifier.assign(newValue);
}

std::string DPWS11Message::getShortName() const {
    return shortName;
}

void DPWS11Message::setShortName(const std::string & newValue) {
	this->shortName = newValue;
}

std::string DPWS11Message::getHttpRequestType() const {
	return httpRequestType;
}

void DPWS11Message::setHttpRequestType(std::string newValue) {
	this->httpRequestType = newValue;
}

std::string DPWS11Message::getHttpUrl() const {
	return httpUrl;
}

void DPWS11Message::setHttpUrl(std::string newValue) {
	this->httpUrl = newValue;
}

DPWS11MessageXMLParser & DPWS11Message::getMessageParser() {
	return xmlparser;
}

const std::vector<std::shared_ptr<Dev::Service>> & DPWS11Message::getHostedServices() {
	return hostedServices;
}

void DPWS11Message::addHostedService(std::shared_ptr<Dev::Service> service) {
	hostedServices.push_back(service);
}

bool DPWS11Message::isSkipGenerateRawBuffer() const {
    return skipGenerateRawBuffer;
}

void DPWS11Message::setSkipGenerateRawBuffer(bool newValue) {
    this->skipGenerateRawBuffer = newValue;
}

void DPWS11Message::setId(const std::string & newId) {
	id = newId;
}

std::shared_ptr<Soap::SoapEnvelope> DPWS11Message::getEnvelope() {
    return envelope;
}

bool DPWS11Message::isSoap() {
    return getEnvelope() != nullptr;
}

} /* namespace DPWS */
} /* namespace Comm */
} /* namespace OSCLib */
