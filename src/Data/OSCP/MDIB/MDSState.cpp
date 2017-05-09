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
 *  MDSState.cpp
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

#include "OSCLib/Data/OSCP/MDIB/MDSState.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/Language.h"
#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

MDSState::MDSState() : data(Defaults::MDSState()) {
}

MDSState::operator CDM::MDSState() const {
	return *data;
}

MDSState::MDSState(const CDM::MDSState & object) : data(new CDM::MDSState(object)) {

}

MDSState::MDSState(const MDSState & object) : data(new CDM::MDSState(*object.data)) {

}

MDSState::~MDSState() {

}

void MDSState::copyFrom(const MDSState & object) {
	*data = *object.data;
}

MDSState & MDSState:: operator=(const MDSState & object) {
	copyFrom(object);
	return *this;
}


MDSState & MDSState::setHandle(const std::string & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}

bool MDSState::getHandle(std::string & out) const {
	if (data->Handle().present()) {
		out = ConvertFromCDM::convert(data->Handle().get());
		return true;
	}
	return false;
}

std::string MDSState::getHandle() const {
	return ConvertFromCDM::convert(data->Handle().get());
}
	
bool MDSState::hasHandle() const {
	return data->Handle().present();
}
	
MDSState & MDSState::setDescriptorHandle(const std::string & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


std::string MDSState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
}
	
MDSState & MDSState::setStateVersion(const VersionCounter & value) {
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool MDSState::getStateVersion(VersionCounter & out) const {
	if (data->StateVersion().present()) {
		out = ConvertFromCDM::convert(data->StateVersion().get());
		return true;
	}
	return false;
}

VersionCounter MDSState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion().get());
}
	
bool MDSState::hasStateVersion() const {
	return data->StateVersion().present();
}
	
MDSState & MDSState::setActivationState(const int & value) {
	data->ActivationState(ConvertToCDM::convert(value));
	return *this;
}

bool MDSState::getActivationState(int & out) const {
	if (data->ActivationState().present()) {
		out = ConvertFromCDM::convert(data->ActivationState().get());
		return true;
	}
	return false;
}

int MDSState::getActivationState() const {
	return ConvertFromCDM::convert(data->ActivationState().get());
}
	
bool MDSState::hasActivationState() const {
	return data->ActivationState().present();
}
	
MDSState & MDSState::setOperatingHours(const unsigned int & value) {
	data->OperatingHours(ConvertToCDM::convert(value));
	return *this;
}

bool MDSState::getOperatingHours(unsigned int & out) const {
	if (data->OperatingHours().present()) {
		out = ConvertFromCDM::convert(data->OperatingHours().get());
		return true;
	}
	return false;
}

unsigned int MDSState::getOperatingHours() const {
	return ConvertFromCDM::convert(data->OperatingHours().get());
}
	
bool MDSState::hasOperatingHours() const {
	return data->OperatingHours().present();
}
	
MDSState & MDSState::setOperatingCycles(const int & value) {
	data->OperatingCycles(ConvertToCDM::convert(value));
	return *this;
}

bool MDSState::getOperatingCycles(int & out) const {
	if (data->OperatingCycles().present()) {
		out = ConvertFromCDM::convert(data->OperatingCycles().get());
		return true;
	}
	return false;
}

int MDSState::getOperatingCycles() const {
	return ConvertFromCDM::convert(data->OperatingCycles().get());
}
	
bool MDSState::hasOperatingCycles() const {
	return data->OperatingCycles().present();
}
	
MDSState & MDSState::setCalibrationInfo(const CalibrationInfo & value) {
	data->CalibrationInfo(ConvertToCDM::convert(value));
	return *this;
}

bool MDSState::getCalibrationInfo(CalibrationInfo & out) const {
	if (data->CalibrationInfo().present()) {
		out = ConvertFromCDM::convert(data->CalibrationInfo().get());
		return true;
	}
	return false;
}

CalibrationInfo MDSState::getCalibrationInfo() const {
	return ConvertFromCDM::convert(data->CalibrationInfo().get());
}
	
bool MDSState::hasCalibrationInfo() const {
	return data->CalibrationInfo().present();
}
	
MDSState & MDSState::setNextCalibration(const CalibrationInfo & value) {
	data->NextCalibration(ConvertToCDM::convert(value));
	return *this;
}

bool MDSState::getNextCalibration(CalibrationInfo & out) const {
	if (data->NextCalibration().present()) {
		out = ConvertFromCDM::convert(data->NextCalibration().get());
		return true;
	}
	return false;
}

CalibrationInfo MDSState::getNextCalibration() const {
	return ConvertFromCDM::convert(data->NextCalibration().get());
}
	
bool MDSState::hasNextCalibration() const {
	return data->NextCalibration().present();
}
	
MDSState & MDSState::setLang(const Language & value) {
	data->Lang(ConvertToCDM::convert(value));
	return *this;
}

bool MDSState::getLang(Language & out) const {
	if (data->Lang().present()) {
		out = ConvertFromCDM::convert(data->Lang().get());
		return true;
	}
	return false;
}

Language MDSState::getLang() const {
	return ConvertFromCDM::convert(data->Lang().get());
}
	
bool MDSState::hasLang() const {
	return data->Lang().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

