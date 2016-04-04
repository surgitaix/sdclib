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
 *  RealTimeSampleArrayMetricState.h
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

#ifndef REALTIMESAMPLEARRAYMETRICSTATE_H_
#define REALTIMESAMPLEARRAYMETRICSTATE_H_

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class RealTimeSampleArrayMetricState {
private:
	RealTimeSampleArrayMetricState(const CDM::RealTimeSampleArrayMetricState & object);
	operator CDM::RealTimeSampleArrayMetricState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	RealTimeSampleArrayMetricState();
	RealTimeSampleArrayMetricState(const RealTimeSampleArrayMetricState & object);
	virtual ~RealTimeSampleArrayMetricState();
    
    void copyFrom(const RealTimeSampleArrayMetricState & object);
    RealTimeSampleArrayMetricState & operator=(const RealTimeSampleArrayMetricState & object);
    
    typedef CDM::RealTimeSampleArrayMetricState WrappedType;
    typedef RealTimeSampleArrayMetricDescriptor DescriptorType;
    typedef OSCPProviderRealTimeSampleArrayMetricStateHandler ProviderHandlerType;
    typedef OSCPConsumerRealTimeSampleArrayMetricStateHandler ConsumerHandlerType;

	RealTimeSampleArrayMetricState & setHandle(const std::string & value);
	std::string getHandle() const;
	bool getHandle(std::string & out) const;
	bool hasHandle() const;

	RealTimeSampleArrayMetricState & setDescriptorHandle(const std::string & value);
	std::string getDescriptorHandle() const;

	RealTimeSampleArrayMetricState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;
	bool getStateVersion(VersionCounter & out) const;
	bool hasStateVersion() const;

	RealTimeSampleArrayMetricState & setComponentActivationState(const ComponentActivation & value);
	ComponentActivation getComponentActivationState() const;
	bool getComponentActivationState(ComponentActivation & out) const;
	bool hasComponentActivationState() const;

	RealTimeSampleArrayMetricState & setCalibrationInfo(const CalibrationInfo & value);
	CalibrationInfo getCalibrationInfo() const;
	bool getCalibrationInfo(CalibrationInfo & out) const;
	bool hasCalibrationInfo() const;

	RealTimeSampleArrayMetricState & setOperatingHours(const int & value);
	int getOperatingHours() const;
	bool getOperatingHours(int & out) const;
	bool hasOperatingHours() const;

	RealTimeSampleArrayMetricState & setOperatingCycles(const int & value);
	int getOperatingCycles() const;
	bool getOperatingCycles(int & out) const;
	bool hasOperatingCycles() const;

	RealTimeSampleArrayMetricState & setObservedValue(const RealTimeSampleArrayValue & value);
	RealTimeSampleArrayValue getObservedValue() const;
	bool getObservedValue(RealTimeSampleArrayValue & out) const;
	bool hasObservedValue() const;

private:
	std::shared_ptr<CDM::RealTimeSampleArrayMetricState> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* REALTIMESAMPLEARRAYMETRICSTATE_H_ */
