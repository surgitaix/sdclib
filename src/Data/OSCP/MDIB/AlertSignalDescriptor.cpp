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
 *  Author: besting, roehser
 */
 
/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 * 
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "OSCLib/Data/OSCP/MDIB/AlertSignalDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

AlertSignalDescriptor::AlertSignalDescriptor() : data(Defaults::AlertSignalDescriptor()) {
}

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
	*data = *object.data;
}

AlertSignalDescriptor & AlertSignalDescriptor:: operator=(const AlertSignalDescriptor & object) {
	copyFrom(object);
	return *this;
}


AlertSignalDescriptor & AlertSignalDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSignalDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue AlertSignalDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool AlertSignalDescriptor::hasType() const {
	return data->Type().present();
}
	
AlertSignalDescriptor & AlertSignalDescriptor::setHandle(const Handle & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


Handle AlertSignalDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
AlertSignalDescriptor & AlertSignalDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSignalDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter AlertSignalDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool AlertSignalDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
AlertSignalDescriptor & AlertSignalDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->SafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSignalDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->SafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->SafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification AlertSignalDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->SafetyClassification().get());
}
	
bool AlertSignalDescriptor::hasSafetyClassification() const {
	return data->SafetyClassification().present();
}
	
AlertSignalDescriptor & AlertSignalDescriptor::setConditionSignaled(const HandleRef & value) {
	data->ConditionSignaled(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSignalDescriptor::getConditionSignaled(HandleRef & out) const {
	if (data->ConditionSignaled().present()) {
		out = ConvertFromCDM::convert(data->ConditionSignaled().get());
		return true;
	}
	return false;
}

HandleRef AlertSignalDescriptor::getConditionSignaled() const {
	return ConvertFromCDM::convert(data->ConditionSignaled().get());
}
	
bool AlertSignalDescriptor::hasConditionSignaled() const {
	return data->ConditionSignaled().present();
}
	
AlertSignalDescriptor & AlertSignalDescriptor::setManifestation(const AlertSignalManifestation & value) {
	data->Manifestation(ConvertToCDM::convert(value));
	return *this;
}


AlertSignalManifestation AlertSignalDescriptor::getManifestation() const {
	return ConvertFromCDM::convert(data->Manifestation());
}
	
AlertSignalDescriptor & AlertSignalDescriptor::setLatching(const bool & value) {
	data->Latching(ConvertToCDM::convert(value));
	return *this;
}


bool AlertSignalDescriptor::getLatching() const {
	return ConvertFromCDM::convert(data->Latching());
}
	
AlertSignalDescriptor & AlertSignalDescriptor::setDefaultSignalGenerationDelay(const xml_schema::Duration & value) {
	data->DefaultSignalGenerationDelay(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSignalDescriptor::getDefaultSignalGenerationDelay(xml_schema::Duration & out) const {
	if (data->DefaultSignalGenerationDelay().present()) {
		out = ConvertFromCDM::convert(data->DefaultSignalGenerationDelay().get());
		return true;
	}
	return false;
}

xml_schema::Duration AlertSignalDescriptor::getDefaultSignalGenerationDelay() const {
	return ConvertFromCDM::convert(data->DefaultSignalGenerationDelay().get());
}
	
bool AlertSignalDescriptor::hasDefaultSignalGenerationDelay() const {
	return data->DefaultSignalGenerationDelay().present();
}
	
AlertSignalDescriptor & AlertSignalDescriptor::setMinSignalGenerationDelay(const xml_schema::Duration & value) {
	data->MinSignalGenerationDelay(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSignalDescriptor::getMinSignalGenerationDelay(xml_schema::Duration & out) const {
	if (data->MinSignalGenerationDelay().present()) {
		out = ConvertFromCDM::convert(data->MinSignalGenerationDelay().get());
		return true;
	}
	return false;
}

xml_schema::Duration AlertSignalDescriptor::getMinSignalGenerationDelay() const {
	return ConvertFromCDM::convert(data->MinSignalGenerationDelay().get());
}
	
bool AlertSignalDescriptor::hasMinSignalGenerationDelay() const {
	return data->MinSignalGenerationDelay().present();
}
	
AlertSignalDescriptor & AlertSignalDescriptor::setMaxSignalGenerationDelay(const xml_schema::Duration & value) {
	data->MaxSignalGenerationDelay(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSignalDescriptor::getMaxSignalGenerationDelay(xml_schema::Duration & out) const {
	if (data->MaxSignalGenerationDelay().present()) {
		out = ConvertFromCDM::convert(data->MaxSignalGenerationDelay().get());
		return true;
	}
	return false;
}

xml_schema::Duration AlertSignalDescriptor::getMaxSignalGenerationDelay() const {
	return ConvertFromCDM::convert(data->MaxSignalGenerationDelay().get());
}
	
bool AlertSignalDescriptor::hasMaxSignalGenerationDelay() const {
	return data->MaxSignalGenerationDelay().present();
}
	
AlertSignalDescriptor & AlertSignalDescriptor::setSignalDelegationSupported(const bool & value) {
	data->SignalDelegationSupported(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSignalDescriptor::getSignalDelegationSupported(bool & out) const {
	if (data->SignalDelegationSupported().present()) {
		out = ConvertFromCDM::convert(data->SignalDelegationSupported().get());
		return true;
	}
	return false;
}

bool AlertSignalDescriptor::getSignalDelegationSupported() const {
	return ConvertFromCDM::convert(data->SignalDelegationSupported().get());
}
	
bool AlertSignalDescriptor::hasSignalDelegationSupported() const {
	return data->SignalDelegationSupported().present();
}
	
AlertSignalDescriptor & AlertSignalDescriptor::setAcknowledgementSupported(const bool & value) {
	data->AcknowledgementSupported(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSignalDescriptor::getAcknowledgementSupported(bool & out) const {
	if (data->AcknowledgementSupported().present()) {
		out = ConvertFromCDM::convert(data->AcknowledgementSupported().get());
		return true;
	}
	return false;
}

bool AlertSignalDescriptor::getAcknowledgementSupported() const {
	return ConvertFromCDM::convert(data->AcknowledgementSupported().get());
}
	
bool AlertSignalDescriptor::hasAcknowledgementSupported() const {
	return data->AcknowledgementSupported().present();
}
	
AlertSignalDescriptor & AlertSignalDescriptor::setAcknowledgeTimeout(const xml_schema::Duration & value) {
	data->AcknowledgeTimeout(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSignalDescriptor::getAcknowledgeTimeout(xml_schema::Duration & out) const {
	if (data->AcknowledgeTimeout().present()) {
		out = ConvertFromCDM::convert(data->AcknowledgeTimeout().get());
		return true;
	}
	return false;
}

xml_schema::Duration AlertSignalDescriptor::getAcknowledgeTimeout() const {
	return ConvertFromCDM::convert(data->AcknowledgeTimeout().get());
}
	
bool AlertSignalDescriptor::hasAcknowledgeTimeout() const {
	return data->AcknowledgeTimeout().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

