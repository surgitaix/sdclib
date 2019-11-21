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
 *  Author: besting, buerger, roehser
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

#include "SDCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "SDCLib/Data/SDC/SDC-fwd.h"
#include "DataModel/osdm-fwd.hxx"

namespace SDCLib {
namespace Data {
namespace SDC {

class BatteryState
{
private:
	BatteryState(const CDM::BatteryState & object);
	operator CDM::BatteryState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	BatteryState(
		HandleRef descriptorhandle
	);
private:
	BatteryState(){};
public:
	BatteryState(const BatteryState& object);
	virtual ~BatteryState() = default;

    void copyFrom(const BatteryState& object);
    BatteryState & operator=(const BatteryState& object);

    typedef CDM::BatteryState WrappedType;

	BatteryState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;
	bool getStateVersion(VersionCounter & out) const;
	bool hasStateVersion() const;

	BatteryState & setDescriptorHandle(const HandleRef & value);
	HandleRef getDescriptorHandle() const;

	BatteryState & setDescriptorVersion(const ReferencedVersion & value);
	ReferencedVersion getDescriptorVersion() const;
	bool getDescriptorVersion(ReferencedVersion & out) const;
	bool hasDescriptorVersion() const;

	BatteryState & setCalibrationInfo(const CalibrationInfo & value);
	CalibrationInfo getCalibrationInfo() const;
	bool getCalibrationInfo(CalibrationInfo & out) const;
	bool hasCalibrationInfo() const;

	BatteryState & setNextCalibration(const CalibrationInfo & value);
	CalibrationInfo getNextCalibration() const;
	bool getNextCalibration(CalibrationInfo & out) const;
	bool hasNextCalibration() const;

	BatteryState & setPhysicalConnector(const PhysicalConnectorInfo & value);
	PhysicalConnectorInfo getPhysicalConnector() const;
	bool getPhysicalConnector(PhysicalConnectorInfo & out) const;
	bool hasPhysicalConnector() const;

	BatteryState & setActivationState(const ComponentActivation & value);
	ComponentActivation getActivationState() const;
	bool getActivationState(ComponentActivation & out) const;
	bool hasActivationState() const;

	BatteryState & setOperatingHours(const unsigned int & value);
	unsigned int getOperatingHours() const;
	bool getOperatingHours(unsigned int & out) const;
	bool hasOperatingHours() const;

	BatteryState & setOperatingCycles(const int & value);
	int getOperatingCycles() const;
	bool getOperatingCycles(int & out) const;
	bool hasOperatingCycles() const;

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

	BatteryState & setChargeStatus(const ChargeStatus & value);
	ChargeStatus getChargeStatus() const;
	bool getChargeStatus(ChargeStatus & out) const;
	bool hasChargeStatus() const;

	BatteryState & setChargeCycles(const unsigned int & value);
	unsigned int getChargeCycles() const;
	bool getChargeCycles(unsigned int & out) const;
	bool hasChargeCycles() const;

private:
	std::shared_ptr<CDM::BatteryState> data = nullptr;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */
#endif /* BATTERYSTATE_H_ */
