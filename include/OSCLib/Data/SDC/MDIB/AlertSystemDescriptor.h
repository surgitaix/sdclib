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
 *  Author: besting, buerger, roehser
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

#include "OSCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/SDC/SDC-fwd.h"
#include "osdm-fwd.hxx"

namespace SDCLib {
namespace Data {
namespace SDC {

class AlertSystemDescriptor {
private:
	AlertSystemDescriptor(const CDM::AlertSystemDescriptor & object);
	operator CDM::AlertSystemDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	AlertSystemDescriptor(
		Handle handle
	);
private:
	AlertSystemDescriptor(){};
public:
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

	AlertSystemDescriptor & setMaxPhysiologicalParallelAlarms(const unsigned int & value);
	unsigned int getMaxPhysiologicalParallelAlarms() const;
	bool getMaxPhysiologicalParallelAlarms(unsigned int & out) const;
	bool hasMaxPhysiologicalParallelAlarms() const;

	AlertSystemDescriptor & setMaxTechnicalParallelAlarms(const unsigned int & value);
	unsigned int getMaxTechnicalParallelAlarms() const;
	bool getMaxTechnicalParallelAlarms(unsigned int & out) const;
	bool hasMaxTechnicalParallelAlarms() const;

	AlertSystemDescriptor & setSelfCheckPeriod(const xml_schema::Duration & value);
	xml_schema::Duration getSelfCheckPeriod() const;
	bool getSelfCheckPeriod(xml_schema::Duration & out) const;
	bool hasSelfCheckPeriod() const;

	AlertSystemDescriptor & addAlertCondition(const AlertConditionDescriptor & value);
	std::vector<AlertConditionDescriptor> getAlertConditionList() const;
	void clearAlertConditionList();

	AlertSystemDescriptor & addAlertSignal(const AlertSignalDescriptor & value);
	std::vector<AlertSignalDescriptor> getAlertSignalList() const;
	void clearAlertSignalList();


	AlertSystemDescriptor & addLimitAlertCondition(const LimitAlertConditionDescriptor & source);
	std::vector<LimitAlertConditionDescriptor> getLimitAlertConditionList() const;
private:
	std::shared_ptr<CDM::AlertSystemDescriptor> data;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */
#endif /* ALERTSYSTEMDESCRIPTOR_H_ */
