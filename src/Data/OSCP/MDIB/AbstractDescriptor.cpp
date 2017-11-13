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
 *  AbstractDescriptor.cpp
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

#include "OSCLib/Data/OSCP/MDIB/AbstractDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

AbstractDescriptor::AbstractDescriptor() : data(Defaults::AbstractDescriptor()) {
}

AbstractDescriptor::operator CDM::AbstractDescriptor() const {
	return *data;
}

AbstractDescriptor::AbstractDescriptor(const CDM::AbstractDescriptor & object) : data(new CDM::AbstractDescriptor(object)) {

}

AbstractDescriptor::AbstractDescriptor(const AbstractDescriptor & object) : data(new CDM::AbstractDescriptor(*object.data)) {

}

AbstractDescriptor::~AbstractDescriptor() {

}

void AbstractDescriptor::copyFrom(const AbstractDescriptor & object) {
	*data = *object.data;
}

AbstractDescriptor & AbstractDescriptor:: operator=(const AbstractDescriptor & object) {
	copyFrom(object);
	return *this;
}


AbstractDescriptor & AbstractDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool AbstractDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue AbstractDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool AbstractDescriptor::hasType() const {
	return data->Type().present();
}
	
AbstractDescriptor & AbstractDescriptor::setHandle(const Handle & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


Handle AbstractDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
AbstractDescriptor & AbstractDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool AbstractDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter AbstractDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool AbstractDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
AbstractDescriptor & AbstractDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->SafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool AbstractDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->SafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->SafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification AbstractDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->SafetyClassification().get());
}
	
bool AbstractDescriptor::hasSafetyClassification() const {
	return data->SafetyClassification().present();
}
	
} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

