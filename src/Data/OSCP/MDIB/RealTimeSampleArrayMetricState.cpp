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
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayValue.h"
#include "OSCLib/Data/OSCP/MDIB/CalibrationInfo.h"
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


RealTimeSampleArrayMetricState & RealTimeSampleArrayMetricState::setHandle(const std::string & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayMetricState::getHandle(std::string & out) const {
	if (data->Handle().present()) {
		out = ConvertFromCDM::convert(data->Handle().get());
		return true;
	}
	return false;
}

std::string RealTimeSampleArrayMetricState::getHandle() const {
	return ConvertFromCDM::convert(data->Handle().get());
}
	
bool RealTimeSampleArrayMetricState::hasHandle() const {
	return data->Handle().present();
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
	
RealTimeSampleArrayMetricState & RealTimeSampleArrayMetricState::setComponentActivationState(const ComponentActivation & value) {
	data->ComponentActivationState(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayMetricState::getComponentActivationState(ComponentActivation & out) const {
	if (data->ComponentActivationState().present()) {
		out = ConvertFromCDM::convert(data->ComponentActivationState().get());
		return true;
	}
	return false;
}

ComponentActivation RealTimeSampleArrayMetricState::getComponentActivationState() const {
	return ConvertFromCDM::convert(data->ComponentActivationState().get());
}
	
bool RealTimeSampleArrayMetricState::hasComponentActivationState() const {
	return data->ComponentActivationState().present();
}
	
RealTimeSampleArrayMetricState & RealTimeSampleArrayMetricState::setCalibrationInfo(const CalibrationInfo & value) {
	data->CalibrationInfo(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayMetricState::getCalibrationInfo(CalibrationInfo & out) const {
	if (data->CalibrationInfo().present()) {
		out = ConvertFromCDM::convert(data->CalibrationInfo().get());
		return true;
	}
	return false;
}

CalibrationInfo RealTimeSampleArrayMetricState::getCalibrationInfo() const {
	return ConvertFromCDM::convert(data->CalibrationInfo().get());
}
	
bool RealTimeSampleArrayMetricState::hasCalibrationInfo() const {
	return data->CalibrationInfo().present();
}
	
RealTimeSampleArrayMetricState & RealTimeSampleArrayMetricState::setOperatingHours(const int & value) {
	data->OperatingHours(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayMetricState::getOperatingHours(int & out) const {
	if (data->OperatingHours().present()) {
		out = ConvertFromCDM::convert(data->OperatingHours().get());
		return true;
	}
	return false;
}

int RealTimeSampleArrayMetricState::getOperatingHours() const {
	return ConvertFromCDM::convert(data->OperatingHours().get());
}
	
bool RealTimeSampleArrayMetricState::hasOperatingHours() const {
	return data->OperatingHours().present();
}
	
RealTimeSampleArrayMetricState & RealTimeSampleArrayMetricState::setOperatingCycles(const int & value) {
	data->OperatingCycles(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayMetricState::getOperatingCycles(int & out) const {
	if (data->OperatingCycles().present()) {
		out = ConvertFromCDM::convert(data->OperatingCycles().get());
		return true;
	}
	return false;
}

int RealTimeSampleArrayMetricState::getOperatingCycles() const {
	return ConvertFromCDM::convert(data->OperatingCycles().get());
}
	
bool RealTimeSampleArrayMetricState::hasOperatingCycles() const {
	return data->OperatingCycles().present();
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

