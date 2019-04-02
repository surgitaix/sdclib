#include <string.h>

const std::string stateEventServiceWsdl=R"(<wsdl:definitions xmlns:wsdl="http://schemas.xmlsoap.org/wsdl/" targetNamespace="http://standards.ieee.org/downloads/11073/11073-20701-2018" xmlns:soap="http://schemas.xmlsoap.org/wsdl/soap/" xmlns:tns="http://standards.ieee.org/downloads/11073/11073-20701-2018" xmlns:wsa="http://www.w3.org/2005/08/addressing" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:mm="http://standards.ieee.org/downloads/11073/11073-10207-2017/message">
    <wsdl:types>
        <xs:schema targetNamespace="http://standards.ieee.org/downloads/11073/11073-10207-2017/message" xmlns:xs="http://www.w3.org/2001/XMLSchema">
            <xs:include schemaLocation="BICEPS_MessageModel.xsd"/>
        </xs:schema>
    </wsdl:types>
    <wsdl:message name="EpisodicAlertReport">
        <wsdl:part element="mm:EpisodicAlertReport" name="parameters"/>
    </wsdl:message>
    <wsdl:message name="EpisodicMetricReport">
        <wsdl:part element="mm:EpisodicMetricReport" name="parameters"/>
    </wsdl:message>
    <wsdl:message name="OperationInvokedReport">
        <wsdl:part element="mm:OperationInvokedReport" name="parameters"/>
    </wsdl:message>
    <wsdl:message name="PeriodicAlertReport">
        <wsdl:part element="mm:PeriodicAlertReport" name="parameters"/>
    </wsdl:message>
    <wsdl:message name="PeriodicMetricReport">
        <wsdl:part element="mm:PeriodicMetricReport" name="parameters"/>
    </wsdl:message>
    <wsdl:portType name="StateEventService" xmlns:p1="http://schemas.xmlsoap.org/ws/2004/08/eventing" p1:EventSource="true">
        <wsdl:operation name="EpisodicAlertReport">
            <wsdl:output message="tns:EpisodicAlertReport" wsa:Action="http://standards.ieee.org/downloads/11073/11073-20701-2018/StateEventService/EpisodicAlertReport"/>
        </wsdl:operation>
        <wsdl:operation name="EpisodicMetricReport">
            <wsdl:output message="tns:EpisodicMetricReport" wsa:Action="http://standards.ieee.org/downloads/11073/11073-20701-2018/StateEventService/EpisodicMetricReport"/>
        </wsdl:operation>
        <wsdl:operation name="PeriodicAlertReport">
            <wsdl:output message="tns:PeriodicAlertReport" wsa:Action="http://standards.ieee.org/downloads/11073/11073-20701-2018/StateEventService/PeriodicAlertReport"/>
        </wsdl:operation>
        <wsdl:operation name="PeriodicMetricReport">
            <wsdl:output message="tns:PeriodicMetricReport" wsa:Action="http://standards.ieee.org/downloads/11073/11073-20701-2018/StateEventService/PeriodicMetricReport"/>
        </wsdl:operation>
    </wsdl:portType>
    <wsdl:binding name="StateEventServiceBinding" type="tns:StateEventService" xmlns:p1="http://schemas.xmlsoap.org/wsdl/soap12/">
        <p1:binding style="document" transport="http://schemas.xmlsoap.org/soap/http"/>
        <wsdl:operation name="EpisodicAlertReport">
            <p1:operation soapAction="http://standards.ieee.org/downloads/11073/11073-20701-2018/StateEventService/EpisodicAlertReport" style="document"/>
            <wsdl:output>
                <p1:body use="literal"/>
            </wsdl:output>
        </wsdl:operation>
        <wsdl:operation name="EpisodicMetricReport">
            <p1:operation soapAction="http://standards.ieee.org/downloads/11073/11073-20701-2018/StateEventService/EpisodicMetricReport" style="document"/>
            <wsdl:output>
                <p1:body use="literal"/>
            </wsdl:output>
        </wsdl:operation>
        <wsdl:operation name="PeriodicAlertReport">
            <p1:operation soapAction="http://standards.ieee.org/downloads/11073/11073-20701-2018/StateEventService/PeriodicAlertReport" style="document"/>
            <wsdl:output>
                <p1:body use="literal"/>
            </wsdl:output>
        </wsdl:operation>
        <wsdl:operation name="PeriodicMetricReport">
            <p1:operation soapAction="http://standards.ieee.org/downloads/11073/11073-20701-2018/StateEventService/PeriodicMetricReport" style="document"/>
            <wsdl:output>
                <p1:body use="literal"/>
            </wsdl:output>
        </wsdl:operation>
    </wsdl:binding>
</wsdl:definitions>)";
