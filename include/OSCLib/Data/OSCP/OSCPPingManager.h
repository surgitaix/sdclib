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
 * OSCPPingManager.h
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: roehser, besting
 */

#ifndef OSCPPINGMANAGER_H_
#define OSCPPINGMANAGER_H_

#include "OSCLib/Util/Task.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"

#include "Poco/Mutex.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

class OSCPPingManager : public Util::Task {
public:
	OSCPPingManager(OSCPConsumer & consumer);
	virtual ~OSCPPingManager();

	void runImpl();
	void detachConsumer();

private:
	Poco::Mutex mutex;
	OSCPConsumer * consumer;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* OSCPPINGMANAGER_H_ */
