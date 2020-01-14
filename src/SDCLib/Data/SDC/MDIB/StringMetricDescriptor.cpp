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
 *  StringMetricDescriptor.cpp
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

#include "SDCLib/Data/SDC/MDIB/StringMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/CodedValue.h"
#include "SDCLib/Data/SDC/MDIB/Relation.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


StringMetricDescriptor::StringMetricDescriptor(
		Handle handle
		,
		CodedValue unit
		,
		MetricCategory metriccategory
		,
		MetricAvailability metricavailability
) : data(Defaults::StringMetricDescriptorInit(
		handle
		,
		unit
		,
		metriccategory
		,
		metricavailability
))
{}

StringMetricDescriptor::operator CDM::StringMetricDescriptor() const {
	return *data;
}

StringMetricDescriptor::StringMetricDescriptor(const CDM::StringMetricDescriptor & object)
: data(new CDM::StringMetricDescriptor(object))
{ }

StringMetricDescriptor::StringMetricDescriptor(const StringMetricDescriptor & object)
: data(std::make_shared<CDM::StringMetricDescriptor>(*object.data))
{ }

void StringMetricDescriptor::copyFrom(const StringMetricDescriptor & object) {
	data = std::make_shared<CDM::StringMetricDescriptor>(*object.data);
}

StringMetricDescriptor & StringMetricDescriptor:: operator=(const StringMetricDescriptor& object) {
	copyFrom(object);
	return *this;
}


StringMetricDescriptor & StringMetricDescriptor::setType(const CodedValue & value) {
	data->setType(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricDescriptor::getType(CodedValue & out) const {
	if (data->getType().present()) {
		out = ConvertFromCDM::convert(data->getType().get());
		return true;
	}
	return false;
}

CodedValue StringMetricDescriptor::getType() const {
	return ConvertFromCDM::convert(data->getType().get());
}

bool StringMetricDescriptor::hasType() const {
	return data->getType().present();
}

StringMetricDescriptor & StringMetricDescriptor::setHandle(const Handle & value) {
	data->setHandle(ConvertToCDM::convert(value));
	return *this;
}


Handle StringMetricDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->getHandle());
}

StringMetricDescriptor & StringMetricDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter StringMetricDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool StringMetricDescriptor::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

StringMetricDescriptor & StringMetricDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->setSafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->getSafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->getSafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification StringMetricDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->getSafetyClassification().get());
}

bool StringMetricDescriptor::hasSafetyClassification() const {
	return data->getSafetyClassification().present();
}

StringMetricDescriptor & StringMetricDescriptor::setUnit(const CodedValue & value) {
	data->setUnit(ConvertToCDM::convert(value));
	return *this;
}


CodedValue StringMetricDescriptor::getUnit() const {
	return ConvertFromCDM::convert(data->getUnit());
}

StringMetricDescriptor & StringMetricDescriptor::setMetricCategory(const MetricCategory & value) {
	data->setMetricCategory(ConvertToCDM::convert(value));
	return *this;
}


MetricCategory StringMetricDescriptor::getMetricCategory() const {
	return ConvertFromCDM::convert(data->getMetricCategory());
}

StringMetricDescriptor & StringMetricDescriptor::setDerivationMethod(const DerivationMethod & value) {
	data->setDerivationMethod(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricDescriptor::getDerivationMethod(DerivationMethod & out) const {
	if (data->getDerivationMethod().present()) {
		out = ConvertFromCDM::convert(data->getDerivationMethod().get());
		return true;
	}
	return false;
}

DerivationMethod StringMetricDescriptor::getDerivationMethod() const {
	return ConvertFromCDM::convert(data->getDerivationMethod().get());
}

bool StringMetricDescriptor::hasDerivationMethod() const {
	return data->getDerivationMethod().present();
}

StringMetricDescriptor & StringMetricDescriptor::setMetricAvailability(const MetricAvailability & value) {
	data->setMetricAvailability(ConvertToCDM::convert(value));
	return *this;
}


MetricAvailability StringMetricDescriptor::getMetricAvailability() const {
	return ConvertFromCDM::convert(data->getMetricAvailability());
}

StringMetricDescriptor & StringMetricDescriptor::setMaxMeasurementTime(const xml_schema::Duration & value) {
	data->setMaxMeasurementTime(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricDescriptor::getMaxMeasurementTime(xml_schema::Duration & out) const {
	if (data->getMaxMeasurementTime().present()) {
		out = ConvertFromCDM::convert(data->getMaxMeasurementTime().get());
		return true;
	}
	return false;
}

xml_schema::Duration StringMetricDescriptor::getMaxMeasurementTime() const {
	return ConvertFromCDM::convert(data->getMaxMeasurementTime().get());
}

bool StringMetricDescriptor::hasMaxMeasurementTime() const {
	return data->getMaxMeasurementTime().present();
}

StringMetricDescriptor & StringMetricDescriptor::setMaxDelayTime(const xml_schema::Duration & value) {
	data->setMaxDelayTime(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricDescriptor::getMaxDelayTime(xml_schema::Duration & out) const {
	if (data->getMaxDelayTime().present()) {
		out = ConvertFromCDM::convert(data->getMaxDelayTime().get());
		return true;
	}
	return false;
}

xml_schema::Duration StringMetricDescriptor::getMaxDelayTime() const {
	return ConvertFromCDM::convert(data->getMaxDelayTime().get());
}

bool StringMetricDescriptor::hasMaxDelayTime() const {
	return data->getMaxDelayTime().present();
}

StringMetricDescriptor & StringMetricDescriptor::setDeterminationPeriod(const xml_schema::Duration & value) {
	data->setDeterminationPeriod(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricDescriptor::getDeterminationPeriod(xml_schema::Duration & out) const {
	if (data->getDeterminationPeriod().present()) {
		out = ConvertFromCDM::convert(data->getDeterminationPeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration StringMetricDescriptor::getDeterminationPeriod() const {
	return ConvertFromCDM::convert(data->getDeterminationPeriod().get());
}

bool StringMetricDescriptor::hasDeterminationPeriod() const {
	return data->getDeterminationPeriod().present();
}

StringMetricDescriptor & StringMetricDescriptor::setLifeTimePeriod(const xml_schema::Duration & value) {
	data->setLifeTimePeriod(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricDescriptor::getLifeTimePeriod(xml_schema::Duration & out) const {
	if (data->getLifeTimePeriod().present()) {
		out = ConvertFromCDM::convert(data->getLifeTimePeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration StringMetricDescriptor::getLifeTimePeriod() const {
	return ConvertFromCDM::convert(data->getLifeTimePeriod().get());
}

bool StringMetricDescriptor::hasLifeTimePeriod() const {
	return data->getLifeTimePeriod().present();
}

StringMetricDescriptor & StringMetricDescriptor::setActivationDuration(const xml_schema::Duration & value) {
	data->setActivationDuration(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricDescriptor::getActivationDuration(xml_schema::Duration & out) const {
	if (data->getActivationDuration().present()) {
		out = ConvertFromCDM::convert(data->getActivationDuration().get());
		return true;
	}
	return false;
}

xml_schema::Duration StringMetricDescriptor::getActivationDuration() const {
	return ConvertFromCDM::convert(data->getActivationDuration().get());
}

bool StringMetricDescriptor::hasActivationDuration() const {
	return data->getActivationDuration().present();
}

StringMetricDescriptor & StringMetricDescriptor::addBodySite(const CodedValue & value) {
	data->getBodySite().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CodedValue> StringMetricDescriptor::getBodySiteList() const {
	std::vector<CodedValue> result;
	result.reserve(data->getBodySite().size());
	for (const auto & value: data->getBodySite()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void StringMetricDescriptor::clearBodySiteList() {
	data->getBodySite().clear();
}

StringMetricDescriptor & StringMetricDescriptor::addRelation(const Relation & value) {
	data->getRelation().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<Relation> StringMetricDescriptor::getRelationList() const {
	std::vector<Relation> result;
	result.reserve(data->getRelation().size());
	for (const auto & value: data->getRelation()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void StringMetricDescriptor::clearRelationList() {
	data->getRelation().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

