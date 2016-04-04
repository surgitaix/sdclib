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
 *  @file Parameter.cpp
 *  @project OSCLib
 *  @date 04.01.2012
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 */

#include "OSCLib/Comm/Soap/XMLEntity.h"
#include "OSCLib/Data/Operation.h"
#include "OSCLib/Data/Parameter.h"
#include "OSCLib/Dependencies/rapidxml/rapidxml.hpp"
#include "OSCLib/Util/TypeConversion.h"

#include <stdexcept>
#include <stdio.h>

namespace OSCLib {
namespace Data {

using namespace rapidxml;

void Parameter::init()
{
	minOccurs = 1;
	maxOccurs = 1;
	compositor = Compositor::SEQUENCE;
	valueSet = false;
}

Parameter::Parameter() : type(Type::ANY)
{
	init();
}

Parameter::Parameter(const std::string & name) : type(Type::ANY)
{
	init();
	this->name.setLocal(name);
}

Parameter::Parameter(const QName & name) : name(name), type(Type::ANY)
{
	init();
}

Parameter::Parameter(const std::string & name, Type type) : type(type)
{
	init();
	this->name.setLocal(name);
}

Parameter::Parameter(const QName & name, Type type) : name(name), type(type)
{
	init();
}

Parameter::Parameter(const std::string & name, Type type, const std::string & value) : type(type), value(value)
{
	init();
	this->name.setLocal(name);
}

Parameter::Parameter(const QName & name, Type type, const std::string & value) : name(name), type(type), value(value)
{
	init();
}

Parameter::Parameter(const std::string & name, const QName & customType) : customType(customType), type(Type::ANY)
{
	init();
	this->name.setLocal(name);
}

Parameter::Parameter(const QName & name, const QName & customType) : name(name), customType(customType), type(Type::ANY)
{
	init();
}

Parameter::~Parameter()
{
}

Parameter::Compositor Parameter::getCompositor() const {
	return compositor;
}

std::string Parameter::getCompositorAsString() const {
	switch (getCompositor()) {
		case Compositor::ALL: return "all"; break;
		case Compositor::SEQUENCE: return "sequence"; break;
		case Compositor::CHOICE: return "choice"; break;
	}
	return "";
}

Parameter & Parameter::setCompositor(Compositor compositor)
{
	this->compositor = compositor;
	return *this;
}

const std::string & Parameter::getName() const
{
	return name.getLocal();
}

Parameter::Type Parameter::getType() const
{
	return type;
}

Parameter & Parameter::setType(Type type)
{
	this->type = type;
	return *this;
}

const std::string & Parameter::getValue() const
{
	return value;
}

Parameter & Parameter::setValue(const std::string & value)
{
	this->value = value;
	valueSet = true;
	return *this;
}

std::vector<Parameter> Parameter::getCopyChildren() const {
	std::vector<Parameter> v;
	v.reserve(children.size());
	for (const auto & child : children) {
		v.emplace_back(*child);
	}
    return v;
}

void Parameter::addToNodeSelf(Comm::Soap::XMLEntity * node, const QName & qBaseName) const {
	const QName qPrmName(getFinalQualifiedParameterName(qBaseName));
	const QName qTypName(getFinalQualifiedParameterTypeName(qBaseName));

	node->setName(qPrmName.getPrefixedName());
	node->setValue(value);
	node->addAttribute("xsi:type", qTypName.getPrefixedName());

	// Add namespaces if prefix doesn't match
	if (qBaseName.getPrefix().compare(qPrmName.getPrefix()) != 0)
		node->addAttribute("xmlns:" + qPrmName.getPrefix(), qPrmName.getNamespace());
	if (qBaseName.getPrefix().compare(qTypName.getPrefix()) != 0 && qTypName.getPrefix().compare("xs") != 0)
		node->addAttribute("xmlns:" + qTypName.getPrefix(), qTypName.getNamespace());
}

void Parameter::addToNodeChildren(Comm::Soap::XMLEntity * node, const QName & qBaseName) const {
	for (const auto &nextParam : children) {
		nextParam->addToNode(node, qBaseName);
	}
}

void Parameter::addToNodeSiblings(Comm::Soap::XMLEntity * node, const QName & qBaseName) const {
	for (const auto & nextParam : siblings) {
		Comm::Soap::XMLEntity * sibling = node->appendChild("");
		nextParam->addToNodeSelf(sibling, qBaseName);
		nextParam->addToNodeChildren(sibling, qBaseName);
	}
}

void Parameter::addToNode(Comm::Soap::XMLEntity * node, const QName & qBaseName) const {
	Comm::Soap::XMLEntity * param = node->appendChild("");
	addToNodeSelf(param, qBaseName);
	addToNodeSiblings(node, qBaseName);
	addToNodeChildren(param, qBaseName);
}

void Parameter::createFromNode(rapidxml::xml_node<>* node) {
	const std::string nodeName(node->name());
	const std::string paramValue(node->value());
	const size_t pos(nodeName.find(":"));
	if (pos != std::string::npos)
		name.setLocal(nodeName.substr(pos + 1));
	else
		name.setLocal(nodeName);

	setValue(paramValue);

	xml_node<>* nextParamNode = node->first_node();

	// Create structure if children available
	while (nextParamNode != nullptr) {

		// Create next
		std::shared_ptr<Parameter> nextParam(new Parameter());
		nextParam->createFromNode(nextParamNode);

		// Check if sibling available
		std::shared_ptr<Parameter> sib(getChild(nextParam->getName()));
		if (sib != nullptr) {
			// Add sibling
			sib->siblings.push_back(nextParam);
		}
		else {
			// Add child
			children.push_back(nextParam);
		}

		nextParamNode = nextParamNode->next_sibling();
	}

}

Parameter & Parameter::operator[](const std::string & path) {
	const Util::StringVector tokens(Util::splitString(path, '.'));
	Parameter * current = this;

	for (auto token : tokens) {
		// Check for sibling index
		int index = -1;
		std::string::size_type parenthesesBegin(token.find("("));
		std::string::size_type parenthesesEnd(token.find(")"));
		if (parenthesesBegin != std::string::npos && parenthesesEnd != std::string::npos)
		{
			index = atoi(token.substr(parenthesesBegin + 1, parenthesesEnd - parenthesesBegin).c_str());
			token = token.substr(0, parenthesesBegin);
		}

		// Get child
		std::shared_ptr<Parameter> next(current->getChild(token));
		if (next != nullptr)
		{
			current = next.get();
		}
		else
		{
			// Create child
			next = std::shared_ptr<Parameter>(new Parameter(token));
			current->children.push_back(next);
			current = next.get();
		}
		if (index >= 0)
		{
			// Get sibling
			if (index > signed(current->siblings.size()))
				throw std::runtime_error("Parameter out of bounds!");
			else if (index == signed(current->siblings.size()))
			{
				// Create sibling
				next = std::shared_ptr<Parameter>(new Parameter(token));
				current->siblings.push_back(next);
				current = next.get();
			}
			else
			{
				current = current->siblings[index].get();
			}
		}
	}
	return *current;
}

int Parameter::getMaxOccurs() const
{
	return maxOccurs;
}

int Parameter::getMinOccurs() const
{
	return minOccurs;
}

Parameter& Parameter::setMaxOccurs(int maxOccurs)
{
	this->maxOccurs = maxOccurs;
	return *this;
}

Parameter& Parameter::setMinOccurs(int minOccurs)
{
	this->minOccurs = minOccurs;
	return *this;
}

bool Parameter::isValueSet() const
{
	return valueSet;
}

void Parameter::setValueSet(bool valueSet)
{
	this->valueSet = valueSet;
}

std::shared_ptr<Parameter> Parameter::getChild(const std::string & name) {
	for(auto & child : children) {
		if(name == child->getName()) {
			return child;
		}
	}
	return nullptr;
}

QName Parameter::getFinalQualifiedParameterTypeName(const QName & operationPortType) const {
	const QName customType(updateParameterTypeNamespaceIfNeededFrom(operationPortType));
	if (customType.getLocal().empty()) {
		return QName(getSimpleTypeName(), "http://www.w3.org/2001/XMLSchema", "xs");
	} else {
		return customType;
	}
}

QName Parameter::getFinalQualifiedParameterName(const QName& operationPortType) const {
	return updateParameterNameNamespaceIfNeededFrom(operationPortType);
}

Parameter & Parameter::setQualifiedName(const QName& name) {
	this->name = name;
	return *this;
}

QName Parameter::updateParameterNameNamespaceIfNeededFrom(const QName & qName) const {
	if (name.getNamespace().empty()) {
		return QName(name.getLocal(), qName.getNamespace(), qName.getPrefix());
	} else {
		return name;
	}
}

QName Parameter::updateParameterTypeNamespaceIfNeededFrom(const QName & qName) const {
	if (customType.getLocal().length() > 0 && customType.getNamespace().empty()) {
		return QName(customType.getLocal(), qName.getNamespace(), qName.getPrefix());
	} else {
		return customType;
	}
}

const QName & Parameter::getQualifiedName() const {
	return name;
}

std::string Parameter::getSimpleTypeName() const {
	switch (type) {
		case Type::STRING:
			return "string";
			break;
		case Type::BASE64:
			return "base64Binary";
			break;
		case Type::LONG:
			return "long";
			break;
		case Type::UNSIGNED_LONG:
			return "unsignedLong";
			break;
		case Type::INT:
			return "int";
			break;
		case Type::UNSIGNED_INT:
			return "unsignedInt";
			break;
		case Type::SHORT:
			return "short";
			break;
		case Type::UNSIGNED_SHORT:
			return "unsignedShort";
			break;
		case Type::BYTE:
			return "byte";
			break;
		case Type::UNSIGNED_BYTE:
			return "unsignedByte";
			break;
		case Type::DECIMAL:
			return "decimal";
			break;
		case Type::FLOAT:
			return "float";
			break;
		case Type::DOUBLE:
			return "double";
			break;
		case Type::BOOLEAN:
			return "boolean";
			break;
		case Type::DURATION:
			return "duration";
			break;
		case Type::DATETIME:
			return "dateTime";
			break;
		case Type::DATE:
			return "date";
			break;
		case Type::TIME:
			return "time";
			break;
		case Type::COMPLEX:
			return getName() + "Type";
			break;
		case Type::ANY:
			return getName() + "Type";
			break;
        case Type::CDM:
        	return "cdm";
            break;
        case Type::ERR:
        	return "ERROR";
			break;
	}
	return "";
}

bool Parameter::hasChildren() const {
    return children.size() > 0;
}

bool Parameter::hasSiblings() const {
    return siblings.size() > 0;
}

size_t Parameter::getChildCount() const {
	return children.size();
}

size_t Parameter::getSiblingCount() const {
	return siblings.size();
}

Parameter & Parameter::setCustomTypeName(const std::string & customType) {
	this->customType.setLocal(customType);
	return *this;
}

Parameter & Parameter::setCustomType(const QName & customType) {
	this->customType = customType;
	return *this;
}

const std::string & Parameter::getCustomTypeName() const {
	return customType.getLocal();
}

const QName & Parameter::getCustomType() const {
	return customType;
}

void Parameter::addChild(const Parameter& childParam) {
	children.push_back(std::make_shared<Parameter>(childParam));
}

bool Parameter::hasValue() const {
	return value.length() > 0;
}

} /* namespace Data */
} /* namespace OSCLib */
