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
 * SDCConsumer.h
 *
 *  @Copyright (C) 2017, SurgiTAIX AG
 *  Author: roehser, besting, buerger
 *  Modified on: 26.08.2019, baumeister
 *
 */

#ifndef SDCLIB_DATA_SDC_SDCCONSUMER_H_
#define SDCLIB_DATA_SDC_SDCCONSUMER_H_

#include "SDCLib/Data/SDC/SDC-fwd.h"
#include "SDCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "SDCLib/Data/SDC/MDIB/custom/MdibContainer.h"
#include "SDCLib/Data/SDC/SDCConsumerAdapter.h"

#include <atomic>
#include <deque>
#include <map>
#include <memory>
#include <string>
#include <mutex>

#include "OSELib/fwd.h"
#include "OSELib/Helper/WithLogger.h"

namespace SDCLib
{
	namespace Data
	{
		namespace SDC
		{

			class SDCConsumer final : public OSELib::Helper::WithLogger
			{
				friend class FutureInvocationState;
				friend class SDCConsumerAdapter;
				//TODO kick after consumer state handler refactoring
				friend class SDCConsumerOperationInvokedHandler;

				// todo remove friend classes and only use oselibconsumer adapter
				friend struct OSELib::ContextServiceEventSink;
				friend struct OSELib::EventReportEventSink;
				friend struct OSELib::SetServiceEventSink;
				friend class OSELib::DPWS::PingManager;
				friend class OSELib::SDC::ServiceManager;

			private:
				struct TransactionState {
					TransactionState(int p_id, InvocationState p_is)
					: m_transactionId(p_id)
					, m_invocationState(p_is)
					{ }
					const int m_transactionId = 0;
					const InvocationState m_invocationState;
				};

				SDCInstance_shared_ptr m_SDCInstance = nullptr;
				OSELib::DPWS::DeviceDescription_shared_ptr m_deviceDescription = nullptr;

				std::map<int, FutureInvocationState *> ml_fisMap;
				std::mutex m_transactionMutex;

				std::shared_ptr<MdibContainer> m_mdib = nullptr;
				std::deque<TransactionState> ml_transactionQueue;
				std::mutex m_mdibVersionMutex;
				std::mutex m_requestMutex;
				std::mutex m_eventMutex;
				std::map<std::string, SDCConsumerOperationInvokedHandler *> ml_eventHandlers;
				SDCConsumerConnectionLostHandler * m_connectionLostHandler = nullptr;
				// todo: kick
				SDCConsumerSystemContextStateChangedHandler * m_contextStateChangedHandler = nullptr;
				SDCConsumerSubscriptionLostHandler * m_subscriptionLostHandler = nullptr;

				unsigned long long int m_lastKnownMDIBVersion = 0;
				std::atomic<bool> m_connected = ATOMIC_VAR_INIT(false);

				std::unique_ptr<SDCConsumerAdapter> m_adapter = nullptr;

			public:

				// Special Member Functions
				SDCConsumer() = delete;
				SDCConsumer(const SDCConsumer& p_obj) = delete;
				SDCConsumer(SDCConsumer&& p_obj) = delete;
				SDCConsumer& operator=(const SDCConsumer& p_obj) = delete;
				SDCConsumer& operator=(SDCConsumer&& p_obj) = delete;
				~SDCConsumer();

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
				bool registerStateEventHandler(SDCConsumerOperationInvokedHandler * p_handler);

				/**
				* @brief Unregister notification.
				*
				* @param handler The event handler
				*
				* @return True, if unregistration was successful
				*/
				bool unregisterStateEventHandler(SDCConsumerOperationInvokedHandler * p_handler);

				/**
				* @brief Request or 'GET' a state.
				*
				* @param handle The handle of the state (descriptor or state handle).
				* @param outState Target state object
				*
				* @return True, if request was successful
				*/

				template<class TStateType>
				std::unique_ptr<TStateType> requestState(const std::string & p_handle);

				/**
				* @brief Commit or 'SET' a state (asynchronously).
				*
				* @param state The state to set
				* @param fis The future invocation state evaluator
				*
				* @return InvocationState The immediate return value
				*/
				InvocationState commitState(const AlertSystemState & p_state, FutureInvocationState & p_fis);
				InvocationState commitState(const AlertSignalState & p_state, FutureInvocationState & p_fis);
				InvocationState commitState(const AlertConditionState & p_state, FutureInvocationState & p_fis);
				InvocationState commitState(const LimitAlertConditionState & p_state, FutureInvocationState & p_fis);
				InvocationState commitState(const EnumStringMetricState & p_state, FutureInvocationState & p_fis);
				InvocationState commitState(const NumericMetricState & p_state, FutureInvocationState & p_fis);
				InvocationState commitState(const StringMetricState & state, FutureInvocationState & p_fis);
				InvocationState commitState(const LocationContextState & p_state, FutureInvocationState & p_fis);
				InvocationState commitState(const EnsembleContextState & p_state, FutureInvocationState & p_fis);
				InvocationState commitState(const OperatorContextState & p_state, FutureInvocationState & p_fis);
				InvocationState commitState(const PatientContextState & p_state, FutureInvocationState & p_fis);
				InvocationState commitState(const WorkflowContextState & p_state, FutureInvocationState & p_fis);

				InvocationState commitState(const AlertSystemState & p_state);
				InvocationState commitState(const AlertSignalState & p_state);
				InvocationState commitState(const AlertConditionState & p_state);
				InvocationState commitState(const LimitAlertConditionState & vstate);
				InvocationState commitState(const EnumStringMetricState & p_state);
				InvocationState commitState(const NumericMetricState & p_state);
				InvocationState commitState(const StringMetricState & p_state);
				InvocationState commitState(const LocationContextState & p_state);
				InvocationState commitState(const EnsembleContextState & p_state);
				InvocationState commitState(const OperatorContextState & p_state);
				InvocationState commitState(const PatientContextState & p_state);
				InvocationState commitState(const WorkflowContextState & p_state);

				/**
				* @brief Call an ACTIVATE operation
				*
				* @param handle The handle (descriptor or state handle).
				* @param fis The future invocation state evaluator
				*
				* @return InvocationState The immediate return value
				*/
				InvocationState activate(const std::string & p_handle, FutureInvocationState & p_fis);
				InvocationState activate(const std::string & p_handle);

				/**
				* @brief Disconnect the consumer from the provider.
				*/
				void disconnect();

				/**
				* @brief Check if consumer is connected.
				*
				* @return True, if connected
				*/
				bool isConnected() const {
					return m_connected;
				}

				/**
				* @brief Set a handler which will be invoked if a ping fails.
				*
				* @param handler The handler
				*/
				void setConnectionLostHandler(SDCConsumerConnectionLostHandler * p_handler);

				// todo:kick?
				/**
				* @brief Set a handler which will be invoked if a context state change event arrives.
				*
				* @param handler The handler
				*/
				void setContextStateChangedHandler(SDCConsumerSystemContextStateChangedHandler * p_handler);

				/**
				* @brief Set a handler which will be invoked if a renewal of a subscription fails.
				*
				* @param handler The handler
				*/
				void setSubscriptionLostHandler(SDCConsumerSubscriptionLostHandler * p_handler);

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
				std::string getEndpointReference() const;

				/**
				* @brief Get last known Mdib version.
				*
				* @return The version
				*/
				unsigned long long int getLastKnownMdibVersion();

			private:

				SDCConsumer(SDCLib::SDCInstance_shared_ptr p_SDCInstance, OSELib::DPWS::DeviceDescription_shared_ptr p_deviceDescription);

				/**
				* @brief Get the managing SDCInstance
				*
				* @return shared_ptr to the SDCInstance
				*/
				SDCInstance_shared_ptr getSDCInstance() { return m_SDCInstance; }

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
				InvocationState commitStateImpl(const StateType & p_state, FutureInvocationState & p_transactionId);

				void handleInvocationState(int p_transactionId, FutureInvocationState & p_fis);

				// This method es called each time a state changes. It calls to the state handler identified by the states descriptor handle
				template<typename T>
				void onStateChanged(const T & p_state);
				// In contrast to the method above, this method calls to all the state handlers identified by states handles. It also invokes by
				// the message dispacher to update the state handler identified by its descriptor
			//    template<typename T>
			//    void onMultiStateChanged(const T & state);

				void onOperationInvoked(const OperationInvocationContext & p_oic, InvocationState p_is);
				void onConnectionLost();
				void onSubscriptionLost();
				void updateLastKnownMdibVersion(unsigned long long int p_newVersion);
			};

		}
	}
}
#endif
