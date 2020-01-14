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
 *  BatteryDescriptor.cpp
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

#include "SDCLib/Data/SDC/MDIB/BatteryDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/Measurement.h"
#include "SDCLib/Data/SDC/MDIB/ProductionSpecification.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


BatteryDescriptor::BatteryDescriptor(
		Handle handle
) : data(Defaults::BatteryDescriptorInit(
		handle
))
{}

BatteryDescriptor::operator CDM::BatteryDescriptor() const {
	return *data;
}

BatteryDescriptor::BatteryDescriptor(const CDM::BatteryDescriptor & object)
: data(new CDM::BatteryDescriptor(object))
{ }

BatteryDescriptor::BatteryDescriptor(const BatteryDescriptor & object)
: data(std::make_shared<CDM::BatteryDescriptor>(*object.data))
{ }

void BatteryDescriptor::copyFrom(const BatteryDescriptor & object) {
	data = std::make_shared<CDM::BatteryDescriptor>(*object.data);
}

BatteryDescriptor & BatteryDescriptor:: operator=(const BatteryDescriptor& object) {
	copyFrom(object);
	return *this;
}


BatteryDescriptor & BatteryDescriptor::setType(const CodedValue & value) {
	data->setType(ConvertToCDM::convert(value));
	return *this;
}

bool BatteryDescriptor::getType(CodedValue & out) const {
	if (data->getType().present()) {
		out = ConvertFromCDM::convert(data->getType().get());
		return true;
	}
	return false;
}

CodedValue BatteryDescriptor::getType() const {
	return ConvertFromCDM::convert(data->getType().get());
}

bool BatteryDescriptor::hasType() const {
	return data->getType().present();
}

BatteryDescriptor & BatteryDescriptor::setHandle(const Handle & value) {
	data->setHandle(ConvertToCDM::convert(value));
	return *this;
}


Handle BatteryDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->getHandle());
}

BatteryDescriptor & BatteryDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool BatteryDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter BatteryDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool BatteryDescriptor::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

BatteryDescriptor & BatteryDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->setSafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool BatteryDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->getSafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->getSafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification BatteryDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->getSafetyClassification().get());
}

bool BatteryDescriptor::hasSafetyClassification() const {
	return data->getSafetyClassification().present();
}

BatteryDescriptor & BatteryDescriptor::addProductionSpecification(const ProductionSpecification & value) {
	data->getProductionSpecification().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ProductionSpecification> BatteryDescriptor::getProductionSpecificationList() const {
	std::vector<ProductionSpecification> result;
	result.reserve(data->getProductionSpecification().size());
	for (const auto & value: data->getProductionSpecification()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void BatteryDescriptor::clearProductionSpecificationList() {
	data->getProductionSpecification().clear();
}

BatteryDescriptor & BatteryDescriptor::setCapacityFullCharge(const Measurement & value) {
	data->setCapacityFullCharge(ConvertToCDM::convert(value));
	return *this;
}

bool BatteryDescriptor::getCapacityFullCharge(Measurement & out) const {
	if (data->getCapacityFullCharge().present()) {
		out = ConvertFromCDM::convert(data->getCapacityFullCharge().get());
		return true;
	}
	return false;
}

Measurement BatteryDescriptor::getCapacityFullCharge() const {
	return ConvertFromCDM::convert(data->getCapacityFullCharge().get());
}

bool BatteryDescriptor::hasCapacityFullCharge() const {
	return data->getCapacityFullCharge().present();
}

BatteryDescriptor & BatteryDescriptor::setCapacitySpecified(const Measurement & value) {
	data->setCapacitySpecified(ConvertToCDM::convert(value));
	return *this;
}

bool BatteryDescriptor::getCapacitySpecified(Measurement & out) const {
	if (data->getCapacitySpecified().present()) {
		out = ConvertFromCDM::convert(data->getCapacitySpecified().get());
		return true;
	}
	return false;
}

Measurement BatteryDescriptor::getCapacitySpecified() const {
	return ConvertFromCDM::convert(data->getCapacitySpecified().get());
}

bool BatteryDescriptor::hasCapacitySpecified() const {
	return data->getCapacitySpecified().present();
}

BatteryDescriptor & BatteryDescriptor::setVoltageSpecified(const Measurement & value) {
	data->setVoltageSpecified(ConvertToCDM::convert(value));
	return *this;
}

bool BatteryDescriptor::getVoltageSpecified(Measurement & out) const {
	if (data->getVoltageSpecified().present()) {
		out = ConvertFromCDM::convert(data->getVoltageSpecified().get());
		return true;
	}
	return false;
}

Measurement BatteryDescriptor::getVoltageSpecified() const {
	return ConvertFromCDM::convert(data->getVoltageSpecified().get());
}

bool BatteryDescriptor::hasVoltageSpecified() const {
	return data->getVoltageSpecified().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

