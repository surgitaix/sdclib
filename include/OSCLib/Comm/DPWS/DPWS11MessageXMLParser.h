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
 * DPWS11MessageXMLParser.h
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: besting, roehser
 */

#ifndef DPWS11MESSAGEXMLPARSER_H_
#define DPWS11MESSAGEXMLPARSER_H_

#include "OSCLib/Comm/DPWS/XMLParser.h"
#include "OSCLib/Data/QName.h"
#include "OSCLib/Dependencies/rapidxml/rapidxml.hpp"
#include "OSCLib/Dev/EndpointReference.h"
#include "OSCLib/Util/StringVector.h"

#include "Poco/Buffer.h"
#include <map>
#include <memory>

namespace OSCLib {
namespace Comm {
namespace DPWS {

class DPWS11Message;
class DPWS11SoapParserHandler;

class DPWS11MessageXMLParser : public XMLParser {
public:
	DPWS11MessageXMLParser();
	virtual ~DPWS11MessageXMLParser();

	Dev::EndpointReference parseEndpointReference(rapidxml::xml_node<>* node);

	void parseSubscribe(DPWS11Message * dpws11msg, rapidxml::xml_node<>* nodeBody);
	void parseSubscribeResponse(DPWS11Message * dpws11msg, rapidxml::xml_node<>* nodeBody);
	void parseRenew(DPWS11Message * dpws11msg, rapidxml::xml_node<>* nodeHeader, rapidxml::xml_node<>* nodeBody);
	void parseUnsubscribe(DPWS11Message * dpws11msg, rapidxml::xml_node<>* nodeHeader);
	void parseProbe(DPWS11Message * dpws11msg, rapidxml::xml_node<>* nodeBody);

	void parseBasicDiscovery(DPWS11Message * dpws11msg, rapidxml::xml_node<>* probeMatches);
	void parseResolve(DPWS11Message * dpws11msg, rapidxml::xml_node<>* nodeBody);

	bool parse(DPWS11Message * dpws11msg, const std::string& str, const Util::StringVector & customActions);

	bool parseHtmlInfo(DPWS11Message * dpws11msg, rapidxml::xml_node<> * root);

	Data::QVector typesNodeToVector(rapidxml::xml_node<> *node);

    void parseParameters(DPWS11Message * dpws11msg, rapidxml::xml_node<>* nodeBody);

    void registerParseHandler(std::string action, std::shared_ptr<DPWS11SoapParserHandler> handler);
    std::shared_ptr<DPWS11SoapParserHandler> getParseHandler(std::string action);

private:

	Poco::Buffer<char> xmlParseBuf;

    std::shared_ptr<rapidxml::xml_document<>> doc;

    bool parseSOAP(DPWS11Message * dpws11msg, rapidxml::xml_node<>* root, const Util::StringVector & customActions);
    bool parseSOAPHeader(DPWS11Message * dpws11msg, rapidxml::xml_node<>* header);
    bool parseSOAPBody(DPWS11Message * dpws11msg, rapidxml::xml_node<>* header, rapidxml::xml_node<>* body, const Util::StringVector & customActions);

    std::map<std::string, std::shared_ptr<DPWS11SoapParserHandler>> parseHandlers;

};

} /* namespace DPWS */
} /* namespace Comm */
} /* namespace OSCLib */
#endif /* DPWS11MESSAGEXMLPARSER_H_ */
