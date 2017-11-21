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
 *  EnsembleContextDescriptor.cpp
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

#include "OSCLib/Data/OSCP/MDIB/EnsembleContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

namespace OSCLib {
namespace Data {
namespace OSCP {


EnsembleContextDescriptor::EnsembleContextDescriptor(
		Handle handle
) : data(Defaults::EnsembleContextDescriptorInit(
		handle
)) {}

EnsembleContextDescriptor::operator CDM::EnsembleContextDescriptor() const {
	return *data;
}

EnsembleContextDescriptor::EnsembleContextDescriptor(const CDM::EnsembleContextDescriptor & object) : data(new CDM::EnsembleContextDescriptor(object)) {

}

EnsembleContextDescriptor::EnsembleContextDescriptor(const EnsembleContextDescriptor & object) : data(new CDM::EnsembleContextDescriptor(*object.data)) {

}

EnsembleContextDescriptor::~EnsembleContextDescriptor() {

}

void EnsembleContextDescriptor::copyFrom(const EnsembleContextDescriptor & object) {
	*data = *object.data;
}

EnsembleContextDescriptor & EnsembleContextDescriptor:: operator=(const EnsembleContextDescriptor & object) {
	copyFrom(object);
	return *this;
}


EnsembleContextDescriptor & EnsembleContextDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool EnsembleContextDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue EnsembleContextDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool EnsembleContextDescriptor::hasType() const {
	return data->Type().present();
}
	
EnsembleContextDescriptor & EnsembleContextDescriptor::setHandle(const Handle & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


Handle EnsembleContextDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
EnsembleContextDescriptor & EnsembleContextDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool EnsembleContextDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter EnsembleContextDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool EnsembleContextDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
EnsembleContextDescriptor & EnsembleContextDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->SafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool EnsembleContextDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->SafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->SafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification EnsembleContextDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->SafetyClassification().get());
}
	
bool EnsembleContextDescriptor::hasSafetyClassification() const {
	return data->SafetyClassification().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

