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
 *  InvocationInfo.cpp
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

#include "OSCLib/Data/OSCP/MDIB/InvocationInfo.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/LocalizedText.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

InvocationInfo::InvocationInfo() : data(Defaults::InvocationInfo()) {
}

InvocationInfo::operator CDM::InvocationInfo() const {
	return *data;
}

InvocationInfo::InvocationInfo(const CDM::InvocationInfo & object) : data(new CDM::InvocationInfo(object)) {

}

InvocationInfo::InvocationInfo(const InvocationInfo & object) : data(new CDM::InvocationInfo(*object.data)) {

}

InvocationInfo::~InvocationInfo() {

}

void InvocationInfo::copyFrom(const InvocationInfo & object) {
	*data = *object.data;
}

InvocationInfo & InvocationInfo:: operator=(const InvocationInfo & object) {
	copyFrom(object);
	return *this;
}


InvocationInfo & InvocationInfo::setTransactionId(const TransactionId & value) {
	data->TransactionId(ConvertToCDM::convert(value));
	return *this;
}


TransactionId InvocationInfo::getTransactionId() const {
	return ConvertFromCDM::convert(data->TransactionId());
}
	
InvocationInfo & InvocationInfo::setInvocationState(const InvocationState & value) {
	data->InvocationState(ConvertToCDM::convert(value));
	return *this;
}


InvocationState InvocationInfo::getInvocationState() const {
	return ConvertFromCDM::convert(data->InvocationState());
}
	
InvocationInfo & InvocationInfo::setInvocationError(const InvocationError & value) {
	data->InvocationError(ConvertToCDM::convert(value));
	return *this;
}

bool InvocationInfo::getInvocationError(InvocationError & out) const {
	if (data->InvocationError().present()) {
		out = ConvertFromCDM::convert(data->InvocationError().get());
		return true;
	}
	return false;
}

InvocationError InvocationInfo::getInvocationError() const {
	return ConvertFromCDM::convert(data->InvocationError().get());
}
	
bool InvocationInfo::hasInvocationError() const {
	return data->InvocationError().present();
}
	
InvocationInfo & InvocationInfo::addInvocationErrorMessage(const LocalizedText & value) {
	data->InvocationErrorMessage().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> InvocationInfo::getInvocationErrorMessages() const {
	std::vector<LocalizedText> result;
	result.reserve(data->InvocationErrorMessage().size());
	for (const auto & value: data->InvocationErrorMessage()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void InvocationInfo::clearInvocationErrorMessages() {
	data->InvocationErrorMessage().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

