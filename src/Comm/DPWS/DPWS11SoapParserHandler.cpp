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
 * DPWS11SoapParserHandler.cpp
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: besting, roehser
 */

#include "OSCLib/Comm/DPWS/DPWS11SoapParserHandler.h"
#include "OSCLib/Comm/DPWS/DPWS11Message.h"
#include "OSCLib/Comm/DPWS/DPWS11Constants.h"
#include "OSCLib/Util/TypeConversion.h"
#include "OSCLib/Comm/DPWS/XMLParser.h"

using namespace rapidxml;

namespace OSCLib {
namespace Comm {
namespace DPWS {
    
Data::QVector DPWS11SoapParserHandler::typesNodeToVector(xml_node<>* node)
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
    
Dev::EndpointReference DPWS11SoapParserHandler::parseEndpointReference(XMLParser * parser, rapidxml::xml_node<>* parent)
{
	xml_node<>* nodeEpr = parent;

	Dev::EndpointReference epr;
	if (nodeEpr == nullptr) {
		return epr;
	}

	const std::string address(parser->getChildValueByQName(WS_NS_ADDRESSING, "Address", nodeEpr, true));
	epr.setAddress(address);

	xml_node<>* nodeRef = parser->getChildByQName(WS_NS_ADDRESSING, "ReferenceParameters", nodeEpr);
	if (nodeRef != nullptr) {
		epr.setReferenceParameters(parser->getChildValueByQName(WS_NS_EVENTING, "Identifier", nodeRef));
	}

	return epr;
}

DPWS11SoapParserHandler::DPWS11SoapParserHandler() {

}

DPWS11SoapParserHandler::~DPWS11SoapParserHandler() {

}

} /* namespace DPWS */
} /* namespace Comm */
} /* namespace OSCLib */
