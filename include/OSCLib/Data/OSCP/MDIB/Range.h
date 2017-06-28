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
 *  Range.h
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

#ifndef RANGE_H_
#define RANGE_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class Range {
private:
	Range(const CDM::Range & object);
	operator CDM::Range() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	Range();
	Range(const Range & object);
	virtual ~Range();
    
    void copyFrom(const Range & object);
    Range & operator=(const Range & object);
    
    typedef CDM::Range WrappedType;

	Range & setLower(const decimal & value);
	decimal getLower() const;
	bool getLower(decimal & out) const;
	bool hasLower() const;

	Range & setUpper(const decimal & value);
	decimal getUpper() const;
	bool getUpper(decimal & out) const;
	bool hasUpper() const;

	Range & setStepWidth(const decimal & value);
	decimal getStepWidth() const;
	bool getStepWidth(decimal & out) const;
	bool hasStepWidth() const;

	Range & setRelativeAccuracy(const decimal & value);
	decimal getRelativeAccuracy() const;
	bool getRelativeAccuracy(decimal & out) const;
	bool hasRelativeAccuracy() const;

	Range & setAbsoluteAccuracy(const decimal & value);
	decimal getAbsoluteAccuracy() const;
	bool getAbsoluteAccuracy(decimal & out) const;
	bool hasAbsoluteAccuracy() const;

private:
	std::shared_ptr<CDM::Range> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* RANGE_H_ */
