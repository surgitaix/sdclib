/*
 * DurationWrapper.cpp
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 01.08.2019, baumeister
 *
 */
#include "OSELib/Helper/DurationWrapper.h"

using namespace OSELib;
using namespace OSELib::Helper;

DurationWrapper::DurationWrapper(const std::string & value)
: xml_schema::Duration(false, 0, 0, 0, 0, 0, 0.0)
{
	parse(value);
}

DurationWrapper & DurationWrapper::operator=(const xml_schema::Duration & source)
{
	negative(source.negative());
	years(source.years());
	months(source.months());
	days(source.days());
	hours(source.hours());
	minutes(source.minutes());
	seconds(source.seconds());
	return *this;
}

std::string DurationWrapper::toString()
{
	std::ostringstream result;
	xsd::cxx::tree::bits::insert(result, *this);
	return result.str();
}


SDCLib::TimePoint DurationWrapper::toExpirationTimePoint()
{
	// Take the current time
	auto t_result = std::chrono::system_clock::now();

	// Offset by duration
	t_result += std::chrono::hours(days()*24 + hours());
	t_result += std::chrono::minutes(minutes());
	t_result += std::chrono::seconds(static_cast<int>(seconds()));

	//Return the new timepoint
	return t_result;
}
