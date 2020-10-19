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
 * FutureInvocationState.cpp
 *
 *  @Copyright (C) 2015, SurgiTAIX AG
 *  Author: besting, röhser
 *  Modified on: 07.09.2020, baumeister
 *
 */

#include "SDCLib/Data/SDC/FutureInvocationState.h"
#include "SDCLib/Data/SDC/SDCConsumer.h"

using namespace SDCLib;
using namespace SDCLib::Data;
using namespace SDCLib::Data::SDC;

FutureInvocationState::FutureInvocationState()
{
    ml_invocationEvents[InvocationState::Cnclld] = std::shared_ptr<Poco::Event>(new Poco::Event(false));
    ml_invocationEvents[InvocationState::CnclldMan] = std::shared_ptr<Poco::Event>(new Poco::Event(false));
    ml_invocationEvents[InvocationState::Fail] = std::shared_ptr<Poco::Event>(new Poco::Event(false));
    ml_invocationEvents[InvocationState::Fin] = std::shared_ptr<Poco::Event>(new Poco::Event(false));
    ml_invocationEvents[InvocationState::FinMod] = std::shared_ptr<Poco::Event>(new Poco::Event(false));
    ml_invocationEvents[InvocationState::Start] = std::shared_ptr<Poco::Event>(new Poco::Event(false));
    ml_invocationEvents[InvocationState::Wait] = std::shared_ptr<Poco::Event>(new Poco::Event(false));
}

FutureInvocationState::~FutureInvocationState()
{
    if(nullptr != m_consumer)
    {
        m_consumer->unregisterFutureInvocationListener(m_transactionId);
    }
}


bool FutureInvocationState::waitReceived(InvocationState p_expected, int p_timeout)
{
    auto t_event = ml_invocationEvents[p_expected];
    if(nullptr == t_event)
    {
        return false;
    }
    return t_event->tryWait(p_timeout);
}

int FutureInvocationState::getTransactionId() const
{
    return m_transactionId;
}

void FutureInvocationState::setEvent(InvocationState p_actual)
{
    ml_invocationEvents[p_actual]->set();
}
