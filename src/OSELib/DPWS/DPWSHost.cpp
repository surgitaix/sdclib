/*
 * DPWSHost.cpp
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#include <OSELib/DPWS/DPWSHostSocketImpl.h>
#include "OSELib/DPWS/MessageAdapter.h"

#include "wsdd-discovery-1.1-schema-os.hxx"

#include "OSELib/DPWS/DPWSCommon.h"
#include "OSELib/DPWS/DPWSHost.h"

namespace OSELib {
namespace DPWS {

DPWSHost::DPWSHost(
		const AddressType & epr,
		const ScopesType & scopes,
		const TypesType & types,
		const XAddressesType & xaddresses,
		int metadataVersion) :
	_started(false),
	_epr(epr),
	_scopes(scopes),
	_types(types),
	_xaddresses(xaddresses),
	_metadataVersion(metadataVersion),
	_impl(new Impl::DPWSHostSocketImpl(*this, *this))
{
}

DPWSHost::~DPWSHost() = default;

void DPWSHost::start() {
	_started = true;
	sendHello();
}

void DPWSHost::stop() {
	EndpointReferenceType epr(_epr);
	ByeType bye(epr);
	_impl->sendBye(bye);
	_started = false;
}

void DPWSHost::setScopes(const ScopesType & scopes) {
	_scopes = scopes;
	++_metadataVersion;
	sendHello();
}

void DPWSHost::setTypes(const TypesType & types) {
	_types.clear();
	std::copy(types.begin(), types.end(), std::back_inserter(_types));
	++_metadataVersion;
	sendHello();
}

void DPWSHost::setXAddresses(const XAddressesType & xaddresses) {
	_xaddresses = xaddresses;
	++_metadataVersion;
	sendHello();
}

void DPWSHost::sendStream(const CDM::WaveformStream & stream) {
	_impl->sendStream(stream, AddressType(_epr));
}

void DPWSHost::sendHello() {
	if (not _started) {
		return;
	}
	HelloType hello(
			_epr,
			_metadataVersion);
	if (not _scopes.empty()) {
		hello.Scopes(_scopes);
	}
	if (not _types.empty()) {
		hello.Types(_types);
	}
	if (not _xaddresses.empty()) {
		hello.XAddrs(_xaddresses);
	}
	_impl->sendHello(hello);
}

std::vector<ProbeMatchType> DPWSHost::dispatch(const ProbeType & filter) {
	ProbeMatchType match(_epr, _metadataVersion);
	if (not _scopes.empty()) {
		match.Scopes(_scopes);
	}
	if (not _types.empty()) {
		match.Types(_types);
	}
	if (not _xaddresses.empty()) {
		match.XAddrs(_xaddresses);
	}
	std::vector<ProbeMatchType> result;
	if (not Impl::compare(filter, match)) {
		return result;
	} else {
		result.push_back(match);
		return result;
	}
}

std::unique_ptr<ResolveMatchType> DPWSHost::dispatch(const ResolveType & filter) {
	std::unique_ptr<ResolveMatchType> result(new ResolveMatchType(_epr, _metadataVersion));
	if (not _scopes.empty()) {
		result->Scopes(_scopes);
	}
	if (not _types.empty()) {
		result->Types(_types);
	}
	if (not _xaddresses.empty()) {
		result->XAddrs(_xaddresses);
	}
	if (not Impl::compare(filter, *result)) {
		return nullptr;
	} else {
		return result;
	}
}

} /* namespace DPWS */
} /* namespace OSELib */
