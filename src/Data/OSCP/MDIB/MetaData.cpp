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
 *  MetaData.cpp
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

#include "OSCLib/Data/OSCP/MDIB/MetaData.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/Udi.h"
#include "OSCLib/Data/OSCP/MDIB/LocalizedText.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

MetaData::MetaData() : data(Defaults::MetaData()) {
}

MetaData::operator CDM::MetaData() const {
	return *data;
}

MetaData::MetaData(const CDM::MetaData & object) : data(new CDM::MetaData(object)) {

}

MetaData::MetaData(const MetaData & object) : data(new CDM::MetaData(*object.data)) {

}

MetaData::~MetaData() {

}

void MetaData::copyFrom(const MetaData & object) {
	*data = *object.data;
}

MetaData & MetaData:: operator=(const MetaData & object) {
	copyFrom(object);
	return *this;
}


MetaData & MetaData::setModelNumber(const std::string & value) {
	data->ModelNumber(ConvertToCDM::convert(value));
	return *this;
}

bool MetaData::getModelNumber(std::string & out) const {
	if (data->ModelNumber().present()) {
		out = ConvertFromCDM::convert(data->ModelNumber().get());
		return true;
	}
	return false;
}

std::string MetaData::getModelNumber() const {
	return ConvertFromCDM::convert(data->ModelNumber().get());
}
	
bool MetaData::hasModelNumber() const {
	return data->ModelNumber().present();
}
	
MetaData & MetaData::addUdi(const Udi & value) {
	data->Udi().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<Udi> MetaData::getUdiLists() const {
	std::vector<Udi> result;
	result.reserve(data->Udi().size());
	for (const auto & value: data->Udi()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void MetaData::clearUdiLists() {
	data->Udi().clear();
}

MetaData & MetaData::addManufacturer(const LocalizedText & value) {
	data->Manufacturer().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> MetaData::getManufacturerLists() const {
	std::vector<LocalizedText> result;
	result.reserve(data->Manufacturer().size());
	for (const auto & value: data->Manufacturer()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void MetaData::clearManufacturerLists() {
	data->Manufacturer().clear();
}

MetaData & MetaData::addModelName(const LocalizedText & value) {
	data->ModelName().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> MetaData::getModelNameLists() const {
	std::vector<LocalizedText> result;
	result.reserve(data->ModelName().size());
	for (const auto & value: data->ModelName()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void MetaData::clearModelNameLists() {
	data->ModelName().clear();
}

MetaData & MetaData::addSerialNumber(const std::string & value) {
	data->SerialNumber().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> MetaData::getSerialNumberLists() const {
	std::vector<std::string> result;
	result.reserve(data->SerialNumber().size());
	for (const auto & value: data->SerialNumber()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void MetaData::clearSerialNumberLists() {
	data->SerialNumber().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

