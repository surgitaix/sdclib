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
 *  MDState.cpp
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

#include "OSCLib/Data/OSCP/MDIB/MDState.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

MDState::MDState() : data(Defaults::MDState()) {
}

MDState::operator CDM::MDState() const {
	return *data;
}

MDState::MDState(const CDM::MDState & object) : data(new CDM::MDState(object)) {

}

MDState::MDState(const MDState & object) : data(new CDM::MDState(*object.data)) {

}

MDState::~MDState() {

}

void MDState::copyFrom(const MDState & object) {
	*data = *object.data;
}

MDState & MDState:: operator=(const MDState & object) {
	copyFrom(object);
	return *this;
}


MDState & MDState::setStateVersion(const VersionCounter & value) {
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool MDState::getStateVersion(VersionCounter & out) const {
	if (data->StateVersion().present()) {
		out = ConvertFromCDM::convert(data->StateVersion().get());
		return true;
	}
	return false;
}

VersionCounter MDState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion().get());
}
	
bool MDState::hasStateVersion() const {
	return data->StateVersion().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

