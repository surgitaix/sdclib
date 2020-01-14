/*
 * OperationTraits.cpp
 *
 *  Created on: 09.06.2015, roehser
 *  Modified on: 24.09.2019, baumeister
 */

#include "OSELib/SDC/OperationTraits.h"
#include "OSELib/SDC/IContextService.h"
#include "OSELib/SDC/IEventReport.h"
#include "OSELib/SDC/IGetService.h"
#include "OSELib/SDC/ISetService.h"
#include "OSELib/SDC/SDCConstants.h"
#include "OSELib/DPWS/DPWS11Constants.h"

#include "DataModel/BICEPS_MessageModel.hxx"
#include "DataModel/NormalizedMessageModel.hxx"

namespace OSELib {
namespace SDC {

std::string ActivateTraits::OperationName() {
	return ACTIVATE;
}
xml_schema::Qname ActivateTraits::PortType() {
	return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_SETSERVICE_PORTTYPE);
}
std::string ActivateTraits::RequestAction() {
	return ACT_ACTIVATE_REQUEST;
}
xml_schema::Qname ActivateTraits::RequestType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OP_ACTIVATE_REQUEST);
}
std::string ActivateTraits::ResponseAction() {
	return ACT_ACTIVATE_RESPONSE;
}
xml_schema::Qname ActivateTraits::ResponseType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OP_ACTIVATE_RESPONSE);
}
std::unique_ptr<ActivateTraits::Response> ActivateTraits::dispatch(ActivateTraits::Dispatcher & p_dispatcher, const Request & p_request) {
	return p_dispatcher.dispatch(p_request);
}

std::string GetContextStatesTraits::OperationName() {
	return GET_CONTEXTSTATES;
}
xml_schema::Qname GetContextStatesTraits::PortType() {
	return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_CONTEXTSERVICE_PORTTYPE);
}
std::string GetContextStatesTraits::RequestAction() {
	return ACT_GET_CONTEXTSTATES_REQUEST;
}
xml_schema::Qname GetContextStatesTraits::RequestType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OP_GET_CONTEXTSTATES_REQUEST);
}
std::string GetContextStatesTraits::ResponseAction() {
	return ACT_GET_CONTEXTSTATES_RESPONSE;
}
xml_schema::Qname GetContextStatesTraits::ResponseType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OP_GET_CONTEXTSTATES_RESPONSE);
}
std::unique_ptr<GetContextStatesTraits::Response> GetContextStatesTraits::dispatch(GetContextStatesTraits::Dispatcher & p_dispatcher, const Request & p_request) {
	return p_dispatcher.dispatch(p_request);
}

std::string GetMDDescriptionTraits::OperationName() {
	return GET_MDDESCRIPTION;
}
xml_schema::Qname GetMDDescriptionTraits::PortType() {
	return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_GETSERVICE_PORTTYPE);
}
std::string GetMDDescriptionTraits::RequestAction() {
	return ACT_GET_MDDESCRIPTION_REQUEST;
}
xml_schema::Qname GetMDDescriptionTraits::RequestType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OP_GET_MDDESCRIPTION_REQUEST);
}
std::string GetMDDescriptionTraits::ResponseAction() {
	return ACT_GET_MDDESCRIPTION_RESPONSE;
}
xml_schema::Qname GetMDDescriptionTraits::ResponseType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OP_GET_MDDESCRIPTION_RESPONSE);
}
std::unique_ptr<GetMDDescriptionTraits::Response> GetMDDescriptionTraits::dispatch(GetMDDescriptionTraits::Dispatcher & p_dispatcher, const Request & p_request) {
	return p_dispatcher.dispatch(p_request);
}

std::string GetMDIBTraits::OperationName() {
	return GET_MDIB;
}
xml_schema::Qname GetMDIBTraits::PortType() {
	return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_GETSERVICE_PORTTYPE);
}
std::string GetMDIBTraits::RequestAction() {
	return ACT_GET_MDIB_REQUEST;
}
xml_schema::Qname GetMDIBTraits::RequestType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OP_GET_MDIB_REQUEST);
}
std::string GetMDIBTraits::ResponseAction() {
	return ACT_GET_MDIB_RESPONSE;
}
xml_schema::Qname GetMDIBTraits::ResponseType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OP_GET_MDIB_RESPONSE);
}
std::unique_ptr<GetMDIBTraits::Response> GetMDIBTraits::dispatch(GetMDIBTraits::Dispatcher & p_dispatcher, const Request & p_request) {
	return p_dispatcher.dispatch(p_request);
}

std::string GetMdStateTraits::OperationName() {
	return GET_MDSTATE;
}
xml_schema::Qname GetMdStateTraits::PortType() {
	return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_GETSERVICE_PORTTYPE);
}
std::string GetMdStateTraits::RequestAction() {
	return ACT_GET_MDSTATE_REQUEST;
}
xml_schema::Qname GetMdStateTraits::RequestType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OP_GET_MDSTATE_REQUEST);
}
std::string GetMdStateTraits::ResponseAction() {
	return ACT_GET_MDSTATE_RESPONSE;
}
xml_schema::Qname GetMdStateTraits::ResponseType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OP_GET_MDSTATE_RESPONSE);
}
std::unique_ptr<GetMdStateTraits::Response> GetMdStateTraits::dispatch(GetMdStateTraits::Dispatcher & p_dispatcher, const Request & p_request) {
	return p_dispatcher.dispatch(p_request);
}

// B.2 Set Service
std::string SetValueTraits::OperationName() {
	return SET_VALUE;
}
xml_schema::Qname SetValueTraits::PortType() {
	return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_SETSERVICE_PORTTYPE);
}
std::string SetValueTraits::RequestAction() {
	return ACT_SET_VALUE_REQUEST;
}
xml_schema::Qname SetValueTraits::RequestType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OP_SET_VALUE_REQUEST);
}
std::string SetValueTraits::ResponseAction() {
	return ACT_SET_VALUE_RESPONSE;
}
xml_schema::Qname SetValueTraits::ResponseType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OP_SET_VALUE_RESPONSE);
}
std::unique_ptr<SetValueTraits::Response> SetValueTraits::dispatch(SetValueTraits::Dispatcher & p_dispatcher, const Request & p_request) {
	return p_dispatcher.dispatch(p_request);
}

std::string SetStringTraits::OperationName() {
	return SET_STRING;
}
xml_schema::Qname SetStringTraits::PortType() {
	return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_SETSERVICE_PORTTYPE);
}
std::string SetStringTraits::RequestAction() {
	return ACT_SET_STRING_REQUEST;
}
xml_schema::Qname SetStringTraits::RequestType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, ACT_SET_STRING_REQUEST);
}
std::string SetStringTraits::ResponseAction() {
	return ACT_SET_STRING_RESPONSE;
}
xml_schema::Qname SetStringTraits::ResponseType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, ACT_SET_STRING_RESPONSE);
}
std::unique_ptr<SetStringTraits::Response> SetStringTraits::dispatch(SetStringTraits::Dispatcher & p_dispatcher, const Request & p_request) {
	return p_dispatcher.dispatch(p_request);
}



std::string SetAlertStateTraits::OperationName() {
	return SET_ALERT_STATE;
}
xml_schema::Qname SetAlertStateTraits::PortType() {
	return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_SETSERVICE_PORTTYPE);
}
std::string SetAlertStateTraits::RequestAction() {
	return ACT_SET_ALERT_STATE_REQUEST;
}
xml_schema::Qname SetAlertStateTraits::RequestType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OP_SET_ALERT_STATE_REQUEST);
}
std::string SetAlertStateTraits::ResponseAction() {
	return ACT_SET_ALERT_STATE_RESPONSE;
}
xml_schema::Qname SetAlertStateTraits::ResponseType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OP_SET_ALERT_STATE_RESPONSE);
}
std::unique_ptr<SetAlertStateTraits::Response> SetAlertStateTraits::dispatch(SetAlertStateTraits::Dispatcher & p_dispatcher, const Request & p_request) {
	return p_dispatcher.dispatch(p_request);
}

std::string SetContextStateTraits::OperationName() {
	return SET_CONTEXTSTATE;
}
xml_schema::Qname SetContextStateTraits::PortType() {
	return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_CONTEXTSERVICE_PORTTYPE);
}
std::string SetContextStateTraits::RequestAction() {
	return ACT_SET_CONTEXTSTATE_REQUEST;
}
xml_schema::Qname SetContextStateTraits::RequestType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OP_SET_CONTEXTSTATE_REQUEST);
}
std::string SetContextStateTraits::ResponseAction() {
	return ACT_SET_CONTEXTSTATE_RESPONSE;
}
xml_schema::Qname SetContextStateTraits::ResponseType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OP_SET_CONTEXTSTATE_RESPONSE);
}
std::unique_ptr<SetContextStateTraits::Response> SetContextStateTraits::dispatch(SetContextStateTraits::Dispatcher & p_dispatcher, const Request & p_request) {
	return p_dispatcher.dispatch(p_request);
}

}
}
