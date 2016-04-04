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

/**
 *  @file CommunicationManager.h
 *  @project OSCLib
 *  @date 05.07.2011
 *  @author Besting
 *  @copyright (c) SurgiTAIX AG
 */

#ifndef COMMUNICATIONMANAGER_H_
#define COMMUNICATIONMANAGER_H_

#include <set>

#include "NetworkInterface.h"
#include "MulticastCallback.h"
#include "UnicastCallback.h"

namespace OSCLib {

class OSCLibrary;

namespace Dev {
	class Device;
}

namespace Comm {

class CommunicationManager;

typedef std::set<CommunicationManager*> ManagerSet;

class CommunicationManager : public MulticastCallback, public UnicastCallback {

	friend class Dev::Device;
	friend class OSCLib::OSCLibrary;

public:
	CommunicationManager();
	virtual ~CommunicationManager();

	virtual std::string getProtocolDomain() const = 0;

protected:
	OSCLib::Dev::Device* device;

	virtual void startManager() = 0;
	virtual void stopManager() = 0;

private:
	void init(Dev::Device* device);
	void shutdown();
};

}
}

#endif /* COMMUNICATIONMANAGER_H_ */
