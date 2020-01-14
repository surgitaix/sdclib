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
 *  @file SDCConstants.h
 *  @project SDCLib
 *  @date 26.09.2019
 *  @author besting, baumeister
 *  @copyright (c) SurgiTAIX AG
 */

#ifndef OSELIB_SDC_SDCCONSTANTS_H_
#define OSELIB_SDC_SDCCONSTANTS_H_

#include <string>

namespace OSELib {
namespace SDC {

const std::string NS_ADDRESSING("http://www.w3.org/2005/08/addressing");
const std::string NS_EVENTING("http://schemas.xmlsoap.org/ws/2004/08/eventing");
const std::string NS_DOMAIN_MODEL("http://standards.ieee.org/downloads/11073/11073-10207-2017/participant");
const std::string NS_MESSAGE_MODEL("http://standards.ieee.org/downloads/11073/11073-10207-2017/message");
const std::string NS_SERVICE_DESCRIPTION("http://standards.ieee.org/downloads/11073/11073-20701-2018");
const std::string NS_WSDL("http://schemas.xmlsoap.org/wsdl/");
//const std::string NS_WSDL_TARGET_NAMESPACE("http://standards.ieee.org/downloads/11073/11073-10207-2017/message");
const std::string NS_WSDL_TARGET_NAMESPACE("http://standards.ieee.org/downloads/11073/11073-20701-2018");
const std::string NS_WSDL_SOAP_BINDING("http://schemas.xmlsoap.org/wsdl/soap/");
const std::string NS_XML_SCHEMA("http://www.w3.org/2001/XMLSchema");
const std::string NS_MDPWS("http://standards.ieee.org/downloads/11073/11073-20702-2016");
const std::string WS_MEX_ORNET_NS_STREAM("http://standardized.namespace.org/ws-streaming");
const std::string MDPWS_STREAM_TYPE("WaveformStream");
const std::string WS_POLICY("http://www.w3.org/ns/ws-policy");
const std::string NS_DPWS("http://docs.oasis-open.org/ws-dd/ns/dpws/2009/01");

const std::string MDPWS_MCAST_ADDR("soap.udp://239.239.239.235");
const int MDPWS_MCAST_PORT(5555);

const std::string WS_MEX_ORNET_STREAM_IDENTIFIER(NS_SERVICE_DESCRIPTION + "/WaveformService"); // FIXME: Rename constant(?)
const std::string WS_MEX_ORNET_STREAM_TYPE("http://docs.oasis-open.org/ws-dd/soapoverudp/1.1/os/wsdd-soapoverudp-1.1-spec-os.html"); // FIXME: Rename constant(?)
const std::string WS_MEX_DIALECT_STREAM("http://standards.ieee.org/downloads/11073/11073-20702-2016");




// UUID related - from IEEE 11073 - 20701 - Annex A
const std::string UUID_SDC_PREFIX("urn:uuid:");
const std::string UUID_SDC_BASE_NAMESPACE("72772F61-0266-49F9-9552-393C1857B269");



// ANNEX B

// B.1 Get Service
const std::string QNAME_GETSERVICE("GetService");
const std::string QNAME_GETSERVICE_PORTTYPE(QNAME_GETSERVICE);

const std::string GET_MDIB("GetMdib");
const std::string OP_GET_MDIB_REQUEST(GET_MDIB);
const std::string ACT_GET_MDIB_REQUEST(NS_SERVICE_DESCRIPTION + "/" + QNAME_GETSERVICE_PORTTYPE + "/" + OP_GET_MDIB_REQUEST);
const std::string OP_GET_MDIB_RESPONSE(GET_MDIB + "Response");
const std::string ACT_GET_MDIB_RESPONSE(NS_SERVICE_DESCRIPTION + "/" + QNAME_GETSERVICE_PORTTYPE + "/" + OP_GET_MDIB_RESPONSE);
const std::string GET_MDDESCRIPTION("GetMdDescription");
const std::string OP_GET_MDDESCRIPTION_REQUEST(GET_MDDESCRIPTION);
const std::string ACT_GET_MDDESCRIPTION_REQUEST(NS_SERVICE_DESCRIPTION + "/" + QNAME_GETSERVICE_PORTTYPE + "/" + OP_GET_MDDESCRIPTION_REQUEST);
const std::string OP_GET_MDDESCRIPTION_RESPONSE(GET_MDDESCRIPTION + "Response");
const std::string ACT_GET_MDDESCRIPTION_RESPONSE(NS_SERVICE_DESCRIPTION + "/" + QNAME_GETSERVICE_PORTTYPE + "/" + OP_GET_MDDESCRIPTION_RESPONSE);
const std::string GET_MDSTATE("GetMdState");
const std::string OP_GET_MDSTATE_REQUEST(GET_MDSTATE);
const std::string ACT_GET_MDSTATE_REQUEST(NS_SERVICE_DESCRIPTION + "/" + QNAME_GETSERVICE_PORTTYPE + "/" + OP_GET_MDSTATE_REQUEST);
const std::string OP_GET_MDSTATE_RESPONSE(GET_MDSTATE + "Response");
const std::string ACT_GET_MDSTATE_RESPONSE(NS_SERVICE_DESCRIPTION + "/" + QNAME_GETSERVICE_PORTTYPE + "/" + OP_GET_MDSTATE_RESPONSE);

// B.2 Set Service
const std::string QNAME_SETSERVICE("SetService");
const std::string QNAME_SETSERVICE_PORTTYPE(QNAME_SETSERVICE);

const std::string SET_VALUE("SetValue");
const std::string OP_SET_VALUE_REQUEST(SET_VALUE);
const std::string ACT_SET_VALUE_REQUEST(NS_SERVICE_DESCRIPTION + "/" + QNAME_SETSERVICE_PORTTYPE + "/" + OP_SET_VALUE_REQUEST);
const std::string OP_SET_VALUE_RESPONSE(SET_VALUE + "Response");
const std::string ACT_SET_VALUE_RESPONSE(NS_SERVICE_DESCRIPTION + "/" + QNAME_SETSERVICE_PORTTYPE + "/" + OP_SET_VALUE_RESPONSE);
const std::string SET_STRING("SetString");
const std::string OP_SET_STRING_REQUEST(SET_STRING);
const std::string ACT_SET_STRING_REQUEST(NS_SERVICE_DESCRIPTION + "/" + QNAME_SETSERVICE_PORTTYPE + "/" + OP_SET_STRING_REQUEST);
const std::string OP_SET_STRING_RESPONSE(SET_STRING + "Response");
const std::string ACT_SET_STRING_RESPONSE(NS_SERVICE_DESCRIPTION + "/" + QNAME_SETSERVICE_PORTTYPE + "/" + OP_SET_STRING_RESPONSE);
const std::string ACTIVATE("Activate");
const std::string OP_ACTIVATE_REQUEST(ACTIVATE);
const std::string ACT_ACTIVATE_REQUEST(NS_SERVICE_DESCRIPTION + "/" + QNAME_SETSERVICE_PORTTYPE + "/" + OP_ACTIVATE_REQUEST);
const std::string OP_ACTIVATE_RESPONSE(ACTIVATE + "Response");
const std::string ACT_ACTIVATE_RESPONSE(NS_SERVICE_DESCRIPTION + "/" + QNAME_SETSERVICE_PORTTYPE + "/" + OP_ACTIVATE_RESPONSE);
const std::string SET_ALERT_STATE("SetAlertState");
const std::string OP_SET_ALERT_STATE_REQUEST(SET_ALERT_STATE);
const std::string ACT_SET_ALERT_STATE_REQUEST(NS_SERVICE_DESCRIPTION + "/" + QNAME_SETSERVICE_PORTTYPE + "/" + OP_SET_ALERT_STATE_REQUEST);
const std::string OP_SET_ALERT_STATE_RESPONSE(SET_ALERT_STATE + "Response");
const std::string ACT_SET_ALERT_STATE_RESPONSE(NS_SERVICE_DESCRIPTION + "/" + QNAME_SETSERVICE_PORTTYPE + "/" + OP_SET_ALERT_STATE_RESPONSE);
const std::string SET_COMPONENT_STATE("SetComponentState");
const std::string OP_SET_COMPONENT_STATE_REQUEST(SET_COMPONENT_STATE);
const std::string ACT_SET_COMPONENT_STATE_REQUEST(NS_SERVICE_DESCRIPTION + "/" + QNAME_SETSERVICE_PORTTYPE + "/" + OP_SET_COMPONENT_STATE_REQUEST);
const std::string OP_SET_COMPONENT_STATE_RESPONSE(SET_COMPONENT_STATE + "Response");
const std::string ACT_SET_COMPONENT_STATE_RESPONSE(NS_SERVICE_DESCRIPTION + "/" + QNAME_SETSERVICE_PORTTYPE + "/" + OP_SET_COMPONENT_STATE_RESPONSE);
const std::string SET_METRIC_STATE("SetMetricState");
const std::string OP_SET_METRIC_STATE_REQUEST(SET_METRIC_STATE);
const std::string ACT_SET_METRIC_STATE_REQUEST(NS_SERVICE_DESCRIPTION + "/" + QNAME_SETSERVICE_PORTTYPE + "/" + OP_SET_METRIC_STATE_REQUEST);
const std::string OP_SET_METRIC_STATE_RESPONSE(SET_METRIC_STATE + "Response");
const std::string ACT_SET_METRIC_STATE_RESPONSE(NS_SERVICE_DESCRIPTION + "/" + QNAME_SETSERVICE_PORTTYPE + "/" + OP_SET_METRIC_STATE_RESPONSE);
const std::string OPERATION_INVOKED_REPORT("OperationInvokedReport");
const std::string OP_OPERATION_INVOKED_REPORT(OPERATION_INVOKED_REPORT);
const std::string ACT_OPERATION_INVOKED_REPORT(NS_SERVICE_DESCRIPTION + "/" + QNAME_SETSERVICE_PORTTYPE + "/" + OP_OPERATION_INVOKED_REPORT);


// NOTE: Create a BICEPS Service to group B.3 - 6 according to R0034 under one hosted service

const std::string QNAME_BICEPSSERVICE("BICEPSService");
const std::string QNAME_BICEPSSERVICE_PORTTYPE(QNAME_BICEPSSERVICE);

const std::string QNAME_DESCRIPTIONEVENTSERVICE("DescriptionEventService");
const std::string QNAME_STATEEVENTSERVICE("StateEventService");
const std::string QNAME_CONTEXTSERVICE("ContextService");
const std::string QNAME_WAVEFORMSERVICE("WaveformService");

// Create PortTypes
const std::string QNAME_DESCRIPTIONEVENTSERVICE_PORTTYPE(QNAME_DESCRIPTIONEVENTSERVICE);
const std::string QNAME_STATEEVENTSERVICE_PORTTYPE(QNAME_STATEEVENTSERVICE);
const std::string QNAME_CONTEXTSERVICE_PORTTYPE(QNAME_CONTEXTSERVICE);
const std::string QNAME_WAVEFORMSERVICE_PORTTYPE(QNAME_WAVEFORMSERVICE);


// B.3 Description Event Service
const std::string DESCRIPTION_MODIFICATION_REPORT("DescriptionModificationReport");
const std::string OP_DESCRIPTION_MODIFICATION_REPORT(DESCRIPTION_MODIFICATION_REPORT);
const std::string ACT_DESCRIPTION_MODIFICATION_REPORT(NS_SERVICE_DESCRIPTION + "/" + QNAME_DESCRIPTIONEVENTSERVICE_PORTTYPE + "/" + OP_DESCRIPTION_MODIFICATION_REPORT);

// B.4 State Event Service
const std::string EPISODIC_ALERT_REPORT("EpisodicAlertReport");
const std::string OP_EPISODIC_ALERT_REPORT(EPISODIC_ALERT_REPORT);
const std::string ACT_EPISODIC_ALERT_REPORT(NS_SERVICE_DESCRIPTION + "/" + QNAME_STATEEVENTSERVICE_PORTTYPE + "/" + OP_EPISODIC_ALERT_REPORT);
const std::string PERIODIC_ALERT_REPORT("PeriodicAlertReport");
const std::string OP_PERIODIC_ALERT_REPORT(PERIODIC_ALERT_REPORT);
const std::string ACT_PERIODIC_ALERT_REPORT(NS_SERVICE_DESCRIPTION + "/" + QNAME_STATEEVENTSERVICE_PORTTYPE + "/" + OP_PERIODIC_ALERT_REPORT);
const std::string EPISODIC_COMPONENT_REPORT("EpisodicComponentReport");
const std::string OP_EPISODIC_COMPONENT_REPORT(EPISODIC_COMPONENT_REPORT);
const std::string ACT_EPISODIC_COMPONENT_REPORT(NS_SERVICE_DESCRIPTION + "/" + QNAME_STATEEVENTSERVICE_PORTTYPE + "/" + OP_EPISODIC_COMPONENT_REPORT);
const std::string PERIODIC_COMPONENT_REPORT("PeriodicComponentReport");
const std::string OP_PERIODIC_COMPONENT_REPORT(PERIODIC_COMPONENT_REPORT);
const std::string ACT_PERIODIC_COMPONENT_REPORT(NS_SERVICE_DESCRIPTION + "/" + QNAME_STATEEVENTSERVICE_PORTTYPE + "/" + OP_PERIODIC_COMPONENT_REPORT);
const std::string EPISODIC_METRIC_REPORT("EpisodicMetricReport");
const std::string OP_EPISODIC_METRIC_REPORT(EPISODIC_METRIC_REPORT);
const std::string ACT_EPISODIC_METRIC_REPORT(NS_SERVICE_DESCRIPTION + "/" + QNAME_STATEEVENTSERVICE_PORTTYPE + "/" + OP_EPISODIC_METRIC_REPORT);
const std::string PERIODIC_METRIC_REPORT("PeriodicMetricReport");
const std::string OP_PERIODIC_METRIC_REPORT(PERIODIC_METRIC_REPORT);
const std::string ACT_PERIODIC_METRIC_REPORT(NS_SERVICE_DESCRIPTION + "/" + QNAME_STATEEVENTSERVICE_PORTTYPE + "/" + OP_PERIODIC_METRIC_REPORT);
const std::string EPISODIC_OPERATIONALSTATE_REPORT("EpisodicOperationalStateReport");
const std::string OP_EPISODIC_OPERATIONALSTATE_REPORT(EPISODIC_OPERATIONALSTATE_REPORT);
const std::string ACT_EPISODIC_OPERATIONALSTATE_REPORT(NS_SERVICE_DESCRIPTION + "/" + QNAME_STATEEVENTSERVICE_PORTTYPE + "/" + OP_EPISODIC_OPERATIONALSTATE_REPORT);
const std::string PERIODIC_OPERATIONALSTATE_REPORT("PeriodicOperationalStateReport");
const std::string OP_PERIODIC_OPERATIONALSTATE_REPORT(PERIODIC_OPERATIONALSTATE_REPORT);
const std::string ACT_PERIODIC_OPERATIONALSTATE_REPORT(NS_SERVICE_DESCRIPTION + "/" + QNAME_STATEEVENTSERVICE_PORTTYPE + "/" + OP_PERIODIC_OPERATIONALSTATE_REPORT);
const std::string SYSTEMERROR_REPORT("SystemErrorReport");
const std::string OP_SYSTEMERROR_REPORT(SYSTEMERROR_REPORT);
const std::string ACT_SYSTEMERROR_REPORT(NS_SERVICE_DESCRIPTION + "/" + QNAME_STATEEVENTSERVICE_PORTTYPE + "/" + OP_SYSTEMERROR_REPORT);

// B.5 Context Service
const std::string GET_CONTEXTSTATES("GetContextStates");
const std::string OP_GET_CONTEXTSTATES_REQUEST(GET_CONTEXTSTATES);
const std::string ACT_GET_CONTEXTSTATES_REQUEST(NS_SERVICE_DESCRIPTION + "/" + QNAME_CONTEXTSERVICE_PORTTYPE + "/" + OP_GET_CONTEXTSTATES_REQUEST);
const std::string OP_GET_CONTEXTSTATES_RESPONSE(GET_CONTEXTSTATES + "Response");
const std::string ACT_GET_CONTEXTSTATES_RESPONSE(NS_SERVICE_DESCRIPTION + "/" + QNAME_CONTEXTSERVICE_PORTTYPE + "/" + OP_GET_CONTEXTSTATES_RESPONSE);
const std::string SET_CONTEXTSTATE("SetContextState");
const std::string OP_SET_CONTEXTSTATE_REQUEST(SET_CONTEXTSTATE);
const std::string ACT_SET_CONTEXTSTATE_REQUEST(NS_SERVICE_DESCRIPTION + "/" + QNAME_CONTEXTSERVICE_PORTTYPE + "/" + OP_SET_CONTEXTSTATE_REQUEST);
const std::string OP_SET_CONTEXTSTATE_RESPONSE(SET_CONTEXTSTATE + "Response");
const std::string ACT_SET_CONTEXTSTATE_RESPONSE(NS_SERVICE_DESCRIPTION + "/" + QNAME_CONTEXTSERVICE_PORTTYPE + "/" + OP_SET_CONTEXTSTATE_RESPONSE);
const std::string EPISODIC_CONTEXT_REPORT("EpisodicContextReport");
const std::string OP_EPISODIC_CONTEXT_REPORT(EPISODIC_CONTEXT_REPORT);
const std::string ACT_EPISODIC_CONTEXT_REPORT(NS_SERVICE_DESCRIPTION + "/" + QNAME_CONTEXTSERVICE_PORTTYPE + "/" + OP_EPISODIC_CONTEXT_REPORT);
const std::string PERIODIC_CONTEXT_REPORT("PeriodicContextReport");
const std::string OP_PERIODIC_CONTEXT_REPORT(PERIODIC_CONTEXT_REPORT);
const std::string ACT_PERIODIC_CONTEXT_REPORT(NS_SERVICE_DESCRIPTION + "/" + QNAME_CONTEXTSERVICE_PORTTYPE + "/" + OP_PERIODIC_CONTEXT_REPORT);

// B.6 Waveform Service
const std::string NOTIFICATION("Notification");
const std::string WAVEFORM_STREAM("WaveformStream");
const std::string OP_WAVEFORM_STREAM_REPORT(WAVEFORM_STREAM);
const std::string ACT_WAVEFORM_STREAM_REPORT(NS_SERVICE_DESCRIPTION + "/" + QNAME_WAVEFORMSERVICE_PORTTYPE + "/" + OP_WAVEFORM_STREAM_REPORT);
const std::string OP_OBSERVED_VALUESTREAM_REPORT("ObservedValueStream");
const std::string ACT_OBSERVED_VALUESTREAM_REPORT(NS_SERVICE_DESCRIPTION + "/" + QNAME_WAVEFORMSERVICE_PORTTYPE + "/" + OP_OBSERVED_VALUESTREAM_REPORT);


}
}

#endif
