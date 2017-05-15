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
 *  Author: besting, roehser
 */
 
/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 * 
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "OSCLib/Data/OSCP/MDIB/AlertSystemDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/AlertConditionDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSignalDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/Duration.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

AlertSystemDescriptor::AlertSystemDescriptor() : data(Defaults::AlertSystemDescriptor()) {
}

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
	*data = *object.data;
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
	
AlertSystemDescriptor & AlertSystemDescriptor::setHandle(const std::string & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


std::string AlertSystemDescriptor::getHandle() const {
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
	
AlertSystemDescriptor & AlertSystemDescriptor::setSafetyClassification(const std::string & value) {
	data->SafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSystemDescriptor::getSafetyClassification(std::string & out) const {
	if (data->SafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->SafetyClassification().get());
		return true;
	}
	return false;
}

std::string AlertSystemDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->SafetyClassification().get());
}
	
bool AlertSystemDescriptor::hasSafetyClassification() const {
	return data->SafetyClassification().present();
}
	
AlertSystemDescriptor & AlertSystemDescriptor::setMaxPhysiologicalAlarmListEntries(const int & value) {
	data->MaxPhysiologicalAlarmListEntries(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSystemDescriptor::getMaxPhysiologicalAlarmListEntries(int & out) const {
	if (data->MaxPhysiologicalAlarmListEntries().present()) {
		out = ConvertFromCDM::convert(data->MaxPhysiologicalAlarmListEntries().get());
		return true;
	}
	return false;
}

int AlertSystemDescriptor::getMaxPhysiologicalAlarmListEntries() const {
	return ConvertFromCDM::convert(data->MaxPhysiologicalAlarmListEntries().get());
}
	
bool AlertSystemDescriptor::hasMaxPhysiologicalAlarmListEntries() const {
	return data->MaxPhysiologicalAlarmListEntries().present();
}
	
AlertSystemDescriptor & AlertSystemDescriptor::setMaxTechnicalAlarmListEntries(const int & value) {
	data->MaxTechnicalAlarmListEntries(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSystemDescriptor::getMaxTechnicalAlarmListEntries(int & out) const {
	if (data->MaxTechnicalAlarmListEntries().present()) {
		out = ConvertFromCDM::convert(data->MaxTechnicalAlarmListEntries().get());
		return true;
	}
	return false;
}

int AlertSystemDescriptor::getMaxTechnicalAlarmListEntries() const {
	return ConvertFromCDM::convert(data->MaxTechnicalAlarmListEntries().get());
}
	
bool AlertSystemDescriptor::hasMaxTechnicalAlarmListEntries() const {
	return data->MaxTechnicalAlarmListEntries().present();
}
	
AlertSystemDescriptor & AlertSystemDescriptor::setSelfCheckPeriod(const Duration & value) {
	data->SelfCheckPeriod(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSystemDescriptor::getSelfCheckPeriod(Duration & out) const {
	if (data->SelfCheckPeriod().present()) {
		out = ConvertFromCDM::convert(data->SelfCheckPeriod().get());
		return true;
	}
	return false;
}

Duration AlertSystemDescriptor::getSelfCheckPeriod() const {
	return ConvertFromCDM::convert(data->SelfCheckPeriod().get());
}
	
bool AlertSystemDescriptor::hasSelfCheckPeriod() const {
	return data->SelfCheckPeriod().present();
}
	
AlertSystemDescriptor & AlertSystemDescriptor::addAlertSignal(const AlertSignalDescriptor & value) {
	data->AlertSignal().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<AlertSignalDescriptor> AlertSystemDescriptor::getAlertSignals() const {
	std::vector<AlertSignalDescriptor> result;
	result.reserve(data->AlertSignal().size());
	for (const auto & value: data->AlertSignal()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void AlertSystemDescriptor::clearAlertSignals() {
	data->AlertSignal().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

