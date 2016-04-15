/*
 * DurationWrapper.cpp
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#include "Poco/Timespan.h"
#include "Poco/Timestamp.h"

#include "OSELib/Helper/DurationWrapper.h"

namespace OSELib {
namespace Helper {

DurationWrapper::DurationWrapper(const std::string & value) : xml_schema::Duration(false, 0, 0, 0, 0, 0, 0.0) {
	parse(value);
}

DurationWrapper & DurationWrapper::operator=(const xml_schema::Duration & source) {
	negative(source.negative());
	years(source.years());
	months(source.months());
	days(source.days());
	hours(source.hours());
	minutes(source.minutes());
	seconds(source.seconds());
	return *this;
}

std::string DurationWrapper::toString() {
	std::ostringstream result;
	xsd::cxx::tree::bits::insert(result, *this);
	return result.str();
}

Poco::Timestamp DurationWrapper::toExpirationTimeStamp() {
	Poco::Timestamp result;
	const Poco::Timespan duration(days(), hours(), minutes(), (int)seconds(), 0);
	return result + duration;
}

} /* namespace Helper */
} /* namespace OSELib */
