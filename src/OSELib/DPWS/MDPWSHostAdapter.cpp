/*
 * MDPWSHostAdapter.cpp
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 20.08.2019, baumeister
 *
 */

#include "OSELib/DPWS/MDPWSHostAdapter.h"
#include "OSELib/DPWS/DPWSCommon.h"


using namespace OSELib::DPWS;

MDPWSHostAdapter::MDPWSHostAdapter(SDCLib::Config::NetworkConfig_shared_ptr p_config,
		const AddressType & p_epr,
		const ScopesType & p_scopes,
		const TypesType & p_types,
		const XAddressesType & p_xaddresses,
		int p_metadataVersion)
: m_epr(p_epr)
, m_scopes(p_scopes)
, m_types(p_types)
, m_xaddresses(p_xaddresses)
, m_metadataVersion(p_metadataVersion)
, m_impl(new Impl::DPWSHostSocketImpl(p_config, *this, *this))
{ }

void MDPWSHostAdapter::start()
{
	m_started = true;
	sendHello();
}

void MDPWSHostAdapter::stop()
{
	EndpointReferenceType t_epr(m_epr);
	ByeType t_bye(t_epr);
	m_impl->sendBye(t_bye);
	m_started = false;
}

void MDPWSHostAdapter::setScopes(const ScopesType & p_scopes)
{
	m_scopes = p_scopes;
	++m_metadataVersion;
	sendHello();
}

void MDPWSHostAdapter::setTypes(const TypesType & p_types)
{
	m_types.clear();
	std::copy(p_types.begin(), p_types.end(), std::back_inserter(m_types));
	++m_metadataVersion;
	sendHello();
}

void MDPWSHostAdapter::setXAddresses(const XAddressesType & p_xaddresses)
{
	m_xaddresses = p_xaddresses;
	++m_metadataVersion;
	sendHello();
}

void MDPWSHostAdapter::sendStream(const MDM::WaveformStream & p_stream)
{
	m_impl->sendStream(p_stream, AddressType(m_epr));
}

void MDPWSHostAdapter::sendHello()
{
	if (! m_started) {
		return;
	}
	HelloType t_hello(m_epr, m_metadataVersion);
	if (! m_scopes.empty()) {
		t_hello.Scopes(m_scopes);
	}
	if (! m_types.empty()) {
		t_hello.Types(m_types);
	}
	if (! m_xaddresses.empty()) {
		t_hello.XAddrs(m_xaddresses);
	}
	m_impl->sendHello(t_hello);
}

std::vector<ProbeMatchType> MDPWSHostAdapter::dispatch(const ProbeType & p_filter)
{
	ProbeMatchType t_match(m_epr, m_metadataVersion);
	if (! m_scopes.empty()) {
		t_match.Scopes(m_scopes);
	}
	if (! m_types.empty()) {
		t_match.Types(m_types);
	}
	if (! m_xaddresses.empty()) {
		t_match.XAddrs(m_xaddresses);
	}
	std::vector<ProbeMatchType> t_result;
	if (! Impl::compare(p_filter, t_match)) {
		return t_result;
	} else {
		t_result.push_back(t_match);
		return t_result;
	}
	// fixme: explicit return "else part" here
}

std::unique_ptr<ResolveMatchType> MDPWSHostAdapter::dispatch(const ResolveType & p_filter)
{
	std::unique_ptr<ResolveMatchType> t_result(new ResolveMatchType(m_epr, m_metadataVersion));
	if (! m_scopes.empty()) {
		t_result->Scopes(m_scopes);
	}
	if (! m_types.empty()) {
		t_result->Types(m_types);
	}
	if (! m_xaddresses.empty()) {
		t_result->XAddrs(m_xaddresses);
	}
	if (! Impl::compare(p_filter, *t_result)) {
		return nullptr;
	} else {
		return t_result;
	}
	// fixme: explicit return "else part" here
}
