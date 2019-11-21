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
 *  SetMetricStateOperationDescriptor.cpp
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

#include "SDCLib/Data/SDC/MDIB/SetMetricStateOperationDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


SetMetricStateOperationDescriptor::SetMetricStateOperationDescriptor(
		Handle handle
		,
		HandleRef operationtarget
) : data(Defaults::SetMetricStateOperationDescriptorInit(
		handle
		,
		operationtarget
))
{}

SetMetricStateOperationDescriptor::operator CDM::SetMetricStateOperationDescriptor() const {
	return *data;
}

SetMetricStateOperationDescriptor::SetMetricStateOperationDescriptor(const CDM::SetMetricStateOperationDescriptor & object)
: data(new CDM::SetMetricStateOperationDescriptor(object))
{ }

SetMetricStateOperationDescriptor::SetMetricStateOperationDescriptor(const SetMetricStateOperationDescriptor & object)
: data(std::make_shared<CDM::SetMetricStateOperationDescriptor>(*object.data))
{ }

void SetMetricStateOperationDescriptor::copyFrom(const SetMetricStateOperationDescriptor & object) {
	data = std::make_shared<CDM::SetMetricStateOperationDescriptor>(*object.data);
}

SetMetricStateOperationDescriptor & SetMetricStateOperationDescriptor:: operator=(const SetMetricStateOperationDescriptor& object) {
	copyFrom(object);
	return *this;
}


SetMetricStateOperationDescriptor & SetMetricStateOperationDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool SetMetricStateOperationDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue SetMetricStateOperationDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}

bool SetMetricStateOperationDescriptor::hasType() const {
	return data->Type().present();
}

SetMetricStateOperationDescriptor & SetMetricStateOperationDescriptor::setHandle(const Handle & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


Handle SetMetricStateOperationDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}

SetMetricStateOperationDescriptor & SetMetricStateOperationDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool SetMetricStateOperationDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter SetMetricStateOperationDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}

bool SetMetricStateOperationDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}

SetMetricStateOperationDescriptor & SetMetricStateOperationDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->SafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool SetMetricStateOperationDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->SafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->SafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification SetMetricStateOperationDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->SafetyClassification().get());
}

bool SetMetricStateOperationDescriptor::hasSafetyClassification() const {
	return data->SafetyClassification().present();
}

SetMetricStateOperationDescriptor & SetMetricStateOperationDescriptor::setOperationTarget(const HandleRef & value) {
	data->OperationTarget(ConvertToCDM::convert(value));
	return *this;
}


HandleRef SetMetricStateOperationDescriptor::getOperationTarget() const {
	return ConvertFromCDM::convert(data->OperationTarget());
}

SetMetricStateOperationDescriptor & SetMetricStateOperationDescriptor::setMaxTimeToFinish(const xml_schema::Duration & value) {
	data->MaxTimeToFinish(ConvertToCDM::convert(value));
	return *this;
}

bool SetMetricStateOperationDescriptor::getMaxTimeToFinish(xml_schema::Duration & out) const {
	if (data->MaxTimeToFinish().present()) {
		out = ConvertFromCDM::convert(data->MaxTimeToFinish().get());
		return true;
	}
	return false;
}

xml_schema::Duration SetMetricStateOperationDescriptor::getMaxTimeToFinish() const {
	return ConvertFromCDM::convert(data->MaxTimeToFinish().get());
}

bool SetMetricStateOperationDescriptor::hasMaxTimeToFinish() const {
	return data->MaxTimeToFinish().present();
}

SetMetricStateOperationDescriptor & SetMetricStateOperationDescriptor::setInvocationEffectiveTimeout(const xml_schema::Duration & value) {
	data->InvocationEffectiveTimeout(ConvertToCDM::convert(value));
	return *this;
}

bool SetMetricStateOperationDescriptor::getInvocationEffectiveTimeout(xml_schema::Duration & out) const {
	if (data->InvocationEffectiveTimeout().present()) {
		out = ConvertFromCDM::convert(data->InvocationEffectiveTimeout().get());
		return true;
	}
	return false;
}

xml_schema::Duration SetMetricStateOperationDescriptor::getInvocationEffectiveTimeout() const {
	return ConvertFromCDM::convert(data->InvocationEffectiveTimeout().get());
}

bool SetMetricStateOperationDescriptor::hasInvocationEffectiveTimeout() const {
	return data->InvocationEffectiveTimeout().present();
}

SetMetricStateOperationDescriptor & SetMetricStateOperationDescriptor::setRetriggerable(const bool & value) {
	data->Retriggerable(ConvertToCDM::convert(value));
	return *this;
}

bool SetMetricStateOperationDescriptor::getRetriggerable(bool & out) const {
	if (data->Retriggerable().present()) {
		out = ConvertFromCDM::convert(data->Retriggerable().get());
		return true;
	}
	return false;
}

bool SetMetricStateOperationDescriptor::getRetriggerable() const {
	return ConvertFromCDM::convert(data->Retriggerable().get());
}

bool SetMetricStateOperationDescriptor::hasRetriggerable() const {
	return data->Retriggerable().present();
}

SetMetricStateOperationDescriptor & SetMetricStateOperationDescriptor::setAccessLevel(const AccessLevel & value) {
	data->AccessLevel(ConvertToCDM::convert(value));
	return *this;
}

bool SetMetricStateOperationDescriptor::getAccessLevel(AccessLevel & out) const {
	if (data->AccessLevel().present()) {
		out = ConvertFromCDM::convert(data->AccessLevel().get());
		return true;
	}
	return false;
}

AccessLevel SetMetricStateOperationDescriptor::getAccessLevel() const {
	return ConvertFromCDM::convert(data->AccessLevel().get());
}

bool SetMetricStateOperationDescriptor::hasAccessLevel() const {
	return data->AccessLevel().present();
}

SetMetricStateOperationDescriptor & SetMetricStateOperationDescriptor::addModifiableData(const std::string & value) {
	data->ModifiableData().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> SetMetricStateOperationDescriptor::getModifiableDataList() const {
	std::vector<std::string> result;
	result.reserve(data->ModifiableData().size());
	for (const auto & value: data->ModifiableData()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void SetMetricStateOperationDescriptor::clearModifiableDataList() {
	data->ModifiableData().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

