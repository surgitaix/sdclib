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
 * DPWS11WSDLParser.cpp
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: besting, roehser
 */

#include "OSCLib/Comm/DPWS/DPWS11Constants.h"
#include "OSCLib/Comm/DPWS/DPWS11Message.h"
#include "OSCLib/Comm/DPWS/DPWS11WSDLParser.h"
#include "OSCLib/Data/RemoteOperation.h"
#include "OSCLib/Dev/Service.h"
#include "OSCLib/Util/DebugOut.h"

using namespace rapidxml;
using namespace OSCLib::Dev;

namespace OSCLib {
namespace Comm {
namespace DPWS {

DPWS11WSDLParser::DPWS11WSDLParser() : xmlParseBuf(1) {

}

DPWS11WSDLParser::~DPWS11WSDLParser() {

}

bool DPWS11WSDLParser::parseWSDL(const std::string & wsdlContent, const std::string & serviceAddr, std::vector<std::shared_ptr<Service>> remoteServices)
{
	xmlParseBuf.resize(wsdlContent.size()+1, false);
	wsdlContent.copy(xmlParseBuf.begin(), wsdlContent.size(), 0);
	xmlParseBuf[wsdlContent.size()] = '\0';

	try {
		doc.reset(new rapidxml::xml_document<>());
		doc->parse<0>(xmlParseBuf.begin());

		if (doc->first_node() == nullptr) {
			Util::DebugOut(Util::DebugOut::Error, "DPWS11WSDLParser") << "Got empty WSDL structure.";
			doc.reset();
			return false;
		}
	}
	catch(rapidxml::parse_error& e) {
		Util::DebugOut(Util::DebugOut::Error, "DPWS11MessageXMLParser") << "Parse error: " << e.what() << ".";
		doc.reset();
		return false;
	}

	xml_node<>* root = doc->first_node();
	// Generate map for namespaces
	parseNamespaces(root);

    if (root == nullptr) {
        Util::DebugOut(Util::DebugOut::Error, "DPWS11MessageXMLParser") << "No valid XML root document.";
        doc.reset();
        return false;
    }

	// Parse by service node
    xml_node<>* serviceNode = getChildByQName(WS_MEX_DIALECT_WSDL, "service", root, false);
    if (serviceNode != nullptr)
    {
        xml_node<>* servicePortNode = getChildByQName(WS_MEX_DIALECT_WSDL, "port", serviceNode, true);

        while (servicePortNode != nullptr) {
            if (!parseServicePort(servicePortNode, root, remoteServices))
                return false;
            servicePortNode = getSiblingByQName(WS_MEX_DIALECT_WSDL, "port", servicePortNode);
        }
    }
    // Parse by given request location
    else
    {
        if (!assertChildExists(WS_MEX_DIALECT_WSDL, "binding", root, true))
        	return false;
        
        xml_node<>* bindingNode = getChildByQName(WS_MEX_DIALECT_WSDL, "binding", root, true);
        const std::string targetNs(root->first_attribute("targetNamespace")->value());

        while (bindingNode != nullptr) {
        	const std::string portTypeName(stripNsPrefix(bindingNode->first_attribute("type")->value()));
            Service * s = findRemoteServiceByServiceAddress(serviceAddr, remoteServices);
            if (s == nullptr)
            {
                Util::DebugOut(Util::DebugOut::Error, "DPWS11WSDLParser") << "Unable to resolve service by port type.";
                return false;
            }
            // Get port type node
            xml_node<>* portType = getWSDLNodeByAttributeMatch(root, "portType", "name", portTypeName);
            if (portType == nullptr) {
                Util::DebugOut(Util::DebugOut::Error, "DPWS11WSDLParser") << "Unable to resolve service by port type (node missing).";
                return false;
            }
            // Parse operation
            parseOperation(s, portType, targetNs);
            bindingNode = getSiblingByQName(WS_MEX_DIALECT_WSDL, "binding", root);
        }
    }

    doc.reset();
	return true;
}

bool DPWS11WSDLParser::parseServicePort(xml_node<> * servicePortNode, rapidxml::xml_node<>* wsdlNode, std::vector<std::shared_ptr<Service>> remoteServices) {

	if (!assertChildExists(WS_NS_WSDL_SOAP12_SCHEMA, "address", servicePortNode, true))
		return false;

	const std::string serviceLoc(getChildByQName(WS_NS_WSDL_SOAP12_SCHEMA, "address", servicePortNode)
			->first_attribute("location")
			->value());

	const std::string targetNs(wsdlNode->first_attribute("targetNamespace")->value());

	// Find matching service in remote services list
	Service * s = findRemoteServiceByServiceAddress(serviceLoc, remoteServices);
	if (s != nullptr) {
		// Get right port type node
		xml_node<> * portType = getPortTypeNode(servicePortNode, wsdlNode);

		parseOperation(s, portType, targetNs);
	}

	return true;
}

Dev::Service * DPWS11WSDLParser::findRemoteServiceByServiceAddress(const std::string & serviceLocation, std::vector<std::shared_ptr<Service>> remoteServices) {
	for (auto &nextEntry : remoteServices) {
        if (serviceLocation.find(nextEntry->getEndpointReference().getAddress()) != std::string::npos) {
            return nextEntry.get();
		}
	}
	return nullptr;
}

xml_node<> * DPWS11WSDLParser::getPortTypeNode(xml_node<> * servicePortNode, xml_node<>* wsdlNode) {
	const std::string bindingName(stripNsPrefix(servicePortNode->first_attribute("binding")->value()));

	// Search right binding tag
	xml_node<>* bindingNode = getWSDLNodeByAttributeMatch(wsdlNode, "binding", "name", bindingName);
	if (bindingNode == nullptr) {
		Util::DebugOut(Util::DebugOut::Error, "DPWS11WSDLParser") << "WSDL 'binding' node missing.";
		return nullptr;
	}

	const std::string portTypeName(stripNsPrefix(bindingNode->first_attribute("type")->value()));

	// Search right port type tag
	xml_node<>* portType = getWSDLNodeByAttributeMatch(wsdlNode, "portType", "name", portTypeName);
	if (portType == nullptr) {
		Util::DebugOut(Util::DebugOut::Error, "DPWS11WSDLParser") << "WSDL 'portType' node missing.";
		return nullptr;
	}

	return portType;
}

std::string DPWS11WSDLParser::stripNsPrefix(const std::string & input) {

	size_t posPref = input.find(':');
	if (posPref != std::string::npos)
		return input.substr(posPref + 1);
	else
		return input;
}

void DPWS11WSDLParser::parseOperation(Dev::Service * service, xml_node<> * portTypeNode, const std::string & targetNamespace) {

	// Add operations and port types
	const std::string portTypeLocalName(portTypeNode->first_attribute("name")->value());

	Data::QName pt(portTypeLocalName, targetNamespace);

	xml_node<>* nextOp = getChildByQName(WS_MEX_DIALECT_WSDL, "operation", portTypeNode);

	while (nextOp != nullptr) {
		const std::string operation(nextOp->first_attribute("name")->value());
		Util::DebugOut(Util::DebugOut::Info, "DPWS11WSDLParser") << "OK, new operation: " << operation;
        if (operation.length() == 0)
            Util::DebugOut(Util::DebugOut::Error, "DPWS11WSDLParser") << "Error, insufficient WSDL information (empty operation name).";

        std::shared_ptr<Data::RemoteOperation> op(new Data::RemoteOperation(operation, pt));
		service->addOperation(op);

		// Try to get soap action (input, output)
		xml_node<>* inputActionNode = getChildByQName(WS_MEX_DIALECT_WSDL, "input", nextOp);
		op->setInputAction(parseSoapAction(inputActionNode));

		xml_node<>* outputActionNode = getChildByQName(WS_MEX_DIALECT_WSDL, "output", nextOp);
		op->setOutputAction(parseSoapAction(outputActionNode));

		nextOp = getSiblingByQName(WS_MEX_DIALECT_WSDL, "operation", nextOp);
	}
}

std::string DPWS11WSDLParser::parseSoapAction(xml_node<>* actionNode) {

	std::string result;
	if (actionNode == nullptr)
		return result;

	std::string actionName(getQNameString(WS_NS_ADDRESSING, "Action"));
	xml_attribute<>* adrAttr = actionNode->first_attribute(actionName.c_str());
	if (adrAttr != nullptr)
		result = std::string(adrAttr->value());
	else {
		parseNamespaces(actionNode);
		actionName = getQNameString(WS_NS_ADDRESSING_METADATA, "Action");
		adrAttr = actionNode->first_attribute(actionName.c_str());
		if (adrAttr != nullptr)
			result = std::string(adrAttr->value());
	}
	return result;
}

xml_node<>* DPWS11WSDLParser::getWSDLNodeByAttributeMatch(xml_node<>* wsdlNode, std::string nodeName, std::string attrName, std::string attrValue)
{
	xml_node<>* nextNode = getChildByQName(WS_MEX_DIALECT_WSDL, nodeName, wsdlNode);

	while (nextNode != nullptr) {
		xml_attribute<>* attr = nextNode->first_attribute(attrName.c_str());
		if (attr != nullptr) {
			const std::string nextValue(attr->value());
			if (nextValue.compare(attrValue) == 0) {
				return nextNode;
			}
		}
		nextNode = getSiblingByQName(WS_MEX_DIALECT_WSDL, nodeName, nextNode);
	}
	return nullptr;
}

} /* namespace DPWS */
} /* namespace Comm */
} /* namespace OSCLib */
