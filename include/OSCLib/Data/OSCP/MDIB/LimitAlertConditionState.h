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
 *  LimitAlertConditionState.h
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

#ifndef LIMITALERTCONDITIONSTATE_H_
#define LIMITALERTCONDITIONSTATE_H_

#include "OSCLib/Data/OSCP/MDIB/custom/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class LimitAlertConditionState {
private:
	LimitAlertConditionState(const CDM::LimitAlertConditionState & object);
	operator CDM::LimitAlertConditionState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	LimitAlertConditionState();
	LimitAlertConditionState(const LimitAlertConditionState & object);
	virtual ~LimitAlertConditionState();
    
    void copyFrom(const LimitAlertConditionState & object);
    LimitAlertConditionState & operator=(const LimitAlertConditionState & object);
    
    typedef CDM::LimitAlertConditionState WrappedType;
    typedef LimitAlertConditionDescriptor DescriptorType;
    typedef OSCPProviderLimitAlertConditionStateHandler ProviderHandlerType;
    typedef OSCPConsumerLimitAlertConditionStateHandler ConsumerHandlerType;

	LimitAlertConditionState & setHandle(const std::string & value);
	std::string getHandle() const;
	bool getHandle(std::string & out) const;
	bool hasHandle() const;

	LimitAlertConditionState & setDescriptorHandle(const std::string & value);
	std::string getDescriptorHandle() const;

	LimitAlertConditionState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;
	bool getStateVersion(VersionCounter & out) const;
	bool hasStateVersion() const;

	LimitAlertConditionState & setActivationState(const AlertActivation & value);
	AlertActivation getActivationState() const;

	LimitAlertConditionState & setRank(const int & value);
	int getRank() const;
	bool getRank(int & out) const;
	bool hasRank() const;

	LimitAlertConditionState & setPresence(const bool & value);
	bool getPresence() const;

	LimitAlertConditionState & setObservationTime(const Timestamp & value);
	Timestamp getObservationTime() const;
	bool getObservationTime(Timestamp & out) const;
	bool hasObservationTime() const;

	LimitAlertConditionState & setLimits(const Range & value);
	Range getLimits() const;
	bool getLimits(Range & out) const;
	bool hasLimits() const;

	LimitAlertConditionState & setMonitoredAlertLimits(const AlertConditionMonitoredLimits & value);
	AlertConditionMonitoredLimits getMonitoredAlertLimits() const;

	LimitAlertConditionState & setAutoLimitActivationState(const AlertActivation & value);
	AlertActivation getAutoLimitActivationState() const;
	bool getAutoLimitActivationState(AlertActivation & out) const;
	bool hasAutoLimitActivationState() const;

private:
	std::shared_ptr<CDM::LimitAlertConditionState> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* LIMITALERTCONDITIONSTATE_H_ */
