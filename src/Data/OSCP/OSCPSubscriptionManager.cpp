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
 * OSCPSubscriptionManager.cpp
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: roehser, besting
 */

#include "OSCLib/Cli/Client.h"
#include "OSCLib/Data/OSCP/OSCPConstants.h"
#include "OSCLib/Data/OSCP/OSCPConsumer.h"
#include "OSCLib/Data/OSCP/OSCPSubscriptionManager.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSystemState.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSignalState.h"
#include "OSCLib/Data/OSCP/MDIB/AlertConditionState.h"
#include "OSCLib/Data/OSCP/MDIB/EnumStringMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/LimitAlertConditionState.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/OperationInvocationContext.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricState.h"
#include "OSCLib/Data/OSCP/Operations/CDMEventSink.h"
#include "OSCLib/Data/OSCP/Operations/OSCPReportTraits.h"
#include "OSCLib/Data/EventSink.h"
#include "OSCLib/Util/DebugOut.h"
#include "osdm.hxx"

#include "Poco/ScopedLock.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

OSCPSubscriptionManager::OSCPSubscriptionManager(OSCPConsumer & consumer) :
		consumer(&consumer),
		episodicAlertEventSink(nullptr),
		episodicContextEventSink(nullptr),
		episodicMetricEventSink(nullptr),
		operationInvokedEventSink(nullptr),
		periodicAlertEventSink(nullptr),
		periodicContextEventSink(nullptr),
		periodicMetricEventSink(nullptr),
		initialized(false),
        error(false)
{

}

OSCPSubscriptionManager::~OSCPSubscriptionManager() {

}

void OSCPSubscriptionManager::runImpl() {
	// Intermediate sleeps allow a faster break out of the run method
	// when the thread should be terminated.
	const int totalTime(15000);
	const int loopCount(30);
	const int loopInterval(totalTime/loopCount);
	int i = 0;
	while (i < loopCount && !isInterrupted()) {
		++i;
		Poco::Thread::sleep(loopInterval);
	}

	Poco::Mutex::ScopedLock lock(mutex);
	if (consumer == nullptr) {
		return;
	}

    bool success = true;
    if (!isInterrupted())
        if (!tryRenew(episodicAlertEventSink))
            success = false;
	if (!isInterrupted())
        if (!tryRenew(episodicContextEventSink))
            success = false;
	if (!isInterrupted())
        if (!tryRenew(episodicMetricEventSink))
            success = false;
	if (!isInterrupted())
        if (!tryRenew(operationInvokedEventSink))
            success = false;
	if (!isInterrupted())
        if (!tryRenew(periodicAlertEventSink))
            success = false;
    if (!isInterrupted())
        if (!tryRenew(periodicContextEventSink))
            success = false;
    if (!isInterrupted())
        if (!tryRenew(periodicMetricEventSink))
            success = false;
    if (error && success) {
        Util::DebugOut(Util::DebugOut::Error, "OSCPSubscriptionManager") << "Subscription re-established." << std::endl;
    }
    error = !success;
}

void OSCPSubscriptionManager::init() {
	Poco::Mutex::ScopedLock lock(mutex);
	if (consumer == nullptr) {
		return;
	}
    if (!initializeSink(episodicAlertEventSink))
    	return;
    if (!initializeSink(episodicContextEventSink))
    	return;
	if (!initializeSink(episodicMetricEventSink))
    	return;
    if (!initializeSink(operationInvokedEventSink))
    	return;
	if (!initializeSink(periodicAlertEventSink))
    	return;
	if (!initializeSink(periodicContextEventSink))
    	return;
	if (!initializeSink(periodicMetricEventSink))
    	return;
    initialized = true;
}

void OSCPSubscriptionManager::remove() {
	if (!initialized) {
		return;
	}
    initialized = false;

    Poco::Mutex::ScopedLock lock(mutex);
	if (consumer == nullptr) {
		return;
	}
	removeSink(episodicAlertEventSink);
	removeSink(episodicContextEventSink);
	removeSink(episodicMetricEventSink);
	removeSink(operationInvokedEventSink);
	removeSink(periodicAlertEventSink);
	removeSink(periodicContextEventSink);
	removeSink(periodicMetricEventSink);
}

template<class SinkType>
bool OSCPSubscriptionManager::tryRenew(std::shared_ptr<SinkType> sink) {
    bool success = true;
	Poco::Mutex::ScopedLock lock(mutex);
	if (consumer == nullptr) {
		return false;
	}
	if (sink == nullptr) {
		Util::DebugOut(Util::DebugOut::Error, "OSCPSubscriptionManager") << "No subscription found to renew. Consumer is not initialized correctly!" << std::endl;
        return false;
	}
	const std::string action(SinkType::TypeTraits::Action());
    if (initialized && consumer->isValid() && !(consumer->client->renewSync(action, SUBSCRIBE_TIMEOUT, sink, 3000))) {
        Util::DebugOut(Util::DebugOut::Error, "OSCPSubscriptionManager") << "Auto-renew failed! Trying to subscribe again. Action: " << action << std::endl;
        success = false;
    }
    if (error && initialized && consumer->isValid()) {
        if (!consumer->client->unsubscribeSync(action, sink, 3000)) {
            Util::DebugOut(Util::DebugOut::Error, "OSCPSubscriptionManager") << "Unsubscribe failed." << std::endl;
        }
        if (!consumer->client->subscribeSync(action, SUBSCRIBE_TIMEOUT, sink, nullptr, 3000)) {
            Util::DebugOut(Util::DebugOut::Error, "OSCPSubscriptionManager") << "Resubscribe failed." << std::endl;
            consumer->onSubscriptionLost();
            success = false;
        }
    }
    return success;
}

template<class SinkType>
bool OSCPSubscriptionManager::initializeSink(std::shared_ptr<SinkType> & sink) {
	Poco::Mutex::ScopedLock lock(mutex);
	if (consumer == nullptr) {
		return false;
	}
    if (sink == nullptr) {
    	sink.reset(new SinkType(*this));
        if (consumer->isValid() && !consumer->client->subscribeSync(SinkType::TypeTraits::Action(), SUBSCRIBE_TIMEOUT, sink)) {
            Util::DebugOut(Util::DebugOut::Error, "OSCPSubscriptionManager") << "Subscription failed: " << sink->getOutputAction() << std::endl;
        	sink.reset();
            return false;
        }
    }
    return true;
}

template<class SinkType>
void OSCPSubscriptionManager::removeSink(std::shared_ptr<SinkType> & sink) {
	Poco::Mutex::ScopedLock lock(mutex);
	if (consumer == nullptr) {
		return;
	}
	if (consumer->isValid() && sink && consumer->connected) {
		consumer->client->unsubscribeSync(SinkType::TypeTraits::Action(), sink);
		sink.reset();
	}
}

bool OSCPSubscriptionManager::isInitialized() {
    return initialized;
}

void OSCPSubscriptionManager::dispatch(std::unique_ptr<EpisodicAlertReportTraits::ReportType> report) {
	Poco::Mutex::ScopedLock lock(mutex);
	if (consumer == nullptr) {
		return;
	}
	consumer->updateLastKnownMDIBVersion(report->MDIBVersion());
	for (const auto & reportDetail : report->AlertReportDetail()) {
		for (const auto & alertState : reportDetail.AlertState()) {
			dispatchAlertState(alertState);
		}
	}
}

void OSCPSubscriptionManager::dispatch(std::unique_ptr<EpisodicContextChangedReportTraits::ReportType> report) {
	Poco::Mutex::ScopedLock lock(mutex);
	if (consumer == nullptr) {
		return;
	}
	consumer->updateLastKnownMDIBVersion(report->MDIBVersion());
	std::vector<std::string> changedStatesHandles;
	for (const auto & reportPart: report->ReportPart()) {
		if (const auto part = dynamic_cast<const CDM::ContextChangedReportPart *>(&reportPart)) {
			for (const auto & handle : part->ChangedContextState()) {
				changedStatesHandles.push_back(handle);
			}
		}
	}
	consumer->onContextStateChanged(changedStatesHandles);
}

void OSCPSubscriptionManager::dispatch(std::unique_ptr<EpisodicMetricReportTraits::ReportType> report) {
	Poco::Mutex::ScopedLock lock(mutex);
	if (consumer == nullptr) {
		return;
	}
	consumer->updateLastKnownMDIBVersion(report->MDIBVersion());
	for (const auto & reportPart : report->ReportPart()) {
		for (const auto & metricState : reportPart.MetricState()) {
			dispatchMetricState(metricState);
		}
	}
}

void OSCPSubscriptionManager::dispatch(std::unique_ptr<OperationInvokedReportTraits::ReportType> report) {
	Poco::Mutex::ScopedLock lock(mutex);
	if (consumer == nullptr) {
		return;
	}
	consumer->updateLastKnownMDIBVersion(report->MDIBVersion());
	for (const auto & irp : report->ReportDetail()) {
		consumer->onOperationInvoked(
			OperationInvocationContext(irp.OperationHandleRef(), irp.TransactionId()),
			ConvertFromCDM::convert(irp.OperationState()));
	}
}

void OSCPSubscriptionManager::dispatch(std::unique_ptr<PeriodicAlertReportTraits::ReportType> report) {
	Poco::Mutex::ScopedLock lock(mutex);
	if (consumer == nullptr) {
		return;
	}
	consumer->updateLastKnownMDIBVersion(report->MDIBVersion());
	for (const auto & reportDetail : report->AlertReportDetail()) {
		for (const auto & state : reportDetail.AlertState()) {
			dispatchAlertState(state);
		}
	}
}

void OSCPSubscriptionManager::dispatch(std::unique_ptr<PeriodicContextChangedReportTraits::ReportType> report) {
	Poco::Mutex::ScopedLock lock(mutex);
	if (consumer == nullptr) {
		return;
	}
	consumer->updateLastKnownMDIBVersion(report->MDIBVersion());
	std::vector<std::string> changedStatesHandles;

	for (const auto & reportPart: report->ReportPart()) {
		if (const auto part = dynamic_cast<const CDM::ContextChangedReportPart *>(&reportPart)) {
			for (const auto & handle : part->ChangedContextState()) {
				changedStatesHandles.push_back(handle);
			}
		}
	}

	consumer->onContextStateChanged(changedStatesHandles);
}

void OSCPSubscriptionManager::dispatch(std::unique_ptr<PeriodicMetricReportTraits::ReportType> report) {
	Poco::Mutex::ScopedLock lock(mutex);
	if (consumer == nullptr) {
		return;
	}
	consumer->updateLastKnownMDIBVersion(report->MDIBVersion());
	for (const auto & reportPart : report->ReportPart()) {
		for (const auto & state : reportPart.MetricState()) {
			dispatchMetricState(state);
		}
	}
}

void OSCPSubscriptionManager::dispatchAlertState(const CDM::AbstractAlertState & alertState) {
	Poco::Mutex::ScopedLock lock(mutex);
	if (consumer == nullptr) {
		return;
	}
	if (const auto state = dynamic_cast<const CDM::AlertSystemState *>(&alertState)) {
		consumer->onStateChanged(ConvertFromCDM::convert(*state));
		return;
	}
	if (const auto state = dynamic_cast<const CDM::AlertSignalState *>(&alertState)) {
		consumer->onStateChanged(ConvertFromCDM::convert(*state));
		return;
	}
	if (const auto state = dynamic_cast<const CDM::LimitAlertConditionState *>(&alertState)) {
		consumer->onStateChanged(ConvertFromCDM::convert(*state));
		return;
	}
	// the order does matter here, because AlertConditionState is the parent class of LimitAlertConditionState
	if (const auto state = dynamic_cast<const CDM::AlertConditionState *>(&alertState)) {
		consumer->onStateChanged(ConvertFromCDM::convert(*state));
		return;
	}
	Util::DebugOut(Util::DebugOut::Error, "OSCPSubscriptionManager") << "Unknown alert state type, event will not be forwarded to handler!";
}

void OSCPSubscriptionManager::dispatchMetricState(const CDM::AbstractMetricState & metricState) {
	Poco::Mutex::ScopedLock lock(mutex);
	if (consumer == nullptr) {
		return;
	}
	if (const auto state = dynamic_cast<const CDM::EnumStringMetricState *>(&metricState)) {
		consumer->onStateChanged(ConvertFromCDM::convert(*state));
		return;
	}
	if (const auto state = dynamic_cast<const CDM::NumericMetricState *>(&metricState)) {
		consumer->onStateChanged(ConvertFromCDM::convert(*state));
		return;
	}
	if (const auto state = dynamic_cast<const CDM::StringMetricState *>(&metricState)) {
		consumer->onStateChanged(ConvertFromCDM::convert(*state));
		return;
	}
	if (const auto state = dynamic_cast<const CDM::RealTimeSampleArrayMetricState *>(&metricState)) {
		consumer->onStateChanged(ConvertFromCDM::convert(*state));
		return;
	}

	Util::DebugOut(Util::DebugOut::Error, "OSCPSubscriptionManager") << "Unknown metric state type, event will not be forwarded to handler!";
}

void OSCPSubscriptionManager::detachConsumer() {
	Poco::Mutex::ScopedLock lock(mutex);
	consumer = nullptr;
}

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
