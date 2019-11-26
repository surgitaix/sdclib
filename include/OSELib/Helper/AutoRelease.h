/*
 * AutoRelease.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef OSELIB_HELPER_AUTORELEASE_H_
#define OSELIB_HELPER_AUTORELEASE_H_

#include <assert.h>

namespace OSELib
{
	namespace Helper
	{
		template<class T>
		struct AutoRelease
		{
			void operator()(T * object) { assert(nullptr != object); object->release(); }
		};

	}
}

#endif
