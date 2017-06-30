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
 *  AlertSignalDescriptor.h
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

#ifndef ALERTSIGNALDESCRIPTOR_H_
#define ALERTSIGNALDESCRIPTOR_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class AlertSignalDescriptor {
private:
	AlertSignalDescriptor(const CDM::AlertSignalDescriptor & object);
	operator CDM::AlertSignalDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	AlertSignalDescriptor();
	AlertSignalDescriptor(const AlertSignalDescriptor & object);
	virtual ~AlertSignalDescriptor();
    
    void copyFrom(const AlertSignalDescriptor & object);
    AlertSignalDescriptor & operator=(const AlertSignalDescriptor & object);
    
    typedef CDM::AlertSignalDescriptor WrappedType;

	AlertSignalDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	AlertSignalDescriptor & setHandle(const Handle & value);
	Handle getHandle() const;

	AlertSignalDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	AlertSignalDescriptor & setSafetyClassification(const SafetyClassification & value);
	SafetyClassification getSafetyClassification() const;
	bool getSafetyClassification(SafetyClassification & out) const;
	bool hasSafetyClassification() const;

	AlertSignalDescriptor & setConditionSignaled(const HandleRef & value);
	HandleRef getConditionSignaled() const;

	AlertSignalDescriptor & setManifestation(const AlertSignalManifestation & value);
	AlertSignalManifestation getManifestation() const;

	AlertSignalDescriptor & setLatching(const bool & value);
	bool getLatching() const;

	AlertSignalDescriptor & setDefaultSignalGenerationDelay(const xml_schema::Duration & value);
	xml_schema::Duration getDefaultSignalGenerationDelay() const;

	AlertSignalDescriptor & setSignalDelegationSupported(const bool & value);
	bool getSignalDelegationSupported() const;

	AlertSignalDescriptor & setAcknowledgementSupported(const bool & value);
	bool getAcknowledgementSupported() const;
	bool getAcknowledgementSupported(bool & out) const;
	bool hasAcknowledgementSupported() const;

	AlertSignalDescriptor & setAcknowledgeTimeout(const xml_schema::Duration & value);
	xml_schema::Duration getAcknowledgeTimeout() const;
	bool getAcknowledgeTimeout(xml_schema::Duration & out) const;
	bool hasAcknowledgeTimeout() const;

private:
	std::shared_ptr<CDM::AlertSignalDescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* ALERTSIGNALDESCRIPTOR_H_ */
