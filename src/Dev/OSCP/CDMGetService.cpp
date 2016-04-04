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
 * CDMGetService.cpp
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: roehser, besting
 */

#include "OSCLib/wsdls.h"
#include "OSCLib/Data/OSCP/Operations/CDMOperation.h"
#include "OSCLib/Data/OSCP/Operations/OSCPOperationTraits.h"
#include "OSCLib/Dev/OSCP/CDMGetService.h"
#include "OSCLib/Dev/OSCP/WSDLBuilder.h"

#include <memory>

namespace OSCLib {
namespace Dev {
namespace OSCP {

CDMGetService::CDMGetService(OSCLib::Data::OSCP::OSCPProvider & provider) {
    setServiceId("GetService");

    typedef Data::OSCP::CDMOperation<Data::OSCP::GetMDDescriptionTraits> GetMDDescriptionOperation;
    typedef Data::OSCP::CDMOperation<Data::OSCP::GetMDIBTraits> GetMDIBOperation;
    typedef Data::OSCP::CDMOperation<Data::OSCP::GetMDStateTraits> GetMDStateOperation;

    addOperation(std::shared_ptr<GetMDDescriptionOperation>(new GetMDDescriptionOperation(provider)));
    addOperation(std::shared_ptr<GetMDIBOperation>(new GetMDIBOperation(provider)));
    addOperation(std::shared_ptr<GetMDStateOperation>(new GetMDStateOperation(provider)));

    WSDLBuilder builder(Data::OSCP::NS_WSDL_TARGET_NAMESPACE, Data::OSCP::QNAME_GETSERVICE_PORTTYPE);
    WSDLBuilderTraitAdapter<Data::OSCP::GetMDDescriptionTraits> GetMDDescriptionTraitsAdapter(builder);
	WSDLBuilderTraitAdapter<Data::OSCP::GetMDIBTraits> GetMDIBTraitsAdapter(builder);
	WSDLBuilderTraitAdapter<Data::OSCP::GetMDStateTraits> GetMDStateOperationAdapter(builder);

	setStaticWSDLContent(builder.serialize());
	addSchemaFile(SCHEMA_DATAMODEL_NAME, SCHEMA_DATAMODEL_CONTENT);
	addSchemaFile(SCHEMA_DICOM_DATAMODEL_NAME, SCHEMA_DICOM_DATAMODEL_CONTENT);
	addSchemaFile(SCHEMA_MESSAGEMODEL_NAME, SCHEMA_MESSAGEMODEL_CONTENT);
	addSchemaFile(SCHEMA_EXTENSION_POINT_NAME, SCHEMA_EXTENSION_POINT_CONTENT);
}

CDMGetService::~CDMGetService() {

}

} /* namespace OSCP */
} /* namespace Comm */
} /* namespace OSCLib */
