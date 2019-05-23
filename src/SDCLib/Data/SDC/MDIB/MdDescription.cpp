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
 *  MdDescription.cpp
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

#include "SDCLib/Data/SDC/MDIB/MdDescription.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/MdsDescriptor.h"

namespace SDCLib {
namespace Data {
namespace SDC {


MdDescription::MdDescription(
) : data(Defaults::MdDescriptionInit(
)) {}

MdDescription::operator CDM::MdDescription() const {
	return *data;
}

MdDescription::MdDescription(const CDM::MdDescription & object) : data(new CDM::MdDescription(object)) {

}

MdDescription::MdDescription(const MdDescription & object) : data(new CDM::MdDescription(*object.data)) {

}

MdDescription::~MdDescription() {

}

void MdDescription::copyFrom(const MdDescription & object) {
	data = std::shared_ptr<CDM::MdDescription>( new CDM::MdDescription(*object.data));
}

MdDescription & MdDescription:: operator=(const MdDescription & object) {
	copyFrom(object);
	return *this;
}


MdDescription & MdDescription::setDescriptionVersion(const VersionCounter & value) {
	data->DescriptionVersion(ConvertToCDM::convert(value));
	return *this;
}

bool MdDescription::getDescriptionVersion(VersionCounter & out) const {
	if (data->DescriptionVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptionVersion().get());
		return true;
	}
	return false;
}

VersionCounter MdDescription::getDescriptionVersion() const {
	return ConvertFromCDM::convert(data->DescriptionVersion().get());
}

bool MdDescription::hasDescriptionVersion() const {
	return data->DescriptionVersion().present();
}

MdDescription & MdDescription::addMds(const MdsDescriptor & value) {
	data->Mds().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<MdsDescriptor> MdDescription::getMdsList() const {
	std::vector<MdsDescriptor> result;
	result.reserve(data->Mds().size());
	for (const auto & value: data->Mds()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void MdDescription::clearMdsList() {
	data->Mds().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

