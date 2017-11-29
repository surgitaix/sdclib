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
 *  LocationContextDescriptor.cpp
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

#include "OSCLib/Data/OSCP/MDIB/LocationContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

namespace OSCLib {
namespace Data {
namespace OSCP {


LocationContextDescriptor::LocationContextDescriptor(
		Handle handle
) : data(Defaults::LocationContextDescriptorInit(
		handle
)) {}

LocationContextDescriptor::operator CDM::LocationContextDescriptor() const {
	return *data;
}

LocationContextDescriptor::LocationContextDescriptor(const CDM::LocationContextDescriptor & object) : data(new CDM::LocationContextDescriptor(object)) {

}

LocationContextDescriptor::LocationContextDescriptor(const LocationContextDescriptor & object) : data(new CDM::LocationContextDescriptor(*object.data)) {

}

LocationContextDescriptor::~LocationContextDescriptor() {

}

void LocationContextDescriptor::copyFrom(const LocationContextDescriptor & object) {
	data = std::shared_ptr<CDM::LocationContextDescriptor>( new CDM::LocationContextDescriptor(*object.data));
}

LocationContextDescriptor & LocationContextDescriptor:: operator=(const LocationContextDescriptor & object) {
	copyFrom(object);
	return *this;
}


LocationContextDescriptor & LocationContextDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool LocationContextDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue LocationContextDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool LocationContextDescriptor::hasType() const {
	return data->Type().present();
}
	
LocationContextDescriptor & LocationContextDescriptor::setHandle(const Handle & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


Handle LocationContextDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
LocationContextDescriptor & LocationContextDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool LocationContextDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter LocationContextDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool LocationContextDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
LocationContextDescriptor & LocationContextDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->SafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool LocationContextDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->SafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->SafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification LocationContextDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->SafetyClassification().get());
}
	
bool LocationContextDescriptor::hasSafetyClassification() const {
	return data->SafetyClassification().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

