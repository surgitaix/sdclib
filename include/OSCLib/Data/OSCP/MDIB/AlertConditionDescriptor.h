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
 *  Author: besting, roehser
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

#include "OSCLib/Data/OSCP/MDIB/custom/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class AlertConditionDescriptor {
private:
	AlertConditionDescriptor(const CDM::AlertConditionDescriptor & object);
	operator CDM::AlertConditionDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	AlertConditionDescriptor();
	AlertConditionDescriptor(const AlertConditionDescriptor & object);
	virtual ~AlertConditionDescriptor();
    
    void copyFrom(const AlertConditionDescriptor & object);
    AlertConditionDescriptor & operator=(const AlertConditionDescriptor & object);
    
    typedef CDM::AlertConditionDescriptor WrappedType;

	AlertConditionDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	AlertConditionDescriptor & setHandle(const std::string & value);
	std::string getHandle() const;

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

	AlertConditionDescriptor & addSource(const std::string & value);
	std::vector<std::string> getSources() const;
	void clearSources();
	
	AlertConditionDescriptor & addCauseInfo(const CauseInfo & value);
	std::vector<CauseInfo> getCauseInfo() const;
	void clearCauseInfo();
	
private:
	std::shared_ptr<CDM::AlertConditionDescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* ALERTCONDITIONDESCRIPTOR_H_ */
