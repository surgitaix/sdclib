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
 * DPWS11WSDLParser.h
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: besting, roehser
 */

#ifndef DPWS11WSDLPARSER_H_
#define DPWS11WSDLPARSER_H_

#include <string>
#include "XMLParser.h"
#include "Poco/Buffer.h"

namespace OSCLib {
namespace Dev {
class Service;
}
namespace Comm {
namespace DPWS {

class DPWS11Message;

class DPWS11WSDLParser: public XMLParser {
public:
	DPWS11WSDLParser();
	virtual ~DPWS11WSDLParser();

	bool parseWSDL(const std::string & wsdlContent, const std::string & serviceAddr, std::vector<std::shared_ptr<Dev::Service>> remoteServices);

private:

	Poco::Buffer<char> xmlParseBuf;

    std::shared_ptr<rapidxml::xml_document<> > doc;

	Dev::Service * findRemoteServiceByServiceAddress(const std::string & serviceLoc, std::vector<std::shared_ptr<Dev::Service>> remoteServices);
	rapidxml::xml_node<>* getWSDLNodeByAttributeMatch(rapidxml::xml_node<>* wsdlNode, std::string nodeName, std::string attrName, std::string attrValue);
	rapidxml::xml_node<> * getPortTypeNode(rapidxml::xml_node<>* servicePortNode, rapidxml::xml_node<>* wsdlNode);
	std::string parseSoapAction(rapidxml::xml_node<>* actionNode);
	std::string stripNsPrefix(const std::string & input);
	void parseOperation(Dev::Service * service, rapidxml::xml_node<> * portTypeNode, const std::string & targetNamespace);
	bool parseServicePort(rapidxml::xml_node<> * servicePortNode, rapidxml::xml_node<>* wsdlNode, std::vector<std::shared_ptr<Dev::Service>> remoteServices);
};

} /* namespace DPWS */
} /* namespace Comm */
} /* namespace OSCLib */
#endif /* DPWS11WSDLPARSER_H_ */
