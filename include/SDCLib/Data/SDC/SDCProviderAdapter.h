/*
 * SDCProviderAdapter.h
 *
 *  Created on: 09.12.2015
 *      Author: matthias
 */

#ifndef SDCLIB_DATA_SDC_SDCPROVIDERADAPTER_H_
#define SDCLIB_DATA_SDC_SDCPROVIDERADAPTER_H_

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

	bool start();
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

	mutable std::mutex m_mutex;
	std::unique_ptr<Poco::ThreadPool> _threadPool;

	std::set<int> streamingPorts;

	std::unique_ptr<OSELib::DPWS::SubscriptionManager> _subscriptionManager;
	std::unique_ptr<OSELib::DPWS::MDPWSHostAdapter> _dpwsHost;
	std::unique_ptr<Poco::Net::HTTPServer> _httpServer;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

#endif /* SDCLIB_DATA_SDC_SDCPROVIDERADAPTER_H_ */
