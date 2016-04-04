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
 * DPWS11MetadataSoapParserHandler.cpp
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: besting, roehser
 */

#ifndef DPWS11METADATASOAPPARSERHANDLER_H_
#define DPWS11METADATASOAPPARSERHANDLER_H_

#include "OSCLib/Comm/DPWS/DPWS11SoapParserHandler.h"

namespace OSCLib {
namespace Comm {
namespace DPWS {

class DPWS11MetadataSoapParserHandler : public DPWS11SoapParserHandler {
public:
	DPWS11MetadataSoapParserHandler();
	virtual ~DPWS11MetadataSoapParserHandler();
    
    void parseMetadata(XMLParser * parser, DPWS11Message * dpws11msg, rapidxml::xml_node<>* nodeMeta, const std::string & dialect);

	void parseMetadataDialectDevice(XMLParser * parser, DPWS11Message * dpws11msg, rapidxml::xml_node<>* nodeMeta);
	void parseMetadataDialectModel(XMLParser * parser, DPWS11Message * dpws11msg, rapidxml::xml_node<>* nodeMeta);
	void parseMetadataDialectRelationship(XMLParser * parser, DPWS11Message * dpws11msg, rapidxml::xml_node<>* nodeMeta);
	void parseMetadataDialectWSDL(XMLParser * parser, DPWS11Message * dpws11msg, rapidxml::xml_node<>* nodeMeta);
    void parseMetadataDialectStream(XMLParser * parser, rapidxml::xml_node<>* nodeMeta);

	bool parseBody(XMLParser * parser, DPWS11Message * dpws11msg, rapidxml::xml_node<>* nodeBody);
    
    std::vector<std::string> getStreamingPeriods() const;
    std::vector<std::string> getStreamingAddresses() const;

private:
    std::vector<std::string> streamingAddresses;
    std::vector<std::string> streamingPeriods;
};

} /* namespace DPWS */
} /* namespace Comm */
} /* namespace OSCLib */
#endif /* DPWS11METADATASOAPPARSERHANDLER_H_ */
