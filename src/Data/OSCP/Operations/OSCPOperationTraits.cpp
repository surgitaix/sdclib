/*
 * OSCPOperationTraits.cpp
 *
 *  Created on: 09.06.2015
 *      Author: roehser
 */

#include "OSCLib/Data/QName.h"
#include "OSCLib/Data/OSCP/OSCPProvider.h"
#include "OSCLib/Data/OSCP/Operations/OSCPOperationTraits.h"
#include "osdm.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

std::string ActivateTraits::OperationName() {
	return "Activate";
}
Data::QName ActivateTraits::PortType() {
	return OSCLib::Data::QName(QNAME_SETSERVICE_PORTTYPE, NS_WSDL_TARGET_NAMESPACE);
}
std::string ActivateTraits::RequestAction() {
	return ACTION_CDM_ACTIVATE_REQUEST;
}
Data::QName ActivateTraits::RequestType() {
	return QName("Activate", NS_MESSAGE_MODEL);
}
std::string ActivateTraits::ResponseAction() {
	return ACTION_CDM_ACTIVATE_RESPONSE;
}
Data::QName ActivateTraits::ResponseType() {
	return QName("ActivateResponse", NS_MESSAGE_MODEL);
}
ActivateTraits::Response ActivateTraits::dispatch(OSCPProvider & provider, const Request & request) {
	return provider.OnActivateAsync(request);
}

std::string GetContextStatesTraits::OperationName() {
	return "GetContextStates";
}
Data::QName GetContextStatesTraits::PortType() {
	return OSCLib::Data::QName(QNAME_CONTEXTSERVICE_PORTTYPE, NS_WSDL_TARGET_NAMESPACE);
}
std::string GetContextStatesTraits::RequestAction() {
	return ACTION_CDM_GET_CONTEXTSTATES_REQUEST;
}
Data::QName GetContextStatesTraits::RequestType() {
	return QName("GetContextStates", NS_MESSAGE_MODEL);
}
std::string GetContextStatesTraits::ResponseAction() {
	return ACTION_CDM_GET_CONTEXTSTATES_RESPONSE;
}
Data::QName GetContextStatesTraits::ResponseType() {
	return QName("GetContextStatesResponse", NS_MESSAGE_MODEL);
}
GetContextStatesTraits::Response GetContextStatesTraits::dispatch(OSCPProvider & provider, const Request & request) {
	return provider.GetContextStates(request);
}

std::string GetMDDescriptionTraits::OperationName() {
	return "GetMDDescription";
}
Data::QName GetMDDescriptionTraits::PortType() {
	return OSCLib::Data::QName(QNAME_GETSERVICE_PORTTYPE, NS_WSDL_TARGET_NAMESPACE);
}
std::string GetMDDescriptionTraits::RequestAction() {
	return ACTION_CDM_GET_MDDESCRIPTION_REQUEST;
}
Data::QName GetMDDescriptionTraits::RequestType() {
	return QName("GetMDDescription", NS_MESSAGE_MODEL);
}
std::string GetMDDescriptionTraits::ResponseAction() {
	return ACTION_CDM_GET_MDDESCRIPTION_RESPONSE;
}
Data::QName GetMDDescriptionTraits::ResponseType() {
	return QName("GetMDDescriptionResponse", NS_MESSAGE_MODEL);
}
GetMDDescriptionTraits::Response GetMDDescriptionTraits::dispatch(OSCPProvider & provider, const Request & request) {
	return provider.GetMDDescription(request);
}

std::string GetMDIBTraits::OperationName() {
	return "GetMDIB";
}
Data::QName GetMDIBTraits::PortType() {
	return OSCLib::Data::QName(QNAME_GETSERVICE_PORTTYPE, NS_WSDL_TARGET_NAMESPACE);
}
std::string GetMDIBTraits::RequestAction() {
	return ACTION_CDM_GET_MDIB_REQUEST;
}
Data::QName GetMDIBTraits::RequestType() {
	return QName("GetMDIB", NS_MESSAGE_MODEL);
}
std::string GetMDIBTraits::ResponseAction() {
	return ACTION_CDM_GET_MDIB_RESPONSE;
}
Data::QName GetMDIBTraits::ResponseType() {
	return QName("GetMDIBResponse", NS_MESSAGE_MODEL);
}
GetMDIBTraits::Response GetMDIBTraits::dispatch(OSCPProvider & provider, const Request & request) {
	return provider.GetMDIB(request);
}

std::string GetMDStateTraits::OperationName() {
	return "GetMDState";
}
Data::QName GetMDStateTraits::PortType() {
	return OSCLib::Data::QName(QNAME_GETSERVICE_PORTTYPE, NS_WSDL_TARGET_NAMESPACE);
}
std::string GetMDStateTraits::RequestAction() {
	return ACTION_CDM_GET_MDSTATE_REQUEST;
}
Data::QName GetMDStateTraits::RequestType() {
	return QName("GetMDState", NS_MESSAGE_MODEL);
}
std::string GetMDStateTraits::ResponseAction() {
	return ACTION_CDM_GET_MDSTATE_RESPONSE;
}
Data::QName GetMDStateTraits::ResponseType() {
	return QName("GetMDStateResponse", NS_MESSAGE_MODEL);
}
GetMDStateTraits::Response GetMDStateTraits::dispatch(OSCPProvider & provider, const Request & request) {
	return provider.GetMDState(request);
}

std::string SetAlertStateTraits::OperationName() {
	return "SetAlertState";
}
Data::QName SetAlertStateTraits::PortType() {
	return OSCLib::Data::QName(QNAME_SETSERVICE_PORTTYPE, NS_WSDL_TARGET_NAMESPACE);;
}
std::string SetAlertStateTraits::RequestAction() {
	return ACTION_CDM_SET_ALERT_STATE_REQUEST;
}
Data::QName SetAlertStateTraits::RequestType() {
	return QName("SetAlertState", NS_MESSAGE_MODEL);
}
std::string SetAlertStateTraits::ResponseAction() {
	return ACTION_CDM_SET_ALERT_STATE_RESPONSE;
}
Data::QName SetAlertStateTraits::ResponseType() {
	return QName("SetAlertStateResponse", NS_MESSAGE_MODEL);
}
SetAlertStateTraits::Response SetAlertStateTraits::dispatch(OSCPProvider & provider, const Request & request) {
	return provider.SetAlertStateAsync(request);
}

std::string SetContextStateTraits::OperationName() {
	return "SetContextState";
}
Data::QName SetContextStateTraits::PortType() {
	return OSCLib::Data::QName(QNAME_CONTEXTSERVICE_PORTTYPE, NS_WSDL_TARGET_NAMESPACE);
}
std::string SetContextStateTraits::RequestAction() {
	return ACTION_CDM_SET_CONTEXT_STATE_REQUEST;
}
Data::QName SetContextStateTraits::RequestType() {
	return QName("SetContextState", NS_MESSAGE_MODEL);
}
std::string SetContextStateTraits::ResponseAction() {
	return ACTION_CDM_SET_CONTEXT_STATE_RESPONSE;
}
Data::QName SetContextStateTraits::ResponseType() {
	return QName("SetContextStateResponse", NS_MESSAGE_MODEL);
}
SetContextStateTraits::Response SetContextStateTraits::dispatch(OSCPProvider & provider, const Request & request) {
	return provider.SetContextStateAsync(request);
}

std::string SetStringTraits::OperationName() {
	return "SetString";
}
Data::QName SetStringTraits::PortType() {
	return OSCLib::Data::QName(QNAME_SETSERVICE_PORTTYPE, NS_WSDL_TARGET_NAMESPACE);
}
std::string SetStringTraits::RequestAction() {
	return ACTION_CDM_SET_STRING_REQUEST;
}
Data::QName SetStringTraits::RequestType() {
	return QName("SetString", NS_MESSAGE_MODEL);
}
std::string SetStringTraits::ResponseAction() {
	return ACTION_CDM_SET_STRING_RESPONSE;
}
Data::QName SetStringTraits::ResponseType() {
	return QName("SetStringResponse", NS_MESSAGE_MODEL);
}
SetStringTraits::Response SetStringTraits::dispatch(OSCPProvider & provider, const Request & request) {
	return provider.SetStringAsync(request);
}

std::string SetValueTraits::OperationName() {
	return "SetValue";
}
Data::QName SetValueTraits::PortType() {
	return OSCLib::Data::QName(QNAME_SETSERVICE_PORTTYPE, NS_WSDL_TARGET_NAMESPACE);
}
std::string SetValueTraits::RequestAction() {
	return ACTION_CDM_SET_VALUE_REQUEST;
}
Data::QName SetValueTraits::RequestType() {
	return QName("SetValue", NS_MESSAGE_MODEL);
}
std::string SetValueTraits::ResponseAction() {
	return ACTION_CDM_SET_VALUE_RESPONSE;
}
Data::QName SetValueTraits::ResponseType() {
	return QName("SetValueResponse", NS_MESSAGE_MODEL);
}
SetValueTraits::Response SetValueTraits::dispatch(OSCPProvider & provider, const Request & request) {
	return provider.SetValueAsync(request);
}

}
}
}
