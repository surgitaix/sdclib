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
 *  Author: besting, buerger, roehser
 */

/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 *
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "SDCLib/Data/SDC/MDIB/BatteryState.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/Measurement.h"
#include "SDCLib/Data/SDC/MDIB/CalibrationInfo.h"
#include "SDCLib/Data/SDC/MDIB/PhysicalConnectorInfo.h"

namespace SDCLib {
namespace Data {
namespace SDC {


BatteryState::BatteryState(
		HandleRef descriptorhandle
) : data(Defaults::BatteryStateInit(
		descriptorhandle
))
{}

BatteryState::operator CDM::BatteryState() const {
	return *data;
}

BatteryState::BatteryState(const CDM::BatteryState & object)
: data(new CDM::BatteryState(object))
{ }

BatteryState::BatteryState(const BatteryState & object)
: data(std::make_shared<CDM::BatteryState>(*object.data))
{ }

void BatteryState::copyFrom(const BatteryState & object) {
	data = std::make_shared<CDM::BatteryState>(*object.data);
}

BatteryState & BatteryState:: operator=(const BatteryState& object) {
	copyFrom(object);
	return *this;
}


BatteryState & BatteryState::setStateVersion(const VersionCounter & value) {
	data->setStateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool BatteryState::getStateVersion(VersionCounter & out) const {
	if (data->getStateVersion().present()) {
		out = ConvertFromCDM::convert(data->getStateVersion().get());
		return true;
	}
	return false;
}

VersionCounter BatteryState::getStateVersion() const {
	return ConvertFromCDM::convert(data->getStateVersion().get());
}

bool BatteryState::hasStateVersion() const {
	return data->getStateVersion().present();
}

BatteryState & BatteryState::setDescriptorHandle(const HandleRef & value) {
	data->setDescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef BatteryState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->getDescriptorHandle());
}

BatteryState & BatteryState::setDescriptorVersion(const ReferencedVersion & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool BatteryState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion BatteryState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool BatteryState::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

BatteryState & BatteryState::setCalibrationInfo(const CalibrationInfo & value) {
	data->setCalibrationInfo(ConvertToCDM::convert(value));
	return *this;
}

bool BatteryState::getCalibrationInfo(CalibrationInfo & out) const {
	if (data->getCalibrationInfo().present()) {
		out = ConvertFromCDM::convert(data->getCalibrationInfo().get());
		return true;
	}
	return false;
}

CalibrationInfo BatteryState::getCalibrationInfo() const {
	return ConvertFromCDM::convert(data->getCalibrationInfo().get());
}

bool BatteryState::hasCalibrationInfo() const {
	return data->getCalibrationInfo().present();
}

BatteryState & BatteryState::setNextCalibration(const CalibrationInfo & value) {
	data->setNextCalibration(ConvertToCDM::convert(value));
	return *this;
}

bool BatteryState::getNextCalibration(CalibrationInfo & out) const {
	if (data->getNextCalibration().present()) {
		out = ConvertFromCDM::convert(data->getNextCalibration().get());
		return true;
	}
	return false;
}

CalibrationInfo BatteryState::getNextCalibration() const {
	return ConvertFromCDM::convert(data->getNextCalibration().get());
}

bool BatteryState::hasNextCalibration() const {
	return data->getNextCalibration().present();
}

BatteryState & BatteryState::setPhysicalConnector(const PhysicalConnectorInfo & value) {
	data->setPhysicalConnector(ConvertToCDM::convert(value));
	return *this;
}

bool BatteryState::getPhysicalConnector(PhysicalConnectorInfo & out) const {
	if (data->getPhysicalConnector().present()) {
		out = ConvertFromCDM::convert(data->getPhysicalConnector().get());
		return true;
	}
	return false;
}

PhysicalConnectorInfo BatteryState::getPhysicalConnector() const {
	return ConvertFromCDM::convert(data->getPhysicalConnector().get());
}

bool BatteryState::hasPhysicalConnector() const {
	return data->getPhysicalConnector().present();
}

BatteryState & BatteryState::setActivationState(const ComponentActivation & value) {
	data->setActivationState(ConvertToCDM::convert(value));
	return *this;
}

bool BatteryState::getActivationState(ComponentActivation & out) const {
	if (data->getActivationState().present()) {
		out = ConvertFromCDM::convert(data->getActivationState().get());
		return true;
	}
	return false;
}

ComponentActivation BatteryState::getActivationState() const {
	return ConvertFromCDM::convert(data->getActivationState().get());
}

bool BatteryState::hasActivationState() const {
	return data->getActivationState().present();
}

BatteryState & BatteryState::setOperatingHours(const unsigned int & value) {
	data->setOperatingHours(ConvertToCDM::convert(value));
	return *this;
}

bool BatteryState::getOperatingHours(unsigned int & out) const {
	if (data->getOperatingHours().present()) {
		out = ConvertFromCDM::convert(data->getOperatingHours().get());
		return true;
	}
	return false;
}

unsigned int BatteryState::getOperatingHours() const {
	return ConvertFromCDM::convert(data->getOperatingHours().get());
}

bool BatteryState::hasOperatingHours() const {
	return data->getOperatingHours().present();
}

BatteryState & BatteryState::setOperatingCycles(const int & value) {
	data->setOperatingCycles(ConvertToCDM::convert(value));
	return *this;
}

bool BatteryState::getOperatingCycles(int & out) const {
	if (data->getOperatingCycles().present()) {
		out = ConvertFromCDM::convert(data->getOperatingCycles().get());
		return true;
	}
	return false;
}

int BatteryState::getOperatingCycles() const {
	return ConvertFromCDM::convert(data->getOperatingCycles().get());
}

bool BatteryState::hasOperatingCycles() const {
	return data->getOperatingCycles().present();
}

BatteryState & BatteryState::setCapacityRemaining(const Measurement & value) {
	data->setCapacityRemaining(ConvertToCDM::convert(value));
	return *this;
}

bool BatteryState::getCapacityRemaining(Measurement & out) const {
	if (data->getCapacityRemaining().present()) {
		out = ConvertFromCDM::convert(data->getCapacityRemaining().get());
		return true;
	}
	return false;
}

Measurement BatteryState::getCapacityRemaining() const {
	return ConvertFromCDM::convert(data->getCapacityRemaining().get());
}

bool BatteryState::hasCapacityRemaining() const {
	return data->getCapacityRemaining().present();
}

BatteryState & BatteryState::setVoltage(const Measurement & value) {
	data->setVoltage(ConvertToCDM::convert(value));
	return *this;
}

bool BatteryState::getVoltage(Measurement & out) const {
	if (data->getVoltage().present()) {
		out = ConvertFromCDM::convert(data->getVoltage().get());
		return true;
	}
	return false;
}

Measurement BatteryState::getVoltage() const {
	return ConvertFromCDM::convert(data->getVoltage().get());
}

bool BatteryState::hasVoltage() const {
	return data->getVoltage().present();
}

BatteryState & BatteryState::setCurrent(const Measurement & value) {
	data->setCurrent(ConvertToCDM::convert(value));
	return *this;
}

bool BatteryState::getCurrent(Measurement & out) const {
	if (data->getCurrent().present()) {
		out = ConvertFromCDM::convert(data->getCurrent().get());
		return true;
	}
	return false;
}

Measurement BatteryState::getCurrent() const {
	return ConvertFromCDM::convert(data->getCurrent().get());
}

bool BatteryState::hasCurrent() const {
	return data->getCurrent().present();
}

BatteryState & BatteryState::setTemperature(const Measurement & value) {
	data->setTemperature(ConvertToCDM::convert(value));
	return *this;
}

bool BatteryState::getTemperature(Measurement & out) const {
	if (data->getTemperature().present()) {
		out = ConvertFromCDM::convert(data->getTemperature().get());
		return true;
	}
	return false;
}

Measurement BatteryState::getTemperature() const {
	return ConvertFromCDM::convert(data->getTemperature().get());
}

bool BatteryState::hasTemperature() const {
	return data->getTemperature().present();
}

BatteryState & BatteryState::setRemainingBatteryTime(const Measurement & value) {
	data->setRemainingBatteryTime(ConvertToCDM::convert(value));
	return *this;
}

bool BatteryState::getRemainingBatteryTime(Measurement & out) const {
	if (data->getRemainingBatteryTime().present()) {
		out = ConvertFromCDM::convert(data->getRemainingBatteryTime().get());
		return true;
	}
	return false;
}

Measurement BatteryState::getRemainingBatteryTime() const {
	return ConvertFromCDM::convert(data->getRemainingBatteryTime().get());
}

bool BatteryState::hasRemainingBatteryTime() const {
	return data->getRemainingBatteryTime().present();
}

BatteryState & BatteryState::setChargeStatus(const ChargeStatus & value) {
	data->setChargeStatus(ConvertToCDM::convert(value));
	return *this;
}

bool BatteryState::getChargeStatus(ChargeStatus & out) const {
	if (data->getChargeStatus().present()) {
		out = ConvertFromCDM::convert(data->getChargeStatus().get());
		return true;
	}
	return false;
}

ChargeStatus BatteryState::getChargeStatus() const {
	return ConvertFromCDM::convert(data->getChargeStatus().get());
}

bool BatteryState::hasChargeStatus() const {
	return data->getChargeStatus().present();
}

BatteryState & BatteryState::setChargeCycles(const unsigned int & value) {
	data->setChargeCycles(ConvertToCDM::convert(value));
	return *this;
}

bool BatteryState::getChargeCycles(unsigned int & out) const {
	if (data->getChargeCycles().present()) {
		out = ConvertFromCDM::convert(data->getChargeCycles().get());
		return true;
	}
	return false;
}

unsigned int BatteryState::getChargeCycles() const {
	return ConvertFromCDM::convert(data->getChargeCycles().get());
}

bool BatteryState::hasChargeCycles() const {
	return data->getChargeCycles().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

