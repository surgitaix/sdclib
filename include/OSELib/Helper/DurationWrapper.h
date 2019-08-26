/*
 * DurationWrapper.h
 *
 * Helper class to convert between various duration formats
 *
 * Created on: 07.12.2015, matthias
 * Modified on: 23.08.2019, baumeister
 *
 */

#ifndef OSELIB_HELPER_DURATIONWRAPPER_H_
#define OSELIB_HELPER_DURATIONWRAPPER_H_

#include "OSELib/fwd.h"

#include "SDCLib/Prerequisites.h"

namespace OSELib
{
	namespace Helper
	{
		class DurationWrapper : public xml_schema::Duration
		{
		public:
			DurationWrapper(const std::string & p_value);
			DurationWrapper(std::chrono::seconds p_seconds);

			// Special Member Functions
			DurationWrapper(const DurationWrapper& p_obj) = default;
			DurationWrapper(DurationWrapper&& p_obj) = default;
			DurationWrapper& operator=(const DurationWrapper& p_obj) = default;
			DurationWrapper& operator=(DurationWrapper&& p_obj) = default;

			// Assignment from xml_schema Duration
			DurationWrapper & operator=(const xml_schema::Duration & p_source);


			std::string toString();

			// Gives a Timepoint from now with the saved duration, only valid if the first parameter is true
			std::pair<bool,SDCLib::TimePoint> toExpirationTimePoint();

			// Converts the Duration, only valid if the first parameter is true
			std::pair<bool,SDCLib::Duration_s> toDuration_s();

			bool isNegative() const;
		};
	}
}

#endif
