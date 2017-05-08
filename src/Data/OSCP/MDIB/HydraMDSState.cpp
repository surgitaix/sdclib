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

