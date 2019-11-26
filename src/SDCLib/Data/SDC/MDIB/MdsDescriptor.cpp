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
 *  MdsDescriptor.cpp
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

#include "SDCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/MetaData.h"
#include "SDCLib/Data/SDC/MDIB/SystemContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ClockDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/BatteryDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ApprovedJurisdictions.h"
#include "SDCLib/Data/SDC/MDIB/VmdDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/AlertSystemDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ScoDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ProductionSpecification.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


MdsDescriptor::MdsDescriptor(
		Handle handle
) : data(Defaults::MdsDescriptorInit(
		handle
))
{}

MdsDescriptor::operator CDM::MdsDescriptor() const {
	return *data;
}

MdsDescriptor::MdsDescriptor(const CDM::MdsDescriptor & object)
: data(new CDM::MdsDescriptor(object))
{ }

MdsDescriptor::MdsDescriptor(const MdsDescriptor & object)
: data(std::make_shared<CDM::MdsDescriptor>(*object.data))
{ }

void MdsDescriptor::copyFrom(const MdsDescriptor & object) {
	data = std::make_shared<CDM::MdsDescriptor>(*object.data);
}

MdsDescriptor & MdsDescriptor:: operator=(const MdsDescriptor& object) {
	copyFrom(object);
	return *this;
}


MdsDescriptor & MdsDescriptor::setType(const CodedValue & value) {
	data->setType(ConvertToCDM::convert(value));
	return *this;
}

bool MdsDescriptor::getType(CodedValue & out) const {
	if (data->getType().present()) {
		out = ConvertFromCDM::convert(data->getType().get());
		return true;
	}
	return false;
}

CodedValue MdsDescriptor::getType() const {
	return ConvertFromCDM::convert(data->getType().get());
}

bool MdsDescriptor::hasType() const {
	return data->getType().present();
}

MdsDescriptor & MdsDescriptor::setHandle(const Handle & value) {
	data->setHandle(ConvertToCDM::convert(value));
	return *this;
}


Handle MdsDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->getHandle());
}

MdsDescriptor & MdsDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool MdsDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter MdsDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool MdsDescriptor::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

MdsDescriptor & MdsDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->setSafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool MdsDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->getSafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->getSafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification MdsDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->getSafetyClassification().get());
}

bool MdsDescriptor::hasSafetyClassification() const {
	return data->getSafetyClassification().present();
}

MdsDescriptor & MdsDescriptor::addProductionSpecification(const ProductionSpecification & value) {
	data->getProductionSpecification().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ProductionSpecification> MdsDescriptor::getProductionSpecificationList() const {
	std::vector<ProductionSpecification> result;
	result.reserve(data->getProductionSpecification().size());
	for (const auto & value: data->getProductionSpecification()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void MdsDescriptor::clearProductionSpecificationList() {
	data->getProductionSpecification().clear();
}

MdsDescriptor & MdsDescriptor::setAlertSystem(const AlertSystemDescriptor & value) {
	data->setAlertSystem(ConvertToCDM::convert(value));
	return *this;
}

bool MdsDescriptor::getAlertSystem(AlertSystemDescriptor & out) const {
	if (data->getAlertSystem().present()) {
		out = ConvertFromCDM::convert(data->getAlertSystem().get());
		return true;
	}
	return false;
}

AlertSystemDescriptor MdsDescriptor::getAlertSystem() const {
	return ConvertFromCDM::convert(data->getAlertSystem().get());
}

bool MdsDescriptor::hasAlertSystem() const {
	return data->getAlertSystem().present();
}

MdsDescriptor & MdsDescriptor::setSco(const ScoDescriptor & value) {
	data->setSco(ConvertToCDM::convert(value));
	return *this;
}

bool MdsDescriptor::getSco(ScoDescriptor & out) const {
	if (data->getSco().present()) {
		out = ConvertFromCDM::convert(data->getSco().get());
		return true;
	}
	return false;
}

ScoDescriptor MdsDescriptor::getSco() const {
	return ConvertFromCDM::convert(data->getSco().get());
}

bool MdsDescriptor::hasSco() const {
	return data->getSco().present();
}

MdsDescriptor & MdsDescriptor::setMetaData(const MetaData & value) {
	data->setMetaData(ConvertToCDM::convert(value));
	return *this;
}

bool MdsDescriptor::getMetaData(MetaData & out) const {
	if (data->getMetaData().present()) {
		out = ConvertFromCDM::convert(data->getMetaData().get());
		return true;
	}
	return false;
}

MetaData MdsDescriptor::getMetaData() const {
	return ConvertFromCDM::convert(data->getMetaData().get());
}

bool MdsDescriptor::hasMetaData() const {
	return data->getMetaData().present();
}

MdsDescriptor & MdsDescriptor::setSystemContext(const SystemContextDescriptor & value) {
	data->setSystemContext(ConvertToCDM::convert(value));
	return *this;
}

bool MdsDescriptor::getSystemContext(SystemContextDescriptor & out) const {
	if (data->getSystemContext().present()) {
		out = ConvertFromCDM::convert(data->getSystemContext().get());
		return true;
	}
	return false;
}

SystemContextDescriptor MdsDescriptor::getSystemContext() const {
	return ConvertFromCDM::convert(data->getSystemContext().get());
}

bool MdsDescriptor::hasSystemContext() const {
	return data->getSystemContext().present();
}

MdsDescriptor & MdsDescriptor::setClock(const ClockDescriptor & value) {
	data->setClock(ConvertToCDM::convert(value));
	return *this;
}

bool MdsDescriptor::getClock(ClockDescriptor & out) const {
	if (data->getClock().present()) {
		out = ConvertFromCDM::convert(data->getClock().get());
		return true;
	}
	return false;
}

ClockDescriptor MdsDescriptor::getClock() const {
	return ConvertFromCDM::convert(data->getClock().get());
}

bool MdsDescriptor::hasClock() const {
	return data->getClock().present();
}

MdsDescriptor & MdsDescriptor::setApprovedJurisdictions(const ApprovedJurisdictions & value) {
	data->setApprovedJurisdictions(ConvertToCDM::convert(value));
	return *this;
}

bool MdsDescriptor::getApprovedJurisdictions(ApprovedJurisdictions & out) const {
	if (data->getApprovedJurisdictions().present()) {
		out = ConvertFromCDM::convert(data->getApprovedJurisdictions().get());
		return true;
	}
	return false;
}

ApprovedJurisdictions MdsDescriptor::getApprovedJurisdictions() const {
	return ConvertFromCDM::convert(data->getApprovedJurisdictions().get());
}

bool MdsDescriptor::hasApprovedJurisdictions() const {
	return data->getApprovedJurisdictions().present();
}

MdsDescriptor & MdsDescriptor::addBattery(const BatteryDescriptor & value) {
	data->getBattery().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<BatteryDescriptor> MdsDescriptor::getBatteryList() const {
	std::vector<BatteryDescriptor> result;
	result.reserve(data->getBattery().size());
	for (const auto & value: data->getBattery()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void MdsDescriptor::clearBatteryList() {
	data->getBattery().clear();
}

MdsDescriptor & MdsDescriptor::addVmd(const VmdDescriptor & value) {
	data->getVmd().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<VmdDescriptor> MdsDescriptor::getVmdList() const {
	std::vector<VmdDescriptor> result;
	result.reserve(data->getVmd().size());
	for (const auto & value: data->getVmd()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void MdsDescriptor::clearVmdList() {
	data->getVmd().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

