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
 *  Author: besting, buerger, roehser
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

#include "OSCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/SDC/SDC-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace SDC {

class LimitAlertConditionState {
private:
	LimitAlertConditionState(const CDM::LimitAlertConditionState & object);
	operator CDM::LimitAlertConditionState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	LimitAlertConditionState(
		HandleRef descriptorhandle
		, 
		AlertActivation activationstate
		, 
		Range limits
		, 
		AlertConditionMonitoredLimits monitoredalertlimits
	); 
private:
	LimitAlertConditionState(){};
public:
	LimitAlertConditionState(const LimitAlertConditionState & object);
	virtual ~LimitAlertConditionState();
    
    void copyFrom(const LimitAlertConditionState & object);
    LimitAlertConditionState & operator=(const LimitAlertConditionState & object);
    
    typedef CDM::LimitAlertConditionState WrappedType;
    typedef LimitAlertConditionDescriptor DescriptorType;

	LimitAlertConditionState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;
	bool getStateVersion(VersionCounter & out) const;
	bool hasStateVersion() const;

	LimitAlertConditionState & setDescriptorHandle(const HandleRef & value);
	HandleRef getDescriptorHandle() const;

	LimitAlertConditionState & setDescriptorVersion(const ReferencedVersion & value);
	ReferencedVersion getDescriptorVersion() const;
	bool getDescriptorVersion(ReferencedVersion & out) const;
	bool hasDescriptorVersion() const;

	LimitAlertConditionState & setActivationState(const AlertActivation & value);
	AlertActivation getActivationState() const;

	LimitAlertConditionState & setActualConditionGenerationDelay(const xml_schema::Duration & value);
	xml_schema::Duration getActualConditionGenerationDelay() const;
	bool getActualConditionGenerationDelay(xml_schema::Duration & out) const;
	bool hasActualConditionGenerationDelay() const;

	LimitAlertConditionState & setActualPriority(const AlertConditionPriority & value);
	AlertConditionPriority getActualPriority() const;
	bool getActualPriority(AlertConditionPriority & out) const;
	bool hasActualPriority() const;

	LimitAlertConditionState & setRank(const int & value);
	int getRank() const;
	bool getRank(int & out) const;
	bool hasRank() const;

	LimitAlertConditionState & setPresence(const bool & value);
	bool getPresence() const;
	bool getPresence(bool & out) const;
	bool hasPresence() const;

	LimitAlertConditionState & setDeterminationTime(const Timestamp & value);
	Timestamp getDeterminationTime() const;
	bool getDeterminationTime(Timestamp & out) const;
	bool hasDeterminationTime() const;

	LimitAlertConditionState & setLimits(const Range & value);
	Range getLimits() const;

	LimitAlertConditionState & setMonitoredAlertLimits(const AlertConditionMonitoredLimits & value);
	AlertConditionMonitoredLimits getMonitoredAlertLimits() const;

	LimitAlertConditionState & setAutoLimitActivationState(const AlertActivation & value);
	AlertActivation getAutoLimitActivationState() const;
	bool getAutoLimitActivationState(AlertActivation & out) const;
	bool hasAutoLimitActivationState() const;

private:
	std::shared_ptr<CDM::LimitAlertConditionState> data;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* LIMITALERTCONDITIONSTATE_H_ */
