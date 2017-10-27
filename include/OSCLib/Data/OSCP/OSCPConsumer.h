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
 * OSCPConsumer.h
 *
 *  @Copyright (C) 2017, SurgiTAIX AG
 *  Author: roehser, besting, buerger
 */

#ifndef OSCPCONSUMER_H_
#define OSCPCONSUMER_H_

#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/MDIB/custom/MdibContainer.h"

#include "OSELib/DPWS/DeviceDescription.h"
#include "OSCLib/Data/OSCP/OSELibConsumerAdapter.h"

#include <atomic>
#include <deque>
#include <map>
#include <memory>
#include <string>

#include "Poco/Mutex.h"

#include "OSELib/Helper/WithLogger.h"

namespace OSELib {
	struct ContextServiceEventSink;
	struct EventReportEventSink;
	namespace OSCP {
		class ServiceManager;
	}
}

namespace OSCLib {
namespace Data {
namespace OSCP {

class OSCPConsumer final : public OSELib::WithLogger {
friend class FutureInvocationState;
friend class OSELibConsumerAdapter;
// todo remove friend classes and only use oselibconsumer adapter
friend struct OSELib::ContextServiceEventSink;
friend struct OSELib::EventReportEventSink;
friend class OSELib::DPWS::PingManager;
friend class OSELib::OSCP::ServiceManager;

private:
	struct TransactionState {
		TransactionState(int id, InvocationState is) :
			transactionId(id),
			invocationState(is) {
		}

		const int transactionId;
		const InvocationState invocationState;
	};
public:
	virtual ~OSCPConsumer();

    /**
    * @brief Get the complete MDIB (description and states).
    *
    * @return The MDIB container
    */
    MdibContainer getMdib();

    /**
    * @brief Get the Medical Device Description.
    *
    * @return The MDD container
    */
    MdDescription getMdDescription();

    /**
    * @brief Get all states as part of the MDIB.
    *
    * @return The MD state container
    */
    MdState getMdState();

    /**
    * @brief Register to be notified if a state changes.
    *
    * Note: internally, registration will include an expiration time, which will be renewed 
    * automatically as long as the consumer exists and is connected.
    *
    * @param handler The event handler
    *
    * @return True, if registration was successful
    */
    bool registerStateEventHandler(OSCPConsumerEventHandler * handler);
    
    /**
    * @brief Unregister notification.
    *
    * @param handler The event handler
    *
    * @return True, if unregistration was successful
    */
    bool unregisterStateEventHandler(OSCPConsumerEventHandler * handler);

    /**
    * @brief Request or 'GET' a state.
    *
    * @param handle The handle of the state (descriptor or state handle).
    * @param outState Target state object
    *
    * @return True, if request was successful
    */

    template<class OutStateType>
    bool requestState(const std::string & handle, OutStateType & state);

    /**
    * @brief Commit or 'SET' a state (asynchronously).
    *
    * @param state The state to set
    * @param fis The future invocation state evaluator
    *
    * @return InvocationState The immediate return value
    */
	InvocationState commitState(const AlertSystemState & state, FutureInvocationState & fis);
	InvocationState commitState(const AlertSignalState & state, FutureInvocationState & fis);
	InvocationState commitState(const AlertConditionState & state, FutureInvocationState & fis);
	InvocationState commitState(const LimitAlertConditionState & state, FutureInvocationState & fis);
	InvocationState commitState(const EnumStringMetricState & state, FutureInvocationState & fis);
	InvocationState commitState(const NumericMetricState & state, FutureInvocationState & fis);
	InvocationState commitState(const StringMetricState & state, FutureInvocationState & fis);
	InvocationState commitState(const LocationContextState & state, FutureInvocationState & fis);
	InvocationState commitState(const EnsembleContextState & state, FutureInvocationState & fis);
	InvocationState commitState(const OperatorContextState & state, FutureInvocationState & fis);
	InvocationState commitState(const PatientContextState & state, FutureInvocationState & fis);
	InvocationState commitState(const WorkflowContextState & state, FutureInvocationState & fis);

	InvocationState commitState(const AlertSystemState & state);
	InvocationState commitState(const AlertSignalState & state);
	InvocationState commitState(const AlertConditionState & state);
	InvocationState commitState(const LimitAlertConditionState & state);
	InvocationState commitState(const EnumStringMetricState & state);
	InvocationState commitState(const NumericMetricState & state);
	InvocationState commitState(const StringMetricState & state);
	InvocationState commitState(const LocationContextState & state);
	InvocationState commitState(const EnsembleContextState & state);
	InvocationState commitState(const OperatorContextState & state);
	InvocationState commitState(const PatientContextState & state);
	InvocationState commitState(const WorkflowContextState & state);

	/**
    * @brief Call an ACTIVATE operation
    *
    * @param handle The handle (descriptor or state handle).
    * @param fis The future invocation state evaluator
    *
    * @return InvocationState The immediate return value
    */
	InvocationState activate(const std::string & handle, FutureInvocationState & fis);
	InvocationState activate(const std::string & handle);

    /**
    * @brief Disconnect the consumer from the provider.
    */
    void disconnect();

    /**
    * @brief Check if consumer is connected.
    *
    * @return True, if connected
    */
    bool isConnected() {
        return connected;
    }

    /**
    * @brief Set a handler which will be invoked if a ping fails.
    *
    * @param handler The handler
    */
    void setConnectionLostHandler(OSCPConsumerConnectionLostHandler * handler);

    /**
    * @brief Set a handler which will be invoked if a context state change event arrives.
    *
    * @param handler The handler
    */
    void setContextStateChangedHandler(OSCPConsumerSystemContextStateChangedHandler * handler);

    /**
    * @brief Set a handler which will be invoked if a renewal of a subscription fails.
    *
    * @param handler The handler
    */
    void setSubscriptionLostHandler(OSCPConsumerSubscriptionLostHandler * handler);

    /**
    * @brief Request Mdib in raw XML format.
    *
    * @return The XML as string
    */
    std::string requestRawMdib();

    /**
    * @brief Get EPR of the connected provider.
    *
    * @return The EPR
    */
    std::string getEndpointReference();

    /**
    * @brief Get last known Mdib version.
    *
    * @return The version
    */
    unsigned long long int getLastKnownMdibVersion();

private:
    OSCPConsumer(const OSELib::DPWS::DeviceDescription & deviceDescription);

    /**
    * @brief Update the local MDIB using an RPC to the provider.
    *
    * @return True, if MDIB updated successfully.
    */
    bool requestMdib();
    std::unique_ptr<MDM::GetMdibResponse> requestCDMMdib();

    MdDescription getCachedMdDescription();

    bool unregisterFutureInvocationListener(int transactionId);

    template<class OperationTraits, class StateType>
    InvocationState commitStateImpl(const StateType & state, FutureInvocationState & transactionId);

    void handleInvocationState(int transactionId, FutureInvocationState & fis);

    template<typename T>
    void onStateChanged(const T & state);
    void onOperationInvoked(const OperationInvocationContext & oic, InvocationState is);
    void onConnectionLost();
    void onSubscriptionLost();
    void onContextStateChanged(const std::vector<std::string> & handle);
    void updateLastKnownMdibVersion(unsigned long long int newVersion);

    //
    //Variables
    //
    std::map<int, FutureInvocationState *> fisMap;
    Poco::Mutex transactionMutex;

    std::shared_ptr<MdibContainer> mdib;
    std::deque<TransactionState> transactionQueue;
	Poco::Mutex mdibVersionMutex;
	Poco::Mutex requestMutex;
    Poco::Mutex eventMutex;
    std::map<std::string, OSCPConsumerEventHandler *> eventHandlers;
    OSCPConsumerConnectionLostHandler * connectionLostHandler;
    OSCPConsumerSystemContextStateChangedHandler * contextStateChangedHandler;
    OSCPConsumerSubscriptionLostHandler * subscriptionLostHandler;

    unsigned long long int lastKnownMDIBVersion;
    std::atomic<bool> connected;
    OSELib::DPWS::DeviceDescription _deviceDescription;
    std::unique_ptr<OSELibConsumerAdapter> _adapter;


};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* OSCPCONSUMER_H_ */
