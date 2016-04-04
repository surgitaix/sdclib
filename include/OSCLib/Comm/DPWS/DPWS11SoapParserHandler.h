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

#ifndef DPWS11SOAPPARSERHANDLER_H_
#define DPWS11SOAPPARSERHANDLER_H_

#include "OSCLib/Dependencies/rapidxml/rapidxml.hpp"
#include "OSCLib/Dev/EndpointReference.h"
#include "OSCLib/Data/QName.h"

namespace OSCLib {
namespace Comm {
namespace DPWS {

class DPWS11Message;    
class XMLParser;
    
class DPWS11SoapParserHandler {
public:
	DPWS11SoapParserHandler();
	virtual ~DPWS11SoapParserHandler();

    Data::QVector typesNodeToVector(rapidxml::xml_node<> *node);
    Dev::EndpointReference parseEndpointReference(XMLParser * parser, rapidxml::xml_node<>* node);
	virtual bool parseBody(XMLParser * parser, DPWS11Message * dpws11msg, rapidxml::xml_node<> * nodeBody) = 0;

};

} /* namespace DPWS */
} /* namespace Comm */
} /* namespace OSCLib */
#endif /* DPWS11SOAPPARSERHANDLER_H_ */
