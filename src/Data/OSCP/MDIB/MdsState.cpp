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
 *  Author: besting, roehser
 */
 
/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 * 
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "OSCLib/Data/OSCP/MDIB/MdsState.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/OperatingJurisdiction.h"
#include "OSCLib/Data/OSCP/MDIB/CalibrationInfo.h"
#include "OSCLib/Data/OSCP/MDIB/PhysicalConnectorInfo.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

MdsState::MdsState() : data(Defaults::MdsState()) {
}

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
	*data = *object.data;
}

MdsState & MdsState:: operator=(const MdsState & object) {
	copyFrom(object);
	return *this;
}


MdsState & MdsState::setStateVersion(const VersionCounter & value) {
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool MdsState::getStateVersion(VersionCounter & out) const {
	if (data->StateVersion().present()) {
		out = ConvertFromCDM::convert(data->StateVersion().get());
		return true;
	}
	return false;
}

VersionCounter MdsState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion().get());
}
	
bool MdsState::hasStateVersion() const {
	return data->StateVersion().present();
}
	
MdsState & MdsState::setDescriptorHandle(const HandleRef & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef MdsState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
}
	
MdsState & MdsState::setDescriptorVersion(const ReferencedVersion & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool MdsState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion MdsState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool MdsState::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
MdsState & MdsState::setCalibrationInfo(const CalibrationInfo & value) {
	data->CalibrationInfo(ConvertToCDM::convert(value));
	return *this;
}

bool MdsState::getCalibrationInfo(CalibrationInfo & out) const {
	if (data->CalibrationInfo().present()) {
		out = ConvertFromCDM::convert(data->CalibrationInfo().get());
		return true;
	}
	return false;
}

CalibrationInfo MdsState::getCalibrationInfo() const {
	return ConvertFromCDM::convert(data->CalibrationInfo().get());
}
	
bool MdsState::hasCalibrationInfo() const {
	return data->CalibrationInfo().present();
}
	
MdsState & MdsState::setNextCalibration(const CalibrationInfo & value) {
	data->NextCalibration(ConvertToCDM::convert(value));
	return *this;
}

bool MdsState::getNextCalibration(CalibrationInfo & out) const {
	if (data->NextCalibration().present()) {
		out = ConvertFromCDM::convert(data->NextCalibration().get());
		return true;
	}
	return false;
}

CalibrationInfo MdsState::getNextCalibration() const {
	return ConvertFromCDM::convert(data->NextCalibration().get());
}
	
bool MdsState::hasNextCalibration() const {
	return data->NextCalibration().present();
}
	
MdsState & MdsState::setPhysicalConnector(const PhysicalConnectorInfo & value) {
	data->PhysicalConnector(ConvertToCDM::convert(value));
	return *this;
}

bool MdsState::getPhysicalConnector(PhysicalConnectorInfo & out) const {
	if (data->PhysicalConnector().present()) {
		out = ConvertFromCDM::convert(data->PhysicalConnector().get());
		return true;
	}
	return false;
}

PhysicalConnectorInfo MdsState::getPhysicalConnector() const {
	return ConvertFromCDM::convert(data->PhysicalConnector().get());
}
	
bool MdsState::hasPhysicalConnector() const {
	return data->PhysicalConnector().present();
}
	
MdsState & MdsState::setActivationState(const ComponentActivation & value) {
	data->ActivationState(ConvertToCDM::convert(value));
	return *this;
}

bool MdsState::getActivationState(ComponentActivation & out) const {
	if (data->ActivationState().present()) {
		out = ConvertFromCDM::convert(data->ActivationState().get());
		return true;
	}
	return false;
}

ComponentActivation MdsState::getActivationState() const {
	return ConvertFromCDM::convert(data->ActivationState().get());
}
	
bool MdsState::hasActivationState() const {
	return data->ActivationState().present();
}
	
MdsState & MdsState::setOperatingHours(const unsigned int & value) {
	data->OperatingHours(ConvertToCDM::convert(value));
	return *this;
}

bool MdsState::getOperatingHours(unsigned int & out) const {
	if (data->OperatingHours().present()) {
		out = ConvertFromCDM::convert(data->OperatingHours().get());
		return true;
	}
	return false;
}

unsigned int MdsState::getOperatingHours() const {
	return ConvertFromCDM::convert(data->OperatingHours().get());
}
	
bool MdsState::hasOperatingHours() const {
	return data->OperatingHours().present();
}
	
MdsState & MdsState::setOperatingCycles(const int & value) {
	data->OperatingCycles(ConvertToCDM::convert(value));
	return *this;
}

bool MdsState::getOperatingCycles(int & out) const {
	if (data->OperatingCycles().present()) {
		out = ConvertFromCDM::convert(data->OperatingCycles().get());
		return true;
	}
	return false;
}

int MdsState::getOperatingCycles() const {
	return ConvertFromCDM::convert(data->OperatingCycles().get());
}
	
bool MdsState::hasOperatingCycles() const {
	return data->OperatingCycles().present();
}
	
MdsState & MdsState::setOperatingJurisdiction(const OperatingJurisdiction & value) {
	data->OperatingJurisdiction(ConvertToCDM::convert(value));
	return *this;
}

bool MdsState::getOperatingJurisdiction(OperatingJurisdiction & out) const {
	if (data->OperatingJurisdiction().present()) {
		out = ConvertFromCDM::convert(data->OperatingJurisdiction().get());
		return true;
	}
	return false;
}

OperatingJurisdiction MdsState::getOperatingJurisdiction() const {
	return ConvertFromCDM::convert(data->OperatingJurisdiction().get());
}
	
bool MdsState::hasOperatingJurisdiction() const {
	return data->OperatingJurisdiction().present();
}
	
MdsState & MdsState::setLang(const xml_schema::Language & value) {
	data->Lang(ConvertToCDM::convert(value));
	return *this;
}

bool MdsState::getLang(xml_schema::Language & out) const {
	if (data->Lang().present()) {
		out = ConvertFromCDM::convert(data->Lang().get());
		return true;
	}
	return false;
}

xml_schema::Language MdsState::getLang() const {
	return ConvertFromCDM::convert(data->Lang().get());
}
	
bool MdsState::hasLang() const {
	return data->Lang().present();
}
	
MdsState & MdsState::setOperatingMode(const MdsOperatingMode & value) {
	data->OperatingMode(ConvertToCDM::convert(value));
	return *this;
}

bool MdsState::getOperatingMode(MdsOperatingMode & out) const {
	if (data->OperatingMode().present()) {
		out = ConvertFromCDM::convert(data->OperatingMode().get());
		return true;
	}
	return false;
}

MdsOperatingMode MdsState::getOperatingMode() const {
	return ConvertFromCDM::convert(data->OperatingMode().get());
}
	
bool MdsState::hasOperatingMode() const {
	return data->OperatingMode().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

