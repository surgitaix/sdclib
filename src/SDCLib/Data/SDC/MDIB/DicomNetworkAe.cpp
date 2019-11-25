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
 *  DicomNetworkAe.cpp
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

#include "SDCLib/Data/SDC/MDIB/DicomNetworkAe.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/DicomTransferCapability.h"
#include "SDCLib/Data/SDC/MDIB/LocalizedText.h"

namespace SDCLib {
namespace Data {
namespace SDC {


DicomNetworkAe::DicomNetworkAe(
		std::string aetitle
		,
		xml_schema::Idrefs networkconnectionreference
		,
		bool associationinitiator
		,
		bool associationacceptor
) : data(Defaults::DicomNetworkAeInit(
		aetitle
		,
		networkconnectionreference
		,
		associationinitiator
		,
		associationacceptor
)) {}

DicomNetworkAe::operator CDM::DicomNetworkAe() const {
	return *data;
}

DicomNetworkAe::DicomNetworkAe(const CDM::DicomNetworkAe & object) : data(new CDM::DicomNetworkAe(object)) {

}

DicomNetworkAe::DicomNetworkAe(const DicomNetworkAe & object) : data(new CDM::DicomNetworkAe(*object.data)) {

}

DicomNetworkAe::~DicomNetworkAe() {

}

void DicomNetworkAe::copyFrom(const DicomNetworkAe & object) {
	data = std::shared_ptr<CDM::DicomNetworkAe>( new CDM::DicomNetworkAe(*object.data));
}

DicomNetworkAe & DicomNetworkAe:: operator=(const DicomNetworkAe & object) {
	copyFrom(object);
	return *this;
}


DicomNetworkAe & DicomNetworkAe::setAeTitle(const std::string & value) {
	data->setAeTitle(ConvertToCDM::convert(value));
	return *this;
}


std::string DicomNetworkAe::getAeTitle() const {
	return ConvertFromCDM::convert(data->getAeTitle());
}

DicomNetworkAe & DicomNetworkAe::setNetworkConnectionReference(const xml_schema::Idrefs & value) {
	data->setNetworkConnectionReference(ConvertToCDM::convert(value));
	return *this;
}


xml_schema::Idrefs DicomNetworkAe::getNetworkConnectionReference() const {
	return ConvertFromCDM::convert(data->getNetworkConnectionReference());
}

DicomNetworkAe & DicomNetworkAe::setAssociationInitiator(const bool & value) {
	data->setAssociationInitiator(ConvertToCDM::convert(value));
	return *this;
}


bool DicomNetworkAe::getAssociationInitiator() const {
	return ConvertFromCDM::convert(data->getAssociationInitiator());
}

DicomNetworkAe & DicomNetworkAe::setAssociationAcceptor(const bool & value) {
	data->setAssociationAcceptor(ConvertToCDM::convert(value));
	return *this;
}


bool DicomNetworkAe::getAssociationAcceptor() const {
	return ConvertFromCDM::convert(data->getAssociationAcceptor());
}

DicomNetworkAe & DicomNetworkAe::addTransferCapability(const DicomTransferCapability & value) {
	data->getTransferCapability().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<DicomTransferCapability> DicomNetworkAe::getTransferCapabilityList() const {
	std::vector<DicomTransferCapability> result;
	result.reserve(data->getTransferCapability().size());
	for (const auto & value: data->getTransferCapability()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DicomNetworkAe::clearTransferCapabilityList() {
	data->getTransferCapability().clear();
}

DicomNetworkAe & DicomNetworkAe::addDescription(const LocalizedText & value) {
	data->getDescription().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> DicomNetworkAe::getDescriptionList() const {
	std::vector<LocalizedText> result;
	result.reserve(data->getDescription().size());
	for (const auto & value: data->getDescription()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DicomNetworkAe::clearDescriptionList() {
	data->getDescription().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

