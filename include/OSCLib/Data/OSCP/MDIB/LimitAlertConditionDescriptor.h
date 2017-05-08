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
 *  Author: besting, roehser
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

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
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
public:
	LimitAlertConditionDescriptor();
	LimitAlertConditionDescriptor(const LimitAlertConditionDescriptor & object);
	virtual ~LimitAlertConditionDescriptor();
    
    void copyFrom(const LimitAlertConditionDescriptor & object);
    LimitAlertConditionDescriptor & operator=(const LimitAlertConditionDescriptor & object);
    
    typedef CDM::LimitAlertConditionDescriptor WrappedType;

	LimitAlertConditionDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	LimitAlertConditionDescriptor & setHandle(const std::string & value);
	std::string getHandle() const;

	LimitAlertConditionDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	LimitAlertConditionDescriptor & setKind(const AlertConditionKind & value);
	AlertConditionKind getKind() const;

	LimitAlertConditionDescriptor & setPriority(const AlertConditionPriority & value);
	AlertConditionPriority getPriority() const;

	LimitAlertConditionDescriptor & addSource(const std::string & value);
	std::vector<std::string> getSources() const;
	void clearSources();
	
	LimitAlertConditionDescriptor & addCauseInfo(const CauseInfo & value);
	std::vector<CauseInfo> getCauseInfo() const;
	void clearCauseInfo();
	
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
