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
 *  MdsState.cpp
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

#include "SDCLib/Data/SDC/MDIB/MdsState.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/OperatingJurisdiction.h"
#include "SDCLib/Data/SDC/MDIB/CalibrationInfo.h"
#include "SDCLib/Data/SDC/MDIB/PhysicalConnectorInfo.h"

namespace SDCLib {
namespace Data {
namespace SDC {


MdsState::MdsState(
		HandleRef descriptorhandle
) : data(Defaults::MdsStateInit(
		descriptorhandle
)) {}

MdsState::operator CDM::MdsState() const {
	return *data;
}

MdsState::MdsState(const CDM::MdsState & object) : data(new CDM::MdsState(object)) {

}

MdsState::MdsState(const MdsState & object) : data(new CDM::MdsState(*object.data)) {

}

MdsState::~MdsState() {

}

void MdsState::copyFrom(const MdsState & object) {
	data = std::shared_ptr<CDM::MdsState>( new CDM::MdsState(*object.data));
}

MdsState & MdsState:: operator=(const MdsState & object) {
	copyFrom(object);
	return *this;
}


MdsState & MdsState::setStateVersion(const VersionCounter & value) {
	data->setStateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool MdsState::getStateVersion(VersionCounter & out) const {
	if (data->getStateVersion().present()) {
		out = ConvertFromCDM::convert(data->getStateVersion().get());
		return true;
	}
	return false;
}

VersionCounter MdsState::getStateVersion() const {
	return ConvertFromCDM::convert(data->getStateVersion().get());
}

bool MdsState::hasStateVersion() const {
	return data->getStateVersion().present();
}

MdsState & MdsState::setDescriptorHandle(const HandleRef & value) {
	data->setDescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef MdsState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->getDescriptorHandle());
}

MdsState & MdsState::setDescriptorVersion(const ReferencedVersion & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool MdsState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion MdsState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool MdsState::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

MdsState & MdsState::setCalibrationInfo(const CalibrationInfo & value) {
	data->setCalibrationInfo(ConvertToCDM::convert(value));
	return *this;
}

bool MdsState::getCalibrationInfo(CalibrationInfo & out) const {
	if (data->getCalibrationInfo().present()) {
		out = ConvertFromCDM::convert(data->getCalibrationInfo().get());
		return true;
	}
	return false;
}

CalibrationInfo MdsState::getCalibrationInfo() const {
	return ConvertFromCDM::convert(data->getCalibrationInfo().get());
}

bool MdsState::hasCalibrationInfo() const {
	return data->getCalibrationInfo().present();
}

MdsState & MdsState::setNextCalibration(const CalibrationInfo & value) {
	data->setNextCalibration(ConvertToCDM::convert(value));
	return *this;
}

bool MdsState::getNextCalibration(CalibrationInfo & out) const {
	if (data->getNextCalibration().present()) {
		out = ConvertFromCDM::convert(data->getNextCalibration().get());
		return true;
	}
	return false;
}

CalibrationInfo MdsState::getNextCalibration() const {
	return ConvertFromCDM::convert(data->getNextCalibration().get());
}

bool MdsState::hasNextCalibration() const {
	return data->getNextCalibration().present();
}

MdsState & MdsState::setPhysicalConnector(const PhysicalConnectorInfo & value) {
	data->setPhysicalConnector(ConvertToCDM::convert(value));
	return *this;
}

bool MdsState::getPhysicalConnector(PhysicalConnectorInfo & out) const {
	if (data->getPhysicalConnector().present()) {
		out = ConvertFromCDM::convert(data->getPhysicalConnector().get());
		return true;
	}
	return false;
}

PhysicalConnectorInfo MdsState::getPhysicalConnector() const {
	return ConvertFromCDM::convert(data->getPhysicalConnector().get());
}

bool MdsState::hasPhysicalConnector() const {
	return data->getPhysicalConnector().present();
}

MdsState & MdsState::setActivationState(const ComponentActivation & value) {
	data->setActivationState(ConvertToCDM::convert(value));
	return *this;
}

bool MdsState::getActivationState(ComponentActivation & out) const {
	if (data->getActivationState().present()) {
		out = ConvertFromCDM::convert(data->getActivationState().get());
		return true;
	}
	return false;
}

ComponentActivation MdsState::getActivationState() const {
	return ConvertFromCDM::convert(data->getActivationState().get());
}

bool MdsState::hasActivationState() const {
	return data->getActivationState().present();
}

MdsState & MdsState::setOperatingHours(const unsigned int & value) {
	data->setOperatingHours(ConvertToCDM::convert(value));
	return *this;
}

bool MdsState::getOperatingHours(unsigned int & out) const {
	if (data->getOperatingHours().present()) {
		out = ConvertFromCDM::convert(data->getOperatingHours().get());
		return true;
	}
	return false;
}

unsigned int MdsState::getOperatingHours() const {
	return ConvertFromCDM::convert(data->getOperatingHours().get());
}

bool MdsState::hasOperatingHours() const {
	return data->getOperatingHours().present();
}

MdsState & MdsState::setOperatingCycles(const int & value) {
	data->setOperatingCycles(ConvertToCDM::convert(value));
	return *this;
}

bool MdsState::getOperatingCycles(int & out) const {
	if (data->getOperatingCycles().present()) {
		out = ConvertFromCDM::convert(data->getOperatingCycles().get());
		return true;
	}
	return false;
}

int MdsState::getOperatingCycles() const {
	return ConvertFromCDM::convert(data->getOperatingCycles().get());
}

bool MdsState::hasOperatingCycles() const {
	return data->getOperatingCycles().present();
}

MdsState & MdsState::setOperatingJurisdiction(const OperatingJurisdiction & value) {
	data->setOperatingJurisdiction(ConvertToCDM::convert(value));
	return *this;
}

bool MdsState::getOperatingJurisdiction(OperatingJurisdiction & out) const {
	if (data->getOperatingJurisdiction().present()) {
		out = ConvertFromCDM::convert(data->getOperatingJurisdiction().get());
		return true;
	}
	return false;
}

OperatingJurisdiction MdsState::getOperatingJurisdiction() const {
	return ConvertFromCDM::convert(data->getOperatingJurisdiction().get());
}

bool MdsState::hasOperatingJurisdiction() const {
	return data->getOperatingJurisdiction().present();
}

MdsState & MdsState::setLang(const xml_schema::Language & value) {
	data->setLang(ConvertToCDM::convert(value));
	return *this;
}

bool MdsState::getLang(xml_schema::Language & out) const {
	if (data->getLang().present()) {
		out = ConvertFromCDM::convert(data->getLang().get());
		return true;
	}
	return false;
}

xml_schema::Language MdsState::getLang() const {
	return ConvertFromCDM::convert(data->getLang().get());
}

bool MdsState::hasLang() const {
	return data->getLang().present();
}

MdsState & MdsState::setOperatingMode(const MdsOperatingMode & value) {
	data->setOperatingMode(ConvertToCDM::convert(value));
	return *this;
}

bool MdsState::getOperatingMode(MdsOperatingMode & out) const {
	if (data->getOperatingMode().present()) {
		out = ConvertFromCDM::convert(data->getOperatingMode().get());
		return true;
	}
	return false;
}

MdsOperatingMode MdsState::getOperatingMode() const {
	return ConvertFromCDM::convert(data->getOperatingMode().get());
}

bool MdsState::hasOperatingMode() const {
	return data->getOperatingMode().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

