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

#include "SDCLib/Data/SDC/MDIB/MetaData.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/Udi.h"
#include "SDCLib/Data/SDC/MDIB/LocalizedText.h"

namespace SDCLib {
namespace Data {
namespace SDC {


MetaData::MetaData(
) : data(Defaults::MetaDataInit(
))
{}

MetaData::operator CDM::MetaData() const {
	return *data;
}

MetaData::MetaData(const CDM::MetaData & object)
: data(new CDM::MetaData(object))
{ }

MetaData::MetaData(const MetaData & object)
: data(std::make_shared<CDM::MetaData>(*object.data))
{ }

void MetaData::copyFrom(const MetaData & object) {
	data = std::make_shared<CDM::MetaData>(*object.data);
}

MetaData & MetaData:: operator=(const MetaData& object) {
	copyFrom(object);
	return *this;
}


MetaData & MetaData::setLotNumber(const std::string & value) {
	data->setLotNumber(ConvertToCDM::convert(value));
	return *this;
}

bool MetaData::getLotNumber(std::string & out) const {
	if (data->getLotNumber().present()) {
		out = ConvertFromCDM::convert(data->getLotNumber().get());
		return true;
	}
	return false;
}

std::string MetaData::getLotNumber() const {
	return ConvertFromCDM::convert(data->getLotNumber().get());
}

bool MetaData::hasLotNumber() const {
	return data->getLotNumber().present();
}

MetaData & MetaData::setManufactureDate(const xml_schema::DateTime & value) {
	data->setManufactureDate(ConvertToCDM::convert(value));
	return *this;
}

bool MetaData::getManufactureDate(xml_schema::DateTime & out) const {
	if (data->getManufactureDate().present()) {
		out = ConvertFromCDM::convert(data->getManufactureDate().get());
		return true;
	}
	return false;
}

xml_schema::DateTime MetaData::getManufactureDate() const {
	return ConvertFromCDM::convert(data->getManufactureDate().get());
}

bool MetaData::hasManufactureDate() const {
	return data->getManufactureDate().present();
}

MetaData & MetaData::setExpirationDate(const xml_schema::DateTime & value) {
	data->setExpirationDate(ConvertToCDM::convert(value));
	return *this;
}

bool MetaData::getExpirationDate(xml_schema::DateTime & out) const {
	if (data->getExpirationDate().present()) {
		out = ConvertFromCDM::convert(data->getExpirationDate().get());
		return true;
	}
	return false;
}

xml_schema::DateTime MetaData::getExpirationDate() const {
	return ConvertFromCDM::convert(data->getExpirationDate().get());
}

bool MetaData::hasExpirationDate() const {
	return data->getExpirationDate().present();
}

MetaData & MetaData::setModelNumber(const std::string & value) {
	data->setModelNumber(ConvertToCDM::convert(value));
	return *this;
}

bool MetaData::getModelNumber(std::string & out) const {
	if (data->getModelNumber().present()) {
		out = ConvertFromCDM::convert(data->getModelNumber().get());
		return true;
	}
	return false;
}

std::string MetaData::getModelNumber() const {
	return ConvertFromCDM::convert(data->getModelNumber().get());
}

bool MetaData::hasModelNumber() const {
	return data->getModelNumber().present();
}

MetaData & MetaData::addUdi(const Udi & value) {
	data->getUdi().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<Udi> MetaData::getUdiList() const {
	std::vector<Udi> result;
	result.reserve(data->getUdi().size());
	for (const auto & value: data->getUdi()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void MetaData::clearUdiList() {
	data->getUdi().clear();
}

MetaData & MetaData::addManufacturer(const LocalizedText & value) {
	data->getManufacturer().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> MetaData::getManufacturerList() const {
	std::vector<LocalizedText> result;
	result.reserve(data->getManufacturer().size());
	for (const auto & value: data->getManufacturer()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void MetaData::clearManufacturerList() {
	data->getManufacturer().clear();
}

MetaData & MetaData::addModelName(const LocalizedText & value) {
	data->getModelName().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> MetaData::getModelNameList() const {
	std::vector<LocalizedText> result;
	result.reserve(data->getModelName().size());
	for (const auto & value: data->getModelName()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void MetaData::clearModelNameList() {
	data->getModelName().clear();
}

MetaData & MetaData::addSerialNumber(const std::string & value) {
	data->getSerialNumber().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> MetaData::getSerialNumberList() const {
	std::vector<std::string> result;
	result.reserve(data->getSerialNumber().size());
	for (const auto & value: data->getSerialNumber()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void MetaData::clearSerialNumberList() {
	data->getSerialNumber().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

