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
 *  @file OSCPConstants.h
 *  @project OSCLib
 *  @date 24.01.2014
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 */

#ifndef OSCP_OSCPCONSTANTS_H_
#define OSCP_OSCPCONSTANTS_H_

#include <string>

namespace OSELib {
namespace OSCP {

const std::string NS_ADDRESSING("http://www.w3.org/2005/08/addressing");
const std::string NS_EVENTING("http://schemas.xmlsoap.org/ws/2004/08/eventing");
const std::string NS_DOMAIN_MODEL("http://p11073-10207/draft8/pm/2017/08/07");
const std::string NS_MESSAGE_MODEL("http://p11073-10207/draft8/msg/2017/08/07");
const std::string NS_WSDL("http://schemas.xmlsoap.org/wsdl/");
const std::string NS_WSDL_TARGET_NAMESPACE("http://p11073-10207/draft8/msg/2017/08/07");
const std::string NS_WSDL_SOAP_BINDING("http://schemas.xmlsoap.org/wsdl/soap/");
const std::string NS_XML_SCHEMA("http://www.w3.org/2001/XMLSchema");
const std::string NS_MDPWS("http://standards.ieee.org/downloads/11073/11073-20702-201x/");
const std::string WS_MEX_ORNET_NS_STREAM("http://standardized.namespace.org/ws-streaming");
const std::string NS_ORNET_STREAM_ID(NS_MESSAGE_MODEL + "/WaveformStreamService");
const std::string WS_POLICY("http://www.w3.org/ns/ws-policy");

const std::string MDPWS_MCAST_ADDR("soap.udp://239.239.239.235");
const int MDPWS_MCAST_PORT(5555);
const std::string MDPWS_STREAMTRANSMISSIONTYPE(NS_MDPWS + "/StreamTransmissionType");

const std::string ACTION_ORNET_STREAM(NS_MESSAGE_MODEL + "/Waveform/WaveformStream");
const std::string WS_MEX_ORNET_STREAM_IDENTIFIER(NS_MESSAGE_MODEL + "/WaveformStreamService");
const std::string WS_MEX_ORNET_STREAM_TYPE("http://docs.oasis-open.org/ws-dd/soapoverudp/1.1/os/wsdd-soapoverudp-1.1-spec-os.html");

const std::string WS_MEX_ORNET_DIALECT_STREAM("http://standardized.namespace.org/ws-streaming/StreamDescriptions");

const std::string SOAP_HTTP_BINDING_URI("http://schemas.xmlsoap.org/soap/http");

// Service Qnames
const std::string QNAME_CONTEXTSERVICE_PORTTYPE("ContextService");
const std::string QNAME_GETSERVICE_PORTTYPE("GetService");
const std::string QNAME_REPORTSERVICE_PORTTYPE("ReportService");
const std::string QNAME_SETSERVICE_PORTTYPE("SetService");
const std::string QNAME_STREAMSERVICE_PORTTYPE("WaveformStreamService");

// SOAP actions
const std::string ACTION_CDM_ACTIVATE_REQUEST(NS_MESSAGE_MODEL + "/" + QNAME_SETSERVICE_PORTTYPE + "/Activate");
const std::string ACTION_CDM_ACTIVATE_RESPONSE(NS_MESSAGE_MODEL + "/" + QNAME_SETSERVICE_PORTTYPE + "/ActivateResponse");

const std::string ACTION_CDM_GET_CONTEXTSTATES_REQUEST(NS_MESSAGE_MODEL + "/" + QNAME_CONTEXTSERVICE_PORTTYPE + "/GetContextStates");
const std::string ACTION_CDM_GET_CONTEXTSTATES_RESPONSE(NS_MESSAGE_MODEL + "/" + QNAME_CONTEXTSERVICE_PORTTYPE + "/GetContextStatesResponse");

const std::string ACTION_CDM_GET_MDDESCRIPTION_REQUEST(NS_MESSAGE_MODEL + "/" + QNAME_GETSERVICE_PORTTYPE + "/GetMDDescription");
const std::string ACTION_CDM_GET_MDDESCRIPTION_RESPONSE(NS_MESSAGE_MODEL + "/" + QNAME_GETSERVICE_PORTTYPE + "/GetMDDescriptionResponse");

const std::string ACTION_CDM_GET_MDIB_REQUEST(NS_MESSAGE_MODEL + "/" + QNAME_GETSERVICE_PORTTYPE + "/GetMDIB");
const std::string ACTION_CDM_GET_MDIB_RESPONSE(NS_MESSAGE_MODEL + "/" + QNAME_GETSERVICE_PORTTYPE + "/GetMDIBResponse");

const std::string ACTION_CDM_GET_MDSTATE_REQUEST(NS_MESSAGE_MODEL + "/" + QNAME_GETSERVICE_PORTTYPE + "/GetMDState");
const std::string ACTION_CDM_GET_MDSTATE_RESPONSE(NS_MESSAGE_MODEL + "/" + QNAME_GETSERVICE_PORTTYPE + "/GetMDStateResponse");

const std::string ACTION_CDM_SET_ALERT_STATE_REQUEST(NS_MESSAGE_MODEL + "/" + QNAME_SETSERVICE_PORTTYPE + "/SetAlertState");
const std::string ACTION_CDM_SET_ALERT_STATE_RESPONSE(NS_MESSAGE_MODEL + "/" + QNAME_SETSERVICE_PORTTYPE + "/SetAlertStateResponse");

const std::string ACTION_CDM_SET_CONTEXT_STATE_REQUEST(NS_MESSAGE_MODEL + "/" + QNAME_CONTEXTSERVICE_PORTTYPE + "/SetContextState");
const std::string ACTION_CDM_SET_CONTEXT_STATE_RESPONSE(NS_MESSAGE_MODEL + "/" + QNAME_CONTEXTSERVICE_PORTTYPE + "/SetContextStateResponse");

const std::string ACTION_CDM_SET_STRING_REQUEST(NS_MESSAGE_MODEL + "/" + QNAME_SETSERVICE_PORTTYPE + "/SetString");
const std::string ACTION_CDM_SET_STRING_RESPONSE(NS_MESSAGE_MODEL + "/" + QNAME_SETSERVICE_PORTTYPE + "/SetStringResponse");

const std::string ACTION_CDM_SET_VALUE_REQUEST(NS_MESSAGE_MODEL + "/" + QNAME_SETSERVICE_PORTTYPE + "/SetValue");
const std::string ACTION_CDM_SET_VALUE_RESPONSE(NS_MESSAGE_MODEL + "/" + QNAME_SETSERVICE_PORTTYPE + "/SetValueResponse");

const std::string EVENT_ACTION_CDM_DESCRIPTION_MODIFICATION_REPORT(NS_MESSAGE_MODEL + "/" + QNAME_REPORTSERVICE_PORTTYPE + "/DescriptionModificationReport");
const std::string EVENT_ACTION_CDM_EPISODIC_ALERT_REPORT(NS_MESSAGE_MODEL + "/" + QNAME_REPORTSERVICE_PORTTYPE + "/EpisodicAlertReport");
const std::string EVENT_ACTION_CDM_PERIODIC_ALERT_REPORT(NS_MESSAGE_MODEL + "/" + QNAME_REPORTSERVICE_PORTTYPE + "/PeriodicAlertReport");
const std::string EVENT_ACTION_CDM_EPISODIC_CONTEXT_REPORT(NS_MESSAGE_MODEL + "/" + QNAME_CONTEXTSERVICE_PORTTYPE + "/EpisodicContextChangedReport");
const std::string EVENT_ACTION_CDM_PERIODIC_CONTEXT_REPORT(NS_MESSAGE_MODEL + "/" + QNAME_CONTEXTSERVICE_PORTTYPE + "/PeriodicContextChangedReport");
const std::string EVENT_ACTION_CDM_EPISODIC_METRIC_REPORT(NS_MESSAGE_MODEL + "/" + QNAME_REPORTSERVICE_PORTTYPE + "/EpisodicMetricReport");
const std::string EVENT_ACTION_CDM_PERIODIC_METRIC_REPORT(NS_MESSAGE_MODEL + "/" + QNAME_REPORTSERVICE_PORTTYPE + "/PeriodicMetricReport");
const std::string EVENT_ACTION_CDM_OPERATION_INVOKED_REPORT(NS_MESSAGE_MODEL + "/" + QNAME_REPORTSERVICE_PORTTYPE + "/OperationInvokedReport");
const std::string EVENT_ACTION_CDM_WAVEFORM_STREAM_REPORT(NS_MESSAGE_MODEL + "/" + QNAME_STREAMSERVICE_PORTTYPE + "/WaveformStream");

}
}

#endif /* OSCPCONSTANTS_H_ */
