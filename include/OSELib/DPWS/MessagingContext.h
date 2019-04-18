/*
 * MessagingContext.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef MESSAGINGCONTEXT_H_
#define MESSAGINGCONTEXT_H_

#include <deque>
#include <string>

#include "wsdd-discovery-1.1-schema-os-fwd.hxx"

#include "Poco/Mutex.h"

namespace OSELib {
namespace DPWS {
namespace Impl {

class MessagingContext {
public:
	MessagingContext();
	~MessagingContext();

	bool registerMessageId(const std::string & id);
	void clearAppSequenceCache();

	void resetInstanceId();

	unsigned long long int getInstanceId() const;
	unsigned long long int getCurrentMessageCounter() const;
	unsigned long long int getNextMessageCounter();
	bool registerAppSequence(::WS::DISCOVERY::AppSequenceType & appSequence);
	bool registerAppSequence(unsigned long long int instanceId, unsigned long long int messageNumber, const std::string & sequenceId = "NULL");

private:
	unsigned long long int _instanceId;
	unsigned long long int _messageCounter;

	std::deque<std::string> _knownMessageIds;
	mutable Poco::FastMutex _knownMessageIdsMutex;
	typedef std::map<std::string, unsigned long long int> SequenceMapping;
	std::map<unsigned long long  int, SequenceMapping> _knownAppsequences;
};

} /* namespace Impl */
} /* namespace DPWS */
} /* namespace OSELib */

#endif /* MESSAGINGCONTEXT_H_ */
