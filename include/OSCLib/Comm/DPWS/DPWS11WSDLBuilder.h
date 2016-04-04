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
 * DPWS11WSDLBuilder.h
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: besting, roehser
 */

#ifndef DPWS11WSDLBUILDER_H_
#define DPWS11WSDLBUILDER_H_

#include <vector>
#include <map>

namespace OSCLib {

namespace Dev {
class Device;
class Service;
}

namespace Data {
class Operation;
class Parameter;
class QName;
typedef std::vector<Parameter> Parameters;
}
namespace Comm {

namespace Soap {
class XMLEntity;
}

namespace DPWS {

class DPWS11Message;

typedef std::vector<std::shared_ptr<Data::Operation>> OperationVector;

class DPWS11WSDLBuilder {
public:
	DPWS11WSDLBuilder();
	virtual ~DPWS11WSDLBuilder();

	void addServiceNode(const DPWS11Message & msg, const Dev::Service & service, Soap::XMLEntity * parent, const OperationVector & operations) const;
    void addWSDLCardinality(const Data::Parameter & parameter, Comm::Soap::XMLEntity* nextElement) const;
    void addWSDLLink(const DPWS11Message & msg, Soap::XMLEntity* wsdlEntity, const Dev::Service & service) const;
    std::map<std::string, OperationVector > getOperationsGroupedByNamespace(const OperationVector & ov) const;
    OperationVector getOperationsByNamespace(const OperationVector & ov, const std::string & nameSpace) const;
    std::string addWSDLMessage(Soap::XMLEntity * wsdlDoc, const OSCLib::Data::QName & elementName, const Data::Operation & op, bool response) const;
    Soap::XMLEntity* addWSDLOperationMessage(Soap::XMLEntity * portOp, const std::string & msgName, const Data::Operation & op, bool response) const;
    void addWSDLComplexParameters(Soap::XMLEntity * schema, Soap::XMLEntity * element, const Data::Parameters & params, const Data::Parameter & parentParam, const OSCLib::Data::QName & operationPortType) const;
    void addWSDLOperationParameters(Soap::XMLEntity * schemaNode, const Data::Parameters & param, const std::string & opName, const OSCLib::Data::QName & operationPortType) const;
	void addTypesNode(Soap::XMLEntity * parent, const std::string & targetNamespace, const OperationVector & operations) const;
	void addBindingNodes(Soap::XMLEntity * parent, const OperationVector & operations) const;
	void addPortTypeNodes(Soap::XMLEntity * parent, const OperationVector & operations) const;

	void addHeaderInformation(Soap::XMLEntity * parent, const std::string & targetNamespace) const;

	void createWSDL(const DPWS11Message & msg, const Dev::Service & service, Soap::XMLEntity * embeddEntity, const std::string & targetNamespace = "") const;
};

} /* namespace DPWS */
} /* namespace Comm */
} /* namespace OSCLib */
#endif /* DPWS11WSDLBUILDER_H_ */
