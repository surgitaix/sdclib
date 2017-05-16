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
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/Language.h"

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


MdsState & MdsState::setLang(const Language & value) {
	data->Lang(ConvertToCDM::convert(value));
	return *this;
}

bool MdsState::getLang(Language & out) const {
	if (data->Lang().present()) {
		out = ConvertFromCDM::convert(data->Lang().get());
		return true;
	}
	return false;
}

Language MdsState::getLang() const {
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

