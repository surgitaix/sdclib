/*
 * IEventSink.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#ifndef OSELIB_DPWS_IEVENTSINK_H_
#define OSELIB_DPWS_IEVENTSINK_H_

#include <string>

namespace OSELib
{
	namespace DPWS
	{
		class IEventSink
		{
		public:
			// Special Member Functions
			IEventSink() = default;
			IEventSink(const IEventSink& p_obj) = default;
			IEventSink(IEventSink&& p_obj) = default;
			IEventSink& operator=(const IEventSink& p_obj) = default;
			IEventSink& operator=(IEventSink&& p_obj) = default;
			virtual ~IEventSink() = default;

			virtual std::string getBaseUri() const = 0;
		};
	}
}

#endif
