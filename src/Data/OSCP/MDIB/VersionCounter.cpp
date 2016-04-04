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
 *  VersionCounter.cpp
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

#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"


namespace OSCLib {
namespace Data {
namespace OSCP {

VersionCounter::VersionCounter() : data(Defaults::VersionCounter()) {
}

VersionCounter::operator CDM::VersionCounter() const {
	return *data;
}

VersionCounter::VersionCounter(const CDM::VersionCounter & object) : data(new CDM::VersionCounter(object)) {

}

VersionCounter::VersionCounter(const VersionCounter & object) : data(new CDM::VersionCounter(*object.data)) {

}

VersionCounter::~VersionCounter() {

}

void VersionCounter::copyFrom(const VersionCounter & object) {
	*data = *object.data;
}

VersionCounter & VersionCounter:: operator=(const VersionCounter & object) {
	copyFrom(object);
	return *this;
}

long long VersionCounter::get() const {
	return *data;
}
	
VersionCounter & VersionCounter::set(const long long & value) {
	*data = value;
	return *this;
} 
	


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

