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
 * OSCPSubscriptionManager.h
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: roehser, besting
 */

#ifndef OSCPSUBSCRIPTIONMANAGER_H_
#define OSCPSUBSCRIPTIONMANAGER_H_

#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "OSCLib/Data/OSCP/Operations/OSCPReportTraits.h"
#include "OSCLib/Util/Task.h"

#include <atomic>
#include <memory>

#include "Poco/Mutex.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

class OSCPSubscriptionManager : public Util::Task {
public:
	OSCPSubscriptionManager(OSCPConsumer & consumer);
	~OSCPSubscriptionManager();

	void init();
	void remove();

	bool isInitialized();

	void dispatch(std::unique_ptr<EpisodicAlertReportTraits::ReportType> report);
	void dispatch(std::unique_ptr<EpisodicContextChangedReportTraits::ReportType> report);
	void dispatch(std::unique_ptr<EpisodicMetricReportTraits::ReportType> report);
	void dispatch(std::unique_ptr<OperationInvokedReportTraits::ReportType> report);
	void dispatch(std::unique_ptr<PeriodicAlertReportTraits::ReportType> report);
	void dispatch(std::unique_ptr<PeriodicContextChangedReportTraits::ReportType> report);
	void dispatch(std::unique_ptr<PeriodicMetricReportTraits::ReportType> report);

	void detachConsumer();
    void setError(bool error) {
        this->error = error;
    }

private:
	void runImpl();

    template<class SinkType>
    bool initializeSink(std::shared_ptr<SinkType> & sink);
    template<class SinkType>
    void removeSink(std::shared_ptr<SinkType> & sink);
    template<class SinkType>
    bool tryRenew(std::shared_ptr<SinkType> sink);

    void dispatchAlertState(const CDM::AbstractAlertState & alertState);
    void dispatchMetricState(const CDM::AbstractMetricState & metricState);

    Poco::Mutex mutex;
    OSCPConsumer * consumer;

    std::shared_ptr<CDMEAREventSink> episodicAlertEventSink;
    std::shared_ptr<CDMECREventSink> episodicContextEventSink;
    std::shared_ptr<CDMEMREventSink> episodicMetricEventSink;
    std::shared_ptr<CDMOIREventSink> operationInvokedEventSink;
    std::shared_ptr<CDMPAREventSink> periodicAlertEventSink;
    std::shared_ptr<CDMPCREventSink> periodicContextEventSink;
    std::shared_ptr<CDMPMREventSink> periodicMetricEventSink;
    std::atomic<bool> initialized;
    std::atomic<bool> error;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* OSCPSUBSCRIPTIONMANAGER_H_ */
