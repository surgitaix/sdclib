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
 * @file DPWS11Client.h
 * @project OSCLib
 * @date 27.02.2012
 * @author Besting
 * @copyright (c) SurgiTAIX AG
 *
 */

#ifndef DPWS11CLIENT_H_
#define DPWS11CLIENT_H_

#include "OSCLib/Comm/DPWS/DPWS11CommunicationManager.h"
#include "OSCLib/Data/Parameter.h"

#include <atomic>
#include <string>

#include "Poco/Mutex.h"
#include "Poco/Event.h"
#include "Poco/ScopedLock.h"
#include "Poco/NotificationQueue.h"

namespace OSCLib {
namespace Comm {
	class Message;
	class Binding;
	class HTTPClientExchanger;
namespace DPWS {
	class DPWS11Message;
}
}

namespace Data {
	class EventSink;
	class Parameter;
	class QName;
}

namespace Dev {
	class Device;
	class Service;
}

namespace Cli {

enum class SearchMode {
    NONE,
    PROBE,
    RESOLVE
};
class HTTPRequester;
class HelloReceivedHandler;

/**
 * @brief An instance of this class represents a DPWS 1.1 compatible client.
 */
class Client : public OSCLib::Comm::DPWS::DPWS11CommunicationManager

{
friend class HTTPRequester;
public:

	static const int DEFAULT_TIMEOUT;

    Client();
private:
    Client(const Client & client);
	Client(std::shared_ptr<Dev::Device> dev);
    void addRemoteDeviceActions(std::shared_ptr<Dev::Device> remote);
public:
	virtual ~Client();

	/**
	 * @brief Add device type search parameter.
	 *
	 * @param type The device type to search for
	 */
    void addDeviceTypeSearchParam(const Data::QName & type);

    Data::QVector getDeviceTypeSearchParams() const;

	/**
	 * @brief Add service scope search parameter.
	 *
	 * @param scope The service scope to search for
	 */
    void addDeviceScopeSearchParam(const std::string & scope);

    Util::StringVector getDeviceScopeSearchParams() const;

	/**
	 * @brief Add device endpoint reference address search parameter.
	 *
	 * @param eprAdr The device's EPR address to search for
	 */
    void setDeviceEPRAdrSearchParam(const std::string & eprAdr);

    /**
    * @brief Get endpoint reference address search parameter.
    *
    * @return id The device's EPR address to search for
    */
    std::string getDeviceEPRAdrSearchParam();

    /**
    * @brief Set device xAddr search parameter.
    *
    * @param xaddr The device's EPR address to search for
    */
    void setDeviceXAddrSearchParam(const std::string & xaddr);

	/**
	 * @brief Add service type search parameter.
	 *
	 * @param type The service type to search for
	 */
    void addServiceTypeSearchParam(const Data::QName & type);

    Data::QVector getServiceTypeSearchParams() const;

	/**
	 * @brief Add service ID search parameter.
	 *
	 * @param id The service ID to search for
	 */
    void setServiceIDSearchParam(const std::string & id);

    std::string getServiceIDSearchParam() const;

	/**
	 * @brief Clear all search parameters.
	 */
    void clearSearchParams();

	/**
	 * @brief Clear the complete client configuration.
	 *
	 * @param b Binding to receive messages (optional)
	 */
    void reset();

	/**
	 * @brief Search for devices and hosted services that match the search parameters (if defined).
	 *
	 * Note: this method does not block.
	 */
    void search();

    /**
    * @brief Returns true in case a client exists that performed a successful search.
    *
    * @return True, if the search has yielded any positive results.
    */
    bool foundAny();

	/**
	 * @brief Check if remote device is still reachable.
	 *
	 * @return True, if remote device is reachable.
	 */
    bool pingSync(int timeout = DEFAULT_TIMEOUT);

    bool pingSync(int timeout, const Dev::Device & dev, const std::string & xaddr);

	/**
	 * @brief Search for devices and hosted services that match the search parameters (if defined).
	 *
	 * Note: this method blocks until the result of the request has been returned!
	 *
	 * @param timeout A timeout in milliseconds (optional)
	 *
	 * @return True, if the search has yielded any positive results.
	 */
    bool searchSync(int timeout = DEFAULT_TIMEOUT);

	/**
	 * @brief Invoke any method after a service has been found.
	 *
	 * Note: this method blocks until the result of the request has been returned!
	 *
	 * @param portType The port type
	 * @param operation The name of the operation
	 * @param input A list of input parameters
	 * @param output Pointer to a list of output parameters to return (optional)
	 * @param timeout A timeout in milliseconds (optional)
     *
	 * @return True, if the invoke request has been sent and the response have been received.
	 */
    bool invokeSync(const Data::QName & portType, const std::string & operation, Data::Parameters & input, Data::Parameters * output = nullptr, int timeout = DEFAULT_TIMEOUT);

	/**
	 * @brief Invoke any method after a service has been found.
	 *
	 * Note: this method blocks until the result of the request has been returned!
	 *
	 * @param action A custom SOAP action used for invocation
	 * @param input A list of input parameters
	 * @param output Pointer to a list of output parameters to return (optional)
	 * @param timeout A timeout in milliseconds (optional)
     *
	 * @return True, if the invoke request has been sent and the response have been received.
	 */
    bool invokeSync(const std::string & action, Data::Parameters & input, Data::Parameters * output = nullptr, int timeout = DEFAULT_TIMEOUT);

	/**
	 *  @brief Get output parameters (invoke required before).
	 *
	 * @return A list of output parameters
	 */
    Data::Parameters getInvokeResult();

	/**
	 * @brief Close client resources for connection. Must be called at the end of each session.
	 */
    void close(bool all = false);

    /**
     * @brief Can be overwritten to receive notification about response to a invoke call.
     */
    virtual void invokeResponse();

    /**
     * @brief Can be overwritten to receive notification about completion of a search operation.
     */
    virtual void searchComplete();

    /**
    * @brief Returns true in case this client performed a successful search.
    *
    * @return True, if the search has yielded any positive results.
    */
    bool isSearchComplete();


    /**
     * @brief Set a handler to receive arbitrary hello messages
     * @param handler The handler
     */
    void setHelloReceivedHandler(std::shared_ptr<HelloReceivedHandler> handler);


    /**
     * @brief Subscribe to an event source of the service found before.
	 *
	 * Note: this method blocks until the result of the request has been returned!
	 *
     * @param portType The port type of the (remote) event source
     * @param source The (remote) event source's name
     * @param duration Duration time in millis (0 if unlimited)
     * @param sink The (local) event sink that receives events
     * @param binding Binding to define a transport address for the sink
     *
     * @return True, if subscription was successful.
     */
	bool subscribeSync(Data::QName & portType, const std::string & source, long duration, std::shared_ptr<Data::EventSink> sink, std::shared_ptr<Comm::AbstractBinding> binding = nullptr, int timeout = DEFAULT_TIMEOUT);

    /**
     * @brief Subscribe to an event source of the service found before.
	 *
	 * Note: this method blocks until the result of the request has been returned!
	 *
     * @param action A custom SOAP action for event subscription
     * @param duration Duration time in millis (0 if unlimited)
     * @param sink The (local) event sink that receives events
     * @param binding Binding to define a transport address for the sink
     *
     * @return True, if subscription was successful.
     */
    bool subscribeSync(const std::string & action, long duration, std::shared_ptr<Data::EventSink> sink, std::shared_ptr<Comm::AbstractBinding> binding = nullptr, int timeout = DEFAULT_TIMEOUT);


    /**
     * @brief Renew a subscription to an event source.
	 *
	 * Note: this method blocks until the result of the request has been returned!
	 *
     * @param portType The port type of the (remote) event source
     * @param source The (remote) event source's name
     * @param duration Duration time in millis
     * @param sink The (local) event sink that receives events
     *
     * @return True, if renewal was successful.
     */
	bool renewSync(Data::QName & portType, const std::string & source, long duration, std::shared_ptr<Data::EventSink> sink, int timeout = DEFAULT_TIMEOUT);

    /**
     * @brief Renew a subscription to an event source.
	 *
	 * Note: this method blocks until the result of the request has been returned!
	 *
     * @param action A custom SOAP action for event renewal
     * @param duration Duration time in millis
     * @param sink The (local) event sink that receives events
     *
     * @return True, if renewal was successful.
     */
    bool renewSync(const std::string & action, long duration, std::shared_ptr<Data::EventSink> sink, int timeout = DEFAULT_TIMEOUT);

	/**
     * @brief Unsubscribe from an event source.
	 *
	 * Note: this method blocks until the result of the request has been returned!
	 *
     * @param portType The port type of the (remote) event source
     * @param source The (remote) event source's name
     * @param sink The (local) event sink that receives events
     *
     * @return True, if unsubscribe request was successful.
     */
	bool unsubscribeSync(Data::QName & portType, const std::string & source, std::shared_ptr<Data::EventSink> sink, int timeout = DEFAULT_TIMEOUT);

    /**
     * @brief Unsubscribe from an event source.
	 *
	 * Note: this method blocks until the result of the request has been returned!
	 *
     * @param action A custom SOAP action for event renewal
     * @param sink The (local) event sink that receives events
     *
     * @return True, if unsubscribe request was successful.
     */
    bool unsubscribeSync(const std::string & action, std::shared_ptr<Data::EventSink> sink, int timeout = DEFAULT_TIMEOUT);

    bool isActionAvailable(std::string action);

    std::string getOutputBodyRawContent();

    std::shared_ptr<OSCLib::Comm::Message> udpMulticastCallback(const Comm::Message & msg) override;

    std::shared_ptr<Comm::Message> unicastCallback(const Comm::Message & msg) override;

    void addRemoteService(std::shared_ptr<Dev::Service> service);

    std::shared_ptr<Dev::Device> getRemoteDevice();

    bool isClosed();

    bool isSearchRunning();
    
    bool isAnySearchRunning();

    void setSearchMode(SearchMode mode);

    SearchMode getSearchMode();

    void addKnownCustomAction(const std::string & action);

    void initWSDLCollector();

    std::vector<std::string> getWSDL();

    std::vector<std::shared_ptr<Client>> getClients();

    bool isInitialized();

    void enableStreaming();

private:

    bool evaluateResponseMessage(const std::shared_ptr<Comm::DPWS::DPWS11Message> dpws11Msg);
    void discoverRemoteDevice(std::shared_ptr<Dev::Device> rmDev, SearchMode sm);
    void createRemoteDevice(const std::shared_ptr<Comm::DPWS::DPWS11Message> dpws11Msg, SearchMode sm);
    std::shared_ptr<Comm::DPWS::DPWS11Message> exchangeMessage(const std::shared_ptr<Comm::DPWS::DPWS11Message> dpws11Msg, int timeout = 0);

    mutable Poco::Mutex mutex;
    mutable Poco::Mutex mutexCallback;
    std::shared_ptr<HTTPRequester> httpRequester;
    std::shared_ptr<HelloReceivedHandler> helloHandler;
    std::vector<std::shared_ptr<Client>> clients;
    std::shared_ptr<std::vector<std::string>> wsdlCollector;
    std::shared_ptr<OSCLib::Comm::HTTPClientExchanger> clHttpExchanger;
    std::vector<std::shared_ptr<Dev::Service>> sinkServices;
    std::vector<std::shared_ptr<Comm::Binding>> streamBindings;

    std::shared_ptr<Dev::Device> localDevice;
    std::shared_ptr<Dev::Device> remoteDevice;
    std::string xaddrSearchParam;
    std::string wsdl;
    std::atomic<bool> initialized;
    std::atomic<bool> searchCompleted;
    SearchMode searchMode;
    std::atomic<bool> closed;
    Poco::Event waitSearch;

    Poco::NotificationQueue httpExchangeQueue;

    void addWSDL(std::string wsdl);

    void storeBasicDiscoveryInfo(std::shared_ptr<Dev::Device> dev, const Comm::DPWS::DPWS11Message & dpws11Msg);

    void init();
    void initMembers();
    void downloadWSDLs(const Util::StringVector & wsdlAddrs);
    void cleanRemoteReferences();
    int getRemoteServiceIndex(const std::string& action, Dev::Device * & outDev);

    void handleAction_WS_ACTION_HELLO(Comm::DPWS::DPWS11Message & dpws11Msg);
    void handleAction_WS_ACTION_BYE(Comm::DPWS::DPWS11Message & dpws11Msg);
    void handleAction_WS_ACTION_PROBE_MATCHES(const std::shared_ptr<Comm::DPWS::DPWS11Message> dpws11Msg);
    void handleAction_WS_ACTION_RESOLVE_MATCHES(const std::shared_ptr<Comm::DPWS::DPWS11Message> dpws11Msg);
    void handleAction_WS_ACTION_GET_RESPONSE(const std::shared_ptr<Comm::DPWS::DPWS11Message> dpws11Msg);
    void handleAction_WS_ACTION_GET_METADATA_RESPONSE(const std::shared_ptr<Comm::DPWS::DPWS11Message> dpws11Msg);
    void handleAction_get_invoke_response_result(const std::shared_ptr<Comm::DPWS::DPWS11Message> dpws11Msg);

    virtual void handleAction_WS_ACTION_PROBE(Comm::DPWS::DPWS11Message * dpws11Msg) override;
    virtual void handleAction_WS_ACTION_RESOLVE(Comm::DPWS::DPWS11Message * dpws11Msg) override;
};

} /* namespace Cli */
} /* namespace OSCLib */
#endif /* DPWS11CLIENT_H_ */
