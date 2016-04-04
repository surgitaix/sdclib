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
 * DPWS11WSDLBuilder.cpp
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: besting, roehser
 */

#include "OSCLib/Comm/DPWS/DPWS11Constants.h"
#include "OSCLib/Comm/DPWS/DPWS11Message.h"
#include "OSCLib/Comm/DPWS/DPWS11WSDLBuilder.h"
#include "OSCLib/Comm/Binding.h"
#include "OSCLib/Comm/Soap/XMLEntity.h"
#include "OSCLib/Data/QName.h"
#include "OSCLib/Dev/Device.h"
#include "OSCLib/Util/DebugOut.h"

#include <algorithm>

using namespace OSCLib;
using namespace OSCLib::Comm::Soap;
using namespace OSCLib::Data;
using namespace OSCLib::Dev;

namespace OSCLib {
namespace Comm {
namespace DPWS {

DPWS11WSDLBuilder::DPWS11WSDLBuilder() {

}

DPWS11WSDLBuilder::~DPWS11WSDLBuilder() {

}

void DPWS11WSDLBuilder::addServiceNode(const DPWS11Message & msg, const Service & service, XMLEntity * definitionsNode, const OperationVector & operations) const
{
	XMLEntity * serviceNode = definitionsNode->appendChild("wsdl:service")
			->addAttribute("name", service.getServiceId());

	Util::StringVector localParts;
	for (OperationVector::const_iterator opsIt = operations.begin(); opsIt != operations.end(); ++opsIt) {
		const std::string localPart((*opsIt)->getPortType().getLocal());
		if (std::find(localParts.begin(), localParts.end(), localPart) == localParts.end()) {
			localParts.push_back(localPart);
		}
	}

	// Add port(s) to service (WSDL 1.1)
	for (Util::StringVector::iterator strIt = localParts.begin(); strIt != localParts.end(); ++strIt) {
		serviceNode->appendChild("wsdl:port")
				->addAttribute("name", *strIt + "Port")
				->addAttribute("binding", "tns:" + *strIt + "Binding1")
				->appendChild("soap:address")
				->addAttribute("location", service.getDefaultTransportAddr(DPWS11, msg.getDispatcher()));
	}
}

void DPWS11WSDLBuilder::addWSDLCardinality(const Parameter & parameter, XMLEntity * nextElement) const
{
	if(parameter.getMinOccurs() != 1) {
		std::string s;
		int i = parameter.getMinOccurs();
		if (i >= 0)
			s = std::to_string(i);
		else
			s = "unbounded";
		nextElement->addAttribute("minOccurs", s);
	}
	if(parameter.getMaxOccurs() != 1) {
		std::string s;
		int i = parameter.getMaxOccurs();
		if (i >= 0)
			s = std::to_string(i);
		else
			s = "unbounded";
		nextElement->addAttribute("maxOccurs", s);
	}
}

void DPWS11WSDLBuilder::addWSDLLink(const DPWS11Message & msg, Soap::XMLEntity * metaDataNode, const Dev::Service & service) const
{
	// Add one metadata section for each operation port type!
	std::map<std::string, std::vector<std::shared_ptr<Operation>>> nsOps = getOperationsGroupedByNamespace(service.getOperations());

	// First, add schemes and types for all namespaces
	std::map<std::string, std::vector<std::shared_ptr<Operation>>>::iterator nsAllOpsIt;
	for (nsAllOpsIt = nsOps.begin(); nsAllOpsIt != nsOps.end(); ++nsAllOpsIt) {
		const std::string nextNamespace(nsAllOpsIt->first);
		const std::string wsdlLink(service.getDefaultTransportAddr(DPWS11, msg.getDispatcher()) + "/" + nextNamespace + "/description.wsdl");
		
		metaDataNode->appendChild("wsx:MetadataSection")
				->addAttribute("Dialect", WS_MEX_DIALECT_WSDL)
				->appendChild("wsx:Location")
				->setValue(wsdlLink);
	}
}

std::map<std::string, OperationVector > DPWS11WSDLBuilder::getOperationsGroupedByNamespace(const OperationVector & ov) const
{
	// Collect all operations according to their namespaces
	std::map<std::string, OperationVector > nsOps;
	OperationVector::const_iterator it;
	for(it = ov.begin(); it != ov.end(); ++it){
		std::shared_ptr<Operation> op(*it);
		const std::string operationNamespace(op->getPortType().getNamespace());
		nsOps[operationNamespace].push_back(op);
	}
	return nsOps;
}

OperationVector DPWS11WSDLBuilder::getOperationsByNamespace(const OperationVector & ov, const std::string & nameSpace) const
{
	// Collect all operations according to their namespaces
	OperationVector nsOps;
	OperationVector::const_iterator it;
	for(it = ov.begin(); it != ov.end(); ++it){
		std::shared_ptr<Operation> op(*it);
		if (nameSpace.compare(op->getPortType().getNamespace()) == 0)
			nsOps.push_back(op);
	}
	return nsOps;
}

void DPWS11WSDLBuilder::addBindingNodes(XMLEntity * parent, const OperationVector & operations) const {
	// Map local port type name -> binding
	std::map<std::string, XMLEntity*> bindings;

	// Prepare binding(s) (WSDL 1.1)
	for (OperationVector::const_iterator opsIt = operations.begin(); opsIt != operations.end(); ++opsIt)
	{
		const std::string localPart((*opsIt)->getPortType().getLocal());
		if (bindings.find(localPart) == bindings.end()) {
			// Create binding tag, but add it later
			XMLEntity * wsdl1Binding = parent->appendChild("wsdl:binding", true);
			wsdl1Binding->addAttribute("name", localPart + "Binding1")
					->addAttribute("type", "tns:" + localPart)
					->appendChild("soap:binding")
					->addAttribute("style", "document")
					->addAttribute("transport", WS_NS_WSDL_SOAP_HTTP);
			// Store in map
			bindings[localPart] = wsdl1Binding;
		}
	}

	// Add operations to binding (WSDL 1.1)
	for (OperationVector::const_iterator nsOpsIt = operations.begin(); nsOpsIt != operations.end(); ++nsOpsIt)
	{
		std::shared_ptr<Operation> op(*nsOpsIt);
		const std::string opName(op->getName());
		const std::string typeName(op->getPortType().getLocal());

		XMLEntity * bindingsNode = bindings[typeName];
		XMLEntity * opBinding = bindingsNode->appendChild("wsdl:operation")
				->addAttribute("name", opName);

		opBinding->appendChild("soap:operation")
				->addAttribute("soapAction", "");

		opBinding->appendChild("wsdl:input")
				->appendChild("soap:body")
				->addAttribute("use", "literal");

		opBinding->appendChild("wsdl:output")
				->appendChild("soap:body")
				->addAttribute("use", "literal");
	}

	for (std::map<std::string, XMLEntity*>::iterator bndgsIt = bindings.begin(); bndgsIt != bindings.end(); ++bndgsIt)
		bndgsIt->second->addNode();
}

void DPWS11WSDLBuilder::addWSDLComplexParameters(XMLEntity * schemaNode, XMLEntity * element, const Parameters & params, const Parameter & parentParam, const OSCLib::Data::QName & operationPortType) const
{
	std::vector<XMLEntity*> toAdd;

	// Complex type
	XMLEntity* typeTag = schemaNode->appendChild("xs:complexType", true);
	// Both type and element tag refer to the TYPE of the parameter, by "name" AND by "type"
	const QName parmName = parentParam.getFinalQualifiedParameterName(operationPortType);
	QName typeName = parentParam.getFinalQualifiedParameterTypeName(operationPortType);
	if (typeName.getNamespace().compare(parmName.getNamespace()) == 0)
		typeName.setPrefix(parmName.getPrefix());
	//typeTag->addQualifiedAttribute("name", typeName, schemaNode);
	typeTag->addAttribute("name", typeName.getLocal());
	// Previous element reference
	element->addQualifiedAttribute("type", typeName, schemaNode);
	XMLEntity* compTag = typeTag->appendChild("xs:" + parentParam.getCompositorAsString(), true);
	toAdd.push_back(compTag);

	Parameters::const_iterator pIt;
	// For every parameter:
	// - Add one "element" tag, if parameter has no children.
	// - Else: add one "element" tag and create a new "complex" tag
	for(pIt = params.begin(); pIt != params.end(); ++pIt) {
		Parameter p = *pIt;
		XMLEntity* nextElement = compTag->appendChild("xs:element", true);
		toAdd.push_back(nextElement);
		//nextElement->addQualifiedAttribute("name", p.getFinalQualifiedParameterName(operationPortType), schemaNode);
		nextElement->addAttribute("name", p.getFinalQualifiedParameterName(operationPortType).getLocal());

		addWSDLCardinality(p, nextElement);

		if (!p.hasChildren()) {
			nextElement->addQualifiedAttribute("type", p.getFinalQualifiedParameterTypeName(operationPortType), schemaNode);
		}
		else {
			std::vector<Parameter> c(p.getCopyChildren());
			addWSDLComplexParameters(schemaNode, nextElement, c, p, operationPortType);
		}
	}

	typeTag->addNode();
	for (size_t i = 0; i < toAdd.size(); ++i) {
		toAdd[i]->addNode();
	}
}

std::string DPWS11WSDLBuilder::addWSDLMessage(XMLEntity * wsdlDoc, const QName & elementName, const Operation &  op, bool response) const
{
	std::string msgName = op.getName() + (response? "ResponseMessage" : "Message");

	XMLEntity * msgNode = wsdlDoc->appendChild("wsdl:message");
	msgNode->addAttribute("name", msgName);
	if (elementName.getLocal().length() > 0)
	{
		msgNode->appendChild("wsdl:part")
			->addAttribute("name", "parameters")
			->addQualifiedAttribute("element", elementName, msgNode);
	}
	return msgName;
}

XMLEntity * DPWS11WSDLBuilder::addWSDLOperationMessage(XMLEntity * portOp, const std::string & msgName, const Operation & op, bool response) const
{
	std::string action = response ? op.getOutputAction() : op.getInputAction();
	XMLEntity * opMsg = portOp->appendChild(response? "wsdl:output" : "wsdl:input", true);
	opMsg->addAttribute("message", "tns:" + msgName)
			->addAttribute("wsa:Action", action);
	return opMsg;
}

void DPWS11WSDLBuilder::addWSDLOperationParameters(Soap::XMLEntity * schemaNode, const Parameters & param, const std::string & opName, const OSCLib::Data::QName & operationPortType) const {
	if (param.size() != 0) {
		// Input element
		XMLEntity* elemOpIn = schemaNode->appendChild("xs:element", true);

		Parameter topLevel = (param.size() == 1)? param.at(0) : Parameter(opName);
		if (param.size() > 1)
		{
			for (size_t i = 0; i < param.size(); ++i)
			{
				topLevel.addChild(param.at(i));
			}
		}

		QName qParName = topLevel.getFinalQualifiedParameterName(operationPortType);

		//elemOpIn->addQualifiedAttribute("name", qParName, schemaNode);
		elemOpIn->addAttribute("name", qParName.getLocal());
		addWSDLCardinality(topLevel, elemOpIn);

		if (topLevel.hasChildren())
		{
			const std::vector<Parameter> c(topLevel.getCopyChildren());
			addWSDLComplexParameters(schemaNode, elemOpIn, c, topLevel, operationPortType);
		}
		else
		{
			QName qTypName = topLevel.getFinalQualifiedParameterTypeName(operationPortType);
			if (qParName.getNamespace().compare(qTypName.getNamespace()) == 0)
				qTypName.setPrefix(qParName.getPrefix());
			elemOpIn->addQualifiedAttribute("type", qTypName, schemaNode);
		}

		// Insert at the end to let stupid parsers get all types
		elemOpIn->addNode();
	}
}

void DPWS11WSDLBuilder::addTypesNode(XMLEntity * parent, const std::string & targetNamespace, const OperationVector & operations) const {

	XMLEntity * typesSchema = parent->appendChild("wsdl:types")
			->appendChild("xs:schema")
			->addAttribute("targetNamespace", targetNamespace)
			->addAttribute("elementFormDefault", "qualified")
			->addAttribute("attributeFormDefault", "unqualified");

	for (OperationVector::const_iterator opsIt = operations.begin(); opsIt != operations.end(); ++opsIt) {
		std::shared_ptr<Operation> op(*opsIt);
		const std::string opName(op->getName());
		addWSDLOperationParameters(typesSchema, op->getInput(), opName, op->getPortType());
		addWSDLOperationParameters(typesSchema, op->getOutput(), opName + "Out", op->getPortType());
	}
}

void DPWS11WSDLBuilder::addHeaderInformation(XMLEntity * parent, const std::string & targetNamespace) const{
	parent->setName("wsdl:definitions")
		->addAttribute("targetNamespace", targetNamespace)
		->addAttribute("xmlns", "http://schemas.xmlsoap.org/wsdl/")
		->addNamespace("tns", targetNamespace)
		->addNamespace("wsdl", WS_MEX_DIALECT_WSDL)
		->addNamespace("s12", WS_NS_SOAP_ENVELOPE)
		->addNamespace("xs", WS_NS_WSDL_XML_SCHEMA)
		->addNamespace("wsa", WS_NS_ADDRESSING)
		->addNamespace("wse", WS_NS_EVENTING)
		->addNamespace("soap", WS_NS_WSDL_SOAP12_SCHEMA);
}

void DPWS11WSDLBuilder::createWSDL(const DPWS11Message & msg, const Service & service, XMLEntity * parent, const std::string & targetNamespace) const
{
	// Collect all operations according to their namespaces
	OperationVector nsOperations = getOperationsByNamespace(service.getOperations(), targetNamespace);

	// Process all operations with respect to requested namespace
	if (nsOperations.size() == 0) {
		Util::DebugOut(Util::DebugOut::Error, "DPWS11WSDLBuilder") << "Requested target namespace not found.";
		return;
	}

	addHeaderInformation(parent, targetNamespace);
	addTypesNode(parent, targetNamespace, nsOperations);
	addPortTypeNodes(parent, nsOperations);
	addBindingNodes(parent, nsOperations);
	addServiceNode(msg, service, parent, nsOperations);
}

void DPWS11WSDLBuilder::addPortTypeNodes(XMLEntity * parent, const OperationVector & operations) const
{
	// Map local port type name -> port type XML tag
	std::map<std::string, XMLEntity*> portTypes;

	// Prepare port type(s) (WSDL 1.1)
	for (OperationVector::const_iterator opsIt = operations.begin(); opsIt != operations.end(); ++opsIt)
	{
		const std::string localPart((*opsIt)->getPortType().getLocal());
		if (portTypes.find(localPart) == portTypes.end())
		{
			// Create port type tag, but add it later
			XMLEntity* wsdlPortType = parent->appendChild("wsdl:portType", true);
			wsdlPortType->addAttribute("name", localPart);
			if ((*opsIt)->getInternalType() == Operation::EVENT_SOURCE) {
				wsdlPortType->addAttribute("wse:EventSource", "true");
			}
			// Store in map
			portTypes[localPart] = wsdlPortType;
		}
	}

	bool hasEventSources = false;

	for (OperationVector::const_iterator opsIt = operations.begin(); opsIt != operations.end(); ++opsIt)
	{
		if ((*opsIt)->getInternalType() == Operation::EVENT_SOURCE) {
			hasEventSources = true;
		}
	}

	// Process operations with respect to port types
	for (OperationVector::const_iterator nsOpsIt = operations.begin(); nsOpsIt != operations.end(); ++nsOpsIt)
	{
		const Operation & op = **nsOpsIt;
		const std::string opName(op.getName());
		const std::string typeName(op.getPortType().getLocal());
		// Add operation to the right port type (WSDL 1.1)
		XMLEntity * portOp = portTypes[typeName]->appendChild("wsdl:operation");
		portOp->addAttribute("name", op.getName());

		XMLEntity * opInputXml = nullptr;
		XMLEntity * opOutputXml = nullptr;

		const Parameters & pInp = op.getInput();
		if (pInp.size() > 0 || !hasEventSources) {
			QName elementName;
			if (pInp.size() == 1)
				elementName = pInp.at(0).getFinalQualifiedParameterName(op.getPortType());
			else if (pInp.size() > 1)
			{
				elementName.setPrefix("tns");
				elementName.setLocal(opName);
				elementName.setNamespace(op.getPortType().getNamespace());
			}
			// Input operation message and part (WSDL 1.1)
			bool response = op.getInternalType() == Operation::EVENT_SOURCE;
			const std::string msgNameIn(addWSDLMessage(parent, elementName, op, response));
			// And operation's input message (port type, WSDL 1.1)
			opInputXml = addWSDLOperationMessage(portOp, msgNameIn, op, false);
		}

		const Parameters & pOut = op.getOutput();
		if (pOut.size() > 0) {
			QName elementName;
			if (pOut.size() == 1)
				elementName = pOut.at(0).getFinalQualifiedParameterName(op.getPortType());
			else if (pOut.size() > 1)
			{
				elementName.setPrefix("tns");
				elementName.setLocal(opName + "Out");
				elementName.setNamespace(op.getPortType().getNamespace());
			}
			// Output operation message and part (WSDL 1.1)
			bool response = op.getInternalType() == Operation::DEFAULT;
			const std::string msgNameOut(addWSDLMessage(parent, elementName, op, response));
			// And operation's output message (port type, WSDL 1.1)
			opOutputXml = addWSDLOperationMessage(portOp, msgNameOut, op, true);
		}

		// Get the right order (event source means output first)
		if (hasEventSources) {
			if (opOutputXml != nullptr)
				opOutputXml->addNode();
			if (opInputXml != nullptr)
				opInputXml->addNode();
		} else {
			if (opInputXml != nullptr)
				opInputXml->addNode();
			if (opOutputXml != nullptr)
				opOutputXml->addNode();
		}
	}

	// Add port type
	for (std::map<std::string, XMLEntity*>::iterator typesIt = portTypes.begin(); typesIt != portTypes.end(); ++typesIt)
		typesIt->second->addNode();
}

} /* namespace DPWS */
} /* namespace Comm */
} /* namespace OSCLib */
