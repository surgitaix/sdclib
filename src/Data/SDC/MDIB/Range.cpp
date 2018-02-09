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
 *  Range.cpp
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

#include "OSCLib/Data/SDC/MDIB/Range.h"
#include "OSCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/SDC/MDIB/Defaults.h"

#include "osdm.hxx"


namespace OSCLib {
namespace Data {
namespace SDC {


Range::Range(
) : data(Defaults::RangeInit(
)) {}

Range::operator CDM::Range() const {
	return *data;
}

Range::Range(const CDM::Range & object) : data(new CDM::Range(object)) {

}

Range::Range(const Range & object) : data(new CDM::Range(*object.data)) {

}

Range::~Range() {

}

void Range::copyFrom(const Range & object) {
	data = std::shared_ptr<CDM::Range>( new CDM::Range(*object.data));
}

Range & Range:: operator=(const Range & object) {
	copyFrom(object);
	return *this;
}


Range & Range::setLower(const double & value) {
	data->Lower(ConvertToCDM::convert(value));
	return *this;
}

bool Range::getLower(double & out) const {
	if (data->Lower().present()) {
		out = ConvertFromCDM::convert(data->Lower().get());
		return true;
	}
	return false;
}

double Range::getLower() const {
	return ConvertFromCDM::convert(data->Lower().get());
}
	
bool Range::hasLower() const {
	return data->Lower().present();
}
	
Range & Range::setUpper(const double & value) {
	data->Upper(ConvertToCDM::convert(value));
	return *this;
}

bool Range::getUpper(double & out) const {
	if (data->Upper().present()) {
		out = ConvertFromCDM::convert(data->Upper().get());
		return true;
	}
	return false;
}

double Range::getUpper() const {
	return ConvertFromCDM::convert(data->Upper().get());
}
	
bool Range::hasUpper() const {
	return data->Upper().present();
}
	
Range & Range::setStepWidth(const double & value) {
	data->StepWidth(ConvertToCDM::convert(value));
	return *this;
}

bool Range::getStepWidth(double & out) const {
	if (data->StepWidth().present()) {
		out = ConvertFromCDM::convert(data->StepWidth().get());
		return true;
	}
	return false;
}

double Range::getStepWidth() const {
	return ConvertFromCDM::convert(data->StepWidth().get());
}
	
bool Range::hasStepWidth() const {
	return data->StepWidth().present();
}
	
Range & Range::setRelativeAccuracy(const double & value) {
	data->RelativeAccuracy(ConvertToCDM::convert(value));
	return *this;
}

bool Range::getRelativeAccuracy(double & out) const {
	if (data->RelativeAccuracy().present()) {
		out = ConvertFromCDM::convert(data->RelativeAccuracy().get());
		return true;
	}
	return false;
}

double Range::getRelativeAccuracy() const {
	return ConvertFromCDM::convert(data->RelativeAccuracy().get());
}
	
bool Range::hasRelativeAccuracy() const {
	return data->RelativeAccuracy().present();
}
	
Range & Range::setAbsoluteAccuracy(const double & value) {
	data->AbsoluteAccuracy(ConvertToCDM::convert(value));
	return *this;
}

bool Range::getAbsoluteAccuracy(double & out) const {
	if (data->AbsoluteAccuracy().present()) {
		out = ConvertFromCDM::convert(data->AbsoluteAccuracy().get());
		return true;
	}
	return false;
}

double Range::getAbsoluteAccuracy() const {
	return ConvertFromCDM::convert(data->AbsoluteAccuracy().get());
}
	
bool Range::hasAbsoluteAccuracy() const {
	return data->AbsoluteAccuracy().present();
}
	

} /* namespace SDC */
} /* namespace Data */
} /* namespace OSCLib */

