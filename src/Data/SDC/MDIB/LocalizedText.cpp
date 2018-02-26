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

#include "OSCLib/Data/SDC/MDIB/LocalizedText.h"
#include "OSCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/SDC/MDIB/Defaults.h"

#include "osdm.hxx"


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
	data->Ref(ConvertToCDM::convert(value));
	return *this;
}

bool LocalizedText::getRef(LocalizedTextRef & out) const {
	if (data->Ref().present()) {
		out = ConvertFromCDM::convert(data->Ref().get());
		return true;
	}
	return false;
}

LocalizedTextRef LocalizedText::getRef() const {
	return ConvertFromCDM::convert(data->Ref().get());
}
	
bool LocalizedText::hasRef() const {
	return data->Ref().present();
}
	
LocalizedText & LocalizedText::setLang(const xml_schema::Language & value) {
	data->Lang(ConvertToCDM::convert(value));
	return *this;
}

bool LocalizedText::getLang(xml_schema::Language & out) const {
	if (data->Lang().present()) {
		out = ConvertFromCDM::convert(data->Lang().get());
		return true;
	}
	return false;
}

xml_schema::Language LocalizedText::getLang() const {
	return ConvertFromCDM::convert(data->Lang().get());
}
	
bool LocalizedText::hasLang() const {
	return data->Lang().present();
}
	
LocalizedText & LocalizedText::setVersion(const ReferencedVersion & value) {
	data->Version(ConvertToCDM::convert(value));
	return *this;
}

bool LocalizedText::getVersion(ReferencedVersion & out) const {
	if (data->Version().present()) {
		out = ConvertFromCDM::convert(data->Version().get());
		return true;
	}
	return false;
}

ReferencedVersion LocalizedText::getVersion() const {
	return ConvertFromCDM::convert(data->Version().get());
}
	
bool LocalizedText::hasVersion() const {
	return data->Version().present();
}
	
LocalizedText & LocalizedText::setTextWidth(const LocalizedTextWidth & value) {
	data->TextWidth(ConvertToCDM::convert(value));
	return *this;
}

bool LocalizedText::getTextWidth(LocalizedTextWidth & out) const {
	if (data->TextWidth().present()) {
		out = ConvertFromCDM::convert(data->TextWidth().get());
		return true;
	}
	return false;
}

LocalizedTextWidth LocalizedText::getTextWidth() const {
	return ConvertFromCDM::convert(data->TextWidth().get());
}
	
bool LocalizedText::hasTextWidth() const {
	return data->TextWidth().present();
}
	

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

