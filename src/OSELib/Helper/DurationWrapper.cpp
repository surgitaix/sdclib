/*
 * DurationWrapper.cpp
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 09.08.2019, baumeister
 *
 */
#include "OSELib/Helper/DurationWrapper.h"

#include <sstream>
#include <time.h>

using namespace OSELib;
using namespace OSELib::Helper;

DurationWrapper::DurationWrapper(const std::string & value)
: xml_schema::Duration(false, 0, 0, 0, 0, 0, 0.0)
{
	parse(value);
}
DurationWrapper::DurationWrapper(std::chrono::seconds p_seconds)
: xml_schema::Duration(false, 0, 0, 0, 0, 0, 0.0)
{
	// Assemble
	negative((p_seconds.count() < 0) ? true : false);
	years(0);
	months(0);
	days(0);
	hours(0);
	minutes(0);
	seconds(p_seconds.count());
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

std::pair<bool,SDCLib::Duration_s> DurationWrapper::toDuration_s()
{
	 // Get current time
	auto t_now = time(NULL);

	// Convert to localtime
	auto t_localTime = *localtime(&t_now);

	// Fill values
	t_localTime.tm_year += years();
	t_localTime.tm_mon += months();
	t_localTime.tm_mday += days();
	t_localTime.tm_hour += hours();
	t_localTime.tm_min += minutes();
	t_localTime.tm_sec += seconds();

	// Calc Duration from string
	auto t_durationTime_t = std::mktime(&t_localTime);

	// Calc diff = number in seconds and return
	long t_seconds = static_cast<long>(difftime(t_durationTime_t, t_now));
	return {true, std::chrono::seconds(t_seconds)};
}

std::pair<bool,SDCLib::TimePoint> DurationWrapper::toExpirationTimePoint()
{
	auto t_durationPair = toDuration_s();
	if(!t_durationPair.first) {
		return {false, {}};
	}
	return {true, std::chrono::system_clock::now() + t_durationPair.second};
}

bool DurationWrapper::isNegative() const
{
	return negative();
}
