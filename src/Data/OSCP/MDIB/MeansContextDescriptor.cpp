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
 *  MeansContextDescriptor.cpp
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

#include "OSCLib/Data/OSCP/MDIB/MeansContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

namespace OSCLib {
namespace Data {
namespace SDC {


MeansContextDescriptor::MeansContextDescriptor(
		Handle handle
) : data(Defaults::MeansContextDescriptorInit(
		handle
)) {}

MeansContextDescriptor::operator CDM::MeansContextDescriptor() const {
	return *data;
}

MeansContextDescriptor::MeansContextDescriptor(const CDM::MeansContextDescriptor & object) : data(new CDM::MeansContextDescriptor(object)) {

}

MeansContextDescriptor::MeansContextDescriptor(const MeansContextDescriptor & object) : data(new CDM::MeansContextDescriptor(*object.data)) {

}

MeansContextDescriptor::~MeansContextDescriptor() {

}

void MeansContextDescriptor::copyFrom(const MeansContextDescriptor & object) {
	data = std::shared_ptr<CDM::MeansContextDescriptor>( new CDM::MeansContextDescriptor(*object.data));
}

MeansContextDescriptor & MeansContextDescriptor:: operator=(const MeansContextDescriptor & object) {
	copyFrom(object);
	return *this;
}


MeansContextDescriptor & MeansContextDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool MeansContextDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue MeansContextDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool MeansContextDescriptor::hasType() const {
	return data->Type().present();
}
	
MeansContextDescriptor & MeansContextDescriptor::setHandle(const Handle & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


Handle MeansContextDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
MeansContextDescriptor & MeansContextDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool MeansContextDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter MeansContextDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool MeansContextDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
MeansContextDescriptor & MeansContextDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->SafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool MeansContextDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->SafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->SafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification MeansContextDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->SafetyClassification().get());
}
	
bool MeansContextDescriptor::hasSafetyClassification() const {
	return data->SafetyClassification().present();
}
	

} /* namespace SDC */
} /* namespace Data */
} /* namespace OSCLib */

