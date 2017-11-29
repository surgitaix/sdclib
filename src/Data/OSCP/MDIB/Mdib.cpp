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
 *  Mdib.cpp
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

#include "OSCLib/Data/OSCP/MDIB/Mdib.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/MdDescription.h"
#include "OSCLib/Data/OSCP/MDIB/MdState.h"

namespace OSCLib {
namespace Data {
namespace OSCP {


Mdib::Mdib(
) : data(Defaults::MdibInit(
)) {}

Mdib::operator CDM::Mdib() const {
	return *data;
}

Mdib::Mdib(const CDM::Mdib & object) : data(new CDM::Mdib(object)) {

}

Mdib::Mdib(const Mdib & object) : data(new CDM::Mdib(*object.data)) {

}

Mdib::~Mdib() {

}

void Mdib::copyFrom(const Mdib & object) {
	data = std::shared_ptr<CDM::Mdib>( new CDM::Mdib(*object.data));
}

Mdib & Mdib:: operator=(const Mdib & object) {
	copyFrom(object);
	return *this;
}


Mdib & Mdib::setMdDescription(const MdDescription & value) {
	data->MdDescription(ConvertToCDM::convert(value));
	return *this;
}

bool Mdib::getMdDescription(MdDescription & out) const {
	if (data->MdDescription().present()) {
		out = ConvertFromCDM::convert(data->MdDescription().get());
		return true;
	}
	return false;
}

MdDescription Mdib::getMdDescription() const {
	return ConvertFromCDM::convert(data->MdDescription().get());
}
	
bool Mdib::hasMdDescription() const {
	return data->MdDescription().present();
}
	
Mdib & Mdib::setMdState(const MdState & value) {
	data->MdState(ConvertToCDM::convert(value));
	return *this;
}

bool Mdib::getMdState(MdState & out) const {
	if (data->MdState().present()) {
		out = ConvertFromCDM::convert(data->MdState().get());
		return true;
	}
	return false;
}

MdState Mdib::getMdState() const {
	return ConvertFromCDM::convert(data->MdState().get());
}
	
bool Mdib::hasMdState() const {
	return data->MdState().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

