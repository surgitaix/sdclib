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
 *  ScoDescriptor.cpp
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

#include "SDCLib/Data/SDC/MDIB/ScoDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/ProductionSpecification.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


ScoDescriptor::ScoDescriptor(
		Handle handle
) : data(Defaults::ScoDescriptorInit(
		handle
))
{}

ScoDescriptor::operator CDM::ScoDescriptor() const {
	return *data;
}

ScoDescriptor::ScoDescriptor(const CDM::ScoDescriptor & object)
: data(new CDM::ScoDescriptor(object))
{ }

ScoDescriptor::ScoDescriptor(const ScoDescriptor & object)
: data(std::make_shared<CDM::ScoDescriptor>(*object.data))
{ }

void ScoDescriptor::copyFrom(const ScoDescriptor & object) {
	data = std::make_shared<CDM::ScoDescriptor>(*object.data);
}

ScoDescriptor & ScoDescriptor:: operator=(const ScoDescriptor& object) {
	copyFrom(object);
	return *this;
}


ScoDescriptor & ScoDescriptor::setType(const CodedValue & value) {
	data->setType(ConvertToCDM::convert(value));
	return *this;
}

bool ScoDescriptor::getType(CodedValue & out) const {
	if (data->getType().present()) {
		out = ConvertFromCDM::convert(data->getType().get());
		return true;
	}
	return false;
}

CodedValue ScoDescriptor::getType() const {
	return ConvertFromCDM::convert(data->getType().get());
}

bool ScoDescriptor::hasType() const {
	return data->getType().present();
}

ScoDescriptor & ScoDescriptor::setHandle(const Handle & value) {
	data->setHandle(ConvertToCDM::convert(value));
	return *this;
}


Handle ScoDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->getHandle());
}

ScoDescriptor & ScoDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool ScoDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter ScoDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool ScoDescriptor::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

ScoDescriptor & ScoDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->setSafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool ScoDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->getSafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->getSafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification ScoDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->getSafetyClassification().get());
}

bool ScoDescriptor::hasSafetyClassification() const {
	return data->getSafetyClassification().present();
}

ScoDescriptor & ScoDescriptor::addProductionSpecification(const ProductionSpecification & value) {
	data->getProductionSpecification().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ProductionSpecification> ScoDescriptor::getProductionSpecificationList() const {
	std::vector<ProductionSpecification> result;
	result.reserve(data->getProductionSpecification().size());
	for (const auto & value: data->getProductionSpecification()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void ScoDescriptor::clearProductionSpecificationList() {
	data->getProductionSpecification().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

