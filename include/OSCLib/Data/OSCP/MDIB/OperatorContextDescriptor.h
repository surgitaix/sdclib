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
 *  OperatorContextDescriptor.h
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

#ifndef OPERATORCONTEXTDESCRIPTOR_H_
#define OPERATORCONTEXTDESCRIPTOR_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class OperatorContextDescriptor {
private:
	OperatorContextDescriptor(const CDM::OperatorContextDescriptor & object);
	operator CDM::OperatorContextDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class OSCPProvider;
	friend class OSCPConsumer;
public:
	OperatorContextDescriptor(
		Handle handle
	); 
private:
	OperatorContextDescriptor(){};
public:
	OperatorContextDescriptor(const OperatorContextDescriptor & object);
	virtual ~OperatorContextDescriptor();
    
    void copyFrom(const OperatorContextDescriptor & object);
    OperatorContextDescriptor & operator=(const OperatorContextDescriptor & object);
    
    typedef CDM::OperatorContextDescriptor WrappedType;
    typedef OperatorContextState StateType;

	OperatorContextDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	OperatorContextDescriptor & setHandle(const Handle & value);
	Handle getHandle() const;

	OperatorContextDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	OperatorContextDescriptor & setSafetyClassification(const SafetyClassification & value);
	SafetyClassification getSafetyClassification() const;
	bool getSafetyClassification(SafetyClassification & out) const;
	bool hasSafetyClassification() const;

private:
	std::shared_ptr<CDM::OperatorContextDescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* OPERATORCONTEXTDESCRIPTOR_H_ */
