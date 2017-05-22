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
 *  RealTimeSampleArrayMetricState.cpp
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

#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayValue.h"
#include "OSCLib/Data/OSCP/MDIB/Duration.h"
#include "OSCLib/Data/OSCP/MDIB/ReferencedVersion.h"
#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

RealTimeSampleArrayMetricState::RealTimeSampleArrayMetricState() : data(Defaults::RealTimeSampleArrayMetricState()) {
}

RealTimeSampleArrayMetricState::operator CDM::RealTimeSampleArrayMetricState() const {
	return *data;
}

RealTimeSampleArrayMetricState::RealTimeSampleArrayMetricState(const CDM::RealTimeSampleArrayMetricState & object) : data(new CDM::RealTimeSampleArrayMetricState(object)) {

}

RealTimeSampleArrayMetricState::RealTimeSampleArrayMetricState(const RealTimeSampleArrayMetricState & object) : data(new CDM::RealTimeSampleArrayMetricState(*object.data)) {

}

RealTimeSampleArrayMetricState::~RealTimeSampleArrayMetricState() {

}

void RealTimeSampleArrayMetricState::copyFrom(const RealTimeSampleArrayMetricState & object) {
	*data = *object.data;
}

RealTimeSampleArrayMetricState & RealTimeSampleArrayMetricState:: operator=(const RealTimeSampleArrayMetricState & object) {
	copyFrom(object);
	return *this;
}


RealTimeSampleArrayMetricState & RealTimeSampleArrayMetricState::setDescriptorVersion(const ReferencedVersion & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayMetricState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion RealTimeSampleArrayMetricState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool RealTimeSampleArrayMetricState::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
RealTimeSampleArrayMetricState & RealTimeSampleArrayMetricState::setDescriptorHandle(const std::string & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


std::string RealTimeSampleArrayMetricState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
}
	
RealTimeSampleArrayMetricState & RealTimeSampleArrayMetricState::setStateVersion(const VersionCounter & value) {
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayMetricState::getStateVersion(VersionCounter & out) const {
	if (data->StateVersion().present()) {
		out = ConvertFromCDM::convert(data->StateVersion().get());
		return true;
	}
	return false;
}

VersionCounter RealTimeSampleArrayMetricState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion().get());
}
	
bool RealTimeSampleArrayMetricState::hasStateVersion() const {
	return data->StateVersion().present();
}
	
RealTimeSampleArrayMetricState & RealTimeSampleArrayMetricState::setActivationState(const ComponentActivation & value) {
	data->ActivationState(ConvertToCDM::convert(value));
	return *this;
}


ComponentActivation RealTimeSampleArrayMetricState::getActivationState() const {
	return ConvertFromCDM::convert(data->ActivationState());
}
	
RealTimeSampleArrayMetricState & RealTimeSampleArrayMetricState::setLifeTimePeriod(const Duration & value) {
	data->LifeTimePeriod(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayMetricState::getLifeTimePeriod(Duration & out) const {
	if (data->LifeTimePeriod().present()) {
		out = ConvertFromCDM::convert(data->LifeTimePeriod().get());
		return true;
	}
	return false;
}

Duration RealTimeSampleArrayMetricState::getLifeTimePeriod() const {
	return ConvertFromCDM::convert(data->LifeTimePeriod().get());
}
	
bool RealTimeSampleArrayMetricState::hasLifeTimePeriod() const {
	return data->LifeTimePeriod().present();
}
	
RealTimeSampleArrayMetricState & RealTimeSampleArrayMetricState::setActiveDeterminationPeriod(const Duration & value) {
	data->ActiveDeterminationPeriod(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayMetricState::getActiveDeterminationPeriod(Duration & out) const {
	if (data->ActiveDeterminationPeriod().present()) {
		out = ConvertFromCDM::convert(data->ActiveDeterminationPeriod().get());
		return true;
	}
	return false;
}

Duration RealTimeSampleArrayMetricState::getActiveDeterminationPeriod() const {
	return ConvertFromCDM::convert(data->ActiveDeterminationPeriod().get());
}
	
bool RealTimeSampleArrayMetricState::hasActiveDeterminationPeriod() const {
	return data->ActiveDeterminationPeriod().present();
}
	
RealTimeSampleArrayMetricState & RealTimeSampleArrayMetricState::setObservedValue(const RealTimeSampleArrayValue & value) {
	data->ObservedValue(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayMetricState::getObservedValue(RealTimeSampleArrayValue & out) const {
	if (data->ObservedValue().present()) {
		out = ConvertFromCDM::convert(data->ObservedValue().get());
		return true;
	}
	return false;
}

RealTimeSampleArrayValue RealTimeSampleArrayMetricState::getObservedValue() const {
	return ConvertFromCDM::convert(data->ObservedValue().get());
}
	
bool RealTimeSampleArrayMetricState::hasObservedValue() const {
	return data->ObservedValue().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

