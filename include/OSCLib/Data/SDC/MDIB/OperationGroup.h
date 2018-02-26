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
 *  OperationGroup.h
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

#ifndef OPERATIONGROUP_H_
#define OPERATIONGROUP_H_

#include "OSCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/SDC/SDC-fwd.h"
#include "osdm-fwd.hxx"

namespace SDCLib {
namespace Data {
namespace SDC {

class OperationGroup {
private:
	OperationGroup(const CDM::OperationGroup & object);
	operator CDM::OperationGroup() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	OperationGroup(
		CodedValue type
	); 
private:
	OperationGroup(){};
public:
	OperationGroup(const OperationGroup & object);
	virtual ~OperationGroup();
    
    void copyFrom(const OperationGroup & object);
    OperationGroup & operator=(const OperationGroup & object);
    
    typedef CDM::OperationGroup WrappedType;

	OperationGroup & setType(const CodedValue & value);
	CodedValue getType() const;

	OperationGroup & setOperatingMode(const OperatingMode & value);
	OperatingMode getOperatingMode() const;
	bool getOperatingMode(OperatingMode & out) const;
	bool hasOperatingMode() const;

	OperationGroup & setOperations(const OperationRef & value);
	OperationRef getOperations() const;
	bool getOperations(OperationRef & out) const;
	bool hasOperations() const;

private:
	std::shared_ptr<CDM::OperationGroup> data;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */
#endif /* OPERATIONGROUP_H_ */
