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
#include "OSELib/SDC/IDescriptionEventServiceEventSink.h"
#include "OSELib/SDC/IStateEventServiceEventSink.h"
#include "OSELib/SDC/IContextServiceEventSink.h"
#include "OSELib/SDC/ISetServiceEventSink.h"
#include "OSELib/SDC/SDCConstants.h"
#include "OSELib/DPWS/DPWS11Constants.h"

#include "DataModel/BICEPS_MessageModel.hxx"
#include "DataModel/NormalizedMessageModel.hxx"


using namespace OSELib;
using namespace OSELib::SDC;


// ********************************************************************************************************************************************
// B.1 Get Service
// ********************************************************************************************************************************************

// GetMdib
std::string GetMDIBTraits::OperationName()
{
    return GET_MDIB;
}
xml_schema::Qname GetMDIBTraits::PortType()
{
    return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_GETSERVICE_PORTTYPE);
}
std::string GetMDIBTraits::RequestAction()
{
    return ACT_GET_MDIB_REQUEST;
}
xml_schema::Qname GetMDIBTraits::RequestType()
{
    return xml_schema::Qname(NS_MESSAGE_MODEL, OP_GET_MDIB_REQUEST);
}
std::string GetMDIBTraits::ResponseAction()
{
    return ACT_GET_MDIB_RESPONSE;
}
xml_schema::Qname GetMDIBTraits::ResponseType()
{
    return xml_schema::Qname(NS_MESSAGE_MODEL, OP_GET_MDIB_RESPONSE);
}
std::unique_ptr<GetMDIBTraits::Response> GetMDIBTraits::dispatch(GetMDIBTraits::Dispatcher& p_dispatcher, const Request& p_request)
{
    return p_dispatcher.dispatch(p_request);
}
// GetMdDescription
std::string GetMDDescriptionTraits::OperationName()
{
    return GET_MDDESCRIPTION;
}
xml_schema::Qname GetMDDescriptionTraits::PortType()
{
    return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_GETSERVICE_PORTTYPE);
}
std::string GetMDDescriptionTraits::RequestAction()
{
    return ACT_GET_MDDESCRIPTION_REQUEST;
}
xml_schema::Qname GetMDDescriptionTraits::RequestType()
{
    return xml_schema::Qname(NS_MESSAGE_MODEL, OP_GET_MDDESCRIPTION_REQUEST);
}
std::string GetMDDescriptionTraits::ResponseAction()
{
    return ACT_GET_MDDESCRIPTION_RESPONSE;
}
xml_schema::Qname GetMDDescriptionTraits::ResponseType()
{
    return xml_schema::Qname(NS_MESSAGE_MODEL, OP_GET_MDDESCRIPTION_RESPONSE);
}
std::unique_ptr<GetMDDescriptionTraits::Response> GetMDDescriptionTraits::dispatch(GetMDDescriptionTraits::Dispatcher& p_dispatcher,
                                                                                   const Request& p_request)
{
    return p_dispatcher.dispatch(p_request);
}
// GetMdState
std::string GetMdStateTraits::OperationName()
{
    return GET_MDSTATE;
}
xml_schema::Qname GetMdStateTraits::PortType()
{
    return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_GETSERVICE_PORTTYPE);
}
std::string GetMdStateTraits::RequestAction()
{
    return ACT_GET_MDSTATE_REQUEST;
}
xml_schema::Qname GetMdStateTraits::RequestType()
{
    return xml_schema::Qname(NS_MESSAGE_MODEL, OP_GET_MDSTATE_REQUEST);
}
std::string GetMdStateTraits::ResponseAction()
{
    return ACT_GET_MDSTATE_RESPONSE;
}
xml_schema::Qname GetMdStateTraits::ResponseType()
{
    return xml_schema::Qname(NS_MESSAGE_MODEL, OP_GET_MDSTATE_RESPONSE);
}
std::unique_ptr<GetMdStateTraits::Response> GetMdStateTraits::dispatch(GetMdStateTraits::Dispatcher& p_dispatcher, const Request& p_request)
{
    return p_dispatcher.dispatch(p_request);
}



// ********************************************************************************************************************************************
// B.2 Set Service
// ********************************************************************************************************************************************

// SetValue
std::string SetValueTraits::OperationName()
{
    return SET_VALUE;
}
xml_schema::Qname SetValueTraits::PortType()
{
    return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_SETSERVICE_PORTTYPE);
}
std::string SetValueTraits::RequestAction()
{
    return ACT_SET_VALUE_REQUEST;
}
xml_schema::Qname SetValueTraits::RequestType()
{
    return xml_schema::Qname(NS_MESSAGE_MODEL, OP_SET_VALUE_REQUEST);
}
std::string SetValueTraits::ResponseAction()
{
    return ACT_SET_VALUE_RESPONSE;
}
xml_schema::Qname SetValueTraits::ResponseType()
{
    return xml_schema::Qname(NS_MESSAGE_MODEL, OP_SET_VALUE_RESPONSE);
}
std::unique_ptr<SetValueTraits::Response> SetValueTraits::dispatch(SetValueTraits::Dispatcher& p_dispatcher, const Request& p_request)
{
    return p_dispatcher.dispatch(p_request);
}
// SetString
std::string SetStringTraits::OperationName()
{
    return SET_STRING;
}
xml_schema::Qname SetStringTraits::PortType()
{
    return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_SETSERVICE_PORTTYPE);
}
std::string SetStringTraits::RequestAction()
{
    return ACT_SET_STRING_REQUEST;
}
xml_schema::Qname SetStringTraits::RequestType()
{
    return xml_schema::Qname(NS_MESSAGE_MODEL, ACT_SET_STRING_REQUEST);
}
std::string SetStringTraits::ResponseAction()
{
    return ACT_SET_STRING_RESPONSE;
}
xml_schema::Qname SetStringTraits::ResponseType()
{
    return xml_schema::Qname(NS_MESSAGE_MODEL, ACT_SET_STRING_RESPONSE);
}
std::unique_ptr<SetStringTraits::Response> SetStringTraits::dispatch(SetStringTraits::Dispatcher& p_dispatcher, const Request& p_request)
{
    return p_dispatcher.dispatch(p_request);
}
// Activate
std::string ActivateTraits::OperationName()
{
    return ACTIVATE;
}
xml_schema::Qname ActivateTraits::PortType()
{
    return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_SETSERVICE_PORTTYPE);
}
std::string ActivateTraits::RequestAction()
{
    return ACT_ACTIVATE_REQUEST;
}
xml_schema::Qname ActivateTraits::RequestType()
{
    return xml_schema::Qname(NS_MESSAGE_MODEL, OP_ACTIVATE_REQUEST);
}
std::string ActivateTraits::ResponseAction()
{
    return ACT_ACTIVATE_RESPONSE;
}
xml_schema::Qname ActivateTraits::ResponseType()
{
    return xml_schema::Qname(NS_MESSAGE_MODEL, OP_ACTIVATE_RESPONSE);
}
std::unique_ptr<ActivateTraits::Response> ActivateTraits::dispatch(ActivateTraits::Dispatcher& p_dispatcher, const Request& p_request)
{
    return p_dispatcher.dispatch(p_request);
}
// SetAlertState
std::string SetAlertStateTraits::OperationName()
{
    return SET_ALERT_STATE;
}
xml_schema::Qname SetAlertStateTraits::PortType()
{
    return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_SETSERVICE_PORTTYPE);
}
std::string SetAlertStateTraits::RequestAction()
{
    return ACT_SET_ALERT_STATE_REQUEST;
}
xml_schema::Qname SetAlertStateTraits::RequestType()
{
    return xml_schema::Qname(NS_MESSAGE_MODEL, OP_SET_ALERT_STATE_REQUEST);
}
std::string SetAlertStateTraits::ResponseAction()
{
    return ACT_SET_ALERT_STATE_RESPONSE;
}
xml_schema::Qname SetAlertStateTraits::ResponseType()
{
    return xml_schema::Qname(NS_MESSAGE_MODEL, OP_SET_ALERT_STATE_RESPONSE);
}
std::unique_ptr<SetAlertStateTraits::Response> SetAlertStateTraits::dispatch(SetAlertStateTraits::Dispatcher& p_dispatcher,
                                                                             const Request& p_request)
{
    return p_dispatcher.dispatch(p_request);
}
// SetComponentState
std::string SetComponentStateTraits::OperationName()
{
    return SET_COMPONENT_STATE;
}
xml_schema::Qname SetComponentStateTraits::PortType()
{
    return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_SETSERVICE_PORTTYPE);
}
std::string SetComponentStateTraits::RequestAction()
{
    return ACT_SET_COMPONENT_STATE_REQUEST;
}
xml_schema::Qname SetComponentStateTraits::RequestType()
{
    return xml_schema::Qname(NS_MESSAGE_MODEL, OP_SET_COMPONENT_STATE_REQUEST);
}
std::string SetComponentStateTraits::ResponseAction()
{
    return ACT_SET_COMPONENT_STATE_RESPONSE;
}
xml_schema::Qname SetComponentStateTraits::ResponseType()
{
    return xml_schema::Qname(NS_MESSAGE_MODEL, OP_SET_COMPONENT_STATE_RESPONSE);
}
std::unique_ptr<SetComponentStateTraits::Response> SetComponentStateTraits::dispatch(SetComponentStateTraits::Dispatcher& p_dispatcher,
                                                                             const Request& p_request)
{
    return p_dispatcher.dispatch(p_request);
}
// SetMetricState // TODO
// OperationInvokedReport
xml_schema::Qname OperationInvokedReportTraits::MessageType()
{
    return xml_schema::Qname(NS_MESSAGE_MODEL, OP_OPERATION_INVOKED_REPORT);
}
std::string OperationInvokedReportTraits::NotificationName()
{
    return OPERATION_INVOKED_REPORT;
}
xml_schema::Qname OperationInvokedReportTraits::PortType()
{
    return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_STATEEVENTSERVICE_PORTTYPE);
}
std::string OperationInvokedReportTraits::Action()
{
    return ACT_OPERATION_INVOKED_REPORT;
}
void OperationInvokedReportTraits::dispatch(Dispatcher& p_dispatcher, const ReportType& p_report)
{
    p_dispatcher.dispatch(p_report);
}



// ********************************************************************************************************************************************
// B.3 Description Event Service
// ********************************************************************************************************************************************

// DescriptionModificationReport
xml_schema::Qname DescriptionModificationReportTraits::MessageType()
{
    return xml_schema::Qname(NS_MESSAGE_MODEL, OP_DESCRIPTION_MODIFICATION_REPORT);
}
std::string DescriptionModificationReportTraits::NotificationName()
{
    return DESCRIPTION_MODIFICATION_REPORT;
}
xml_schema::Qname DescriptionModificationReportTraits::PortType()
{
    return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_DESCRIPTIONEVENTSERVICE_PORTTYPE);
}
std::string DescriptionModificationReportTraits::Action()
{
    return ACT_DESCRIPTION_MODIFICATION_REPORT;
}
void DescriptionModificationReportTraits::dispatch(Dispatcher& p_dispatcher, const ReportType& p_report)
{
    p_dispatcher.dispatch(p_report);
}



// ********************************************************************************************************************************************
// B.4 State Event Service
// ********************************************************************************************************************************************

// EpisodicAlertReport
xml_schema::Qname EpisodicAlertReportTraits::MessageType()
{
    return xml_schema::Qname(NS_MESSAGE_MODEL, OP_EPISODIC_ALERT_REPORT);
}
std::string EpisodicAlertReportTraits::NotificationName()
{
    return EPISODIC_ALERT_REPORT;
}
xml_schema::Qname EpisodicAlertReportTraits::PortType()
{
    return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_STATEEVENTSERVICE_PORTTYPE);
}
std::string EpisodicAlertReportTraits::Action()
{
    return ACT_EPISODIC_ALERT_REPORT;
}
void EpisodicAlertReportTraits::dispatch(Dispatcher& p_dispatcher, const ReportType& p_report)
{
    p_dispatcher.dispatch(p_report);
}
// PeriodicAlertReport
xml_schema::Qname PeriodicAlertReportTraits::MessageType()
{
    return xml_schema::Qname(NS_MESSAGE_MODEL, OP_PERIODIC_ALERT_REPORT);
}
std::string PeriodicAlertReportTraits::NotificationName()
{
    return PERIODIC_ALERT_REPORT;
}
xml_schema::Qname PeriodicAlertReportTraits::PortType()
{
    return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_STATEEVENTSERVICE_PORTTYPE);
}
std::string PeriodicAlertReportTraits::Action()
{
    return ACT_PERIODIC_ALERT_REPORT;
}
void PeriodicAlertReportTraits::dispatch(Dispatcher& p_dispatcher, const ReportType& p_report)
{
    p_dispatcher.dispatch(p_report);
}
// EpisodicComponentReport
xml_schema::Qname EpisodicComponentReportTraits::MessageType()
{
    return xml_schema::Qname(NS_MESSAGE_MODEL, OP_EPISODIC_COMPONENT_REPORT);
}
std::string EpisodicComponentReportTraits::NotificationName()
{
    return EPISODIC_COMPONENT_REPORT;
}
xml_schema::Qname EpisodicComponentReportTraits::PortType()
{
    return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_STATEEVENTSERVICE_PORTTYPE);
}
std::string EpisodicComponentReportTraits::Action()
{
    return ACT_EPISODIC_COMPONENT_REPORT;
}
void EpisodicComponentReportTraits::dispatch(Dispatcher& p_dispatcher, const ReportType& p_report)
{
    p_dispatcher.dispatch(p_report);
}
// PeriodicComponentReport // TODO
// EpisodicMetricReport
xml_schema::Qname EpisodicMetricReportTraits::MessageType()
{
    return xml_schema::Qname(NS_MESSAGE_MODEL, OP_EPISODIC_METRIC_REPORT);
}
std::string EpisodicMetricReportTraits::NotificationName()
{
    return EPISODIC_METRIC_REPORT;
}
xml_schema::Qname EpisodicMetricReportTraits::PortType()
{
    return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_STATEEVENTSERVICE_PORTTYPE);
}
std::string EpisodicMetricReportTraits::Action()
{
    return ACT_EPISODIC_METRIC_REPORT;
}
void EpisodicMetricReportTraits::dispatch(Dispatcher& p_dispatcher, const ReportType& p_report)
{
    p_dispatcher.dispatch(p_report);
}
// PeriodicMetricReport
xml_schema::Qname PeriodicMetricReportTraits::MessageType()
{
    return xml_schema::Qname(NS_MESSAGE_MODEL, OP_PERIODIC_METRIC_REPORT);
}
std::string PeriodicMetricReportTraits::NotificationName()
{
    return PERIODIC_METRIC_REPORT;
}
xml_schema::Qname PeriodicMetricReportTraits::PortType()
{
    return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_STATEEVENTSERVICE_PORTTYPE);
}
std::string PeriodicMetricReportTraits::Action()
{
    return ACT_PERIODIC_METRIC_REPORT;
}
void PeriodicMetricReportTraits::dispatch(Dispatcher& p_dispatcher, const ReportType& p_report)
{
    p_dispatcher.dispatch(p_report);
}
// EpisodicOperationalStateReport
xml_schema::Qname EpisodicOperationalStateReportTraits::MessageType()
{
    return xml_schema::Qname(NS_MESSAGE_MODEL, OP_EPISODIC_OPERATIONALSTATE_REPORT);
}
std::string EpisodicOperationalStateReportTraits::NotificationName()
{
    return EPISODIC_OPERATIONALSTATE_REPORT;
}
xml_schema::Qname EpisodicOperationalStateReportTraits::PortType()
{
    return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_STATEEVENTSERVICE_PORTTYPE);
}
std::string EpisodicOperationalStateReportTraits::Action()
{
    return ACT_EPISODIC_OPERATIONALSTATE_REPORT;
}
void EpisodicOperationalStateReportTraits::dispatch(Dispatcher& p_dispatcher, const ReportType& p_report)
{
    p_dispatcher.dispatch(p_report);
}
// PeriodicOperationalStateReport // TODO
// SystemErrorReport // TODO



// ********************************************************************************************************************************************
// B.5 Context Service
// ********************************************************************************************************************************************

// GetContextStates
std::string GetContextStatesTraits::OperationName()
{
    return GET_CONTEXTSTATES;
}
xml_schema::Qname GetContextStatesTraits::PortType()
{
    return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_CONTEXTSERVICE_PORTTYPE);
}
std::string GetContextStatesTraits::RequestAction()
{
    return ACT_GET_CONTEXTSTATES_REQUEST;
}
xml_schema::Qname GetContextStatesTraits::RequestType()
{
    return xml_schema::Qname(NS_MESSAGE_MODEL, OP_GET_CONTEXTSTATES_REQUEST);
}
std::string GetContextStatesTraits::ResponseAction()
{
    return ACT_GET_CONTEXTSTATES_RESPONSE;
}
xml_schema::Qname GetContextStatesTraits::ResponseType()
{
    return xml_schema::Qname(NS_MESSAGE_MODEL, OP_GET_CONTEXTSTATES_RESPONSE);
}
std::unique_ptr<GetContextStatesTraits::Response> GetContextStatesTraits::dispatch(GetContextStatesTraits::Dispatcher& p_dispatcher,
                                                                                   const Request& p_request)
{
    return p_dispatcher.dispatch(p_request);
}
// SetContextState
std::string SetContextStateTraits::OperationName()
{
    return SET_CONTEXTSTATE;
}
xml_schema::Qname SetContextStateTraits::PortType()
{
    return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_CONTEXTSERVICE_PORTTYPE);
}
std::string SetContextStateTraits::RequestAction()
{
    return ACT_SET_CONTEXTSTATE_REQUEST;
}
xml_schema::Qname SetContextStateTraits::RequestType()
{
    return xml_schema::Qname(NS_MESSAGE_MODEL, OP_SET_CONTEXTSTATE_REQUEST);
}
std::string SetContextStateTraits::ResponseAction()
{
    return ACT_SET_CONTEXTSTATE_RESPONSE;
}
xml_schema::Qname SetContextStateTraits::ResponseType()
{
    return xml_schema::Qname(NS_MESSAGE_MODEL, OP_SET_CONTEXTSTATE_RESPONSE);
}
std::unique_ptr<SetContextStateTraits::Response> SetContextStateTraits::dispatch(SetContextStateTraits::Dispatcher& p_dispatcher,
                                                                                 const Request& p_request)
{
    return p_dispatcher.dispatch(p_request);
}
// GetContextStatesByIdentification // TODO
// GetContextStatesByFilter // TODO
// EpisodicContextReport
xml_schema::Qname EpisodicContextReportTraits::MessageType()
{
    return xml_schema::Qname(NS_MESSAGE_MODEL, OP_EPISODIC_CONTEXT_REPORT);
}
std::string EpisodicContextReportTraits::NotificationName()
{
    return EPISODIC_CONTEXT_REPORT;
}
xml_schema::Qname EpisodicContextReportTraits::PortType()
{
    return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_CONTEXTSERVICE_PORTTYPE);
}
std::string EpisodicContextReportTraits::Action()
{
    return ACT_EPISODIC_CONTEXT_REPORT;
}
void EpisodicContextReportTraits::dispatch(Dispatcher& p_dispatcher, const ReportType& p_report)
{
    p_dispatcher.dispatch(p_report);
}
// PeriodicContextReport
xml_schema::Qname PeriodicContextReportTraits::MessageType()
{
    return xml_schema::Qname(NS_MESSAGE_MODEL, OP_PERIODIC_CONTEXT_REPORT);
}
std::string PeriodicContextReportTraits::NotificationName()
{
    return PERIODIC_CONTEXT_REPORT;
}
xml_schema::Qname PeriodicContextReportTraits::PortType()
{
    return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_CONTEXTSERVICE_PORTTYPE);
}
std::string PeriodicContextReportTraits::Action()
{
    return ACT_PERIODIC_CONTEXT_REPORT;
}
void PeriodicContextReportTraits::dispatch(Dispatcher& p_dispatcher, const ReportType& p_report)
{
    p_dispatcher.dispatch(p_report);
}



// ********************************************************************************************************************************************
// B.6 Waveform Service
// ********************************************************************************************************************************************

// WaveformStream
xml_schema::Qname WaveformStreamTraits::MessageType()
{
    return xml_schema::Qname(NS_MESSAGE_MODEL, OP_WAVEFORM_STREAM_REPORT);
}
std::string WaveformStreamTraits::NotificationName()
{
    return WAVEFORM_STREAM;
}
xml_schema::Qname WaveformStreamTraits::PortType()
{
    return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_WAVEFORMSERVICE_PORTTYPE);
}
std::string WaveformStreamTraits::Action()
{
    return ACT_WAVEFORM_STREAM_REPORT;
}
void WaveformStreamTraits::dispatch(Dispatcher& p_dispatcher, const ReportType& p_report)
{
    p_dispatcher.dispatch(p_report);
}
// ObservedValueStream // TODO

