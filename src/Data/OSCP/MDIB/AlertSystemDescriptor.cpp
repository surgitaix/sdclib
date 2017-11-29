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

#include "OSCLib/Data/OSCP/MDIB/AlertSystemDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/AlertConditionDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSignalDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

namespace OSCLib {
namespace Data {
namespace OSCP {


AlertSystemDescriptor::AlertSystemDescriptor(
		Handle handle
) : data(Defaults::AlertSystemDescriptorInit(
		handle
)) {}

AlertSystemDescriptor::operator CDM::AlertSystemDescriptor() const {
	return *data;
}

AlertSystemDescriptor::AlertSystemDescriptor(const CDM::AlertSystemDescriptor & object) : data(new CDM::AlertSystemDescriptor(object)) {

}

AlertSystemDescriptor::AlertSystemDescriptor(const AlertSystemDescriptor & object) : data(new CDM::AlertSystemDescriptor(*object.data)) {

}

AlertSystemDescriptor::~AlertSystemDescriptor() {

}

void AlertSystemDescriptor::copyFrom(const AlertSystemDescriptor & object) {
	data = std::shared_ptr<CDM::AlertSystemDescriptor>( new CDM::AlertSystemDescriptor(*object.data));
}

AlertSystemDescriptor & AlertSystemDescriptor:: operator=(const AlertSystemDescriptor & object) {
	copyFrom(object);
	return *this;
}


AlertSystemDescriptor & AlertSystemDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSystemDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue AlertSystemDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool AlertSystemDescriptor::hasType() const {
	return data->Type().present();
}
	
AlertSystemDescriptor & AlertSystemDescriptor::setHandle(const Handle & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


Handle AlertSystemDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
AlertSystemDescriptor & AlertSystemDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSystemDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter AlertSystemDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool AlertSystemDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
AlertSystemDescriptor & AlertSystemDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->SafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSystemDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->SafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->SafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification AlertSystemDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->SafetyClassification().get());
}
	
bool AlertSystemDescriptor::hasSafetyClassification() const {
	return data->SafetyClassification().present();
}
	
AlertSystemDescriptor & AlertSystemDescriptor::setMaxPhysiologicalParallelAlarms(const unsigned int & value) {
	data->MaxPhysiologicalParallelAlarms(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSystemDescriptor::getMaxPhysiologicalParallelAlarms(unsigned int & out) const {
	if (data->MaxPhysiologicalParallelAlarms().present()) {
		out = ConvertFromCDM::convert(data->MaxPhysiologicalParallelAlarms().get());
		return true;
	}
	return false;
}

unsigned int AlertSystemDescriptor::getMaxPhysiologicalParallelAlarms() const {
	return ConvertFromCDM::convert(data->MaxPhysiologicalParallelAlarms().get());
}
	
bool AlertSystemDescriptor::hasMaxPhysiologicalParallelAlarms() const {
	return data->MaxPhysiologicalParallelAlarms().present();
}
	
AlertSystemDescriptor & AlertSystemDescriptor::setMaxTechnicalParallelAlarms(const unsigned int & value) {
	data->MaxTechnicalParallelAlarms(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSystemDescriptor::getMaxTechnicalParallelAlarms(unsigned int & out) const {
	if (data->MaxTechnicalParallelAlarms().present()) {
		out = ConvertFromCDM::convert(data->MaxTechnicalParallelAlarms().get());
		return true;
	}
	return false;
}

unsigned int AlertSystemDescriptor::getMaxTechnicalParallelAlarms() const {
	return ConvertFromCDM::convert(data->MaxTechnicalParallelAlarms().get());
}
	
bool AlertSystemDescriptor::hasMaxTechnicalParallelAlarms() const {
	return data->MaxTechnicalParallelAlarms().present();
}
	
AlertSystemDescriptor & AlertSystemDescriptor::setSelfCheckPeriod(const xml_schema::Duration & value) {
	data->SelfCheckPeriod(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSystemDescriptor::getSelfCheckPeriod(xml_schema::Duration & out) const {
	if (data->SelfCheckPeriod().present()) {
		out = ConvertFromCDM::convert(data->SelfCheckPeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration AlertSystemDescriptor::getSelfCheckPeriod() const {
	return ConvertFromCDM::convert(data->SelfCheckPeriod().get());
}
	
bool AlertSystemDescriptor::hasSelfCheckPeriod() const {
	return data->SelfCheckPeriod().present();
}
	
AlertSystemDescriptor & AlertSystemDescriptor::addAlertCondition(const AlertConditionDescriptor & value) {
	data->AlertCondition().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<AlertConditionDescriptor> AlertSystemDescriptor::getAlertConditionList() const {
	std::vector<AlertConditionDescriptor> result;
	result.reserve(data->AlertCondition().size());
	for (const auto & value: data->AlertCondition()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void AlertSystemDescriptor::clearAlertConditionList() {
	data->AlertCondition().clear();
}

AlertSystemDescriptor & AlertSystemDescriptor::addAlertSignal(const AlertSignalDescriptor & value) {
	data->AlertSignal().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<AlertSignalDescriptor> AlertSystemDescriptor::getAlertSignalList() const {
	std::vector<AlertSignalDescriptor> result;
	result.reserve(data->AlertSignal().size());
	for (const auto & value: data->AlertSignal()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void AlertSystemDescriptor::clearAlertSignalList() {
	data->AlertSignal().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

