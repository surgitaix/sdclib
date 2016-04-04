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
 *  DICOMNetworkAE.cpp
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

#include "OSCLib/Data/OSCP/MDIB/DICOMNetworkAE.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/DICOMTransferCapability.h"
#include "OSCLib/Data/OSCP/MDIB/LocalizedText.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

DICOMNetworkAE::DICOMNetworkAE() : data(Defaults::DICOMNetworkAE()) {
}

DICOMNetworkAE::operator CDM::DICOMNetworkAE() const {
	return *data;
}

DICOMNetworkAE::DICOMNetworkAE(const CDM::DICOMNetworkAE & object) : data(new CDM::DICOMNetworkAE(object)) {

}

DICOMNetworkAE::DICOMNetworkAE(const DICOMNetworkAE & object) : data(new CDM::DICOMNetworkAE(*object.data)) {

}

DICOMNetworkAE::~DICOMNetworkAE() {

}

void DICOMNetworkAE::copyFrom(const DICOMNetworkAE & object) {
	*data = *object.data;
}

DICOMNetworkAE & DICOMNetworkAE:: operator=(const DICOMNetworkAE & object) {
	copyFrom(object);
	return *this;
}


DICOMNetworkAE & DICOMNetworkAE::setAETitle(const std::string & value) {
	data->AETitle(ConvertToCDM::convert(value));
	return *this;
}


std::string DICOMNetworkAE::getAETitle() const {
	return ConvertFromCDM::convert(data->AETitle());
}
	
DICOMNetworkAE & DICOMNetworkAE::setAssociationInitiator(const bool & value) {
	data->AssociationInitiator(ConvertToCDM::convert(value));
	return *this;
}


bool DICOMNetworkAE::getAssociationInitiator() const {
	return ConvertFromCDM::convert(data->AssociationInitiator());
}
	
DICOMNetworkAE & DICOMNetworkAE::setAssociationAcceptor(const bool & value) {
	data->AssociationAcceptor(ConvertToCDM::convert(value));
	return *this;
}


bool DICOMNetworkAE::getAssociationAcceptor() const {
	return ConvertFromCDM::convert(data->AssociationAcceptor());
}
	
DICOMNetworkAE & DICOMNetworkAE::setDescription(const std::string & value) {
	data->Description(ConvertToCDM::convert(value));
	return *this;
}

bool DICOMNetworkAE::getDescription(std::string & out) const {
	if (data->Description().present()) {
		out = ConvertFromCDM::convert(data->Description().get());
		return true;
	}
	return false;
}

std::string DICOMNetworkAE::getDescription() const {
	return ConvertFromCDM::convert(data->Description().get());
}
	
bool DICOMNetworkAE::hasDescription() const {
	return data->Description().present();
}
	
DICOMNetworkAE & DICOMNetworkAE::addNetworkConnectionReference(const std::string & value) {
	data->NetworkConnectionReference().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> DICOMNetworkAE::getNetworkConnectionReferences() const {
	std::vector<std::string> result;
	result.reserve(data->NetworkConnectionReference().size());
	for (const auto & value: data->NetworkConnectionReference()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DICOMNetworkAE::clearNetworkConnectionReferences() {
	data->NetworkConnectionReference().clear();
}

DICOMNetworkAE & DICOMNetworkAE::addTransferCapability(const DICOMTransferCapability & value) {
	data->TransferCapability().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<DICOMTransferCapability> DICOMNetworkAE::getTransferCapabilities() const {
	std::vector<DICOMTransferCapability> result;
	result.reserve(data->TransferCapability().size());
	for (const auto & value: data->TransferCapability()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DICOMNetworkAE::clearTransferCapabilities() {
	data->TransferCapability().clear();
}

DICOMNetworkAE & DICOMNetworkAE::addApplicationCluster(const LocalizedText & value) {
	data->ApplicationCluster().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> DICOMNetworkAE::getApplicationClusters() const {
	std::vector<LocalizedText> result;
	result.reserve(data->ApplicationCluster().size());
	for (const auto & value: data->ApplicationCluster()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DICOMNetworkAE::clearApplicationClusters() {
	data->ApplicationCluster().clear();
}

DICOMNetworkAE & DICOMNetworkAE::addSupportedCharacterSet(const std::string & value) {
	data->SupportedCharacterSet().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> DICOMNetworkAE::getSupportedCharacterSets() const {
	std::vector<std::string> result;
	result.reserve(data->SupportedCharacterSet().size());
	for (const auto & value: data->SupportedCharacterSet()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DICOMNetworkAE::clearSupportedCharacterSets() {
	data->SupportedCharacterSet().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

