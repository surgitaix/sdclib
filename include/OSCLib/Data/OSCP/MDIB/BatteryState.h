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
 *  BatteryState.h
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

#ifndef BATTERYSTATE_H_
#define BATTERYSTATE_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class BatteryState {
private:
	BatteryState(const CDM::BatteryState & object);
	operator CDM::BatteryState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	BatteryState();
	BatteryState(const BatteryState & object);
	virtual ~BatteryState();
    
    void copyFrom(const BatteryState & object);
    BatteryState & operator=(const BatteryState & object);
    
    typedef CDM::BatteryState WrappedType;

	BatteryState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;

	BatteryState & setDescriptorHandle(const HandleRef & value);
	HandleRef getDescriptorHandle() const;

	BatteryState & setDescriptorVersion(const ReferencedVersion & value);
	ReferencedVersion getDescriptorVersion() const;

	BatteryState & setCalibrationInfo(const CalibrationInfo & value);
	CalibrationInfo getCalibrationInfo() const;
	bool getCalibrationInfo(CalibrationInfo & out) const;
	bool hasCalibrationInfo() const;

	BatteryState & setNextCalibration(const CalibrationInfo & value);
	CalibrationInfo getNextCalibration() const;
	bool getNextCalibration(CalibrationInfo & out) const;
	bool hasNextCalibration() const;

	BatteryState & setActivationState(const ComponentActivation & value);
	ComponentActivation getActivationState() const;

	BatteryState & setOperatingHours(const unsigned int & value);
	unsigned int getOperatingHours() const;

	BatteryState & setOperatingCycles(const int & value);
	int getOperatingCycles() const;

	BatteryState & setCapacityRemaining(const Measurement & value);
	Measurement getCapacityRemaining() const;
	bool getCapacityRemaining(Measurement & out) const;
	bool hasCapacityRemaining() const;

	BatteryState & setVoltage(const Measurement & value);
	Measurement getVoltage() const;
	bool getVoltage(Measurement & out) const;
	bool hasVoltage() const;

	BatteryState & setCurrent(const Measurement & value);
	Measurement getCurrent() const;
	bool getCurrent(Measurement & out) const;
	bool hasCurrent() const;

	BatteryState & setTemperature(const Measurement & value);
	Measurement getTemperature() const;
	bool getTemperature(Measurement & out) const;
	bool hasTemperature() const;

	BatteryState & setRemainingBatteryTime(const Measurement & value);
	Measurement getRemainingBatteryTime() const;
	bool getRemainingBatteryTime(Measurement & out) const;
	bool hasRemainingBatteryTime() const;

	BatteryState & setChargeStatus(const ChargeStatusType & value);
	ChargeStatusType getChargeStatus() const;

	BatteryState & setChargeCycles(const unsigned int & value);
	unsigned int getChargeCycles() const;

private:
	std::shared_ptr<CDM::BatteryState> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* BATTERYSTATE_H_ */
