
#ifndef OSELIB_SDC_OPERATIONTRAITS_H_
#define OSELIB_SDC_OPERATIONTRAITS_H_

#include <memory>
#include <string>

#include "OSELib/fwd.h"


namespace OSELib
{
    namespace SDC
    {
        // ********************************************************************************************************************************************
        // B.1 Get Service
        // ********************************************************************************************************************************************
        struct GetMDIBTraits
        {
            typedef MDM::GetMdib Request;
            typedef MDM::GetMdibResponse Response;
            typedef IGetService Dispatcher;
            static std::string OperationName();
            static xml_schema::Qname PortType();
            static std::string RequestAction();
            static xml_schema::Qname RequestType();
            static std::string ResponseAction();
            static xml_schema::Qname ResponseType();
            static std::unique_ptr<Response> dispatch(Dispatcher& p_dispatcher, const Request& p_request);
        };

        struct GetMDDescriptionTraits
        {
            typedef MDM::GetMdDescription Request;
            typedef MDM::GetMdDescriptionResponse Response;
            typedef IGetService Dispatcher;
            static std::string OperationName();
            static xml_schema::Qname PortType();
            static std::string RequestAction();
            static xml_schema::Qname RequestType();
            static std::string ResponseAction();
            static xml_schema::Qname ResponseType();
            static std::unique_ptr<Response> dispatch(Dispatcher& p_dispatcher, const Request& p_request);
        };

        struct GetMdStateTraits
        {
            typedef MDM::GetMdState Request;
            typedef MDM::GetMdStateResponse Response;
            typedef IGetService Dispatcher;
            static std::string OperationName();
            static xml_schema::Qname PortType();
            static std::string RequestAction();
            static xml_schema::Qname RequestType();
            static std::string ResponseAction();
            static xml_schema::Qname ResponseType();
            static std::unique_ptr<Response> dispatch(Dispatcher& p_dispatcher, const Request& p_request);
        };


        // ********************************************************************************************************************************************
        // B.2 Set Service
        // ********************************************************************************************************************************************
        struct SetValueTraits
        {
            typedef MDM::SetValue Request;
            typedef MDM::SetValueResponse Response;
            typedef ISetService Dispatcher;
            static std::string OperationName();
            static xml_schema::Qname PortType();
            static std::string RequestAction();
            static xml_schema::Qname RequestType();
            static std::string ResponseAction();
            static xml_schema::Qname ResponseType();
            static std::unique_ptr<Response> dispatch(Dispatcher& p_dispatcher, const Request& p_request);
        };

        struct SetStringTraits
        {
            typedef MDM::SetString Request;
            typedef MDM::SetStringResponse Response;
            typedef ISetService Dispatcher;
            static std::string OperationName();
            static xml_schema::Qname PortType();
            static std::string RequestAction();
            static xml_schema::Qname RequestType();
            static std::string ResponseAction();
            static xml_schema::Qname ResponseType();
            static std::unique_ptr<Response> dispatch(Dispatcher& p_dispatcher, const Request& p_request);
        };

        struct ActivateTraits
        {
            typedef MDM::Activate Request;
            typedef MDM::ActivateResponse Response;
            typedef ISetService Dispatcher;
            static std::string OperationName();
            static xml_schema::Qname PortType();
            static std::string RequestAction();
            static xml_schema::Qname RequestType();
            static std::string ResponseAction();
            static xml_schema::Qname ResponseType();
            static std::unique_ptr<Response> dispatch(Dispatcher& p_dispatcher, const Request& p_request);
        };

        struct SetAlertStateTraits
        {
            typedef MDM::SetAlertState Request;
            typedef MDM::SetAlertStateResponse Response;
            typedef ISetService Dispatcher;
            static std::string OperationName();
            static xml_schema::Qname PortType();
            static std::string RequestAction();
            static xml_schema::Qname RequestType();
            static std::string ResponseAction();
            static xml_schema::Qname ResponseType();
            static std::unique_ptr<Response> dispatch(Dispatcher& p_dispatcher, const Request& p_request);
        };

        struct SetComponentStateTraits
		{
			typedef MDM::SetComponentState Request;
			typedef MDM::SetComponentStateResponse Response;
			typedef ISetService Dispatcher;
			static std::string OperationName();
			static xml_schema::Qname PortType();
			static std::string RequestAction();
			static xml_schema::Qname RequestType();
			static std::string ResponseAction();
			static xml_schema::Qname ResponseType();
			static std::unique_ptr<Response> dispatch(Dispatcher& p_dispatcher, const Request& p_request);
		};

        // SetMetricState

        struct OperationInvokedReportTraits
        {
            typedef MDM::OperationInvokedReport ReportType;
            typedef ISetServiceEventSink Dispatcher;
            static xml_schema::Qname MessageType();
            static std::string NotificationName();
            static xml_schema::Qname PortType();
            static std::string Action();
            static void dispatch(Dispatcher& p_dispatcher, const ReportType& p_request);
        };


        // ********************************************************************************************************************************************
        // B.3 Description Event Service
        // ********************************************************************************************************************************************
        struct DescriptionModificationReportTraits
        {
            typedef MDM::DescriptionModificationReport ReportType;
            typedef IDescriptionEventServiceEventSink Dispatcher;
            static xml_schema::Qname MessageType();
            static std::string NotificationName();
            static xml_schema::Qname PortType();
            static std::string Action();
            static void dispatch(Dispatcher& p_dispatcher, const ReportType& p_request);
        };


        // ********************************************************************************************************************************************
        // B.4 State Event Service
        // ********************************************************************************************************************************************

        // AlertReport
        struct EpisodicAlertReportTraits
        {
            typedef MDM::EpisodicAlertReport ReportType;
            typedef IStateEventServiceEventSink Dispatcher;
            static xml_schema::Qname MessageType();
            static std::string NotificationName();
            static xml_schema::Qname PortType();
            static std::string Action();
            static void dispatch(Dispatcher& p_dispatcher, const ReportType& p_request);
        };
        struct PeriodicAlertReportTraits
        {
            typedef MDM::PeriodicAlertReport ReportType;
            typedef IStateEventServiceEventSink Dispatcher;
            static xml_schema::Qname MessageType();
            static std::string NotificationName();
            static xml_schema::Qname PortType();
            static std::string Action();
            static void dispatch(Dispatcher& p_dispatcher, const ReportType& p_request);
        };

        // ComponentReport
        struct EpisodicComponentReportTraits
        {
            typedef MDM::EpisodicComponentReport ReportType;
            typedef IStateEventServiceEventSink Dispatcher;
            static xml_schema::Qname MessageType();
            static std::string NotificationName();
            static xml_schema::Qname PortType();
            static std::string Action();
            static void dispatch(Dispatcher& p_dispatcher, const ReportType& p_request);
        };
        // PERIODICCOMPONENTREPORT // TODO

        // MetricReport
        struct EpisodicMetricReportTraits
        {
            typedef MDM::EpisodicMetricReport ReportType;
            typedef IStateEventServiceEventSink Dispatcher;
            static xml_schema::Qname MessageType();
            static std::string NotificationName();
            static xml_schema::Qname PortType();
            static std::string Action();
            static void dispatch(Dispatcher& p_dispatcher, const ReportType& p_request);
        };
        struct PeriodicMetricReportTraits
        {
            typedef MDM::PeriodicMetricReport ReportType;
            typedef IStateEventServiceEventSink Dispatcher;
            static xml_schema::Qname MessageType();
            static std::string NotificationName();
            static xml_schema::Qname PortType();
            static std::string Action();
            static void dispatch(Dispatcher& p_dispatcher, const ReportType& p_request);
        };

        // OperationalStateReport
        struct EpisodicOperationalStateReportTraits
        {
            typedef MDM::EpisodicOperationalStateReport ReportType;
            typedef IStateEventServiceEventSink Dispatcher;
            static xml_schema::Qname MessageType();
            static std::string NotificationName();
            static xml_schema::Qname PortType();
            static std::string Action();
            static void dispatch(Dispatcher& p_dispatcher, const ReportType& p_request);
        };
        // PERIODICOperationalStateReport // TODO

        // SystemErrorReport // TODO

        // ********************************************************************************************************************************************
        // B.5 Context Service
        // ********************************************************************************************************************************************

        struct GetContextStatesTraits
        {
            typedef MDM::GetContextStates Request;
            typedef MDM::GetContextStatesResponse Response;
            typedef IContextService Dispatcher;
            static std::string OperationName();
            static xml_schema::Qname PortType();
            static std::string RequestAction();
            static xml_schema::Qname RequestType();
            static std::string ResponseAction();
            static xml_schema::Qname ResponseType();
            static std::unique_ptr<Response> dispatch(Dispatcher& p_dispatcher, const Request& p_request);
        };

        struct SetContextStateTraits
        {
            typedef MDM::SetContextState Request;
            typedef MDM::SetContextStateResponse Response;
            typedef IContextService Dispatcher;
            static std::string OperationName();
            static xml_schema::Qname PortType();
            static std::string RequestAction();
            static xml_schema::Qname RequestType();
            static std::string ResponseAction();
            static xml_schema::Qname ResponseType();
            static std::unique_ptr<Response> dispatch(Dispatcher& p_dispatcher, const Request& p_request);
        };

        // GETCONTEXTSTATESBYIDENTIFICATION // TODO
        // GETCONTEXTSTATESBYFILTER // TODO

        struct EpisodicContextReportTraits
        {
            typedef MDM::EpisodicContextReport ReportType;
            typedef IContextServiceEventSink Dispatcher;
            static xml_schema::Qname MessageType();
            static std::string NotificationName();
            static xml_schema::Qname PortType();
            static std::string Action();
            static void dispatch(Dispatcher& p_dispatcher, const ReportType& p_request);
        };

        struct PeriodicContextReportTraits
        {
            typedef MDM::PeriodicContextReport ReportType;
            typedef IContextServiceEventSink Dispatcher;
            static xml_schema::Qname MessageType();
            static std::string NotificationName();
            static xml_schema::Qname PortType();
            static std::string Action();
            static void dispatch(Dispatcher& p_dispatcher, const ReportType& p_request);
        };

        // ********************************************************************************************************************************************
        // B.6 Waveform Service
        // ********************************************************************************************************************************************

        struct WaveformStreamTraits
        {
            typedef MDM::WaveformStream ReportType;
            typedef IStateEventServiceEventSink Dispatcher;
            static xml_schema::Qname MessageType();
            static std::string NotificationName();
            static xml_schema::Qname PortType();
            static std::string Action();
            static void dispatch(Dispatcher& p_dispatcher, const ReportType& p_request);
        };
        // ObservedValueStream // TODO


    }  // namespace SDC
}  // namespace OSELib
#endif
