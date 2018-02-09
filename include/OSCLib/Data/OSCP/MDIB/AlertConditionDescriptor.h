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
 *  AlertConditionDescriptor.h
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

#ifndef ALERTCONDITIONDESCRIPTOR_H_
#define ALERTCONDITIONDESCRIPTOR_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/SDC-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace SDC {

class AlertConditionDescriptor {
private:
	AlertConditionDescriptor(const CDM::AlertConditionDescriptor & object);
	operator CDM::AlertConditionDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	AlertConditionDescriptor(
		Handle handle
		, 
		AlertConditionKind kind
		, 
		AlertConditionPriority priority
	); 
private:
	AlertConditionDescriptor(){};
public:
	AlertConditionDescriptor(const AlertConditionDescriptor & object);
	virtual ~AlertConditionDescriptor();
    
    void copyFrom(const AlertConditionDescriptor & object);
    AlertConditionDescriptor & operator=(const AlertConditionDescriptor & object);
    
    typedef CDM::AlertConditionDescriptor WrappedType;

	AlertConditionDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	AlertConditionDescriptor & setHandle(const Handle & value);
	Handle getHandle() const;

	AlertConditionDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	AlertConditionDescriptor & setSafetyClassification(const SafetyClassification & value);
	SafetyClassification getSafetyClassification() const;
	bool getSafetyClassification(SafetyClassification & out) const;
	bool hasSafetyClassification() const;

	AlertConditionDescriptor & setKind(const AlertConditionKind & value);
	AlertConditionKind getKind() const;

	AlertConditionDescriptor & setPriority(const AlertConditionPriority & value);
	AlertConditionPriority getPriority() const;

	AlertConditionDescriptor & setDefaultConditionGenerationDelay(const xml_schema::Duration & value);
	xml_schema::Duration getDefaultConditionGenerationDelay() const;
	bool getDefaultConditionGenerationDelay(xml_schema::Duration & out) const;
	bool hasDefaultConditionGenerationDelay() const;

	AlertConditionDescriptor & setCanEscalate(const CanEscalate & value);
	CanEscalate getCanEscalate() const;
	bool getCanEscalate(CanEscalate & out) const;
	bool hasCanEscalate() const;

	AlertConditionDescriptor & setCanDeescalate(const CanDeescalate & value);
	CanDeescalate getCanDeescalate() const;
	bool getCanDeescalate(CanDeescalate & out) const;
	bool hasCanDeescalate() const;

	AlertConditionDescriptor & addSource(const HandleRef & value);
	std::vector<HandleRef> getSourceList() const;
	void clearSourceList();
	
	AlertConditionDescriptor & addCauseInfo(const CauseInfo & value);
	std::vector<CauseInfo> getCauseInfoList() const;
	void clearCauseInfoList();
	
private:
	std::shared_ptr<CDM::AlertConditionDescriptor> data;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* ALERTCONDITIONDESCRIPTOR_H_ */
