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
        struct ByeCallback
        {
            virtual ~ByeCallback() = default;
            virtual void bye(const ByeType& p_notification) = 0;
        };

        struct HelloCallback
        {
            virtual ~HelloCallback() = default;
            virtual void hello(const HelloType& p_notification) = 0;
        };

        struct ProbeMatchCallback
        {
            virtual ~ProbeMatchCallback() = default;
            virtual void probeMatch(const ProbeMatchType& p_notification) = 0;
        };

        struct ResolveMatchCallback
        {
            virtual ~ResolveMatchCallback() = default;
            virtual void resolveMatch(const ResolveMatchType& p_notification) = 0;
        };

        class MDPWSDiscoveryClientAdapter : public ByeNotificationDispatcher,
                                            public HelloNotificationDispatcher,
                                            public ProbeMatchNotificationDispatcher,
                                            public ResolveMatchNotificationDispatcher
        {
        private:
            std::unique_ptr<Impl::DPWSDiscoveryClientSocketImpl> m_impl = nullptr;

            std::mutex m_mutex_probe;
            typedef std::tuple<ProbeType, ProbeMatchCallback*> ProbeMatchHandler;
            std::vector<ProbeMatchHandler> m_probeMatchHandlers;

            std::mutex m_mutex_resolve;
            typedef std::tuple<ResolveType, ResolveMatchCallback*> ResolveMatchHandler;
            std::vector<ResolveMatchHandler> m_resolveMatchHandlers;

            std::mutex m_mutex_hello;
            std::vector<HelloCallback*> m_helloHandlers;

            std::mutex m_mutex_bye;
            std::vector<ByeCallback*> m_byeHandlers;

        public:
            MDPWSDiscoveryClientAdapter(SDCLib::Config::NetworkConfig_shared_ptr p_config);
            MDPWSDiscoveryClientAdapter(const MDPWSDiscoveryClientAdapter& p_obj) = delete;
            MDPWSDiscoveryClientAdapter(MDPWSDiscoveryClientAdapter&& p_obj) = delete;
            MDPWSDiscoveryClientAdapter& operator=(const MDPWSDiscoveryClientAdapter& p_obj) = delete;
            MDPWSDiscoveryClientAdapter& operator=(MDPWSDiscoveryClientAdapter&& p_obj) = delete;
            virtual ~MDPWSDiscoveryClientAdapter();


            void addProbeMatchEventHandler(const ProbeType p_filter, ProbeMatchCallback&);
            void removeProbeMatchEventHandler(ProbeMatchCallback&);

            void addResolveMatchEventHandler(const ResolveType p_filter, ResolveMatchCallback&);
            void removeResolveMatchEventHandler(ResolveMatchCallback&);

            void addHelloEventHandler(HelloCallback&);
            void removeHelloEventHandler(HelloCallback&);

            void addByeEventHandler(ByeCallback&);
            void removeByeEventHandler(ByeCallback&);

        private:
            void dispatch(const ProbeMatchType&) override;
            void dispatch(const ResolveMatchType&) override;
            void dispatch(const ByeType&) override;
            void dispatch(const HelloType&) override;
        };
    }  // namespace DPWS
}  // namespace OSELib

#endif
