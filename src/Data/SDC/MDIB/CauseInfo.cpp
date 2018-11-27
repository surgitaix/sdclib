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
 *  CauseInfo.cpp
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

#include "OSCLib/Data/SDC/MDIB/CauseInfo.h"
#include "OSCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/SDC/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/SDC/MDIB/RemedyInfo.h"
#include "OSCLib/Data/SDC/MDIB/LocalizedText.h"

namespace SDCLib {
namespace Data {
namespace SDC {


CauseInfo::CauseInfo(
) : data(Defaults::CauseInfoInit(
)) {}

CauseInfo::operator CDM::CauseInfo() const {
	return *data;
}

CauseInfo::CauseInfo(const CDM::CauseInfo & object) : data(new CDM::CauseInfo(object)) {

}

CauseInfo::CauseInfo(const CauseInfo & object) : data(new CDM::CauseInfo(*object.data)) {

}

CauseInfo::~CauseInfo() {

}

void CauseInfo::copyFrom(const CauseInfo & object) {
	data = std::shared_ptr<CDM::CauseInfo>( new CDM::CauseInfo(*object.data));
}

CauseInfo & CauseInfo:: operator=(const CauseInfo & object) {
	copyFrom(object);
	return *this;
}


CauseInfo & CauseInfo::setRemedyInfo(const RemedyInfo & value) {
	data->RemedyInfo(ConvertToCDM::convert(value));
	return *this;
}

bool CauseInfo::getRemedyInfo(RemedyInfo & out) const {
	if (data->RemedyInfo().present()) {
		out = ConvertFromCDM::convert(data->RemedyInfo().get());
		return true;
	}
	return false;
}

RemedyInfo CauseInfo::getRemedyInfo() const {
	return ConvertFromCDM::convert(data->RemedyInfo().get());
}

bool CauseInfo::hasRemedyInfo() const {
	return data->RemedyInfo().present();
}

CauseInfo & CauseInfo::addDescription(const LocalizedText & value) {
	data->Description().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> CauseInfo::getDescriptionList() const {
	std::vector<LocalizedText> result;
	result.reserve(data->Description().size());
	for (const auto & value: data->Description()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void CauseInfo::clearDescriptionList() {
	data->Description().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

