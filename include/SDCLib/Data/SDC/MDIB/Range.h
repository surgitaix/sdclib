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
 *  Author: besting, buerger, roehser
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

#include "SDCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "SDCLib/Data/SDC/SDC-fwd.h"
#include "DataModel/osdm-fwd.hxx"

namespace SDCLib {
namespace Data {
namespace SDC {

class Range
{
private:
	Range(const CDM::Range & object);
	operator CDM::Range() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	Range(
	);
	Range(const Range& object);
	virtual ~Range() = default;

    void copyFrom(const Range& object);
    Range & operator=(const Range& object);

    typedef CDM::Range WrappedType;

	Range & setLower(const double & value);
	double getLower() const;
	bool getLower(double & out) const;
	bool hasLower() const;

	Range & setUpper(const double & value);
	double getUpper() const;
	bool getUpper(double & out) const;
	bool hasUpper() const;

	Range & setStepWidth(const double & value);
	double getStepWidth() const;
	bool getStepWidth(double & out) const;
	bool hasStepWidth() const;

	Range & setRelativeAccuracy(const double & value);
	double getRelativeAccuracy() const;
	bool getRelativeAccuracy(double & out) const;
	bool hasRelativeAccuracy() const;

	Range & setAbsoluteAccuracy(const double & value);
	double getAbsoluteAccuracy() const;
	bool getAbsoluteAccuracy(double & out) const;
	bool hasAbsoluteAccuracy() const;

private:
	std::shared_ptr<CDM::Range> data = nullptr;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */
#endif /* RANGE_H_ */
