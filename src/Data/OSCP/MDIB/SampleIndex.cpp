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
 *  SampleIndex.cpp
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

#include "OSCLib/Data/OSCP/MDIB/SampleIndex.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"


namespace OSCLib {
namespace Data {
namespace OSCP {

SampleIndex::SampleIndex() : data(Defaults::SampleIndex()) {
}

SampleIndex::operator CDM::SampleIndex() const {
	return *data;
}

SampleIndex::SampleIndex(const CDM::SampleIndex & object) : data(new CDM::SampleIndex(object)) {

}

SampleIndex::SampleIndex(const SampleIndex & object) : data(new CDM::SampleIndex(*object.data)) {

}

SampleIndex::~SampleIndex() {

}

void SampleIndex::copyFrom(const SampleIndex & object) {
	*data = *object.data;
}

SampleIndex & SampleIndex:: operator=(const SampleIndex & object) {
	copyFrom(object);
	return *this;
}

int SampleIndex::get() const {
	return *data;
}
	
SampleIndex & SampleIndex::set(const int & value) {
	*data = value;
	return *this;
} 
	


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

