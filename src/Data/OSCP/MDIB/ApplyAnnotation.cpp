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
 *  ApplyAnnotation.cpp
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

#include "OSCLib/Data/OSCP/MDIB/ApplyAnnotation.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"


namespace OSCLib {
namespace Data {
namespace OSCP {


ApplyAnnotation::ApplyAnnotation(
		unsigned int annotationindex
		, 
		unsigned int sampleindex
) : data(Defaults::ApplyAnnotationInit(
		annotationindex
		,
		sampleindex
)) {}

ApplyAnnotation::operator CDM::ApplyAnnotation() const {
	return *data;
}

ApplyAnnotation::ApplyAnnotation(const CDM::ApplyAnnotation & object) : data(new CDM::ApplyAnnotation(object)) {

}

ApplyAnnotation::ApplyAnnotation(const ApplyAnnotation & object) : data(new CDM::ApplyAnnotation(*object.data)) {

}

ApplyAnnotation::~ApplyAnnotation() {

}

void ApplyAnnotation::copyFrom(const ApplyAnnotation & object) {
	*data = *object.data;
}

ApplyAnnotation & ApplyAnnotation:: operator=(const ApplyAnnotation & object) {
	copyFrom(object);
	return *this;
}


ApplyAnnotation & ApplyAnnotation::setAnnotationIndex(const unsigned int & value) {
	data->AnnotationIndex(ConvertToCDM::convert(value));
	return *this;
}


unsigned int ApplyAnnotation::getAnnotationIndex() const {
	return ConvertFromCDM::convert(data->AnnotationIndex());
}
	
ApplyAnnotation & ApplyAnnotation::setSampleIndex(const unsigned int & value) {
	data->SampleIndex(ConvertToCDM::convert(value));
	return *this;
}


unsigned int ApplyAnnotation::getSampleIndex() const {
	return ConvertFromCDM::convert(data->SampleIndex());
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

