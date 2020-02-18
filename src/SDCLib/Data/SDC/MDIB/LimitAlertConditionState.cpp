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
 *  LimitAlertConditionState.cpp
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

#include "SDCLib/Data/SDC/MDIB/LimitAlertConditionState.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/Range.h"

namespace SDCLib {
namespace Data {
namespace SDC {


LimitAlertConditionState::LimitAlertConditionState(
		HandleRef descriptorhandle
		,
		AlertActivation activationstate
		,
		Range limits
		,
		AlertConditionMonitoredLimits monitoredalertlimits
) : data(Defaults::LimitAlertConditionStateInit(
		descriptorhandle
		,
		activationstate
		,
		limits
		,
		monitoredalertlimits
))
{}

LimitAlertConditionState::operator CDM::LimitAlertConditionState() const {
	return *data;
}

LimitAlertConditionState::LimitAlertConditionState(const CDM::LimitAlertConditionState & object)
: data(new CDM::LimitAlertConditionState(object))
{ }

LimitAlertConditionState::LimitAlertConditionState(const LimitAlertConditionState & object)
: data(std::make_shared<CDM::LimitAlertConditionState>(*object.data))
{ }

void LimitAlertConditionState::copyFrom(const LimitAlertConditionState & object) {
	data = std::make_shared<CDM::LimitAlertConditionState>(*object.data);
}

LimitAlertConditionState & LimitAlertConditionState:: operator=(const LimitAlertConditionState& object) {
	copyFrom(object);
	return *this;
}


LimitAlertConditionState & LimitAlertConditionState::setStateVersion(const VersionCounter & value) {
	data->setStateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool LimitAlertConditionState::getStateVersion(VersionCounter & out) const {
	if (data->getStateVersion().present()) {
		out = ConvertFromCDM::convert(data->getStateVersion().get());
		return true;
	}
	return false;
}

VersionCounter LimitAlertConditionState::getStateVersion() const {
	return ConvertFromCDM::convert(data->getStateVersion().get());
}

bool LimitAlertConditionState::hasStateVersion() const {
	return data->getStateVersion().present();
}

LimitAlertConditionState & LimitAlertConditionState::setDescriptorHandle(const HandleRef & value) {
	data->setDescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef LimitAlertConditionState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->getDescriptorHandle());
}

LimitAlertConditionState & LimitAlertConditionState::setDescriptorVersion(const ReferencedVersion & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool LimitAlertConditionState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion LimitAlertConditionState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool LimitAlertConditionState::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

LimitAlertConditionState & LimitAlertConditionState::setActivationState(const AlertActivation & value) {
	data->setActivationState(ConvertToCDM::convert(value));
	return *this;
}


AlertActivation LimitAlertConditionState::getActivationState() const {
	return ConvertFromCDM::convert(data->getActivationState());
}

LimitAlertConditionState & LimitAlertConditionState::setActualConditionGenerationDelay(const xml_schema::Duration & value) {
	data->setActualConditionGenerationDelay(ConvertToCDM::convert(value));
	return *this;
}

bool LimitAlertConditionState::getActualConditionGenerationDelay(xml_schema::Duration & out) const {
	if (data->getActualConditionGenerationDelay().present()) {
		out = ConvertFromCDM::convert(data->getActualConditionGenerationDelay().get());
		return true;
	}
	return false;
}

xml_schema::Duration LimitAlertConditionState::getActualConditionGenerationDelay() const {
	return ConvertFromCDM::convert(data->getActualConditionGenerationDelay().get());
}

bool LimitAlertConditionState::hasActualConditionGenerationDelay() const {
	return data->getActualConditionGenerationDelay().present();
}

LimitAlertConditionState & LimitAlertConditionState::setActualPriority(const AlertConditionPriority & value) {
	data->setActualPriority(ConvertToCDM::convert(value));
	return *this;
}

bool LimitAlertConditionState::getActualPriority(AlertConditionPriority & out) const {
	if (data->getActualPriority().present()) {
		out = ConvertFromCDM::convert(data->getActualPriority().get());
		return true;
	}
	return false;
}

AlertConditionPriority LimitAlertConditionState::getActualPriority() const {
	return ConvertFromCDM::convert(data->getActualPriority().get());
}

bool LimitAlertConditionState::hasActualPriority() const {
	return data->getActualPriority().present();
}

LimitAlertConditionState & LimitAlertConditionState::setRank(const int & value) {
	data->setRank(ConvertToCDM::convert(value));
	return *this;
}

bool LimitAlertConditionState::getRank(int & out) const {
	if (data->getRank().present()) {
		out = ConvertFromCDM::convert(data->getRank().get());
		return true;
	}
	return false;
}

int LimitAlertConditionState::getRank() const {
	return ConvertFromCDM::convert(data->getRank().get());
}

bool LimitAlertConditionState::hasRank() const {
	return data->getRank().present();
}

LimitAlertConditionState & LimitAlertConditionState::setPresence(const bool & value) {
	data->setPresence(ConvertToCDM::convert(value));
	return *this;
}

bool LimitAlertConditionState::getPresence(bool & out) const {
	if (data->getPresence().present()) {
		out = ConvertFromCDM::convert(data->getPresence().get());
		return true;
	}
	return false;
}

bool LimitAlertConditionState::getPresence() const {
	return ConvertFromCDM::convert(data->getPresence().get());
}

bool LimitAlertConditionState::hasPresence() const {
	return data->getPresence().present();
}

LimitAlertConditionState & LimitAlertConditionState::setDeterminationTime(const Timestamp & value) {
	data->setDeterminationTime(ConvertToCDM::convert(value));
	return *this;
}

bool LimitAlertConditionState::getDeterminationTime(Timestamp & out) const {
	if (data->getDeterminationTime().present()) {
		out = ConvertFromCDM::convert(data->getDeterminationTime().get());
		return true;
	}
	return false;
}

Timestamp LimitAlertConditionState::getDeterminationTime() const {
	return ConvertFromCDM::convert(data->getDeterminationTime().get());
}

bool LimitAlertConditionState::hasDeterminationTime() const {
	return data->getDeterminationTime().present();
}

LimitAlertConditionState & LimitAlertConditionState::setLimits(const Range & value) {
	data->setLimits(ConvertToCDM::convert(value));
	return *this;
}


Range LimitAlertConditionState::getLimits() const {
	return ConvertFromCDM::convert(data->getLimits());
}

LimitAlertConditionState & LimitAlertConditionState::setMonitoredAlertLimits(const AlertConditionMonitoredLimits & value) {
	data->setMonitoredAlertLimits(ConvertToCDM::convert(value));
	return *this;
}


AlertConditionMonitoredLimits LimitAlertConditionState::getMonitoredAlertLimits() const {
	return ConvertFromCDM::convert(data->getMonitoredAlertLimits());
}

LimitAlertConditionState & LimitAlertConditionState::setAutoLimitActivationState(const AlertActivation & value) {
	data->setAutoLimitActivationState(ConvertToCDM::convert(value));
	return *this;
}

bool LimitAlertConditionState::getAutoLimitActivationState(AlertActivation & out) const {
	if (data->getAutoLimitActivationState().present()) {
		out = ConvertFromCDM::convert(data->getAutoLimitActivationState().get());
		return true;
	}
	return false;
}

AlertActivation LimitAlertConditionState::getAutoLimitActivationState() const {
	return ConvertFromCDM::convert(data->getAutoLimitActivationState().get());
}

bool LimitAlertConditionState::hasAutoLimitActivationState() const {
	return data->getAutoLimitActivationState().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

