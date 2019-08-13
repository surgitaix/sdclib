#ifndef SDCLIB_WSDL_CONTEXTSERVICEWSDL_H
#define SDCLIB_WSDL_CONTEXTSERVICEWSDL_H

#include <string.h>

const std::string contextServiceWsdl=R"(<wsdl:definitions xmlns:wsdl="http://schemas.xmlsoap.org/wsdl/" targetNamespace="http://standards.ieee.org/downloads/11073/11073-20701-2018" xmlns:soap="http://schemas.xmlsoap.org/wsdl/soap/" xmlns:tns="http://standards.ieee.org/downloads/11073/11073-20701-2018" xmlns:wsa="http://www.w3.org/2005/08/addressing" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:mm="http://standards.ieee.org/downloads/11073/11073-10207-2017/message">
    <wsdl:types>
        <xs:schema targetNamespace="http://standards.ieee.org/downloads/11073/11073-10207-2017/message" xmlns:xs="http://www.w3.org/2001/XMLSchema">
            <xs:include schemaLocation="BICEPS_MessageModel.xsd"/>
        </xs:schema>
    </wsdl:types>
    <wsdl:message name="GetContextStates">
        <wsdl:part element="mm:GetContextStates" name="parameters"/>
    </wsdl:message>
    <wsdl:message name="GetContextStatesResponse">
        <wsdl:part element="mm:GetContextStatesResponse" name="parameters"/>
    </wsdl:message>
    <wsdl:message name="SetContextState">
        <wsdl:part element="mm:SetContextState" name="parameters"/>
    </wsdl:message>
    <wsdl:message name="SetContextStateResponse">
        <wsdl:part element="mm:SetContextStateResponse" name="parameters"/>
    </wsdl:message>
    <wsdl:message name="EpisodicContextReport">
        <wsdl:part element="mm:EpisodicContextReport" name="parameters"/>
    </wsdl:message>
    <wsdl:message name="PeriodicContextReport">
        <wsdl:part element="mm:PeriodicContextReport" name="parameters"/>
    </wsdl:message>
    <wsdl:portType name="ContextService" xmlns:p1="http://schemas.xmlsoap.org/ws/2004/08/eventing" p1:EventSource="true">
        <wsdl:operation name="GetContextStates">
            <wsdl:input message="tns:GetContextStates" wsa:Action="http://standards.ieee.org/downloads/11073/11073-20701-2018/ContextService/GetContextStates"/>
            <wsdl:output message="tns:GetContextStatesResponse" wsa:Action="http://standards.ieee.org/downloads/11073/11073-20701-2018/ContextService/GetContextStatesResponse"/>
        </wsdl:operation>
        <wsdl:operation name="SetContextState">
            <wsdl:input message="tns:SetContextState" wsa:Action="http://standards.ieee.org/downloads/11073/11073-20701-2018/ContextService/SetContextState"/>
            <wsdl:output message="tns:SetContextStateResponse" wsa:Action="http://standards.ieee.org/downloads/11073/11073-20701-2018/ContextService/SetContextStateResponse"/>
        </wsdl:operation>
        <wsdl:operation name="EpisodicContextReport">
            <wsdl:output message="tns:EpisodicContextReport" wsa:Action="http://standards.ieee.org/downloads/11073/11073-20701-2018/ContextService/EpisodicContextReport"/>
        </wsdl:operation>
        <wsdl:operation name="PeriodicContextReport">
            <wsdl:output message="tns:PeriodicContextReport" wsa:Action="http://standards.ieee.org/downloads/11073/11073-20701-2018/ContextService/PeriodicContextReport"/>
        </wsdl:operation>
    </wsdl:portType>
    <wsdl:binding name="ContextServiceBinding" type="tns:ContextService" xmlns:p1="http://schemas.xmlsoap.org/wsdl/soap12/">
        <p1:binding style="document" transport="http://schemas.xmlsoap.org/soap/http"/>
        <wsdl:operation name="GetContextStates">
            <p1:operation soapAction="http://standards.ieee.org/downloads/11073/11073-20701-2018/ContextService/GetContextStates" style="document"/>
            <wsdl:input>
                <p1:body use="literal"/>
            </wsdl:input>
            <wsdl:output>
                <p1:body use="literal"/>
            </wsdl:output>
        </wsdl:operation>
        <wsdl:operation name="SetContextState">
            <p1:operation soapAction="http://standards.ieee.org/downloads/11073/11073-20701-2018/ContextService/SetContextState" style="document"/>
            <wsdl:input>
                <p1:body use="literal"/>
            </wsdl:input>
            <wsdl:output>
                <p1:body use="literal"/>
            </wsdl:output>
        </wsdl:operation>
        <wsdl:operation name="EpisodicContextReport">
            <p1:operation soapAction="http://standards.ieee.org/downloads/11073/11073-20701-2018/ContextService/EpisodicContextReport" style="document"/>
            <wsdl:output>
                <p1:body use="literal"/>
            </wsdl:output>
        </wsdl:operation>
        <wsdl:operation name="PeriodicContextReport">
            <p1:operation soapAction="http://standards.ieee.org/downloads/11073/11073-20701-2018/ContextService/PeriodicContextReport" style="document"/>
            <wsdl:output>
                <p1:body use="literal"/>
            </wsdl:output>
        </wsdl:operation>
    </wsdl:binding>
</wsdl:definitions>)";

#endif
