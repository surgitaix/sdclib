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
 *  ChannelDescriptor.cpp
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

#include "SDCLib/Data/SDC/MDIB/ChannelDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/ProductionSpecification.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


ChannelDescriptor::ChannelDescriptor(
		Handle handle
) : data(Defaults::ChannelDescriptorInit(
		handle
)) {}

ChannelDescriptor::operator CDM::ChannelDescriptor() const {
	return *data;
}

ChannelDescriptor::ChannelDescriptor(const CDM::ChannelDescriptor & object) : data(new CDM::ChannelDescriptor(object)) {

}

ChannelDescriptor::ChannelDescriptor(const ChannelDescriptor & object) : data(new CDM::ChannelDescriptor(*object.data)) {

}

ChannelDescriptor::~ChannelDescriptor() {

}

void ChannelDescriptor::copyFrom(const ChannelDescriptor & object) {
	data = std::shared_ptr<CDM::ChannelDescriptor>( new CDM::ChannelDescriptor(*object.data));
}

ChannelDescriptor & ChannelDescriptor:: operator=(const ChannelDescriptor & object) {
	copyFrom(object);
	return *this;
}


ChannelDescriptor & ChannelDescriptor::setType(const CodedValue & value) {
	data->setType(ConvertToCDM::convert(value));
	return *this;
}

bool ChannelDescriptor::getType(CodedValue & out) const {
	if (data->getType().present()) {
		out = ConvertFromCDM::convert(data->getType().get());
		return true;
	}
	return false;
}

CodedValue ChannelDescriptor::getType() const {
	return ConvertFromCDM::convert(data->getType().get());
}

bool ChannelDescriptor::hasType() const {
	return data->getType().present();
}

ChannelDescriptor & ChannelDescriptor::setHandle(const Handle & value) {
	data->setHandle(ConvertToCDM::convert(value));
	return *this;
}


Handle ChannelDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->getHandle());
}

ChannelDescriptor & ChannelDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool ChannelDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter ChannelDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool ChannelDescriptor::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

ChannelDescriptor & ChannelDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->setSafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool ChannelDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->getSafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->getSafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification ChannelDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->getSafetyClassification().get());
}

bool ChannelDescriptor::hasSafetyClassification() const {
	return data->getSafetyClassification().present();
}

ChannelDescriptor & ChannelDescriptor::addProductionSpecification(const ProductionSpecification & value) {
	data->getProductionSpecification().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ProductionSpecification> ChannelDescriptor::getProductionSpecificationList() const {
	std::vector<ProductionSpecification> result;
	result.reserve(data->getProductionSpecification().size());
	for (const auto & value: data->getProductionSpecification()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void ChannelDescriptor::clearProductionSpecificationList() {
	data->getProductionSpecification().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

