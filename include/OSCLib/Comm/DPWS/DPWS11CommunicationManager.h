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
*  @file DPWS11CommunicationManager.h
*  @project OSCLib
*  @date 24.08.2011
*  @author besting
*  @copyright (c) SurgiTAIX AG
*/


#ifndef DPWSCOMMUNICATIONMANAGER_H_
#define DPWSCOMMUNICATIONMANAGER_H_

#include "OSCLib/Comm/AbstractBinding.h"
#include "OSCLib/Comm/CommunicationManager.h"
#include "OSCLib/Util/StringVector.h"
#include "Poco/Mutex.h"
#include "Poco/NotificationQueue.h"

#include <list>
#include <map>
#include <set>
#include <memory>

namespace Poco {
    class ThreadPool;
namespace Net {
    class HTTPServer;
    class HTTPClientSession;
}
}

namespace OSCLib {
namespace Dev {
    class Service;
}
namespace Comm {

class Message;
class Binding;
class HTTPClientExchanger;

namespace DPWS {

class DPWS11Message;
class DPWS11ActionHandler;

class DPWS11CommunicationManager : public OSCLib::Comm::CommunicationManager {
    friend class DPWSHttpRequestHandler;
public:
    DPWS11CommunicationManager();
    virtual ~DPWS11CommunicationManager();

    bool sendMessage(DPWS11Message & msg);

    virtual std::shared_ptr<OSCLib::Comm::Message> udpMulticastCallback(const Message & msg) override;
    virtual std::shared_ptr<OSCLib::Comm::Message> unicastCallback(const Message & msg) override;

    std::string getProtocolDomain() const override;
    
    void addDPWSActionHandler(const std::string & action, std::shared_ptr<DPWS11ActionHandler> handler);
    std::shared_ptr<DPWS11ActionHandler> getDPWSActionHandler(const std::string & action);



protected:

    void startManager() override;
    void stopManager() override;

    void injectService(std::shared_ptr<OSCLib::Dev::Service> s);
    void withdrawService(std::shared_ptr<OSCLib::Dev::Service> s);
    void injectBinding(std::shared_ptr<AbstractBinding> binding);
    void withdrawBinding(std::shared_ptr<AbstractBinding> binding);

    bool validateMsgId(const std::string & id);
    void trackMsgId(const std::string & id);

    void addKnownCustomAction(const std::string & action);
    Util::StringVector getKnownCustomActions() const;
    void removeKnownCustomAction(const std::string & action);
    void registerListener(std::shared_ptr<AbstractBinding> b);
    void unregisterListener(std::shared_ptr<AbstractBinding> b);

    std::map<std::string, std::shared_ptr<DPWS11ActionHandler> > actionHandlers;

private:
    std::shared_ptr<Poco::ThreadPool> threadPool;
    std::shared_ptr<HTTPClientExchanger> cmHttpExchanger;
    std::map<std::string, std::shared_ptr<Poco::Net::HTTPServer>> httpServers;
    std::set<std::string> knownCustomActions;
    Poco::NotificationQueue invokerQueue;

    int getRequestedServiceIndex(DPWS11Message & dpws11Msg, const std::string & getPath = "");

    int getServiceIndexByActionString(std::string request);

    std::list<std::string> trackedMsgIds;
    Poco::Mutex mutexTrackedMsgIds;
    mutable Poco::Mutex mutexCustomActions;
    mutable Poco::Mutex mutexHttpServer;
    mutable Poco::Mutex mutexCallback;

    virtual void handleAction_WS_ACTION_PROBE(DPWS11Message * dpws11Msg);
    virtual void handleAction_WS_ACTION_RESOLVE(DPWS11Message * dpws11Msg);
    void handleAction_WS_ACTION_GET_METADATA_REQUEST(DPWS11Message * dpws11Msg);
    void handleAction_WS_ACTION_SUBSCRIBE(DPWS11Message * dpws11Msg);
    void handleAction_WS_ACTION_RENEW(DPWS11Message * dpws11Msg);
    void handleAction_WS_ACTION_UNSUBSCRIBE(DPWS11Message * dpws11Msg);
    void handleAction_WS_ACTION_GET(DPWS11Message * dpws11Msg);
    void handleAction_invoke(std::shared_ptr<DPWS11Message>, int index);
	void handleAction_HTTP_GET_FILE(DPWS11Message * dpws11Msg, const std::string & path);
    void handleAction_HTTP_GET_WSDL(DPWS11Message * dpws11Msg, const std::string & path);

protected:
    std::vector<std::shared_ptr<AbstractBinding>> bindings;
};

} /* namespace DPWS */
} /* namespace Comm */
} /* namespace OSCLib */
#endif /* DPWSCOMMUNICATIONMANAGER_H_ */
