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
 *  Author: besting, roehser
 */
 
/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 * 
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "OSCLib/Data/OSCP/MDIB/LocalizedText.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"


namespace OSCLib {
namespace Data {
namespace OSCP {

LocalizedText::LocalizedText() : data(Defaults::LocalizedText()) {
}

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
	*data = *object.data;
}

LocalizedText & LocalizedText:: operator=(const LocalizedText & object) {
	copyFrom(object);
	return *this;
}


LocalizedText & LocalizedText::setRef(const LocalizedTextRef & value) {
	data->Ref(ConvertToCDM::convert(value));
	return *this;
}


LocalizedTextRef LocalizedText::getRef() const {
	return ConvertFromCDM::convert(data->Ref());
}
	
LocalizedText & LocalizedText::setLang(const language & value) {
	data->Lang(ConvertToCDM::convert(value));
	return *this;
}


language LocalizedText::getLang() const {
	return ConvertFromCDM::convert(data->Lang());
}
	
LocalizedText & LocalizedText::setVersion(const ReferencedVersion & value) {
	data->Version(ConvertToCDM::convert(value));
	return *this;
}


ReferencedVersion LocalizedText::getVersion() const {
	return ConvertFromCDM::convert(data->Version());
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

