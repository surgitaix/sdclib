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
 *  Translation.cpp
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

#include "SDCLib/Data/SDC/MDIB/Translation.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"


namespace SDCLib {
namespace Data {
namespace SDC {


Translation::Translation(
		CodeIdentifier code
) : data(Defaults::TranslationInit(
		code
)) {}

Translation::operator CDM::Translation() const {
	return *data;
}

Translation::Translation(const CDM::Translation & object) : data(new CDM::Translation(object)) {

}

Translation::Translation(const Translation & object) : data(new CDM::Translation(*object.data)) {

}

Translation::~Translation() {

}

void Translation::copyFrom(const Translation & object) {
	data = std::shared_ptr<CDM::Translation>( new CDM::Translation(*object.data));
}

Translation & Translation:: operator=(const Translation & object) {
	copyFrom(object);
	return *this;
}


Translation & Translation::setCode(const CodeIdentifier & value) {
	data->setCode(ConvertToCDM::convert(value));
	return *this;
}


CodeIdentifier Translation::getCode() const {
	return ConvertFromCDM::convert(data->getCode());
}

Translation & Translation::setCodingSystem(const xml_schema::Uri & value) {
	data->setCodingSystem(ConvertToCDM::convert(value));
	return *this;
}

bool Translation::getCodingSystem(xml_schema::Uri & out) const {
	if (data->getCodingSystem().present()) {
		out = ConvertFromCDM::convert(data->getCodingSystem().get());
		return true;
	}
	return false;
}

xml_schema::Uri Translation::getCodingSystem() const {
	return ConvertFromCDM::convert(data->getCodingSystem().get());
}

bool Translation::hasCodingSystem() const {
	return data->getCodingSystem().present();
}

Translation & Translation::setCodingSystemVersion(const std::string & value) {
	data->setCodingSystemVersion(ConvertToCDM::convert(value));
	return *this;
}

bool Translation::getCodingSystemVersion(std::string & out) const {
	if (data->getCodingSystemVersion().present()) {
		out = ConvertFromCDM::convert(data->getCodingSystemVersion().get());
		return true;
	}
	return false;
}

std::string Translation::getCodingSystemVersion() const {
	return ConvertFromCDM::convert(data->getCodingSystemVersion().get());
}

bool Translation::hasCodingSystemVersion() const {
	return data->getCodingSystemVersion().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

