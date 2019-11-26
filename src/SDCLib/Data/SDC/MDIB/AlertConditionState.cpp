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
	data->setStateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool AlertConditionState::getStateVersion(VersionCounter & out) const {
	if (data->getStateVersion().present()) {
		out = ConvertFromCDM::convert(data->getStateVersion().get());
		return true;
	}
	return false;
}

VersionCounter AlertConditionState::getStateVersion() const {
	return ConvertFromCDM::convert(data->getStateVersion().get());
}

bool AlertConditionState::hasStateVersion() const {
	return data->getStateVersion().present();
}

AlertConditionState & AlertConditionState::setDescriptorHandle(const HandleRef & value) {
	data->setDescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef AlertConditionState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->getDescriptorHandle());
}

AlertConditionState & AlertConditionState::setDescriptorVersion(const ReferencedVersion & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool AlertConditionState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion AlertConditionState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool AlertConditionState::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

AlertConditionState & AlertConditionState::setActivationState(const AlertActivation & value) {
	data->setActivationState(ConvertToCDM::convert(value));
	return *this;
}


AlertActivation AlertConditionState::getActivationState() const {
	return ConvertFromCDM::convert(data->getActivationState());
}

AlertConditionState & AlertConditionState::setActualConditionGenerationDelay(const xml_schema::Duration & value) {
	data->setActualConditionGenerationDelay(ConvertToCDM::convert(value));
	return *this;
}

bool AlertConditionState::getActualConditionGenerationDelay(xml_schema::Duration & out) const {
	if (data->getActualConditionGenerationDelay().present()) {
		out = ConvertFromCDM::convert(data->getActualConditionGenerationDelay().get());
		return true;
	}
	return false;
}

xml_schema::Duration AlertConditionState::getActualConditionGenerationDelay() const {
	return ConvertFromCDM::convert(data->getActualConditionGenerationDelay().get());
}

bool AlertConditionState::hasActualConditionGenerationDelay() const {
	return data->getActualConditionGenerationDelay().present();
}

AlertConditionState & AlertConditionState::setActualPriority(const AlertConditionPriority & value) {
	data->setActualPriority(ConvertToCDM::convert(value));
	return *this;
}

bool AlertConditionState::getActualPriority(AlertConditionPriority & out) const {
	if (data->getActualPriority().present()) {
		out = ConvertFromCDM::convert(data->getActualPriority().get());
		return true;
	}
	return false;
}

AlertConditionPriority AlertConditionState::getActualPriority() const {
	return ConvertFromCDM::convert(data->getActualPriority().get());
}

bool AlertConditionState::hasActualPriority() const {
	return data->getActualPriority().present();
}

AlertConditionState & AlertConditionState::setRank(const int & value) {
	data->setRank(ConvertToCDM::convert(value));
	return *this;
}

bool AlertConditionState::getRank(int & out) const {
	if (data->getRank().present()) {
		out = ConvertFromCDM::convert(data->getRank().get());
		return true;
	}
	return false;
}

int AlertConditionState::getRank() const {
	return ConvertFromCDM::convert(data->getRank().get());
}

bool AlertConditionState::hasRank() const {
	return data->getRank().present();
}

AlertConditionState & AlertConditionState::setPresence(const bool & value) {
	data->setPresence(ConvertToCDM::convert(value));
	return *this;
}

bool AlertConditionState::getPresence(bool & out) const {
	if (data->getPresence().present()) {
		out = ConvertFromCDM::convert(data->getPresence().get());
		return true;
	}
	return false;
}

bool AlertConditionState::getPresence() const {
	return ConvertFromCDM::convert(data->getPresence().get());
}

bool AlertConditionState::hasPresence() const {
	return data->getPresence().present();
}

AlertConditionState & AlertConditionState::setDeterminationTime(const Timestamp & value) {
	data->setDeterminationTime(ConvertToCDM::convert(value));
	return *this;
}

bool AlertConditionState::getDeterminationTime(Timestamp & out) const {
	if (data->getDeterminationTime().present()) {
		out = ConvertFromCDM::convert(data->getDeterminationTime().get());
		return true;
	}
	return false;
}

Timestamp AlertConditionState::getDeterminationTime() const {
	return ConvertFromCDM::convert(data->getDeterminationTime().get());
}

bool AlertConditionState::hasDeterminationTime() const {
	return data->getDeterminationTime().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

