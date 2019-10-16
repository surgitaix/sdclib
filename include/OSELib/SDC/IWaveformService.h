/*
 * IWaveformService
 *
 *  Created on: 15.03.2019, buerger
 *  Modified on: 26.09.2019, baumeister
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
		class IWaveformService : public virtual DPWS::IService, public virtual DPWS::ISubscriptionManager
		{
		public:
			// Special Member Functions
			IWaveformService() = default;
			IWaveformService(const IWaveformService& p_obj) = delete;
			IWaveformService(IWaveformService&& p_obj) = delete;
			IWaveformService& operator=(const IWaveformService& p_obj) = delete;
			IWaveformService& operator=(IWaveformService&& p_obj) = delete;
			virtual ~IWaveformService() = default;
		};
	}
}

#endif
