/*
 * MessagingContext.h
 *
 *  Created on: 18.07.2019
 *      Author: matthias, baumeister
 */

#ifndef MESSAGINGCONTEXT_H_
#define MESSAGINGCONTEXT_H_

#include <deque>
#include <string>
#include <mutex>
#include <map>
#include <atomic>

#include "wsdd-discovery-1.1-schema-os-fwd.hxx"

namespace OSELib {
namespace DPWS {
namespace Impl {

class MessagingContext
{
private:

    std::mutex m_mutex_messageID;
    std::mutex m_mutex_appSequence;

	std::atomic_ullong _instanceId = ATOMIC_VAR_INIT(0);
	std::atomic_ullong _messageCounter = ATOMIC_VAR_INIT(0);

	std::deque<std::string> _knownMessageIds;
	using SequenceMapping = std::map<std::string, unsigned long long int>;
	std::map<unsigned long long  int, SequenceMapping> _knownAppsequences;

public:

    // Special Member Functions
	MessagingContext();
    MessagingContext(const MessagingContext& p_obj) = delete;
    MessagingContext(MessagingContext&& p_obj) = delete;
    MessagingContext& operator=(const MessagingContext& p_obj) = delete;
    MessagingContext& operator=(MessagingContext&& p_obj) = delete;
	~MessagingContext() = default;

	bool registerMessageId(const std::string & id);
	void clearAppSequenceCache();

	void resetInstanceId();

	unsigned long long int getInstanceId() const;
	unsigned long long int getCurrentMessageCounter() const;
	unsigned long long int getNextMessageCounter();
	bool registerAppSequence(WS::DISCOVERY::AppSequenceType & appSequence);
	bool registerAppSequence(unsigned long long int instanceId, unsigned long long int messageNumber, const std::string & sequenceId = "NULL");
};

} /* namespace Impl */
} /* namespace DPWS */
} /* namespace OSELib */

#endif /* MESSAGINGCONTEXT_H_ */
