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
 *  VmdDescriptor.cpp
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

#include "SDCLib/Data/SDC/MDIB/VmdDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/ApprovedJurisdictions.h"
#include "SDCLib/Data/SDC/MDIB/ChannelDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/AlertSystemDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ScoDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ProductionSpecification.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


VmdDescriptor::VmdDescriptor(
		Handle handle
) : data(Defaults::VmdDescriptorInit(
		handle
)) {}

VmdDescriptor::operator CDM::VmdDescriptor() const {
	return *data;
}

VmdDescriptor::VmdDescriptor(const CDM::VmdDescriptor & object) : data(new CDM::VmdDescriptor(object)) {

}

VmdDescriptor::VmdDescriptor(const VmdDescriptor & object) : data(new CDM::VmdDescriptor(*object.data)) {

}

VmdDescriptor::~VmdDescriptor() {

}

void VmdDescriptor::copyFrom(const VmdDescriptor & object) {
	data = std::shared_ptr<CDM::VmdDescriptor>( new CDM::VmdDescriptor(*object.data));
}

VmdDescriptor & VmdDescriptor:: operator=(const VmdDescriptor & object) {
	copyFrom(object);
	return *this;
}


VmdDescriptor & VmdDescriptor::setType(const CodedValue & value) {
	data->setType(ConvertToCDM::convert(value));
	return *this;
}

bool VmdDescriptor::getType(CodedValue & out) const {
	if (data->getType().present()) {
		out = ConvertFromCDM::convert(data->getType().get());
		return true;
	}
	return false;
}

CodedValue VmdDescriptor::getType() const {
	return ConvertFromCDM::convert(data->getType().get());
}

bool VmdDescriptor::hasType() const {
	return data->getType().present();
}

VmdDescriptor & VmdDescriptor::setHandle(const Handle & value) {
	data->setHandle(ConvertToCDM::convert(value));
	return *this;
}


Handle VmdDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->getHandle());
}

VmdDescriptor & VmdDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool VmdDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter VmdDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool VmdDescriptor::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

VmdDescriptor & VmdDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->setSafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool VmdDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->getSafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->getSafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification VmdDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->getSafetyClassification().get());
}

bool VmdDescriptor::hasSafetyClassification() const {
	return data->getSafetyClassification().present();
}

VmdDescriptor & VmdDescriptor::addProductionSpecification(const ProductionSpecification & value) {
	data->getProductionSpecification().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ProductionSpecification> VmdDescriptor::getProductionSpecificationList() const {
	std::vector<ProductionSpecification> result;
	result.reserve(data->getProductionSpecification().size());
	for (const auto & value: data->getProductionSpecification()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void VmdDescriptor::clearProductionSpecificationList() {
	data->getProductionSpecification().clear();
}

VmdDescriptor & VmdDescriptor::setAlertSystem(const AlertSystemDescriptor & value) {
	data->setAlertSystem(ConvertToCDM::convert(value));
	return *this;
}

bool VmdDescriptor::getAlertSystem(AlertSystemDescriptor & out) const {
	if (data->getAlertSystem().present()) {
		out = ConvertFromCDM::convert(data->getAlertSystem().get());
		return true;
	}
	return false;
}

AlertSystemDescriptor VmdDescriptor::getAlertSystem() const {
	return ConvertFromCDM::convert(data->getAlertSystem().get());
}

bool VmdDescriptor::hasAlertSystem() const {
	return data->getAlertSystem().present();
}

VmdDescriptor & VmdDescriptor::setSco(const ScoDescriptor & value) {
	data->setSco(ConvertToCDM::convert(value));
	return *this;
}

bool VmdDescriptor::getSco(ScoDescriptor & out) const {
	if (data->getSco().present()) {
		out = ConvertFromCDM::convert(data->getSco().get());
		return true;
	}
	return false;
}

ScoDescriptor VmdDescriptor::getSco() const {
	return ConvertFromCDM::convert(data->getSco().get());
}

bool VmdDescriptor::hasSco() const {
	return data->getSco().present();
}

VmdDescriptor & VmdDescriptor::setApprovedJurisdictions(const ApprovedJurisdictions & value) {
	data->setApprovedJurisdictions(ConvertToCDM::convert(value));
	return *this;
}

bool VmdDescriptor::getApprovedJurisdictions(ApprovedJurisdictions & out) const {
	if (data->getApprovedJurisdictions().present()) {
		out = ConvertFromCDM::convert(data->getApprovedJurisdictions().get());
		return true;
	}
	return false;
}

ApprovedJurisdictions VmdDescriptor::getApprovedJurisdictions() const {
	return ConvertFromCDM::convert(data->getApprovedJurisdictions().get());
}

bool VmdDescriptor::hasApprovedJurisdictions() const {
	return data->getApprovedJurisdictions().present();
}

VmdDescriptor & VmdDescriptor::addChannel(const ChannelDescriptor & value) {
	data->getChannel().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ChannelDescriptor> VmdDescriptor::getChannelList() const {
	std::vector<ChannelDescriptor> result;
	result.reserve(data->getChannel().size());
	for (const auto & value: data->getChannel()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void VmdDescriptor::clearChannelList() {
	data->getChannel().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

