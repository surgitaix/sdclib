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
 *  ActivateOperationDescriptor.cpp
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

#include "OSCLib/Data/OSCP/MDIB/ActivateOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/Duration.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

ActivateOperationDescriptor::ActivateOperationDescriptor() : data(Defaults::ActivateOperationDescriptor()) {
}

ActivateOperationDescriptor::operator CDM::ActivateOperationDescriptor() const {
	return *data;
}

ActivateOperationDescriptor::ActivateOperationDescriptor(const CDM::ActivateOperationDescriptor & object) : data(new CDM::ActivateOperationDescriptor(object)) {

}

ActivateOperationDescriptor::ActivateOperationDescriptor(const ActivateOperationDescriptor & object) : data(new CDM::ActivateOperationDescriptor(*object.data)) {

}

ActivateOperationDescriptor::~ActivateOperationDescriptor() {

}

void ActivateOperationDescriptor::copyFrom(const ActivateOperationDescriptor & object) {
	*data = *object.data;
}

ActivateOperationDescriptor & ActivateOperationDescriptor:: operator=(const ActivateOperationDescriptor & object) {
	copyFrom(object);
	return *this;
}


ActivateOperationDescriptor & ActivateOperationDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool ActivateOperationDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue ActivateOperationDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool ActivateOperationDescriptor::hasType() const {
	return data->Type().present();
}
	
ActivateOperationDescriptor & ActivateOperationDescriptor::setHandle(const std::string & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


std::string ActivateOperationDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
ActivateOperationDescriptor & ActivateOperationDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool ActivateOperationDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter ActivateOperationDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool ActivateOperationDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
ActivateOperationDescriptor & ActivateOperationDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->SafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool ActivateOperationDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->SafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->SafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification ActivateOperationDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->SafetyClassification().get());
}
	
bool ActivateOperationDescriptor::hasSafetyClassification() const {
	return data->SafetyClassification().present();
}
	
ActivateOperationDescriptor & ActivateOperationDescriptor::setOperationTarget(const std::string & value) {
	data->OperationTarget(ConvertToCDM::convert(value));
	return *this;
}


std::string ActivateOperationDescriptor::getOperationTarget() const {
	return ConvertFromCDM::convert(data->OperationTarget());
}
	
ActivateOperationDescriptor & ActivateOperationDescriptor::setActivationDuration(const Duration & value) {
	data->ActivationDuration(ConvertToCDM::convert(value));
	return *this;
}

bool ActivateOperationDescriptor::getActivationDuration(Duration & out) const {
	if (data->ActivationDuration().present()) {
		out = ConvertFromCDM::convert(data->ActivationDuration().get());
		return true;
	}
	return false;
}

Duration ActivateOperationDescriptor::getActivationDuration() const {
	return ConvertFromCDM::convert(data->ActivationDuration().get());
}
	
bool ActivateOperationDescriptor::hasActivationDuration() const {
	return data->ActivationDuration().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

