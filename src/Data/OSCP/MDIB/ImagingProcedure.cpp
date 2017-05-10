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
 *  Author: besting, roehser
 */
 
/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 * 
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "OSCLib/Data/OSCP/MDIB/ImagingProcedure.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/InstanceIdentifier.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

ImagingProcedure::ImagingProcedure() : data(Defaults::ImagingProcedure()) {
}

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
	*data = *object.data;
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
	
ImagingProcedure & ImagingProcedure::setRequestedProcedureID(const InstanceIdentifier & value) {
	data->RequestedProcedureID(ConvertToCDM::convert(value));
	return *this;
}


InstanceIdentifier ImagingProcedure::getRequestedProcedureID() const {
	return ConvertFromCDM::convert(data->RequestedProcedureID());
}
	
ImagingProcedure & ImagingProcedure::setStudyInstanceUID(const InstanceIdentifier & value) {
	data->StudyInstanceUID(ConvertToCDM::convert(value));
	return *this;
}


InstanceIdentifier ImagingProcedure::getStudyInstanceUID() const {
	return ConvertFromCDM::convert(data->StudyInstanceUID());
}
	
ImagingProcedure & ImagingProcedure::setScheduledProcedureStepID(const InstanceIdentifier & value) {
	data->ScheduledProcedureStepID(ConvertToCDM::convert(value));
	return *this;
}


InstanceIdentifier ImagingProcedure::getScheduledProcedureStepID() const {
	return ConvertFromCDM::convert(data->ScheduledProcedureStepID());
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
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

