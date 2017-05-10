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
 *  Annotation.cpp
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

#include "OSCLib/Data/OSCP/MDIB/Annotation.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/SampleIndex.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

Annotation::Annotation() : data(Defaults::Annotation()) {
}

Annotation::operator CDM::Annotation() const {
	return *data;
}

Annotation::Annotation(const CDM::Annotation & object) : data(new CDM::Annotation(object)) {

}

Annotation::Annotation(const Annotation & object) : data(new CDM::Annotation(*object.data)) {

}

Annotation::~Annotation() {

}

void Annotation::copyFrom(const Annotation & object) {
	*data = *object.data;
}

Annotation & Annotation:: operator=(const Annotation & object) {
	copyFrom(object);
	return *this;
}


Annotation & Annotation::setCode(const CodedValue & value) {
	data->Code(ConvertToCDM::convert(value));
	return *this;
}


CodedValue Annotation::getCode() const {
	return ConvertFromCDM::convert(data->Code());
}
	
Annotation & Annotation::setSampleIndex(const SampleIndex & value) {
	data->SampleIndex(ConvertToCDM::convert(value));
	return *this;
}

bool Annotation::getSampleIndex(SampleIndex & out) const {
	if (data->SampleIndex().present()) {
		out = ConvertFromCDM::convert(data->SampleIndex().get());
		return true;
	}
	return false;
}

SampleIndex Annotation::getSampleIndex() const {
	return ConvertFromCDM::convert(data->SampleIndex().get());
}
	
bool Annotation::hasSampleIndex() const {
	return data->SampleIndex().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

