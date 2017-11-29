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
 *  Author: besting, buerger, roehser
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


MetaData::MetaData(
) : data(Defaults::MetaDataInit(
)) {}

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
	data = std::shared_ptr<CDM::MetaData>( new CDM::MetaData(*object.data));
}

MetaData & MetaData:: operator=(const MetaData & object) {
	copyFrom(object);
	return *this;
}


MetaData & MetaData::setLotNumber(const std::string & value) {
	data->LotNumber(ConvertToCDM::convert(value));
	return *this;
}

bool MetaData::getLotNumber(std::string & out) const {
	if (data->LotNumber().present()) {
		out = ConvertFromCDM::convert(data->LotNumber().get());
		return true;
	}
	return false;
}

std::string MetaData::getLotNumber() const {
	return ConvertFromCDM::convert(data->LotNumber().get());
}
	
bool MetaData::hasLotNumber() const {
	return data->LotNumber().present();
}
	
MetaData & MetaData::setManufactureDate(const xml_schema::DateTime & value) {
	data->ManufactureDate(ConvertToCDM::convert(value));
	return *this;
}

bool MetaData::getManufactureDate(xml_schema::DateTime & out) const {
	if (data->ManufactureDate().present()) {
		out = ConvertFromCDM::convert(data->ManufactureDate().get());
		return true;
	}
	return false;
}

xml_schema::DateTime MetaData::getManufactureDate() const {
	return ConvertFromCDM::convert(data->ManufactureDate().get());
}
	
bool MetaData::hasManufactureDate() const {
	return data->ManufactureDate().present();
}
	
MetaData & MetaData::setExpirationDate(const xml_schema::DateTime & value) {
	data->ExpirationDate(ConvertToCDM::convert(value));
	return *this;
}

bool MetaData::getExpirationDate(xml_schema::DateTime & out) const {
	if (data->ExpirationDate().present()) {
		out = ConvertFromCDM::convert(data->ExpirationDate().get());
		return true;
	}
	return false;
}

xml_schema::DateTime MetaData::getExpirationDate() const {
	return ConvertFromCDM::convert(data->ExpirationDate().get());
}
	
bool MetaData::hasExpirationDate() const {
	return data->ExpirationDate().present();
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

std::vector<Udi> MetaData::getUdiList() const {
	std::vector<Udi> result;
	result.reserve(data->Udi().size());
	for (const auto & value: data->Udi()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void MetaData::clearUdiList() {
	data->Udi().clear();
}

MetaData & MetaData::addManufacturer(const LocalizedText & value) {
	data->Manufacturer().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> MetaData::getManufacturerList() const {
	std::vector<LocalizedText> result;
	result.reserve(data->Manufacturer().size());
	for (const auto & value: data->Manufacturer()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void MetaData::clearManufacturerList() {
	data->Manufacturer().clear();
}

MetaData & MetaData::addModelName(const LocalizedText & value) {
	data->ModelName().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> MetaData::getModelNameList() const {
	std::vector<LocalizedText> result;
	result.reserve(data->ModelName().size());
	for (const auto & value: data->ModelName()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void MetaData::clearModelNameList() {
	data->ModelName().clear();
}

MetaData & MetaData::addSerialNumber(const std::string & value) {
	data->SerialNumber().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> MetaData::getSerialNumberList() const {
	std::vector<std::string> result;
	result.reserve(data->SerialNumber().size());
	for (const auto & value: data->SerialNumber()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void MetaData::clearSerialNumberList() {
	data->SerialNumber().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

