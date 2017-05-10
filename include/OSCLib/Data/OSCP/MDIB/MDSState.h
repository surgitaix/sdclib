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
 *  MDSState.h
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

#ifndef MDSSTATE_H_
#define MDSSTATE_H_

#include "OSCLib/Data/OSCP/MDIB/custom/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class MDSState {
private:
	MDSState(const CDM::MDSState & object);
	operator CDM::MDSState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	MDSState();
	MDSState(const MDSState & object);
	virtual ~MDSState();
    
    void copyFrom(const MDSState & object);
    MDSState & operator=(const MDSState & object);
    
    typedef CDM::MDSState WrappedType;
    typedef HydraMDSDescriptor DescriptorType;
    typedef OSCPProviderHydraMDSStateHandler ProviderHandlerType;

	MDSState & setHandle(const std::string & value);
	std::string getHandle() const;
	bool getHandle(std::string & out) const;
	bool hasHandle() const;

	MDSState & setDescriptorHandle(const std::string & value);
	std::string getDescriptorHandle() const;

	MDSState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;
	bool getStateVersion(VersionCounter & out) const;
	bool hasStateVersion() const;

	MDSState & setActivationState(const int & value);
	int getActivationState() const;
	bool getActivationState(int & out) const;
	bool hasActivationState() const;

	MDSState & setOperatingHours(const unsigned int & value);
	unsigned int getOperatingHours() const;
	bool getOperatingHours(unsigned int & out) const;
	bool hasOperatingHours() const;

	MDSState & setOperatingCycles(const int & value);
	int getOperatingCycles() const;
	bool getOperatingCycles(int & out) const;
	bool hasOperatingCycles() const;

	MDSState & setCalibrationInfo(const CalibrationInfo & value);
	CalibrationInfo getCalibrationInfo() const;
	bool getCalibrationInfo(CalibrationInfo & out) const;
	bool hasCalibrationInfo() const;

	MDSState & setNextCalibration(const CalibrationInfo & value);
	CalibrationInfo getNextCalibration() const;
	bool getNextCalibration(CalibrationInfo & out) const;
	bool hasNextCalibration() const;

	MDSState & setLang(const Language & value);
	Language getLang() const;
	bool getLang(Language & out) const;
	bool hasLang() const;

private:
	std::shared_ptr<CDM::MDSState> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* MDSSTATE_H_ */
