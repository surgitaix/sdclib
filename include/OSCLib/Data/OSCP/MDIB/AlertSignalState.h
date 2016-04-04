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
 *  AlertSignalState.h
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

#ifndef ALERTSIGNALSTATE_H_
#define ALERTSIGNALSTATE_H_

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class AlertSignalState {
private:
	AlertSignalState(const CDM::AlertSignalState & object);
	operator CDM::AlertSignalState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	AlertSignalState();
	AlertSignalState(const AlertSignalState & object);
	virtual ~AlertSignalState();
    
    void copyFrom(const AlertSignalState & object);
    AlertSignalState & operator=(const AlertSignalState & object);
    
    typedef CDM::AlertSignalState WrappedType;
    typedef AlertSignalDescriptor DescriptorType;
    typedef OSCPProviderAlertSignalStateHandler ProviderHandlerType;
    typedef OSCPConsumerAlertSignalStateHandler ConsumerHandlerType;

	AlertSignalState & setHandle(const std::string & value);
	std::string getHandle() const;
	bool getHandle(std::string & out) const;
	bool hasHandle() const;

	AlertSignalState & setDescriptorHandle(const std::string & value);
	std::string getDescriptorHandle() const;

	AlertSignalState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;
	bool getStateVersion(VersionCounter & out) const;
	bool hasStateVersion() const;

	AlertSignalState & setLocation(const PrimaryAlertSignalLocation & value);
	PrimaryAlertSignalLocation getLocation() const;
	bool getLocation(PrimaryAlertSignalLocation & out) const;
	bool hasLocation() const;

	AlertSignalState & setSlot(const int & value);
	int getSlot() const;
	bool getSlot(int & out) const;
	bool hasSlot() const;

	AlertSignalState & setActivationState(const PausableActivation & value);
	PausableActivation getActivationState() const;

	AlertSignalState & setPresence(const SignalPresence & value);
	SignalPresence getPresence() const;
	bool getPresence(SignalPresence & out) const;
	bool hasPresence() const;

private:
	std::shared_ptr<CDM::AlertSignalState> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* ALERTSIGNALSTATE_H_ */
