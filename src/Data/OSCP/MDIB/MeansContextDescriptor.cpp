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
 *  MeansContextDescriptor.cpp
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

#include "OSCLib/Data/OSCP/MDIB/MeansContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"


namespace OSCLib {
namespace Data {
namespace OSCP {

MeansContextDescriptor::MeansContextDescriptor() : data(Defaults::MeansContextDescriptor()) {
}

MeansContextDescriptor::operator CDM::MeansContextDescriptor() const {
	return *data;
}

MeansContextDescriptor::MeansContextDescriptor(const CDM::MeansContextDescriptor & object) : data(new CDM::MeansContextDescriptor(object)) {

}

MeansContextDescriptor::MeansContextDescriptor(const MeansContextDescriptor & object) : data(new CDM::MeansContextDescriptor(*object.data)) {

}

MeansContextDescriptor::~MeansContextDescriptor() {

}

void MeansContextDescriptor::copyFrom(const MeansContextDescriptor & object) {
	*data = *object.data;
}

MeansContextDescriptor & MeansContextDescriptor:: operator=(const MeansContextDescriptor & object) {
	copyFrom(object);
	return *this;
}



} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

