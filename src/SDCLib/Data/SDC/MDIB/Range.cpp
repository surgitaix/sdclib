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

#include "SDCLib/Data/SDC/MDIB/Range.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"


namespace SDCLib {
namespace Data {
namespace SDC {


Range::Range(
) : data(Defaults::RangeInit(
))
{}

Range::operator CDM::Range() const {
	return *data;
}

Range::Range(const CDM::Range & object)
: data(new CDM::Range(object))
{ }

Range::Range(const Range & object)
: data(std::make_shared<CDM::Range>(*object.data))
{ }

void Range::copyFrom(const Range & object) {
	data = std::make_shared<CDM::Range>(*object.data);
}

Range & Range:: operator=(const Range& object) {
	copyFrom(object);
	return *this;
}


Range & Range::setLower(const double & value) {
	data->setLower(ConvertToCDM::convert(value));
	return *this;
}

bool Range::getLower(double & out) const {
	if (data->getLower().present()) {
		out = ConvertFromCDM::convert(data->getLower().get());
		return true;
	}
	return false;
}

double Range::getLower() const {
	return ConvertFromCDM::convert(data->getLower().get());
}

bool Range::hasLower() const {
	return data->getLower().present();
}

Range & Range::setUpper(const double & value) {
	data->setUpper(ConvertToCDM::convert(value));
	return *this;
}

bool Range::getUpper(double & out) const {
	if (data->getUpper().present()) {
		out = ConvertFromCDM::convert(data->getUpper().get());
		return true;
	}
	return false;
}

double Range::getUpper() const {
	return ConvertFromCDM::convert(data->getUpper().get());
}

bool Range::hasUpper() const {
	return data->getUpper().present();
}

Range & Range::setStepWidth(const double & value) {
	data->setStepWidth(ConvertToCDM::convert(value));
	return *this;
}

bool Range::getStepWidth(double & out) const {
	if (data->getStepWidth().present()) {
		out = ConvertFromCDM::convert(data->getStepWidth().get());
		return true;
	}
	return false;
}

double Range::getStepWidth() const {
	return ConvertFromCDM::convert(data->getStepWidth().get());
}

bool Range::hasStepWidth() const {
	return data->getStepWidth().present();
}

Range & Range::setRelativeAccuracy(const double & value) {
	data->setRelativeAccuracy(ConvertToCDM::convert(value));
	return *this;
}

bool Range::getRelativeAccuracy(double & out) const {
	if (data->getRelativeAccuracy().present()) {
		out = ConvertFromCDM::convert(data->getRelativeAccuracy().get());
		return true;
	}
	return false;
}

double Range::getRelativeAccuracy() const {
	return ConvertFromCDM::convert(data->getRelativeAccuracy().get());
}

bool Range::hasRelativeAccuracy() const {
	return data->getRelativeAccuracy().present();
}

Range & Range::setAbsoluteAccuracy(const double & value) {
	data->setAbsoluteAccuracy(ConvertToCDM::convert(value));
	return *this;
}

bool Range::getAbsoluteAccuracy(double & out) const {
	if (data->getAbsoluteAccuracy().present()) {
		out = ConvertFromCDM::convert(data->getAbsoluteAccuracy().get());
		return true;
	}
	return false;
}

double Range::getAbsoluteAccuracy() const {
	return ConvertFromCDM::convert(data->getAbsoluteAccuracy().get());
}

bool Range::hasAbsoluteAccuracy() const {
	return data->getAbsoluteAccuracy().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

