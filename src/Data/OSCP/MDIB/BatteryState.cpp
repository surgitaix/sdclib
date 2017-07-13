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
 *  BatteryState.cpp
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

#include "OSCLib/Data/OSCP/MDIB/BatteryState.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/Measurement.h"
#include "OSCLib/Data/OSCP/MDIB/CalibrationInfo.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

BatteryState::BatteryState() : data(Defaults::BatteryState()) {
}

BatteryState::operator CDM::BatteryState() const {
	return *data;
}

BatteryState::BatteryState(const CDM::BatteryState & object) : data(new CDM::BatteryState(object)) {

}

BatteryState::BatteryState(const BatteryState & object) : data(new CDM::BatteryState(*object.data)) {

}

BatteryState::~BatteryState() {

}

void BatteryState::copyFrom(const BatteryState & object) {
	*data = *object.data;
}

BatteryState & BatteryState:: operator=(const BatteryState & object) {
	copyFrom(object);
	return *this;
}


BatteryState & BatteryState::setStateVersion(const VersionCounter & value) {
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}


VersionCounter BatteryState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion());
}
	
BatteryState & BatteryState::setDescriptorHandle(const HandleRef & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef BatteryState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
}
	
BatteryState & BatteryState::setDescriptorVersion(const ReferencedVersion & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}


ReferencedVersion BatteryState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion());
}
	
BatteryState & BatteryState::setCalibrationInfo(const CalibrationInfo & value) {
	data->CalibrationInfo(ConvertToCDM::convert(value));
	return *this;
}

bool BatteryState::getCalibrationInfo(CalibrationInfo & out) const {
	if (data->CalibrationInfo().present()) {
		out = ConvertFromCDM::convert(data->CalibrationInfo().get());
		return true;
	}
	return false;
}

CalibrationInfo BatteryState::getCalibrationInfo() const {
	return ConvertFromCDM::convert(data->CalibrationInfo().get());
}
	
bool BatteryState::hasCalibrationInfo() const {
	return data->CalibrationInfo().present();
}
	
BatteryState & BatteryState::setNextCalibration(const CalibrationInfo & value) {
	data->NextCalibration(ConvertToCDM::convert(value));
	return *this;
}

bool BatteryState::getNextCalibration(CalibrationInfo & out) const {
	if (data->NextCalibration().present()) {
		out = ConvertFromCDM::convert(data->NextCalibration().get());
		return true;
	}
	return false;
}

CalibrationInfo BatteryState::getNextCalibration() const {
	return ConvertFromCDM::convert(data->NextCalibration().get());
}
	
bool BatteryState::hasNextCalibration() const {
	return data->NextCalibration().present();
}
	
BatteryState & BatteryState::setActivationState(const ComponentActivation & value) {
	data->ActivationState(ConvertToCDM::convert(value));
	return *this;
}


ComponentActivation BatteryState::getActivationState() const {
	return ConvertFromCDM::convert(data->ActivationState());
}
	
BatteryState & BatteryState::setOperatingHours(const unsigned int & value) {
	data->OperatingHours(ConvertToCDM::convert(value));
	return *this;
}


unsigned int BatteryState::getOperatingHours() const {
	return ConvertFromCDM::convert(data->OperatingHours());
}
	
BatteryState & BatteryState::setOperatingCycles(const int & value) {
	data->OperatingCycles(ConvertToCDM::convert(value));
	return *this;
}


int BatteryState::getOperatingCycles() const {
	return ConvertFromCDM::convert(data->OperatingCycles());
}
	
BatteryState & BatteryState::setCapacityRemaining(const Measurement & value) {
	data->CapacityRemaining(ConvertToCDM::convert(value));
	return *this;
}

bool BatteryState::getCapacityRemaining(Measurement & out) const {
	if (data->CapacityRemaining().present()) {
		out = ConvertFromCDM::convert(data->CapacityRemaining().get());
		return true;
	}
	return false;
}

Measurement BatteryState::getCapacityRemaining() const {
	return ConvertFromCDM::convert(data->CapacityRemaining().get());
}
	
bool BatteryState::hasCapacityRemaining() const {
	return data->CapacityRemaining().present();
}
	
BatteryState & BatteryState::setVoltage(const Measurement & value) {
	data->Voltage(ConvertToCDM::convert(value));
	return *this;
}

bool BatteryState::getVoltage(Measurement & out) const {
	if (data->Voltage().present()) {
		out = ConvertFromCDM::convert(data->Voltage().get());
		return true;
	}
	return false;
}

Measurement BatteryState::getVoltage() const {
	return ConvertFromCDM::convert(data->Voltage().get());
}
	
bool BatteryState::hasVoltage() const {
	return data->Voltage().present();
}
	
BatteryState & BatteryState::setCurrent(const Measurement & value) {
	data->Current(ConvertToCDM::convert(value));
	return *this;
}

bool BatteryState::getCurrent(Measurement & out) const {
	if (data->Current().present()) {
		out = ConvertFromCDM::convert(data->Current().get());
		return true;
	}
	return false;
}

Measurement BatteryState::getCurrent() const {
	return ConvertFromCDM::convert(data->Current().get());
}
	
bool BatteryState::hasCurrent() const {
	return data->Current().present();
}
	
BatteryState & BatteryState::setTemperature(const Measurement & value) {
	data->Temperature(ConvertToCDM::convert(value));
	return *this;
}

bool BatteryState::getTemperature(Measurement & out) const {
	if (data->Temperature().present()) {
		out = ConvertFromCDM::convert(data->Temperature().get());
		return true;
	}
	return false;
}

Measurement BatteryState::getTemperature() const {
	return ConvertFromCDM::convert(data->Temperature().get());
}
	
bool BatteryState::hasTemperature() const {
	return data->Temperature().present();
}
	
BatteryState & BatteryState::setRemainingBatteryTime(const Measurement & value) {
	data->RemainingBatteryTime(ConvertToCDM::convert(value));
	return *this;
}

bool BatteryState::getRemainingBatteryTime(Measurement & out) const {
	if (data->RemainingBatteryTime().present()) {
		out = ConvertFromCDM::convert(data->RemainingBatteryTime().get());
		return true;
	}
	return false;
}

Measurement BatteryState::getRemainingBatteryTime() const {
	return ConvertFromCDM::convert(data->RemainingBatteryTime().get());
}
	
bool BatteryState::hasRemainingBatteryTime() const {
	return data->RemainingBatteryTime().present();
}
	
BatteryState & BatteryState::setChargeStatus(const ChargeStatusType & value) {
	data->ChargeStatus(ConvertToCDM::convert(value));
	return *this;
}


ChargeStatusType BatteryState::getChargeStatus() const {
	return ConvertFromCDM::convert(data->ChargeStatus());
}
	
BatteryState & BatteryState::setChargeCycles(const unsigned int & value) {
	data->ChargeCycles(ConvertToCDM::convert(value));
	return *this;
}


unsigned int BatteryState::getChargeCycles() const {
	return ConvertFromCDM::convert(data->ChargeCycles());
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

