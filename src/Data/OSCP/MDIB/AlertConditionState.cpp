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
 *  AlertConditionState.cpp
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

#include "OSCLib/Data/OSCP/MDIB/AlertConditionState.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"


namespace OSCLib {
namespace Data {
namespace OSCP {

AlertConditionState::AlertConditionState() : data(Defaults::AlertConditionState()) {
}

AlertConditionState::operator CDM::AlertConditionState() const {
	return *data;
}

AlertConditionState::AlertConditionState(const CDM::AlertConditionState & object) : data(new CDM::AlertConditionState(object)) {

}

AlertConditionState::AlertConditionState(const AlertConditionState & object) : data(new CDM::AlertConditionState(*object.data)) {

}

AlertConditionState::~AlertConditionState() {

}

void AlertConditionState::copyFrom(const AlertConditionState & object) {
	*data = *object.data;
}

AlertConditionState & AlertConditionState:: operator=(const AlertConditionState & object) {
	copyFrom(object);
	return *this;
}


AlertConditionState & AlertConditionState::setStateVersion(const VersionCounter & value) {
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}


VersionCounter AlertConditionState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion());
}
	
AlertConditionState & AlertConditionState::setDescriptorHandle(const HandleRef & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef AlertConditionState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
}
	
AlertConditionState & AlertConditionState::setDescriptorVersion(const ReferencedVersion & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}


ReferencedVersion AlertConditionState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion());
}
	
AlertConditionState & AlertConditionState::setActivationState(const AlertActivation & value) {
	data->ActivationState(ConvertToCDM::convert(value));
	return *this;
}


AlertActivation AlertConditionState::getActivationState() const {
	return ConvertFromCDM::convert(data->ActivationState());
}
	
AlertConditionState & AlertConditionState::setActualPriority(const AlertConditionPriority & value) {
	data->ActualPriority(ConvertToCDM::convert(value));
	return *this;
}


AlertConditionPriority AlertConditionState::getActualPriority() const {
	return ConvertFromCDM::convert(data->ActualPriority());
}
	
AlertConditionState & AlertConditionState::setRank(const int & value) {
	data->Rank(ConvertToCDM::convert(value));
	return *this;
}


int AlertConditionState::getRank() const {
	return ConvertFromCDM::convert(data->Rank());
}
	
AlertConditionState & AlertConditionState::setPresence(const boolean & value) {
	data->Presence(ConvertToCDM::convert(value));
	return *this;
}


boolean AlertConditionState::getPresence() const {
	return ConvertFromCDM::convert(data->Presence());
}
	
AlertConditionState & AlertConditionState::setDeterminationTime(const Timestamp & value) {
	data->DeterminationTime(ConvertToCDM::convert(value));
	return *this;
}


Timestamp AlertConditionState::getDeterminationTime() const {
	return ConvertFromCDM::convert(data->DeterminationTime());
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

