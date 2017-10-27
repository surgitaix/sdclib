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
 * OSCPProviderOperationHandler.h
 *
 *  @Copyright (C) 2015, SurgiTAIX AG
 *  Author: besting, roehser
 */

#ifndef INCLUDE_OSCLIB_DATA_OSCP_OSCPPROVIDERACTIVATEOPERATIONHANDLER_H_
#define INCLUDE_OSCLIB_DATA_OSCP_OSCPPROVIDERACTIVATEOPERATIONHANDLER_H_

#include "OSCLib/Data/OSCP/OSCPProviderMdStateHandler.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

class OSCPProviderActivateOperationHandler : public OSCPProviderMdStateHandler {
public:
	OSCPProviderActivateOperationHandler();
	virtual ~OSCPProviderActivateOperationHandler();

    /**
    * @brief Called on incoming consumer request for activation
    *
    * Notes:
    * - The consumer will wait for this method to complete.
    *
    * @return invocation state
    */
    virtual InvocationState onActivateRequest(const MdibContainer & mdib, const OperationInvocationContext & oic);

    /**
    * @brief Notify all registered consumers about a changed MDIB object.
    *
    * @param object The MDIB object
    */
    void updateState(const OSCLib::Data::OSCP::NumericMetricState & object);
    void updateState(const OSCLib::Data::OSCP::RealTimeSampleArrayMetricState & object);
    void updateState(const OSCLib::Data::OSCP::StringMetricState & object);
    void updateState(const OSCLib::Data::OSCP::AlertConditionState & object);
    void updateState(const OSCLib::Data::OSCP::AlertSystemState & object);
    void updateState(const OSCLib::Data::OSCP::AlertSignalState & object);
    void updateState(const OSCLib::Data::OSCP::LimitAlertConditionState & object);

private:
    template<class T> void notifyMDIBObjectChangedImpl(const T & object);
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

#endif /* INCLUDE_OSCLIB_DATA_OSCP_OSCPPROVIDERACTIVATEOPERATIONHANDLER_H_ */
