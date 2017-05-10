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
 *  ReferencedVersion.cpp
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

#include "OSCLib/Data/OSCP/MDIB/ReferencedVersion.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"


namespace OSCLib {
namespace Data {
namespace OSCP {

ReferencedVersion::ReferencedVersion() : data(Defaults::ReferencedVersion()) {
}

ReferencedVersion::operator CDM::ReferencedVersion() const {
	return *data;
}

ReferencedVersion::ReferencedVersion(const CDM::ReferencedVersion & object) : data(new CDM::ReferencedVersion(object)) {

}

ReferencedVersion::ReferencedVersion(const ReferencedVersion & object) : data(new CDM::ReferencedVersion(*object.data)) {

}

ReferencedVersion::~ReferencedVersion() {

}

void ReferencedVersion::copyFrom(const ReferencedVersion & object) {
	*data = *object.data;
}

ReferencedVersion & ReferencedVersion:: operator=(const ReferencedVersion & object) {
	copyFrom(object);
	return *this;
}

long long ReferencedVersion::get() const {
	return *data;
}
	
ReferencedVersion & ReferencedVersion::set(const long long & value) {
	*data = value;
	return *this;
} 
	


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

