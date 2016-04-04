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
 *  @file DPWS11Constants.h
 *  @project OSCLib
 *  @date 05.07.2011
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 */

#ifndef DPWSCONSTANTS_H_
#define DPWSCONSTANTS_H_

#include <string>

namespace OSCLib {
namespace Comm {
namespace DPWS {

const std::string DPWS11("DPWS_11");
const std::string MDPWS("MDPWS");

const int APP_MAX_DELAY(500);  // milliseconds [WS-discovery]
const int MATCH_TIMEOUT(10);  // seconds [WS-discovery]
const int DP_MAX_TIMEOUT(5);  // seconds for discovery proxy timeout [WS-discovery]
const int MAX_ENVELOPE_SIZE(32767);  // octets
const int MAX_UDP_ENVELOPE_SIZE(4096); // octets
const int MAX_FIELD_SIZE(256); // unicode characters
const int MAX_URI_SIZE(2048); // octets
const int MULTICAST_UDP_REPEAT(1); // [SOAP-over-UDP]
const int UDP_MAX_DELAY(250); // milliseconds [SOAP-over-UDP]
const int UDP_MIN_DELAY(50);  // milliseconds [SOAP-over-UDP]
const int UDP_UPPER_DELAY(450);  //milliseconds [SOAP-over-UDP]
const int UDP_ENVELOPE_SIZE(4096);
const int UDP_UNICAST_UDP_REPEAT(1);
const int UDP_UNICAST_MIN_DELAY(50);
const int UDP_UNICAST_MAX_DELAY(250);
const int UDP_UNICAST_UPPER_DELAY(500);
const int UPD_MULTICAST_DISCOVERY_PORT(3702);
const int UDP_MULTICAST_UDP_REPEAT(2);
const int UDP_MULTICAST_MIN_DELAY(50);
const int UDP_MULTICAST_MAX_DELAY(250);
const int UDP_MULTICAST_UPPER_DELAY(500);
const std::string UDP_MULTICAST_IP_V4("239.255.255.250");
const std::string UDP_MULTICAST_IP_V6("FF02::C");

const std::string WS_NS_DPWS("http://docs.oasis-open.org/ws-dd/ns/dpws/2009/01");
const std::string WS_NS_SOAP_ENVELOPE("http://www.w3.org/2003/05/soap-envelope");
const std::string WS_NS_WSDL_SOAP("http://schemas.xmlsoap.org/wsdl/");
const std::string WS_NS_WSDL_W3_SOAP("http://www.w3.org/ns/wsdl/soap");
const std::string WS_NS_WSDL_W3_SOAP_HTTP("http://www.w3.org/2003/05/soap/bindings/HTTP/");
const std::string WS_NS_WSDL_SOAP12_SCHEMA("http://schemas.xmlsoap.org/wsdl/soap12/");
const std::string WS_NS_WSDL_XML_SCHEMA("http://www.w3.org/2001/XMLSchema");
const std::string WS_NS_WSDL_XML_SCHEMA_INSTANCE("http://www.w3.org/2001/XMLSchema-instance");
const std::string WS_NS_WSDL_SOAP_HTTP("http://schemas.xmlsoap.org/soap/http");
const std::string WS_NS_ADDRESSING("http://www.w3.org/2005/08/addressing");
const std::string WS_NS_ADDRESSING_METADATA("http://www.w3.org/2007/05/addressing/metadata");
const std::string WS_NS_METADATA_EXCHANGE("http://schemas.xmlsoap.org/ws/2004/09/mex");
const std::string WS_NS_DISCOVERY("http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01");
const std::string WS_NS_EVENTING("http://schemas.xmlsoap.org/ws/2004/08/eventing");

const std::string WS_ADDRESSING_ANONYMOUS("http://www.w3.org/2005/08/addressing/anonymous");

const std::string WS_ACTION("http://docs.oasis-open.org/ws-dd/ns/dpws/2009/01/Action");
const std::string WS_ACTION_HELLO("http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01/Hello");
const std::string WS_ACTION_BYE("http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01/Bye");
const std::string WS_ACTION_GET("http://schemas.xmlsoap.org/ws/2004/09/transfer/Get");
const std::string WS_ACTION_GET_RESPONSE("http://schemas.xmlsoap.org/ws/2004/09/transfer/GetResponse");
const std::string WS_ACTION_GET_METADATA_REQUEST("http://schemas.xmlsoap.org/ws/2004/09/mex/GetMetadata/Request");
const std::string WS_ACTION_GET_METADATA_RESPONSE("http://schemas.xmlsoap.org/ws/2004/09/mex/GetMetadata/Response");

const std::string WS_ACTION_RESOLVE("http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01/Resolve");
const std::string WS_ACTION_RESOLVE_MATCHES("http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01/ResolveMatches");
const std::string WS_ACTION_PROBE("http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01/Probe");
const std::string WS_ACTION_PROBE_MATCHES("http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01/ProbeMatches");

const std::string WS_ACTION_SUBSCRIBE("http://schemas.xmlsoap.org/ws/2004/08/eventing/Subscribe");
const std::string WS_ACTION_SUBSCRIBE_RESPONSE("http://schemas.xmlsoap.org/ws/2004/08/eventing/SubscribeResponse");
const std::string WS_ACTION_RENEW("http://schemas.xmlsoap.org/ws/2004/08/eventing/Renew");
const std::string WS_ACTION_RENEW_RESPONSE("http://schemas.xmlsoap.org/ws/2004/08/eventing/RenewResponse");
const std::string WS_ACTION_UNSUBSCRIBE("http://schemas.xmlsoap.org/ws/2004/08/eventing/Unsubscribe");
const std::string WS_ACTION_UNSUBSCRIBE_RESPONSE("http://schemas.xmlsoap.org/ws/2004/08/eventing/UnsubscribeResponse");

const std::string WS_DISCOVERY_URN("urn:docs-oasis-open-org:ws-dd:ns:discovery:2009:01");

const std::string WS_MEX_DIALECT_MODEL("http://docs.oasis-open.org/ws-dd/ns/dpws/2009/01/ThisModel");
const std::string WS_MEX_DIALECT_DEVICE("http://docs.oasis-open.org/ws-dd/ns/dpws/2009/01/ThisDevice");
const std::string WS_MEX_DIALECT_WSDL("http://schemas.xmlsoap.org/wsdl/");
const std::string WS_MEX_DIALECT_REL("http://docs.oasis-open.org/ws-dd/ns/dpws/2009/01/Relationship");
const std::string WS_MEX_REL_HOST("http://docs.oasis-open.org/ws-dd/ns/dpws/2009/01/host");

const std::string WS_EVENTING_PUSH("http://schemas.xmlsoap.org/ws/2004/08/eventing/DeliveryModes/Push");

}
}
}

#endif /* DPWSCONSTANTS_H_ */
