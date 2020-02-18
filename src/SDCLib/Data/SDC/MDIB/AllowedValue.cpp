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
 *  AllowedValue.cpp
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

#include "SDCLib/Data/SDC/MDIB/AllowedValue.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/CodedValue.h"
#include "SDCLib/Data/SDC/MDIB/InstanceIdentifier.h"
#include "SDCLib/Data/SDC/MDIB/Measurement.h"

namespace SDCLib {
namespace Data {
namespace SDC {


AllowedValue::AllowedValue(
		std::string value
) : data(Defaults::AllowedValueInit(
		value
))
{}

AllowedValue::operator CDM::AllowedValue() const {
	return *data;
}

AllowedValue::AllowedValue(const CDM::AllowedValue & object)
: data(new CDM::AllowedValue(object))
{ }

AllowedValue::AllowedValue(const AllowedValue & object)
: data(std::make_shared<CDM::AllowedValue>(*object.data))
{ }

void AllowedValue::copyFrom(const AllowedValue & object) {
	data = std::make_shared<CDM::AllowedValue>(*object.data);
}

AllowedValue & AllowedValue:: operator=(const AllowedValue& object) {
	copyFrom(object);
	return *this;
}


AllowedValue & AllowedValue::setValue(const std::string & value) {
	data->setValue(ConvertToCDM::convert(value));
	return *this;
}


std::string AllowedValue::getValue() const {
	return ConvertFromCDM::convert(data->getValue());
}

AllowedValue & AllowedValue::setType(const CodedValue & value) {
	data->setType(ConvertToCDM::convert(value));
	return *this;
}

bool AllowedValue::getType(CodedValue & out) const {
	if (data->getType().present()) {
		out = ConvertFromCDM::convert(data->getType().get());
		return true;
	}
	return false;
}

CodedValue AllowedValue::getType() const {
	return ConvertFromCDM::convert(data->getType().get());
}

bool AllowedValue::hasType() const {
	return data->getType().present();
}

AllowedValue & AllowedValue::setIdentification(const InstanceIdentifier & value) {
	data->setIdentification(ConvertToCDM::convert(value));
	return *this;
}

bool AllowedValue::getIdentification(InstanceIdentifier & out) const {
	if (data->getIdentification().present()) {
		out = ConvertFromCDM::convert(data->getIdentification().get());
		return true;
	}
	return false;
}

InstanceIdentifier AllowedValue::getIdentification() const {
	return ConvertFromCDM::convert(data->getIdentification().get());
}

bool AllowedValue::hasIdentification() const {
	return data->getIdentification().present();
}

AllowedValue & AllowedValue::setCharacteristic(const Measurement & value) {
	data->setCharacteristic(ConvertToCDM::convert(value));
	return *this;
}

bool AllowedValue::getCharacteristic(Measurement & out) const {
	if (data->getCharacteristic().present()) {
		out = ConvertFromCDM::convert(data->getCharacteristic().get());
		return true;
	}
	return false;
}

Measurement AllowedValue::getCharacteristic() const {
	return ConvertFromCDM::convert(data->getCharacteristic().get());
}

bool AllowedValue::hasCharacteristic() const {
	return data->getCharacteristic().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

