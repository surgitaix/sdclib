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
 *  LimitAlertConditionDescriptor.h
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

#ifndef LIMITALERTCONDITIONDESCRIPTOR_H_
#define LIMITALERTCONDITIONDESCRIPTOR_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/SDC-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class LimitAlertConditionDescriptor {
private:
	LimitAlertConditionDescriptor(const CDM::LimitAlertConditionDescriptor & object);
	operator CDM::LimitAlertConditionDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	LimitAlertConditionDescriptor(
		Handle handle
		, 
		AlertConditionKind kind
		, 
		AlertConditionPriority priority
		, 
		Range maxlimits
	); 
private:
	LimitAlertConditionDescriptor(){};
public:
	LimitAlertConditionDescriptor(const LimitAlertConditionDescriptor & object);
	virtual ~LimitAlertConditionDescriptor();
    
    void copyFrom(const LimitAlertConditionDescriptor & object);
    LimitAlertConditionDescriptor & operator=(const LimitAlertConditionDescriptor & object);
    
    typedef CDM::LimitAlertConditionDescriptor WrappedType;

	LimitAlertConditionDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	LimitAlertConditionDescriptor & setHandle(const Handle & value);
	Handle getHandle() const;

	LimitAlertConditionDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	LimitAlertConditionDescriptor & setSafetyClassification(const SafetyClassification & value);
	SafetyClassification getSafetyClassification() const;
	bool getSafetyClassification(SafetyClassification & out) const;
	bool hasSafetyClassification() const;

	LimitAlertConditionDescriptor & setKind(const AlertConditionKind & value);
	AlertConditionKind getKind() const;

	LimitAlertConditionDescriptor & setPriority(const AlertConditionPriority & value);
	AlertConditionPriority getPriority() const;

	LimitAlertConditionDescriptor & setDefaultConditionGenerationDelay(const xml_schema::Duration & value);
	xml_schema::Duration getDefaultConditionGenerationDelay() const;
	bool getDefaultConditionGenerationDelay(xml_schema::Duration & out) const;
	bool hasDefaultConditionGenerationDelay() const;

	LimitAlertConditionDescriptor & setCanEscalate(const CanEscalate & value);
	CanEscalate getCanEscalate() const;
	bool getCanEscalate(CanEscalate & out) const;
	bool hasCanEscalate() const;

	LimitAlertConditionDescriptor & setCanDeescalate(const CanDeescalate & value);
	CanDeescalate getCanDeescalate() const;
	bool getCanDeescalate(CanDeescalate & out) const;
	bool hasCanDeescalate() const;

	LimitAlertConditionDescriptor & addSource(const HandleRef & value);
	std::vector<HandleRef> getSourceList() const;
	void clearSourceList();
	
	LimitAlertConditionDescriptor & addCauseInfo(const CauseInfo & value);
	std::vector<CauseInfo> getCauseInfoList() const;
	void clearCauseInfoList();
	
	LimitAlertConditionDescriptor & setMaxLimits(const Range & value);
	Range getMaxLimits() const;

	LimitAlertConditionDescriptor & setAutoLimitSupported(const bool & value);
	bool getAutoLimitSupported() const;
	bool getAutoLimitSupported(bool & out) const;
	bool hasAutoLimitSupported() const;

private:
	std::shared_ptr<CDM::LimitAlertConditionDescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* LIMITALERTCONDITIONDESCRIPTOR_H_ */
