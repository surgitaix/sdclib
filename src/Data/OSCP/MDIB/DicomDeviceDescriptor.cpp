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
 *  DicomDeviceDescriptor.cpp
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

#include "OSCLib/Data/OSCP/MDIB/DicomDeviceDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/Base64Binary.h"
#include "OSCLib/Data/OSCP/MDIB/DicomNetworkAe.h"
#include "OSCLib/Data/OSCP/MDIB/DicomNetworkConnection.h"
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

DicomDeviceDescriptor::DicomDeviceDescriptor() : data(Defaults::DicomDeviceDescriptor()) {
}

DicomDeviceDescriptor::operator CDM::DicomDeviceDescriptor() const {
	return *data;
}

DicomDeviceDescriptor::DicomDeviceDescriptor(const CDM::DicomDeviceDescriptor & object) : data(new CDM::DicomDeviceDescriptor(object)) {

}

DicomDeviceDescriptor::DicomDeviceDescriptor(const DicomDeviceDescriptor & object) : data(new CDM::DicomDeviceDescriptor(*object.data)) {

}

DicomDeviceDescriptor::~DicomDeviceDescriptor() {

}

void DicomDeviceDescriptor::copyFrom(const DicomDeviceDescriptor & object) {
	*data = *object.data;
}

DicomDeviceDescriptor & DicomDeviceDescriptor:: operator=(const DicomDeviceDescriptor & object) {
	copyFrom(object);
	return *this;
}


DicomDeviceDescriptor & DicomDeviceDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool DicomDeviceDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue DicomDeviceDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool DicomDeviceDescriptor::hasType() const {
	return data->Type().present();
}
	
DicomDeviceDescriptor & DicomDeviceDescriptor::setHandle(const std::string & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


std::string DicomDeviceDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
DicomDeviceDescriptor & DicomDeviceDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool DicomDeviceDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter DicomDeviceDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool DicomDeviceDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
DicomDeviceDescriptor & DicomDeviceDescriptor::addProductionSpecification(const ProductionSpecification & value) {
	data->ProductionSpecification().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ProductionSpecification> DicomDeviceDescriptor::getProductionSpecifications() const {
	std::vector<ProductionSpecification> result;
	result.reserve(data->ProductionSpecification().size());
	for (const auto & value: data->ProductionSpecification()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DicomDeviceDescriptor::clearProductionSpecifications() {
	data->ProductionSpecification().clear();
}

DicomDeviceDescriptor & DicomDeviceDescriptor::setMetaData(const SystemMetaData & value) {
	data->MetaData(ConvertToCDM::convert(value));
	return *this;
}

bool DicomDeviceDescriptor::getMetaData(SystemMetaData & out) const {
	if (data->MetaData().present()) {
		out = ConvertFromCDM::convert(data->MetaData().get());
		return true;
	}
	return false;
}

SystemMetaData DicomDeviceDescriptor::getMetaData() const {
	return ConvertFromCDM::convert(data->MetaData().get());
}
	
bool DicomDeviceDescriptor::hasMetaData() const {
	return data->MetaData().present();
}
	
DicomDeviceDescriptor & DicomDeviceDescriptor::setContext(const SystemContext & value) {
	data->Context(ConvertToCDM::convert(value));
	return *this;
}


SystemContext DicomDeviceDescriptor::getContext() const {
	return ConvertFromCDM::convert(data->Context());
}
	
DicomDeviceDescriptor & DicomDeviceDescriptor::setClock(const ClockDescriptor & value) {
	data->Clock(ConvertToCDM::convert(value));
	return *this;
}

bool DicomDeviceDescriptor::getClock(ClockDescriptor & out) const {
	if (data->Clock().present()) {
		out = ConvertFromCDM::convert(data->Clock().get());
		return true;
	}
	return false;
}

ClockDescriptor DicomDeviceDescriptor::getClock() const {
	return ConvertFromCDM::convert(data->Clock().get());
}
	
bool DicomDeviceDescriptor::hasClock() const {
	return data->Clock().present();
}
	
DicomDeviceDescriptor & DicomDeviceDescriptor::setDescription(const std::string & value) {
	data->Description(ConvertToCDM::convert(value));
	return *this;
}

bool DicomDeviceDescriptor::getDescription(std::string & out) const {
	if (data->Description().present()) {
		out = ConvertFromCDM::convert(data->Description().get());
		return true;
	}
	return false;
}

std::string DicomDeviceDescriptor::getDescription() const {
	return ConvertFromCDM::convert(data->Description().get());
}
	
bool DicomDeviceDescriptor::hasDescription() const {
	return data->Description().present();
}
	
DicomDeviceDescriptor & DicomDeviceDescriptor::setStationName(const std::string & value) {
	data->StationName(ConvertToCDM::convert(value));
	return *this;
}

bool DicomDeviceDescriptor::getStationName(std::string & out) const {
	if (data->StationName().present()) {
		out = ConvertFromCDM::convert(data->StationName().get());
		return true;
	}
	return false;
}

std::string DicomDeviceDescriptor::getStationName() const {
	return ConvertFromCDM::convert(data->StationName().get());
}
	
bool DicomDeviceDescriptor::hasStationName() const {
	return data->StationName().present();
}
	
DicomDeviceDescriptor & DicomDeviceDescriptor::setIssuerOfPatientID(const std::string & value) {
	data->IssuerOfPatientID(ConvertToCDM::convert(value));
	return *this;
}

bool DicomDeviceDescriptor::getIssuerOfPatientID(std::string & out) const {
	if (data->IssuerOfPatientID().present()) {
		out = ConvertFromCDM::convert(data->IssuerOfPatientID().get());
		return true;
	}
	return false;
}

std::string DicomDeviceDescriptor::getIssuerOfPatientID() const {
	return ConvertFromCDM::convert(data->IssuerOfPatientID().get());
}
	
bool DicomDeviceDescriptor::hasIssuerOfPatientID() const {
	return data->IssuerOfPatientID().present();
}
	
DicomDeviceDescriptor & DicomDeviceDescriptor::addNetworkAe(const DicomNetworkAe & value) {
	data->NetworkAe().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<DicomNetworkAe> DicomDeviceDescriptor::getNetworkAes() const {
	std::vector<DicomNetworkAe> result;
	result.reserve(data->NetworkAe().size());
	for (const auto & value: data->NetworkAe()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DicomDeviceDescriptor::clearNetworkAes() {
	data->NetworkAe().clear();
}

DicomDeviceDescriptor & DicomDeviceDescriptor::addNetworkConnection(const DicomNetworkConnection & value) {
	data->NetworkConnection().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<DicomNetworkConnection> DicomDeviceDescriptor::getNetworkConnection() const {
	std::vector<DicomNetworkConnection> result;
	result.reserve(data->NetworkConnection().size());
	for (const auto & value: data->NetworkConnection()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DicomDeviceDescriptor::clearNetworkConnection() {
	data->NetworkConnection().clear();
}

DicomDeviceDescriptor & DicomDeviceDescriptor::addSoftwareVersion(const std::string & value) {
	data->SoftwareVersion().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> DicomDeviceDescriptor::getSoftwareVersions() const {
	std::vector<std::string> result;
	result.reserve(data->SoftwareVersion().size());
	for (const auto & value: data->SoftwareVersion()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DicomDeviceDescriptor::clearSoftwareVersions() {
	data->SoftwareVersion().clear();
}

DicomDeviceDescriptor & DicomDeviceDescriptor::addInstitutionName(const LocalizedText & value) {
	data->InstitutionName().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> DicomDeviceDescriptor::getInstitutionNames() const {
	std::vector<LocalizedText> result;
	result.reserve(data->InstitutionName().size());
	for (const auto & value: data->InstitutionName()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DicomDeviceDescriptor::clearInstitutionNames() {
	data->InstitutionName().clear();
}

DicomDeviceDescriptor & DicomDeviceDescriptor::addInstitutionAddress(const LocalizedText & value) {
	data->InstitutionAddress().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> DicomDeviceDescriptor::getInstitutionAddresses() const {
	std::vector<LocalizedText> result;
	result.reserve(data->InstitutionAddress().size());
	for (const auto & value: data->InstitutionAddress()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DicomDeviceDescriptor::clearInstitutionAddresses() {
	data->InstitutionAddress().clear();
}

DicomDeviceDescriptor & DicomDeviceDescriptor::addInstitutionalDepartmentName(const LocalizedText & value) {
	data->InstitutionalDepartmentName().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> DicomDeviceDescriptor::getInstitutionalDepartmentNames() const {
	std::vector<LocalizedText> result;
	result.reserve(data->InstitutionalDepartmentName().size());
	for (const auto & value: data->InstitutionalDepartmentName()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DicomDeviceDescriptor::clearInstitutionalDepartmentNames() {
	data->InstitutionalDepartmentName().clear();
}

DicomDeviceDescriptor & DicomDeviceDescriptor::addPrimaryDeviceType(const LocalizedText & value) {
	data->PrimaryDeviceType().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> DicomDeviceDescriptor::getPrimaryDeviceTypes() const {
	std::vector<LocalizedText> result;
	result.reserve(data->PrimaryDeviceType().size());
	for (const auto & value: data->PrimaryDeviceType()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DicomDeviceDescriptor::clearPrimaryDeviceTypes() {
	data->PrimaryDeviceType().clear();
}

DicomDeviceDescriptor & DicomDeviceDescriptor::addPublicCertificate(const Base64Binary & value) {
	data->PublicCertificate().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<Base64Binary> DicomDeviceDescriptor::getPublicCertificates() const {
	std::vector<Base64Binary> result;
	result.reserve(data->PublicCertificate().size());
	for (const auto & value: data->PublicCertificate()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DicomDeviceDescriptor::clearPublicCertificates() {
	data->PublicCertificate().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

