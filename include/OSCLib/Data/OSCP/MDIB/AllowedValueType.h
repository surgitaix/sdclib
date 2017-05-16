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
 *  AllowedValueType.h
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

#ifndef ALLOWEDVALUETYPE_H_
#define ALLOWEDVALUETYPE_H_

#include "OSCLib/Data/OSCP/MDIB/custom/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class AllowedValueType {
private:
	AllowedValueType(const CDM::AllowedValueType & object);
	operator CDM::AllowedValueType() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	AllowedValueType();
	AllowedValueType(const AllowedValueType & object);
	virtual ~AllowedValueType();
    
    void copyFrom(const AllowedValueType & object);
    AllowedValueType & operator=(const AllowedValueType & object);
    
    typedef CDM::AllowedValueType WrappedType;

	AllowedValueType & setValue(const std::string & value);
	std::string getValue() const;

	AllowedValueType & setType(const CodedValue & value);
	CodedValue getType() const;

private:
	std::shared_ptr<CDM::AllowedValueType> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* ALLOWEDVALUETYPE_H_ */
