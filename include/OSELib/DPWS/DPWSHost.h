/*
 * DPWSHost.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef DPWS_DPWSHOST_H_
#define DPWS_DPWSHOST_H_

#include <memory>

#include "OSELib/DPWS/Types.h"

namespace OSELib {
namespace DPWS {

// fixme add mutex to datastructures. calling dispatch (from a socket call) and setting a scope or type causes a race condition

class DPWSHost :
		public ProbeNotificationDispatcher,
		public ResolveNotificationDispatcher
{
public:
	DPWSHost(const AddressType & epr,
			const ScopesType & scopes,
			const TypesType & types,
			const XAddressesType & xaddresses,
			int metadataVersion = 1);
	virtual ~DPWSHost();

	void start();
	void stop();

	void setScopes(const ScopesType & scopes);
	void setTypes(const TypesType & types);
	void setXAddresses(const XAddressesType & xaddresses);

	virtual std::vector<ProbeMatchType> dispatch(const ProbeType & filter) override;

private:
	void sendHello();

	virtual std::unique_ptr<ResolveMatchType> dispatch(const ResolveType & filter) override;

	bool _started;
	const AddressType _epr;
	ScopesType _scopes;
	TypesType _types;
	XAddressesType _xaddresses;
	int _metadataVersion;

	std::unique_ptr<Impl::DPWSDiscoveryHostSocketImpl> _impl;
};

} /* namespace DPWS */
} /* namespace OSELib */

#endif /* DPWS_DPWSHOST_H_ */
