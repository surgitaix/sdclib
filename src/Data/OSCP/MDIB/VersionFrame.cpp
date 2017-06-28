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
 *  VersionFrame.cpp
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

#include "OSCLib/Data/OSCP/MDIB/VersionFrame.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"


namespace OSCLib {
namespace Data {
namespace OSCP {

VersionFrame::VersionFrame() : data(Defaults::VersionFrame()) {
}

VersionFrame::operator CDM::VersionFrame() const {
	return *data;
}

VersionFrame::VersionFrame(const CDM::VersionFrame & object) : data(new CDM::VersionFrame(object)) {

}

VersionFrame::VersionFrame(const VersionFrame & object) : data(new CDM::VersionFrame(*object.data)) {

}

VersionFrame::~VersionFrame() {

}

void VersionFrame::copyFrom(const VersionFrame & object) {
	*data = *object.data;
}

VersionFrame & VersionFrame:: operator=(const VersionFrame & object) {
	copyFrom(object);
	return *this;
}


VersionFrame & VersionFrame::setStart(const ReferencedVersion & value) {
	data->Start(ConvertToCDM::convert(value));
	return *this;
}


ReferencedVersion VersionFrame::getStart() const {
	return ConvertFromCDM::convert(data->Start());
}
	
VersionFrame & VersionFrame::setEnd(const ReferencedVersion & value) {
	data->End(ConvertToCDM::convert(value));
	return *this;
}


ReferencedVersion VersionFrame::getEnd() const {
	return ConvertFromCDM::convert(data->End());
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

