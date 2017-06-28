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
 *  StringMetricState.h
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

#ifndef STRINGMETRICSTATE_H_
#define STRINGMETRICSTATE_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class StringMetricState {
private:
	StringMetricState(const CDM::StringMetricState & object);
	operator CDM::StringMetricState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	StringMetricState();
	StringMetricState(const StringMetricState & object);
	virtual ~StringMetricState();
    
    void copyFrom(const StringMetricState & object);
    StringMetricState & operator=(const StringMetricState & object);
    
    typedef CDM::StringMetricState WrappedType;

	StringMetricState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;

	StringMetricState & setDescriptorHandle(const HandleRef & value);
	HandleRef getDescriptorHandle() const;

	StringMetricState & setDescriptorVersion(const ReferencedVersion & value);
	ReferencedVersion getDescriptorVersion() const;

	StringMetricState & setActivationState(const ComponentActivation & value);
	ComponentActivation getActivationState() const;

	StringMetricState & setActiveDeterminationPeriod(const duration & value);
	duration getActiveDeterminationPeriod() const;

	StringMetricState & setLifeTimePeriod(const duration & value);
	duration getLifeTimePeriod() const;
	bool getLifeTimePeriod(duration & out) const;
	bool hasLifeTimePeriod() const;

	StringMetricState & addBodySite(const CodedValue & value);
	std::vector<CodedValue> getBodySites() const;
	void clearBodySites();
	
	StringMetricState & setMetricValue(const StringMetricValue & value);
	StringMetricValue getMetricValue() const;
	bool getMetricValue(StringMetricValue & out) const;
	bool hasMetricValue() const;

private:
	std::shared_ptr<CDM::StringMetricState> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* STRINGMETRICSTATE_H_ */
