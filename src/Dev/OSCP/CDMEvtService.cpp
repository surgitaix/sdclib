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
 * CDMEvtService.cpp
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: roehser, besting
 */

#include "OSCLib/wsdls.h"
#include "OSCLib/Data/OSCP/Operations/CDMEventSource.h"
#include "OSCLib/Dev/OSCP/CDMEvtService.h"
#include "OSCLib/Dev/OSCP/WSDLBuilder.h"
#include "OSCLib/Util/DebugOut.h"
#include <memory>

namespace OSCLib {
namespace Dev {
namespace OSCP {

CDMEvtService::CDMEvtService() {
    setServiceId("EventReport");

    addEvent(std::shared_ptr<Data::OSCP::CDMEpisodicAlertEventSource>(new Data::OSCP::CDMEpisodicAlertEventSource()));
    addEvent(std::shared_ptr<Data::OSCP::CDMEpisodicMetricEventSource>(new Data::OSCP::CDMEpisodicMetricEventSource()));
    addEvent(std::shared_ptr<Data::OSCP::CDMOperationInvokedReportSource>(new Data::OSCP::CDMOperationInvokedReportSource));
    addEvent(std::shared_ptr<Data::OSCP::CDMPeriodicAlertEventSource>(new Data::OSCP::CDMPeriodicAlertEventSource()));
    addEvent(std::shared_ptr<Data::OSCP::CDMPeriodicMetricEventSource>(new Data::OSCP::CDMPeriodicMetricEventSource()));

    WSDLBuilder builder(Data::OSCP::NS_WSDL_TARGET_NAMESPACE, Data::OSCP::QNAME_REPORTSERVICE_PORTTYPE);
    WSDLBuilderTraitAdapter<Data::OSCP::EpisodicAlertReportTraits> EpisodicAlertReportTraitsAdapter(builder);
    WSDLBuilderTraitAdapter<Data::OSCP::EpisodicMetricReportTraits> EpisodicMetricReportTraitsAdapter(builder);
    WSDLBuilderTraitAdapter<Data::OSCP::OperationInvokedReportTraits> OperationInvokedReportAdapter(builder);
    WSDLBuilderTraitAdapter<Data::OSCP::PeriodicAlertReportTraits> PeriodicAlertReportTraitsAdapter(builder);
    WSDLBuilderTraitAdapter<Data::OSCP::PeriodicMetricReportTraits> PeriodicMetricReportTraitsAdapter(builder);

	setStaticWSDLContent(builder.serialize());
	addSchemaFile(SCHEMA_DATAMODEL_NAME, SCHEMA_DATAMODEL_CONTENT);
	addSchemaFile(SCHEMA_DICOM_DATAMODEL_NAME, SCHEMA_DICOM_DATAMODEL_CONTENT);
	addSchemaFile(SCHEMA_MESSAGEMODEL_NAME, SCHEMA_MESSAGEMODEL_CONTENT);
	addSchemaFile(SCHEMA_EXTENSION_POINT_NAME, SCHEMA_EXTENSION_POINT_CONTENT);
}

CDMEvtService::~CDMEvtService() {

}

} /* namespace OSCP */
} /* namespace Comm */
} /* namespace OSCLib */
