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
 *  Timestamp.cpp
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

#include "OSCLib/Data/OSCP/MDIB/Timestamp.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"


namespace OSCLib {
namespace Data {
namespace OSCP {

Timestamp::Timestamp() : data(Defaults::Timestamp()) {
}

Timestamp::operator CDM::Timestamp() const {
	return *data;
}

Timestamp::Timestamp(const CDM::Timestamp & object) : data(new CDM::Timestamp(object)) {

}

Timestamp::Timestamp(const Timestamp & object) : data(new CDM::Timestamp(*object.data)) {

}

Timestamp::~Timestamp() {

}

void Timestamp::copyFrom(const Timestamp & object) {
	*data = *object.data;
}

Timestamp & Timestamp:: operator=(const Timestamp & object) {
	copyFrom(object);
	return *this;
}

long long Timestamp::get() const {
	return *data;
}
	
Timestamp & Timestamp::set(const long long & value) {
	*data = value;
	return *this;
} 
	


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

