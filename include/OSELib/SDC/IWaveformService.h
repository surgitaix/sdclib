/*
 * IWaveformService
 *
 *  Created on: 15.03.2019
 *      Author: buerger
 */

#ifndef SDC_WAVEFORMSERVICE_H_
#define SDC_WAVEFORMSERVICE_H_

#include "OSELib/fwd.h"
#include "OSELib/DPWS/IService.h"
#include "OSELib/DPWS/ISubscriptionManager.h"

namespace OSELib {
namespace SDC {

class IWaveformService : public DPWS::IService, public DPWS::ISubscriptionManager {
public:
	virtual ~IWaveformService() = default;
};

} /* namespace SDC */
} /* namespace OSELib */

#endif /* SDC_WAVEFORMSERVICE_H_ */
