/**
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  *
  */

/*
 * OSCPProviderDistributionSampleArrayMetricStateHandler.h
 *
 *  @Copyright (C) 2017, SurgiTAIX AG
 *  Author: buerger
 */

#ifndef DATA_OSCP_OSCPPROVIDERDISTRIBUTIONSAMPLEARRAYMETRICSTATEHANDLER_H_
#define DATA_OSCP_OSCPPROVIDERDISTRIBUTIONSAMPLEARRAYMETRICSTATEHANDLER_H_

#include "OSCLib/Data/OSCP/OSCPProviderMdStateHandler.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

class OSCPProviderDistributionSampleArrayMetricStateHandler : public OSCPProviderMdStateHandler {
public:
	OSCPProviderDistributionSampleArrayMetricStateHandler();
	virtual ~OSCPProviderDistributionSampleArrayMetricStateHandler();

    /**
    * @brief Called on incoming consumer request for a state change
    *
    * Notes:
    * - The consumer will wait for this method to complete. (InvocationState::Fin)
    *
    * @param state The requested state containing fields to be updated.
    *
    * @return InvocationState
    */
    virtual InvocationState onStateChangeRequest(const DistributionSampleArrayMetricState & state, const OperationInvocationContext & oic);

    void updateState(const OSCLib::Data::OSCP::DistributionSampleArrayMetricState & object);


    /**
	* @brief the initial state has to be defined by the user
	*
	*/
    virtual DistributionSampleArrayMetricState getInitialState() = 0;

    /**
    * @brief Return the handle of this handler's state.
    *
    * @return The handle
    */
    std::string getDescriptorHandle();
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

#endif /* DATA_OSCP_OSCPPROVIDERDISTRIBUTIONSAMPLEARRAYMETRICSTATEHANDLER_H_ */
