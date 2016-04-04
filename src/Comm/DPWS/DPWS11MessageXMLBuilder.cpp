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
 * DPWS11MessageXMLBuilder.cpp
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: besting, roehser
 */

#include "OSCLib/Comm/DPWS/DPWS11Message.h"
#include "OSCLib/Comm/DPWS/DPWS11MessageXMLBuilder.h"
#include "OSCLib/Comm/DPWS/DPWS11Constants.h"
#include "OSCLib/Data/OSCP/OSCPConstants.h"
#include "OSCLib/Comm/Binding.h"
#include "OSCLib/Comm/Soap/XMLEntity.h"
#include "OSCLib/Dev/Device.h"
#include "OSCLib/Dev/DeviceCharacteristics.h"
#include "OSCLib/Dev/EndpointReference.h"
#include "OSCLib/Util/DebugOut.h"
#include "OSCLib/Util/TypeConversion.h"
#include "Poco/ScopedLock.h"

using namespace OSCLib;
using namespace OSCLib::Comm::Soap;
using namespace OSCLib::Data;
using namespace OSCLib::Data::OSCP;

namespace OSCLib {
namespace Comm {
namespace DPWS {

void DPWS11MessageXMLBuilder::appendEndpointReferenceTo(XMLEntity * parent, const Dev::EndpointReference & endpointRef) {
	parent->appendChild("wsa:EndpointReference")
			->appendChild("wsa:Address")
			->setValue(endpointRef.getAddress());
}

void DPWS11MessageXMLBuilder::addMetadataModel(Soap::XMLEntity * parent, const Dev::Device & device) {
	const Dev::DeviceCharacteristics & dc = device.getDeviceCharacteristics();

	XMLEntity* metaDataSecModel = parent->appendChild("wsx:MetadataSection");
	metaDataSecModel->addAttribute("Dialect", WS_MEX_DIALECT_MODEL);

	XMLEntity* model = metaDataSecModel->appendChild("dpws:ThisModel");
	model->addTextNode("dpws:Manufacturer", dc.getManufacturer());
	model->addTextNode("dpws:ManufacturerUrl", dc.getManufacturerUrl());

	const Dev::LocalizedString & names = dc.getModelNames();
	Dev::LocalizedString::const_iterator it;
	for (it = names.begin(); it != names.end(); ++it)
	{
		model->appendChild("dpws:ModelName")
				->setValue(it->second)
				->addAttribute("xml:lang", it->first);
	}
	model->addTextNode("dpws:ModelNumber", dc.getModelNumber());
	model->addTextNode("dpws:ModelUrl", dc.getModelUrl());
	model->addTextNode("dpws:PresentationUrl", dc.getPresentationUrl());
}


void DPWS11MessageXMLBuilder::addMetadataDevice(Soap::XMLEntity * parent, const Dev::Device & device) {
	const Dev::DeviceCharacteristics & dc = device.getDeviceCharacteristics();

	XMLEntity * metaDataSecDevice = parent->appendChild("wsx:MetadataSection")
			->addAttribute("Dialect", WS_MEX_DIALECT_DEVICE);

	XMLEntity * deviceNode = metaDataSecDevice->appendChild("dpws:ThisDevice");

	const Dev::LocalizedString & names = dc.getFriendlyNames();
	Dev::LocalizedString::const_iterator it;
	for (it = names.begin(); it != names.end(); ++it) {
		deviceNode->appendChild("dpws:FriendlyName")
				->setValue(it->second)
				->addAttribute("xml:lang", it->first);
	}
	deviceNode->addTextNode("dpws:FirmwareVersion", dc.getFirmwareVersion());
	deviceNode->addTextNode("dpws:SerialNumber", dc.getSerialNumber());
}

void DPWS11MessageXMLBuilder::addMetadataService(const DPWS11Message & msg, Soap::XMLEntity * parent, const Dev::Service & service) {
	if (!service.isRunning())
		return;

	XMLEntity * hosted = parent->appendChild("dpws:Hosted");
	// Service endpoint reference / transport address
	Dev::EndpointReference epr = service.getEndpointReference();

	// Use transport address as new EPR
	epr.setAddress(service.getDefaultTransportAddr(DPWS11, msg.getDispatcher()));

	appendEndpointReferenceTo(hosted, epr);

	// Types
	addTypesAttributes(hosted, service);
	addTypesNode(hosted, "dpws:Types", service);

	// Service ID
	hosted->appendChild("dpws:ServiceId")
			->setValue(service.getServiceId());
}

void DPWS11MessageXMLBuilder::addMetadataRelationship(const DPWS11Message & msg, Soap::XMLEntity * parent, const Dev::Device & device, int wsdlIndex) {

	XMLEntity * relationship = parent->appendChild("wsx:MetadataSection")
			->addAttribute("Dialect", WS_MEX_DIALECT_REL)
			->appendChild("dpws:Relationship")
			->addAttribute("Type", WS_MEX_REL_HOST);

	// Host
	XMLEntity * host = relationship->appendChild("dpws:Host");
	appendEndpointReferenceTo(host, device.getEndpointReference());

	// Add Types
	addTypesAttributes(host, device);
	addTypesNode(host, "dpws:Types", device);

	// Hosted
    if (device.getServiceCount() > 0)
	{
		if (wsdlIndex == -1) {
			// add all
            size_t sSize = device.getServiceCount();
            for (size_t i = 0; i < sSize; ++i) {
                auto & nextService = device.getService(i);
                addMetadataService(msg, relationship, *nextService);
            }
		} else {
			// add single
            addMetadataService(msg, relationship, *device.getService(wsdlIndex));
		}
	}
}

void DPWS11MessageXMLBuilder::addMetadataStreaming(Soap::XMLEntity * parent, const Dev::Device & device, int wsdlIndex) {
    // Check for waveform service id
    if (wsdlIndex < 0 || (wsdlIndex >= 0 && device.getService(wsdlIndex)->getServiceId() != "WaveformEventReport"))
        return;
    // Check for MDPWS bindings
    auto pbmIt = device.getProtocolBindings().find(MDPWS);
    if (pbmIt == device.getProtocolBindings().end())
        return;

	XMLEntity * streamDescriptions = parent->appendChild("wsx:MetadataSection")
			->addAttribute("Dialect", WS_MEX_ORNET_DIALECT_STREAM)
			->addAttribute("Identifier", WS_MEX_ORNET_STREAM_IDENTIFIER)
			->appendChild("wsstm:StreamDescriptions")
			->addNamespace("wsstm", WS_MEX_ORNET_NS_STREAM)
			->addAttribute("targetNamespace", WS_MEX_ORNET_STREAM_IDENTIFIER);

	// Stream types
    addMetadataServiceStream(streamDescriptions, *device.getService(wsdlIndex));
}

void DPWS11MessageXMLBuilder::addMetadataServiceStream(Soap::XMLEntity * parent, const Dev::Service & service) {
	if (!service.isRunning())
		return;

	XMLEntity * streamType = parent->appendChild("wsstm:streamType")
			->addAttribute("id", "WaveformStream")
			->addAttribute("actionURI", ACTION_ORNET_STREAM)
			->addAttribute("streamType", WS_MEX_ORNET_STREAM_TYPE);
	streamType->addQualifiedAttribute("element", QName("WaveformStream", NS_MESSAGE_MODEL), streamType);

	// Iterate all mcast bindings
	for (const auto & protoBnd : service.getProtocolBindings()) {
		for (const auto & nextBnd : protoBnd.second) {
			if (nextBnd->getType() == AbstractBinding::UDP_MULTICAST) {
				XMLEntity * streamTrans = streamType->appendChild("wsstm:StreamTransmission");
				streamTrans->addTextNode("wsstm:streamAddress", nextBnd->toString());
			}
		}
	}

}

void DPWS11MessageXMLBuilder::addXAddrs(XMLEntity * parent, const Dev::Device & device) {

	Util::StringVector xaddrs;

	// We need at least two bindings here (multicast discovery and at least one unicast).
	if (device.getProtocolBindings().find(DPWS11)->second.size() <= 1)
		Util::DebugOut(Util::DebugOut::Error, "DPWS11MessageXMLBuilder") << "No device address available. Missing DPWS 1.1 binding.";
	else
	{
		const std::vector<std::shared_ptr<AbstractBinding>> & bindings = device.getProtocolBindings().find(DPWS11)->second;

		for (const auto & bnd : bindings) {
			if (bnd->getType() != AbstractBinding::UDP_MULTICAST)
			{
				Binding ipBndClone(*std::dynamic_pointer_cast<Binding>(bnd));
				std::vector<Poco::Net::NetworkInterface> ifs = findInterfaces(ipBndClone);
				for (const auto nif : ifs) {
					ipBndClone.setSocketAddress(Poco::Net::SocketAddress(nif.address(), ipBndClone.getPort()));
					xaddrs.push_back(ipBndClone.toString());
				}
			}
		}
	}
	parent->addTextNode("wsd:XAddrs", Util::joinString(xaddrs));
}

void DPWS11MessageXMLBuilder::addTypesAttributes(XMLEntity * node, const Dev::Entity & entity) {
	const QVector & types = entity.getTypes();

	for(QVector::const_iterator qIt = types.begin(); qIt != types.end(); ++qIt) {
		node->addNamespace(qIt->getPrefix(), qIt->getNamespace());
	}
}

void DPWS11MessageXMLBuilder::addTypesNode(XMLEntity * parent, const std::string & nodeName, const Dev::Entity & entity) {
	const QVector & types = entity.getTypes();

	Util::StringVector typeStrings;
	for(QVector::const_iterator qIt = types.begin();qIt != types.end(); ++qIt) {
		typeStrings.push_back(qIt->getPrefixedName());
	}

	if (typeStrings.size() != 0) {
		parent->appendChild(nodeName)
				->setValue(Util::joinString(typeStrings));
	}
}

void DPWS11MessageXMLBuilder::addScopes(XMLEntity * parent, const Dev::Entity & entity) {
	parent->addTextNode("wsd:Scopes", Util::joinString(entity.getScopes()));
}

void DPWS11MessageXMLBuilder::addBasicDiscoveryInfo(XMLEntity* parent, const Dev::Device & device, bool addXAdrr) {
	// Endpoint reference
	appendEndpointReferenceTo(parent, device.getEndpointReference());

	// Add Types
	addTypesAttributes(parent, device);
	addTypesNode(parent, "wsd:Types", device);

	// Add Scopes
	addScopes(parent, device);

	// Add XAddrs
	if (addXAdrr) {
		addXAddrs(parent, device);
	}

	// Add metadata version
	parent->addTextNode("wsd:MetadataVersion", std::to_string(device.getMetaDataVersion()));
}

std::vector<Poco::Net::NetworkInterface> DPWS11MessageXMLBuilder::findInterfaces(const IPBinding & binding)
{
	Poco::Net::IPAddress interfaceIp(binding.getIp());
	std::vector<Poco::Net::NetworkInterface> ifList;
	for (const auto & nextIf : Poco::Net::NetworkInterface::list())
	{
		if (nextIf.supportsIPv4() && nextIf.address().isUnicast()
				&& !nextIf.address().isLoopback() && (nextIf.address() == interfaceIp || binding.getIp() == "0.0.0.0"))
			ifList.push_back(nextIf);
	}
	return ifList;
}


} /* namespace DPWS */
} /* namespace Comm */
} /* namespace OSCLib */
