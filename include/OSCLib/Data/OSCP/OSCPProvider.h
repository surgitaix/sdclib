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
 * OSCPProvider.h
 *
 *  @Copyright (C) 2017, SurgiTAIX AG
 *  Author: besting, buerger, roehser
 */

#ifndef OSCPPROVIDER_H_
#define OSCPPROVIDER_H_

#include <atomic>
#include <memory>

#include "Poco/NotificationQueue.h"
#include "Poco/Mutex.h"
#include "Poco/Timestamp.h"
#include "Poco/Timespan.h"

#include "OSCLib/Dev/DeviceCharacteristics.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "OSCLib/Data/OSCP/OSELibProviderAdapter.h"
#include "OSCLib/Data/OSCP/MDIB/MDIB-fwd.h"
#include "OSCLib/Data/OSCP/MDIB/MdState.h"

#include "OSELib/Helper/WithLogger.h"


// todo remove
namespace OSELib {
	struct ContextReportServiceImpl;
	struct GetServiceImpl;
	struct SetServiceImpl;
}

namespace OSCLib {
namespace Data {
namespace OSCP {

class OSCPProvider final : public OSELib::WithLogger {
    friend class AsyncProviderInvoker;

    // todo: kick after provider state handler refactoring
    friend class OSCPProviderMdStateHandler;

    friend class SDCProviderStateHandler;

    // todo replace by friend class OSELibProviderAdapter
    friend struct OSELib::ContextReportServiceImpl;
    friend struct OSELib::GetServiceImpl;
    friend struct OSELib::SetServiceImpl;


public:
    OSCPProvider();
    virtual ~OSCPProvider();

    /**
    * @brief Get the complete Medical Device Infomation Base (MDIB, description and states).
    *
    * @return The MDIB container
    */
    MdibContainer getMdib();

    /**
    * @brief Set the (static) Medical Device Description
    *
    * @param The MdDescription
    */
    void setMdDescription(const MdDescription & mdDescription);
    /**
    * @brief Set the (static) Medical Device Description
    *
    * @param The MdDescription as xml string
    */
    void setMdDescription(std::string xml);

    /**
    * @brief Get the (static) Medical Device Description.
    *
    * @return The MdDescription
    */
    MdDescription getMdDescription() const;

    /**
    * @brief Get all states as part of the MDIB.
    *
    * @return The MD state container
    */
    MdState getMdState();

    /**
    * @brief Activates the SetOperation of a state defined in descriptor in the ownerMDS.
    * Comparable to createSetOperationForDescriptor, but with more flexibility regarding the described state
    *
    * @param ActivateOperationDescriptor: contains name of the service control objects handle and the targets handle (e.g. descriptor.setHandle("handle_cmd").setOperationTarget("handle_max"))
    * @param MdsDescriptor: the containing mds
    *
    *
    */
    void addActivateOperationForDescriptor(const ActivateOperationDescriptor & descriptor, MdsDescriptor & ownerMDS);


    /**
    * @brief Activates the SetOperation of a descriptor: makes the target state of the descriptor settable through the consumer)
    *
    *
    * @param the descriptor to be made settable
    * @param MdsDescriptor: the containing mds
    *
    */
    void createSetOperationForDescriptor(const AlertConditionDescriptor & descriptor, MdsDescriptor & ownerMDS);
    void createSetOperationForDescriptor(const AlertSignalDescriptor & descriptor, MdsDescriptor & ownerMDS);
    void createSetOperationForDescriptor(const AlertSystemDescriptor & descriptor, MdsDescriptor & ownerMDS);
    void createSetOperationForDescriptor(const EnumStringMetricDescriptor & descriptor, MdsDescriptor & ownerMDS);
    void createSetOperationForDescriptor(const LimitAlertConditionDescriptor & descriptor, MdsDescriptor & ownerMDS);
    void createSetOperationForDescriptor(const NumericMetricDescriptor & descriptor, MdsDescriptor & ownerMDS);
    void createSetOperationForDescriptor(const StringMetricDescriptor & descriptor, MdsDescriptor & ownerMDS);
    void createSetOperationForDescriptor(const PatientContextDescriptor & descriptor, MdsDescriptor & ownerMDS);
    void createSetOperationForDescriptor(const LocationContextDescriptor & descriptor, MdsDescriptor & ownerMDS);
    void createSetOperationForDescriptor(const EnsembleContextDescriptor & descriptor, MdsDescriptor & ownerMDS);
    void createSetOperationForDescriptor(const OperatorContextDescriptor & descriptor, MdsDescriptor & ownerMDS);
    void createSetOperationForDescriptor(const WorkflowContextDescriptor & descriptor, MdsDescriptor & ownerMDS);



    /**
    * @brief Trigger an alert condition using a flag to indicate the condition's presence.
    *
    * Calling this method will handle all alert signals which reference this condition automatically.
    *
    * Depending on the condition's presence (true or false), alert signals will be handled as follows:
    * 1. True: the alert signal's presence state will be set ON (no matter what the previous value was)
    * 2. False: if an alert signal's presence state is currently set to ON, it will be set to LATCHED
    * However, it will never be set OFF or ACK (see notes below).
    * Due to the modification of signal states by this method, condition and signal state handlers implemented by user
    * code will be invoked. This implementation should trigger an event to inform all consumers about
    * that modification of the modified alert signal states.
    *
    * @param alertConditionHandle The handle of the alert condition state.
    * @param conditionPresence True, if the condition has been detected.
    * @param oic operation invocation context
    */
    void setAlertConditionPresence(const std::string & alertConditionHandle, bool conditionPresence, const OperationInvocationContext & oic);
    void evaluateAlertConditions(const std::string & source);

    /**
    * @brief Start the provider.
    *
    * All needed DPWS devices & services will be created and hosted.
    */
    void startup();
    
    /**
    * @brief Stop the provider.
    *
    * All needed DPWS devices & services will be stopped and deleted.
    */
    void shutdown();
    
    template<class T>
    void replaceState(const T & state);

    /**
    * @brief Add a state handler to provide states and to process incoming change requests from a consumer.
    *
    * @param handler The handler
    */
    void addMdSateHandler(SDCProviderStateHandler * handler);

    /**
    * @brief Remove a request handler which provides states and processes incoming change requests from a consumer.
    *
    * @param handler The handler
    */
    void removeMDStateHandler(SDCProviderStateHandler * handler);

    /**
     * @brief Set the endpoint reference.
     *
     * @param epr the EPR
     */
	void setEndpointReference(const std::string & epr);

    /**
     * @brief Set the endpoint reference.
     *
     * @return The EPR
     */
	const std::string getEndpointReference() const;

    /**
     * @brief Get the low level DPWS device characteristics.
     *
     * @return The DPWS device characteristics
     */
	const Dev::DeviceCharacteristics& getDeviceCharacteristics() const;
	void setDeviceCharacteristics(const Dev::DeviceCharacteristics& deviceCharacteristics);


    /**
     * @brief Get the current Mdib version.
     *
     * @return The Mdib version.
     */
    unsigned long long int getMdibVersion() const;


    /**
     * @brief Increment Mdib version by 1.
     */
    void incrementMDIBVersion();

    Poco::Mutex & getMutex();
    
    void lock() {
    	getMutex().lock();
    }

    void unlock() {
    	getMutex().unlock();
    }    

    /**
     * @brief Set the periodic event fire interval.
     *
     * @param seconds Interval seconds
     * @param millisecods Interval milliseconds
     */
    void setPeriodicEventInterval(const int seconds, const int milliseconds);
    std::vector<std::string> getHandlesForPeriodicUpdate();
    void addHandleForPeriodicEvent(const std::string & handle);
    void removeHandleForPeriodicEvent(const std::string & handle);

    /**
	* @brief Called on incoming consumer request for a state change.
	*
	* Notes:
	* - Can be overridden by a custom OSCP provider as an alternative to the usage of handlers.
	* - The consumer will wait for this method to complete.
	* - Make sure to update the state's invocation state and notify about the change.
	*
	* @param state The requested state containing fields to be updated.
	*
	* @return invocation state
	*/

	template<typename T>
		InvocationState onStateChangeRequest(const T & state, const OperationInvocationContext & oic);


    /**
    * @brief Update internal state and notify all registered consumers about a changed MDIB object (episodic metric event).
    * These functions are used by the state handlers. Use those instead for updating the provider's states
    *
    * @param object The MDIB object
    */
    void updateState(const AlertSystemState & object);
    void updateState(const AlertSignalState & object);
    void updateState(const AlertConditionState & object);
    void updateState(const EnumStringMetricState & object);
    void updateState(const EnsembleContextState & object);
    void updateState(const LimitAlertConditionState & object);
    void updateState(const LocationContextState & object);
    void updateState(const NumericMetricState & object);
    void updateState(const OperatorContextState & object);
    void updateState(const PatientContextState & object);
    void updateState(const MeansContextState & object);
    void updateState(const StringMetricState & object);
    void updateState(const RealTimeSampleArrayMetricState & object);
    void updateState(const WorkflowContextState & object);
    void updateState(const DistributionSampleArrayMetricState & object);

protected:

    /**
    * @brief Notify all registered consumers about an operation invoked event (fires operation invoked event).
    *
    * @param object The MDIB object
    */
    void notifyOperationInvoked(const OperationInvocationContext & oic, Data::OSCP::InvocationState is);

private:
    void firePeriodicReportImpl(const std::vector<std::string> & handles);

    template<class T>
    void notifyAlertEventImpl(const T & object);
    template<class T>
    void notifyContextEventImpl(const T & object);
    template<class T>
	void notifyEpisodicMetricImpl(const T & object);

    template<class T>
    void notifyStreamMetricImpl(const T & object);

    template<class T>
    void createSetOperationForContextDescriptor(const T & descriptor, MdsDescriptor & ownerMDS);

    template<class StateType>
    bool isMetricChangeAllowed(const StateType & state, OSCPProvider & provider);

	MDM::SetValueResponse SetValueAsync(const MDM::SetValue & request);
    void SetValue(const MDM::SetValue & request, const OperationInvocationContext & oic);

    MDM::ActivateResponse OnActivateAsync(const MDM::Activate & request);
    void OnActivate(const OperationInvocationContext & oic);

    MDM::SetStringResponse SetStringAsync(const MDM::SetString & request);
    void SetString(const MDM::SetString & request, const OperationInvocationContext & oic);
    template<class T>
    void SetStringImpl(const T & state, const OperationInvocationContext & oic);

    MDM::SetAlertStateResponse SetAlertStateAsync(const MDM::SetAlertState & request);
    void SetAlertState(const MDM::SetAlertState & request, const OperationInvocationContext & oic);
    template<typename StateType>
    void SetAlertStateImpl(const StateType & state, const OperationInvocationContext & oic);

    MDM::GetMdibResponse GetMdib(const MDM::GetMdib & request);
    MDM::GetMdDescriptionResponse GetMdDescription(const MDM::GetMdDescription & request);
    MDM::GetMdStateResponse GetMdState(const MDM::GetMdState & request);

    // For handling requests for context states:
    // handle = empty -> all context states
    // handle = specific handle -> get the context state referenced by this handle
    MDM::GetContextStatesResponse GetContextStates(const MDM::GetContextStates & request);
    MDM::SetContextStateResponse SetContextStateAsync(const MDM::SetContextState & request);
    void SetContextState(const MDM::SetContextState & request, const OperationInvocationContext & oic);
    template<typename TState>
    void SetContextStateImpl(const TState & state,  const OperationInvocationContext & oic);

    template<class T>
    void addSetOperationToSCOObjectImpl(const T & source, MdsDescriptor & ownerMDS);

    template<class T>
    void enqueueInvokeNotification(const T & request, const OperationInvocationContext & oic);

    unsigned int incrementAndGetTransactionId();
    std::atomic_uint atomicTransactionId;

    std::atomic_ullong mdibVersion;

    std::map<std::string, SDCProviderStateHandler *> stateHandlers;

	std::shared_ptr<MdDescription> m_mdDescription;
    std::unique_ptr<OSELibProviderAdapter> _adapter;
    Dev::DeviceCharacteristics devicecharacteristics;
	Poco::Mutex mutex;

    std::string endpointReference;

	MdState mdibStates;
    MdState operationStates;
    Poco::NotificationQueue invokeQueue;
    std::shared_ptr<AsyncProviderInvoker> providerInvoker;

    std::vector<std::string> handlesForPeriodicUpdates;
    Poco::Timestamp lastPeriodicEvent;
    Poco::Timespan periodicEventInterval;
    
//    std::map<std::string, int> streamingPorts;

};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* OSCPPROVIDER_H_ */
