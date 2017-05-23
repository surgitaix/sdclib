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
 *  RelatedMeasurement.cpp
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

#include "OSCLib/Data/OSCP/MDIB/RelatedMeasurement.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/Measurement.h"
#include "OSCLib/Data/OSCP/MDIB/ReferenceRange.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

RelatedMeasurement::RelatedMeasurement() : data(Defaults::RelatedMeasurement()) {
}

RelatedMeasurement::operator CDM::RelatedMeasurement() const {
	return *data;
}

RelatedMeasurement::RelatedMeasurement(const CDM::RelatedMeasurement & object) : data(new CDM::RelatedMeasurement(object)) {

}

RelatedMeasurement::RelatedMeasurement(const RelatedMeasurement & object) : data(new CDM::RelatedMeasurement(*object.data)) {

}

RelatedMeasurement::~RelatedMeasurement() {

}

void RelatedMeasurement::copyFrom(const RelatedMeasurement & object) {
	*data = *object.data;
}

RelatedMeasurement & RelatedMeasurement:: operator=(const RelatedMeasurement & object) {
	copyFrom(object);
	return *this;
}


RelatedMeasurement & RelatedMeasurement::setValue(const Measurement & value) {
	data->Value(ConvertToCDM::convert(value));
	return *this;
}

bool RelatedMeasurement::getValue(Measurement & out) const {
	if (data->Value().present()) {
		out = ConvertFromCDM::convert(data->Value().get());
		return true;
	}
	return false;
}

Measurement RelatedMeasurement::getValue() const {
	return ConvertFromCDM::convert(data->Value().get());
}
	
bool RelatedMeasurement::hasValue() const {
	return data->Value().present();
}
	
RelatedMeasurement & RelatedMeasurement::addReferenceRange(const ReferenceRange & value) {
	data->ReferenceRange().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ReferenceRange> RelatedMeasurement::getReferenceRanges() const {
	std::vector<ReferenceRange> result;
	result.reserve(data->ReferenceRange().size());
	for (const auto & value: data->ReferenceRange()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void RelatedMeasurement::clearReferenceRanges() {
	data->ReferenceRange().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

