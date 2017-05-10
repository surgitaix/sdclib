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
 *  SystemMetaData.cpp
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

#include "OSCLib/Data/OSCP/MDIB/SystemMetaData.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/LocalizedText.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

SystemMetaData::SystemMetaData() : data(Defaults::SystemMetaData()) {
}

SystemMetaData::operator CDM::SystemMetaData() const {
	return *data;
}

SystemMetaData::SystemMetaData(const CDM::SystemMetaData & object) : data(new CDM::SystemMetaData(object)) {

}

SystemMetaData::SystemMetaData(const SystemMetaData & object) : data(new CDM::SystemMetaData(*object.data)) {

}

SystemMetaData::~SystemMetaData() {

}

void SystemMetaData::copyFrom(const SystemMetaData & object) {
	*data = *object.data;
}

SystemMetaData & SystemMetaData:: operator=(const SystemMetaData & object) {
	copyFrom(object);
	return *this;
}


SystemMetaData & SystemMetaData::setUDI(const std::string & value) {
	data->UDI(ConvertToCDM::convert(value));
	return *this;
}

bool SystemMetaData::getUDI(std::string & out) const {
	if (data->UDI().present()) {
		out = ConvertFromCDM::convert(data->UDI().get());
		return true;
	}
	return false;
}

std::string SystemMetaData::getUDI() const {
	return ConvertFromCDM::convert(data->UDI().get());
}
	
bool SystemMetaData::hasUDI() const {
	return data->UDI().present();
}
	
SystemMetaData & SystemMetaData::addManufacturer(const LocalizedText & value) {
	data->Manufacturer().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> SystemMetaData::getManufacturer() const {
	std::vector<LocalizedText> result;
	result.reserve(data->Manufacturer().size());
	for (const auto & value: data->Manufacturer()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void SystemMetaData::clearManufacturer() {
	data->Manufacturer().clear();
}

SystemMetaData & SystemMetaData::addModelName(const LocalizedText & value) {
	data->ModelName().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> SystemMetaData::getModelName() const {
	std::vector<LocalizedText> result;
	result.reserve(data->ModelName().size());
	for (const auto & value: data->ModelName()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void SystemMetaData::clearModelName() {
	data->ModelName().clear();
}

SystemMetaData & SystemMetaData::addModelNumber(const std::string & value) {
	data->ModelNumber().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> SystemMetaData::getModelNumber() const {
	std::vector<std::string> result;
	result.reserve(data->ModelNumber().size());
	for (const auto & value: data->ModelNumber()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void SystemMetaData::clearModelNumber() {
	data->ModelNumber().clear();
}

SystemMetaData & SystemMetaData::addSerialNumber(const std::string & value) {
	data->SerialNumber().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> SystemMetaData::getSerialNumber() const {
	std::vector<std::string> result;
	result.reserve(data->SerialNumber().size());
	for (const auto & value: data->SerialNumber()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void SystemMetaData::clearSerialNumber() {
	data->SerialNumber().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

