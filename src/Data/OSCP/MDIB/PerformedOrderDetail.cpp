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
 *  PerformedOrderDetail.cpp
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

#include "OSCLib/Data/OSCP/MDIB/PerformedOrderDetail.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/InstanceIdentifier.h"
#include "OSCLib/Data/OSCP/MDIB/ClinicalInfo.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/DateTime.h"
#include "OSCLib/Data/OSCP/MDIB/PersonParticipation.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

PerformedOrderDetail::PerformedOrderDetail() : data(Defaults::PerformedOrderDetail()) {
}

PerformedOrderDetail::operator CDM::PerformedOrderDetail() const {
	return *data;
}

PerformedOrderDetail::PerformedOrderDetail(const CDM::PerformedOrderDetail & object) : data(new CDM::PerformedOrderDetail(object)) {

}

PerformedOrderDetail::PerformedOrderDetail(const PerformedOrderDetail & object) : data(new CDM::PerformedOrderDetail(*object.data)) {

}

PerformedOrderDetail::~PerformedOrderDetail() {

}

void PerformedOrderDetail::copyFrom(const PerformedOrderDetail & object) {
	*data = *object.data;
}

PerformedOrderDetail & PerformedOrderDetail:: operator=(const PerformedOrderDetail & object) {
	copyFrom(object);
	return *this;
}


PerformedOrderDetail & PerformedOrderDetail::setStart(const DateTime & value) {
	data->Start(ConvertToCDM::convert(value));
	return *this;
}

bool PerformedOrderDetail::getStart(DateTime & out) const {
	if (data->Start().present()) {
		out = ConvertFromCDM::convert(data->Start().get());
		return true;
	}
	return false;
}

DateTime PerformedOrderDetail::getStart() const {
	return ConvertFromCDM::convert(data->Start().get());
}
	
bool PerformedOrderDetail::hasStart() const {
	return data->Start().present();
}
	
PerformedOrderDetail & PerformedOrderDetail::setEnd(const DateTime & value) {
	data->End(ConvertToCDM::convert(value));
	return *this;
}

bool PerformedOrderDetail::getEnd(DateTime & out) const {
	if (data->End().present()) {
		out = ConvertFromCDM::convert(data->End().get());
		return true;
	}
	return false;
}

DateTime PerformedOrderDetail::getEnd() const {
	return ConvertFromCDM::convert(data->End().get());
}
	
bool PerformedOrderDetail::hasEnd() const {
	return data->End().present();
}
	
PerformedOrderDetail & PerformedOrderDetail::addPerformer(const PersonParticipation & value) {
	data->Performer().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<PersonParticipation> PerformedOrderDetail::getPerformers() const {
	std::vector<PersonParticipation> result;
	result.reserve(data->Performer().size());
	for (const auto & value: data->Performer()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void PerformedOrderDetail::clearPerformers() {
	data->Performer().clear();
}

PerformedOrderDetail & PerformedOrderDetail::addService(const CodedValue & value) {
	data->Service().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CodedValue> PerformedOrderDetail::getServices() const {
	std::vector<CodedValue> result;
	result.reserve(data->Service().size());
	for (const auto & value: data->Service()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void PerformedOrderDetail::clearServices() {
	data->Service().clear();
}

PerformedOrderDetail & PerformedOrderDetail::addImagingProcedure(const ImagingProcedure & value) {
	data->ImagingProcedure().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ImagingProcedure> PerformedOrderDetail::getImagingProcedures() const {
	std::vector<ImagingProcedure> result;
	result.reserve(data->ImagingProcedure().size());
	for (const auto & value: data->ImagingProcedure()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void PerformedOrderDetail::clearImagingProcedures() {
	data->ImagingProcedure().clear();
}

PerformedOrderDetail & PerformedOrderDetail::setFillerOrderNumber(const InstanceIdentifier & value) {
	data->FillerOrderNumber(ConvertToCDM::convert(value));
	return *this;
}


InstanceIdentifier PerformedOrderDetail::getFillerOrderNumber() const {
	return ConvertFromCDM::convert(data->FillerOrderNumber());
}
	
PerformedOrderDetail & PerformedOrderDetail::addResultingClinicalInfo(const ClinicalInfo & value) {
	data->ResultingClinicalInfo().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ClinicalInfo> PerformedOrderDetail::getResultingClinicalInfos() const {
	std::vector<ClinicalInfo> result;
	result.reserve(data->ResultingClinicalInfo().size());
	for (const auto & value: data->ResultingClinicalInfo()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void PerformedOrderDetail::clearResultingClinicalInfos() {
	data->ResultingClinicalInfo().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

