/*
 * MDPWSDiscoveryClientAdapter.cpp
 *
 *  Created on: 11.12.2015, matthias
 *  Modified on: 23.08.2019, baumeister
 */

#include "OSELib/DPWS/MDPWSDiscoveryClientAdapter.h"
#include "OSELib/DPWS/DPWSCommon.h"

#include "DataModel/NormalizedMessageModel.hxx"

using namespace OSELib;
using namespace OSELib::DPWS;

MDPWSDiscoveryClientAdapter::MDPWSDiscoveryClientAdapter(SDCLib::Config::NetworkConfig_shared_ptr p_config)
    : m_impl(new Impl::DPWSDiscoveryClientSocketImpl(p_config, *this, *this, *this, *this))
{
}
MDPWSDiscoveryClientAdapter::~MDPWSDiscoveryClientAdapter() = default;

void MDPWSDiscoveryClientAdapter::addProbeMatchEventHandler(const ProbeType p_filter, ProbeMatchCallback& p_callback)
{
    std::lock_guard<std::mutex> lock(m_mutex_probe);
    m_probeMatchHandlers.push_back(ProbeMatchHandler(p_filter, &p_callback));
    m_impl->sendProbe(p_filter);
}

void MDPWSDiscoveryClientAdapter::removeProbeMatchEventHandler(ProbeMatchCallback& p_callback)
{
    std::lock_guard<std::mutex> lock(m_mutex_probe);
    auto iterator = std::find_if(m_probeMatchHandlers.begin(), m_probeMatchHandlers.end(), [&](const ProbeMatchHandler& p_handler) {
        return std::get<1>(p_handler) == &p_callback;
    });
    if(iterator != m_probeMatchHandlers.end())
    {
        m_probeMatchHandlers.erase(iterator);
    }
}

void MDPWSDiscoveryClientAdapter::addResolveMatchEventHandler(const ResolveType p_filter, ResolveMatchCallback& p_callback)
{
    std::lock_guard<std::mutex> lock(m_mutex_resolve);
    m_resolveMatchHandlers.push_back(ResolveMatchHandler(p_filter, &p_callback));
    m_impl->sendResolve(p_filter);
}

void MDPWSDiscoveryClientAdapter::removeResolveMatchEventHandler(ResolveMatchCallback& p_callback)
{
    std::lock_guard<std::mutex> lock(m_mutex_resolve);
    auto iterator = std::find_if(m_resolveMatchHandlers.begin(), m_resolveMatchHandlers.end(), [&](const ResolveMatchHandler& p_handler) {
        return std::get<1>(p_handler) == &p_callback;
    });
    if(iterator != m_resolveMatchHandlers.end())
    {
        m_resolveMatchHandlers.erase(iterator);
    }
}

void MDPWSDiscoveryClientAdapter::addHelloEventHandler(HelloCallback& p_callback)
{
    std::lock_guard<std::mutex> lock(m_mutex_hello);
    // FIXME: No check if double entries exist needed here?
    m_helloHandlers.push_back(&p_callback);
}

void MDPWSDiscoveryClientAdapter::removeHelloEventHandler(HelloCallback& p_callback)
{
    std::lock_guard<std::mutex> lock(m_mutex_hello);
    auto iterator = std::find(m_helloHandlers.begin(), m_helloHandlers.end(), &p_callback);
    if(iterator != m_helloHandlers.end())
    {
        m_helloHandlers.erase(iterator);
    }
}

void MDPWSDiscoveryClientAdapter::addByeEventHandler(ByeCallback& p_callback)
{
    std::lock_guard<std::mutex> lock(m_mutex_bye);
    // FIXME: No check if double entries exist needed here?
    m_byeHandlers.push_back(&p_callback);
}

void MDPWSDiscoveryClientAdapter::removeByeEventHandler(ByeCallback& p_callback)
{
    std::lock_guard<std::mutex> lock(m_mutex_bye);
    auto iterator = std::find(m_byeHandlers.begin(), m_byeHandlers.end(), &p_callback);
    if(iterator != m_byeHandlers.end())
    {
        m_byeHandlers.erase(iterator);
    }
}

void MDPWSDiscoveryClientAdapter::dispatch(const ProbeMatchType& p_notification)
{
    std::vector<ProbeMatchHandler> matchingHandlers;
    {  // LOCK
        std::lock_guard<std::mutex> lock(m_mutex_probe);
        for(const auto& handler : m_probeMatchHandlers)
        {
            if(Impl::compare(std::get<0>(handler), p_notification))
            {
                matchingHandlers.push_back(handler);
            }
        };
    }  // UNLOCK
    for(const auto& handler : matchingHandlers)
    {
        std::get<1>(handler)->probeMatch(p_notification);
    }
}

void MDPWSDiscoveryClientAdapter::dispatch(const ResolveMatchType& p_notification)
{
    std::vector<ResolveMatchHandler> matchingHandlers;
    {  // LOCK
        std::lock_guard<std::mutex> lock(m_mutex_resolve);
        for(const auto& handler : m_resolveMatchHandlers)
        {
            if(Impl::compare(std::get<0>(handler), p_notification))
            {
                matchingHandlers.push_back(handler);
            }
        }
    }  // UNLOCK
    for(const auto& handler : matchingHandlers)
    {
        std::get<1>(handler)->resolveMatch(p_notification);
    }
}

void MDPWSDiscoveryClientAdapter::dispatch(const ByeType& p_notification)
{
    std::lock_guard<std::mutex> lock(m_mutex_bye);
    for(auto& callback : m_byeHandlers)
    {
        callback->bye(p_notification);
    }
}

void MDPWSDiscoveryClientAdapter::dispatch(const HelloType& p_notification)
{
    std::lock_guard<std::mutex> lock(m_mutex_hello);
    for(auto& callback : m_helloHandlers)
    {
        callback->hello(p_notification);
    }
}
