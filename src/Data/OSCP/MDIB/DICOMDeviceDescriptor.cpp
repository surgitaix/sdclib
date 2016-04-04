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
 *  DICOMDeviceDescriptor.cpp
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

#include "OSCLib/Data/OSCP/MDIB/DICOMDeviceDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/Base64Binary.h"
#include "OSCLib/Data/OSCP/MDIB/DICOMNetworkAE.h"
#include "OSCLib/Data/OSCP/MDIB/DICOMNetworkConnection.h"
#include "OSCLib/Data/OSCP/MDIB/LocalizedText.h"
#include "OSCLib/Data/OSCP/MDIB/ClockDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SystemContext.h"
#include "OSCLib/Data/OSCP/MDIB/SystemMetaData.h"
#include "OSCLib/Data/OSCP/MDIB/ProductionSpecification.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

DICOMDeviceDescriptor::DICOMDeviceDescriptor() : data(Defaults::DICOMDeviceDescriptor()) {
}

DICOMDeviceDescriptor::operator CDM::DICOMDeviceDescriptor() const {
	return *data;
}

DICOMDeviceDescriptor::DICOMDeviceDescriptor(const CDM::DICOMDeviceDescriptor & object) : data(new CDM::DICOMDeviceDescriptor(object)) {

}

DICOMDeviceDescriptor::DICOMDeviceDescriptor(const DICOMDeviceDescriptor & object) : data(new CDM::DICOMDeviceDescriptor(*object.data)) {

}

DICOMDeviceDescriptor::~DICOMDeviceDescriptor() {

}

void DICOMDeviceDescriptor::copyFrom(const DICOMDeviceDescriptor & object) {
	*data = *object.data;
}

DICOMDeviceDescriptor & DICOMDeviceDescriptor:: operator=(const DICOMDeviceDescriptor & object) {
	copyFrom(object);
	return *this;
}


DICOMDeviceDescriptor & DICOMDeviceDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool DICOMDeviceDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue DICOMDeviceDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool DICOMDeviceDescriptor::hasType() const {
	return data->Type().present();
}
	
DICOMDeviceDescriptor & DICOMDeviceDescriptor::setHandle(const std::string & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


std::string DICOMDeviceDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
DICOMDeviceDescriptor & DICOMDeviceDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool DICOMDeviceDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter DICOMDeviceDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool DICOMDeviceDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
DICOMDeviceDescriptor & DICOMDeviceDescriptor::setIntendedUse(const IntendedUse & value) {
	data->IntendedUse(ConvertToCDM::convert(value));
	return *this;
}

bool DICOMDeviceDescriptor::getIntendedUse(IntendedUse & out) const {
	if (data->IntendedUse().present()) {
		out = ConvertFromCDM::convert(data->IntendedUse().get());
		return true;
	}
	return false;
}

IntendedUse DICOMDeviceDescriptor::getIntendedUse() const {
	return ConvertFromCDM::convert(data->IntendedUse().get());
}
	
bool DICOMDeviceDescriptor::hasIntendedUse() const {
	return data->IntendedUse().present();
}
	
DICOMDeviceDescriptor & DICOMDeviceDescriptor::addProductionSpecification(const ProductionSpecification & value) {
	data->ProductionSpecification().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ProductionSpecification> DICOMDeviceDescriptor::getProductionSpecifications() const {
	std::vector<ProductionSpecification> result;
	result.reserve(data->ProductionSpecification().size());
	for (const auto & value: data->ProductionSpecification()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DICOMDeviceDescriptor::clearProductionSpecifications() {
	data->ProductionSpecification().clear();
}

DICOMDeviceDescriptor & DICOMDeviceDescriptor::setMetaData(const SystemMetaData & value) {
	data->MetaData(ConvertToCDM::convert(value));
	return *this;
}

bool DICOMDeviceDescriptor::getMetaData(SystemMetaData & out) const {
	if (data->MetaData().present()) {
		out = ConvertFromCDM::convert(data->MetaData().get());
		return true;
	}
	return false;
}

SystemMetaData DICOMDeviceDescriptor::getMetaData() const {
	return ConvertFromCDM::convert(data->MetaData().get());
}
	
bool DICOMDeviceDescriptor::hasMetaData() const {
	return data->MetaData().present();
}
	
DICOMDeviceDescriptor & DICOMDeviceDescriptor::setContext(const SystemContext & value) {
	data->Context(ConvertToCDM::convert(value));
	return *this;
}


SystemContext DICOMDeviceDescriptor::getContext() const {
	return ConvertFromCDM::convert(data->Context());
}
	
DICOMDeviceDescriptor & DICOMDeviceDescriptor::setClock(const ClockDescriptor & value) {
	data->Clock(ConvertToCDM::convert(value));
	return *this;
}

bool DICOMDeviceDescriptor::getClock(ClockDescriptor & out) const {
	if (data->Clock().present()) {
		out = ConvertFromCDM::convert(data->Clock().get());
		return true;
	}
	return false;
}

ClockDescriptor DICOMDeviceDescriptor::getClock() const {
	return ConvertFromCDM::convert(data->Clock().get());
}
	
bool DICOMDeviceDescriptor::hasClock() const {
	return data->Clock().present();
}
	
DICOMDeviceDescriptor & DICOMDeviceDescriptor::setDescription(const std::string & value) {
	data->Description(ConvertToCDM::convert(value));
	return *this;
}

bool DICOMDeviceDescriptor::getDescription(std::string & out) const {
	if (data->Description().present()) {
		out = ConvertFromCDM::convert(data->Description().get());
		return true;
	}
	return false;
}

std::string DICOMDeviceDescriptor::getDescription() const {
	return ConvertFromCDM::convert(data->Description().get());
}
	
bool DICOMDeviceDescriptor::hasDescription() const {
	return data->Description().present();
}
	
DICOMDeviceDescriptor & DICOMDeviceDescriptor::setStationName(const std::string & value) {
	data->StationName(ConvertToCDM::convert(value));
	return *this;
}

bool DICOMDeviceDescriptor::getStationName(std::string & out) const {
	if (data->StationName().present()) {
		out = ConvertFromCDM::convert(data->StationName().get());
		return true;
	}
	return false;
}

std::string DICOMDeviceDescriptor::getStationName() const {
	return ConvertFromCDM::convert(data->StationName().get());
}
	
bool DICOMDeviceDescriptor::hasStationName() const {
	return data->StationName().present();
}
	
DICOMDeviceDescriptor & DICOMDeviceDescriptor::setIssuerOfPatientID(const std::string & value) {
	data->IssuerOfPatientID(ConvertToCDM::convert(value));
	return *this;
}

bool DICOMDeviceDescriptor::getIssuerOfPatientID(std::string & out) const {
	if (data->IssuerOfPatientID().present()) {
		out = ConvertFromCDM::convert(data->IssuerOfPatientID().get());
		return true;
	}
	return false;
}

std::string DICOMDeviceDescriptor::getIssuerOfPatientID() const {
	return ConvertFromCDM::convert(data->IssuerOfPatientID().get());
}
	
bool DICOMDeviceDescriptor::hasIssuerOfPatientID() const {
	return data->IssuerOfPatientID().present();
}
	
DICOMDeviceDescriptor & DICOMDeviceDescriptor::addNetworkAE(const DICOMNetworkAE & value) {
	data->NetworkAE().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<DICOMNetworkAE> DICOMDeviceDescriptor::getNetworkAEs() const {
	std::vector<DICOMNetworkAE> result;
	result.reserve(data->NetworkAE().size());
	for (const auto & value: data->NetworkAE()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DICOMDeviceDescriptor::clearNetworkAEs() {
	data->NetworkAE().clear();
}

DICOMDeviceDescriptor & DICOMDeviceDescriptor::addNetworkConnection(const DICOMNetworkConnection & value) {
	data->NetworkConnection().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<DICOMNetworkConnection> DICOMDeviceDescriptor::getNetworkConnection() const {
	std::vector<DICOMNetworkConnection> result;
	result.reserve(data->NetworkConnection().size());
	for (const auto & value: data->NetworkConnection()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DICOMDeviceDescriptor::clearNetworkConnection() {
	data->NetworkConnection().clear();
}

DICOMDeviceDescriptor & DICOMDeviceDescriptor::addSoftwareVersion(const std::string & value) {
	data->SoftwareVersion().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> DICOMDeviceDescriptor::getSoftwareVersions() const {
	std::vector<std::string> result;
	result.reserve(data->SoftwareVersion().size());
	for (const auto & value: data->SoftwareVersion()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DICOMDeviceDescriptor::clearSoftwareVersions() {
	data->SoftwareVersion().clear();
}

DICOMDeviceDescriptor & DICOMDeviceDescriptor::addInstitutionName(const LocalizedText & value) {
	data->InstitutionName().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> DICOMDeviceDescriptor::getInstitutionNames() const {
	std::vector<LocalizedText> result;
	result.reserve(data->InstitutionName().size());
	for (const auto & value: data->InstitutionName()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DICOMDeviceDescriptor::clearInstitutionNames() {
	data->InstitutionName().clear();
}

DICOMDeviceDescriptor & DICOMDeviceDescriptor::addInstitutionAddress(const LocalizedText & value) {
	data->InstitutionAddress().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> DICOMDeviceDescriptor::getInstitutionAddresses() const {
	std::vector<LocalizedText> result;
	result.reserve(data->InstitutionAddress().size());
	for (const auto & value: data->InstitutionAddress()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DICOMDeviceDescriptor::clearInstitutionAddresses() {
	data->InstitutionAddress().clear();
}

DICOMDeviceDescriptor & DICOMDeviceDescriptor::addInstitutionalDepartmentName(const LocalizedText & value) {
	data->InstitutionalDepartmentName().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> DICOMDeviceDescriptor::getInstitutionalDepartmentNames() const {
	std::vector<LocalizedText> result;
	result.reserve(data->InstitutionalDepartmentName().size());
	for (const auto & value: data->InstitutionalDepartmentName()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DICOMDeviceDescriptor::clearInstitutionalDepartmentNames() {
	data->InstitutionalDepartmentName().clear();
}

DICOMDeviceDescriptor & DICOMDeviceDescriptor::addPrimaryDeviceType(const LocalizedText & value) {
	data->PrimaryDeviceType().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> DICOMDeviceDescriptor::getPrimaryDeviceTypes() const {
	std::vector<LocalizedText> result;
	result.reserve(data->PrimaryDeviceType().size());
	for (const auto & value: data->PrimaryDeviceType()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DICOMDeviceDescriptor::clearPrimaryDeviceTypes() {
	data->PrimaryDeviceType().clear();
}

DICOMDeviceDescriptor & DICOMDeviceDescriptor::addPublicCertificate(const Base64Binary & value) {
	data->PublicCertificate().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<Base64Binary> DICOMDeviceDescriptor::getPublicCertificates() const {
	std::vector<Base64Binary> result;
	result.reserve(data->PublicCertificate().size());
	for (const auto & value: data->PublicCertificate()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DICOMDeviceDescriptor::clearPublicCertificates() {
	data->PublicCertificate().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

