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
 *  SetStringOperationDescriptor.cpp
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

#include "SDCLib/Data/SDC/MDIB/SetStringOperationDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


SetStringOperationDescriptor::SetStringOperationDescriptor(
		Handle handle
		,
		HandleRef operationtarget
) : data(Defaults::SetStringOperationDescriptorInit(
		handle
		,
		operationtarget
))
{}

SetStringOperationDescriptor::operator CDM::SetStringOperationDescriptor() const {
	return *data;
}

SetStringOperationDescriptor::SetStringOperationDescriptor(const CDM::SetStringOperationDescriptor & object)
: data(new CDM::SetStringOperationDescriptor(object))
{ }

SetStringOperationDescriptor::SetStringOperationDescriptor(const SetStringOperationDescriptor & object)
: data(std::make_shared<CDM::SetStringOperationDescriptor>(*object.data))
{ }

void SetStringOperationDescriptor::copyFrom(const SetStringOperationDescriptor & object) {
	data = std::make_shared<CDM::SetStringOperationDescriptor>(*object.data);
}

SetStringOperationDescriptor & SetStringOperationDescriptor:: operator=(const SetStringOperationDescriptor& object) {
	copyFrom(object);
	return *this;
}


SetStringOperationDescriptor & SetStringOperationDescriptor::setType(const CodedValue & value) {
	data->setType(ConvertToCDM::convert(value));
	return *this;
}

bool SetStringOperationDescriptor::getType(CodedValue & out) const {
	if (data->getType().present()) {
		out = ConvertFromCDM::convert(data->getType().get());
		return true;
	}
	return false;
}

CodedValue SetStringOperationDescriptor::getType() const {
	return ConvertFromCDM::convert(data->getType().get());
}

bool SetStringOperationDescriptor::hasType() const {
	return data->getType().present();
}

SetStringOperationDescriptor & SetStringOperationDescriptor::setHandle(const Handle & value) {
	data->setHandle(ConvertToCDM::convert(value));
	return *this;
}


Handle SetStringOperationDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->getHandle());
}

SetStringOperationDescriptor & SetStringOperationDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool SetStringOperationDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter SetStringOperationDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool SetStringOperationDescriptor::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

SetStringOperationDescriptor & SetStringOperationDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->setSafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool SetStringOperationDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->getSafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->getSafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification SetStringOperationDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->getSafetyClassification().get());
}

bool SetStringOperationDescriptor::hasSafetyClassification() const {
	return data->getSafetyClassification().present();
}

SetStringOperationDescriptor & SetStringOperationDescriptor::setOperationTarget(const HandleRef & value) {
	data->setOperationTarget(ConvertToCDM::convert(value));
	return *this;
}


HandleRef SetStringOperationDescriptor::getOperationTarget() const {
	return ConvertFromCDM::convert(data->getOperationTarget());
}

SetStringOperationDescriptor & SetStringOperationDescriptor::setMaxTimeToFinish(const xml_schema::Duration & value) {
	data->setMaxTimeToFinish(ConvertToCDM::convert(value));
	return *this;
}

bool SetStringOperationDescriptor::getMaxTimeToFinish(xml_schema::Duration & out) const {
	if (data->getMaxTimeToFinish().present()) {
		out = ConvertFromCDM::convert(data->getMaxTimeToFinish().get());
		return true;
	}
	return false;
}

xml_schema::Duration SetStringOperationDescriptor::getMaxTimeToFinish() const {
	return ConvertFromCDM::convert(data->getMaxTimeToFinish().get());
}

bool SetStringOperationDescriptor::hasMaxTimeToFinish() const {
	return data->getMaxTimeToFinish().present();
}

SetStringOperationDescriptor & SetStringOperationDescriptor::setInvocationEffectiveTimeout(const xml_schema::Duration & value) {
	data->setInvocationEffectiveTimeout(ConvertToCDM::convert(value));
	return *this;
}

bool SetStringOperationDescriptor::getInvocationEffectiveTimeout(xml_schema::Duration & out) const {
	if (data->getInvocationEffectiveTimeout().present()) {
		out = ConvertFromCDM::convert(data->getInvocationEffectiveTimeout().get());
		return true;
	}
	return false;
}

xml_schema::Duration SetStringOperationDescriptor::getInvocationEffectiveTimeout() const {
	return ConvertFromCDM::convert(data->getInvocationEffectiveTimeout().get());
}

bool SetStringOperationDescriptor::hasInvocationEffectiveTimeout() const {
	return data->getInvocationEffectiveTimeout().present();
}

SetStringOperationDescriptor & SetStringOperationDescriptor::setRetriggerable(const bool & value) {
	data->setRetriggerable(ConvertToCDM::convert(value));
	return *this;
}

bool SetStringOperationDescriptor::getRetriggerable(bool & out) const {
	if (data->getRetriggerable().present()) {
		out = ConvertFromCDM::convert(data->getRetriggerable().get());
		return true;
	}
	return false;
}

bool SetStringOperationDescriptor::getRetriggerable() const {
	return ConvertFromCDM::convert(data->getRetriggerable().get());
}

bool SetStringOperationDescriptor::hasRetriggerable() const {
	return data->getRetriggerable().present();
}

SetStringOperationDescriptor & SetStringOperationDescriptor::setAccessLevel(const AccessLevel & value) {
	data->setAccessLevel(ConvertToCDM::convert(value));
	return *this;
}

bool SetStringOperationDescriptor::getAccessLevel(AccessLevel & out) const {
	if (data->getAccessLevel().present()) {
		out = ConvertFromCDM::convert(data->getAccessLevel().get());
		return true;
	}
	return false;
}

AccessLevel SetStringOperationDescriptor::getAccessLevel() const {
	return ConvertFromCDM::convert(data->getAccessLevel().get());
}

bool SetStringOperationDescriptor::hasAccessLevel() const {
	return data->getAccessLevel().present();
}

SetStringOperationDescriptor & SetStringOperationDescriptor::setMaxLength(const unsigned long long & value) {
	data->setMaxLength(ConvertToCDM::convert(value));
	return *this;
}

bool SetStringOperationDescriptor::getMaxLength(unsigned long long & out) const {
	if (data->getMaxLength().present()) {
		out = ConvertFromCDM::convert(data->getMaxLength().get());
		return true;
	}
	return false;
}

unsigned long long SetStringOperationDescriptor::getMaxLength() const {
	return ConvertFromCDM::convert(data->getMaxLength().get());
}

bool SetStringOperationDescriptor::hasMaxLength() const {
	return data->getMaxLength().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

