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
 *  AlertSignalDescriptor.cpp
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

#include "SDCLib/Data/SDC/MDIB/AlertSignalDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


AlertSignalDescriptor::AlertSignalDescriptor(
		Handle handle
		,
		AlertSignalManifestation manifestation
		,
		bool latching
) : data(Defaults::AlertSignalDescriptorInit(
		handle
		,
		manifestation
		,
		latching
)) {}

AlertSignalDescriptor::operator CDM::AlertSignalDescriptor() const {
	return *data;
}

AlertSignalDescriptor::AlertSignalDescriptor(const CDM::AlertSignalDescriptor & object) : data(new CDM::AlertSignalDescriptor(object)) {

}

AlertSignalDescriptor::AlertSignalDescriptor(const AlertSignalDescriptor & object) : data(new CDM::AlertSignalDescriptor(*object.data)) {

}

AlertSignalDescriptor::~AlertSignalDescriptor() {

}

void AlertSignalDescriptor::copyFrom(const AlertSignalDescriptor & object) {
	data = std::shared_ptr<CDM::AlertSignalDescriptor>( new CDM::AlertSignalDescriptor(*object.data));
}

AlertSignalDescriptor & AlertSignalDescriptor:: operator=(const AlertSignalDescriptor & object) {
	copyFrom(object);
	return *this;
}


AlertSignalDescriptor & AlertSignalDescriptor::setType(const CodedValue & value) {
	data->setType(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSignalDescriptor::getType(CodedValue & out) const {
	if (data->getType().present()) {
		out = ConvertFromCDM::convert(data->getType().get());
		return true;
	}
	return false;
}

CodedValue AlertSignalDescriptor::getType() const {
	return ConvertFromCDM::convert(data->getType().get());
}

bool AlertSignalDescriptor::hasType() const {
	return data->getType().present();
}

AlertSignalDescriptor & AlertSignalDescriptor::setHandle(const Handle & value) {
	data->setHandle(ConvertToCDM::convert(value));
	return *this;
}


Handle AlertSignalDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->getHandle());
}

AlertSignalDescriptor & AlertSignalDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSignalDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter AlertSignalDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool AlertSignalDescriptor::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

AlertSignalDescriptor & AlertSignalDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->setSafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSignalDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->getSafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->getSafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification AlertSignalDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->getSafetyClassification().get());
}

bool AlertSignalDescriptor::hasSafetyClassification() const {
	return data->getSafetyClassification().present();
}

AlertSignalDescriptor & AlertSignalDescriptor::setConditionSignaled(const HandleRef & value) {
	data->setConditionSignaled(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSignalDescriptor::getConditionSignaled(HandleRef & out) const {
	if (data->getConditionSignaled().present()) {
		out = ConvertFromCDM::convert(data->getConditionSignaled().get());
		return true;
	}
	return false;
}

HandleRef AlertSignalDescriptor::getConditionSignaled() const {
	return ConvertFromCDM::convert(data->getConditionSignaled().get());
}

bool AlertSignalDescriptor::hasConditionSignaled() const {
	return data->getConditionSignaled().present();
}

AlertSignalDescriptor & AlertSignalDescriptor::setManifestation(const AlertSignalManifestation & value) {
	data->setManifestation(ConvertToCDM::convert(value));
	return *this;
}


AlertSignalManifestation AlertSignalDescriptor::getManifestation() const {
	return ConvertFromCDM::convert(data->getManifestation());
}

AlertSignalDescriptor & AlertSignalDescriptor::setLatching(const bool & value) {
	data->setLatching(ConvertToCDM::convert(value));
	return *this;
}


bool AlertSignalDescriptor::getLatching() const {
	return ConvertFromCDM::convert(data->getLatching());
}

AlertSignalDescriptor & AlertSignalDescriptor::setDefaultSignalGenerationDelay(const xml_schema::Duration & value) {
	data->setDefaultSignalGenerationDelay(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSignalDescriptor::getDefaultSignalGenerationDelay(xml_schema::Duration & out) const {
	if (data->getDefaultSignalGenerationDelay().present()) {
		out = ConvertFromCDM::convert(data->getDefaultSignalGenerationDelay().get());
		return true;
	}
	return false;
}

xml_schema::Duration AlertSignalDescriptor::getDefaultSignalGenerationDelay() const {
	return ConvertFromCDM::convert(data->getDefaultSignalGenerationDelay().get());
}

bool AlertSignalDescriptor::hasDefaultSignalGenerationDelay() const {
	return data->getDefaultSignalGenerationDelay().present();
}

AlertSignalDescriptor & AlertSignalDescriptor::setMinSignalGenerationDelay(const xml_schema::Duration & value) {
	data->setMinSignalGenerationDelay(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSignalDescriptor::getMinSignalGenerationDelay(xml_schema::Duration & out) const {
	if (data->getMinSignalGenerationDelay().present()) {
		out = ConvertFromCDM::convert(data->getMinSignalGenerationDelay().get());
		return true;
	}
	return false;
}

xml_schema::Duration AlertSignalDescriptor::getMinSignalGenerationDelay() const {
	return ConvertFromCDM::convert(data->getMinSignalGenerationDelay().get());
}

bool AlertSignalDescriptor::hasMinSignalGenerationDelay() const {
	return data->getMinSignalGenerationDelay().present();
}

AlertSignalDescriptor & AlertSignalDescriptor::setMaxSignalGenerationDelay(const xml_schema::Duration & value) {
	data->setMaxSignalGenerationDelay(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSignalDescriptor::getMaxSignalGenerationDelay(xml_schema::Duration & out) const {
	if (data->getMaxSignalGenerationDelay().present()) {
		out = ConvertFromCDM::convert(data->getMaxSignalGenerationDelay().get());
		return true;
	}
	return false;
}

xml_schema::Duration AlertSignalDescriptor::getMaxSignalGenerationDelay() const {
	return ConvertFromCDM::convert(data->getMaxSignalGenerationDelay().get());
}

bool AlertSignalDescriptor::hasMaxSignalGenerationDelay() const {
	return data->getMaxSignalGenerationDelay().present();
}

AlertSignalDescriptor & AlertSignalDescriptor::setSignalDelegationSupported(const bool & value) {
	data->setSignalDelegationSupported(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSignalDescriptor::getSignalDelegationSupported(bool & out) const {
	if (data->getSignalDelegationSupported().present()) {
		out = ConvertFromCDM::convert(data->getSignalDelegationSupported().get());
		return true;
	}
	return false;
}

bool AlertSignalDescriptor::getSignalDelegationSupported() const {
	return ConvertFromCDM::convert(data->getSignalDelegationSupported().get());
}

bool AlertSignalDescriptor::hasSignalDelegationSupported() const {
	return data->getSignalDelegationSupported().present();
}

AlertSignalDescriptor & AlertSignalDescriptor::setAcknowledgementSupported(const bool & value) {
	data->setAcknowledgementSupported(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSignalDescriptor::getAcknowledgementSupported(bool & out) const {
	if (data->getAcknowledgementSupported().present()) {
		out = ConvertFromCDM::convert(data->getAcknowledgementSupported().get());
		return true;
	}
	return false;
}

bool AlertSignalDescriptor::getAcknowledgementSupported() const {
	return ConvertFromCDM::convert(data->getAcknowledgementSupported().get());
}

bool AlertSignalDescriptor::hasAcknowledgementSupported() const {
	return data->getAcknowledgementSupported().present();
}

AlertSignalDescriptor & AlertSignalDescriptor::setAcknowledgeTimeout(const xml_schema::Duration & value) {
	data->setAcknowledgeTimeout(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSignalDescriptor::getAcknowledgeTimeout(xml_schema::Duration & out) const {
	if (data->getAcknowledgeTimeout().present()) {
		out = ConvertFromCDM::convert(data->getAcknowledgeTimeout().get());
		return true;
	}
	return false;
}

xml_schema::Duration AlertSignalDescriptor::getAcknowledgeTimeout() const {
	return ConvertFromCDM::convert(data->getAcknowledgeTimeout().get());
}

bool AlertSignalDescriptor::hasAcknowledgeTimeout() const {
	return data->getAcknowledgeTimeout().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

