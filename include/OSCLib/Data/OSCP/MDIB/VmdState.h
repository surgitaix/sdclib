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
 *  VmdState.h
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

#ifndef VMDSTATE_H_
#define VMDSTATE_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class VmdState {
private:
	VmdState(const CDM::VmdState & object);
	operator CDM::VmdState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	VmdState();
	VmdState(const VmdState & object);
	virtual ~VmdState();
    
    void copyFrom(const VmdState & object);
    VmdState & operator=(const VmdState & object);
    
    typedef CDM::VmdState WrappedType;

	VmdState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;

	VmdState & setDescriptorHandle(const HandleRef & value);
	HandleRef getDescriptorHandle() const;

	VmdState & setDescriptorVersion(const ReferencedVersion & value);
	ReferencedVersion getDescriptorVersion() const;

	VmdState & setCalibrationInfo(const CalibrationInfo & value);
	CalibrationInfo getCalibrationInfo() const;
	bool getCalibrationInfo(CalibrationInfo & out) const;
	bool hasCalibrationInfo() const;

	VmdState & setNextCalibration(const CalibrationInfo & value);
	CalibrationInfo getNextCalibration() const;
	bool getNextCalibration(CalibrationInfo & out) const;
	bool hasNextCalibration() const;

	VmdState & setActivationState(const ComponentActivation & value);
	ComponentActivation getActivationState() const;

	VmdState & setOperatingHours(const unsignedInt & value);
	unsignedInt getOperatingHours() const;

	VmdState & setOperatingCycles(const int & value);
	int getOperatingCycles() const;

private:
	std::shared_ptr<CDM::VmdState> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* VMDSTATE_H_ */
