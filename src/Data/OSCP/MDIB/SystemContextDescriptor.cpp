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
 *  SystemContextDescriptor.cpp
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

#include "OSCLib/Data/OSCP/MDIB/SystemContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/PatientContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LocationContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/EnsembleContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/OperatorContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/WorkflowContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/MeansContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

namespace OSCLib {
namespace Data {
namespace SDC {


SystemContextDescriptor::SystemContextDescriptor(
		Handle handle
) : data(Defaults::SystemContextDescriptorInit(
		handle
)) {}

SystemContextDescriptor::operator CDM::SystemContextDescriptor() const {
	return *data;
}

SystemContextDescriptor::SystemContextDescriptor(const CDM::SystemContextDescriptor & object) : data(new CDM::SystemContextDescriptor(object)) {

}

SystemContextDescriptor::SystemContextDescriptor(const SystemContextDescriptor & object) : data(new CDM::SystemContextDescriptor(*object.data)) {

}

SystemContextDescriptor::~SystemContextDescriptor() {

}

void SystemContextDescriptor::copyFrom(const SystemContextDescriptor & object) {
	data = std::shared_ptr<CDM::SystemContextDescriptor>( new CDM::SystemContextDescriptor(*object.data));
}

SystemContextDescriptor & SystemContextDescriptor:: operator=(const SystemContextDescriptor & object) {
	copyFrom(object);
	return *this;
}


SystemContextDescriptor & SystemContextDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContextDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue SystemContextDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool SystemContextDescriptor::hasType() const {
	return data->Type().present();
}
	
SystemContextDescriptor & SystemContextDescriptor::setHandle(const Handle & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


Handle SystemContextDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
SystemContextDescriptor & SystemContextDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContextDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter SystemContextDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool SystemContextDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
SystemContextDescriptor & SystemContextDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->SafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContextDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->SafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->SafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification SystemContextDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->SafetyClassification().get());
}
	
bool SystemContextDescriptor::hasSafetyClassification() const {
	return data->SafetyClassification().present();
}
	
SystemContextDescriptor & SystemContextDescriptor::setPatientContext(const PatientContextDescriptor & value) {
	data->PatientContext(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContextDescriptor::getPatientContext(PatientContextDescriptor & out) const {
	if (data->PatientContext().present()) {
		out = ConvertFromCDM::convert(data->PatientContext().get());
		return true;
	}
	return false;
}

PatientContextDescriptor SystemContextDescriptor::getPatientContext() const {
	return ConvertFromCDM::convert(data->PatientContext().get());
}
	
bool SystemContextDescriptor::hasPatientContext() const {
	return data->PatientContext().present();
}
	
SystemContextDescriptor & SystemContextDescriptor::setLocationContext(const LocationContextDescriptor & value) {
	data->LocationContext(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContextDescriptor::getLocationContext(LocationContextDescriptor & out) const {
	if (data->LocationContext().present()) {
		out = ConvertFromCDM::convert(data->LocationContext().get());
		return true;
	}
	return false;
}

LocationContextDescriptor SystemContextDescriptor::getLocationContext() const {
	return ConvertFromCDM::convert(data->LocationContext().get());
}
	
bool SystemContextDescriptor::hasLocationContext() const {
	return data->LocationContext().present();
}
	
SystemContextDescriptor & SystemContextDescriptor::addEnsembleContext(const EnsembleContextDescriptor & value) {
	data->EnsembleContext().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<EnsembleContextDescriptor> SystemContextDescriptor::getEnsembleContextList() const {
	std::vector<EnsembleContextDescriptor> result;
	result.reserve(data->EnsembleContext().size());
	for (const auto & value: data->EnsembleContext()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void SystemContextDescriptor::clearEnsembleContextList() {
	data->EnsembleContext().clear();
}

SystemContextDescriptor & SystemContextDescriptor::addOperatorContext(const OperatorContextDescriptor & value) {
	data->OperatorContext().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<OperatorContextDescriptor> SystemContextDescriptor::getOperatorContextList() const {
	std::vector<OperatorContextDescriptor> result;
	result.reserve(data->OperatorContext().size());
	for (const auto & value: data->OperatorContext()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void SystemContextDescriptor::clearOperatorContextList() {
	data->OperatorContext().clear();
}

SystemContextDescriptor & SystemContextDescriptor::addWorkflowContext(const WorkflowContextDescriptor & value) {
	data->WorkflowContext().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<WorkflowContextDescriptor> SystemContextDescriptor::getWorkflowContextList() const {
	std::vector<WorkflowContextDescriptor> result;
	result.reserve(data->WorkflowContext().size());
	for (const auto & value: data->WorkflowContext()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void SystemContextDescriptor::clearWorkflowContextList() {
	data->WorkflowContext().clear();
}

SystemContextDescriptor & SystemContextDescriptor::addMeansContext(const MeansContextDescriptor & value) {
	data->MeansContext().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<MeansContextDescriptor> SystemContextDescriptor::getMeansContextList() const {
	std::vector<MeansContextDescriptor> result;
	result.reserve(data->MeansContext().size());
	for (const auto & value: data->MeansContext()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void SystemContextDescriptor::clearMeansContextList() {
	data->MeansContext().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace OSCLib */

