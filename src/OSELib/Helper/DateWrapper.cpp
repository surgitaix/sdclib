/*
 * DateWrapper.cpp
 *
 *  Created on: 11.10.2019, baumeister
 *  Modified on:
 *
 */

#include "OSELib/Helper/DateWrapper.h"

#include <sstream>
#include <time.h>

using namespace OSELib;
using namespace OSELib::Helper;

DateWrapper::DateWrapper(const std::string & p_value)
: xml_schema::Date(0, 0, 0)
{
	parse(p_value);
}

DateWrapper & DateWrapper::operator=(const xml_schema::Date & p_source)
{
	year(p_source.year());
	month(p_source.month());
	day(p_source.day());
	return *this;
}

std::string DateWrapper::toString()
{
	std::ostringstream result;
	xsd::cxx::tree::bits::insert(result, *this);
	return result.str();
}
