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
 *  DicomTransferCapability.cpp
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

#include "OSCLib/Data/OSCP/MDIB/DicomTransferCapability.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"


namespace OSCLib {
namespace Data {
namespace OSCP {


DicomTransferCapability::DicomTransferCapability(
		std::string sopclass
		, 
		DicomTransferRole transferrole
) : data(Defaults::DicomTransferCapabilityInit(
		sopclass
		,
		transferrole
)) {}

DicomTransferCapability::operator CDM::DicomTransferCapability() const {
	return *data;
}

DicomTransferCapability::DicomTransferCapability(const CDM::DicomTransferCapability & object) : data(new CDM::DicomTransferCapability(object)) {

}

DicomTransferCapability::DicomTransferCapability(const DicomTransferCapability & object) : data(new CDM::DicomTransferCapability(*object.data)) {

}

DicomTransferCapability::~DicomTransferCapability() {

}

void DicomTransferCapability::copyFrom(const DicomTransferCapability & object) {
	*data = *object.data;
}

DicomTransferCapability & DicomTransferCapability:: operator=(const DicomTransferCapability & object) {
	copyFrom(object);
	return *this;
}


DicomTransferCapability & DicomTransferCapability::setSopClass(const std::string & value) {
	data->SopClass(ConvertToCDM::convert(value));
	return *this;
}


std::string DicomTransferCapability::getSopClass() const {
	return ConvertFromCDM::convert(data->SopClass());
}
	
DicomTransferCapability & DicomTransferCapability::setTransferRole(const DicomTransferRole & value) {
	data->TransferRole(ConvertToCDM::convert(value));
	return *this;
}


DicomTransferRole DicomTransferCapability::getTransferRole() const {
	return ConvertFromCDM::convert(data->TransferRole());
}
	
DicomTransferCapability & DicomTransferCapability::addTransferSyntax(const std::string & value) {
	data->TransferSyntax().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> DicomTransferCapability::getTransferSyntaxList() const {
	std::vector<std::string> result;
	result.reserve(data->TransferSyntax().size());
	for (const auto & value: data->TransferSyntax()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DicomTransferCapability::clearTransferSyntaxList() {
	data->TransferSyntax().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

