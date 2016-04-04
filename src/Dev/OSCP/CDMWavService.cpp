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
 * CDMWavService.cpp
 *
 *  @Copyright (C) 2016, SurgiTAIX AG
 *  Author: besting, roehser
 */

#include "OSCLib/Dev/OSCP/CDMWavService.h"
#include "OSCLib/wsdls.h"
#include "OSCLib/Data/OSCP/Operations/CDMEventSource.h"
#include "OSCLib/Dev/OSCP/WSDLBuilder.h"
#include "OSCLib/Util/DebugOut.h"
#include "OSCLib/Data/QName.h"
#include "OSCLib/Data/OSCP/OSCPConstants.h"
#include <memory>

namespace OSCLib {
namespace Dev {
namespace OSCP {

CDMWavService::CDMWavService() {
	setServiceId("WaveformEventReport");

	addEvent(std::shared_ptr<Data::OSCP::CDMWaveformStreamSource>(new Data::OSCP::CDMWaveformStreamSource()));

    WSDLBuilder builder(Data::OSCP::NS_WSDL_TARGET_NAMESPACE, Data::OSCP::QNAME_STREAMSERVICE_PORTTYPE);
    WSDLBuilderTraitAdapter<Data::OSCP::WaveformStreamTraits> WaveformStreamTraitsAdapter(builder);
    builder.addStreamType(Data::OSCP::WS_MEX_ORNET_STREAM_IDENTIFIER, Data::OSCP::ACTION_ORNET_STREAM, Data::OSCP::WS_MEX_ORNET_STREAM_TYPE, "WaveformStream");

	setStaticWSDLContent(builder.serialize());
	addSchemaFile(SCHEMA_DATAMODEL_NAME, SCHEMA_DATAMODEL_CONTENT);
	addSchemaFile(SCHEMA_DICOM_DATAMODEL_NAME, SCHEMA_DICOM_DATAMODEL_CONTENT);
	addSchemaFile(SCHEMA_MESSAGEMODEL_NAME, SCHEMA_MESSAGEMODEL_CONTENT);
	addSchemaFile(SCHEMA_EXTENSION_POINT_NAME, SCHEMA_EXTENSION_POINT_CONTENT);

}

CDMWavService::~CDMWavService() {

}

} /* namespace OSCP */
} /* namespace Dev */
} /* namespace OSCLib */
