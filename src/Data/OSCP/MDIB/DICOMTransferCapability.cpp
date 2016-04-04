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
 *  DICOMTransferCapability.cpp
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

#include "OSCLib/Data/OSCP/MDIB/DICOMTransferCapability.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"


namespace OSCLib {
namespace Data {
namespace OSCP {

DICOMTransferCapability::DICOMTransferCapability() : data(Defaults::DICOMTransferCapability()) {
}

DICOMTransferCapability::operator CDM::DICOMTransferCapability() const {
	return *data;
}

DICOMTransferCapability::DICOMTransferCapability(const CDM::DICOMTransferCapability & object) : data(new CDM::DICOMTransferCapability(object)) {

}

DICOMTransferCapability::DICOMTransferCapability(const DICOMTransferCapability & object) : data(new CDM::DICOMTransferCapability(*object.data)) {

}

DICOMTransferCapability::~DICOMTransferCapability() {

}

void DICOMTransferCapability::copyFrom(const DICOMTransferCapability & object) {
	*data = *object.data;
}

DICOMTransferCapability & DICOMTransferCapability:: operator=(const DICOMTransferCapability & object) {
	copyFrom(object);
	return *this;
}


DICOMTransferCapability & DICOMTransferCapability::setSOPClass(const std::string & value) {
	data->SOPClass(ConvertToCDM::convert(value));
	return *this;
}


std::string DICOMTransferCapability::getSOPClass() const {
	return ConvertFromCDM::convert(data->SOPClass());
}
	
DICOMTransferCapability & DICOMTransferCapability::setTransferRole(const DICOMTransferRole & value) {
	data->TransferRole(ConvertToCDM::convert(value));
	return *this;
}


DICOMTransferRole DICOMTransferCapability::getTransferRole() const {
	return ConvertFromCDM::convert(data->TransferRole());
}
	
DICOMTransferCapability & DICOMTransferCapability::addTransferSyntax(const std::string & value) {
	data->TransferSyntax().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> DICOMTransferCapability::getTransferSyntaxes() const {
	std::vector<std::string> result;
	result.reserve(data->TransferSyntax().size());
	for (const auto & value: data->TransferSyntax()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DICOMTransferCapability::clearTransferSyntaxes() {
	data->TransferSyntax().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

