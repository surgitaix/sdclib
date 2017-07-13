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
 *  RelatedMeasurementType.h
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

#ifndef RELATEDMEASUREMENTTYPE_H_
#define RELATEDMEASUREMENTTYPE_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class RelatedMeasurementType {
private:
	RelatedMeasurementType(const CDM::RelatedMeasurementType & object);
	operator CDM::RelatedMeasurementType() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	RelatedMeasurementType();
	RelatedMeasurementType(const RelatedMeasurementType & object);
	virtual ~RelatedMeasurementType();
    
    void copyFrom(const RelatedMeasurementType & object);
    RelatedMeasurementType & operator=(const RelatedMeasurementType & object);
    
    typedef CDM::RelatedMeasurementType WrappedType;

	RelatedMeasurementType & setValue(const Measurement & value);
	Measurement getValue() const;

	RelatedMeasurementType & setValidity(const MeasurementValidity & value);
	MeasurementValidity getValidity() const;

private:
	std::shared_ptr<CDM::RelatedMeasurementType> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* RELATEDMEASUREMENTTYPE_H_ */
