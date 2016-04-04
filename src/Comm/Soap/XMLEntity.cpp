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
 *  @file XMLEntity.cpp
 *  @project OSCLib
 *  @date 08.07.2011
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 */

#include "OSCLib/Comm/Soap/XMLEntity.h"
#include "OSCLib/Data/QName.h"
#include "OSCLib/Dependencies/rapidxml/rapidxml_print.hpp"

using namespace rapidxml;
using namespace OSCLib::Data;

namespace OSCLib {
namespace Comm {
namespace Soap {

XMLEntity::XMLEntity() : xmlParseBuf(1), docOwner(true), parent(nullptr) {
	doc = new xml_document<>;
	xml_node<>* decl = doc->allocate_node(node_declaration);
	decl->append_attribute(doc->allocate_attribute("version", "1.0"));
	decl->append_attribute(doc->allocate_attribute("encoding", "UTF-8"));
	doc->append_node(decl);
	node = doc->allocate_node(node_element);
	doc->append_node(node);
}

XMLEntity::XMLEntity(const XMLEntity & e) : xmlParseBuf(1), docOwner(true), parent(nullptr) {
    doc = new xml_document<>;
    std::string xmlString = e.toString();
    xmlParseBuf.resize(xmlString.size() + 1, false);
    xmlString.copy(xmlParseBuf.begin(), xmlString.size(), 0);
    xmlParseBuf[xmlString.size()] = '\0';
    doc->parse<0>(xmlParseBuf.begin());
    node = doc->first_node();
}

XMLEntity::XMLEntity(rapidxml::xml_node<>* newNodeValue)
    : xmlParseBuf(1), docOwner(false), doc(nullptr), node(newNodeValue), parent(nullptr)
{
    initDoc(newNodeValue);
}

XMLEntity::XMLEntity(XMLEntity * parent, const std::string & nodeName, bool addLater)
    : xmlParseBuf(1), docOwner(false), doc(nullptr), parent(parent)
{
	node = getDoc()->allocate_node(node_element);
	if (!addLater) {
		addNode();
	}
	setName(nodeName);
}

XMLEntity::~XMLEntity() {
	if (docOwner) {
		delete doc;
	}
}

void XMLEntity::addNode() {
	parent->getNode()->append_node(node);
}

std::string XMLEntity::toString(int flags) const {
	std::string xmlStr;
	print(std::back_inserter(xmlStr), *node, flags);
	return xmlStr;
}

XMLEntity * XMLEntity::setName(const std::string & name) {
	if (name.compare("") != 0) {
		char * newName = getDoc()->allocate_string(name.c_str());
		node->name(newName);
	}
	return this;
}

XMLEntity * XMLEntity::setValue(const std::string & value) {
	char * newVal = getDoc()->allocate_string(value.c_str());
	node->value(newVal);
	return this;
}

XMLEntity * XMLEntity::addAttribute(const std::string & key, const std::string & value) {
	char * newKey = getDoc()->allocate_string(key.c_str());
	char * newVal = getDoc()->allocate_string(value.c_str());
	node->append_attribute(getDoc()->allocate_attribute(newKey, newVal));
	return this;
}

std::string XMLEntity::getQualifiedInvariantAttributeValue(const std::string & key) {
	xml_attribute<> * attr = node->first_attribute(key.c_str());
	if (attr != nullptr) 	{
		return stripNsPrefix(attr->value());
	}
	for (attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
		std::string attrName = stripNsPrefix(std::string(attr->name()));
		if (attrName.compare(key) == 0) 		{
			return stripNsPrefix(attr->value());
		}
	}
	return "";
}

std::string XMLEntity::stripNsPrefix(const std::string & input) const {
	size_t posPref = input.find(':');
	if (posPref != std::string::npos)
		return input.substr(posPref + 1);
	else
		return input;
}

XMLEntity * XMLEntity::addQualifiedAttribute(const std::string & key, const OSCLib::Data::QName & val, XMLEntity * nsTarget) {
	QName keyName = QName(key, "", "");
	return addQualifiedAttribute(keyName, val, nsTarget);
}

XMLEntity * XMLEntity::addQualifiedAttribute(const OSCLib::Data::QName & key, const std::string & val, XMLEntity * nsTarget) {
	QName valName = QName(val, "", "");
	return addQualifiedAttribute(key, valName, nsTarget);
}

XMLEntity * XMLEntity::addQualifiedAttribute(const OSCLib::Data::QName & key, const OSCLib::Data::QName & val, XMLEntity * nsTarget) {
	std::string keySep = key.getPrefix().length() == 0? "" :  ":";
	std::string valSep = val.getPrefix().length() == 0? "" :  ":";
	char * newKey = getDoc()->allocate_string(std::string(key.getPrefix() + keySep + key.getLocal()).c_str());
	char * newVal = getDoc()->allocate_string(std::string(val.getPrefix() + valSep + val.getLocal()).c_str());
	node->append_attribute(getDoc()->allocate_attribute(newKey, newVal));
	if (nsTarget != 0) {
		bool nsKeyFound = (key.getNamespace().length() == 0);
		bool nsValFound = (val.getNamespace().length() == 0);
		for (xml_attribute<> * attr = nsTarget->getNode()->first_attribute();
			attr; attr = attr->next_attribute()) {
			std::string attrName(attr->name());
			if (attrName.find("xmlns:") != std::string::npos) {
				std::string ns(attr->value());
				std::string pr(stripNsPrefix(attrName));
				if (ns.compare(val.getNamespace()) == 0 && pr.compare(val.getPrefix()) == 0) {
					nsValFound = true;
				}
				if (ns.compare(key.getNamespace()) == 0 && pr.compare(key.getPrefix()) == 0) {
					nsKeyFound = true;
				}
			}
		}
		if (!nsValFound) {
			nsTarget->addNamespace(val.getPrefix(), val.getNamespace());
		}
		if (!nsKeyFound) {
			nsTarget->addNamespace(key.getPrefix(), key.getNamespace());
		}
	}
	return this;
}

XMLEntity * XMLEntity::addTextNode(const std::string & name, const std::string & text) {
	char * newName = getDoc()->allocate_string(name.c_str());
	char * newText = text.compare("") != 0? getDoc()->allocate_string(text.c_str()) : 0;
	xml_node<>* n = getDoc()->allocate_node(node_element, newName, newText);
	getNode()->append_node(n);
	std::shared_ptr<XMLEntity> ret(new XMLEntity(n));
	refs.push_back(ret);
	return ret.get();
}

rapidxml::xml_node<> * XMLEntity::getNode() const {
	return node;
}

XMLEntity * XMLEntity::getParent() const {
	return parent;
}

rapidxml::xml_document<> * XMLEntity::getDoc() const {
	const XMLEntity * p = this;
	while (p->parent != nullptr)
		p = p->parent;
	return p->doc;
}

XMLEntity * XMLEntity::addNamespace(const std::string & prefix, const std::string & nameSpace) {
	this->addAttribute("xmlns:" + prefix, nameSpace);
	return this;
}

XMLEntity * XMLEntity::appendChild(const std::string & childName, bool addLater) {
	std::shared_ptr<XMLEntity> ret(new XMLEntity(this, childName, addLater));
	refs.push_back(ret);
	return ret.get();
}

void XMLEntity::initDoc(rapidxml::xml_node<> * node) const {
	if (docOwner) {
		delete doc;
	}
    doc = node->document();
}

} /* namespace Soap */
} /* namespace Comm */
} /* namespace OSCLib */
