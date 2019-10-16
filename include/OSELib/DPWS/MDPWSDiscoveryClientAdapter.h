/*
 * MDPWSDiscoveryClientAdapter.h
 *
 *  Created on: 11.12.2015, matthias
 *  Modified on: 23.08.2019, baumeister
 *
 */

#ifndef OSELIB_DPWS_MDPWSDISCOVERYCLIENTADAPTER_H_
#define OSELIB_DPWS_MDPWSDISCOVERYCLIENTADAPTER_H_

#include "OSELib/fwd.h"
#include "OSELib/DPWS/Types.h"
#include "SDCLib/Prerequisites.h"
#include "OSELib/DPWS/DPWSDiscoveryClientSocketImpl.h"

namespace OSELib
{
	namespace DPWS
	{

		struct ByeCallback {
			virtual ~ByeCallback() = default;
			virtual void bye(const ByeType & p_notification) = 0;
		};

		struct HelloCallback {
			virtual ~HelloCallback() = default;
			virtual void hello(const HelloType & p_notification) = 0;
		};

		struct ProbeMatchCallback {
			virtual ~ProbeMatchCallback() = default;
			virtual void probeMatch(const ProbeMatchType & p_notification) = 0;
		};

		struct ResolveMatchCallback {
			virtual ~ResolveMatchCallback() = default;
			virtual void resolveMatch(const ResolveMatchType & p_notification) = 0;
		};

		class MDPWSDiscoveryClientAdapter :
				public ByeNotificationDispatcher,
				public HelloNotificationDispatcher,
				public ProbeMatchNotificationDispatcher,
				public ResolveMatchNotificationDispatcher
		{
		private:

			std::mutex m_mutex;

			std::unique_ptr<Impl::DPWSDiscoveryClientSocketImpl> m_impl = nullptr;

			typedef std::tuple<ProbeType, ProbeMatchCallback *> ProbeMatchHandler;
			typedef std::tuple<ResolveType, ResolveMatchCallback *> ResolveMatchHandler;
			std::vector<ProbeMatchHandler> ml_probeMatchHandlers;
			std::vector<ResolveMatchHandler> ml_resolveMatchHandlers;
			std::vector<HelloCallback*> ml_helloHandlers;
			std::vector<ByeCallback*> ml_byeHandlers;

		public:
			MDPWSDiscoveryClientAdapter(SDCLib::Config::NetworkConfig_shared_ptr p_config);
			// Special Member Functions
			MDPWSDiscoveryClientAdapter(const MDPWSDiscoveryClientAdapter& p_obj) = delete;
			MDPWSDiscoveryClientAdapter(MDPWSDiscoveryClientAdapter&& p_obj) = delete;
			MDPWSDiscoveryClientAdapter& operator=(const MDPWSDiscoveryClientAdapter& p_obj) = delete;
			MDPWSDiscoveryClientAdapter& operator=(MDPWSDiscoveryClientAdapter&& p_obj) = delete;
			virtual ~MDPWSDiscoveryClientAdapter() = default;


			void addProbeMatchEventHandler(const ProbeType p_filter, ProbeMatchCallback & p_callback);
			void removeProbeMatchEventHandler(ProbeMatchCallback & p_callback);

			void addResolveMatchEventHandler(const ResolveType p_filter, ResolveMatchCallback & p_callback);
			void removeResolveMatchEventHandler(ResolveMatchCallback & p_callback);

			void addHelloEventHandler(HelloCallback & p_callback);
			void removeHelloEventHandler(HelloCallback & p_callback);

			void addByeEventHandler(ByeCallback & p_callback);
			void removeByeEventHandler(ByeCallback & p_callback);

		private:
			void dispatch(const ProbeMatchType & p_notification) override;
			void dispatch(const ResolveMatchType & p_notification) override;
			void dispatch(const ByeType & p_notification) override;
			void dispatch(const HelloType & p_notification) override;
		};
	}
}

#endif
