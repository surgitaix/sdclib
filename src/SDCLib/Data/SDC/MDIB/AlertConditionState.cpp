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
 *  Author: besting, buerger, roehser
 */

/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 *
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "SDCLib/Data/SDC/MDIB/AlertConditionState.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"


namespace SDCLib {
namespace Data {
namespace SDC {


AlertConditionState::AlertConditionState(
		HandleRef descriptorhandle
		,
		AlertActivation activationstate
) : data(Defaults::AlertConditionStateInit(
		descriptorhandle
		,
		activationstate
))
{}

AlertConditionState::operator CDM::AlertConditionState() const {
	return *data;
}

AlertConditionState::AlertConditionState(const CDM::AlertConditionState & object)
: data(new CDM::AlertConditionState(object))
{ }

AlertConditionState::AlertConditionState(const AlertConditionState & object)
: data(std::make_shared<CDM::AlertConditionState>(*object.data))
{ }

void AlertConditionState::copyFrom(const AlertConditionState & object) {
	data = std::make_shared<CDM::AlertConditionState>(*object.data);
}

AlertConditionState & AlertConditionState:: operator=(const AlertConditionState& object) {
	copyFrom(object);
	return *this;
}


AlertConditionState & AlertConditionState::setStateVersion(const VersionCounter & value) {
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool AlertConditionState::getStateVersion(VersionCounter & out) const {
	if (data->StateVersion().present()) {
		out = ConvertFromCDM::convert(data->StateVersion().get());
		return true;
	}
	return false;
}

VersionCounter AlertConditionState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion().get());
}

bool AlertConditionState::hasStateVersion() const {
	return data->StateVersion().present();
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

bool AlertConditionState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion AlertConditionState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}

bool AlertConditionState::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}

AlertConditionState & AlertConditionState::setActivationState(const AlertActivation & value) {
	data->ActivationState(ConvertToCDM::convert(value));
	return *this;
}


AlertActivation AlertConditionState::getActivationState() const {
	return ConvertFromCDM::convert(data->ActivationState());
}

AlertConditionState & AlertConditionState::setActualConditionGenerationDelay(const xml_schema::Duration & value) {
	data->ActualConditionGenerationDelay(ConvertToCDM::convert(value));
	return *this;
}

bool AlertConditionState::getActualConditionGenerationDelay(xml_schema::Duration & out) const {
	if (data->ActualConditionGenerationDelay().present()) {
		out = ConvertFromCDM::convert(data->ActualConditionGenerationDelay().get());
		return true;
	}
	return false;
}

xml_schema::Duration AlertConditionState::getActualConditionGenerationDelay() const {
	return ConvertFromCDM::convert(data->ActualConditionGenerationDelay().get());
}

bool AlertConditionState::hasActualConditionGenerationDelay() const {
	return data->ActualConditionGenerationDelay().present();
}

AlertConditionState & AlertConditionState::setActualPriority(const AlertConditionPriority & value) {
	data->ActualPriority(ConvertToCDM::convert(value));
	return *this;
}

bool AlertConditionState::getActualPriority(AlertConditionPriority & out) const {
	if (data->ActualPriority().present()) {
		out = ConvertFromCDM::convert(data->ActualPriority().get());
		return true;
	}
	return false;
}

AlertConditionPriority AlertConditionState::getActualPriority() const {
	return ConvertFromCDM::convert(data->ActualPriority().get());
}

bool AlertConditionState::hasActualPriority() const {
	return data->ActualPriority().present();
}

AlertConditionState & AlertConditionState::setRank(const int & value) {
	data->Rank(ConvertToCDM::convert(value));
	return *this;
}

bool AlertConditionState::getRank(int & out) const {
	if (data->Rank().present()) {
		out = ConvertFromCDM::convert(data->Rank().get());
		return true;
	}
	return false;
}

int AlertConditionState::getRank() const {
	return ConvertFromCDM::convert(data->Rank().get());
}

bool AlertConditionState::hasRank() const {
	return data->Rank().present();
}

AlertConditionState & AlertConditionState::setPresence(const bool & value) {
	data->Presence(ConvertToCDM::convert(value));
	return *this;
}

bool AlertConditionState::getPresence(bool & out) const {
	if (data->Presence().present()) {
		out = ConvertFromCDM::convert(data->Presence().get());
		return true;
	}
	return false;
}

bool AlertConditionState::getPresence() const {
	return ConvertFromCDM::convert(data->Presence().get());
}

bool AlertConditionState::hasPresence() const {
	return data->Presence().present();
}

AlertConditionState & AlertConditionState::setDeterminationTime(const Timestamp & value) {
	data->DeterminationTime(ConvertToCDM::convert(value));
	return *this;
}

bool AlertConditionState::getDeterminationTime(Timestamp & out) const {
	if (data->DeterminationTime().present()) {
		out = ConvertFromCDM::convert(data->DeterminationTime().get());
		return true;
	}
	return false;
}

Timestamp AlertConditionState::getDeterminationTime() const {
	return ConvertFromCDM::convert(data->DeterminationTime().get());
}

bool AlertConditionState::hasDeterminationTime() const {
	return data->DeterminationTime().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

