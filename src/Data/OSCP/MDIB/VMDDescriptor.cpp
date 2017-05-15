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
 *  VMDDescriptor.cpp
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

#include "OSCLib/Data/OSCP/MDIB/VMDDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/AlertSystemDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ChannelDescriptor.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

VMDDescriptor::VMDDescriptor() : data(Defaults::VMDDescriptor()) {
}

VMDDescriptor::operator CDM::VMDDescriptor() const {
	return *data;
}

VMDDescriptor::VMDDescriptor(const CDM::VMDDescriptor & object) : data(new CDM::VMDDescriptor(object)) {

}

VMDDescriptor::VMDDescriptor(const VMDDescriptor & object) : data(new CDM::VMDDescriptor(*object.data)) {

}

VMDDescriptor::~VMDDescriptor() {

}

void VMDDescriptor::copyFrom(const VMDDescriptor & object) {
	*data = *object.data;
}

VMDDescriptor & VMDDescriptor:: operator=(const VMDDescriptor & object) {
	copyFrom(object);
	return *this;
}


VMDDescriptor & VMDDescriptor::setAlertSystem(const AlertSystemDescriptor & value) {
	data->AlertSystem(ConvertToCDM::convert(value));
	return *this;
}

bool VMDDescriptor::getAlertSystem(AlertSystemDescriptor & out) const {
	if (data->AlertSystem().present()) {
		out = ConvertFromCDM::convert(data->AlertSystem().get());
		return true;
	}
	return false;
}

AlertSystemDescriptor VMDDescriptor::getAlertSystem() const {
	return ConvertFromCDM::convert(data->AlertSystem().get());
}
	
bool VMDDescriptor::hasAlertSystem() const {
	return data->AlertSystem().present();
}
	
VMDDescriptor & VMDDescriptor::addChannel(const ChannelDescriptor & value) {
	data->Channel().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ChannelDescriptor> VMDDescriptor::getChannels() const {
	std::vector<ChannelDescriptor> result;
	result.reserve(data->Channel().size());
	for (const auto & value: data->Channel()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void VMDDescriptor::clearChannels() {
	data->Channel().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

