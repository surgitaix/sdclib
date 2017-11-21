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
 *  BatteryDescriptor.cpp
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

#include "OSCLib/Data/OSCP/MDIB/BatteryDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/Measurement.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

namespace OSCLib {
namespace Data {
namespace OSCP {


BatteryDescriptor::BatteryDescriptor(
		Handle handle
) : data(Defaults::BatteryDescriptorInit(
		handle
)) {}

BatteryDescriptor::operator CDM::BatteryDescriptor() const {
	return *data;
}

BatteryDescriptor::BatteryDescriptor(const CDM::BatteryDescriptor & object) : data(new CDM::BatteryDescriptor(object)) {

}

BatteryDescriptor::BatteryDescriptor(const BatteryDescriptor & object) : data(new CDM::BatteryDescriptor(*object.data)) {

}

BatteryDescriptor::~BatteryDescriptor() {

}

void BatteryDescriptor::copyFrom(const BatteryDescriptor & object) {
	*data = *object.data;
}

BatteryDescriptor & BatteryDescriptor:: operator=(const BatteryDescriptor & object) {
	copyFrom(object);
	return *this;
}


BatteryDescriptor & BatteryDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool BatteryDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue BatteryDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool BatteryDescriptor::hasType() const {
	return data->Type().present();
}
	
BatteryDescriptor & BatteryDescriptor::setHandle(const Handle & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


Handle BatteryDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
BatteryDescriptor & BatteryDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool BatteryDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter BatteryDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool BatteryDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
BatteryDescriptor & BatteryDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->SafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool BatteryDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->SafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->SafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification BatteryDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->SafetyClassification().get());
}
	
bool BatteryDescriptor::hasSafetyClassification() const {
	return data->SafetyClassification().present();
}
	
BatteryDescriptor & BatteryDescriptor::setCapacityFullCharge(const Measurement & value) {
	data->CapacityFullCharge(ConvertToCDM::convert(value));
	return *this;
}

bool BatteryDescriptor::getCapacityFullCharge(Measurement & out) const {
	if (data->CapacityFullCharge().present()) {
		out = ConvertFromCDM::convert(data->CapacityFullCharge().get());
		return true;
	}
	return false;
}

Measurement BatteryDescriptor::getCapacityFullCharge() const {
	return ConvertFromCDM::convert(data->CapacityFullCharge().get());
}
	
bool BatteryDescriptor::hasCapacityFullCharge() const {
	return data->CapacityFullCharge().present();
}
	
BatteryDescriptor & BatteryDescriptor::setCapacitySpecified(const Measurement & value) {
	data->CapacitySpecified(ConvertToCDM::convert(value));
	return *this;
}

bool BatteryDescriptor::getCapacitySpecified(Measurement & out) const {
	if (data->CapacitySpecified().present()) {
		out = ConvertFromCDM::convert(data->CapacitySpecified().get());
		return true;
	}
	return false;
}

Measurement BatteryDescriptor::getCapacitySpecified() const {
	return ConvertFromCDM::convert(data->CapacitySpecified().get());
}
	
bool BatteryDescriptor::hasCapacitySpecified() const {
	return data->CapacitySpecified().present();
}
	
BatteryDescriptor & BatteryDescriptor::setVoltageSpecified(const Measurement & value) {
	data->VoltageSpecified(ConvertToCDM::convert(value));
	return *this;
}

bool BatteryDescriptor::getVoltageSpecified(Measurement & out) const {
	if (data->VoltageSpecified().present()) {
		out = ConvertFromCDM::convert(data->VoltageSpecified().get());
		return true;
	}
	return false;
}

Measurement BatteryDescriptor::getVoltageSpecified() const {
	return ConvertFromCDM::convert(data->VoltageSpecified().get());
}
	
bool BatteryDescriptor::hasVoltageSpecified() const {
	return data->VoltageSpecified().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

