/*
 * OSCPOperationTraits.cpp
 *
 *  Created on: 09.06.2015
 *      Author: roehser
 */

#include <OSELib/SDC/SDCConstants.h>
#include "BICEPS_MessageModel.hxx"
#include "NormalizedMessageModel.hxx"

#include "OSELib/DPWS/DPWS11Constants.h"
#include "OSELib/SDC/IContextService.h"
#include "OSELib/SDC/IEventReport.h"
#include "OSELib/SDC/IGetService.h"
#include "OSELib/SDC/ISetService.h"
#include "OSELib/SDC/OperationTraits.h"

namespace OSELib {
namespace SDC {

std::string ActivateTraits::OperationName() {
	return "Activate";
}
xml_schema::Qname ActivateTraits::PortType() {
	return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_SETSERVICE_PORTTYPE);
}
std::string ActivateTraits::RequestAction() {
	return ACTION_CDM_ACTIVATE_REQUEST;
}
xml_schema::Qname ActivateTraits::RequestType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OperationName());
}
std::string ActivateTraits::ResponseAction() {
	return ACTION_CDM_ACTIVATE_RESPONSE;
}
xml_schema::Qname ActivateTraits::ResponseType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OperationName() + "Response");
}
std::unique_ptr<ActivateTraits::Response> ActivateTraits::dispatch(ActivateTraits::Dispatcher & dispatcher, const Request & request) {
	return dispatcher.dispatch(request);
}

std::string GetContextStatesTraits::OperationName() {
	return "GetContextStates";
}
xml_schema::Qname GetContextStatesTraits::PortType() {
	return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_CONTEXTSERVICE_PORTTYPE);
}
std::string GetContextStatesTraits::RequestAction() {
	return ACTION_CDM_GET_CONTEXTSTATES_REQUEST;
}
xml_schema::Qname GetContextStatesTraits::RequestType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OperationName());
}
std::string GetContextStatesTraits::ResponseAction() {
	return ACTION_CDM_GET_CONTEXTSTATES_RESPONSE;
}
xml_schema::Qname GetContextStatesTraits::ResponseType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OperationName() + "Response");
}
std::unique_ptr<GetContextStatesTraits::Response> GetContextStatesTraits::dispatch(GetContextStatesTraits::Dispatcher & dispatcher, const Request & request) {
	return dispatcher.dispatch(request);
}

std::string GetMDDescriptionTraits::OperationName() {
	return "GetMdDescription";
}
xml_schema::Qname GetMDDescriptionTraits::PortType() {
	return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_GETSERVICE_PORTTYPE);
}
std::string GetMDDescriptionTraits::RequestAction() {
	return ACTION_CDM_GET_MDDESCRIPTION_REQUEST;
}
xml_schema::Qname GetMDDescriptionTraits::RequestType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OperationName());
}
std::string GetMDDescriptionTraits::ResponseAction() {
	return ACTION_CDM_GET_MDDESCRIPTION_RESPONSE;
}
xml_schema::Qname GetMDDescriptionTraits::ResponseType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OperationName() + "Response");
}
std::unique_ptr<GetMDDescriptionTraits::Response> GetMDDescriptionTraits::dispatch(GetMDDescriptionTraits::Dispatcher & dispatcher, const Request & request) {
	return dispatcher.dispatch(request);
}

std::string GetMDIBTraits::OperationName() {
	return "GetMdib";
}
xml_schema::Qname GetMDIBTraits::PortType() {
	return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_GETSERVICE_PORTTYPE);
}
std::string GetMDIBTraits::RequestAction() {
	return ACTION_CDM_GET_MDIB_REQUEST;
}
xml_schema::Qname GetMDIBTraits::RequestType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OperationName());
}
std::string GetMDIBTraits::ResponseAction() {
	return ACTION_CDM_GET_MDIB_RESPONSE;
}
xml_schema::Qname GetMDIBTraits::ResponseType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OperationName() + "Response");
}
std::unique_ptr<GetMDIBTraits::Response> GetMDIBTraits::dispatch(GetMDIBTraits::Dispatcher & dispatcher, const Request & request) {
	return dispatcher.dispatch(request);
}

std::string GetMdStateTraits::OperationName() {
	return "GetMdState";
}
xml_schema::Qname GetMdStateTraits::PortType() {
	return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_GETSERVICE_PORTTYPE);
}
std::string GetMdStateTraits::RequestAction() {
	return ACTION_CDM_GET_MDSTATE_REQUEST;
}
xml_schema::Qname GetMdStateTraits::RequestType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OperationName());
}
std::string GetMdStateTraits::ResponseAction() {
	return ACTION_CDM_GET_MDSTATE_RESPONSE;
}
xml_schema::Qname GetMdStateTraits::ResponseType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OperationName() + "Response");
}
std::unique_ptr<GetMdStateTraits::Response> GetMdStateTraits::dispatch(GetMdStateTraits::Dispatcher & dispatcher, const Request & request) {
	return dispatcher.dispatch(request);
}

std::string SetAlertStateTraits::OperationName() {
	return "SetAlertState";
}
xml_schema::Qname SetAlertStateTraits::PortType() {
	return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_SETSERVICE_PORTTYPE);
}
std::string SetAlertStateTraits::RequestAction() {
	return ACTION_CDM_SET_ALERT_STATE_REQUEST;
}
xml_schema::Qname SetAlertStateTraits::RequestType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OperationName());
}
std::string SetAlertStateTraits::ResponseAction() {
	return ACTION_CDM_SET_ALERT_STATE_RESPONSE;
}
xml_schema::Qname SetAlertStateTraits::ResponseType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OperationName() + "Response");
}
std::unique_ptr<SetAlertStateTraits::Response> SetAlertStateTraits::dispatch(SetAlertStateTraits::Dispatcher & dispatcher, const Request & request) {
	return dispatcher.dispatch(request);
}

std::string SetContextStateTraits::OperationName() {
	return "SetContextState";
}
xml_schema::Qname SetContextStateTraits::PortType() {
	return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_CONTEXTSERVICE_PORTTYPE);
}
std::string SetContextStateTraits::RequestAction() {
	return ACTION_CDM_SET_CONTEXT_STATE_REQUEST;
}
xml_schema::Qname SetContextStateTraits::RequestType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OperationName());
}
std::string SetContextStateTraits::ResponseAction() {
	return ACTION_CDM_SET_CONTEXT_STATE_RESPONSE;
}
xml_schema::Qname SetContextStateTraits::ResponseType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OperationName() + "Response");
}
std::unique_ptr<SetContextStateTraits::Response> SetContextStateTraits::dispatch(SetContextStateTraits::Dispatcher & dispatcher, const Request & request) {
	return dispatcher.dispatch(request);
}

std::string SetStringTraits::OperationName() {
	return "SetString";
}
xml_schema::Qname SetStringTraits::PortType() {
	return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_SETSERVICE_PORTTYPE);
}
std::string SetStringTraits::RequestAction() {
	return ACTION_CDM_SET_STRING_REQUEST;
}
xml_schema::Qname SetStringTraits::RequestType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OperationName());
}
std::string SetStringTraits::ResponseAction() {
	return ACTION_CDM_SET_STRING_RESPONSE;
}
xml_schema::Qname SetStringTraits::ResponseType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OperationName() + "Response");
}
std::unique_ptr<SetStringTraits::Response> SetStringTraits::dispatch(SetStringTraits::Dispatcher & dispatcher, const Request & request) {
	return dispatcher.dispatch(request);
}

std::string SetValueTraits::OperationName() {
	return "SetValue";
}
xml_schema::Qname SetValueTraits::PortType() {
	return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_SETSERVICE_PORTTYPE);
}
std::string SetValueTraits::RequestAction() {
	return ACTION_CDM_SET_VALUE_REQUEST;
}
xml_schema::Qname SetValueTraits::RequestType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OperationName());
}
std::string SetValueTraits::ResponseAction() {
	return ACTION_CDM_SET_VALUE_RESPONSE;
}
xml_schema::Qname SetValueTraits::ResponseType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OperationName() + "Response");
}
std::unique_ptr<SetValueTraits::Response> SetValueTraits::dispatch(SetValueTraits::Dispatcher & dispatcher, const Request & request) {
	return dispatcher.dispatch(request);
}

}
}
