/*
 * DateWrapper.h
 *
 * Helper class to convert xml schema date
 *
 * Created on: 11.10.2019, baumeister
 * Modified on:
 *
 */

#ifndef OSELIB_HELPER_DATEWRAPPER_H_
#define OSELIB_HELPER_DATEWRAPPER_H_

#include "OSELib/fwd.h"

#include "SDCLib/Prerequisites.h"

#include "DataModel/NormalizedMessageModel-fwd.hxx"

namespace OSELib
{
	namespace Helper
	{
		class DateWrapper : public xml_schema::Date
		{
		public:
			DateWrapper(const std::string & p_value);

			// Special Member Functions
			DateWrapper(const DateWrapper& p_obj) = default;
			DateWrapper(DateWrapper&& p_obj) = default;
			DateWrapper& operator=(const DateWrapper& p_obj) = default;
			DateWrapper& operator=(DateWrapper&& p_obj) = default;

			// Assignment from xml_schema Date
			DateWrapper & operator=(const xml_schema::Date & p_source);

			std::string toString();

			int getDay() { return day(); }
			int getMonth() { return month(); }
			int getYear() { return year(); }
		};
	}
}

#endif
