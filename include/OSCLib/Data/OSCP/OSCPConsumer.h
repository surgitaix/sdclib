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
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: roehser, besting
 */

#ifndef OSCPCONSUMER_H_
#define OSCPCONSUMER_H_

#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/MDIB/MDIBContainer.h"

#include <atomic>
#include <deque>
#include <map>
#include <memory>
#include <string>

#include "Poco/Mutex.h"

namespace OSCLib {

namespace Cli {
class Client;
}

namespace Comm {
namespace DPWS {
class DPWS11WaveformStreamActionHandler;
}
}

namespace Data {
namespace OSCP {

class OSCPConsumer {
friend class OSCPPingManager;
friend class OSCPServiceManager;
friend class OSCPSubscriptionManager;
friend class OSCLib::Comm::DPWS::DPWS11WaveformStreamActionHandler;
friend class FutureInvocationState;
private:
	struct TransactionState {
		TransactionState(int id, InvocationState is) :
			transactionId(id),
			invocationState(is) {
		}

		const int transactionId;
		const InvocationState invocationState;
	};
private:
    virtual OSCPConsumer & operator=(const OSCPConsumer & consumer) { return *this; }
public:
    OSCPConsumer(const OSCPConsumer & consumer) { throw std::runtime_error("Not implemented."); }
	virtual ~OSCPConsumer();

    /**
    * @brief Get the complete MDIB (description and states).
    *
    * @return The MDIB container
    */
    MDIBContainer getMDIB();

    /**
    * @brief Get the Medical Device Description.
    *
    * @return The MDD container
    */
    MDDescription getMDDescription();

    /**
    * @brief Get all states as part of the MDIB.
    *
    * @return The MD state container
    */
    MDState getMDState();

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
	bool requestState(const std::string & handle, AlertConditionState & outState);
	bool requestState(const std::string & handle, AlertSignalState & outState);
    bool requestState(const std::string & handle, AlertSystemState & outState);
	bool requestState(const std::string & handle, ClockState & outState);
	bool requestState(const std::string & handle, ComponentState & outState);
	bool requestState(const std::string & handle, EnsembleContextState & outState);
    bool requestState(const std::string & handle, EnumStringMetricState & outState);
	bool requestState(const std::string & handle, LimitAlertConditionState & outState);
	bool requestState(const std::string & handle, LocationContextState & outState);
	bool requestState(const std::string & handle, NumericMetricState & outState);
	bool requestState(const std::string & handle, OperationState & outState);
	bool requestState(const std::string & handle, OperatorContextState & outState);
	bool requestState(const std::string & handle, PatientContextState & outState);
	bool requestState(const std::string & handle, StringMetricState & outState);
	bool requestState(const std::string & handle, WorkflowContextState & outState);

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
    * @brief Check if consumer is valid.
    *
    * @return True, if connected
    */
    bool isValid();

    /**
    * @brief Check if consumer is connected.
    *
    * @return True, if connected
    */
    bool isConnected() {
        return connected;
    }

    /**
    * @brief Get the logical (default) transport address of the provider used by DPWS (XAddr).
    *
    * @return The XAddr
    */
    std::string getProviderXAddr() const;

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
    void setContextStateChangedHandler(OSCPConsumerContextStateChangedHandler * handler);

    /**
    * @brief Set a handler which will be invoked if a renewal of a subscription fails.
    *
    * @param handler The handler
    */
    void setSubscriptionLostHandler(OSCPConsumerSubscriptionLostHandler * handler);

    std::string requestRawMDIB();

    std::string getEndpointReference();

    unsigned long long int getLastKnownMDIBVersion();

private:
    OSCPConsumer();
    OSCPConsumer(std::shared_ptr<Cli::Client> client);

    /**
    * @brief Update the local MDIB using an RPC to the provider.
    *
    * @param True, if MDIB updated successfully.
    */
    bool requestMDIB();
    std::unique_ptr<CDM::GetMDIBResponse> requestCDMMDIB();

    MDDescription getCachedMDDescription();

    bool unregisterFutureInvocationListener(int transactionId);

    template<class OperationTraits, class StateType>
    InvocationState commitStateImpl(const StateType & state, FutureInvocationState & transactionId);

    void handleInvocationState(int transactionId, FutureInvocationState & fis);

    template<class OutStateType>
    bool requestStateImpl(const std::string & handle, OutStateType & state);

    template<class OperationTraits>
    std::unique_ptr<typename OperationTraits::Response> invokeImpl(const typename OperationTraits::Request & request);

    template<typename T>
    void onStateChanged(const T & state);
    void onOperationInvoked(const OperationInvocationContext & oic, InvocationState is);
    void onConnectionLost();
    void onSubscriptionLost();
    void onContextStateChanged(const std::vector<std::string> & handle);

    void initializePingManager();
    void initializeCDMEventSinks();
    void removeCDMEventSinks();

    void updateLastKnownMDIBVersion(unsigned long long int newVersion);

    std::shared_ptr<Cli::Client> client;
    Poco::Mutex pingManMutex;
	std::shared_ptr<OSCPPingManager> pingMan;
	Poco::Mutex subManMutex;
    std::shared_ptr<OSCPSubscriptionManager> subMan;

    std::map<int, FutureInvocationState *> fisMap;
    Poco::Mutex transactionMutex;

    std::shared_ptr<MDIBContainer> mdib;
    std::deque<TransactionState> transactionQueue;
	Poco::Mutex mdibVersionMutex;
	Poco::Mutex requestMutex;
    Poco::Mutex eventMutex;
    std::map<std::string, OSCPConsumerEventHandler *> eventHandlers;
    OSCPConsumerConnectionLostHandler * connectionLostHandler;
    OSCPConsumerContextStateChangedHandler * contextStateChangedHandler;
    OSCPConsumerSubscriptionLostHandler * subscriptionLostHandler;

    unsigned long long int lastKnownMDIBVersion;
    std::atomic<bool> connected;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* OSCPCONSUMER_H_ */
