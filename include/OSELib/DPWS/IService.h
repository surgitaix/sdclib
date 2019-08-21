/*
 * IService.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#ifndef OSELIB_DPWS_ISERVICE_H_
#define OSELIB_DPWS_ISERVICE_H_

#include <string>
#include "OSELib/DPWS/OperationTraits.h"

namespace OSELib
{
	namespace DPWS
	{
		class IService
		{
		public:
			// Special Member Functions
			IService() = default;
			IService(const IService& p_obj) = default;
			IService(IService&& p_obj) = default;
			IService& operator=(const IService& p_obj) = default;
			IService& operator=(IService&& p_obj) = default;
			virtual ~IService() = default;

			virtual std::string getBaseUri() const = 0;
			virtual std::string getWSDL() = 0;
			virtual GetMetadataTraits::Response getMetadata(const std::string & serverAddress, bool p_SSL) = 0;
		};

	}
}

#endif
