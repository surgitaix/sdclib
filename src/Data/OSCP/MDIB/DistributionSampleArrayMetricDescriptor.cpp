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

#include "OSCLib/Data/OSCP/MDIB/DistributionSampleArrayMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/Range.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

namespace OSCLib {
namespace Data {
namespace OSCP {


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
)) {}

DistributionSampleArrayMetricDescriptor::operator CDM::DistributionSampleArrayMetricDescriptor() const {
	return *data;
}

DistributionSampleArrayMetricDescriptor::DistributionSampleArrayMetricDescriptor(const CDM::DistributionSampleArrayMetricDescriptor & object) : data(new CDM::DistributionSampleArrayMetricDescriptor(object)) {

}

DistributionSampleArrayMetricDescriptor::DistributionSampleArrayMetricDescriptor(const DistributionSampleArrayMetricDescriptor & object) : data(new CDM::DistributionSampleArrayMetricDescriptor(*object.data)) {

}

DistributionSampleArrayMetricDescriptor::~DistributionSampleArrayMetricDescriptor() {

}

void DistributionSampleArrayMetricDescriptor::copyFrom(const DistributionSampleArrayMetricDescriptor & object) {
	*data = *object.data;
}

DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor:: operator=(const DistributionSampleArrayMetricDescriptor & object) {
	copyFrom(object);
	return *this;
}


DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool DistributionSampleArrayMetricDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue DistributionSampleArrayMetricDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool DistributionSampleArrayMetricDescriptor::hasType() const {
	return data->Type().present();
}
	
DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor::setHandle(const Handle & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


Handle DistributionSampleArrayMetricDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool DistributionSampleArrayMetricDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter DistributionSampleArrayMetricDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool DistributionSampleArrayMetricDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->SafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool DistributionSampleArrayMetricDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->SafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->SafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification DistributionSampleArrayMetricDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->SafetyClassification().get());
}
	
bool DistributionSampleArrayMetricDescriptor::hasSafetyClassification() const {
	return data->SafetyClassification().present();
}
	
DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor::setUnit(const CodedValue & value) {
	data->Unit(ConvertToCDM::convert(value));
	return *this;
}


CodedValue DistributionSampleArrayMetricDescriptor::getUnit() const {
	return ConvertFromCDM::convert(data->Unit());
}
	
DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor::setMetricCategory(const MetricCategory & value) {
	data->MetricCategory(ConvertToCDM::convert(value));
	return *this;
}


MetricCategory DistributionSampleArrayMetricDescriptor::getMetricCategory() const {
	return ConvertFromCDM::convert(data->MetricCategory());
}
	
DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor::setDerivationMethod(const DerivationMethod & value) {
	data->DerivationMethod(ConvertToCDM::convert(value));
	return *this;
}

bool DistributionSampleArrayMetricDescriptor::getDerivationMethod(DerivationMethod & out) const {
	if (data->DerivationMethod().present()) {
		out = ConvertFromCDM::convert(data->DerivationMethod().get());
		return true;
	}
	return false;
}

DerivationMethod DistributionSampleArrayMetricDescriptor::getDerivationMethod() const {
	return ConvertFromCDM::convert(data->DerivationMethod().get());
}
	
bool DistributionSampleArrayMetricDescriptor::hasDerivationMethod() const {
	return data->DerivationMethod().present();
}
	
DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor::setMetricAvailability(const MetricAvailability & value) {
	data->MetricAvailability(ConvertToCDM::convert(value));
	return *this;
}


MetricAvailability DistributionSampleArrayMetricDescriptor::getMetricAvailability() const {
	return ConvertFromCDM::convert(data->MetricAvailability());
}
	
DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor::setMaxMeasurementTime(const xml_schema::Duration & value) {
	data->MaxMeasurementTime(ConvertToCDM::convert(value));
	return *this;
}

bool DistributionSampleArrayMetricDescriptor::getMaxMeasurementTime(xml_schema::Duration & out) const {
	if (data->MaxMeasurementTime().present()) {
		out = ConvertFromCDM::convert(data->MaxMeasurementTime().get());
		return true;
	}
	return false;
}

xml_schema::Duration DistributionSampleArrayMetricDescriptor::getMaxMeasurementTime() const {
	return ConvertFromCDM::convert(data->MaxMeasurementTime().get());
}
	
bool DistributionSampleArrayMetricDescriptor::hasMaxMeasurementTime() const {
	return data->MaxMeasurementTime().present();
}
	
DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor::setMaxDelayTime(const xml_schema::Duration & value) {
	data->MaxDelayTime(ConvertToCDM::convert(value));
	return *this;
}

bool DistributionSampleArrayMetricDescriptor::getMaxDelayTime(xml_schema::Duration & out) const {
	if (data->MaxDelayTime().present()) {
		out = ConvertFromCDM::convert(data->MaxDelayTime().get());
		return true;
	}
	return false;
}

xml_schema::Duration DistributionSampleArrayMetricDescriptor::getMaxDelayTime() const {
	return ConvertFromCDM::convert(data->MaxDelayTime().get());
}
	
bool DistributionSampleArrayMetricDescriptor::hasMaxDelayTime() const {
	return data->MaxDelayTime().present();
}
	
DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor::setDeterminationPeriod(const xml_schema::Duration & value) {
	data->DeterminationPeriod(ConvertToCDM::convert(value));
	return *this;
}

bool DistributionSampleArrayMetricDescriptor::getDeterminationPeriod(xml_schema::Duration & out) const {
	if (data->DeterminationPeriod().present()) {
		out = ConvertFromCDM::convert(data->DeterminationPeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration DistributionSampleArrayMetricDescriptor::getDeterminationPeriod() const {
	return ConvertFromCDM::convert(data->DeterminationPeriod().get());
}
	
bool DistributionSampleArrayMetricDescriptor::hasDeterminationPeriod() const {
	return data->DeterminationPeriod().present();
}
	
DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor::setLifeTimePeriod(const xml_schema::Duration & value) {
	data->LifeTimePeriod(ConvertToCDM::convert(value));
	return *this;
}

bool DistributionSampleArrayMetricDescriptor::getLifeTimePeriod(xml_schema::Duration & out) const {
	if (data->LifeTimePeriod().present()) {
		out = ConvertFromCDM::convert(data->LifeTimePeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration DistributionSampleArrayMetricDescriptor::getLifeTimePeriod() const {
	return ConvertFromCDM::convert(data->LifeTimePeriod().get());
}
	
bool DistributionSampleArrayMetricDescriptor::hasLifeTimePeriod() const {
	return data->LifeTimePeriod().present();
}
	
DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor::setActivationDuration(const xml_schema::Duration & value) {
	data->ActivationDuration(ConvertToCDM::convert(value));
	return *this;
}

bool DistributionSampleArrayMetricDescriptor::getActivationDuration(xml_schema::Duration & out) const {
	if (data->ActivationDuration().present()) {
		out = ConvertFromCDM::convert(data->ActivationDuration().get());
		return true;
	}
	return false;
}

xml_schema::Duration DistributionSampleArrayMetricDescriptor::getActivationDuration() const {
	return ConvertFromCDM::convert(data->ActivationDuration().get());
}
	
bool DistributionSampleArrayMetricDescriptor::hasActivationDuration() const {
	return data->ActivationDuration().present();
}
	
DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor::addBodySite(const CodedValue & value) {
	data->BodySite().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CodedValue> DistributionSampleArrayMetricDescriptor::getBodySiteList() const {
	std::vector<CodedValue> result;
	result.reserve(data->BodySite().size());
	for (const auto & value: data->BodySite()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DistributionSampleArrayMetricDescriptor::clearBodySiteList() {
	data->BodySite().clear();
}

DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor::setDomainUnit(const CodedValue & value) {
	data->DomainUnit(ConvertToCDM::convert(value));
	return *this;
}


CodedValue DistributionSampleArrayMetricDescriptor::getDomainUnit() const {
	return ConvertFromCDM::convert(data->DomainUnit());
}
	
DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor::setDistributionRange(const Range & value) {
	data->DistributionRange(ConvertToCDM::convert(value));
	return *this;
}


Range DistributionSampleArrayMetricDescriptor::getDistributionRange() const {
	return ConvertFromCDM::convert(data->DistributionRange());
}
	
DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor::setResolution(const double & value) {
	data->Resolution(ConvertToCDM::convert(value));
	return *this;
}


double DistributionSampleArrayMetricDescriptor::getResolution() const {
	return ConvertFromCDM::convert(data->Resolution());
}
	
DistributionSampleArrayMetricDescriptor & DistributionSampleArrayMetricDescriptor::addTechnicalRange(const Range & value) {
	data->TechnicalRange().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<Range> DistributionSampleArrayMetricDescriptor::getTechnicalRangeList() const {
	std::vector<Range> result;
	result.reserve(data->TechnicalRange().size());
	for (const auto & value: data->TechnicalRange()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DistributionSampleArrayMetricDescriptor::clearTechnicalRangeList() {
	data->TechnicalRange().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

