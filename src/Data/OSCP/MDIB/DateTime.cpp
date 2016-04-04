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
 *  DateTime.cpp
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

#include "OSCLib/Data/OSCP/MDIB/DateTime.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"


namespace OSCLib {
namespace Data {
namespace OSCP {

DateTime::DateTime() : data(Defaults::DateTime()) {
}

DateTime::operator CDM::DateTime() const {
	return *data;
}

DateTime::DateTime(const CDM::DateTime & object) : data(new CDM::DateTime(object)) {

}

DateTime::DateTime(const DateTime & object) : data(new CDM::DateTime(*object.data)) {

}

DateTime::~DateTime() {

}

void DateTime::copyFrom(const DateTime & object) {
	*data = *object.data;
}

DateTime & DateTime:: operator=(const DateTime & object) {
	copyFrom(object);
	return *this;
}


DateTime & DateTime::setyear(const int & value) {
	data->year(ConvertToCDM::convert(value));
	return *this;
}


int DateTime::getyear() const {
	return ConvertFromCDM::convert(data->year());
}
	
DateTime & DateTime::setmonth(const unsigned short & value) {
	data->month(ConvertToCDM::convert(value));
	return *this;
}


unsigned short DateTime::getmonth() const {
	return ConvertFromCDM::convert(data->month());
}
	
DateTime & DateTime::setday(const unsigned short & value) {
	data->day(ConvertToCDM::convert(value));
	return *this;
}


unsigned short DateTime::getday() const {
	return ConvertFromCDM::convert(data->day());
}
	
DateTime & DateTime::sethours(const unsigned short & value) {
	data->hours(ConvertToCDM::convert(value));
	return *this;
}


unsigned short DateTime::gethours() const {
	return ConvertFromCDM::convert(data->hours());
}
	
DateTime & DateTime::setminutes(const unsigned short & value) {
	data->minutes(ConvertToCDM::convert(value));
	return *this;
}


unsigned short DateTime::getminutes() const {
	return ConvertFromCDM::convert(data->minutes());
}
	
DateTime & DateTime::setseconds(const double & value) {
	data->seconds(ConvertToCDM::convert(value));
	return *this;
}


double DateTime::getseconds() const {
	return ConvertFromCDM::convert(data->seconds());
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

