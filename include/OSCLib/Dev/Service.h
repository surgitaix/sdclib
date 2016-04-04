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
 *  @file Service.h
 *  @project OSCLib
 *  @date 16.08.2011
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 */


#ifndef SERVICE_H_
#define SERVICE_H_

#include "Entity.h"
#include "OSCLib/Data/Operation.h"
#include "OSCLib/Data/SubscriptionVector.h"

#include <atomic>

namespace OSCLib {

namespace Data {
	class EventSource;
	class Subscription;
	class QName;
}

namespace Dev {

class Device;

class Service : public Entity {
public:
	Service();
	virtual ~Service();
    void configureDefaultDPWS11();
    Dev::Device * getParentDevice();
    void setParentDevice(Dev::Device * parentDevice);
    void start();
    void stop();
    bool isRunning() const;

    const std::string & getServiceId() const;
    void setServiceId(const std::string & id);

    const Data::OperationVector & getOperations() const;
    std::shared_ptr<Data::Operation> getOperation(const std::string & action) const;
    void addOperation(std::shared_ptr<Data::Operation> op);

    void addSubscription(std::shared_ptr<Data::Subscription> subscription);
    void cleanExpiredSubscriptions();
    std::vector<std::shared_ptr<Data::Subscription>> getActiveSubscriptions(const std::string & actionString);
    bool renewSubscription(const std::string & ident, const std::string & expires);
    void cancelSubscription(const std::string & ident);

    std::string getStaticWSDL();
    void setStaticWSDLContent(const std::string & content);
    void addSchemaFile(const std::string & requestURL, const std::string & content);
    std::map<std::string, std::string> getSchemaFiles() const;

    void addEvent(std::shared_ptr<Data::EventSource> event);

    // Return the parent device's scopes
    const Util::StringVector & getScopes() const;
    virtual void clearScopes();

private:
    Dev::Device * parentDevice;
	Data::OperationVector operations;
	Data::SubscriptionVector subscriptions;
	std::string serviceId;
    std::string staticWSDLContent;
    std::map<std::string, std::string> schemaFiles;
    std::atomic<bool> running;
};

} /* namespace Device */
} /* namespace OSCLib */
#endif /* SERVICE_H_ */
