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
 *  ChannelState.h
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

#ifndef CHANNELSTATE_H_
#define CHANNELSTATE_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class ChannelState {
private:
	ChannelState(const CDM::ChannelState & object);
	operator CDM::ChannelState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	ChannelState();
	ChannelState(const ChannelState & object);
	virtual ~ChannelState();
    
    void copyFrom(const ChannelState & object);
    ChannelState & operator=(const ChannelState & object);
    
    typedef CDM::ChannelState WrappedType;

	ChannelState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;

	ChannelState & setDescriptorHandle(const HandleRef & value);
	HandleRef getDescriptorHandle() const;

	ChannelState & setDescriptorVersion(const ReferencedVersion & value);
	ReferencedVersion getDescriptorVersion() const;

	ChannelState & setCalibrationInfo(const CalibrationInfo & value);
	CalibrationInfo getCalibrationInfo() const;
	bool getCalibrationInfo(CalibrationInfo & out) const;
	bool hasCalibrationInfo() const;

	ChannelState & setNextCalibration(const CalibrationInfo & value);
	CalibrationInfo getNextCalibration() const;
	bool getNextCalibration(CalibrationInfo & out) const;
	bool hasNextCalibration() const;

	ChannelState & setActivationState(const ComponentActivation & value);
	ComponentActivation getActivationState() const;

	ChannelState & setOperatingHours(const unsigned int & value);
	unsigned int getOperatingHours() const;

	ChannelState & setOperatingCycles(const int & value);
	int getOperatingCycles() const;

private:
	std::shared_ptr<CDM::ChannelState> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* CHANNELSTATE_H_ */
