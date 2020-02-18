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

#include "SDCLib/Data/SDC/MDIB/DicomDeviceDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/DicomNetworkAe.h"
#include "SDCLib/Data/SDC/MDIB/DicomNetworkConnection.h"
#include "SDCLib/Data/SDC/MDIB/LocalizedText.h"
#include "SDCLib/Data/SDC/MDIB/AlertSystemDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ScoDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ProductionSpecification.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


DicomDeviceDescriptor::DicomDeviceDescriptor(
		Handle handle
) : data(Defaults::DicomDeviceDescriptorInit(
		handle
))
{}

DicomDeviceDescriptor::operator CDM::DicomDeviceDescriptor() const {
	return *data;
}

DicomDeviceDescriptor::DicomDeviceDescriptor(const CDM::DicomDeviceDescriptor & object)
: data(new CDM::DicomDeviceDescriptor(object))
{ }

DicomDeviceDescriptor::DicomDeviceDescriptor(const DicomDeviceDescriptor & object)
: data(std::make_shared<CDM::DicomDeviceDescriptor>(*object.data))
{ }

void DicomDeviceDescriptor::copyFrom(const DicomDeviceDescriptor & object) {
	data = std::make_shared<CDM::DicomDeviceDescriptor>(*object.data);
}

DicomDeviceDescriptor & DicomDeviceDescriptor:: operator=(const DicomDeviceDescriptor& object) {
	copyFrom(object);
	return *this;
}


DicomDeviceDescriptor & DicomDeviceDescriptor::setType(const CodedValue & value) {
	data->setType(ConvertToCDM::convert(value));
	return *this;
}

bool DicomDeviceDescriptor::getType(CodedValue & out) const {
	if (data->getType().present()) {
		out = ConvertFromCDM::convert(data->getType().get());
		return true;
	}
	return false;
}

CodedValue DicomDeviceDescriptor::getType() const {
	return ConvertFromCDM::convert(data->getType().get());
}

bool DicomDeviceDescriptor::hasType() const {
	return data->getType().present();
}

DicomDeviceDescriptor & DicomDeviceDescriptor::setHandle(const Handle & value) {
	data->setHandle(ConvertToCDM::convert(value));
	return *this;
}


Handle DicomDeviceDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->getHandle());
}

DicomDeviceDescriptor & DicomDeviceDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool DicomDeviceDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter DicomDeviceDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool DicomDeviceDescriptor::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

DicomDeviceDescriptor & DicomDeviceDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->setSafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool DicomDeviceDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->getSafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->getSafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification DicomDeviceDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->getSafetyClassification().get());
}

bool DicomDeviceDescriptor::hasSafetyClassification() const {
	return data->getSafetyClassification().present();
}

DicomDeviceDescriptor & DicomDeviceDescriptor::addProductionSpecification(const ProductionSpecification & value) {
	data->getProductionSpecification().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ProductionSpecification> DicomDeviceDescriptor::getProductionSpecificationList() const {
	std::vector<ProductionSpecification> result;
	result.reserve(data->getProductionSpecification().size());
	for (const auto & value: data->getProductionSpecification()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DicomDeviceDescriptor::clearProductionSpecificationList() {
	data->getProductionSpecification().clear();
}

DicomDeviceDescriptor & DicomDeviceDescriptor::setAlertSystem(const AlertSystemDescriptor & value) {
	data->setAlertSystem(ConvertToCDM::convert(value));
	return *this;
}

bool DicomDeviceDescriptor::getAlertSystem(AlertSystemDescriptor & out) const {
	if (data->getAlertSystem().present()) {
		out = ConvertFromCDM::convert(data->getAlertSystem().get());
		return true;
	}
	return false;
}

AlertSystemDescriptor DicomDeviceDescriptor::getAlertSystem() const {
	return ConvertFromCDM::convert(data->getAlertSystem().get());
}

bool DicomDeviceDescriptor::hasAlertSystem() const {
	return data->getAlertSystem().present();
}

DicomDeviceDescriptor & DicomDeviceDescriptor::setSco(const ScoDescriptor & value) {
	data->setSco(ConvertToCDM::convert(value));
	return *this;
}

bool DicomDeviceDescriptor::getSco(ScoDescriptor & out) const {
	if (data->getSco().present()) {
		out = ConvertFromCDM::convert(data->getSco().get());
		return true;
	}
	return false;
}

ScoDescriptor DicomDeviceDescriptor::getSco() const {
	return ConvertFromCDM::convert(data->getSco().get());
}

bool DicomDeviceDescriptor::hasSco() const {
	return data->getSco().present();
}

DicomDeviceDescriptor & DicomDeviceDescriptor::setIssuerOfPatientID(const std::string & value) {
	data->setIssuerOfPatientID(ConvertToCDM::convert(value));
	return *this;
}

bool DicomDeviceDescriptor::getIssuerOfPatientID(std::string & out) const {
	if (data->getIssuerOfPatientID().present()) {
		out = ConvertFromCDM::convert(data->getIssuerOfPatientID().get());
		return true;
	}
	return false;
}

std::string DicomDeviceDescriptor::getIssuerOfPatientID() const {
	return ConvertFromCDM::convert(data->getIssuerOfPatientID().get());
}

bool DicomDeviceDescriptor::hasIssuerOfPatientID() const {
	return data->getIssuerOfPatientID().present();
}

DicomDeviceDescriptor & DicomDeviceDescriptor::addNetworkAe(const DicomNetworkAe & value) {
	data->getNetworkAe().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<DicomNetworkAe> DicomDeviceDescriptor::getNetworkAeList() const {
	std::vector<DicomNetworkAe> result;
	result.reserve(data->getNetworkAe().size());
	for (const auto & value: data->getNetworkAe()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DicomDeviceDescriptor::clearNetworkAeList() {
	data->getNetworkAe().clear();
}

DicomDeviceDescriptor & DicomDeviceDescriptor::addNetworkConnection(const DicomNetworkConnection & value) {
	data->getNetworkConnection().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<DicomNetworkConnection> DicomDeviceDescriptor::getNetworkConnectionList() const {
	std::vector<DicomNetworkConnection> result;
	result.reserve(data->getNetworkConnection().size());
	for (const auto & value: data->getNetworkConnection()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DicomDeviceDescriptor::clearNetworkConnectionList() {
	data->getNetworkConnection().clear();
}

DicomDeviceDescriptor & DicomDeviceDescriptor::addDescription(const LocalizedText & value) {
	data->getDescription().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> DicomDeviceDescriptor::getDescriptionList() const {
	std::vector<LocalizedText> result;
	result.reserve(data->getDescription().size());
	for (const auto & value: data->getDescription()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DicomDeviceDescriptor::clearDescriptionList() {
	data->getDescription().clear();
}

DicomDeviceDescriptor & DicomDeviceDescriptor::addStationName(const LocalizedText & value) {
	data->getStationName().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> DicomDeviceDescriptor::getStationNameList() const {
	std::vector<LocalizedText> result;
	result.reserve(data->getStationName().size());
	for (const auto & value: data->getStationName()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DicomDeviceDescriptor::clearStationNameList() {
	data->getStationName().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

