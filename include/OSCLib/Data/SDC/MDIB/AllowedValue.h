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
 *  AllowedValue.h
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

#ifndef ALLOWEDVALUE_H_
#define ALLOWEDVALUE_H_

#include "OSCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/SDC/SDC-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace SDC {

class AllowedValue {
private:
	AllowedValue(const CDM::AllowedValue & object);
	operator CDM::AllowedValue() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	AllowedValue(
		std::string value
	); 
private:
	AllowedValue(){};
public:
	AllowedValue(const AllowedValue & object);
	virtual ~AllowedValue();
    
    void copyFrom(const AllowedValue & object);
    AllowedValue & operator=(const AllowedValue & object);
    
    typedef CDM::AllowedValue WrappedType;

	AllowedValue & setValue(const std::string & value);
	std::string getValue() const;

	AllowedValue & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	AllowedValue & setIdentification(const InstanceIdentifier & value);
	InstanceIdentifier getIdentification() const;
	bool getIdentification(InstanceIdentifier & out) const;
	bool hasIdentification() const;

	AllowedValue & setCharacteristic(const Measurement & value);
	Measurement getCharacteristic() const;
	bool getCharacteristic(Measurement & out) const;
	bool hasCharacteristic() const;

private:
	std::shared_ptr<CDM::AllowedValue> data;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* ALLOWEDVALUE_H_ */
