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
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/AlertConditionReference.h"
#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

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


AlertSystemState & AlertSystemState::setHandle(const std::string & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSystemState::getHandle(std::string & out) const {
	if (data->Handle().present()) {
		out = ConvertFromCDM::convert(data->Handle().get());
		return true;
	}
	return false;
}

std::string AlertSystemState::getHandle() const {
	return ConvertFromCDM::convert(data->Handle().get());
}
	
bool AlertSystemState::hasHandle() const {
	return data->Handle().present();
}
	
AlertSystemState & AlertSystemState::setDescriptorHandle(const std::string & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


std::string AlertSystemState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
}
	
AlertSystemState & AlertSystemState::setStateVersion(const VersionCounter & value) {
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSystemState::getStateVersion(VersionCounter & out) const {
	if (data->StateVersion().present()) {
		out = ConvertFromCDM::convert(data->StateVersion().get());
		return true;
	}
	return false;
}

VersionCounter AlertSystemState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion().get());
}
	
bool AlertSystemState::hasStateVersion() const {
	return data->StateVersion().present();
}
	
AlertSystemState & AlertSystemState::setActivationState(const PausableActivation & value) {
	data->ActivationState(ConvertToCDM::convert(value));
	return *this;
}


PausableActivation AlertSystemState::getActivationState() const {
	return ConvertFromCDM::convert(data->ActivationState());
}
	
AlertSystemState & AlertSystemState::setPresentPhysiologicalAlarmConditions(const AlertConditionReference & value) {
	data->PresentPhysiologicalAlarmConditions(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSystemState::getPresentPhysiologicalAlarmConditions(AlertConditionReference & out) const {
	if (data->PresentPhysiologicalAlarmConditions().present()) {
		out = ConvertFromCDM::convert(data->PresentPhysiologicalAlarmConditions().get());
		return true;
	}
	return false;
}

AlertConditionReference AlertSystemState::getPresentPhysiologicalAlarmConditions() const {
	return ConvertFromCDM::convert(data->PresentPhysiologicalAlarmConditions().get());
}
	
bool AlertSystemState::hasPresentPhysiologicalAlarmConditions() const {
	return data->PresentPhysiologicalAlarmConditions().present();
}
	
AlertSystemState & AlertSystemState::setPresentTechnicalAlarmConditions(const AlertConditionReference & value) {
	data->PresentTechnicalAlarmConditions(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSystemState::getPresentTechnicalAlarmConditions(AlertConditionReference & out) const {
	if (data->PresentTechnicalAlarmConditions().present()) {
		out = ConvertFromCDM::convert(data->PresentTechnicalAlarmConditions().get());
		return true;
	}
	return false;
}

AlertConditionReference AlertSystemState::getPresentTechnicalAlarmConditions() const {
	return ConvertFromCDM::convert(data->PresentTechnicalAlarmConditions().get());
}
	
bool AlertSystemState::hasPresentTechnicalAlarmConditions() const {
	return data->PresentTechnicalAlarmConditions().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

