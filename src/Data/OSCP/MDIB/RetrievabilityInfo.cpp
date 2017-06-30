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
 *  RetrievabilityInfo.cpp
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

#include "OSCLib/Data/OSCP/MDIB/RetrievabilityInfo.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"


namespace OSCLib {
namespace Data {
namespace OSCP {

RetrievabilityInfo::RetrievabilityInfo() : data(Defaults::RetrievabilityInfo()) {
}

RetrievabilityInfo::operator CDM::RetrievabilityInfo() const {
	return *data;
}

RetrievabilityInfo::RetrievabilityInfo(const CDM::RetrievabilityInfo & object) : data(new CDM::RetrievabilityInfo(object)) {

}

RetrievabilityInfo::RetrievabilityInfo(const RetrievabilityInfo & object) : data(new CDM::RetrievabilityInfo(*object.data)) {

}

RetrievabilityInfo::~RetrievabilityInfo() {

}

void RetrievabilityInfo::copyFrom(const RetrievabilityInfo & object) {
	*data = *object.data;
}

RetrievabilityInfo & RetrievabilityInfo:: operator=(const RetrievabilityInfo & object) {
	copyFrom(object);
	return *this;
}


RetrievabilityInfo & RetrievabilityInfo::setMethod(const RetrievabilityMethod & value) {
	data->Method(ConvertToCDM::convert(value));
	return *this;
}


RetrievabilityMethod RetrievabilityInfo::getMethod() const {
	return ConvertFromCDM::convert(data->Method());
}
	
RetrievabilityInfo & RetrievabilityInfo::setUpdatePeriod(const xml_schema::Duration & value) {
	data->UpdatePeriod(ConvertToCDM::convert(value));
	return *this;
}


xml_schema::Duration RetrievabilityInfo::getUpdatePeriod() const {
	return ConvertFromCDM::convert(data->UpdatePeriod());
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

