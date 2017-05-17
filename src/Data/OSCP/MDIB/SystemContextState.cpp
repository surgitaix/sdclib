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
 *  SystemContextState.cpp
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

#include "OSCLib/Data/OSCP/MDIB/SystemContextState.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

SystemContextState::SystemContextState() : data(Defaults::SystemContextState()) {
}

SystemContextState::operator CDM::SystemContextState() const {
	return *data;
}

SystemContextState::SystemContextState(const CDM::SystemContextState & object) : data(new CDM::SystemContextState(object)) {

}

SystemContextState::SystemContextState(const SystemContextState & object) : data(new CDM::SystemContextState(*object.data)) {

}

SystemContextState::~SystemContextState() {

}

void SystemContextState::copyFrom(const SystemContextState & object) {
	*data = *object.data;
}

SystemContextState & SystemContextState:: operator=(const SystemContextState & object) {
	copyFrom(object);
	return *this;
}


SystemContextState & SystemContextState::setHandle(const std::string & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContextState::getHandle(std::string & out) const {
	if (data->Handle().present()) {
		out = ConvertFromCDM::convert(data->Handle().get());
		return true;
	}
	return false;
}

std::string SystemContextState::getHandle() const {
	return ConvertFromCDM::convert(data->Handle().get());
}
	
bool SystemContextState::hasHandle() const {
	return data->Handle().present();
}
	
SystemContextState & SystemContextState::setDescriptorHandle(const std::string & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


std::string SystemContextState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
}
	
SystemContextState & SystemContextState::setStateVersion(const VersionCounter & value) {
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContextState::getStateVersion(VersionCounter & out) const {
	if (data->StateVersion().present()) {
		out = ConvertFromCDM::convert(data->StateVersion().get());
		return true;
	}
	return false;
}

VersionCounter SystemContextState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion().get());
}
	
bool SystemContextState::hasStateVersion() const {
	return data->StateVersion().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

