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
 *  LocalizedText.cpp
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

#include "SDCLib/Data/SDC/MDIB/LocalizedText.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"


namespace SDCLib {
namespace Data {
namespace SDC {


LocalizedText::LocalizedText(
) : data(Defaults::LocalizedTextInit(
)) {}

LocalizedText::operator CDM::LocalizedText() const {
	return *data;
}

LocalizedText::LocalizedText(const CDM::LocalizedText & object) : data(new CDM::LocalizedText(object)) {

}

LocalizedText::LocalizedText(const LocalizedText & object) : data(new CDM::LocalizedText(*object.data)) {

}

LocalizedText::~LocalizedText() {

}

void LocalizedText::copyFrom(const LocalizedText & object) {
	data = std::shared_ptr<CDM::LocalizedText>( new CDM::LocalizedText(*object.data));
}

LocalizedText & LocalizedText:: operator=(const LocalizedText & object) {
	copyFrom(object);
	return *this;
}


LocalizedText & LocalizedText::setRef(const LocalizedTextRef & value) {
	data->setRef(ConvertToCDM::convert(value));
	return *this;
}

bool LocalizedText::getRef(LocalizedTextRef & out) const {
	if (data->getRef().present()) {
		out = ConvertFromCDM::convert(data->getRef().get());
		return true;
	}
	return false;
}

LocalizedTextRef LocalizedText::getRef() const {
	return ConvertFromCDM::convert(data->getRef().get());
}

bool LocalizedText::hasRef() const {
	return data->getRef().present();
}

LocalizedText & LocalizedText::setLang(const xml_schema::Language & value) {
	data->setLang(ConvertToCDM::convert(value));
	return *this;
}

bool LocalizedText::getLang(xml_schema::Language & out) const {
	if (data->getLang().present()) {
		out = ConvertFromCDM::convert(data->getLang().get());
		return true;
	}
	return false;
}

xml_schema::Language LocalizedText::getLang() const {
	return ConvertFromCDM::convert(data->getLang().get());
}

bool LocalizedText::hasLang() const {
	return data->getLang().present();
}

LocalizedText & LocalizedText::setVersion(const ReferencedVersion & value) {
	data->setVersion(ConvertToCDM::convert(value));
	return *this;
}

bool LocalizedText::getVersion(ReferencedVersion & out) const {
	if (data->getVersion().present()) {
		out = ConvertFromCDM::convert(data->getVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion LocalizedText::getVersion() const {
	return ConvertFromCDM::convert(data->getVersion().get());
}

bool LocalizedText::hasVersion() const {
	return data->getVersion().present();
}

LocalizedText & LocalizedText::setTextWidth(const LocalizedTextWidth & value) {
	data->setTextWidth(ConvertToCDM::convert(value));
	return *this;
}

bool LocalizedText::getTextWidth(LocalizedTextWidth & out) const {
	if (data->getTextWidth().present()) {
		out = ConvertFromCDM::convert(data->getTextWidth().get());
		return true;
	}
	return false;
}

LocalizedTextWidth LocalizedText::getTextWidth() const {
	return ConvertFromCDM::convert(data->getTextWidth().get());
}

bool LocalizedText::hasTextWidth() const {
	return data->getTextWidth().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

