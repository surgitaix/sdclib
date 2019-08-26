/*
 * MDPWSDiscoveryClientAdapter.cpp
 *
 *  Created on: 11.12.2015, matthias
 *  Modified on: 23.08.2019, baumeister
 */

#include "OSELib/DPWS/MDPWSDiscoveryClientAdapter.h"
#include "OSELib/DPWS/DPWSCommon.h"

#include "NormalizedMessageModel.hxx"

namespace OSELib {
namespace DPWS {

MDPWSDiscoveryClientAdapter::MDPWSDiscoveryClientAdapter(SDCLib::Config::NetworkConfig_shared_ptr p_config)
: m_impl(new Impl::DPWSDiscoveryClientSocketImpl(p_config, *this, *this, *this, *this))
{ }

void MDPWSDiscoveryClientAdapter::addProbeMatchEventHandler(const ProbeType p_filter, ProbeMatchCallback & p_callback)
{
	std::lock_guard<std::mutex> t_lock(m_mutex);
	ml_probeMatchHandlers.push_back(ProbeMatchHandler(p_filter, &p_callback));
	m_impl->sendProbe(p_filter);
}

void MDPWSDiscoveryClientAdapter::removeProbeMatchEventHandler(ProbeMatchCallback & p_callback)
{
	std::lock_guard<std::mutex> t_lock(m_mutex);
	auto t_iterator = std::find_if(ml_probeMatchHandlers.begin(), ml_probeMatchHandlers.end(), [&](const ProbeMatchHandler & p_handler) { return std::get<1>(p_handler) == &p_callback; } );
	if (t_iterator != ml_probeMatchHandlers.end()) {
		ml_probeMatchHandlers.erase(t_iterator);
	}
}

void MDPWSDiscoveryClientAdapter::addResolveMatchEventHandler(const ResolveType p_filter, ResolveMatchCallback & p_callback)
{
	std::lock_guard<std::mutex> t_lock(m_mutex);
	ml_resolveMatchHandlers.push_back(ResolveMatchHandler(p_filter, &p_callback));
	m_impl->sendResolve(p_filter);
}

void MDPWSDiscoveryClientAdapter::removeResolveMatchEventHandler(ResolveMatchCallback & p_callback)
{
	std::lock_guard<std::mutex> t_lock(m_mutex);
	auto t_iterator = std::find_if(ml_resolveMatchHandlers.begin(), ml_resolveMatchHandlers.end(), [&](const ResolveMatchHandler & p_handler) { return std::get<1>(p_handler) == &p_callback; } );
	if (t_iterator != ml_resolveMatchHandlers.end()) {
		ml_resolveMatchHandlers.erase(t_iterator);
	}
}

void MDPWSDiscoveryClientAdapter::addHelloEventHandler(HelloCallback & p_callback)
{
	std::lock_guard<std::mutex> t_lock(m_mutex);
	// FIXME: No check if double entries exist needed here?
	ml_helloHandlers.push_back(&p_callback);
}

void MDPWSDiscoveryClientAdapter::removeHelloEventHandler(HelloCallback & p_callback)
{
	std::lock_guard<std::mutex> t_lock(m_mutex);
	auto t_iterator = std::find(ml_helloHandlers.begin(), ml_helloHandlers.end(), &p_callback);
	if (t_iterator != ml_helloHandlers.end()) {
		ml_helloHandlers.erase(t_iterator);
	}
}

void MDPWSDiscoveryClientAdapter::addByeEventHandler(ByeCallback & p_callback)
{
	std::lock_guard<std::mutex> t_lock(m_mutex);
	// FIXME: No check if double entries exist needed here?
	ml_byeHandlers.push_back(&p_callback);
}

void MDPWSDiscoveryClientAdapter::removeByeEventHandler(ByeCallback & p_callback)
{
	std::lock_guard<std::mutex> t_lock(m_mutex);
	auto t_iterator = std::find(ml_byeHandlers.begin(), ml_byeHandlers.end(), &p_callback);
	if (t_iterator != ml_byeHandlers.end()) {
		ml_byeHandlers.erase(t_iterator);
	}
}

void MDPWSDiscoveryClientAdapter::dispatch(const ProbeMatchType & p_notification)
{
	std::lock_guard<std::mutex> t_lock(m_mutex);
	std::vector<ProbeMatchHandler> t_matchingHandlers;
	for (const auto & t_handler : ml_probeMatchHandlers) {
		if (Impl::compare(std::get<0>(t_handler), p_notification)) {
			t_matchingHandlers.push_back(t_handler);
		}
	};
	for (const auto & t_handler : t_matchingHandlers) {
		std::get<1>(t_handler)->probeMatch(p_notification);
	}
}

void MDPWSDiscoveryClientAdapter::dispatch(const ResolveMatchType & p_notification)
{
	std::lock_guard<std::mutex> t_lock(m_mutex);
	std::vector<ResolveMatchHandler> t_matchingHandlers;
	for (const auto & t_handler : ml_resolveMatchHandlers) {
		if (Impl::compare(std::get<0>(t_handler), p_notification)) {
			t_matchingHandlers.push_back(t_handler);
		}
	}
	for (const auto & t_handler : t_matchingHandlers) {
		std::get<1>(t_handler)->resolveMatch(p_notification);
	}
}

void MDPWSDiscoveryClientAdapter::dispatch(const ByeType & p_notification)
{
	std::lock_guard<std::mutex> t_lock(m_mutex);
	for (auto & t_callback : ml_byeHandlers) {
		t_callback->bye(p_notification);
	}
}

void MDPWSDiscoveryClientAdapter::dispatch(const HelloType & p_notification)
{
	std::lock_guard<std::mutex> t_lock(m_mutex);
	for (auto & t_callback : ml_helloHandlers) {
		t_callback->hello(p_notification);
	}
}

}
}
