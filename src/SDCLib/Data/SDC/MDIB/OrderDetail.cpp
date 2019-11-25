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

#include "SDCLib/Data/SDC/MDIB/OrderDetail.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/PersonParticipation.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"
#include "SDCLib/Data/SDC/MDIB/ImagingProcedure.h"

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
	data->setStart(ConvertToCDM::convert(value));
	return *this;
}

bool OrderDetail::getStart(xml_schema::DateTime & out) const {
	if (data->getStart().present()) {
		out = ConvertFromCDM::convert(data->getStart().get());
		return true;
	}
	return false;
}

xml_schema::DateTime OrderDetail::getStart() const {
	return ConvertFromCDM::convert(data->getStart().get());
}

bool OrderDetail::hasStart() const {
	return data->getStart().present();
}

OrderDetail & OrderDetail::setEnd(const xml_schema::DateTime & value) {
	data->setEnd(ConvertToCDM::convert(value));
	return *this;
}

bool OrderDetail::getEnd(xml_schema::DateTime & out) const {
	if (data->getEnd().present()) {
		out = ConvertFromCDM::convert(data->getEnd().get());
		return true;
	}
	return false;
}

xml_schema::DateTime OrderDetail::getEnd() const {
	return ConvertFromCDM::convert(data->getEnd().get());
}

bool OrderDetail::hasEnd() const {
	return data->getEnd().present();
}

OrderDetail & OrderDetail::addPerformer(const PersonParticipation & value) {
	data->getPerformer().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<PersonParticipation> OrderDetail::getPerformerList() const {
	std::vector<PersonParticipation> result;
	result.reserve(data->getPerformer().size());
	for (const auto & value: data->getPerformer()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void OrderDetail::clearPerformerList() {
	data->getPerformer().clear();
}

OrderDetail & OrderDetail::addService(const CodedValue & value) {
	data->getService().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CodedValue> OrderDetail::getServiceList() const {
	std::vector<CodedValue> result;
	result.reserve(data->getService().size());
	for (const auto & value: data->getService()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void OrderDetail::clearServiceList() {
	data->getService().clear();
}

OrderDetail & OrderDetail::addImagingProcedure(const ImagingProcedure & value) {
	data->getImagingProcedure().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ImagingProcedure> OrderDetail::getImagingProcedureList() const {
	std::vector<ImagingProcedure> result;
	result.reserve(data->getImagingProcedure().size());
	for (const auto & value: data->getImagingProcedure()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void OrderDetail::clearImagingProcedureList() {
	data->getImagingProcedure().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

