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
 *  AbstractMetricDescriptor.cpp
 *
 *  @Copyright (C) 2015, SurgiTAIX AG
 *  Author: besting, roehser
 */
 
/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 * 
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "OSCLib/Data/OSCP/MDIB/AbstractMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/Relation.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

AbstractMetricDescriptor::AbstractMetricDescriptor() : data(Defaults::AbstractMetricDescriptor()) {
}

AbstractMetricDescriptor::operator CDM::AbstractMetricDescriptor() const {
	return *data;
}

AbstractMetricDescriptor::AbstractMetricDescriptor(const CDM::AbstractMetricDescriptor & object) : data(new CDM::AbstractMetricDescriptor(object)) {

}

// IMPORTANT: call copy constructor of base class!!!
AbstractMetricDescriptor::AbstractMetricDescriptor(const AbstractMetricDescriptor & object) : AbstractDescriptor(object), data(new CDM::AbstractMetricDescriptor(*object.data)) {

}

AbstractMetricDescriptor::~AbstractMetricDescriptor() {

}

void AbstractMetricDescriptor::copyFrom(const AbstractMetricDescriptor & object) {
	*data = *object.data;
}

AbstractMetricDescriptor & AbstractMetricDescriptor:: operator=(const AbstractMetricDescriptor & object) {
	copyFrom(object);
	return *this;
}
	
AbstractMetricDescriptor & AbstractMetricDescriptor::setUnit(const CodedValue & value) {
	data->Unit(ConvertToCDM::convert(value));
	return *this;
}


CodedValue AbstractMetricDescriptor::getUnit() const {
	return ConvertFromCDM::convert(data->Unit());
}
	
AbstractMetricDescriptor & AbstractMetricDescriptor::setMetricCategory(const MetricCategory & value) {
	data->MetricCategory(ConvertToCDM::convert(value));
	return *this;
}


MetricCategory AbstractMetricDescriptor::getMetricCategory() const {
	return ConvertFromCDM::convert(data->MetricCategory());
}
	
AbstractMetricDescriptor & AbstractMetricDescriptor::setDerivationMethod(const DerivationMethod & value) {
	data->DerivationMethod(ConvertToCDM::convert(value));
	return *this;
}

bool AbstractMetricDescriptor::getDerivationMethod(DerivationMethod & out) const {
	if (data->DerivationMethod().present()) {
		out = ConvertFromCDM::convert(data->DerivationMethod().get());
		return true;
	}
	return false;
}

DerivationMethod AbstractMetricDescriptor::getDerivationMethod() const {
	return ConvertFromCDM::convert(data->DerivationMethod().get());
}
	
bool AbstractMetricDescriptor::hasDerivationMethod() const {
	return data->DerivationMethod().present();
}
	
AbstractMetricDescriptor & AbstractMetricDescriptor::setMetricAvailability(const MetricAvailability & value) {
	data->MetricAvailability(ConvertToCDM::convert(value));
	return *this;
}


MetricAvailability AbstractMetricDescriptor::getMetricAvailability() const {
	return ConvertFromCDM::convert(data->MetricAvailability());
}
	
AbstractMetricDescriptor & AbstractMetricDescriptor::setMaxMeasurementTime(const xml_schema::Duration & value) {
	data->MaxMeasurementTime(ConvertToCDM::convert(value));
	return *this;
}

bool AbstractMetricDescriptor::getMaxMeasurementTime(xml_schema::Duration & out) const {
	if (data->MaxMeasurementTime().present()) {
		out = ConvertFromCDM::convert(data->MaxMeasurementTime().get());
		return true;
	}
	return false;
}

xml_schema::Duration AbstractMetricDescriptor::getMaxMeasurementTime() const {
	return ConvertFromCDM::convert(data->MaxMeasurementTime().get());
}
	
bool AbstractMetricDescriptor::hasMaxMeasurementTime() const {
	return data->MaxMeasurementTime().present();
}
	
AbstractMetricDescriptor & AbstractMetricDescriptor::setMaxDelayTime(const xml_schema::Duration & value) {
	data->MaxDelayTime(ConvertToCDM::convert(value));
	return *this;
}

bool AbstractMetricDescriptor::getMaxDelayTime(xml_schema::Duration & out) const {
	if (data->MaxDelayTime().present()) {
		out = ConvertFromCDM::convert(data->MaxDelayTime().get());
		return true;
	}
	return false;
}

xml_schema::Duration AbstractMetricDescriptor::getMaxDelayTime() const {
	return ConvertFromCDM::convert(data->MaxDelayTime().get());
}
	
bool AbstractMetricDescriptor::hasMaxDelayTime() const {
	return data->MaxDelayTime().present();
}
	
AbstractMetricDescriptor & AbstractMetricDescriptor::setDeterminationPeriod(const xml_schema::Duration & value) {
	data->DeterminationPeriod(ConvertToCDM::convert(value));
	return *this;
}

bool AbstractMetricDescriptor::getDeterminationPeriod(xml_schema::Duration & out) const {
	if (data->DeterminationPeriod().present()) {
		out = ConvertFromCDM::convert(data->DeterminationPeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration AbstractMetricDescriptor::getDeterminationPeriod() const {
	return ConvertFromCDM::convert(data->DeterminationPeriod().get());
}
	
bool AbstractMetricDescriptor::hasDeterminationPeriod() const {
	return data->DeterminationPeriod().present();
}
	
AbstractMetricDescriptor & AbstractMetricDescriptor::setLifeTimePeriod(const xml_schema::Duration & value) {
	data->LifeTimePeriod(ConvertToCDM::convert(value));
	return *this;
}

bool AbstractMetricDescriptor::getLifeTimePeriod(xml_schema::Duration & out) const {
	if (data->LifeTimePeriod().present()) {
		out = ConvertFromCDM::convert(data->LifeTimePeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration AbstractMetricDescriptor::getLifeTimePeriod() const {
	return ConvertFromCDM::convert(data->LifeTimePeriod().get());
}
	
bool AbstractMetricDescriptor::hasLifeTimePeriod() const {
	return data->LifeTimePeriod().present();
}
	
AbstractMetricDescriptor & AbstractMetricDescriptor::setActivationDuration(const xml_schema::Duration & value) {
	data->ActivationDuration(ConvertToCDM::convert(value));
	return *this;
}

bool AbstractMetricDescriptor::getActivationDuration(xml_schema::Duration & out) const {
	if (data->ActivationDuration().present()) {
		out = ConvertFromCDM::convert(data->ActivationDuration().get());
		return true;
	}
	return false;
}

xml_schema::Duration AbstractMetricDescriptor::getActivationDuration() const {
	return ConvertFromCDM::convert(data->ActivationDuration().get());
}
	
bool AbstractMetricDescriptor::hasActivationDuration() const {
	return data->ActivationDuration().present();
}
	
AbstractMetricDescriptor & AbstractMetricDescriptor::addBodySite(const CodedValue & value) {
	data->BodySite().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CodedValue> AbstractMetricDescriptor::getBodySiteList() const {
	std::vector<CodedValue> result;
	result.reserve(data->BodySite().size());
	for (const auto & value: data->BodySite()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void AbstractMetricDescriptor::clearBodySiteList() {
	data->BodySite().clear();
}

AbstractMetricDescriptor & AbstractMetricDescriptor::addRelation(const Relation & value) {
	data->Relation().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<Relation> AbstractMetricDescriptor::getRelationList() const {
	std::vector<Relation> result;
	result.reserve(data->Relation().size());
	for (const auto & value: data->Relation()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void AbstractMetricDescriptor::clearRelationList() {
	data->Relation().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

