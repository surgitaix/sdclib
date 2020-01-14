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
 *  AlertSystemDescriptor.cpp
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

#include "SDCLib/Data/SDC/MDIB/AlertSystemDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/AlertConditionDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/AlertSignalDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


AlertSystemDescriptor::AlertSystemDescriptor(
		Handle handle
) : data(Defaults::AlertSystemDescriptorInit(
		handle
))
{}

AlertSystemDescriptor::operator CDM::AlertSystemDescriptor() const {
	return *data;
}

AlertSystemDescriptor::AlertSystemDescriptor(const CDM::AlertSystemDescriptor & object)
: data(new CDM::AlertSystemDescriptor(object))
{ }

AlertSystemDescriptor::AlertSystemDescriptor(const AlertSystemDescriptor & object)
: data(std::make_shared<CDM::AlertSystemDescriptor>(*object.data))
{ }

void AlertSystemDescriptor::copyFrom(const AlertSystemDescriptor & object) {
	data = std::make_shared<CDM::AlertSystemDescriptor>(*object.data);
}

AlertSystemDescriptor & AlertSystemDescriptor:: operator=(const AlertSystemDescriptor& object) {
	copyFrom(object);
	return *this;
}


AlertSystemDescriptor & AlertSystemDescriptor::setType(const CodedValue & value) {
	data->setType(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSystemDescriptor::getType(CodedValue & out) const {
	if (data->getType().present()) {
		out = ConvertFromCDM::convert(data->getType().get());
		return true;
	}
	return false;
}

CodedValue AlertSystemDescriptor::getType() const {
	return ConvertFromCDM::convert(data->getType().get());
}

bool AlertSystemDescriptor::hasType() const {
	return data->getType().present();
}

AlertSystemDescriptor & AlertSystemDescriptor::setHandle(const Handle & value) {
	data->setHandle(ConvertToCDM::convert(value));
	return *this;
}


Handle AlertSystemDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->getHandle());
}

AlertSystemDescriptor & AlertSystemDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSystemDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter AlertSystemDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool AlertSystemDescriptor::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

AlertSystemDescriptor & AlertSystemDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->setSafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSystemDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->getSafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->getSafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification AlertSystemDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->getSafetyClassification().get());
}

bool AlertSystemDescriptor::hasSafetyClassification() const {
	return data->getSafetyClassification().present();
}

AlertSystemDescriptor & AlertSystemDescriptor::setMaxPhysiologicalParallelAlarms(const unsigned int & value) {
	data->setMaxPhysiologicalParallelAlarms(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSystemDescriptor::getMaxPhysiologicalParallelAlarms(unsigned int & out) const {
	if (data->getMaxPhysiologicalParallelAlarms().present()) {
		out = ConvertFromCDM::convert(data->getMaxPhysiologicalParallelAlarms().get());
		return true;
	}
	return false;
}

unsigned int AlertSystemDescriptor::getMaxPhysiologicalParallelAlarms() const {
	return ConvertFromCDM::convert(data->getMaxPhysiologicalParallelAlarms().get());
}

bool AlertSystemDescriptor::hasMaxPhysiologicalParallelAlarms() const {
	return data->getMaxPhysiologicalParallelAlarms().present();
}

AlertSystemDescriptor & AlertSystemDescriptor::setMaxTechnicalParallelAlarms(const unsigned int & value) {
	data->setMaxTechnicalParallelAlarms(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSystemDescriptor::getMaxTechnicalParallelAlarms(unsigned int & out) const {
	if (data->getMaxTechnicalParallelAlarms().present()) {
		out = ConvertFromCDM::convert(data->getMaxTechnicalParallelAlarms().get());
		return true;
	}
	return false;
}

unsigned int AlertSystemDescriptor::getMaxTechnicalParallelAlarms() const {
	return ConvertFromCDM::convert(data->getMaxTechnicalParallelAlarms().get());
}

bool AlertSystemDescriptor::hasMaxTechnicalParallelAlarms() const {
	return data->getMaxTechnicalParallelAlarms().present();
}

AlertSystemDescriptor & AlertSystemDescriptor::setSelfCheckPeriod(const xml_schema::Duration & value) {
	data->setSelfCheckPeriod(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSystemDescriptor::getSelfCheckPeriod(xml_schema::Duration & out) const {
	if (data->getSelfCheckPeriod().present()) {
		out = ConvertFromCDM::convert(data->getSelfCheckPeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration AlertSystemDescriptor::getSelfCheckPeriod() const {
	return ConvertFromCDM::convert(data->getSelfCheckPeriod().get());
}

bool AlertSystemDescriptor::hasSelfCheckPeriod() const {
	return data->getSelfCheckPeriod().present();
}

AlertSystemDescriptor & AlertSystemDescriptor::addAlertCondition(const AlertConditionDescriptor & value) {
	data->getAlertCondition().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<AlertConditionDescriptor> AlertSystemDescriptor::getAlertConditionList() const {
	std::vector<AlertConditionDescriptor> result;
	result.reserve(data->getAlertCondition().size());
	for (const auto & value: data->getAlertCondition()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void AlertSystemDescriptor::clearAlertConditionList() {
	data->getAlertCondition().clear();
}

AlertSystemDescriptor & AlertSystemDescriptor::addAlertSignal(const AlertSignalDescriptor & value) {
	data->getAlertSignal().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<AlertSignalDescriptor> AlertSystemDescriptor::getAlertSignalList() const {
	std::vector<AlertSignalDescriptor> result;
	result.reserve(data->getAlertSignal().size());
	for (const auto & value: data->getAlertSignal()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void AlertSystemDescriptor::clearAlertSignalList() {
	data->getAlertSignal().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

