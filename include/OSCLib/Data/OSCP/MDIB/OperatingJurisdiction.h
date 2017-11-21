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
 *  OperatingJurisdiction.h
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

#ifndef OPERATINGJURISDICTION_H_
#define OPERATINGJURISDICTION_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class OperatingJurisdiction {
private:
	OperatingJurisdiction(const CDM::OperatingJurisdiction & object);
	operator CDM::OperatingJurisdiction() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	OperatingJurisdiction(
	); 
	OperatingJurisdiction(const OperatingJurisdiction & object);
	virtual ~OperatingJurisdiction();
    
    void copyFrom(const OperatingJurisdiction & object);
    OperatingJurisdiction & operator=(const OperatingJurisdiction & object);
    
    typedef CDM::OperatingJurisdiction WrappedType;

	OperatingJurisdiction & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	OperatingJurisdiction & addIdentifierName(const LocalizedText & value);
	std::vector<LocalizedText> getIdentifierNameList() const;
	void clearIdentifierNameList();
	
private:
	std::shared_ptr<CDM::OperatingJurisdiction> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* OPERATINGJURISDICTION_H_ */
