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
 *  RealTimeSampleArrayMetricDescriptor.cpp
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

#include "SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricDescriptor.h"
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


RealTimeSampleArrayMetricDescriptor::RealTimeSampleArrayMetricDescriptor(
		Handle handle
		,
		CodedValue unit
		,
		MetricCategory metriccategory
		,
		MetricAvailability metricavailability
		,
		double resolution
		,
		xml_schema::Duration sampleperiod
) : data(Defaults::RealTimeSampleArrayMetricDescriptorInit(
		handle
		,
		unit
		,
		metriccategory
		,
		metricavailability
		,
		resolution
		,
		sampleperiod
))
{}

RealTimeSampleArrayMetricDescriptor::operator CDM::RealTimeSampleArrayMetricDescriptor() const {
	return *data;
}

RealTimeSampleArrayMetricDescriptor::RealTimeSampleArrayMetricDescriptor(const CDM::RealTimeSampleArrayMetricDescriptor & object)
: data(new CDM::RealTimeSampleArrayMetricDescriptor(object))
{ }

RealTimeSampleArrayMetricDescriptor::RealTimeSampleArrayMetricDescriptor(const RealTimeSampleArrayMetricDescriptor & object)
: data(std::make_shared<CDM::RealTimeSampleArrayMetricDescriptor>(*object.data))
{ }

void RealTimeSampleArrayMetricDescriptor::copyFrom(const RealTimeSampleArrayMetricDescriptor & object) {
	data = std::make_shared<CDM::RealTimeSampleArrayMetricDescriptor>(*object.data);
}

RealTimeSampleArrayMetricDescriptor & RealTimeSampleArrayMetricDescriptor:: operator=(const RealTimeSampleArrayMetricDescriptor& object) {
	copyFrom(object);
	return *this;
}


RealTimeSampleArrayMetricDescriptor & RealTimeSampleArrayMetricDescriptor::setType(const CodedValue & value) {
	data->setType(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayMetricDescriptor::getType(CodedValue & out) const {
	if (data->getType().present()) {
		out = ConvertFromCDM::convert(data->getType().get());
		return true;
	}
	return false;
}

CodedValue RealTimeSampleArrayMetricDescriptor::getType() const {
	return ConvertFromCDM::convert(data->getType().get());
}

bool RealTimeSampleArrayMetricDescriptor::hasType() const {
	return data->getType().present();
}

RealTimeSampleArrayMetricDescriptor & RealTimeSampleArrayMetricDescriptor::setHandle(const Handle & value) {
	data->setHandle(ConvertToCDM::convert(value));
	return *this;
}


Handle RealTimeSampleArrayMetricDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->getHandle());
}

RealTimeSampleArrayMetricDescriptor & RealTimeSampleArrayMetricDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayMetricDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter RealTimeSampleArrayMetricDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool RealTimeSampleArrayMetricDescriptor::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

RealTimeSampleArrayMetricDescriptor & RealTimeSampleArrayMetricDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->setSafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayMetricDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->getSafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->getSafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification RealTimeSampleArrayMetricDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->getSafetyClassification().get());
}

bool RealTimeSampleArrayMetricDescriptor::hasSafetyClassification() const {
	return data->getSafetyClassification().present();
}

RealTimeSampleArrayMetricDescriptor & RealTimeSampleArrayMetricDescriptor::setUnit(const CodedValue & value) {
	data->setUnit(ConvertToCDM::convert(value));
	return *this;
}


CodedValue RealTimeSampleArrayMetricDescriptor::getUnit() const {
	return ConvertFromCDM::convert(data->getUnit());
}

RealTimeSampleArrayMetricDescriptor & RealTimeSampleArrayMetricDescriptor::setMetricCategory(const MetricCategory & value) {
	data->setMetricCategory(ConvertToCDM::convert(value));
	return *this;
}


MetricCategory RealTimeSampleArrayMetricDescriptor::getMetricCategory() const {
	return ConvertFromCDM::convert(data->getMetricCategory());
}

RealTimeSampleArrayMetricDescriptor & RealTimeSampleArrayMetricDescriptor::setDerivationMethod(const DerivationMethod & value) {
	data->setDerivationMethod(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayMetricDescriptor::getDerivationMethod(DerivationMethod & out) const {
	if (data->getDerivationMethod().present()) {
		out = ConvertFromCDM::convert(data->getDerivationMethod().get());
		return true;
	}
	return false;
}

DerivationMethod RealTimeSampleArrayMetricDescriptor::getDerivationMethod() const {
	return ConvertFromCDM::convert(data->getDerivationMethod().get());
}

bool RealTimeSampleArrayMetricDescriptor::hasDerivationMethod() const {
	return data->getDerivationMethod().present();
}

RealTimeSampleArrayMetricDescriptor & RealTimeSampleArrayMetricDescriptor::setMetricAvailability(const MetricAvailability & value) {
	data->setMetricAvailability(ConvertToCDM::convert(value));
	return *this;
}


MetricAvailability RealTimeSampleArrayMetricDescriptor::getMetricAvailability() const {
	return ConvertFromCDM::convert(data->getMetricAvailability());
}

RealTimeSampleArrayMetricDescriptor & RealTimeSampleArrayMetricDescriptor::setMaxMeasurementTime(const xml_schema::Duration & value) {
	data->setMaxMeasurementTime(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayMetricDescriptor::getMaxMeasurementTime(xml_schema::Duration & out) const {
	if (data->getMaxMeasurementTime().present()) {
		out = ConvertFromCDM::convert(data->getMaxMeasurementTime().get());
		return true;
	}
	return false;
}

xml_schema::Duration RealTimeSampleArrayMetricDescriptor::getMaxMeasurementTime() const {
	return ConvertFromCDM::convert(data->getMaxMeasurementTime().get());
}

bool RealTimeSampleArrayMetricDescriptor::hasMaxMeasurementTime() const {
	return data->getMaxMeasurementTime().present();
}

RealTimeSampleArrayMetricDescriptor & RealTimeSampleArrayMetricDescriptor::setMaxDelayTime(const xml_schema::Duration & value) {
	data->setMaxDelayTime(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayMetricDescriptor::getMaxDelayTime(xml_schema::Duration & out) const {
	if (data->getMaxDelayTime().present()) {
		out = ConvertFromCDM::convert(data->getMaxDelayTime().get());
		return true;
	}
	return false;
}

xml_schema::Duration RealTimeSampleArrayMetricDescriptor::getMaxDelayTime() const {
	return ConvertFromCDM::convert(data->getMaxDelayTime().get());
}

bool RealTimeSampleArrayMetricDescriptor::hasMaxDelayTime() const {
	return data->getMaxDelayTime().present();
}

RealTimeSampleArrayMetricDescriptor & RealTimeSampleArrayMetricDescriptor::setDeterminationPeriod(const xml_schema::Duration & value) {
	data->setDeterminationPeriod(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayMetricDescriptor::getDeterminationPeriod(xml_schema::Duration & out) const {
	if (data->getDeterminationPeriod().present()) {
		out = ConvertFromCDM::convert(data->getDeterminationPeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration RealTimeSampleArrayMetricDescriptor::getDeterminationPeriod() const {
	return ConvertFromCDM::convert(data->getDeterminationPeriod().get());
}

bool RealTimeSampleArrayMetricDescriptor::hasDeterminationPeriod() const {
	return data->getDeterminationPeriod().present();
}

RealTimeSampleArrayMetricDescriptor & RealTimeSampleArrayMetricDescriptor::setLifeTimePeriod(const xml_schema::Duration & value) {
	data->setLifeTimePeriod(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayMetricDescriptor::getLifeTimePeriod(xml_schema::Duration & out) const {
	if (data->getLifeTimePeriod().present()) {
		out = ConvertFromCDM::convert(data->getLifeTimePeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration RealTimeSampleArrayMetricDescriptor::getLifeTimePeriod() const {
	return ConvertFromCDM::convert(data->getLifeTimePeriod().get());
}

bool RealTimeSampleArrayMetricDescriptor::hasLifeTimePeriod() const {
	return data->getLifeTimePeriod().present();
}

RealTimeSampleArrayMetricDescriptor & RealTimeSampleArrayMetricDescriptor::setActivationDuration(const xml_schema::Duration & value) {
	data->setActivationDuration(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayMetricDescriptor::getActivationDuration(xml_schema::Duration & out) const {
	if (data->getActivationDuration().present()) {
		out = ConvertFromCDM::convert(data->getActivationDuration().get());
		return true;
	}
	return false;
}

xml_schema::Duration RealTimeSampleArrayMetricDescriptor::getActivationDuration() const {
	return ConvertFromCDM::convert(data->getActivationDuration().get());
}

bool RealTimeSampleArrayMetricDescriptor::hasActivationDuration() const {
	return data->getActivationDuration().present();
}

RealTimeSampleArrayMetricDescriptor & RealTimeSampleArrayMetricDescriptor::addBodySite(const CodedValue & value) {
	data->getBodySite().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CodedValue> RealTimeSampleArrayMetricDescriptor::getBodySiteList() const {
	std::vector<CodedValue> result;
	result.reserve(data->getBodySite().size());
	for (const auto & value: data->getBodySite()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void RealTimeSampleArrayMetricDescriptor::clearBodySiteList() {
	data->getBodySite().clear();
}

RealTimeSampleArrayMetricDescriptor & RealTimeSampleArrayMetricDescriptor::addRelation(const Relation & value) {
	data->getRelation().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<Relation> RealTimeSampleArrayMetricDescriptor::getRelationList() const {
	std::vector<Relation> result;
	result.reserve(data->getRelation().size());
	for (const auto & value: data->getRelation()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void RealTimeSampleArrayMetricDescriptor::clearRelationList() {
	data->getRelation().clear();
}

RealTimeSampleArrayMetricDescriptor & RealTimeSampleArrayMetricDescriptor::setResolution(const double & value) {
	data->setResolution(ConvertToCDM::convert(value));
	return *this;
}


double RealTimeSampleArrayMetricDescriptor::getResolution() const {
	return ConvertFromCDM::convert(data->getResolution());
}

RealTimeSampleArrayMetricDescriptor & RealTimeSampleArrayMetricDescriptor::setSamplePeriod(const xml_schema::Duration & value) {
	data->setSamplePeriod(ConvertToCDM::convert(value));
	return *this;
}


xml_schema::Duration RealTimeSampleArrayMetricDescriptor::getSamplePeriod() const {
	return ConvertFromCDM::convert(data->getSamplePeriod());
}

RealTimeSampleArrayMetricDescriptor & RealTimeSampleArrayMetricDescriptor::addTechnicalRange(const Range & value) {
	data->getTechnicalRange().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<Range> RealTimeSampleArrayMetricDescriptor::getTechnicalRangeList() const {
	std::vector<Range> result;
	result.reserve(data->getTechnicalRange().size());
	for (const auto & value: data->getTechnicalRange()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void RealTimeSampleArrayMetricDescriptor::clearTechnicalRangeList() {
	data->getTechnicalRange().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

