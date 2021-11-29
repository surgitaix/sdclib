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
 * SDCProvider.h
 *
 *  @Copyright (C) 2017, SurgiTAIX AG
 *  Author: besting, buerger, roehser
 *  Modified on: 29.08.2019, baumeister
 *
 */

#ifndef SDCLIB_DATA_SDC_SDCPROVIDER_H_
#define SDCLIB_DATA_SDC_SDCPROVIDER_H_

#include "SDCLib/Prerequisites.h"
#include "SDCLib/Dev/DeviceCharacteristics.h"
#include "SDCLib/Data/SDC/SDC-fwd.h"
#include "SDCLib/Data/SDC/SDCProviderAdapter.h"
#include "SDCLib/Data/SDC/MDIB/MDIB-fwd.h"
#include "SDCLib/Data/SDC/MDIB/MdState.h"

#include "OSELib/Helper/WithLogger.h"

#include <Poco/NotificationQueue.h>

#include <map>

namespace SDCLib
{
	namespace Data
	{
		namespace SDC
		{
			class SDCProvider final : public OSELib::Helper::WithLogger
			{
				friend class AsyncProviderInvoker;

				// todo: kick after provider state handler refactoring
				friend class SDCProviderStateHandler;

				// todo replace by friend class SDCProviderAdapter

				friend class OSELib::GetServiceImpl;
				friend class OSELib::SetServiceImpl;
				friend class OSELib::BICEPSServiceImpl;

			private:

				SDCInstance_shared_ptr m_SDCInstance{nullptr};

				mutable std::mutex m_mutex;
				std::atomic<bool> m_started{false};

				std::atomic_uint atomicTransactionId{0};

				std::atomic_ullong mdibVersion{0};

				std::map<std::string, SDCProviderStateHandler *> m_stateHandlers;
				mutable std::mutex m_mutex_MdStateHandler;

				std::unique_ptr<MdDescription> m_MdDescription;
				mutable std::mutex m_mutex_MdDescription;

				MdState m_MdState;
				mutable std::mutex m_mutex_MdState;
				MdState m_operationStates;

				std::unique_ptr<SDCProviderAdapter> m_adapter{nullptr};
				Dev::DeviceCharacteristics m_devicecharacteristics;
				mutable std::mutex m_mutex_DevC;

				std::string m_endpointReference;
				mutable std::mutex m_mutex_EPR;


				std::mutex m_mutex_invokeQueue;
				Poco::NotificationQueue m_invokeQueue;
				std::shared_ptr<AsyncProviderInvoker> m_providerInvoker{nullptr};

				std::vector<std::string> ml_handlesForPeriodicUpdates;
				mutable std::mutex m_mutex_PeriodicUpdateHandles;

				std::atomic<std::chrono::milliseconds> m_periodicEventInterval{std::chrono::milliseconds(10)};

				TimePoint m_lastPeriodicEvent{std::chrono::system_clock::now()};
				mutable std::mutex m_mutex_PeriodicEvent;

			public:

				SDCProvider(SDCInstance_shared_ptr p_SDCInstance);
				// Special Member Functions
				SDCProvider(const SDCProvider& p_obj) = delete;
				SDCProvider(SDCProvider&& p_obj) = delete;
				SDCProvider& operator=(const SDCProvider& p_obj) = delete;
				SDCProvider& operator=(SDCProvider&& p_obj) = delete;

				~SDCProvider();

				/**
				* @brief Get the managing SDCInstance
				*
				* @return shared_ptr to the SDCInstance
				*/
				SDCInstance_shared_ptr getSDCInstance() { return m_SDCInstance; }

				/**
				* @brief Get the complete Medical Device Infomation Base (MDIB, description and states).
				*
				* @return The MDIB container
				*/
				MdibContainer getMdib() const;

				/**
				* @brief Set the (static) Medical Device Description
				*
				* @param The MdDescription
				*/
				bool setMdDescription(const MdDescription & p_MdDescription);
				/**
				* @brief Set the (static) Medical Device Description
				*
				* @param The MdDescription as xml string
				*/
				bool setMdDescription(std::string p_xml);

				/**
				* @brief Get the (static) Medical Device Description. Empty if not started yet.
				*
				* @return The MdDescription
				*/
				MdDescription getMdDescription() const;

				/**
				* @brief Get all states as part of the MDIB.
				*
				* @return The MD state container
				*/
				MdState getMdState() const;

				/**
				* @brief Activates the SetOperation of a state defined in descriptor in the ownerMDS.
				* Comparable to createSetOperationForDescriptor, but with more flexibility regarding the described state
				*
				* @param ActivateOperationDescriptor: contains name of the service control objects handle and the targets handle (e.g. descriptor.setHandle("handle_cmd").setOperationTarget("handle_max"))
				* @param MdsDescriptor: the containing mds
				*
				*
				*/
				void addActivateOperationForDescriptor(const ActivateOperationDescriptor & p_descriptor, MdsDescriptor & p_ownerMDS);


				/**
				* @brief Activates the SetOperation of a descriptor: makes the target state of the descriptor settable through the consumer)
				*
				*
				* @param the descriptor to be made settable
				* @param MdsDescriptor: the containing mds
				*
				*/
				void createSetOperationForDescriptor(const AlertConditionDescriptor & p_descriptor, MdsDescriptor & p_ownerMDS);
				void createSetOperationForDescriptor(const AlertSignalDescriptor & p_descriptor, MdsDescriptor & p_ownerMDS);
				void createSetOperationForDescriptor(const AlertSystemDescriptor & p_descriptor, MdsDescriptor & p_ownerMDS);
				void createSetOperationForDescriptor(const EnumStringMetricDescriptor & p_descriptor, MdsDescriptor & p_ownerMDS);
				void createSetOperationForDescriptor(const LimitAlertConditionDescriptor & p_descriptor, MdsDescriptor & p_ownerMDS);
				void createSetOperationForDescriptor(const NumericMetricDescriptor & p_descriptor, MdsDescriptor & p_ownerMDS);
				void createSetOperationForDescriptor(const StringMetricDescriptor & p_descriptor, MdsDescriptor & p_ownerMDS);
				void createSetOperationForDescriptor(const PatientContextDescriptor & p_descriptor, MdsDescriptor & p_ownerMDS);
				void createSetOperationForDescriptor(const LocationContextDescriptor & p_descriptor, MdsDescriptor & p_ownerMDS);
				void createSetOperationForDescriptor(const EnsembleContextDescriptor & p_descriptor, MdsDescriptor & p_ownerMDS);
				void createSetOperationForDescriptor(const OperatorContextDescriptor & p_descriptor, MdsDescriptor & p_ownerMDS);
				void createSetOperationForDescriptor(const WorkflowContextDescriptor & p_descriptor, MdsDescriptor & p_ownerMDS);

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
				void setAlertConditionPresence(const std::string & p_alertConditionHandle, bool p_conditionPresence, const OperationInvocationContext & p_oic);

				void evaluateAlertConditions(const std::string & p_source) const;
				void reevaluateAlertConditions(const std::string & p_alertConditionDescriptor) const;


				/**
				* @brief Start the provider.
				* @return True if successful, false if something went wrong. (See log for further details.)
				*
				* All needed DPWS devices & services will be created and hosted.
				*/
				bool startup();

				/**
				* @brief Returns if the Provider was already started (initialized).
				*
				* @return true/false
				*/
				bool isStarted() const { return m_started; }

				/**
				* @brief Stop the provider.
				*
				* All needed DPWS devices & services will be stopped and deleted.
				*/
				void shutdown();

				template<class T>
				void replaceState(T p_state);

				/**
				* @brief Add a state handler to provide states and to process incoming change requests from a consumer.
				*
				* @param handler The handler
				*/
				void addMdStateHandler(SDCProviderStateHandler* p_handler);

				/**
				* @brief Remove a request handler which provides states and processes incoming change requests from a consumer.
				*
				* @param handler The handler
				*/
				void removeMDStateHandler(SDCProviderStateHandler* p_handler);

				/**
				 * @brief Set the endpoint reference without any conversion.
				 *
				 * @param p_epr the EPR
				 */
				void setEndpointReference(const std::string& p_epr);

				/**
				 * @brief Set the endpoint reference by Name. This function will convert it to a UUIDv5 of type urn:uuid:<UUIDv5(name)>
				 *
				 * @param p_name UDI of the EPR
				 */
				void setEndpointReferenceByName(const std::string& p_name);

				/**
				 * @brief Get the endpoint reference.
				 *
				 * @return The EPR
				 */
				std::string getEndpointReference() const;

				/**
				 * @brief Get the low level DPWS device characteristics.
				 *
				 * @return The DPWS device characteristics
				 */
				Dev::DeviceCharacteristics getDeviceCharacteristics() const;
				void setDeviceCharacteristics(const Dev::DeviceCharacteristics p_deviceCharacteristics);


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


				std::mutex& getMutex() { return m_mutex; } // FIXME! TODO: Keep mutex internal!

				/**
				 * @brief Set the periodic event fire interval.
				 *
				 * @param p_interval Interval in milliseconds
				 */
				void setPeriodicEventInterval(std::chrono::milliseconds p_interval);
				std::chrono::milliseconds getPeriodicEventInterval() const;
				TimePoint getLastPeriodicEvent() const;
				void setLastPeriodicEvent(TimePoint p_timepoint);
				std::vector<std::string> getHandlesForPeriodicUpdate() const;
				void addHandleForPeriodicEvent(const std::string& p_handle);
				void removeHandleForPeriodicEvent(const std::string& p_handle);

				/**
				* @brief Called on incoming consumer request for a state change.
				*
				* Notes:
				* - Can be overridden by a custom SDC provider as an alternative to the usage of handlers.
				* - The consumer will wait for this method to complete.
				* - Make sure to update the state's invocation state and notify about the change.
				*
				* @param state The requested state containing fields to be updated.
				*
				* @return invocation state
				*/

				template<typename T>
					InvocationState onStateChangeRequest(const T & p_state, const OperationInvocationContext & p_oic);


				/**
				* @brief Update internal state and notify all registered consumers about a changed MDIB object (episodic metric event).
				* These functions are used by the state handlers. Use those instead for updating the provider's states
				*
				* @param object The MDIB object
				*/
				void updateState(const AlertSystemState & p_object);
				void updateState(const AlertSignalState & p_object);
				void updateState(const AlertConditionState & p_object);
				void updateState(const EnumStringMetricState & p_object);
				void updateState(const EnsembleContextState & p_object);
				void updateState(const LimitAlertConditionState & p_object);
				void updateState(const LocationContextState & p_object);
				void updateState(const NumericMetricState & p_object);
				void updateState(const OperatorContextState & p_object);
				void updateState(const PatientContextState & p_object);
				void updateState(const MeansContextState & p_object);
				void updateState(const StringMetricState & p_object);
				void updateState(const RealTimeSampleArrayMetricState & p_object);
				void updateState(const WorkflowContextState & p_object);
				void updateState(const DistributionSampleArrayMetricState & p_object);

			protected:

				/**
				* @brief Notify all registered consumers about an operation invoked event (fires operation invoked event).
				*
				* @param object The MDIB object
				*/
				void notifyOperationInvoked(const OperationInvocationContext & p_oic, Data::SDC::InvocationState p_is);


			private:
				void firePeriodicReportImpl();
				void startAsyncProviderInvoker();
				void stopAsyncProviderInvoker();


				//Sets the updated state within the MDIB and increases the MDIBVersion
				template<class T>
				void updateMDIB(const T& p_object);

				template<class T>
				void notifyAlertEventImpl(const T& p_object);
				template<class T>
				void notifyContextEventImpl(const T& p_object);
				template<class T>
				void notifyEpisodicMetricImpl(const T& p_object);
				template<class T>
				void notifyEpisodicOperationalStateImpl(const T& p_object);

				template<class T>
				void notifyStreamMetricImpl(const T& p_object);

				template<class T>
				void createSetOperationForContextDescriptor(const T& p_descriptor, MdsDescriptor & p_ownerMDS);

				template<class StateType>
				bool isMetricChangeAllowed(const StateType & p_state, SDCProvider & p_provider);

				MDM::SetValueResponse SetValueAsync(const MDM::SetValue & p_request);
				void SetValue(const MDM::SetValue & p_request, const OperationInvocationContext & p_oic);

				MDM::ActivateResponse OnActivateAsync(const MDM::Activate & p_request);
				void OnActivate(const OperationInvocationContext & p_oic);

				MDM::SetStringResponse SetStringAsync(const MDM::SetString & p_request);
				void SetString(const MDM::SetString & p_request, const OperationInvocationContext & p_oic);
				template<class T>
				void SetStringImpl(const T & p_state, const OperationInvocationContext & p_oic);

				MDM::SetAlertStateResponse SetAlertStateAsync(const MDM::SetAlertState & p_request);
				void SetAlertState(const MDM::SetAlertState& p_request, const OperationInvocationContext& p_oic);
				template<typename StateType>
				void SetAlertStateImpl(const StateType & p_state, const OperationInvocationContext & p_oic);

				MDM::GetMdibResponse GetMdib(const MDM::GetMdib & p_request);
				MDM::GetMdDescriptionResponse GetMdDescription(const MDM::GetMdDescription & p_request);
				MDM::GetMdStateResponse GetMdState(const MDM::GetMdState & p_request);

				// For handling requests for context states:
				// handle = empty -> all context states
				// handle = specific handle -> get the context state referenced by this handle
				MDM::GetContextStatesResponse GetContextStates(const MDM::GetContextStates & p_request);
				MDM::SetContextStateResponse SetContextStateAsync(const MDM::SetContextState & p_request);
				void SetContextState(const MDM::SetContextState & p_request, const OperationInvocationContext & p_oic);
				template<typename TState>
				void SetContextStateImpl(const TState & p_state,  const OperationInvocationContext & p_oic);

				template<class T>
				bool addSetOperationToSCOObjectImpl(const T & p_source, MdsDescriptor & p_ownerMDS);

				template<class T>
				void enqueueInvokeNotification(const T & p_request, const OperationInvocationContext & p_oic);

				unsigned int incrementAndGetTransactionId();

				void _incrementMdStateVersion();

				// Note: Hotfix initializing "implied" values
				template<class T>
				void _initAbstractStateDefaults(T& p_state);
				template<class T>
				void _initComponentStateDefaults(T& p_state);
				template<class T>
				void _initStateMetricValueDefaults(T& p_state);

			};
		}
	}
}
#endif
