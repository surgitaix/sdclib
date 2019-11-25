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
 *  AlertSystemState.cpp
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

#include "SDCLib/Data/SDC/MDIB/AlertSystemState.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/SystemSignalActivation.h"

namespace SDCLib {
namespace Data {
namespace SDC {


AlertSystemState::AlertSystemState(
		HandleRef descriptorhandle
		,
		AlertActivation activationstate
) : data(Defaults::AlertSystemStateInit(
		descriptorhandle
		,
		activationstate
)) {}

AlertSystemState::operator CDM::AlertSystemState() const {
	return *data;
}

AlertSystemState::AlertSystemState(const CDM::AlertSystemState & object) : data(new CDM::AlertSystemState(object)) {

}

AlertSystemState::AlertSystemState(const AlertSystemState & object) : data(new CDM::AlertSystemState(*object.data)) {

}

AlertSystemState::~AlertSystemState() {

}

void AlertSystemState::copyFrom(const AlertSystemState & object) {
	data = std::shared_ptr<CDM::AlertSystemState>( new CDM::AlertSystemState(*object.data));
}

AlertSystemState & AlertSystemState:: operator=(const AlertSystemState & object) {
	copyFrom(object);
	return *this;
}


AlertSystemState & AlertSystemState::setStateVersion(const VersionCounter & value) {
	data->setStateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSystemState::getStateVersion(VersionCounter & out) const {
	if (data->getStateVersion().present()) {
		out = ConvertFromCDM::convert(data->getStateVersion().get());
		return true;
	}
	return false;
}

VersionCounter AlertSystemState::getStateVersion() const {
	return ConvertFromCDM::convert(data->getStateVersion().get());
}

bool AlertSystemState::hasStateVersion() const {
	return data->getStateVersion().present();
}

AlertSystemState & AlertSystemState::setDescriptorHandle(const HandleRef & value) {
	data->setDescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef AlertSystemState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->getDescriptorHandle());
}

AlertSystemState & AlertSystemState::setDescriptorVersion(const ReferencedVersion & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSystemState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion AlertSystemState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool AlertSystemState::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

AlertSystemState & AlertSystemState::setActivationState(const AlertActivation & value) {
	data->setActivationState(ConvertToCDM::convert(value));
	return *this;
}


AlertActivation AlertSystemState::getActivationState() const {
	return ConvertFromCDM::convert(data->getActivationState());
}

AlertSystemState & AlertSystemState::setLastSelfCheck(const Timestamp & value) {
	data->setLastSelfCheck(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSystemState::getLastSelfCheck(Timestamp & out) const {
	if (data->getLastSelfCheck().present()) {
		out = ConvertFromCDM::convert(data->getLastSelfCheck().get());
		return true;
	}
	return false;
}

Timestamp AlertSystemState::getLastSelfCheck() const {
	return ConvertFromCDM::convert(data->getLastSelfCheck().get());
}

bool AlertSystemState::hasLastSelfCheck() const {
	return data->getLastSelfCheck().present();
}

AlertSystemState & AlertSystemState::setSelfCheckCount(const long long & value) {
	data->setSelfCheckCount(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSystemState::getSelfCheckCount(long long & out) const {
	if (data->getSelfCheckCount().present()) {
		out = ConvertFromCDM::convert(data->getSelfCheckCount().get());
		return true;
	}
	return false;
}

long long AlertSystemState::getSelfCheckCount() const {
	return ConvertFromCDM::convert(data->getSelfCheckCount().get());
}

bool AlertSystemState::hasSelfCheckCount() const {
	return data->getSelfCheckCount().present();
}

AlertSystemState & AlertSystemState::setPresentPhysiologicalAlarmConditions(const AlertConditionReference & value) {
	data->setPresentPhysiologicalAlarmConditions(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSystemState::getPresentPhysiologicalAlarmConditions(AlertConditionReference & out) const {
	if (data->getPresentPhysiologicalAlarmConditions().present()) {
		out = ConvertFromCDM::convert(data->getPresentPhysiologicalAlarmConditions().get());
		return true;
	}
	return false;
}

AlertConditionReference AlertSystemState::getPresentPhysiologicalAlarmConditions() const {
	return ConvertFromCDM::convert(data->getPresentPhysiologicalAlarmConditions().get());
}

bool AlertSystemState::hasPresentPhysiologicalAlarmConditions() const {
	return data->getPresentPhysiologicalAlarmConditions().present();
}

AlertSystemState & AlertSystemState::setPresentTechnicalAlarmConditions(const AlertConditionReference & value) {
	data->setPresentTechnicalAlarmConditions(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSystemState::getPresentTechnicalAlarmConditions(AlertConditionReference & out) const {
	if (data->getPresentTechnicalAlarmConditions().present()) {
		out = ConvertFromCDM::convert(data->getPresentTechnicalAlarmConditions().get());
		return true;
	}
	return false;
}

AlertConditionReference AlertSystemState::getPresentTechnicalAlarmConditions() const {
	return ConvertFromCDM::convert(data->getPresentTechnicalAlarmConditions().get());
}

bool AlertSystemState::hasPresentTechnicalAlarmConditions() const {
	return data->getPresentTechnicalAlarmConditions().present();
}

AlertSystemState & AlertSystemState::addSystemSignalActivation(const SystemSignalActivation & value) {
	data->getSystemSignalActivation().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<SystemSignalActivation> AlertSystemState::getSystemSignalActivationList() const {
	std::vector<SystemSignalActivation> result;
	result.reserve(data->getSystemSignalActivation().size());
	for (const auto & value: data->getSystemSignalActivation()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void AlertSystemState::clearSystemSignalActivationList() {
	data->getSystemSignalActivation().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

