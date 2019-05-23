/*
 * MDPWSHostAdapter.cpp
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#include "OSELib/DPWS/DPWSHostSocketImpl.h"
#include "OSELib/DPWS/MessageAdapter.h"

#include "wsdd-discovery-1.1-schema-os.hxx"

#include "OSELib/DPWS/DPWSCommon.h"
#include "OSELib/DPWS/MDPWSHostAdapter.h"

using namespace OSELib::DPWS;

MDPWSHostAdapter::MDPWSHostAdapter(
        SDCLib::SDCInstance_shared_ptr p_SDCInstance,
		const AddressType & epr,
		const ScopesType & scopes,
		const TypesType & types,
		const XAddressesType & xaddresses,
		int metadataVersion) :
	_epr(epr),
	_scopes(scopes),
	_types(types),
	_xaddresses(xaddresses),
	_metadataVersion(metadataVersion),
    _impl(new Impl::DPWSHostSocketImpl(p_SDCInstance, *this, *this))
{
}
MDPWSHostAdapter::~MDPWSHostAdapter() = default;

void MDPWSHostAdapter::start() {
	_started = true;
	sendHello();
}

void MDPWSHostAdapter::stop() {
	EndpointReferenceType epr(_epr);
	ByeType bye(epr);
	_impl->sendBye(bye);
	_started = false;
}

void MDPWSHostAdapter::setScopes(const ScopesType & scopes) {
	_scopes = scopes;
	++_metadataVersion;
	sendHello();
}

void MDPWSHostAdapter::setTypes(const TypesType & types) {
	_types.clear();
	std::copy(types.begin(), types.end(), std::back_inserter(_types));
	++_metadataVersion;
	sendHello();
}

void MDPWSHostAdapter::setXAddresses(const XAddressesType & xaddresses) {
	_xaddresses = xaddresses;
	++_metadataVersion;
	sendHello();
}

void MDPWSHostAdapter::sendStream(const MDM::WaveformStream & stream) {
	_impl->sendStream(stream, AddressType(_epr));
}

void MDPWSHostAdapter::sendHello() {
	if (! _started) {
		return;
	}
	HelloType hello(
			_epr,
			_metadataVersion);
	if (! _scopes.empty()) {
		hello.Scopes(_scopes);
	}
	if (! _types.empty()) {
		hello.Types(_types);
	}
	if (! _xaddresses.empty()) {
		hello.XAddrs(_xaddresses);
	}
	_impl->sendHello(hello);
}

std::vector<ProbeMatchType> MDPWSHostAdapter::dispatch(const ProbeType & filter) {
	ProbeMatchType match(_epr, _metadataVersion);
	if (! _scopes.empty()) {
		match.Scopes(_scopes);
	}
	if (! _types.empty()) {
		match.Types(_types);
	}
	if (! _xaddresses.empty()) {
		match.XAddrs(_xaddresses);
	}
	std::vector<ProbeMatchType> result;
	if (! Impl::compare(filter, match)) {
		return result;
	} else {
		result.push_back(match);
		return result;
	}
}

std::unique_ptr<ResolveMatchType> MDPWSHostAdapter::dispatch(const ResolveType & filter) {
	std::unique_ptr<ResolveMatchType> result(new ResolveMatchType(_epr, _metadataVersion));
	if (! _scopes.empty()) {
		result->Scopes(_scopes);
	}
	if (! _types.empty()) {
		result->Types(_types);
	}
	if (! _xaddresses.empty()) {
		result->XAddrs(_xaddresses);
	}
	if (! Impl::compare(filter, *result)) {
		return nullptr;
	} else {
		return result;
	}
}
