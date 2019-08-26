/*
 * MessagingContext.cpp
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 26.08.2019, baumeister
 */

#include "OSELib/DPWS/MessagingContext.h"

#include "wsdd-discovery-1.1-schema-os.hxx"
#include "config/config.h"

#include <chrono>


namespace OSELib {
namespace DPWS {
namespace Impl {

MessagingContext::MessagingContext()
{
    // NOTE: This was the old, hard coded value
    assert(SDCLib::Config::SDC_MAX_KNOWN_MESSAGE_IDS > 100);
}
bool MessagingContext::registerMessageId(const std::string & p_id)
{
	if(p_id.empty()) {
		return false;
	}
    std::lock_guard<std::mutex> t_lock(m_mutex_messageID);
	if (std::find(ml_knownMessageIds.begin(), ml_knownMessageIds.end(), p_id) != ml_knownMessageIds.end()) {
		return false;
	}
    if (ml_knownMessageIds.size() >= SDCLib::Config::SDC_MAX_KNOWN_MESSAGE_IDS) {
        ml_knownMessageIds.pop_back();
    }
    ml_knownMessageIds.push_front(p_id);
    return true;
}

void MessagingContext::clearAppSequenceCache()
{
    std::lock_guard<std::mutex> t_lock(m_mutex_appSequence);
	ml_knownAppsequences.clear();
}

void MessagingContext::resetInstanceId()
{
    //FIXME: Is this valid?
	m_instanceId = std::chrono::system_clock::now().time_since_epoch().count() / 1000000;
}

unsigned long long int MessagingContext::getInstanceId() const
{
	return m_instanceId;
}

unsigned long long int MessagingContext::getCurrentMessageCounter() const
{
	return m_messageCounter;
}

unsigned long long int MessagingContext::getNextMessageCounter()
{
	return ++m_messageCounter;
}

bool MessagingContext::registerAppSequence(::WS::DISCOVERY::AppSequenceType & p_appSequence)
{
	if (p_appSequence.SequenceId().present()) {
		return registerAppSequence(p_appSequence.InstanceId(), p_appSequence.MessageNumber(), p_appSequence.SequenceId().get());
	}
    return registerAppSequence(p_appSequence.InstanceId(), p_appSequence.MessageNumber());
}

bool MessagingContext::registerAppSequence(unsigned long long int p_instanceId, unsigned long long int p_messageNumber, const std::string & p_sequenceId)
{
    std::lock_guard<std::mutex> t_lock(m_mutex_appSequence);

	auto t_appsequenceIterator = ml_knownAppsequences.find(p_instanceId);
	if (t_appsequenceIterator == ml_knownAppsequences.end()) {
		// instance id unknown => add new mapping and store sequence id and message number
		SequenceMapping sequenceMapping;
		sequenceMapping[p_sequenceId] = p_messageNumber;
		ml_knownAppsequences[p_instanceId] = sequenceMapping;
		return true;
	}
	// instance id known => search for sequence id
	SequenceMapping & t_sequenceMapping(t_appsequenceIterator->second);
	auto t_sequenceMappingIterator = t_sequenceMapping.find(p_sequenceId);
	if (t_sequenceMappingIterator == t_sequenceMapping.end()) {
		//instance id known, sequence id unknown => add new mapping and store message number
		t_sequenceMapping[p_sequenceId] = p_messageNumber;
		return true;
	}

	// instance id and sequence id known => compare message number
	if (t_sequenceMappingIterator->second < p_messageNumber) {
		// message number is newer than cached value => accept and update
		t_sequenceMappingIterator->second = p_messageNumber;
		return true;
	}

	// instance id and sequence id known, cached message number is higher than received value => reject new value
	return false;
}

}
}
}
