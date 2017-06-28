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
 *  Author: besting, roehser
 */
 
/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 * 
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "OSCLib/Data/OSCP/MDIB/AlertSystemState.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/SystemSignalActivation.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

AlertSystemState::AlertSystemState() : data(Defaults::AlertSystemState()) {
}

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
	*data = *object.data;
}

AlertSystemState & AlertSystemState:: operator=(const AlertSystemState & object) {
	copyFrom(object);
	return *this;
}


AlertSystemState & AlertSystemState::setStateVersion(const VersionCounter & value) {
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}


VersionCounter AlertSystemState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion());
}
	
AlertSystemState & AlertSystemState::setDescriptorHandle(const HandleRef & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef AlertSystemState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
}
	
AlertSystemState & AlertSystemState::setDescriptorVersion(const ReferencedVersion & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}


ReferencedVersion AlertSystemState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion());
}
	
AlertSystemState & AlertSystemState::setActivationState(const AlertActivation & value) {
	data->ActivationState(ConvertToCDM::convert(value));
	return *this;
}


AlertActivation AlertSystemState::getActivationState() const {
	return ConvertFromCDM::convert(data->ActivationState());
}
	
AlertSystemState & AlertSystemState::setLastSelfCheck(const Timestamp & value) {
	data->LastSelfCheck(ConvertToCDM::convert(value));
	return *this;
}


Timestamp AlertSystemState::getLastSelfCheck() const {
	return ConvertFromCDM::convert(data->LastSelfCheck());
}
	
AlertSystemState & AlertSystemState::setSelfCheckCount(const long & value) {
	data->SelfCheckCount(ConvertToCDM::convert(value));
	return *this;
}


long AlertSystemState::getSelfCheckCount() const {
	return ConvertFromCDM::convert(data->SelfCheckCount());
}
	
AlertSystemState & AlertSystemState::setPresentPhysiologicalAlarmConditions(const AlertConditionReference & value) {
	data->PresentPhysiologicalAlarmConditions(ConvertToCDM::convert(value));
	return *this;
}


AlertConditionReference AlertSystemState::getPresentPhysiologicalAlarmConditions() const {
	return ConvertFromCDM::convert(data->PresentPhysiologicalAlarmConditions());
}
	
AlertSystemState & AlertSystemState::setPresentTechnicalAlarmConditions(const AlertConditionReference & value) {
	data->PresentTechnicalAlarmConditions(ConvertToCDM::convert(value));
	return *this;
}


AlertConditionReference AlertSystemState::getPresentTechnicalAlarmConditions() const {
	return ConvertFromCDM::convert(data->PresentTechnicalAlarmConditions());
}
	
AlertSystemState & AlertSystemState::addSystemSignalActivation(const SystemSignalActivation & value) {
	data->SystemSignalActivation().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<SystemSignalActivation> AlertSystemState::getSystemSignalActivations() const {
	std::vector<SystemSignalActivation> result;
	result.reserve(data->SystemSignalActivation().size());
	for (const auto & value: data->SystemSignalActivation()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void AlertSystemState::clearSystemSignalActivations() {
	data->SystemSignalActivation().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

