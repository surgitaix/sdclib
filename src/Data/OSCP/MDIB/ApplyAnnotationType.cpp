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
 *  ApplyAnnotationType.cpp
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

#include "OSCLib/Data/OSCP/MDIB/ApplyAnnotationType.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"


namespace OSCLib {
namespace Data {
namespace OSCP {

ApplyAnnotationType::ApplyAnnotationType() : data(Defaults::ApplyAnnotationType()) {
}

ApplyAnnotationType::operator CDM::ApplyAnnotationType() const {
	return *data;
}

ApplyAnnotationType::ApplyAnnotationType(const CDM::ApplyAnnotationType & object) : data(new CDM::ApplyAnnotationType(object)) {

}

ApplyAnnotationType::ApplyAnnotationType(const ApplyAnnotationType & object) : data(new CDM::ApplyAnnotationType(*object.data)) {

}

ApplyAnnotationType::~ApplyAnnotationType() {

}

void ApplyAnnotationType::copyFrom(const ApplyAnnotationType & object) {
	*data = *object.data;
}

ApplyAnnotationType & ApplyAnnotationType:: operator=(const ApplyAnnotationType & object) {
	copyFrom(object);
	return *this;
}


ApplyAnnotationType & ApplyAnnotationType::setAnnotationIndex(const unsigned int & value) {
	data->AnnotationIndex(ConvertToCDM::convert(value));
	return *this;
}


unsigned int ApplyAnnotationType::getAnnotationIndex() const {
	return ConvertFromCDM::convert(data->AnnotationIndex());
}
	
ApplyAnnotationType & ApplyAnnotationType::setSampleIndex(const unsigned int & value) {
	data->SampleIndex(ConvertToCDM::convert(value));
	return *this;
}


unsigned int ApplyAnnotationType::getSampleIndex() const {
	return ConvertFromCDM::convert(data->SampleIndex());
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

