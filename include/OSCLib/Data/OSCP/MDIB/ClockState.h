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
 *  ClockState.h
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

#ifndef CLOCKSTATE_H_
#define CLOCKSTATE_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class ClockState {
private:
	ClockState(const CDM::ClockState & object);
	operator CDM::ClockState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	ClockState();
	ClockState(const ClockState & object);
	virtual ~ClockState();
    
    void copyFrom(const ClockState & object);
    ClockState & operator=(const ClockState & object);
    
    typedef CDM::ClockState WrappedType;
    typedef ClockDescriptor DescriptorType;

	ClockState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;
	bool getStateVersion(VersionCounter & out) const;
	bool hasStateVersion() const;

	ClockState & setDescriptorHandle(const HandleRef & value);
	HandleRef getDescriptorHandle() const;

	ClockState & setDescriptorVersion(const ReferencedVersion & value);
	ReferencedVersion getDescriptorVersion() const;
	bool getDescriptorVersion(ReferencedVersion & out) const;
	bool hasDescriptorVersion() const;

	ClockState & setCalibrationInfo(const CalibrationInfo & value);
	CalibrationInfo getCalibrationInfo() const;
	bool getCalibrationInfo(CalibrationInfo & out) const;
	bool hasCalibrationInfo() const;

	ClockState & setNextCalibration(const CalibrationInfo & value);
	CalibrationInfo getNextCalibration() const;
	bool getNextCalibration(CalibrationInfo & out) const;
	bool hasNextCalibration() const;

	ClockState & setPhysicalConnector(const PhysicalConnectorInfo & value);
	PhysicalConnectorInfo getPhysicalConnector() const;
	bool getPhysicalConnector(PhysicalConnectorInfo & out) const;
	bool hasPhysicalConnector() const;

	ClockState & setActivationState(const ComponentActivation & value);
	ComponentActivation getActivationState() const;
	bool getActivationState(ComponentActivation & out) const;
	bool hasActivationState() const;

	ClockState & setOperatingHours(const unsigned int & value);
	unsigned int getOperatingHours() const;
	bool getOperatingHours(unsigned int & out) const;
	bool hasOperatingHours() const;

	ClockState & setOperatingCycles(const int & value);
	int getOperatingCycles() const;
	bool getOperatingCycles(int & out) const;
	bool hasOperatingCycles() const;

	ClockState & setActiveSyncProtocol(const CodedValue & value);
	CodedValue getActiveSyncProtocol() const;
	bool getActiveSyncProtocol(CodedValue & out) const;
	bool hasActiveSyncProtocol() const;

	ClockState & setDateAndTime(const Timestamp & value);
	Timestamp getDateAndTime() const;
	bool getDateAndTime(Timestamp & out) const;
	bool hasDateAndTime() const;

	ClockState & setRemoteSync(const bool & value);
	bool getRemoteSync() const;

	ClockState & setAccuracy(const double & value);
	double getAccuracy() const;
	bool getAccuracy(double & out) const;
	bool hasAccuracy() const;

	ClockState & setLastSet(const Timestamp & value);
	Timestamp getLastSet() const;
	bool getLastSet(Timestamp & out) const;
	bool hasLastSet() const;

	ClockState & setTimeZone(const TimeZone & value);
	TimeZone getTimeZone() const;
	bool getTimeZone(TimeZone & out) const;
	bool hasTimeZone() const;

	ClockState & setCriticalUse(const bool & value);
	bool getCriticalUse() const;
	bool getCriticalUse(bool & out) const;
	bool hasCriticalUse() const;

	ClockState & addReferenceSource(const std::string & value);
	std::vector<std::string> getReferenceSourceLists() const;
	void clearReferenceSourceLists();
	
private:
	std::shared_ptr<CDM::ClockState> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* CLOCKSTATE_H_ */
