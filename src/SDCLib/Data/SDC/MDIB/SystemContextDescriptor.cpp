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

#include "SDCLib/Data/SDC/MDIB/SystemContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/PatientContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/LocationContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/EnsembleContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/OperatorContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/WorkflowContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/MeansContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ProductionSpecification.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


SystemContextDescriptor::SystemContextDescriptor(
		Handle handle
) : data(Defaults::SystemContextDescriptorInit(
		handle
))
{}

SystemContextDescriptor::operator CDM::SystemContextDescriptor() const {
	return *data;
}

SystemContextDescriptor::SystemContextDescriptor(const CDM::SystemContextDescriptor & object)
: data(new CDM::SystemContextDescriptor(object))
{ }

SystemContextDescriptor::SystemContextDescriptor(const SystemContextDescriptor & object)
: data(std::make_shared<CDM::SystemContextDescriptor>(*object.data))
{ }

void SystemContextDescriptor::copyFrom(const SystemContextDescriptor & object) {
	data = std::make_shared<CDM::SystemContextDescriptor>(*object.data);
}

SystemContextDescriptor & SystemContextDescriptor:: operator=(const SystemContextDescriptor& object) {
	copyFrom(object);
	return *this;
}


SystemContextDescriptor & SystemContextDescriptor::setType(const CodedValue & value) {
	data->setType(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContextDescriptor::getType(CodedValue & out) const {
	if (data->getType().present()) {
		out = ConvertFromCDM::convert(data->getType().get());
		return true;
	}
	return false;
}

CodedValue SystemContextDescriptor::getType() const {
	return ConvertFromCDM::convert(data->getType().get());
}

bool SystemContextDescriptor::hasType() const {
	return data->getType().present();
}

SystemContextDescriptor & SystemContextDescriptor::setHandle(const Handle & value) {
	data->setHandle(ConvertToCDM::convert(value));
	return *this;
}


Handle SystemContextDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->getHandle());
}

SystemContextDescriptor & SystemContextDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContextDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter SystemContextDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool SystemContextDescriptor::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

SystemContextDescriptor & SystemContextDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->setSafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContextDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->getSafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->getSafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification SystemContextDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->getSafetyClassification().get());
}

bool SystemContextDescriptor::hasSafetyClassification() const {
	return data->getSafetyClassification().present();
}

SystemContextDescriptor & SystemContextDescriptor::addProductionSpecification(const ProductionSpecification & value) {
	data->getProductionSpecification().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ProductionSpecification> SystemContextDescriptor::getProductionSpecificationList() const {
	std::vector<ProductionSpecification> result;
	result.reserve(data->getProductionSpecification().size());
	for (const auto & value: data->getProductionSpecification()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void SystemContextDescriptor::clearProductionSpecificationList() {
	data->getProductionSpecification().clear();
}

SystemContextDescriptor & SystemContextDescriptor::setPatientContext(const PatientContextDescriptor & value) {
	data->setPatientContext(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContextDescriptor::getPatientContext(PatientContextDescriptor & out) const {
	if (data->getPatientContext().present()) {
		out = ConvertFromCDM::convert(data->getPatientContext().get());
		return true;
	}
	return false;
}

PatientContextDescriptor SystemContextDescriptor::getPatientContext() const {
	return ConvertFromCDM::convert(data->getPatientContext().get());
}

bool SystemContextDescriptor::hasPatientContext() const {
	return data->getPatientContext().present();
}

SystemContextDescriptor & SystemContextDescriptor::setLocationContext(const LocationContextDescriptor & value) {
	data->setLocationContext(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContextDescriptor::getLocationContext(LocationContextDescriptor & out) const {
	if (data->getLocationContext().present()) {
		out = ConvertFromCDM::convert(data->getLocationContext().get());
		return true;
	}
	return false;
}

LocationContextDescriptor SystemContextDescriptor::getLocationContext() const {
	return ConvertFromCDM::convert(data->getLocationContext().get());
}

bool SystemContextDescriptor::hasLocationContext() const {
	return data->getLocationContext().present();
}

SystemContextDescriptor & SystemContextDescriptor::addEnsembleContext(const EnsembleContextDescriptor & value) {
	data->getEnsembleContext().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<EnsembleContextDescriptor> SystemContextDescriptor::getEnsembleContextList() const {
	std::vector<EnsembleContextDescriptor> result;
	result.reserve(data->getEnsembleContext().size());
	for (const auto & value: data->getEnsembleContext()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void SystemContextDescriptor::clearEnsembleContextList() {
	data->getEnsembleContext().clear();
}

SystemContextDescriptor & SystemContextDescriptor::addOperatorContext(const OperatorContextDescriptor & value) {
	data->getOperatorContext().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<OperatorContextDescriptor> SystemContextDescriptor::getOperatorContextList() const {
	std::vector<OperatorContextDescriptor> result;
	result.reserve(data->getOperatorContext().size());
	for (const auto & value: data->getOperatorContext()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void SystemContextDescriptor::clearOperatorContextList() {
	data->getOperatorContext().clear();
}

SystemContextDescriptor & SystemContextDescriptor::addWorkflowContext(const WorkflowContextDescriptor & value) {
	data->getWorkflowContext().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<WorkflowContextDescriptor> SystemContextDescriptor::getWorkflowContextList() const {
	std::vector<WorkflowContextDescriptor> result;
	result.reserve(data->getWorkflowContext().size());
	for (const auto & value: data->getWorkflowContext()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void SystemContextDescriptor::clearWorkflowContextList() {
	data->getWorkflowContext().clear();
}

SystemContextDescriptor & SystemContextDescriptor::addMeansContext(const MeansContextDescriptor & value) {
	data->getMeansContext().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<MeansContextDescriptor> SystemContextDescriptor::getMeansContextList() const {
	std::vector<MeansContextDescriptor> result;
	result.reserve(data->getMeansContext().size());
	for (const auto & value: data->getMeansContext()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void SystemContextDescriptor::clearMeansContextList() {
	data->getMeansContext().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

