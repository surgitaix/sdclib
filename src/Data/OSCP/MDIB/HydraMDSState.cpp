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
 *  HydraMDSState.cpp
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

#include "OSCLib/Data/OSCP/MDIB/HydraMDSState.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/Language.h"
#include "OSCLib/Data/OSCP/MDIB/CalibrationInfo.h"
#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

HydraMDSState::HydraMDSState() : data(Defaults::HydraMDSState()) {
}

HydraMDSState::operator CDM::HydraMDSState() const {
	return *data;
}

HydraMDSState::HydraMDSState(const CDM::HydraMDSState & object) : data(new CDM::HydraMDSState(object)) {

}

HydraMDSState::HydraMDSState(const HydraMDSState & object) : data(new CDM::HydraMDSState(*object.data)) {

}

HydraMDSState::~HydraMDSState() {

}

void HydraMDSState::copyFrom(const HydraMDSState & object) {
	*data = *object.data;
}

HydraMDSState & HydraMDSState:: operator=(const HydraMDSState & object) {
	copyFrom(object);
	return *this;
}


HydraMDSState & HydraMDSState::setHandle(const std::string & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}

bool HydraMDSState::getHandle(std::string & out) const {
	if (data->Handle().present()) {
		out = ConvertFromCDM::convert(data->Handle().get());
		return true;
	}
	return false;
}

std::string HydraMDSState::getHandle() const {
	return ConvertFromCDM::convert(data->Handle().get());
}
	
bool HydraMDSState::hasHandle() const {
	return data->Handle().present();
}
	
HydraMDSState & HydraMDSState::setDescriptorHandle(const std::string & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


std::string HydraMDSState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
}
	
HydraMDSState & HydraMDSState::setStateVersion(const VersionCounter & value) {
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool HydraMDSState::getStateVersion(VersionCounter & out) const {
	if (data->StateVersion().present()) {
		out = ConvertFromCDM::convert(data->StateVersion().get());
		return true;
	}
	return false;
}

VersionCounter HydraMDSState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion().get());
}
	
bool HydraMDSState::hasStateVersion() const {
	return data->StateVersion().present();
}
	
HydraMDSState & HydraMDSState::setComponentActivationState(const ComponentActivation & value) {
	data->ComponentActivationState(ConvertToCDM::convert(value));
	return *this;
}

bool HydraMDSState::getComponentActivationState(ComponentActivation & out) const {
	if (data->ComponentActivationState().present()) {
		out = ConvertFromCDM::convert(data->ComponentActivationState().get());
		return true;
	}
	return false;
}

ComponentActivation HydraMDSState::getComponentActivationState() const {
	return ConvertFromCDM::convert(data->ComponentActivationState().get());
}
	
bool HydraMDSState::hasComponentActivationState() const {
	return data->ComponentActivationState().present();
}
	
HydraMDSState & HydraMDSState::setCalibrationInfo(const CalibrationInfo & value) {
	data->CalibrationInfo(ConvertToCDM::convert(value));
	return *this;
}

bool HydraMDSState::getCalibrationInfo(CalibrationInfo & out) const {
	if (data->CalibrationInfo().present()) {
		out = ConvertFromCDM::convert(data->CalibrationInfo().get());
		return true;
	}
	return false;
}

CalibrationInfo HydraMDSState::getCalibrationInfo() const {
	return ConvertFromCDM::convert(data->CalibrationInfo().get());
}
	
bool HydraMDSState::hasCalibrationInfo() const {
	return data->CalibrationInfo().present();
}
	
HydraMDSState & HydraMDSState::setOperatingHours(const int & value) {
	data->OperatingHours(ConvertToCDM::convert(value));
	return *this;
}

bool HydraMDSState::getOperatingHours(int & out) const {
	if (data->OperatingHours().present()) {
		out = ConvertFromCDM::convert(data->OperatingHours().get());
		return true;
	}
	return false;
}

int HydraMDSState::getOperatingHours() const {
	return ConvertFromCDM::convert(data->OperatingHours().get());
}
	
bool HydraMDSState::hasOperatingHours() const {
	return data->OperatingHours().present();
}
	
HydraMDSState & HydraMDSState::setOperatingCycles(const int & value) {
	data->OperatingCycles(ConvertToCDM::convert(value));
	return *this;
}

bool HydraMDSState::getOperatingCycles(int & out) const {
	if (data->OperatingCycles().present()) {
		out = ConvertFromCDM::convert(data->OperatingCycles().get());
		return true;
	}
	return false;
}

int HydraMDSState::getOperatingCycles() const {
	return ConvertFromCDM::convert(data->OperatingCycles().get());
}
	
bool HydraMDSState::hasOperatingCycles() const {
	return data->OperatingCycles().present();
}
	
HydraMDSState & HydraMDSState::setLang(const Language & value) {
	data->Lang(ConvertToCDM::convert(value));
	return *this;
}

bool HydraMDSState::getLang(Language & out) const {
	if (data->Lang().present()) {
		out = ConvertFromCDM::convert(data->Lang().get());
		return true;
	}
	return false;
}

Language HydraMDSState::getLang() const {
	return ConvertFromCDM::convert(data->Lang().get());
}
	
bool HydraMDSState::hasLang() const {
	return data->Lang().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

