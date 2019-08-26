/**
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  *
  */

/*
 * FutureInvocationState.h
 *
 *  @Copyright (C) 2015, SurgiTAIX AG
 *  Author: besting, röhser
 *	Modified on: 26.08.2019, baumeister
 *
 */

#ifndef SDCLIB_DATA_SDC_FUTURETRANSACTIONSTATE_H_
#define SDCLIB_DATA_SDC_FUTURETRANSACTIONSTATE_H_

#include "SDCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include <Poco/Event.h>

#include <mutex>
#include <map>
#include <memory>
#include <atomic>

namespace SDCLib
{
	namespace Data
	{
		namespace SDC
		{
			class SDCConsumer;

			class FutureInvocationState
			{
				friend class SDCConsumer;
			private:

				std::atomic<int> m_transactionId = ATOMIC_VAR_INIT(-1);
				SDCConsumer * m_consumer = nullptr;
				std::mutex m_mutex;

				std::map<InvocationState, std::shared_ptr<Poco::Event>> ml_invocationEvents;

			public:

				// Special Member Functions
				FutureInvocationState();
				FutureInvocationState(const FutureInvocationState& p_obj) = delete;
				FutureInvocationState(FutureInvocationState&& p_obj) = delete;
				FutureInvocationState& operator=(const FutureInvocationState& p_obj) = delete;
				FutureInvocationState& operator=(FutureInvocationState&& p_obj) = delete;
				virtual ~FutureInvocationState();

				bool waitReceived(InvocationState p_expected, int p_timeout);

				int getTransactionId() const;

			private:

				void setEvent(InvocationState p_actual);

			};

		}
	}
}

#endif
