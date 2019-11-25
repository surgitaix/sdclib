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
 *  NumericMetricDescriptor.cpp
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

#include "SDCLib/Data/SDC/MDIB/NumericMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/Range.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"
#include "SDCLib/Data/SDC/MDIB/Relation.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


NumericMetricDescriptor::NumericMetricDescriptor(
		Handle handle
		,
		CodedValue unit
		,
		MetricCategory metriccategory
		,
		MetricAvailability metricavailability
		,
		double resolution
) : data(Defaults::NumericMetricDescriptorInit(
		handle
		,
		unit
		,
		metriccategory
		,
		metricavailability
		,
		resolution
)) {}

NumericMetricDescriptor::operator CDM::NumericMetricDescriptor() const {
	return *data;
}

NumericMetricDescriptor::NumericMetricDescriptor(const CDM::NumericMetricDescriptor & object) : data(new CDM::NumericMetricDescriptor(object)) {

}

NumericMetricDescriptor::NumericMetricDescriptor(const NumericMetricDescriptor & object) : data(new CDM::NumericMetricDescriptor(*object.data)) {

}

NumericMetricDescriptor::~NumericMetricDescriptor() {

}

void NumericMetricDescriptor::copyFrom(const NumericMetricDescriptor & object) {
	data = std::shared_ptr<CDM::NumericMetricDescriptor>( new CDM::NumericMetricDescriptor(*object.data));
}

NumericMetricDescriptor & NumericMetricDescriptor:: operator=(const NumericMetricDescriptor & object) {
	copyFrom(object);
	return *this;
}


NumericMetricDescriptor & NumericMetricDescriptor::setType(const CodedValue & value) {
	data->setType(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricDescriptor::getType(CodedValue & out) const {
	if (data->getType().present()) {
		out = ConvertFromCDM::convert(data->getType().get());
		return true;
	}
	return false;
}

CodedValue NumericMetricDescriptor::getType() const {
	return ConvertFromCDM::convert(data->getType().get());
}

bool NumericMetricDescriptor::hasType() const {
	return data->getType().present();
}

NumericMetricDescriptor & NumericMetricDescriptor::setHandle(const Handle & value) {
	data->setHandle(ConvertToCDM::convert(value));
	return *this;
}


Handle NumericMetricDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->getHandle());
}

NumericMetricDescriptor & NumericMetricDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter NumericMetricDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool NumericMetricDescriptor::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

NumericMetricDescriptor & NumericMetricDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->setSafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->getSafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->getSafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification NumericMetricDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->getSafetyClassification().get());
}

bool NumericMetricDescriptor::hasSafetyClassification() const {
	return data->getSafetyClassification().present();
}

NumericMetricDescriptor & NumericMetricDescriptor::setUnit(const CodedValue & value) {
	data->setUnit(ConvertToCDM::convert(value));
	return *this;
}


CodedValue NumericMetricDescriptor::getUnit() const {
	return ConvertFromCDM::convert(data->getUnit());
}

NumericMetricDescriptor & NumericMetricDescriptor::setMetricCategory(const MetricCategory & value) {
	data->setMetricCategory(ConvertToCDM::convert(value));
	return *this;
}


MetricCategory NumericMetricDescriptor::getMetricCategory() const {
	return ConvertFromCDM::convert(data->getMetricCategory());
}

NumericMetricDescriptor & NumericMetricDescriptor::setDerivationMethod(const DerivationMethod & value) {
	data->setDerivationMethod(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricDescriptor::getDerivationMethod(DerivationMethod & out) const {
	if (data->getDerivationMethod().present()) {
		out = ConvertFromCDM::convert(data->getDerivationMethod().get());
		return true;
	}
	return false;
}

DerivationMethod NumericMetricDescriptor::getDerivationMethod() const {
	return ConvertFromCDM::convert(data->getDerivationMethod().get());
}

bool NumericMetricDescriptor::hasDerivationMethod() const {
	return data->getDerivationMethod().present();
}

NumericMetricDescriptor & NumericMetricDescriptor::setMetricAvailability(const MetricAvailability & value) {
	data->setMetricAvailability(ConvertToCDM::convert(value));
	return *this;
}


MetricAvailability NumericMetricDescriptor::getMetricAvailability() const {
	return ConvertFromCDM::convert(data->getMetricAvailability());
}

NumericMetricDescriptor & NumericMetricDescriptor::setMaxMeasurementTime(const xml_schema::Duration & value) {
	data->setMaxMeasurementTime(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricDescriptor::getMaxMeasurementTime(xml_schema::Duration & out) const {
	if (data->getMaxMeasurementTime().present()) {
		out = ConvertFromCDM::convert(data->getMaxMeasurementTime().get());
		return true;
	}
	return false;
}

xml_schema::Duration NumericMetricDescriptor::getMaxMeasurementTime() const {
	return ConvertFromCDM::convert(data->getMaxMeasurementTime().get());
}

bool NumericMetricDescriptor::hasMaxMeasurementTime() const {
	return data->getMaxMeasurementTime().present();
}

NumericMetricDescriptor & NumericMetricDescriptor::setMaxDelayTime(const xml_schema::Duration & value) {
	data->setMaxDelayTime(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricDescriptor::getMaxDelayTime(xml_schema::Duration & out) const {
	if (data->getMaxDelayTime().present()) {
		out = ConvertFromCDM::convert(data->getMaxDelayTime().get());
		return true;
	}
	return false;
}

xml_schema::Duration NumericMetricDescriptor::getMaxDelayTime() const {
	return ConvertFromCDM::convert(data->getMaxDelayTime().get());
}

bool NumericMetricDescriptor::hasMaxDelayTime() const {
	return data->getMaxDelayTime().present();
}

NumericMetricDescriptor & NumericMetricDescriptor::setDeterminationPeriod(const xml_schema::Duration & value) {
	data->setDeterminationPeriod(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricDescriptor::getDeterminationPeriod(xml_schema::Duration & out) const {
	if (data->getDeterminationPeriod().present()) {
		out = ConvertFromCDM::convert(data->getDeterminationPeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration NumericMetricDescriptor::getDeterminationPeriod() const {
	return ConvertFromCDM::convert(data->getDeterminationPeriod().get());
}

bool NumericMetricDescriptor::hasDeterminationPeriod() const {
	return data->getDeterminationPeriod().present();
}

NumericMetricDescriptor & NumericMetricDescriptor::setLifeTimePeriod(const xml_schema::Duration & value) {
	data->setLifeTimePeriod(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricDescriptor::getLifeTimePeriod(xml_schema::Duration & out) const {
	if (data->getLifeTimePeriod().present()) {
		out = ConvertFromCDM::convert(data->getLifeTimePeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration NumericMetricDescriptor::getLifeTimePeriod() const {
	return ConvertFromCDM::convert(data->getLifeTimePeriod().get());
}

bool NumericMetricDescriptor::hasLifeTimePeriod() const {
	return data->getLifeTimePeriod().present();
}

NumericMetricDescriptor & NumericMetricDescriptor::setActivationDuration(const xml_schema::Duration & value) {
	data->setActivationDuration(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricDescriptor::getActivationDuration(xml_schema::Duration & out) const {
	if (data->getActivationDuration().present()) {
		out = ConvertFromCDM::convert(data->getActivationDuration().get());
		return true;
	}
	return false;
}

xml_schema::Duration NumericMetricDescriptor::getActivationDuration() const {
	return ConvertFromCDM::convert(data->getActivationDuration().get());
}

bool NumericMetricDescriptor::hasActivationDuration() const {
	return data->getActivationDuration().present();
}

NumericMetricDescriptor & NumericMetricDescriptor::addBodySite(const CodedValue & value) {
	data->getBodySite().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CodedValue> NumericMetricDescriptor::getBodySiteList() const {
	std::vector<CodedValue> result;
	result.reserve(data->getBodySite().size());
	for (const auto & value: data->getBodySite()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void NumericMetricDescriptor::clearBodySiteList() {
	data->getBodySite().clear();
}

NumericMetricDescriptor & NumericMetricDescriptor::addRelation(const Relation & value) {
	data->getRelation().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<Relation> NumericMetricDescriptor::getRelationList() const {
	std::vector<Relation> result;
	result.reserve(data->getRelation().size());
	for (const auto & value: data->getRelation()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void NumericMetricDescriptor::clearRelationList() {
	data->getRelation().clear();
}

NumericMetricDescriptor & NumericMetricDescriptor::setResolution(const double & value) {
	data->setResolution(ConvertToCDM::convert(value));
	return *this;
}


double NumericMetricDescriptor::getResolution() const {
	return ConvertFromCDM::convert(data->getResolution());
}

NumericMetricDescriptor & NumericMetricDescriptor::setAveragingPeriod(const xml_schema::Duration & value) {
	data->setAveragingPeriod(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricDescriptor::getAveragingPeriod(xml_schema::Duration & out) const {
	if (data->getAveragingPeriod().present()) {
		out = ConvertFromCDM::convert(data->getAveragingPeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration NumericMetricDescriptor::getAveragingPeriod() const {
	return ConvertFromCDM::convert(data->getAveragingPeriod().get());
}

bool NumericMetricDescriptor::hasAveragingPeriod() const {
	return data->getAveragingPeriod().present();
}

NumericMetricDescriptor & NumericMetricDescriptor::addTechnicalRange(const Range & value) {
	data->getTechnicalRange().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<Range> NumericMetricDescriptor::getTechnicalRangeList() const {
	std::vector<Range> result;
	result.reserve(data->getTechnicalRange().size());
	for (const auto & value: data->getTechnicalRange()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void NumericMetricDescriptor::clearTechnicalRangeList() {
	data->getTechnicalRange().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

