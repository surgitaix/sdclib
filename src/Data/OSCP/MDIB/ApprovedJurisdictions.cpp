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
 *  ApprovedJurisdictions.cpp
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

#include "OSCLib/Data/OSCP/MDIB/ApprovedJurisdictions.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/InstanceIdentifier.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

ApprovedJurisdictions::ApprovedJurisdictions() : data(Defaults::ApprovedJurisdictions()) {
}

ApprovedJurisdictions::operator CDM::ApprovedJurisdictions() const {
	return *data;
}

ApprovedJurisdictions::ApprovedJurisdictions(const CDM::ApprovedJurisdictions & object) : data(new CDM::ApprovedJurisdictions(object)) {

}

ApprovedJurisdictions::ApprovedJurisdictions(const ApprovedJurisdictions & object) : data(new CDM::ApprovedJurisdictions(*object.data)) {

}

ApprovedJurisdictions::~ApprovedJurisdictions() {

}

void ApprovedJurisdictions::copyFrom(const ApprovedJurisdictions & object) {
	*data = *object.data;
}

ApprovedJurisdictions & ApprovedJurisdictions:: operator=(const ApprovedJurisdictions & object) {
	copyFrom(object);
	return *this;
}


ApprovedJurisdictions & ApprovedJurisdictions::addApprovedJurisdiction(const InstanceIdentifier & value) {
	data->ApprovedJurisdiction().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<InstanceIdentifier> ApprovedJurisdictions::getApprovedJurisdictionLists() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->ApprovedJurisdiction().size());
	for (const auto & value: data->ApprovedJurisdiction()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void ApprovedJurisdictions::clearApprovedJurisdictionLists() {
	data->ApprovedJurisdiction().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

