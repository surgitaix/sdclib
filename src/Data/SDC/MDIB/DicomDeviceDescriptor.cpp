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
 *  Author: besting, buerger, roehser
 */
 
/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 * 
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "OSCLib/Data/SDC/MDIB/DicomDeviceDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/SDC/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/SDC/MDIB/DicomNetworkAe.h"
#include "OSCLib/Data/SDC/MDIB/DicomNetworkConnection.h"
#include "OSCLib/Data/SDC/MDIB/LocalizedText.h"
#include "OSCLib/Data/SDC/MDIB/AlertSystemDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/ScoDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/ProductionSpecification.h"
#include "OSCLib/Data/SDC/MDIB/CodedValue.h"

namespace OSCLib {
namespace Data {
namespace SDC {


DicomDeviceDescriptor::DicomDeviceDescriptor(
		Handle handle
) : data(Defaults::DicomDeviceDescriptorInit(
		handle
)) {}

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
	data = std::shared_ptr<CDM::DicomDeviceDescriptor>( new CDM::DicomDeviceDescriptor(*object.data));
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
	
DicomDeviceDescriptor & DicomDeviceDescriptor::setHandle(const Handle & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


Handle DicomDeviceDescriptor::getHandle() const {
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
	
DicomDeviceDescriptor & DicomDeviceDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->SafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool DicomDeviceDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->SafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->SafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification DicomDeviceDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->SafetyClassification().get());
}
	
bool DicomDeviceDescriptor::hasSafetyClassification() const {
	return data->SafetyClassification().present();
}
	
DicomDeviceDescriptor & DicomDeviceDescriptor::addProductionSpecification(const ProductionSpecification & value) {
	data->ProductionSpecification().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ProductionSpecification> DicomDeviceDescriptor::getProductionSpecificationList() const {
	std::vector<ProductionSpecification> result;
	result.reserve(data->ProductionSpecification().size());
	for (const auto & value: data->ProductionSpecification()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DicomDeviceDescriptor::clearProductionSpecificationList() {
	data->ProductionSpecification().clear();
}

DicomDeviceDescriptor & DicomDeviceDescriptor::setAlertSystem(const AlertSystemDescriptor & value) {
	data->AlertSystem(ConvertToCDM::convert(value));
	return *this;
}

bool DicomDeviceDescriptor::getAlertSystem(AlertSystemDescriptor & out) const {
	if (data->AlertSystem().present()) {
		out = ConvertFromCDM::convert(data->AlertSystem().get());
		return true;
	}
	return false;
}

AlertSystemDescriptor DicomDeviceDescriptor::getAlertSystem() const {
	return ConvertFromCDM::convert(data->AlertSystem().get());
}
	
bool DicomDeviceDescriptor::hasAlertSystem() const {
	return data->AlertSystem().present();
}
	
DicomDeviceDescriptor & DicomDeviceDescriptor::setSco(const ScoDescriptor & value) {
	data->Sco(ConvertToCDM::convert(value));
	return *this;
}

bool DicomDeviceDescriptor::getSco(ScoDescriptor & out) const {
	if (data->Sco().present()) {
		out = ConvertFromCDM::convert(data->Sco().get());
		return true;
	}
	return false;
}

ScoDescriptor DicomDeviceDescriptor::getSco() const {
	return ConvertFromCDM::convert(data->Sco().get());
}
	
bool DicomDeviceDescriptor::hasSco() const {
	return data->Sco().present();
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

std::vector<DicomNetworkAe> DicomDeviceDescriptor::getNetworkAeList() const {
	std::vector<DicomNetworkAe> result;
	result.reserve(data->NetworkAe().size());
	for (const auto & value: data->NetworkAe()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DicomDeviceDescriptor::clearNetworkAeList() {
	data->NetworkAe().clear();
}

DicomDeviceDescriptor & DicomDeviceDescriptor::addNetworkConnection(const DicomNetworkConnection & value) {
	data->NetworkConnection().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<DicomNetworkConnection> DicomDeviceDescriptor::getNetworkConnectionList() const {
	std::vector<DicomNetworkConnection> result;
	result.reserve(data->NetworkConnection().size());
	for (const auto & value: data->NetworkConnection()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DicomDeviceDescriptor::clearNetworkConnectionList() {
	data->NetworkConnection().clear();
}

DicomDeviceDescriptor & DicomDeviceDescriptor::addDescription(const LocalizedText & value) {
	data->Description().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> DicomDeviceDescriptor::getDescriptionList() const {
	std::vector<LocalizedText> result;
	result.reserve(data->Description().size());
	for (const auto & value: data->Description()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DicomDeviceDescriptor::clearDescriptionList() {
	data->Description().clear();
}

DicomDeviceDescriptor & DicomDeviceDescriptor::addStationName(const LocalizedText & value) {
	data->StationName().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> DicomDeviceDescriptor::getStationNameList() const {
	std::vector<LocalizedText> result;
	result.reserve(data->StationName().size());
	for (const auto & value: data->StationName()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DicomDeviceDescriptor::clearStationNameList() {
	data->StationName().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace OSCLib */

