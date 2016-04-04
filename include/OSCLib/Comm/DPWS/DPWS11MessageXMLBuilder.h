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
 * DPWS11MessageXMLBuilder.h
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: besting, roehser
 */

#ifndef DPWS11MESSAGEXMLBUILDER_H_
#define DPWS11MESSAGEXMLBUILDER_H_

#include <string>
#include <vector>
#include "Poco/Net/NetworkInterface.h"

namespace OSCLib {
namespace Dev {
class Device;
class EndpointReference;
class Service;
class Entity;
}

namespace Comm {
class IPBinding;
namespace DPWS{
class DPWS11Message;
}
namespace Soap {
class XMLEntity;
}

namespace DPWS {

class DPWS11MessageXMLBuilder {
public:

	static void addBasicDiscoveryInfo(Soap::XMLEntity * entity, const Dev::Device & dev, bool xAdrr = true);
	static void addXAddrs(Soap::XMLEntity * parent, const Dev::Device & device);
	static void addTypesAttributes(Soap::XMLEntity * node, const Dev::Entity & entity);
	static void addTypesNode(Soap::XMLEntity * parent, const std::string & typesName, const Dev::Entity & entity);
	static void addScopes(Soap::XMLEntity * parent, const Dev::Entity & entity);

	static void addMetadataModel(Soap::XMLEntity * parent, const Dev::Device & device);
	static void addMetadataDevice(Soap::XMLEntity * parent, const Dev::Device & device);
	static void addMetadataRelationship(const Comm::DPWS::DPWS11Message & msg, Soap::XMLEntity * parent, const Dev::Device & device, int wsdlIndex);
	static void addMetadataStreaming(Soap::XMLEntity * parent, const Dev::Device & device, int wsdlIndex);
	static void addMetadataService(const Comm::DPWS::DPWS11Message & msg, Soap::XMLEntity * parent, const Dev::Service & service);
	static void addMetadataServiceStream(Soap::XMLEntity * parent, const Dev::Service & service);

	static void appendEndpointReferenceTo(Soap::XMLEntity * parent, const Dev::EndpointReference & endpointRef);

private:

	static std::vector<Poco::Net::NetworkInterface> findInterfaces(const IPBinding & binding);

	DPWS11MessageXMLBuilder() {
	}

	~DPWS11MessageXMLBuilder() {
	}
};

} /* namespace DPWS */
} /* namespace Comm */
} /* namespace OSCLib */
#endif /* DPWS11MESSAGEXMLBUILDER_H_ */
