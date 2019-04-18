/*
 * MessagingContext.cpp
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#include <chrono>

#include "wsdd-discovery-1.1-schema-os.hxx"

#include "OSELib/DPWS/MessagingContext.h"

namespace OSELib {
namespace DPWS {
namespace Impl {

MessagingContext::MessagingContext() :
	_instanceId(0),
	_messageCounter(0)
{
}

MessagingContext::~MessagingContext() {
}

bool MessagingContext::registerMessageId(const std::string & id) {
	//not thread-safe due to pop_back...
	Poco::FastMutex::ScopedLock lock(_knownMessageIdsMutex);
	if (std::find(_knownMessageIds.begin(), _knownMessageIds.end(), id) != _knownMessageIds.end()) {
		return false;
	} else {
		if (_knownMessageIds.size() >= 100) {
			_knownMessageIds.pop_back();
		}
		_knownMessageIds.push_front(id);
		return true;
	}
}

void MessagingContext::clearAppSequenceCache() {
	_knownAppsequences.clear();
}

void MessagingContext::resetInstanceId() {
	_instanceId = std::chrono::system_clock::now().time_since_epoch().count() / 1000000;
}

unsigned long long int MessagingContext::getInstanceId() const {
	return _instanceId;
}

unsigned long long int MessagingContext::getCurrentMessageCounter() const {
	return _messageCounter;
}

unsigned long long int MessagingContext::getNextMessageCounter() {
	return ++_messageCounter;
}

bool MessagingContext::registerAppSequence(::WS::DISCOVERY::AppSequenceType & appSequence) {
	if (appSequence.SequenceId().present()) {
		return registerAppSequence(appSequence.InstanceId(), appSequence.MessageNumber(), appSequence.SequenceId().get());
	} else {
		return registerAppSequence(appSequence.InstanceId(), appSequence.MessageNumber());
	}
}

bool MessagingContext::registerAppSequence(unsigned long long int instanceId, unsigned long long int messageNumber, const std::string & sequenceId) {
	auto appsequenceIterator = _knownAppsequences.find(instanceId);
	if (appsequenceIterator == _knownAppsequences.end()) {
		// instance id unknown => add new mapping and store sequence id and message number
		SequenceMapping sequenceMapping;
		sequenceMapping[sequenceId] = messageNumber;
		_knownAppsequences[instanceId] = sequenceMapping;
		return true;
	}
	// instance id known => search for sequence id
	SequenceMapping & sequenceMapping(appsequenceIterator->second);
	auto sequenceMappingIterator = sequenceMapping.find(sequenceId);
	if (sequenceMappingIterator == sequenceMapping.end()) {
		//instance id known, sequence id unknown => add new mapping and store message number
		sequenceMapping[sequenceId] = messageNumber;
		return true;
	}

	// instance id and sequence id known => compare message number
	if (sequenceMappingIterator->second < messageNumber) {
		// message number is newer than cached value => accept and update
		sequenceMappingIterator->second = messageNumber;
		return true;
	}

	// instance id and sequence id known, cached message number is higher than received value => reject new value
	return false;
}

} /* namespace Impl */
} /* namespace DPWS */
} /* namespace OSELib */
