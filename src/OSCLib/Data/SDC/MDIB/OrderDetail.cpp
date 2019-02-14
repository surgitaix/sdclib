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
 *  OrderDetail.cpp
 *
 *  @Copyright (C) 2015, SurgiTAIX AG
 *  Author: besting, buerger, roehser
 */

/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 *
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "OSCLib/Data/SDC/MDIB/OrderDetail.h"
#include "OSCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/SDC/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/SDC/MDIB/PersonParticipation.h"
#include "OSCLib/Data/SDC/MDIB/CodedValue.h"
#include "OSCLib/Data/SDC/MDIB/ImagingProcedure.h"

namespace SDCLib {
namespace Data {
namespace SDC {


OrderDetail::OrderDetail(
) : data(Defaults::OrderDetailInit(
)) {}

OrderDetail::operator CDM::OrderDetail() const {
	return *data;
}

OrderDetail::OrderDetail(const CDM::OrderDetail & object) : data(new CDM::OrderDetail(object)) {

}

OrderDetail::OrderDetail(const OrderDetail & object) : data(new CDM::OrderDetail(*object.data)) {

}

OrderDetail::~OrderDetail() {

}

void OrderDetail::copyFrom(const OrderDetail & object) {
	data = std::shared_ptr<CDM::OrderDetail>( new CDM::OrderDetail(*object.data));
}

OrderDetail & OrderDetail:: operator=(const OrderDetail & object) {
	copyFrom(object);
	return *this;
}


OrderDetail & OrderDetail::setStart(const xml_schema::DateTime & value) {
	data->Start(ConvertToCDM::convert(value));
	return *this;
}

bool OrderDetail::getStart(xml_schema::DateTime & out) const {
	if (data->Start().present()) {
		out = ConvertFromCDM::convert(data->Start().get());
		return true;
	}
	return false;
}

xml_schema::DateTime OrderDetail::getStart() const {
	return ConvertFromCDM::convert(data->Start().get());
}

bool OrderDetail::hasStart() const {
	return data->Start().present();
}

OrderDetail & OrderDetail::setEnd(const xml_schema::DateTime & value) {
	data->End(ConvertToCDM::convert(value));
	return *this;
}

bool OrderDetail::getEnd(xml_schema::DateTime & out) const {
	if (data->End().present()) {
		out = ConvertFromCDM::convert(data->End().get());
		return true;
	}
	return false;
}

xml_schema::DateTime OrderDetail::getEnd() const {
	return ConvertFromCDM::convert(data->End().get());
}

bool OrderDetail::hasEnd() const {
	return data->End().present();
}

OrderDetail & OrderDetail::addPerformer(const PersonParticipation & value) {
	data->Performer().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<PersonParticipation> OrderDetail::getPerformerList() const {
	std::vector<PersonParticipation> result;
	result.reserve(data->Performer().size());
	for (const auto & value: data->Performer()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void OrderDetail::clearPerformerList() {
	data->Performer().clear();
}

OrderDetail & OrderDetail::addService(const CodedValue & value) {
	data->Service().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CodedValue> OrderDetail::getServiceList() const {
	std::vector<CodedValue> result;
	result.reserve(data->Service().size());
	for (const auto & value: data->Service()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void OrderDetail::clearServiceList() {
	data->Service().clear();
}

OrderDetail & OrderDetail::addImagingProcedure(const ImagingProcedure & value) {
	data->ImagingProcedure().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ImagingProcedure> OrderDetail::getImagingProcedureList() const {
	std::vector<ImagingProcedure> result;
	result.reserve(data->ImagingProcedure().size());
	for (const auto & value: data->ImagingProcedure()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void OrderDetail::clearImagingProcedureList() {
	data->ImagingProcedure().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

