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
 *  AlertSystemDescriptor.h
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

#ifndef ALERTSYSTEMDESCRIPTOR_H_
#define ALERTSYSTEMDESCRIPTOR_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class AlertSystemDescriptor {
private:
	AlertSystemDescriptor(const CDM::AlertSystemDescriptor & object);
	operator CDM::AlertSystemDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	AlertSystemDescriptor();
	AlertSystemDescriptor(const AlertSystemDescriptor & object);
	virtual ~AlertSystemDescriptor();
    
    void copyFrom(const AlertSystemDescriptor & object);
    AlertSystemDescriptor & operator=(const AlertSystemDescriptor & object);
    
    typedef CDM::AlertSystemDescriptor WrappedType;

	AlertSystemDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	AlertSystemDescriptor & setHandle(const Handle & value);
	Handle getHandle() const;

	AlertSystemDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	AlertSystemDescriptor & setSafetyClassification(const SafetyClassification & value);
	SafetyClassification getSafetyClassification() const;
	bool getSafetyClassification(SafetyClassification & out) const;
	bool hasSafetyClassification() const;

	AlertSystemDescriptor & setMaxPhysiologicalParallelAlarms(const unsignedInt & value);
	unsignedInt getMaxPhysiologicalParallelAlarms() const;

	AlertSystemDescriptor & setMaxTechnicalParallelAlarms(const unsignedInt & value);
	unsignedInt getMaxTechnicalParallelAlarms() const;

	AlertSystemDescriptor & setSelfCheckPeriod(const duration & value);
	duration getSelfCheckPeriod() const;

	AlertSystemDescriptor & addAlertCondition(const AlertConditionDescriptor & value);
	std::vector<AlertConditionDescriptor> getAlertConditions() const;
	void clearAlertConditions();
	
	AlertSystemDescriptor & addAlertSignal(const AlertSignalDescriptor & value);
	std::vector<AlertSignalDescriptor> getAlertSignals() const;
	void clearAlertSignals();
	
private:
	std::shared_ptr<CDM::AlertSystemDescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* ALERTSYSTEMDESCRIPTOR_H_ */
