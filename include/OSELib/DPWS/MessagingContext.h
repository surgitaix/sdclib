/*
 * MessagingContext.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 26.08.2019, baumeister
 *
 */

#ifndef OSELIB_DPWS_IMPL_MESSAGINGCONTEXT_H_
#define OSELIB_DPWS_IMPL_MESSAGINGCONTEXT_H_

#include <deque>
#include <string>
#include <mutex>
#include <map>
#include <atomic>

#include "wsdd-discovery-1.1-schema-os-fwd.hxx"

namespace OSELib
{
	namespace DPWS
	{
		namespace Impl
		{
			class MessagingContext
			{
			private:

				std::mutex m_mutex_messageID;
				std::mutex m_mutex_appSequence;

				std::atomic_ullong m_instanceId = ATOMIC_VAR_INIT(0);
				std::atomic_ullong m_messageCounter = ATOMIC_VAR_INIT(0);

				std::deque<std::string> ml_knownMessageIds;
				using SequenceMapping = std::map<std::string, unsigned long long int>;
				std::map<unsigned long long  int, SequenceMapping> ml_knownAppsequences;

			public:

				// Special Member Functions
				MessagingContext();
				MessagingContext(const MessagingContext& p_obj) = delete;
				MessagingContext(MessagingContext&& p_obj) = delete;
				MessagingContext& operator=(const MessagingContext& p_obj) = delete;
				MessagingContext& operator=(MessagingContext&& p_obj) = delete;
				~MessagingContext() = default;

				bool registerMessageId(const std::string & p_id);
				void clearAppSequenceCache();

				void resetInstanceId();

				unsigned long long int getInstanceId() const;
				unsigned long long int getCurrentMessageCounter() const;
				unsigned long long int getNextMessageCounter();
				bool registerAppSequence(WS::DISCOVERY::AppSequenceType & p_appSequence);
				bool registerAppSequence(unsigned long long int instanceId, unsigned long long int p_messageNumber, const std::string & p_sequenceId = "NULL");
			};
		}
	}
}

#endif
