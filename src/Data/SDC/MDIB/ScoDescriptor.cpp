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
 *  ScoDescriptor.cpp
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

#include "OSCLib/Data/SDC/MDIB/ScoDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/SDC/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


ScoDescriptor::ScoDescriptor(
		Handle handle
) : data(Defaults::ScoDescriptorInit(
		handle
)) {}

ScoDescriptor::operator CDM::ScoDescriptor() const {
	return *data;
}

ScoDescriptor::ScoDescriptor(const CDM::ScoDescriptor & object) : data(new CDM::ScoDescriptor(object)) {

}

ScoDescriptor::ScoDescriptor(const ScoDescriptor & object) : data(new CDM::ScoDescriptor(*object.data)) {

}

ScoDescriptor::~ScoDescriptor() {

}

void ScoDescriptor::copyFrom(const ScoDescriptor & object) {
	data = std::shared_ptr<CDM::ScoDescriptor>( new CDM::ScoDescriptor(*object.data));
}

ScoDescriptor & ScoDescriptor:: operator=(const ScoDescriptor & object) {
	copyFrom(object);
	return *this;
}


ScoDescriptor & ScoDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool ScoDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue ScoDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool ScoDescriptor::hasType() const {
	return data->Type().present();
}
	
ScoDescriptor & ScoDescriptor::setHandle(const Handle & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


Handle ScoDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
ScoDescriptor & ScoDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool ScoDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter ScoDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool ScoDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
ScoDescriptor & ScoDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->SafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool ScoDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->SafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->SafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification ScoDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->SafetyClassification().get());
}
	
bool ScoDescriptor::hasSafetyClassification() const {
	return data->SafetyClassification().present();
}
	

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

