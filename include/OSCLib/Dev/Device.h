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
 *  @file Device.h
 *  @project OSCLib
 *  @date 05.07.2011
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 */

#ifndef DEVICE_H_
#define DEVICE_H_

#include "DeviceCharacteristics.h"
#include "Entity.h"
#include "Service.h"
#include "OSCLib/Comm/CommunicationManager.h"
#include "Poco/Mutex.h"

#include <atomic>

namespace OSCLib {
namespace Dev {

class Device;

typedef std::vector<std::shared_ptr<Service>> ServiceVector;
typedef std::set<std::shared_ptr<Dev::Device>> DeviceSet;

class Device : public Entity {

public:
	Device();
	virtual ~Device();

    const DeviceCharacteristics & getDeviceCharacteristics() const;
    void setDeviceCharacteristics(const DeviceCharacteristics & description);

    int getMetaDataVersion() const;
    void setMetaDataVersion(int metaDataVersion);
    int getInstanceId() const;
    int getMessageNumber() const;
    void setInstanceId(int instanceId);
    void setMessageNumber(int messageNumber);
    void incMessageNumber();

    const Util::StringVector & getScopes() const;
    virtual void clearScopes();
    void addScope(const std::string & scope);
    void addScopes(const Util::StringVector & scopes);

    void addManager(Comm::CommunicationManager* man);
    Comm::CommunicationManager * getDefaultCommunicationManager(const std::string & protocol);

    const std::shared_ptr<Service> getService(unsigned int index) const;

    ServiceVector getServices();

    size_t getServiceCount() const;
    void addService(std::shared_ptr<Service> service);
    void removeService(std::shared_ptr<Service> service);

    Poco::Mutex & getServicesMutex() const {
        return mutexServices;
    }

    virtual void start();
    virtual void stop();
    bool isRunning() const;

    void clearManagersWithoutDelete();
    void clearManagersAndDelete();

	void setLocalAdapterAddress(const std::string & adr) {
		localAdapterAddress = adr;
	}

	std::string getLocalAdapterAddress() {
		return localAdapterAddress;
	}

private:
	DeviceCharacteristics description;
	std::string localAdapterAddress;
	int metaDataVersion;
	int instanceId;
	std::atomic<int> messageNumber;
	std::atomic<bool> running;

	Util::StringVector scopes;
	ServiceVector services;
	Comm::ManagerSet managers;

    void configureDefaultDPWS11();
	void addDefaultCharacteristics();
	mutable Poco::Mutex mutexServices;
    mutable Poco::Mutex mutexManagers;
};

}
}

#endif /* DEVICE_H_ */
