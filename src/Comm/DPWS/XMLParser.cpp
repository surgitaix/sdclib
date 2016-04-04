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
 * XMLParser.cpp
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: besting, roehser
 */

#include "OSCLib/Comm/DPWS/XMLParser.h"
#include "OSCLib/Util/DebugOut.h"

namespace OSCLib {
namespace Comm {
namespace DPWS {

XMLParser::XMLParser() {
}

XMLParser::~XMLParser() {

}

bool XMLParser::assertChildExists(const std::string & childFullName, rapidxml::xml_node<>* parent, bool showErrorMessage) {

	if (parent == nullptr) {
		return false;
	}

	rapidxml::xml_node<> * child = parent->first_node(childFullName.c_str());

	if (child == nullptr) {
		if (showErrorMessage) {
			Util::DebugOut(Util::DebugOut::Error, "XMLParser") << "Child node missing '" << childFullName <<"' of parent node '" << parent->name() << "'";
		}
		return false;
	} else {
		return true;
	}
}

bool XMLParser::assertChildExists(const std::string & nameSpace, const std::string & nodeName, rapidxml::xml_node<>* parent, bool showErrorMessage) {
	return assertChildExists(getQNameString(nameSpace, nodeName), parent, showErrorMessage);
}

std::string XMLParser::getChildValueByQName(const std::string & nameSpace, const std::string & nodeName, rapidxml::xml_node<>* parent, bool requiredNode) {

	if (parent == nullptr) {
		return "";
	}

	rapidxml::xml_node<> * child = getChildByQName(nameSpace, nodeName, parent, requiredNode);

	if (child != nullptr) {
		return std::string(child->value());
	} else {
		return "";
	}
}

rapidxml::xml_node<>* XMLParser::getChildByQName(const std::string & nameSpace, const std::string & nodeName, rapidxml::xml_node<>* parent, bool requiredNode) {
	if (parent == nullptr) {
		return nullptr;
	}

	rapidxml::xml_node<> * child = parent->first_node(getQNameString(nameSpace, nodeName).c_str());

	if (child == nullptr && requiredNode) {
		Util::DebugOut(Util::DebugOut::Error, "XMLParser") << "Child node missing '" << nodeName <<"' of parent node '" << parent->name() << "'";
	}

	return child;
}

rapidxml::xml_node<>* XMLParser::getSiblingByQName(const std::string & nameSpace, const std::string & nodeName, rapidxml::xml_node<>* parent, bool requiredNode) {
	if (parent == nullptr) {
		return nullptr;
	}

	rapidxml::xml_node<> * sibling = parent->next_sibling(getQNameString(nameSpace, nodeName).c_str());

	if (sibling == nullptr && requiredNode) {
		Util::DebugOut(Util::DebugOut::Error, "XMLParser") << "Sibling node missing '" << nodeName <<"' of parent node '" << parent->name() << "'";
	}

	return sibling;
}

void XMLParser::parseNamespaces(rapidxml::xml_node<> * node)
{
	for (rapidxml::xml_attribute<>* attr = node->first_attribute();
		 attr; attr = attr->next_attribute())
	{
		std::string attrStr(attr->name());
		std::string attrSuf;
		size_t pos = attrStr.find(":");
		if (pos != std::string::npos)
			attrSuf = attrStr.substr(pos + 1);
		nsMap[attr->value()] = attrSuf;
	}
}

const Util::StringMap & XMLParser::getNsMap() {
	return nsMap;
}

void XMLParser::setNsMap(const Util::StringMap & newNsMap) {
	this->nsMap.clear();
	this->nsMap.insert(newNsMap.begin(), newNsMap.end());
}

std::string XMLParser::getQNameString(const std::string & nameSpace, const std::string & nodeName) {
	return nsMap[nameSpace] + ":" + nodeName;
}

} /* namespace DPWS */
} /* namespace Comm */
} /* namespace OSCLib */
