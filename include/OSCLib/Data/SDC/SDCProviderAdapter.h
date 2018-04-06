/*
 * SDCProviderAdapter.h
 *
 *  Created on: 09.12.2015
 *      Author: matthias
 */

#ifndef DATA_OSCP_SDCPROVIDERADAPTER_H_
#define DATA_OSCP_SDCPROVIDERADAPTER_H_

#include "Poco/Mutex.h"

#include "SDC-fwd.h"
#include "OSELib/fwd.h"
#include <set>

namespace SDCLib {
namespace Data {
namespace SDC {

class SDCProviderAdapter {
public:
	SDCProviderAdapter(SDCProvider & provider);
	virtual ~SDCProviderAdapter();

	void start(MDPWSTransportLayerConfiguration config);
	void stop();

	void notifyEvent(const MDM::EpisodicAlertReport & report);
	void notifyEvent(const MDM::EpisodicContextReport & report);
	void notifyEvent(const MDM::EpisodicMetricReport & report);
	void notifyEvent(const MDM::PeriodicAlertReport & report);
	void notifyEvent(const MDM::PeriodicContextReport & report);
	void notifyEvent(const MDM::PeriodicMetricReport & report);
	void notifyEvent(const MDM::OperationInvokedReport & report);
	void notifyEvent(const MDM::WaveformStream & stream);

	void addStreamingPort(const int port);
	void removeStreamingPort(const int port);

private:
	SDCProvider & _provider;

	mutable Poco::Mutex mutex;
	std::unique_ptr<Poco::ThreadPool> _threadPool;

	std::set<int> streamingPorts;

	std::unique_ptr<OSELib::DPWS::SubscriptionManager> _subscriptionManager;
	std::unique_ptr<OSELib::DPWS::MDPWSHostAdapter> _dpwsHost;
	std::unique_ptr<Poco::Net::HTTPServer> _httpServer;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

#endif /* DATA_OSCP_SDCPROVIDERADAPTER_H_ */
