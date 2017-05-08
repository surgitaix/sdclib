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
 *  AlertConditionState.h
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

#ifndef ALERTCONDITIONSTATE_H_
#define ALERTCONDITIONSTATE_H_

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class AlertConditionState {
private:
	AlertConditionState(const CDM::AlertConditionState & object);
	operator CDM::AlertConditionState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	AlertConditionState();
	AlertConditionState(const AlertConditionState & object);
	virtual ~AlertConditionState();
    
    void copyFrom(const AlertConditionState & object);
    AlertConditionState & operator=(const AlertConditionState & object);
    
    typedef CDM::AlertConditionState WrappedType;
    typedef AlertConditionDescriptor DescriptorType;
    typedef OSCPProviderAlertConditionStateHandler ProviderHandlerType;
    typedef OSCPConsumerAlertConditionStateHandler ConsumerHandlerType;

	AlertConditionState & setHandle(const std::string & value);
	std::string getHandle() const;
	bool getHandle(std::string & out) const;
	bool hasHandle() const;

	AlertConditionState & setDescriptorHandle(const std::string & value);
	std::string getDescriptorHandle() const;

	AlertConditionState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;
	bool getStateVersion(VersionCounter & out) const;
	bool hasStateVersion() const;

	AlertConditionState & setActivationState(const AlertActivation & value);
	AlertActivation getActivationState() const;

	AlertConditionState & setRank(const int & value);
	int getRank() const;
	bool getRank(int & out) const;
	bool hasRank() const;

	AlertConditionState & setPresence(const bool & value);
	bool getPresence() const;

	AlertConditionState & setObservationTime(const Timestamp & value);
	Timestamp getObservationTime() const;
	bool getObservationTime(Timestamp & out) const;
	bool hasObservationTime() const;

private:
	std::shared_ptr<CDM::AlertConditionState> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* ALERTCONDITIONSTATE_H_ */
