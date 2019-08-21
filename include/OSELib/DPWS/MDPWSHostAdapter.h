/*
 * MDPWSHostAdapter.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 20.08.2019, baumeister
 *
 */

#ifndef OSELIB_DPWS_DPWSHOST_H_
#define OSELIB_DPWS_DPWSHOST_H_

#include <memory>

#include "OSELib/DPWS/DPWSHostSocketImpl.h"

#include "wsdd-discovery-1.1-schema-os.hxx"

namespace OSELib
{
	namespace DPWS
	{

		// fixme add mutex to datastructures. calling dispatch (from a socket call) and setting a scope or type causes a race condition

		class MDPWSHostAdapter : public ProbeNotificationDispatcher, public ResolveNotificationDispatcher
		{
		private:
			std::atomic<bool> m_started = ATOMIC_VAR_INIT(false);
			const AddressType m_epr;
			ScopesType m_scopes;
			TypesType m_types;
			XAddressesType m_xaddresses;
			std::atomic<int> m_metadataVersion = ATOMIC_VAR_INIT(1);

			std::unique_ptr<Impl::DPWSHostSocketImpl> m_impl = nullptr;

		public:
			MDPWSHostAdapter(
					SDCLib::Config::NetworkConfig_shared_ptr p_config,
					const AddressType & epr,
					const ScopesType & scopes,
					const TypesType & types,
					const XAddressesType & xaddresses,
					int metadataVersion = 1);
			// Special Member Functions
			MDPWSHostAdapter(const MDPWSHostAdapter& p_obj) = delete;
			MDPWSHostAdapter(MDPWSHostAdapter&& p_obj) = delete;
			MDPWSHostAdapter& operator=(const MDPWSHostAdapter& p_obj) = delete;
			MDPWSHostAdapter& operator=(MDPWSHostAdapter&& p_obj) = delete;
			virtual ~MDPWSHostAdapter() = default;

			void start();
			void stop();
			void sendStream(const MDM::WaveformStream & p_stream);

			void setScopes(const ScopesType & p_scopes);
			void setTypes(const TypesType & p_types);
			void setXAddresses(const XAddressesType & p_xaddresses);

			std::vector<ProbeMatchType> dispatch(const ProbeType & p_filter) override;

		private:
			void sendHello();

			std::unique_ptr<ResolveMatchType> dispatch(const ResolveType & p_filter) override;

		};

	}
}

#endif
