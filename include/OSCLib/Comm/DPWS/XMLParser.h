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
 * XMLParser.h
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: besting, roehser
 */

#ifndef XMLPARSER_H_
#define XMLPARSER_H_

#include "OSCLib/Dependencies/rapidxml/rapidxml.hpp"
#include "OSCLib/Util/StringMap.h"
#include "OSCLib/Util/StringVector.h"

namespace OSCLib {
namespace Comm {
namespace DPWS {

class XMLParser {
public:
	XMLParser();
	virtual ~XMLParser();

	void parseNamespaces(rapidxml::xml_node<>* node);

	const Util::StringMap & getNsMap();
	void setNsMap(const Util::StringMap & nsMap);

	bool assertChildExists(const std::string & childFullName, rapidxml::xml_node<>* parent, bool showErrorMessage = false);
	bool assertChildExists(const std::string & nameSpace, const std::string & nodeName, rapidxml::xml_node<>* parent, bool showErrorMessage = false);

    std::string getQNameString(const std::string & nameSpace, const std::string & nodeName);

    rapidxml::xml_node<>* getChildByQName(const std::string & nameSpace, const std::string & nodeName, rapidxml::xml_node<>* parent, bool requiredNode = false);
    rapidxml::xml_node<>* getSiblingByQName(const std::string & nameSpace, const std::string & nodeName, rapidxml::xml_node<>* parent, bool requiredNode = false);

    std::string getChildValueByQName(const std::string & nameSpace, const std::string & nodeName, rapidxml::xml_node<>* parent, bool debugOut = false);

protected:
    Util::StringMap nsMap;
};

} /* namespace DPWS */
} /* namespace Comm */
} /* namespace OSCLib */
#endif /* XMLPARSER_H_ */
