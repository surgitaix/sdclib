/*
 * AutoRelease.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef OSELIB_HELPER_AUTORELEASE_H_
#define OSELIB_HELPER_AUTORELEASE_H_

namespace OSELib
{
	namespace Helper
	{
		template<class T>
		struct AutoRelease
		{
			void operator()(T * object) { object->release(); }
		};

	}
}

#endif
