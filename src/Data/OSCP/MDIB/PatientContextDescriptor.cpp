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
 *  PatientContextDescriptor.cpp
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

#include "OSCLib/Data/OSCP/MDIB/PatientContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

namespace OSCLib {
namespace Data {
namespace OSCP {


PatientContextDescriptor::PatientContextDescriptor(
		Handle handle
) : data(Defaults::PatientContextDescriptorInit(
		handle
)) {}

PatientContextDescriptor::operator CDM::PatientContextDescriptor() const {
	return *data;
}

PatientContextDescriptor::PatientContextDescriptor(const CDM::PatientContextDescriptor & object) : data(new CDM::PatientContextDescriptor(object)) {

}

PatientContextDescriptor::PatientContextDescriptor(const PatientContextDescriptor & object) : data(new CDM::PatientContextDescriptor(*object.data)) {

}

PatientContextDescriptor::~PatientContextDescriptor() {

}

void PatientContextDescriptor::copyFrom(const PatientContextDescriptor & object) {
	data = std::shared_ptr<CDM::PatientContextDescriptor>( new CDM::PatientContextDescriptor(*object.data));
}

PatientContextDescriptor & PatientContextDescriptor:: operator=(const PatientContextDescriptor & object) {
	copyFrom(object);
	return *this;
}


PatientContextDescriptor & PatientContextDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool PatientContextDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue PatientContextDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool PatientContextDescriptor::hasType() const {
	return data->Type().present();
}
	
PatientContextDescriptor & PatientContextDescriptor::setHandle(const Handle & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


Handle PatientContextDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
PatientContextDescriptor & PatientContextDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool PatientContextDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter PatientContextDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool PatientContextDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
PatientContextDescriptor & PatientContextDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->SafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool PatientContextDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->SafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->SafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification PatientContextDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->SafetyClassification().get());
}
	
bool PatientContextDescriptor::hasSafetyClassification() const {
	return data->SafetyClassification().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

