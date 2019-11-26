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

#include "DataModel/osdm.hxx"

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
))
{}

ImagingProcedure::operator CDM::ImagingProcedure() const {
	return *data;
}

ImagingProcedure::ImagingProcedure(const CDM::ImagingProcedure & object)
: data(new CDM::ImagingProcedure(object))
{ }

ImagingProcedure::ImagingProcedure(const ImagingProcedure & object)
: data(std::make_shared<CDM::ImagingProcedure>(*object.data))
{ }

void ImagingProcedure::copyFrom(const ImagingProcedure & object) {
	data = std::make_shared<CDM::ImagingProcedure>(*object.data);
}

ImagingProcedure & ImagingProcedure:: operator=(const ImagingProcedure& object) {
	copyFrom(object);
	return *this;
}


ImagingProcedure & ImagingProcedure::setAccessionIdentifier(const InstanceIdentifier & value) {
	data->setAccessionIdentifier(ConvertToCDM::convert(value));
	return *this;
}


InstanceIdentifier ImagingProcedure::getAccessionIdentifier() const {
	return ConvertFromCDM::convert(data->getAccessionIdentifier());
}

ImagingProcedure & ImagingProcedure::setRequestedProcedureId(const InstanceIdentifier & value) {
	data->setRequestedProcedureId(ConvertToCDM::convert(value));
	return *this;
}


InstanceIdentifier ImagingProcedure::getRequestedProcedureId() const {
	return ConvertFromCDM::convert(data->getRequestedProcedureId());
}

ImagingProcedure & ImagingProcedure::setStudyInstanceUid(const InstanceIdentifier & value) {
	data->setStudyInstanceUid(ConvertToCDM::convert(value));
	return *this;
}


InstanceIdentifier ImagingProcedure::getStudyInstanceUid() const {
	return ConvertFromCDM::convert(data->getStudyInstanceUid());
}

ImagingProcedure & ImagingProcedure::setScheduledProcedureStepId(const InstanceIdentifier & value) {
	data->setScheduledProcedureStepId(ConvertToCDM::convert(value));
	return *this;
}


InstanceIdentifier ImagingProcedure::getScheduledProcedureStepId() const {
	return ConvertFromCDM::convert(data->getScheduledProcedureStepId());
}

ImagingProcedure & ImagingProcedure::setModality(const CodedValue & value) {
	data->setModality(ConvertToCDM::convert(value));
	return *this;
}

bool ImagingProcedure::getModality(CodedValue & out) const {
	if (data->getModality().present()) {
		out = ConvertFromCDM::convert(data->getModality().get());
		return true;
	}
	return false;
}

CodedValue ImagingProcedure::getModality() const {
	return ConvertFromCDM::convert(data->getModality().get());
}

bool ImagingProcedure::hasModality() const {
	return data->getModality().present();
}

ImagingProcedure & ImagingProcedure::setProtocolCode(const CodedValue & value) {
	data->setProtocolCode(ConvertToCDM::convert(value));
	return *this;
}

bool ImagingProcedure::getProtocolCode(CodedValue & out) const {
	if (data->getProtocolCode().present()) {
		out = ConvertFromCDM::convert(data->getProtocolCode().get());
		return true;
	}
	return false;
}

CodedValue ImagingProcedure::getProtocolCode() const {
	return ConvertFromCDM::convert(data->getProtocolCode().get());
}

bool ImagingProcedure::hasProtocolCode() const {
	return data->getProtocolCode().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

