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

#include "OSCLib/Comm/DPWS/DPWS11MetadataSoapParserHandler.h"
#include "OSCLib/Comm/DPWS/DPWS11Message.h"
#include "OSCLib/Comm/DPWS/XMLParser.h"
#include "OSCLib/Comm/DPWS/DPWS11Constants.h"
#include "OSCLib/Data/OSCP/OSCPConstants.h"
#include "OSCLib/Dev/Service.h"
#include "OSCLib/Util/DebugOut.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "OSCLib/Comm/Binding.h"

using namespace rapidxml;

namespace OSCLib {
namespace Comm {
namespace DPWS {

DPWS11MetadataSoapParserHandler::DPWS11MetadataSoapParserHandler() {

}

DPWS11MetadataSoapParserHandler::~DPWS11MetadataSoapParserHandler() {

}

void DPWS11MetadataSoapParserHandler::parseMetadataDialectDevice(XMLParser * parser, DPWS11Message * dpws11msg, rapidxml::xml_node<>* nodeMeta) {
	Dev::DeviceCharacteristics & incDeviceCharacteristics = dpws11msg->getIncomingDeviceCharacteristics();
	xml_node<>* nodeDevice = nodeMeta->first_node();

	const std::string friendlyName(parser->getQNameString(WS_NS_DPWS, "FriendlyName"));
	for (xml_node<>* nextName = parser->getChildByQName(WS_NS_DPWS, "FriendlyName", nodeDevice);
		nextName; nextName = nextName->next_sibling(friendlyName.c_str()))
	{
		xml_attribute<>* attr = nextName->first_attribute("xml:lang");
		if (attr != nullptr)
			incDeviceCharacteristics.addFriendlyName(attr->value(), nextName->value());
	}

	incDeviceCharacteristics.setFirmwareVersion(parser->getChildValueByQName(WS_NS_DPWS, "FirmwareVersion", nodeDevice));
	incDeviceCharacteristics.setSerialNumber(parser->getChildValueByQName(WS_NS_DPWS, "SerialNumber", nodeDevice));
}

void DPWS11MetadataSoapParserHandler::parseMetadataDialectModel(XMLParser * parser, DPWS11Message * dpws11msg, rapidxml::xml_node<>* nodeMeta) {
	Dev::DeviceCharacteristics & incDeviceCharacteristics = dpws11msg->getIncomingDeviceCharacteristics();

	xml_node<>* nodeModel = nodeMeta->first_node();

	incDeviceCharacteristics.setManufacturer(parser->getChildValueByQName(WS_NS_DPWS, "Manufacturer", nodeModel));
	incDeviceCharacteristics.setManufacturerUrl(parser->getChildValueByQName(WS_NS_DPWS, "ManufacturerUrl", nodeModel));
	incDeviceCharacteristics.setModelNumber(parser->getChildValueByQName(WS_NS_DPWS, "ModelNumber", nodeModel));
	incDeviceCharacteristics.setModelUrl(parser->getChildValueByQName(WS_NS_DPWS, "ModelUrl", nodeModel));
	incDeviceCharacteristics.setPresentationUrl(parser->getChildValueByQName(WS_NS_DPWS, "PresentationUrl", nodeModel));

	const std::string modelName(parser->getQNameString(WS_NS_DPWS, "ModelName"));
	for (xml_node<>* nextName = nodeModel->first_node(modelName.c_str());
		nextName; nextName = nextName->next_sibling(modelName.c_str()))
	{
		xml_attribute<>* attr = nextName->first_attribute("xml:lang");
		if (attr != nullptr)
			incDeviceCharacteristics.addModelName(attr->value(), nextName->value());
	}
}

void DPWS11MetadataSoapParserHandler::parseMetadataDialectRelationship(XMLParser * parser, DPWS11Message * dpws11msg, rapidxml::xml_node<>* nodeMeta)
{

	const std::string relName(parser->getQNameString(WS_NS_DPWS, "Relationship"));

	for (xml_node<>* nextRel = nodeMeta->first_node(relName.c_str());
			nextRel; nextRel = nextRel->next_sibling(relName.c_str()))
	{
		const std::string hostedName(parser->getQNameString(WS_NS_DPWS, "Hosted"));

		for (xml_node<>* hostedNode = nextRel->first_node(hostedName.c_str());
				hostedNode; hostedNode = hostedNode->next_sibling(hostedName.c_str()))
		{
			if (hostedNode == nullptr)
				continue;

			std::shared_ptr<Dev::Service> hostedService(new Dev::Service());
			if (parser->assertChildExists(WS_NS_DPWS, "Types", hostedNode)) {
				xml_node<>* typesNode = parser->getChildByQName(WS_NS_DPWS, "Types", hostedNode);
				hostedService->addTypes(typesNodeToVector(typesNode));
			}

			if (parser->assertChildExists(WS_NS_DPWS, "ServiceId", hostedNode)) {
				const std::string remoteServiceId(parser->getChildValueByQName(WS_NS_DPWS, "ServiceId", hostedNode));
				hostedService->setServiceId(remoteServiceId);
			}

			/**
			 * Parse endpoint references.
			 * There might be several endpoint references for ipv6 and ipv4.
			 * However we currently support only ipv4 address.
             * If more than one ipv4 is present, we use the first one that punches trough.
			 */
			if (parser->assertChildExists(WS_NS_ADDRESSING, "EndpointReference", hostedNode)) {
				const std::string eprName(parser->getQNameString(WS_NS_ADDRESSING, "EndpointReference"));
				for (xml_node<>* eprNode = hostedNode->first_node(eprName.c_str());
						eprNode; eprNode = eprNode->next_sibling(eprName.c_str()))
				{
					Dev::EndpointReference eprAdr(parseEndpointReference(parser, eprNode));
					if (eprAdr.getAddress().find('[') == std::string::npos && eprAdr.getAddress().find(']') == std::string::npos) {
                        // Check if device is reachable using this xaddr
                        try{
                            Poco::Net::StreamSocket ss;
                            std::shared_ptr<Binding> eprBinding = std::make_shared<Binding>(eprAdr.getAddress());
                            Poco::Net::SocketAddress socketAdr(eprBinding->getIp(), eprBinding->getPort());
                            ss.connect(socketAdr, 500000);
                            // Found suitable connection (no exception)
                            hostedService->setEPRAddress(eprAdr.getAddress());
                            ss.close();
                            break;
                        }
                        catch (Poco::Exception&) {
                            // Don't use
                        }
					}
				}
			}

			dpws11msg->addHostedService(hostedService);
		}
	}
}

void DPWS11MetadataSoapParserHandler::parseMetadataDialectWSDL(XMLParser * parser, DPWS11Message * dpws11msg, rapidxml::xml_node<>* nodeMeta) {
	// WSDL location section contained in GetMetadataResponse
	xml_node<>* nodeLocation = parser->getChildByQName(WS_NS_METADATA_EXCHANGE, "Location", nodeMeta);
	if (nodeLocation != nullptr) {
		dpws11msg->addIncomingWSDLLocation(nodeLocation->value());
	}
}

void DPWS11MetadataSoapParserHandler::parseMetadataDialectStream(XMLParser * parser, rapidxml::xml_node<>* nodeMeta) {
	// Stream description node expected to be first node
	xml_node<>* nodeStreamDesr = nodeMeta->first_node();
    parser->parseNamespaces(nodeStreamDesr);
    
	xml_node<>* nodeStreamType = parser->getChildByQName(OSCLib::Data::OSCP::WS_MEX_ORNET_NS_STREAM, "streamType", nodeStreamDesr, true);
	if (nodeStreamType != nullptr) {
        streamingAddresses.clear();
        streamingPeriods.clear();
        for (auto nextTransNode = parser->getChildByQName(OSCLib::Data::OSCP::WS_MEX_ORNET_NS_STREAM, "StreamTransmission", nodeStreamType, true);
            nextTransNode; nextTransNode = nextTransNode->next_sibling())
        {
            xml_node<>* streamAddress = parser->getChildByQName(OSCLib::Data::OSCP::WS_MEX_ORNET_NS_STREAM, "streamAddress", nextTransNode, true);
            xml_node<>* streamPeriod = parser->getChildByQName(OSCLib::Data::OSCP::WS_MEX_ORNET_NS_STREAM, "streamPeriod", nextTransNode);
            if (streamAddress != nullptr)
                streamingAddresses.push_back(streamAddress->value());
            if (streamPeriod != nullptr)
                streamingPeriods.push_back(streamPeriod->value());
        }     
	}
}

void DPWS11MetadataSoapParserHandler::parseMetadata(XMLParser * parser, DPWS11Message * dpws11msg, xml_node<>* nodeMeta, const std::string & dialect)
{
	if (dialect.compare(WS_MEX_DIALECT_DEVICE) == 0) {
		parseMetadataDialectDevice(parser, dpws11msg, nodeMeta);
	}
	else if (dialect.compare(WS_MEX_DIALECT_MODEL) == 0) {
		parseMetadataDialectModel(parser, dpws11msg, nodeMeta);
	}
	else if (dialect.compare(WS_MEX_DIALECT_REL) == 0) {
		parseMetadataDialectRelationship(parser, dpws11msg, nodeMeta);
	}
	else if (dialect.compare(WS_MEX_DIALECT_WSDL) == 0) {
		parseMetadataDialectWSDL(parser, dpws11msg, nodeMeta);
	}
	else if (dialect.compare(OSCLib::Data::OSCP::WS_MEX_ORNET_DIALECT_STREAM) == 0) {
		parseMetadataDialectStream(parser, nodeMeta);
	}
}

bool DPWS11MetadataSoapParserHandler::parseBody(XMLParser * parser, DPWS11Message * dpws11msg, rapidxml::xml_node<> * nodeBody) {
    xml_node<>* nodeMetadata = parser->getChildByQName(WS_NS_METADATA_EXCHANGE, "Metadata", nodeBody);
    if (nodeMetadata == nullptr) {
        Util::DebugOut(Util::DebugOut::Error, "DPWS11MessageXMLParser") << "Missing metadata node.";
        return false;
    }
    for (xml_node<>* nextMetaSection = parser->getChildByQName(WS_NS_METADATA_EXCHANGE, "MetadataSection", nodeMetadata);
        nextMetaSection; nextMetaSection = nextMetaSection->next_sibling())
    {
        xml_attribute<>* attr = nextMetaSection->first_attribute("Dialect");
        const std::string dialect(attr->value());
        parseMetadata(parser, dpws11msg, nextMetaSection, dialect);
    }    
    
	return false;
}

std::vector<std::string> DPWS11MetadataSoapParserHandler::getStreamingPeriods() const {
    return streamingPeriods;
}

std::vector<std::string> DPWS11MetadataSoapParserHandler::getStreamingAddresses() const {
    return streamingAddresses;
}

} /* namespace DPWS */
} /* namespace Comm */
} /* namespace OSCLib */
