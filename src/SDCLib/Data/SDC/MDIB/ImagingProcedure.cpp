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
 *  ImagingProcedure.cpp
 *
 *  @Copyright (C) 2015, SurgiTAIX AG
 *  Author: besting, buerger, roehser
 */

/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 *
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "SDCLib/Data/SDC/MDIB/ImagingProcedure.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/InstanceIdentifier.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


ImagingProcedure::ImagingProcedure(
		InstanceIdentifier accessionidentifier
		,
		InstanceIdentifier requestedprocedureid
		,
		InstanceIdentifier studyinstanceuid
		,
		InstanceIdentifier scheduledprocedurestepid
) : data(Defaults::ImagingProcedureInit(
		accessionidentifier
		,
		requestedprocedureid
		,
		studyinstanceuid
		,
		scheduledprocedurestepid
)) {}

ImagingProcedure::operator CDM::ImagingProcedure() const {
	return *data;
}

ImagingProcedure::ImagingProcedure(const CDM::ImagingProcedure & object) : data(new CDM::ImagingProcedure(object)) {

}

ImagingProcedure::ImagingProcedure(const ImagingProcedure & object) : data(new CDM::ImagingProcedure(*object.data)) {

}

ImagingProcedure::~ImagingProcedure() {

}

void ImagingProcedure::copyFrom(const ImagingProcedure & object) {
	data = std::shared_ptr<CDM::ImagingProcedure>( new CDM::ImagingProcedure(*object.data));
}

ImagingProcedure & ImagingProcedure:: operator=(const ImagingProcedure & object) {
	copyFrom(object);
	return *this;
}


ImagingProcedure & ImagingProcedure::setAccessionIdentifier(const InstanceIdentifier & value) {
	data->AccessionIdentifier(ConvertToCDM::convert(value));
	return *this;
}


InstanceIdentifier ImagingProcedure::getAccessionIdentifier() const {
	return ConvertFromCDM::convert(data->AccessionIdentifier());
}

ImagingProcedure & ImagingProcedure::setRequestedProcedureId(const InstanceIdentifier & value) {
	data->RequestedProcedureId(ConvertToCDM::convert(value));
	return *this;
}


InstanceIdentifier ImagingProcedure::getRequestedProcedureId() const {
	return ConvertFromCDM::convert(data->RequestedProcedureId());
}

ImagingProcedure & ImagingProcedure::setStudyInstanceUid(const InstanceIdentifier & value) {
	data->StudyInstanceUid(ConvertToCDM::convert(value));
	return *this;
}


InstanceIdentifier ImagingProcedure::getStudyInstanceUid() const {
	return ConvertFromCDM::convert(data->StudyInstanceUid());
}

ImagingProcedure & ImagingProcedure::setScheduledProcedureStepId(const InstanceIdentifier & value) {
	data->ScheduledProcedureStepId(ConvertToCDM::convert(value));
	return *this;
}


InstanceIdentifier ImagingProcedure::getScheduledProcedureStepId() const {
	return ConvertFromCDM::convert(data->ScheduledProcedureStepId());
}

ImagingProcedure & ImagingProcedure::setModality(const CodedValue & value) {
	data->Modality(ConvertToCDM::convert(value));
	return *this;
}

bool ImagingProcedure::getModality(CodedValue & out) const {
	if (data->Modality().present()) {
		out = ConvertFromCDM::convert(data->Modality().get());
		return true;
	}
	return false;
}

CodedValue ImagingProcedure::getModality() const {
	return ConvertFromCDM::convert(data->Modality().get());
}

bool ImagingProcedure::hasModality() const {
	return data->Modality().present();
}

ImagingProcedure & ImagingProcedure::setProtocolCode(const CodedValue & value) {
	data->ProtocolCode(ConvertToCDM::convert(value));
	return *this;
}

bool ImagingProcedure::getProtocolCode(CodedValue & out) const {
	if (data->ProtocolCode().present()) {
		out = ConvertFromCDM::convert(data->ProtocolCode().get());
		return true;
	}
	return false;
}

CodedValue ImagingProcedure::getProtocolCode() const {
	return ConvertFromCDM::convert(data->ProtocolCode().get());
}

bool ImagingProcedure::hasProtocolCode() const {
	return data->ProtocolCode().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

