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
 *  DistributionSampleArrayMetricDescriptor.cpp
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

#include "SDCLib/Data/SDC/MDIB/DistributionSampleArrayMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/Range.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"
#include "SDCLib/Data/SDC/MDIB/Relation.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


DistributionSampleArrayMetricDescriptor::DistributionSampleArrayMetricDescriptor(
		Handle handle
		,
		CodedValue unit
		,
		MetricCategory metriccategory
		,
		MetricAvailability metricavailability
		,
		CodedValue domainunit
		,
		Range distributionrange
		,
		double resolution
) : data(Defaults::DistributionSampleArrayMetricDescriptorInit(
		handle
		,
		unit
		,
		metriccategory
		,
		metricavailability
		,
		domainunit
		,
		distributionrange
		,
		resolution
))
{}

DistributionSampleArrayMetricDescriptor::operator CDM::DistributionSampleArrayMetricDescriptor() const {
	return *data;
}

DistributionSampleArrayMetricDescriptor::DistributionSampleArrayMetricDescriptor(const CDM::DistributionSampleArrayMetricDescriptor & object)
: data(new CDM::DistributionSampleArrayMetricDescriptor(object))
{ }

DistributionSampleArrayMetricDescriptor::DistributionSampleArrayMetricDescriptor(const DistributionSampleArrayMetricDescriptor & object)
: data(std::make_shared<CDM::DistributionSampleArrayMetricDescriptor>(*object.data))
{ }

void DistributionSampleArrayMetricDescriptor::copyFrom(const DistributionSampleArrayMetricDescriptor & object) {
	data = std::make_shared<CDM::DistributionSampleArrayMetricDescriptor>(*object.data);
}

DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor:: operator=(const DistributionSampleArrayMetricDescriptor& object) {
	copyFrom(object);
	return *this;
}


DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor::setType(const CodedValue & value) {
	data->setType(ConvertToCDM::convert(value));
	return *this;
}

bool DistributionSampleArrayMetricDescriptor::getType(CodedValue & out) const {
	if (data->getType().present()) {
		out = ConvertFromCDM::convert(data->getType().get());
		return true;
	}
	return false;
}

CodedValue DistributionSampleArrayMetricDescriptor::getType() const {
	return ConvertFromCDM::convert(data->getType().get());
}

bool DistributionSampleArrayMetricDescriptor::hasType() const {
	return data->getType().present();
}

DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor::setHandle(const Handle & value) {
	data->setHandle(ConvertToCDM::convert(value));
	return *this;
}


Handle DistributionSampleArrayMetricDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->getHandle());
}

DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool DistributionSampleArrayMetricDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter DistributionSampleArrayMetricDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool DistributionSampleArrayMetricDescriptor::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->setSafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool DistributionSampleArrayMetricDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->getSafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->getSafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification DistributionSampleArrayMetricDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->getSafetyClassification().get());
}

bool DistributionSampleArrayMetricDescriptor::hasSafetyClassification() const {
	return data->getSafetyClassification().present();
}

DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor::setUnit(const CodedValue & value) {
	data->setUnit(ConvertToCDM::convert(value));
	return *this;
}


CodedValue DistributionSampleArrayMetricDescriptor::getUnit() const {
	return ConvertFromCDM::convert(data->getUnit());
}

DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor::setMetricCategory(const MetricCategory & value) {
	data->setMetricCategory(ConvertToCDM::convert(value));
	return *this;
}


MetricCategory DistributionSampleArrayMetricDescriptor::getMetricCategory() const {
	return ConvertFromCDM::convert(data->getMetricCategory());
}

DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor::setDerivationMethod(const DerivationMethod & value) {
	data->setDerivationMethod(ConvertToCDM::convert(value));
	return *this;
}

bool DistributionSampleArrayMetricDescriptor::getDerivationMethod(DerivationMethod & out) const {
	if (data->getDerivationMethod().present()) {
		out = ConvertFromCDM::convert(data->getDerivationMethod().get());
		return true;
	}
	return false;
}

DerivationMethod DistributionSampleArrayMetricDescriptor::getDerivationMethod() const {
	return ConvertFromCDM::convert(data->getDerivationMethod().get());
}

bool DistributionSampleArrayMetricDescriptor::hasDerivationMethod() const {
	return data->getDerivationMethod().present();
}

DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor::setMetricAvailability(const MetricAvailability & value) {
	data->setMetricAvailability(ConvertToCDM::convert(value));
	return *this;
}


MetricAvailability DistributionSampleArrayMetricDescriptor::getMetricAvailability() const {
	return ConvertFromCDM::convert(data->getMetricAvailability());
}

DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor::setMaxMeasurementTime(const xml_schema::Duration & value) {
	data->setMaxMeasurementTime(ConvertToCDM::convert(value));
	return *this;
}

bool DistributionSampleArrayMetricDescriptor::getMaxMeasurementTime(xml_schema::Duration & out) const {
	if (data->getMaxMeasurementTime().present()) {
		out = ConvertFromCDM::convert(data->getMaxMeasurementTime().get());
		return true;
	}
	return false;
}

xml_schema::Duration DistributionSampleArrayMetricDescriptor::getMaxMeasurementTime() const {
	return ConvertFromCDM::convert(data->getMaxMeasurementTime().get());
}

bool DistributionSampleArrayMetricDescriptor::hasMaxMeasurementTime() const {
	return data->getMaxMeasurementTime().present();
}

DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor::setMaxDelayTime(const xml_schema::Duration & value) {
	data->setMaxDelayTime(ConvertToCDM::convert(value));
	return *this;
}

bool DistributionSampleArrayMetricDescriptor::getMaxDelayTime(xml_schema::Duration & out) const {
	if (data->getMaxDelayTime().present()) {
		out = ConvertFromCDM::convert(data->getMaxDelayTime().get());
		return true;
	}
	return false;
}

xml_schema::Duration DistributionSampleArrayMetricDescriptor::getMaxDelayTime() const {
	return ConvertFromCDM::convert(data->getMaxDelayTime().get());
}

bool DistributionSampleArrayMetricDescriptor::hasMaxDelayTime() const {
	return data->getMaxDelayTime().present();
}

DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor::setDeterminationPeriod(const xml_schema::Duration & value) {
	data->setDeterminationPeriod(ConvertToCDM::convert(value));
	return *this;
}

bool DistributionSampleArrayMetricDescriptor::getDeterminationPeriod(xml_schema::Duration & out) const {
	if (data->getDeterminationPeriod().present()) {
		out = ConvertFromCDM::convert(data->getDeterminationPeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration DistributionSampleArrayMetricDescriptor::getDeterminationPeriod() const {
	return ConvertFromCDM::convert(data->getDeterminationPeriod().get());
}

bool DistributionSampleArrayMetricDescriptor::hasDeterminationPeriod() const {
	return data->getDeterminationPeriod().present();
}

DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor::setLifeTimePeriod(const xml_schema::Duration & value) {
	data->setLifeTimePeriod(ConvertToCDM::convert(value));
	return *this;
}

bool DistributionSampleArrayMetricDescriptor::getLifeTimePeriod(xml_schema::Duration & out) const {
	if (data->getLifeTimePeriod().present()) {
		out = ConvertFromCDM::convert(data->getLifeTimePeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration DistributionSampleArrayMetricDescriptor::getLifeTimePeriod() const {
	return ConvertFromCDM::convert(data->getLifeTimePeriod().get());
}

bool DistributionSampleArrayMetricDescriptor::hasLifeTimePeriod() const {
	return data->getLifeTimePeriod().present();
}

DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor::setActivationDuration(const xml_schema::Duration & value) {
	data->setActivationDuration(ConvertToCDM::convert(value));
	return *this;
}

bool DistributionSampleArrayMetricDescriptor::getActivationDuration(xml_schema::Duration & out) const {
	if (data->getActivationDuration().present()) {
		out = ConvertFromCDM::convert(data->getActivationDuration().get());
		return true;
	}
	return false;
}

xml_schema::Duration DistributionSampleArrayMetricDescriptor::getActivationDuration() const {
	return ConvertFromCDM::convert(data->getActivationDuration().get());
}

bool DistributionSampleArrayMetricDescriptor::hasActivationDuration() const {
	return data->getActivationDuration().present();
}

DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor::addBodySite(const CodedValue & value) {
	data->getBodySite().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CodedValue> DistributionSampleArrayMetricDescriptor::getBodySiteList() const {
	std::vector<CodedValue> result;
	result.reserve(data->getBodySite().size());
	for (const auto & value: data->getBodySite()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DistributionSampleArrayMetricDescriptor::clearBodySiteList() {
	data->getBodySite().clear();
}

DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor::addRelation(const Relation & value) {
	data->getRelation().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<Relation> DistributionSampleArrayMetricDescriptor::getRelationList() const {
	std::vector<Relation> result;
	result.reserve(data->getRelation().size());
	for (const auto & value: data->getRelation()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DistributionSampleArrayMetricDescriptor::clearRelationList() {
	data->getRelation().clear();
}

DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor::setDomainUnit(const CodedValue & value) {
	data->setDomainUnit(ConvertToCDM::convert(value));
	return *this;
}


CodedValue DistributionSampleArrayMetricDescriptor::getDomainUnit() const {
	return ConvertFromCDM::convert(data->getDomainUnit());
}

DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor::setDistributionRange(const Range & value) {
	data->setDistributionRange(ConvertToCDM::convert(value));
	return *this;
}


Range DistributionSampleArrayMetricDescriptor::getDistributionRange() const {
	return ConvertFromCDM::convert(data->getDistributionRange());
}

DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor::setResolution(const double & value) {
	data->setResolution(ConvertToCDM::convert(value));
	return *this;
}


double DistributionSampleArrayMetricDescriptor::getResolution() const {
	return ConvertFromCDM::convert(data->getResolution());
}

DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor::addTechnicalRange(const Range & value) {
	data->getTechnicalRange().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<Range> DistributionSampleArrayMetricDescriptor::getTechnicalRangeList() const {
	std::vector<Range> result;
	result.reserve(data->getTechnicalRange().size());
	for (const auto & value: data->getTechnicalRange()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DistributionSampleArrayMetricDescriptor::clearTechnicalRangeList() {
	data->getTechnicalRange().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

