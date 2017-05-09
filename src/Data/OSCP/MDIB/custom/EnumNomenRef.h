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
 *  EnumNomenRef.h
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

#ifndef ENUMNOMENREF_H_
#define ENUMNOMENREF_H_

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class EnumNomenRef {
private:
	EnumNomenRef(const CDM::EnumNomenRef & object);
	operator CDM::EnumNomenRef() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	EnumNomenRef();
	EnumNomenRef(const EnumNomenRef & object);
	virtual ~EnumNomenRef();
    
    void copyFrom(const EnumNomenRef & object);
    EnumNomenRef & operator=(const EnumNomenRef & object);
    
    typedef CDM::EnumNomenRef WrappedType;

	EnumNomenRef & setCode(const CodedValue & value);
	CodedValue getCode() const;

	EnumNomenRef & setEnumIndex(const SampleIndex & value);
	SampleIndex getEnumIndex() const;
	bool getEnumIndex(SampleIndex & out) const;
	bool hasEnumIndex() const;

private:
	std::shared_ptr<CDM::EnumNomenRef> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* ENUMNOMENREF_H_ */
