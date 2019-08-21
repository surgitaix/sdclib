/*
 * IWaveformService
 *
 *  Created on: 15.03.2019, buerger
 *  Modified on: 21.08.2019, baumeister
 *
 */

#ifndef OSELIB_SDC_WAVEFORMSERVICE_H_
#define OSELIB_SDC_WAVEFORMSERVICE_H_

#include "OSELib/DPWS/IService.h"
#include "OSELib/DPWS/ISubscriptionManager.h"

namespace OSELib
{
	namespace SDC
	{
		class IWaveformService : public DPWS::IService, public DPWS::ISubscriptionManager
		{
		public:
			// Special Member Functions
			IWaveformService() = default;
			IWaveformService(const IWaveformService& p_obj) = default;
			IWaveformService(IWaveformService&& p_obj) = default;
			IWaveformService& operator=(const IWaveformService& p_obj) = default;
			IWaveformService& operator=(IWaveformService&& p_obj) = default;
			virtual ~IWaveformService() = default;
		};
	}
}

#endif
