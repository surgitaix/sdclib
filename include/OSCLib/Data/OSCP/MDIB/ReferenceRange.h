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
 *  ReferenceRange.h
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

#ifndef REFERENCERANGE_H_
#define REFERENCERANGE_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class ReferenceRange {
private:
	ReferenceRange(const CDM::ReferenceRange & object);
	operator CDM::ReferenceRange() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class OSCPProvider;
	friend class OSCPConsumer;
public:
	ReferenceRange(
		Range range
	); 
private:
	ReferenceRange(){};
public:
	ReferenceRange(const ReferenceRange & object);
	virtual ~ReferenceRange();
    
    void copyFrom(const ReferenceRange & object);
    ReferenceRange & operator=(const ReferenceRange & object);
    
    typedef CDM::ReferenceRange WrappedType;

	ReferenceRange & setRange(const Range & value);
	Range getRange() const;

	ReferenceRange & setMeaning(const CodedValue & value);
	CodedValue getMeaning() const;
	bool getMeaning(CodedValue & out) const;
	bool hasMeaning() const;

private:
	std::shared_ptr<CDM::ReferenceRange> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* REFERENCERANGE_H_ */
