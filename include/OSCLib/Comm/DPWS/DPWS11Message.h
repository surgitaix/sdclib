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
 *  @file DPWS11Message.h
 *  @project OSCLib
 *  @date 24.08.2011
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 */


#ifndef DPWSMESSAGE_H_
#define DPWSMESSAGE_H_

#include "DPWS11MessageXMLParser.h"
#include "OSCLib/Comm/Message.h"
#include "OSCLib/Data/Parameter.h"
#include "OSCLib/Dev/DeviceCharacteristics.h"
#include "OSCLib/Dev/EndpointReference.h"

#include <string>
#include <vector>
#include <memory>

namespace OSCLib {

namespace Dev {
	class Device;
	class EndpointReference;
	class Entity;
	class Service;
}

namespace Data {
	class Operation;
	class Subscription;
}
namespace Comm {
	class Binding;
    class AbstractBinding;

namespace Soap {
	class XMLEntity;
	class SoapEnvelope;
	class SoapBody;
}

namespace DPWS {

class DPWS11Message: public OSCLib::Comm::Message {
public:
	DPWS11Message();
	virtual ~DPWS11Message();

	void addReplyTo(const std::string & replyTo);

	void initMessage(const std::string & shortName = "");
	void createHelloMessage(const Dev::Device & device);
	void createByeMessage(const Dev::Device & device);
	void createGetMessage(const Dev::Device & device);
	void createGetMetadataMessage(const Dev::Device & device, unsigned int serviceIndex);
	void createGetResponse(const Dev::Device & device, int wsdlIndex = -1);
	void createGetMetadataResponse(const Dev::Device & device, int wsdlIndex = -1);
	void createProbeMessage(const Dev::Device & device, const std::string & xaddr = "");
	void createResolveMessage(const Dev::Device & device);
	void createMatchResponse(const Dev::Device & device, bool probe = false);
	void createInvokeMessage(const Dev::Device & device, unsigned int serviceIndex, const std::string & action, Data::Parameters& inputParams);
	bool createInvokeResponse(const Dev::Device & device, unsigned int serviceIndex);
	void createEventMessage(const Data::Subscription & subscription, const Data::Parameters & params, const std::string & eventName, const Data::QName & portType);
    void createStreamMessage(const Data::Parameters & params, const std::string from, const std::string mcastTo, const Dev::Device & device);
	void createSubscribeMessage(const std::string & action, long duration, const Dev::Device & localDevice, unsigned int localIndex, const Dev::Device & remoteDevice, unsigned int remoteIndex);
	void createSubscribeResponse(const Dev::Device & device, unsigned int serviceIndex);
	void createRenewMessage(const Dev::Service & localSinkService, const Dev::Service & remoteSourceService, long duration);
	void createRenewResponse(const Dev::Device & device, unsigned int serviceIndex);
	void createUnsubscribeMessage(const Dev::Service & localSinkService, const Dev::Service & remoteSourceService);
	void createUnsubscribeResponse(const Dev::Device & device, unsigned int serviceIndex);

    void createStaticWSDL(const std::string & wsdl);
	void createWSDL(const Dev::Service & service, std::string targetNamespace);

	bool parseXML(const std::string & str, const Util::StringVector & customActions);

    const std::string & getIncomingAction() const;
    void setIncomingAction(const std::string & incAction);

    const std::string & getIncomingTo() const;
    void setIncomingTo(const std::string & incTo);

    const std::string & getIncomingRelatesTo() const;
    void setIncomingRelatesTo(const std::string & incRelatesTo);

    const std::string & getIncomingReplyToAddr() const;
    void setIncomingReplyToAddr(const std::string & incReplyToAddr);

    const std::string & getIncomingId() const;
    void setIncomingId(const std::string & incId);

    const Dev::EndpointReference & getIncomingDeviceEPRAddress() const;
    void setIncomingDeviceEPRAddress(const Dev::EndpointReference & incDeviceEPRAddress);

    const Dev::EndpointReference & getIncomingSubManEPRAddress() const;
    void setIncomingSubManEPRAddress(const Dev::EndpointReference & incSubManEPRAddress);

    const std::string & getIncomingScopes() const;
    void setIncomingScopes(const std::string & incScopes);

    const std::vector<std::string> & getIncomingWSDLLocations();
    void addIncomingWSDLLocation(const std::string & incWSDLLocations);

    const Data::QVector & getIncomingTypes() const;
    void setIncomingTypes(const Data::QVector & types);

    int getIncomingMetadataVersion() const;
    void setIncomingMetadataVersion(int incMetadataVersion);

    OSCLib::Dev::DeviceCharacteristics & getIncomingDeviceCharacteristics();

    const std::string & getIncomingXAddrs() const;
    void setIncomingXAddrs(const std::string & incXAddrs);

    std::shared_ptr<Data::Subscription> getIncomingSubscription() const;
    void setIncomingSubscription(std::shared_ptr<Data::Subscription> incSubscription);

    const std::string & getIncomingRenewExpires() const;
    void setIncomingRenewExpires(const std::string & incRenewExpires);
    bool getIncomingRenewResponseSucceeded() const;
    void setIncomingRenewResponseSucceeded(bool incRenewResponseSucceeded);

    const std::string & getIncomingEventSourceIdent() const;
    void setIncomingEventSourceIdent(const std::string & incRenewIdent);

    std::string getShortName() const;
    void setShortName(const std::string & shortName);

    void copyRaw(const Message & msg);
    bool configureUnicast(std::shared_ptr<Comm::Binding> destination = nullptr);
    bool configureMulticast();

	std::string getHttpRequestType() const;
	void setHttpRequestType(std::string httpRequestType);

	std::string getHttpUrl() const;
	void setHttpUrl(std::string httpUrl);

	DPWS11MessageXMLParser & getMessageParser();

	const std::vector<std::shared_ptr<Dev::Service>>& getHostedServices();
	void addHostedService(std::shared_ptr<Dev::Service> service);

	Data::Parameters parameters;
    std::string bodyRawContent;

	static void generateRawBuffer(DPWS11Message & msg);

    bool isSkipGenerateRawBuffer() const;
    void setSkipGenerateRawBuffer(bool skipGenerateRawBuffer);

    const std::string getId() const;
    void setId(const std::string & newId);

private:

    bool isRequest() const;
    void setRequest(bool request);

	std::string httpUrl;
	std::string httpRequestType;
	std::string incId;
	std::string incTo;
	std::string incRelatesTo;
	std::string incReplyToAddr;
	std::string incAction;
	Dev::EndpointReference incDeviceEPRAddress;
	Dev::EndpointReference incSubManEPRAddress;
	std::string incScopes;
	std::string incXAddrs;
    bool incRenewResponseSucceeded;
	std::vector<std::string> incWSDLLocations;
	int incMetadataVersion;
	Dev::DeviceCharacteristics incDeviceCharacteristics;
	Data::QVector incTypes;
	std::vector<std::shared_ptr<Dev::Service>> hostedServices;
	std::shared_ptr<Data::Subscription> incSubscription;
	std::string incEventSourceIdentifier;
	std::string incRenewExpires;
	std::string shortName;
	DPWS11MessageXMLParser xmlparser;

    bool skipGenerateRawBuffer;
    bool request;

    std::shared_ptr<Soap::SoapEnvelope> envelope;
    std::shared_ptr<Soap::XMLEntity> rawXML;
    std::string id;

    std::string getMsgXml(int flags = 0);

    // we need the cdmDoc and cdmBuf variables as members of DPWS11Message, because
    // rapidxmls internal memory management only produces shallow copies of documents
    bool attachCDMStringToSoapBody(const std::string & xmlStr, Soap::SoapBody * b);
    rapidxml::xml_document<> cdmDoc;
    Poco::Buffer<char> cdmBuf;
    std::shared_ptr<Soap::SoapEnvelope> getEnvelope();
    bool isSoap();
};

} /* namespace DPWS */
} /* namespace Comm */
} /* namespace OSCLib */
#endif /* DPWSMESSAGE_H_ */
