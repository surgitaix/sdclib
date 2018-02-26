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

#include "OSCLib/Data/SDC/MDIB/NumericMetricDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/SDC/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/SDC/MDIB/Range.h"
#include "OSCLib/Data/SDC/MDIB/CodedValue.h"
#include "OSCLib/Data/SDC/MDIB/Relation.h"
#include "OSCLib/Data/SDC/MDIB/CodedValue.h"

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
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue NumericMetricDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool NumericMetricDescriptor::hasType() const {
	return data->Type().present();
}
	
NumericMetricDescriptor & NumericMetricDescriptor::setHandle(const Handle & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


Handle NumericMetricDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
NumericMetricDescriptor & NumericMetricDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter NumericMetricDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool NumericMetricDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
NumericMetricDescriptor & NumericMetricDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->SafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->SafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->SafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification NumericMetricDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->SafetyClassification().get());
}
	
bool NumericMetricDescriptor::hasSafetyClassification() const {
	return data->SafetyClassification().present();
}
	
NumericMetricDescriptor & NumericMetricDescriptor::setUnit(const CodedValue & value) {
	data->Unit(ConvertToCDM::convert(value));
	return *this;
}


CodedValue NumericMetricDescriptor::getUnit() const {
	return ConvertFromCDM::convert(data->Unit());
}
	
NumericMetricDescriptor & NumericMetricDescriptor::setMetricCategory(const MetricCategory & value) {
	data->MetricCategory(ConvertToCDM::convert(value));
	return *this;
}


MetricCategory NumericMetricDescriptor::getMetricCategory() const {
	return ConvertFromCDM::convert(data->MetricCategory());
}
	
NumericMetricDescriptor & NumericMetricDescriptor::setDerivationMethod(const DerivationMethod & value) {
	data->DerivationMethod(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricDescriptor::getDerivationMethod(DerivationMethod & out) const {
	if (data->DerivationMethod().present()) {
		out = ConvertFromCDM::convert(data->DerivationMethod().get());
		return true;
	}
	return false;
}

DerivationMethod NumericMetricDescriptor::getDerivationMethod() const {
	return ConvertFromCDM::convert(data->DerivationMethod().get());
}
	
bool NumericMetricDescriptor::hasDerivationMethod() const {
	return data->DerivationMethod().present();
}
	
NumericMetricDescriptor & NumericMetricDescriptor::setMetricAvailability(const MetricAvailability & value) {
	data->MetricAvailability(ConvertToCDM::convert(value));
	return *this;
}


MetricAvailability NumericMetricDescriptor::getMetricAvailability() const {
	return ConvertFromCDM::convert(data->MetricAvailability());
}
	
NumericMetricDescriptor & NumericMetricDescriptor::setMaxMeasurementTime(const xml_schema::Duration & value) {
	data->MaxMeasurementTime(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricDescriptor::getMaxMeasurementTime(xml_schema::Duration & out) const {
	if (data->MaxMeasurementTime().present()) {
		out = ConvertFromCDM::convert(data->MaxMeasurementTime().get());
		return true;
	}
	return false;
}

xml_schema::Duration NumericMetricDescriptor::getMaxMeasurementTime() const {
	return ConvertFromCDM::convert(data->MaxMeasurementTime().get());
}
	
bool NumericMetricDescriptor::hasMaxMeasurementTime() const {
	return data->MaxMeasurementTime().present();
}
	
NumericMetricDescriptor & NumericMetricDescriptor::setMaxDelayTime(const xml_schema::Duration & value) {
	data->MaxDelayTime(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricDescriptor::getMaxDelayTime(xml_schema::Duration & out) const {
	if (data->MaxDelayTime().present()) {
		out = ConvertFromCDM::convert(data->MaxDelayTime().get());
		return true;
	}
	return false;
}

xml_schema::Duration NumericMetricDescriptor::getMaxDelayTime() const {
	return ConvertFromCDM::convert(data->MaxDelayTime().get());
}
	
bool NumericMetricDescriptor::hasMaxDelayTime() const {
	return data->MaxDelayTime().present();
}
	
NumericMetricDescriptor & NumericMetricDescriptor::setDeterminationPeriod(const xml_schema::Duration & value) {
	data->DeterminationPeriod(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricDescriptor::getDeterminationPeriod(xml_schema::Duration & out) const {
	if (data->DeterminationPeriod().present()) {
		out = ConvertFromCDM::convert(data->DeterminationPeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration NumericMetricDescriptor::getDeterminationPeriod() const {
	return ConvertFromCDM::convert(data->DeterminationPeriod().get());
}
	
bool NumericMetricDescriptor::hasDeterminationPeriod() const {
	return data->DeterminationPeriod().present();
}
	
NumericMetricDescriptor & NumericMetricDescriptor::setLifeTimePeriod(const xml_schema::Duration & value) {
	data->LifeTimePeriod(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricDescriptor::getLifeTimePeriod(xml_schema::Duration & out) const {
	if (data->LifeTimePeriod().present()) {
		out = ConvertFromCDM::convert(data->LifeTimePeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration NumericMetricDescriptor::getLifeTimePeriod() const {
	return ConvertFromCDM::convert(data->LifeTimePeriod().get());
}
	
bool NumericMetricDescriptor::hasLifeTimePeriod() const {
	return data->LifeTimePeriod().present();
}
	
NumericMetricDescriptor & NumericMetricDescriptor::setActivationDuration(const xml_schema::Duration & value) {
	data->ActivationDuration(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricDescriptor::getActivationDuration(xml_schema::Duration & out) const {
	if (data->ActivationDuration().present()) {
		out = ConvertFromCDM::convert(data->ActivationDuration().get());
		return true;
	}
	return false;
}

xml_schema::Duration NumericMetricDescriptor::getActivationDuration() const {
	return ConvertFromCDM::convert(data->ActivationDuration().get());
}
	
bool NumericMetricDescriptor::hasActivationDuration() const {
	return data->ActivationDuration().present();
}
	
NumericMetricDescriptor & NumericMetricDescriptor::addBodySite(const CodedValue & value) {
	data->BodySite().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CodedValue> NumericMetricDescriptor::getBodySiteList() const {
	std::vector<CodedValue> result;
	result.reserve(data->BodySite().size());
	for (const auto & value: data->BodySite()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void NumericMetricDescriptor::clearBodySiteList() {
	data->BodySite().clear();
}

NumericMetricDescriptor & NumericMetricDescriptor::addRelation(const Relation & value) {
	data->Relation().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<Relation> NumericMetricDescriptor::getRelationList() const {
	std::vector<Relation> result;
	result.reserve(data->Relation().size());
	for (const auto & value: data->Relation()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void NumericMetricDescriptor::clearRelationList() {
	data->Relation().clear();
}

NumericMetricDescriptor & NumericMetricDescriptor::setResolution(const double & value) {
	data->Resolution(ConvertToCDM::convert(value));
	return *this;
}


double NumericMetricDescriptor::getResolution() const {
	return ConvertFromCDM::convert(data->Resolution());
}
	
NumericMetricDescriptor & NumericMetricDescriptor::setAveragingPeriod(const xml_schema::Duration & value) {
	data->AveragingPeriod(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricDescriptor::getAveragingPeriod(xml_schema::Duration & out) const {
	if (data->AveragingPeriod().present()) {
		out = ConvertFromCDM::convert(data->AveragingPeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration NumericMetricDescriptor::getAveragingPeriod() const {
	return ConvertFromCDM::convert(data->AveragingPeriod().get());
}
	
bool NumericMetricDescriptor::hasAveragingPeriod() const {
	return data->AveragingPeriod().present();
}
	
NumericMetricDescriptor & NumericMetricDescriptor::addTechnicalRange(const Range & value) {
	data->TechnicalRange().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<Range> NumericMetricDescriptor::getTechnicalRangeList() const {
	std::vector<Range> result;
	result.reserve(data->TechnicalRange().size());
	for (const auto & value: data->TechnicalRange()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void NumericMetricDescriptor::clearTechnicalRangeList() {
	data->TechnicalRange().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

