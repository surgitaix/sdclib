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
 *  EnumStringMetricDescriptor.cpp
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

#include "SDCLib/Data/SDC/MDIB/EnumStringMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/AllowedValue.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"
#include "SDCLib/Data/SDC/MDIB/Relation.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


EnumStringMetricDescriptor::EnumStringMetricDescriptor(
		Handle handle
		,
		CodedValue unit
		,
		MetricCategory metriccategory
		,
		MetricAvailability metricavailability
) : data(Defaults::EnumStringMetricDescriptorInit(
		handle
		,
		unit
		,
		metriccategory
		,
		metricavailability
))
{}

EnumStringMetricDescriptor::operator CDM::EnumStringMetricDescriptor() const {
	return *data;
}

EnumStringMetricDescriptor::EnumStringMetricDescriptor(const CDM::EnumStringMetricDescriptor & object)
: data(new CDM::EnumStringMetricDescriptor(object))
{ }

EnumStringMetricDescriptor::EnumStringMetricDescriptor(const EnumStringMetricDescriptor & object)
: data(std::make_shared<CDM::EnumStringMetricDescriptor>(*object.data))
{ }

void EnumStringMetricDescriptor::copyFrom(const EnumStringMetricDescriptor & object) {
	data = std::make_shared<CDM::EnumStringMetricDescriptor>(*object.data);
}

EnumStringMetricDescriptor & EnumStringMetricDescriptor:: operator=(const EnumStringMetricDescriptor& object) {
	copyFrom(object);
	return *this;
}


EnumStringMetricDescriptor & EnumStringMetricDescriptor::setType(const CodedValue & value) {
	data->setType(ConvertToCDM::convert(value));
	return *this;
}

bool EnumStringMetricDescriptor::getType(CodedValue & out) const {
	if (data->getType().present()) {
		out = ConvertFromCDM::convert(data->getType().get());
		return true;
	}
	return false;
}

CodedValue EnumStringMetricDescriptor::getType() const {
	return ConvertFromCDM::convert(data->getType().get());
}

bool EnumStringMetricDescriptor::hasType() const {
	return data->getType().present();
}

EnumStringMetricDescriptor & EnumStringMetricDescriptor::setHandle(const Handle & value) {
	data->setHandle(ConvertToCDM::convert(value));
	return *this;
}


Handle EnumStringMetricDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->getHandle());
}

EnumStringMetricDescriptor & EnumStringMetricDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool EnumStringMetricDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter EnumStringMetricDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool EnumStringMetricDescriptor::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

EnumStringMetricDescriptor & EnumStringMetricDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->setSafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool EnumStringMetricDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->getSafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->getSafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification EnumStringMetricDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->getSafetyClassification().get());
}

bool EnumStringMetricDescriptor::hasSafetyClassification() const {
	return data->getSafetyClassification().present();
}

EnumStringMetricDescriptor & EnumStringMetricDescriptor::setUnit(const CodedValue & value) {
	data->setUnit(ConvertToCDM::convert(value));
	return *this;
}


CodedValue EnumStringMetricDescriptor::getUnit() const {
	return ConvertFromCDM::convert(data->getUnit());
}

EnumStringMetricDescriptor & EnumStringMetricDescriptor::setMetricCategory(const MetricCategory & value) {
	data->setMetricCategory(ConvertToCDM::convert(value));
	return *this;
}


MetricCategory EnumStringMetricDescriptor::getMetricCategory() const {
	return ConvertFromCDM::convert(data->getMetricCategory());
}

EnumStringMetricDescriptor & EnumStringMetricDescriptor::setDerivationMethod(const DerivationMethod & value) {
	data->setDerivationMethod(ConvertToCDM::convert(value));
	return *this;
}

bool EnumStringMetricDescriptor::getDerivationMethod(DerivationMethod & out) const {
	if (data->getDerivationMethod().present()) {
		out = ConvertFromCDM::convert(data->getDerivationMethod().get());
		return true;
	}
	return false;
}

DerivationMethod EnumStringMetricDescriptor::getDerivationMethod() const {
	return ConvertFromCDM::convert(data->getDerivationMethod().get());
}

bool EnumStringMetricDescriptor::hasDerivationMethod() const {
	return data->getDerivationMethod().present();
}

EnumStringMetricDescriptor & EnumStringMetricDescriptor::setMetricAvailability(const MetricAvailability & value) {
	data->setMetricAvailability(ConvertToCDM::convert(value));
	return *this;
}


MetricAvailability EnumStringMetricDescriptor::getMetricAvailability() const {
	return ConvertFromCDM::convert(data->getMetricAvailability());
}

EnumStringMetricDescriptor & EnumStringMetricDescriptor::setMaxMeasurementTime(const xml_schema::Duration & value) {
	data->setMaxMeasurementTime(ConvertToCDM::convert(value));
	return *this;
}

bool EnumStringMetricDescriptor::getMaxMeasurementTime(xml_schema::Duration & out) const {
	if (data->getMaxMeasurementTime().present()) {
		out = ConvertFromCDM::convert(data->getMaxMeasurementTime().get());
		return true;
	}
	return false;
}

xml_schema::Duration EnumStringMetricDescriptor::getMaxMeasurementTime() const {
	return ConvertFromCDM::convert(data->getMaxMeasurementTime().get());
}

bool EnumStringMetricDescriptor::hasMaxMeasurementTime() const {
	return data->getMaxMeasurementTime().present();
}

EnumStringMetricDescriptor & EnumStringMetricDescriptor::setMaxDelayTime(const xml_schema::Duration & value) {
	data->setMaxDelayTime(ConvertToCDM::convert(value));
	return *this;
}

bool EnumStringMetricDescriptor::getMaxDelayTime(xml_schema::Duration & out) const {
	if (data->getMaxDelayTime().present()) {
		out = ConvertFromCDM::convert(data->getMaxDelayTime().get());
		return true;
	}
	return false;
}

xml_schema::Duration EnumStringMetricDescriptor::getMaxDelayTime() const {
	return ConvertFromCDM::convert(data->getMaxDelayTime().get());
}

bool EnumStringMetricDescriptor::hasMaxDelayTime() const {
	return data->getMaxDelayTime().present();
}

EnumStringMetricDescriptor & EnumStringMetricDescriptor::setDeterminationPeriod(const xml_schema::Duration & value) {
	data->setDeterminationPeriod(ConvertToCDM::convert(value));
	return *this;
}

bool EnumStringMetricDescriptor::getDeterminationPeriod(xml_schema::Duration & out) const {
	if (data->getDeterminationPeriod().present()) {
		out = ConvertFromCDM::convert(data->getDeterminationPeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration EnumStringMetricDescriptor::getDeterminationPeriod() const {
	return ConvertFromCDM::convert(data->getDeterminationPeriod().get());
}

bool EnumStringMetricDescriptor::hasDeterminationPeriod() const {
	return data->getDeterminationPeriod().present();
}

EnumStringMetricDescriptor & EnumStringMetricDescriptor::setLifeTimePeriod(const xml_schema::Duration & value) {
	data->setLifeTimePeriod(ConvertToCDM::convert(value));
	return *this;
}

bool EnumStringMetricDescriptor::getLifeTimePeriod(xml_schema::Duration & out) const {
	if (data->getLifeTimePeriod().present()) {
		out = ConvertFromCDM::convert(data->getLifeTimePeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration EnumStringMetricDescriptor::getLifeTimePeriod() const {
	return ConvertFromCDM::convert(data->getLifeTimePeriod().get());
}

bool EnumStringMetricDescriptor::hasLifeTimePeriod() const {
	return data->getLifeTimePeriod().present();
}

EnumStringMetricDescriptor & EnumStringMetricDescriptor::setActivationDuration(const xml_schema::Duration & value) {
	data->setActivationDuration(ConvertToCDM::convert(value));
	return *this;
}

bool EnumStringMetricDescriptor::getActivationDuration(xml_schema::Duration & out) const {
	if (data->getActivationDuration().present()) {
		out = ConvertFromCDM::convert(data->getActivationDuration().get());
		return true;
	}
	return false;
}

xml_schema::Duration EnumStringMetricDescriptor::getActivationDuration() const {
	return ConvertFromCDM::convert(data->getActivationDuration().get());
}

bool EnumStringMetricDescriptor::hasActivationDuration() const {
	return data->getActivationDuration().present();
}

EnumStringMetricDescriptor & EnumStringMetricDescriptor::addBodySite(const CodedValue & value) {
	data->getBodySite().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CodedValue> EnumStringMetricDescriptor::getBodySiteList() const {
	std::vector<CodedValue> result;
	result.reserve(data->getBodySite().size());
	for (const auto & value: data->getBodySite()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void EnumStringMetricDescriptor::clearBodySiteList() {
	data->getBodySite().clear();
}

EnumStringMetricDescriptor & EnumStringMetricDescriptor::addRelation(const Relation & value) {
	data->getRelation().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<Relation> EnumStringMetricDescriptor::getRelationList() const {
	std::vector<Relation> result;
	result.reserve(data->getRelation().size());
	for (const auto & value: data->getRelation()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void EnumStringMetricDescriptor::clearRelationList() {
	data->getRelation().clear();
}

EnumStringMetricDescriptor & EnumStringMetricDescriptor::addAllowedValue(const AllowedValue & value) {
	data->getAllowedValue().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<AllowedValue> EnumStringMetricDescriptor::getAllowedValueList() const {
	std::vector<AllowedValue> result;
	result.reserve(data->getAllowedValue().size());
	for (const auto & value: data->getAllowedValue()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void EnumStringMetricDescriptor::clearAllowedValueList() {
	data->getAllowedValue().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

