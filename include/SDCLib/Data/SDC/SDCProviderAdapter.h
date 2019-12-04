/*
 * SDCProviderAdapter.h
 *
 *  Created on: 09.12.2015, matthias
 *  Modified on: 26.09.2019, baumeister
 *
 */

#ifndef SDCLIB_DATA_SDC_SDCPROVIDERADAPTER_H_
#define SDCLIB_DATA_SDC_SDCPROVIDERADAPTER_H_

#include "SDC-fwd.h"
#include "OSELib/DPWS/SubscriptionManager.h"
#include "OSELib/DPWS/MDPWSHostAdapter.h"
#include "OSELib/HTTP/HTTPServer.h"

#include <set>
#include <mutex>

namespace OSELib {
	class GetServiceImpl;
	class SetServiceImpl;
	class BICEPSServiceImpl;
}

namespace SDCLib
{
	namespace Data
	{
		namespace SDC
		{
			class SDCProviderAdapter
			{
			private:
				SDCProvider & m_provider;

				mutable std::mutex m_mutex;

				std::set<int> ml_streamingPorts;

				std::unique_ptr<OSELib::DPWS::SubscriptionManager> m_subscriptionManager = nullptr;
				std::unique_ptr<OSELib::DPWS::MDPWSHostAdapter> m_dpwsHost = nullptr;
				std::unique_ptr<OSELib::HTTP::HTTPServer> m_httpServer = nullptr;

			public:
				SDCProviderAdapter(SDCProvider & p_provider);
				// Special Member Functions
				SDCProviderAdapter(const SDCProviderAdapter& p_obj) = delete;
				SDCProviderAdapter(SDCProviderAdapter&& p_obj) = delete;
				SDCProviderAdapter& operator=(const SDCProviderAdapter& p_obj) = delete;
				SDCProviderAdapter& operator=(SDCProviderAdapter&& p_obj) = delete;
				~SDCProviderAdapter();

				bool start();

				// DescriptionEvent
				void notifyEvent(const MDM::DescriptionModificationReport & p_report);
				// StateEvent
				void notifyEvent(const MDM::EpisodicAlertReport & p_report);
				void notifyEvent(const MDM::EpisodicComponentReport & p_report);
				void notifyEvent(const MDM::EpisodicContextReport & p_report);
				void notifyEvent(const MDM::EpisodicMetricReport & p_report);
				void notifyEvent(const MDM::EpisodicOperationalStateReport & p_report);
				void notifyEvent(const MDM::PeriodicAlertReport & p_report);
				void notifyEvent(const MDM::PeriodicContextReport & p_report);
				void notifyEvent(const MDM::PeriodicMetricReport & p_report);
				void notifyEvent(const MDM::OperationInvokedReport & p_report);
				// Waveform
				void notifyEvent(const MDM::WaveformStream & p_stream);

				void addStreamingPort(const int p_port);
				void removeStreamingPort(const int p_port);
			};

		}
	}
}

#endif
