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
 *  RelatedMeasurement.h
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

#ifndef RELATEDMEASUREMENT_H_
#define RELATEDMEASUREMENT_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/SDC-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace SDC {

class RelatedMeasurement {
private:
	RelatedMeasurement(const CDM::RelatedMeasurement & object);
	operator CDM::RelatedMeasurement() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	RelatedMeasurement(
		Measurement value
	); 
private:
	RelatedMeasurement(){};
public:
	RelatedMeasurement(const RelatedMeasurement & object);
	virtual ~RelatedMeasurement();
    
    void copyFrom(const RelatedMeasurement & object);
    RelatedMeasurement & operator=(const RelatedMeasurement & object);
    
    typedef CDM::RelatedMeasurement WrappedType;

	RelatedMeasurement & setValue(const Measurement & value);
	Measurement getValue() const;

	RelatedMeasurement & setValidity(const MeasurementValidity & value);
	MeasurementValidity getValidity() const;
	bool getValidity(MeasurementValidity & out) const;
	bool hasValidity() const;

	RelatedMeasurement & addReferenceRange(const ReferenceRange & value);
	std::vector<ReferenceRange> getReferenceRangeList() const;
	void clearReferenceRangeList();
	
private:
	std::shared_ptr<CDM::RelatedMeasurement> data;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* RELATEDMEASUREMENT_H_ */
