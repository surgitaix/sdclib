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
 *  Duration.cpp
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

#include "OSCLib/Data/OSCP/MDIB/Duration.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"


namespace OSCLib {
namespace Data {
namespace OSCP {

Duration::Duration() : data(Defaults::Duration()) {
}

Duration::operator CDM::Duration() const {
	return *data;
}

Duration::Duration(const CDM::Duration & object) : data(new CDM::Duration(object)) {

}

Duration::Duration(const Duration & object) : data(new CDM::Duration(*object.data)) {

}

Duration::~Duration() {

}

void Duration::copyFrom(const Duration & object) {
	*data = *object.data;
}

Duration & Duration:: operator=(const Duration & object) {
	copyFrom(object);
	return *this;
}


Duration & Duration::setnegative(const bool & value) {
	data->negative(ConvertToCDM::convert(value));
	return *this;
}


bool Duration::getnegative() const {
	return ConvertFromCDM::convert(data->negative());
}
	
Duration & Duration::setyears(const unsigned int & value) {
	data->years(ConvertToCDM::convert(value));
	return *this;
}


unsigned int Duration::getyears() const {
	return ConvertFromCDM::convert(data->years());
}
	
Duration & Duration::setmonths(const unsigned int & value) {
	data->months(ConvertToCDM::convert(value));
	return *this;
}


unsigned int Duration::getmonths() const {
	return ConvertFromCDM::convert(data->months());
}
	
Duration & Duration::setdays(const unsigned int & value) {
	data->days(ConvertToCDM::convert(value));
	return *this;
}


unsigned int Duration::getdays() const {
	return ConvertFromCDM::convert(data->days());
}
	
Duration & Duration::sethours(const unsigned int & value) {
	data->hours(ConvertToCDM::convert(value));
	return *this;
}


unsigned int Duration::gethours() const {
	return ConvertFromCDM::convert(data->hours());
}
	
Duration & Duration::setminutes(const unsigned int & value) {
	data->minutes(ConvertToCDM::convert(value));
	return *this;
}


unsigned int Duration::getminutes() const {
	return ConvertFromCDM::convert(data->minutes());
}
	
Duration & Duration::setseconds(const double & value) {
	data->seconds(ConvertToCDM::convert(value));
	return *this;
}


double Duration::getseconds() const {
	return ConvertFromCDM::convert(data->seconds());
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

