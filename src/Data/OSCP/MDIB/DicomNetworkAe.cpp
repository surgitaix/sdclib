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
 *  Author: besting, roehser
 */
 
/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 * 
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "OSCLib/Data/OSCP/MDIB/DicomNetworkAe.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/DicomTransferCapability.h"
#include "OSCLib/Data/OSCP/MDIB/LocalizedText.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

DicomNetworkAe::DicomNetworkAe() : data(Defaults::DicomNetworkAe()) {
}

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
	*data = *object.data;
}

DicomNetworkAe & DicomNetworkAe:: operator=(const DicomNetworkAe & object) {
	copyFrom(object);
	return *this;
}


DicomNetworkAe & DicomNetworkAe::setAeTitle(const std::string & value) {
	data->AeTitle(ConvertToCDM::convert(value));
	return *this;
}


std::string DicomNetworkAe::getAeTitle() const {
	return ConvertFromCDM::convert(data->AeTitle());
}
	
DicomNetworkAe & DicomNetworkAe::setNetworkConnectionReference(const std::string & value) {
	data->NetworkConnectionReference(ConvertToCDM::convert(value));
	return *this;
}


std::string DicomNetworkAe::getNetworkConnectionReference() const {
	return ConvertFromCDM::convert(data->NetworkConnectionReference());
}
	
DicomNetworkAe & DicomNetworkAe::setAssociationInitiator(const bool & value) {
	data->AssociationInitiator(ConvertToCDM::convert(value));
	return *this;
}


bool DicomNetworkAe::getAssociationInitiator() const {
	return ConvertFromCDM::convert(data->AssociationInitiator());
}
	
DicomNetworkAe & DicomNetworkAe::setAssociationAcceptor(const bool & value) {
	data->AssociationAcceptor(ConvertToCDM::convert(value));
	return *this;
}


bool DicomNetworkAe::getAssociationAcceptor() const {
	return ConvertFromCDM::convert(data->AssociationAcceptor());
}
	
DicomNetworkAe & DicomNetworkAe::addTransferCapability(const DicomTransferCapability & value) {
	data->TransferCapability().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<DicomTransferCapability> DicomNetworkAe::getTransferCapabilities() const {
	std::vector<DicomTransferCapability> result;
	result.reserve(data->TransferCapability().size());
	for (const auto & value: data->TransferCapability()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DicomNetworkAe::clearTransferCapabilities() {
	data->TransferCapability().clear();
}

DicomNetworkAe & DicomNetworkAe::addApplicationCluster(const LocalizedText & value) {
	data->ApplicationCluster().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> DicomNetworkAe::getApplicationClusters() const {
	std::vector<LocalizedText> result;
	result.reserve(data->ApplicationCluster().size());
	for (const auto & value: data->ApplicationCluster()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DicomNetworkAe::clearApplicationClusters() {
	data->ApplicationCluster().clear();
}

DicomNetworkAe & DicomNetworkAe::addSupportedCharacterSet(const std::string & value) {
	data->SupportedCharacterSet().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> DicomNetworkAe::getSupportedCharacterSets() const {
	std::vector<std::string> result;
	result.reserve(data->SupportedCharacterSet().size());
	for (const auto & value: data->SupportedCharacterSet()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DicomNetworkAe::clearSupportedCharacterSets() {
	data->SupportedCharacterSet().clear();
}

DicomNetworkAe & DicomNetworkAe::addDescription(const LocalizedText & value) {
	data->Description().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> DicomNetworkAe::getDescriptions() const {
	std::vector<LocalizedText> result;
	result.reserve(data->Description().size());
	for (const auto & value: data->Description()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DicomNetworkAe::clearDescriptions() {
	data->Description().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

