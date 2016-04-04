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
 * DPWS11MessageXMLParser.cpp
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: besting, roehser
 */

#include "OSCLib/Comm/DPWS/DPWS11Constants.h"
#include "OSCLib/Comm/Soap/XMLEntity.h"
#include "OSCLib/Comm/DPWS/DPWS11Message.h"
#include "OSCLib/Comm/DPWS/DPWS11MessageXMLParser.h"
#include "OSCLib/Comm/DPWS/DPWS11SoapParserHandler.h"
#include "OSCLib/Data/Subscription.h"
#include "OSCLib/Data/OSCP/OSCPConstants.h"
#include "OSCLib/Dev/DeviceCharacteristics.h"
#include "OSCLib/Dev/EndpointReference.h"
#include "OSCLib/Dev/Service.h"
#include "OSCLib/Util/TypeConversion.h"
#include "OSCLib/Util/DebugOut.h"

#include <algorithm>
#include <string>

using namespace rapidxml;

namespace OSCLib {
namespace Comm {
namespace DPWS {

DPWS11MessageXMLParser::DPWS11MessageXMLParser() :
		xmlParseBuf(1), doc(nullptr) {

}

DPWS11MessageXMLParser::~DPWS11MessageXMLParser() {

}

Dev::EndpointReference DPWS11MessageXMLParser::parseEndpointReference(rapidxml::xml_node<>* parent)
{
	xml_node<>* nodeEpr = parent;

	Dev::EndpointReference epr;
	if (nodeEpr == nullptr) {
		return epr;
	}

	const std::string address(getChildValueByQName(WS_NS_ADDRESSING, "Address", nodeEpr, true));
	epr.setAddress(address);

	xml_node<>* nodeRef = getChildByQName(WS_NS_ADDRESSING, "ReferenceParameters", nodeEpr);
	if (nodeRef != nullptr) {
		epr.setReferenceParameters(getChildValueByQName(WS_NS_EVENTING, "Identifier", nodeRef));
	}

	return epr;
}

void DPWS11MessageXMLParser::parseSubscribe(DPWS11Message * dpws11msg, xml_node<>* nodeBody)
{
	xml_node<>* nodeSubscribe = getChildByQName(WS_NS_EVENTING, "Subscribe", nodeBody, true);

	if (nodeSubscribe != nullptr) {
		dpws11msg->setIncomingSubscription(std::shared_ptr<Data::Subscription>(new Data::Subscription()));
		std::shared_ptr<Data::Subscription> incSubscription(dpws11msg->getIncomingSubscription());

		const std::string endToName(getQNameString(WS_NS_EVENTING, "EndTo"));
		Dev::EndpointReference endToEpr = parseEndpointReference(nodeSubscribe->first_node(endToName.c_str()));
		incSubscription->setEndTo(endToEpr);

		xml_node<>* nodeDelivery = getChildByQName(WS_NS_EVENTING, "Delivery", nodeSubscribe);
		const std::string notifyToName(getQNameString(WS_NS_EVENTING, "NotifyTo"));
		Dev::EndpointReference notifyToEpr = parseEndpointReference(nodeDelivery->first_node(notifyToName.c_str()));
		incSubscription->setNotifyTo(notifyToEpr);

		incSubscription->setExpires(getChildValueByQName(WS_NS_EVENTING, "Expires", nodeSubscribe));
		incSubscription->setFilterAction(getChildValueByQName(WS_NS_EVENTING, "Filter", nodeSubscribe));
	}
}

void DPWS11MessageXMLParser::parseSubscribeResponse(DPWS11Message * dpws11msg, xml_node<>* nodeBody)
{
	xml_node<>* nodeSubscribeResponse = getChildByQName(WS_NS_EVENTING, "SubscribeResponse", nodeBody, true);

	if (nodeSubscribeResponse != nullptr) {
		xml_node<>* nodeManager = getChildByQName(WS_NS_EVENTING, "SubscriptionManager", nodeSubscribeResponse, true);
		if (nodeManager == nullptr)
			return;

		Dev::EndpointReference subManEpr = parseEndpointReference(nodeManager);
		dpws11msg->setIncomingSubManEPRAddress(subManEpr);

	}
}

void DPWS11MessageXMLParser::parseRenew(DPWS11Message * dpws11msg, xml_node<>* nodeHeader, xml_node<>* nodeBody)
{
	xml_node<>* nodeRenew = getChildByQName(WS_NS_EVENTING, "Renew", nodeBody, true);

	dpws11msg->setIncomingEventSourceIdent(getChildValueByQName(WS_NS_EVENTING, "Identifier", nodeHeader));

	if (nodeRenew != nullptr) {
		dpws11msg->setIncomingRenewExpires(getChildValueByQName(WS_NS_EVENTING, "Expires", nodeRenew));
	}
}

void DPWS11MessageXMLParser::parseUnsubscribe(DPWS11Message * dpws11msg, xml_node<>* nodeHeader)
{
	dpws11msg->setIncomingEventSourceIdent(getChildValueByQName(WS_NS_EVENTING, "Identifier", nodeHeader));
}

void DPWS11MessageXMLParser::parseProbe(DPWS11Message * dpws11msg, xml_node<>* nodeBody)
{
	xml_node<>* nodeProbe = getChildByQName(WS_NS_DISCOVERY, "Probe", nodeBody, true);

	if (nodeProbe != nullptr) {

		xml_node<>* nodeTypes = getChildByQName(WS_NS_DISCOVERY, "Types", nodeProbe);
		if (nodeTypes != nullptr) {
			dpws11msg->setIncomingTypes(typesNodeToVector(nodeTypes));
		}

		xml_node<>* nodeScopes = getChildByQName(WS_NS_DISCOVERY, "Scopes", nodeProbe);
		if (nodeScopes != nullptr) {
			dpws11msg->setIncomingScopes(nodeScopes->value());
		}
	}
}

void DPWS11MessageXMLParser::parseBasicDiscovery(DPWS11Message * dpws11msg, xml_node<>* innerNode)
{
	xml_node<>* nodeTypes = getChildByQName(WS_NS_DISCOVERY, "Types", innerNode);
	if (nodeTypes != nullptr) {
		dpws11msg->setIncomingTypes(typesNodeToVector(nodeTypes));
	}

	xml_node<>* nodeScopes = getChildByQName(WS_NS_DISCOVERY, "Scopes", innerNode);
	if (nodeScopes != nullptr) {
		dpws11msg->setIncomingScopes(nodeScopes->value());
	}

	xml_node<>* nodeMeta = getChildByQName(WS_NS_DISCOVERY, "MetadataVersion", innerNode);
	if (nodeMeta != nullptr) {
		dpws11msg->setIncomingMetadataVersion(atoi(nodeMeta->value()));
	}

	xml_node<>* nodeAdr = getChildByQName(WS_NS_DISCOVERY, "XAddrs", innerNode);
	if (nodeAdr != nullptr) {
		dpws11msg->setIncomingXAddrs(nodeAdr->value());
	}
	dpws11msg->setIncomingDeviceEPRAddress(parseEndpointReference(innerNode->first_node()));
}

void DPWS11MessageXMLParser::parseResolve(DPWS11Message * dpws11msg, xml_node<>* nodeBody)
{
	xml_node<>* nodeResolve = getChildByQName(WS_NS_DISCOVERY, "Resolve", nodeBody, true);

	parseNamespaces(nodeResolve);

	if (nodeResolve != nullptr) {
		dpws11msg->setIncomingDeviceEPRAddress(parseEndpointReference(nodeResolve->first_node()));
	}
}

bool DPWS11MessageXMLParser::parseSOAPHeader(DPWS11Message * dpws11msg, xml_node<>* header) {

	if (assertChildExists(WS_NS_ADDRESSING, "MessageID", header))
		dpws11msg->setIncomingId(getChildValueByQName(WS_NS_ADDRESSING, "MessageID", header));

	if (assertChildExists(WS_NS_ADDRESSING, "To", header))
		dpws11msg->setIncomingTo(getChildValueByQName(WS_NS_ADDRESSING, "To", header));

	if (assertChildExists(WS_NS_ADDRESSING, "RelatesTo", header))
		dpws11msg->setIncomingRelatesTo(getChildValueByQName(WS_NS_ADDRESSING, "RelatesTo", header));

	if (assertChildExists(WS_NS_ADDRESSING, "Action", header, true))
		dpws11msg->setIncomingAction(getChildValueByQName(WS_NS_ADDRESSING, "Action", header));

	if (assertChildExists(WS_NS_ADDRESSING, "ReplyTo", header)) {
		xml_node<>* nodeReply = getChildByQName(WS_NS_ADDRESSING, "ReplyTo", header);

		if (assertChildExists(WS_NS_ADDRESSING, "Address", nodeReply))
			dpws11msg->setIncomingReplyToAddr(getChildValueByQName(WS_NS_ADDRESSING, "Address", nodeReply));
	}

	return true;
}

bool DPWS11MessageXMLParser::parseSOAPBody(DPWS11Message * dpws11msg, xml_node<>* header, xml_node<>* body, const Util::StringVector & customActions) {
	const std::string action(dpws11msg->getIncomingAction());

	if (action.compare(WS_ACTION_PROBE) == 0) {
		parseProbe(dpws11msg, body);
	}
	if (action.compare(WS_ACTION_PROBE_MATCHES) == 0) {

		if (!assertChildExists(WS_NS_DISCOVERY, "ProbeMatches", body, true))
			return false;

		xml_node<>* nodeProbeMatches = getChildByQName(WS_NS_DISCOVERY, "ProbeMatches", body);

		if (!assertChildExists(WS_NS_DISCOVERY, "ProbeMatch", nodeProbeMatches, true))
			return false;

		xml_node<>* innerNode = getChildByQName(WS_NS_DISCOVERY, "ProbeMatch", nodeProbeMatches);

		parseBasicDiscovery(dpws11msg, innerNode);
	}
	if (action.compare(WS_ACTION_RESOLVE_MATCHES) == 0) {
		if (!assertChildExists(WS_NS_DISCOVERY, "ResolveMatches", body, true)) {
			return false;
		}

		xml_node<>* nodeResolveMatches = getChildByQName(WS_NS_DISCOVERY, "ResolveMatches", body);

		if (!assertChildExists(WS_NS_DISCOVERY, "ResolveMatch", nodeResolveMatches))
			return false;

		xml_node<>* innerNode = getChildByQName(WS_NS_DISCOVERY, "ResolveMatch", nodeResolveMatches);
		if (innerNode == nullptr) {
			Util::DebugOut(Util::DebugOut::Error, "DPWS11MessageXMLParser") << "'ResolveMatch' node missing!";
		}
		parseBasicDiscovery(dpws11msg, innerNode);
	}
	if (action.compare(WS_ACTION_HELLO) == 0) {
		xml_node<>* nodeHello = getChildByQName(WS_NS_DISCOVERY, "Hello", body, true);
		if (nodeHello == nullptr) {
			return false;
		}
		parseBasicDiscovery(dpws11msg, nodeHello);
	}
	if (action.compare(WS_ACTION_RESOLVE) == 0) {
		parseResolve(dpws11msg, body);
	}
	if (action.compare(WS_ACTION_SUBSCRIBE) == 0) {
		parseSubscribe(dpws11msg, body);
	}
	if (action.compare(WS_ACTION_SUBSCRIBE_RESPONSE) == 0) {
		parseSubscribeResponse(dpws11msg, body);
	}
	if (action.compare(WS_ACTION_RENEW) == 0) {
		parseRenew(dpws11msg, header, body);
	}
	if (action.compare(WS_ACTION_UNSUBSCRIBE) == 0) {
		parseUnsubscribe(dpws11msg, header);
	}

    if (action.compare(WS_ACTION_RENEW_RESPONSE) == 0) {
        dpws11msg->setIncomingRenewResponseSucceeded(false);
        xml_node<>* nodeRenewResponse = getChildByQName(WS_NS_EVENTING, "RenewResponse", body);
        if (nodeRenewResponse != nullptr) {
            dpws11msg->setIncomingRenewResponseSucceeded(getChildByQName(WS_NS_EVENTING, "Expires", nodeRenewResponse) != 0);
        }
    }

	if (std::find(customActions.begin(), customActions.end(), action) != customActions.end()) {
		parseParameters(dpws11msg, body);
	}
    
    if (body->first_node() != nullptr)
    {
        Soap::XMLEntity xe(body->first_node());
        dpws11msg->bodyRawContent = xe.toString();
    }    

	std::map<std::string, std::shared_ptr<DPWS11SoapParserHandler>>::iterator it = parseHandlers.begin();
	while (it != parseHandlers.end())
	{
		if (action.compare(it->first) == 0) {
			it->second->parseBody(this, dpws11msg, body);
		}
		it++;
	}

	return true;
}


bool DPWS11MessageXMLParser::parseSOAP(DPWS11Message * dpws11msg, xml_node<>* root, const Util::StringVector & customActions) {

	if (!assertChildExists(WS_NS_SOAP_ENVELOPE, "Header", root, true))
		return false;
	if (!assertChildExists(WS_NS_SOAP_ENVELOPE, "Body", root, true))
		return false;

	xml_node<>* header = getChildByQName(WS_NS_SOAP_ENVELOPE, "Header", root);
	xml_node<>* body = getChildByQName(WS_NS_SOAP_ENVELOPE, "Body", root);

	parseNamespaces(header);
	parseNamespaces(body);

	// Check addressing version
	if (nsMap.find(WS_NS_ADDRESSING) == nsMap.end()) {
		Util::DebugOut(Util::DebugOut::Info, "DPWS11MessageXMLParser") << "DPWS version not supported, skipping message.";
		return false;
	}

	bool status = true;
	status &= parseSOAPHeader(dpws11msg, header);
	status &= parseSOAPBody(dpws11msg, header, body, customActions);
	return status;

}

bool DPWS11MessageXMLParser::parse(DPWS11Message * dpws11msg, const std::string & xmlString, const Util::StringVector & customActions)
{
	if (xmlString.empty() ) {
		Util::DebugOut(Util::DebugOut::Error, "DPWS11MessageXMLParser") << "Got empty message.";
		return false;
	}

	xmlParseBuf.resize(xmlString.size()+1, false);
	xmlString.copy(xmlParseBuf.begin(), xmlString.size(), 0);
	xmlParseBuf[xmlString.size()] = '\0';

	try
	{
		doc.reset(new xml_document<>);
		doc->parse<0>(xmlParseBuf.begin());

		if (doc->first_node() == nullptr) {
			Util::DebugOut(Util::DebugOut::Error, "DPWS11MessageXMLParser") << "Got empty message.";
			return false;
		}
	}
	catch(rapidxml::parse_error& e) {
		Util::DebugOut(Util::DebugOut::Error, "DPWS11MessageXMLParser") << "Parse error: " << e.what() << ".";
	}

	xml_node<>* root = doc->first_node();

    if (root == nullptr)
    {
        Util::DebugOut(Util::DebugOut::Error, "DPWS11MessageXMLParser") << "No valid XML root document.";
        return false;
    }

	// Generate map for namespaces
	parseNamespaces(root);

	// Check if we have a message we can parse.
	bool http = parseHtmlInfo(dpws11msg, doc.get());
	assertChildExists(WS_MEX_DIALECT_WSDL, "definitions", doc.get());

	const bool soap = assertChildExists(WS_NS_SOAP_ENVELOPE, "Header", root);
	if (soap) {
		bool status = parseSOAP(dpws11msg, root, customActions);
		doc->clear();
		return status;
	}

	if (http) {
		return true;
	}

	Util::DebugOut(Util::DebugOut::Error, "DPWS11MessageXMLParser") << "Unknown message format.";
	return false;
}

bool DPWS11MessageXMLParser::parseHtmlInfo(DPWS11Message * dpws11msg, rapidxml::xml_node<> * root) {

	if (root == nullptr) {
		return false;
	}

	rapidxml::xml_node<> * httpinfo = root->first_node("httpinfo");

	if (httpinfo == nullptr) {
		return false;
	}

	rapidxml::xml_node<> * url = httpinfo->first_node("url");
	rapidxml::xml_node<> * type = httpinfo->first_node("type");

	if (type == nullptr || url == nullptr) {
			return false;
	}

	dpws11msg->setHttpUrl(url->value());
	dpws11msg->setHttpRequestType(type->value());
	return true;
}

Data::QVector DPWS11MessageXMLParser::typesNodeToVector(xml_node<>* node)
{
	std::map<std::string, std::string> prefixNsMap;

	{
		xml_node<>* next = node;
		// Collect all namespaces until root
		while (next != nullptr) {
			for (xml_attribute<>* attr = next->first_attribute();
				 attr; attr = attr->next_attribute()) {
				const std::string attrName(attr->name());
				if (attrName.find("xmlns:") != std::string::npos) {
					const std::string nsPrefix(attrName.substr(attrName.find(":") + 1));
					prefixNsMap[nsPrefix] = attr->value();
				}
			}
			next = next->parent();
		}
	}

	const Util::StringVector tokens(Util::splitString(std::string(node->value()), ' '));

	Data::QVector qnames;

	Util::StringVector::const_iterator token;
	for (token = tokens.begin(); token != tokens.end(); ++token) {
		size_t pos = token->find(":");
		if (pos != std::string::npos) {
			const std::string prefix(token->substr(0, pos));
			const std::string name(token->substr(pos + 1));
			const Data::QName qn(name, prefixNsMap[prefix], prefix);
			qnames.push_back(qn);
		}
	}
	return qnames;
}

void DPWS11MessageXMLParser::parseParameters(DPWS11Message * dpws11msg, xml_node<>* nodeBody) {

	if (nodeBody == nullptr)
		return;
	if (nodeBody->first_node() == nullptr)
		return;

	xml_node<>* parent = nodeBody;
	auto doc = nodeBody->document();

	for (auto attr = parent->first_attribute(); attr != nullptr; attr = attr->next_attribute()) {
		for (auto nextParamNode = parent->first_node();
				nextParamNode; nextParamNode = nextParamNode->next_sibling())
		{
			const std::string attributeName(attr->name(), attr->name_size());
			if (attributeName.find("xmlns") != std::string::npos) {
				nextParamNode->append_attribute(doc->allocate_attribute(attr->name(), attr->value(), attr->name_size(), attr->value_size()));
			}
		}
	}

	for (xml_node<>* nextParamNode = parent->first_node();
		nextParamNode; nextParamNode = nextParamNode->next_sibling())
	{
		Data::Parameter nextParameter("");
		nextParameter.createFromNode(nextParamNode);
		dpws11msg->parameters.push_back(nextParameter);
	}
}

void DPWS11MessageXMLParser::registerParseHandler(std::string action, std::shared_ptr<DPWS11SoapParserHandler> handler) {
	parseHandlers[action] = handler;
}

std::shared_ptr<DPWS11SoapParserHandler> DPWS11MessageXMLParser::getParseHandler(std::string action) {
    return parseHandlers[action];
}


} /* namespace DPWS */
} /* namespace Comm */
} /* namespace OSCLib */
