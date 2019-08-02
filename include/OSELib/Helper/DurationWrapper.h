/*
 * DurationWrapper.h
 *
 * Helper class to convert between various duration formats
 *
 * Created on: 07.12.2015, matthias
 * Modified on: 01.08.2019, baumeister
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
			DurationWrapper(const std::string & value);

			DurationWrapper & operator=(const xml_schema::Duration & source);

			std::string toString();

			SDCLib::TimePoint toExpirationTimePoint();
		};
	}
}

#endif /* OSELIB_HELPER_DURATIONWRAPPER_H_ */
