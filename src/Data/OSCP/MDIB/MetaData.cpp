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
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

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


MetaData & MetaData::setUdi(const std::string & value) {
	data->Udi(ConvertToCDM::convert(value));
	return *this;
}

bool MetaData::getUdi(std::string & out) const {
	if (data->Udi().present()) {
		out = ConvertFromCDM::convert(data->Udi().get());
		return true;
	}
	return false;
}

std::string MetaData::getUdi() const {
	return ConvertFromCDM::convert(data->Udi().get());
}
	
bool MetaData::hasUdi() const {
	return data->Udi().present();
}
	
MetaData & MetaData::addManufacturer(const LocalizedText & value) {
	data->Manufacturer().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> MetaData::getManufacturer() const {
	std::vector<LocalizedText> result;
	result.reserve(data->Manufacturer().size());
	for (const auto & value: data->Manufacturer()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void MetaData::clearManufacturer() {
	data->Manufacturer().clear();
}

MetaData & MetaData::addModelName(const LocalizedText & value) {
	data->ModelName().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> MetaData::getModelName() const {
	std::vector<LocalizedText> result;
	result.reserve(data->ModelName().size());
	for (const auto & value: data->ModelName()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void MetaData::clearModelName() {
	data->ModelName().clear();
}

MetaData & MetaData::addModelNumber(const std::string & value) {
	data->ModelNumber().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> MetaData::getModelNumber() const {
	std::vector<std::string> result;
	result.reserve(data->ModelNumber().size());
	for (const auto & value: data->ModelNumber()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void MetaData::clearModelNumber() {
	data->ModelNumber().clear();
}

MetaData & MetaData::addSerialNumber(const std::string & value) {
	data->SerialNumber().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> MetaData::getSerialNumber() const {
	std::vector<std::string> result;
	result.reserve(data->SerialNumber().size());
	for (const auto & value: data->SerialNumber()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void MetaData::clearSerialNumber() {
	data->SerialNumber().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

