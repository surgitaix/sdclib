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
 *  EnumStringMetricState.h
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

#ifndef ENUMSTRINGMETRICSTATE_H_
#define ENUMSTRINGMETRICSTATE_H_

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class EnumStringMetricState {
private:
	EnumStringMetricState(const CDM::EnumStringMetricState & object);
	operator CDM::EnumStringMetricState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	EnumStringMetricState();
	EnumStringMetricState(const EnumStringMetricState & object);
	virtual ~EnumStringMetricState();
    
    void copyFrom(const EnumStringMetricState & object);
    EnumStringMetricState & operator=(const EnumStringMetricState & object);
    
    typedef CDM::EnumStringMetricState WrappedType;
    typedef EnumStringMetricDescriptor DescriptorType;
    typedef OSCPProviderEnumStringMetricStateHandler ProviderHandlerType;
    typedef OSCPConsumerEnumStringMetricStateHandler ConsumerHandlerType;

	EnumStringMetricState & setHandle(const std::string & value);
	std::string getHandle() const;
	bool getHandle(std::string & out) const;
	bool hasHandle() const;

	EnumStringMetricState & setDescriptorHandle(const std::string & value);
	std::string getDescriptorHandle() const;

	EnumStringMetricState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;
	bool getStateVersion(VersionCounter & out) const;
	bool hasStateVersion() const;

	EnumStringMetricState & setComponentActivationState(const ComponentActivation & value);
	ComponentActivation getComponentActivationState() const;
	bool getComponentActivationState(ComponentActivation & out) const;
	bool hasComponentActivationState() const;

	EnumStringMetricState & setCalibrationInfo(const CalibrationInfo & value);
	CalibrationInfo getCalibrationInfo() const;
	bool getCalibrationInfo(CalibrationInfo & out) const;
	bool hasCalibrationInfo() const;

	EnumStringMetricState & setOperatingHours(const int & value);
	int getOperatingHours() const;
	bool getOperatingHours(int & out) const;
	bool hasOperatingHours() const;

	EnumStringMetricState & setOperatingCycles(const int & value);
	int getOperatingCycles() const;
	bool getOperatingCycles(int & out) const;
	bool hasOperatingCycles() const;

	EnumStringMetricState & setObservedValue(const StringMetricValue & value);
	StringMetricValue getObservedValue() const;
	bool getObservedValue(StringMetricValue & out) const;
	bool hasObservedValue() const;

private:
	std::shared_ptr<CDM::EnumStringMetricState> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* ENUMSTRINGMETRICSTATE_H_ */
