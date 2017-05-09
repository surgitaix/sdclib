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
 *  AbstractDeviceComponentState.h
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

#ifndef ABSTRACTDEVICECOMPONENTSTATE_H_
#define ABSTRACTDEVICECOMPONENTSTATE_H_

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class AbstractDeviceComponentState {
private:
	AbstractDeviceComponentState(const CDM::AbstractDeviceComponentState & object);
	operator CDM::AbstractDeviceComponentState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	AbstractDeviceComponentState();
	AbstractDeviceComponentState(const AbstractDeviceComponentState & object);
	virtual ~AbstractDeviceComponentState();
    
    void copyFrom(const AbstractDeviceComponentState & object);
    AbstractDeviceComponentState & operator=(const AbstractDeviceComponentState & object);
    
    typedef CDM::AbstractDeviceComponentState WrappedType;

	AbstractDeviceComponentState & setHandle(const std::string & value);
	std::string getHandle() const;
	bool getHandle(std::string & out) const;
	bool hasHandle() const;

	AbstractDeviceComponentState & setDescriptorHandle(const std::string & value);
	std::string getDescriptorHandle() const;

	AbstractDeviceComponentState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;
	bool getStateVersion(VersionCounter & out) const;
	bool hasStateVersion() const;

	AbstractDeviceComponentState & setActivationState(const int & value);
	int getActivationState() const;
	bool getActivationState(int & out) const;
	bool hasActivationState() const;

	AbstractDeviceComponentState & setOperatingHours(const unsigned int & value);
	unsigned int getOperatingHours() const;
	bool getOperatingHours(unsigned int & out) const;
	bool hasOperatingHours() const;

	AbstractDeviceComponentState & setOperatingCycles(const int & value);
	int getOperatingCycles() const;
	bool getOperatingCycles(int & out) const;
	bool hasOperatingCycles() const;

	AbstractDeviceComponentState & setCalibrationInfo(const CalibrationInfo & value);
	CalibrationInfo getCalibrationInfo() const;
	bool getCalibrationInfo(CalibrationInfo & out) const;
	bool hasCalibrationInfo() const;

	AbstractDeviceComponentState & setNextCalibration(const CalibrationInfo & value);
	CalibrationInfo getNextCalibration() const;
	bool getNextCalibration(CalibrationInfo & out) const;
	bool hasNextCalibration() const;

private:
	std::shared_ptr<CDM::AbstractDeviceComponentState> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* ABSTRACTDEVICECOMPONENTSTATE_H_ */
