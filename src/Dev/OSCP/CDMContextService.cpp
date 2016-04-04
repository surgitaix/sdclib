/*
 * CDMPhiService.cpp
 *
 *  Created on: 26.05.2015
 *      Author: roehser
 */

#include "OSCLib/wsdls.h"
#include "OSCLib/Data/OSCP/Operations/CDMEventSource.h"
#include "OSCLib/Data/OSCP/Operations/CDMOperation.h"
#include "OSCLib/Data/OSCP/Operations/OSCPOperationTraits.h"
#include "OSCLib/Dev/OSCP/CDMContextService.h"
#include "OSCLib/Dev/OSCP/WSDLBuilder.h"

#include <memory>

namespace OSCLib {
namespace Dev {
namespace OSCP {

CDMContextService::CDMContextService(OSCLib::Data::OSCP::OSCPProvider & provider) {
	setServiceId("PHI");

    typedef Data::OSCP::CDMOperation<Data::OSCP::GetContextStatesTraits> GetContextStatesOperation;
    typedef Data::OSCP::CDMOperation<Data::OSCP::SetContextStateTraits> SetContextStateOperation;

	addOperation(std::shared_ptr<GetContextStatesOperation>(new GetContextStatesOperation(provider)));
	addOperation(std::shared_ptr<SetContextStateOperation>(new SetContextStateOperation(provider)));
	addEvent(std::shared_ptr<Data::OSCP::CDMEpisodicContextChangedEventSource>(new Data::OSCP::CDMEpisodicContextChangedEventSource()));
	addEvent(std::shared_ptr<Data::OSCP::CDMPeriodicContextChangedEventSource>(new Data::OSCP::CDMPeriodicContextChangedEventSource()));

    WSDLBuilder builder(Data::OSCP::NS_WSDL_TARGET_NAMESPACE, Data::OSCP::QNAME_CONTEXTSERVICE_PORTTYPE);
    WSDLBuilderTraitAdapter<Data::OSCP::GetContextStatesTraits> GetContextStatesTraitsAdapter(builder);
	WSDLBuilderTraitAdapter<Data::OSCP::SetContextStateTraits> SetContextStateTraitsAdapter(builder);
	WSDLBuilderTraitAdapter<Data::OSCP::EpisodicContextChangedReportTraits> EpisodicContextChangedReportTraitsAdapter(builder);
	WSDLBuilderTraitAdapter<Data::OSCP::PeriodicContextChangedReportTraits> PeriodicContextChangedReportTraitsAdapter(builder);

	setStaticWSDLContent(builder.serialize());
	addSchemaFile(SCHEMA_DATAMODEL_NAME, SCHEMA_DATAMODEL_CONTENT);
	addSchemaFile(SCHEMA_DICOM_DATAMODEL_NAME, SCHEMA_DICOM_DATAMODEL_CONTENT);
	addSchemaFile(SCHEMA_MESSAGEMODEL_NAME, SCHEMA_MESSAGEMODEL_CONTENT);
	addSchemaFile(SCHEMA_EXTENSION_POINT_NAME, SCHEMA_EXTENSION_POINT_CONTENT);
}

CDMContextService::~CDMContextService() {

}

} /* namespace OSCP */
} /* namespace Dev */
} /* namespace OSCLib */
