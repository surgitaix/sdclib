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
 *  SystemSignalActivation.cpp
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

#include "SDCLib/Data/SDC/MDIB/SystemSignalActivation.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"


namespace SDCLib {
namespace Data {
namespace SDC {


SystemSignalActivation::SystemSignalActivation(
		AlertSignalManifestation manifestation
		,
		AlertActivation state
) : data(Defaults::SystemSignalActivationInit(
		manifestation
		,
		state
)) {}

SystemSignalActivation::operator CDM::SystemSignalActivation() const {
	return *data;
}

SystemSignalActivation::SystemSignalActivation(const CDM::SystemSignalActivation & object) : data(new CDM::SystemSignalActivation(object)) {

}

SystemSignalActivation::SystemSignalActivation(const SystemSignalActivation & object) : data(new CDM::SystemSignalActivation(*object.data)) {

}

SystemSignalActivation::~SystemSignalActivation() {

}

void SystemSignalActivation::copyFrom(const SystemSignalActivation & object) {
	data = std::shared_ptr<CDM::SystemSignalActivation>( new CDM::SystemSignalActivation(*object.data));
}

SystemSignalActivation & SystemSignalActivation:: operator=(const SystemSignalActivation & object) {
	copyFrom(object);
	return *this;
}


SystemSignalActivation & SystemSignalActivation::setManifestation(const AlertSignalManifestation & value) {
	data->Manifestation(ConvertToCDM::convert(value));
	return *this;
}


AlertSignalManifestation SystemSignalActivation::getManifestation() const {
	return ConvertFromCDM::convert(data->Manifestation());
}

SystemSignalActivation & SystemSignalActivation::setState(const AlertActivation & value) {
	data->State(ConvertToCDM::convert(value));
	return *this;
}


AlertActivation SystemSignalActivation::getState() const {
	return ConvertFromCDM::convert(data->State());
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

