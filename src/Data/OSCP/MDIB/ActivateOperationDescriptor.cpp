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
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/Argument.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

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
	
ActivateOperationDescriptor & ActivateOperationDescriptor::setHandle(const Handle & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


Handle ActivateOperationDescriptor::getHandle() const {
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
	
ActivateOperationDescriptor & ActivateOperationDescriptor::setOperationTarget(const HandleRef & value) {
	data->OperationTarget(ConvertToCDM::convert(value));
	return *this;
}


HandleRef ActivateOperationDescriptor::getOperationTarget() const {
	return ConvertFromCDM::convert(data->OperationTarget());
}
	
ActivateOperationDescriptor & ActivateOperationDescriptor::setMaxTimeToFinish(const xml_schema::Duration & value) {
	data->MaxTimeToFinish(ConvertToCDM::convert(value));
	return *this;
}

bool ActivateOperationDescriptor::getMaxTimeToFinish(xml_schema::Duration & out) const {
	if (data->MaxTimeToFinish().present()) {
		out = ConvertFromCDM::convert(data->MaxTimeToFinish().get());
		return true;
	}
	return false;
}

xml_schema::Duration ActivateOperationDescriptor::getMaxTimeToFinish() const {
	return ConvertFromCDM::convert(data->MaxTimeToFinish().get());
}
	
bool ActivateOperationDescriptor::hasMaxTimeToFinish() const {
	return data->MaxTimeToFinish().present();
}
	
ActivateOperationDescriptor & ActivateOperationDescriptor::setInvocationEffectiveTimeout(const xml_schema::Duration & value) {
	data->InvocationEffectiveTimeout(ConvertToCDM::convert(value));
	return *this;
}

bool ActivateOperationDescriptor::getInvocationEffectiveTimeout(xml_schema::Duration & out) const {
	if (data->InvocationEffectiveTimeout().present()) {
		out = ConvertFromCDM::convert(data->InvocationEffectiveTimeout().get());
		return true;
	}
	return false;
}

xml_schema::Duration ActivateOperationDescriptor::getInvocationEffectiveTimeout() const {
	return ConvertFromCDM::convert(data->InvocationEffectiveTimeout().get());
}
	
bool ActivateOperationDescriptor::hasInvocationEffectiveTimeout() const {
	return data->InvocationEffectiveTimeout().present();
}
	
ActivateOperationDescriptor & ActivateOperationDescriptor::setRetriggerable(const xml_schema::Duration & value) {
	data->Retriggerable(ConvertToCDM::convert(value));
	return *this;
}

bool ActivateOperationDescriptor::getRetriggerable(xml_schema::Duration & out) const {
	if (data->Retriggerable().present()) {
		out = ConvertFromCDM::convert(data->Retriggerable().get());
		return true;
	}
	return false;
}

xml_schema::Duration ActivateOperationDescriptor::getRetriggerable() const {
	return ConvertFromCDM::convert(data->Retriggerable().get());
}
	
bool ActivateOperationDescriptor::hasRetriggerable() const {
	return data->Retriggerable().present();
}
	
ActivateOperationDescriptor & ActivateOperationDescriptor::addModifiableElement(const std::string & value) {
	data->ModifiableElement().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> ActivateOperationDescriptor::getModifiableElementLists() const {
	std::vector<std::string> result;
	result.reserve(data->ModifiableElement().size());
	for (const auto & value: data->ModifiableElement()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void ActivateOperationDescriptor::clearModifiableElementLists() {
	data->ModifiableElement().clear();
}

ActivateOperationDescriptor & ActivateOperationDescriptor::addArgument(const Argument & value) {
	data->Argument().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<Argument> ActivateOperationDescriptor::getArgumentLists() const {
	std::vector<Argument> result;
	result.reserve(data->Argument().size());
	for (const auto & value: data->Argument()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void ActivateOperationDescriptor::clearArgumentLists() {
	data->Argument().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

