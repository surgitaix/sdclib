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
 *  ClockDescriptor.cpp
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

#include "SDCLib/Data/SDC/MDIB/ClockDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/CodedValue.h"
#include "SDCLib/Data/SDC/MDIB/ProductionSpecification.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


ClockDescriptor::ClockDescriptor(
		Handle handle
) : data(Defaults::ClockDescriptorInit(
		handle
)) {}

ClockDescriptor::operator CDM::ClockDescriptor() const {
	return *data;
}

ClockDescriptor::ClockDescriptor(const CDM::ClockDescriptor & object) : data(new CDM::ClockDescriptor(object)) {

}

ClockDescriptor::ClockDescriptor(const ClockDescriptor & object) : data(new CDM::ClockDescriptor(*object.data)) {

}

ClockDescriptor::~ClockDescriptor() {

}

void ClockDescriptor::copyFrom(const ClockDescriptor & object) {
	data = std::shared_ptr<CDM::ClockDescriptor>( new CDM::ClockDescriptor(*object.data));
}

ClockDescriptor & ClockDescriptor:: operator=(const ClockDescriptor & object) {
	copyFrom(object);
	return *this;
}


ClockDescriptor & ClockDescriptor::setType(const CodedValue & value) {
	data->setType(ConvertToCDM::convert(value));
	return *this;
}

bool ClockDescriptor::getType(CodedValue & out) const {
	if (data->getType().present()) {
		out = ConvertFromCDM::convert(data->getType().get());
		return true;
	}
	return false;
}

CodedValue ClockDescriptor::getType() const {
	return ConvertFromCDM::convert(data->getType().get());
}

bool ClockDescriptor::hasType() const {
	return data->getType().present();
}

ClockDescriptor & ClockDescriptor::setHandle(const Handle & value) {
	data->setHandle(ConvertToCDM::convert(value));
	return *this;
}


Handle ClockDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->getHandle());
}

ClockDescriptor & ClockDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool ClockDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter ClockDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool ClockDescriptor::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

ClockDescriptor & ClockDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->setSafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool ClockDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->getSafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->getSafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification ClockDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->getSafetyClassification().get());
}

bool ClockDescriptor::hasSafetyClassification() const {
	return data->getSafetyClassification().present();
}

ClockDescriptor & ClockDescriptor::addProductionSpecification(const ProductionSpecification & value) {
	data->getProductionSpecification().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ProductionSpecification> ClockDescriptor::getProductionSpecificationList() const {
	std::vector<ProductionSpecification> result;
	result.reserve(data->getProductionSpecification().size());
	for (const auto & value: data->getProductionSpecification()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void ClockDescriptor::clearProductionSpecificationList() {
	data->getProductionSpecification().clear();
}

ClockDescriptor & ClockDescriptor::setResolution(const xml_schema::Duration & value) {
	data->setResolution(ConvertToCDM::convert(value));
	return *this;
}

bool ClockDescriptor::getResolution(xml_schema::Duration & out) const {
	if (data->getResolution().present()) {
		out = ConvertFromCDM::convert(data->getResolution().get());
		return true;
	}
	return false;
}

xml_schema::Duration ClockDescriptor::getResolution() const {
	return ConvertFromCDM::convert(data->getResolution().get());
}

bool ClockDescriptor::hasResolution() const {
	return data->getResolution().present();
}

ClockDescriptor & ClockDescriptor::addTimeProtocol(const CodedValue & value) {
	data->getTimeProtocol().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CodedValue> ClockDescriptor::getTimeProtocolList() const {
	std::vector<CodedValue> result;
	result.reserve(data->getTimeProtocol().size());
	for (const auto & value: data->getTimeProtocol()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void ClockDescriptor::clearTimeProtocolList() {
	data->getTimeProtocol().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

