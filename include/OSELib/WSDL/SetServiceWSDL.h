#ifndef OSELIB_WSDL_SETSERVICEWSDL_H
#define OSELIB_WSDL_SETSERVICEWSDL_H

#include <string>

namespace OSELib
{
namespace WSDL
{

const std::string setServiceWsdl=std::string(
R"(<wsdl:definitions xmlns:wsdl="http://schemas.xmlsoap.org/wsdl/" xmlns:wsp="http://www.w3.org/ns/ws-policy" targetNamespace="http://standards.ieee.org/downloads/11073/11073-20701-2018" xmlns:soap="http://schemas.xmlsoap.org/wsdl/soap/" xmlns:tns="http://standards.ieee.org/downloads/11073/11073-20701-2018" xmlns:wsa="http://www.w3.org/2005/08/addressing" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:mm="http://standards.ieee.org/downloads/11073/11073-10207-2017/message" xmlns:dpws="http://docs.oasis-open.org/ws-dd/ns/dpws/2009/01">
    <wsdl:types>
        <xs:schema targetNamespace="http://standards.ieee.org/downloads/11073/11073-10207-2017/message" xmlns:xs="http://www.w3.org/2001/XMLSchema">
            <xs:include schemaLocation="BICEPS_MessageModel.xsd"/>
        </xs:schema>
    </wsdl:types>
    <wsdl:message name="Activate">
        <wsdl:part element="mm:Activate" name="parameters"/>
    </wsdl:message>
    <wsdl:message name="ActivateResponse">
        <wsdl:part element="mm:ActivateResponse" name="parameters"/>
    </wsdl:message>
    <wsdl:message name="SetAlertState">
        <wsdl:part element="mm:SetAlertState" name="parameters"/>
    </wsdl:message>
    <wsdl:message name="SetAlertStateResponse">
        <wsdl:part element="mm:SetAlertStateResponse" name="parameters"/>
    </wsdl:message>
    <wsdl:message name="SetString">
        <wsdl:part element="mm:SetString" name="parameters"/>
    </wsdl:message>
    <wsdl:message name="SetStringResponse">
        <wsdl:part element="mm:SetStringResponse" name="parameters"/>
    </wsdl:message>
    <wsdl:message name="SetValue">
        <wsdl:part element="mm:SetValue" name="parameters"/>
    </wsdl:message>
    <wsdl:message name="SetValueResponse">
        <wsdl:part element="mm:SetValueResponse" name="parameters"/>
    </wsdl:message>
    <wsdl:message name="SetMetricState">
        <wsdl:part element="mm:SetMetricState" name="parameters"/>
    </wsdl:message>
    <wsdl:message name="SetMetricStateResponse">
        <wsdl:part element="mm:SetMetricStateResponse" name="parameters"/>
    </wsdl:message>
    <wsdl:message name="OperationInvokedReport">
        <wsdl:part element="mm:OperationInvokedReport" name="parameters"/>
    </wsdl:message>        
    <wsdl:portType name="SetService" xmlns:p1="http://schemas.xmlsoap.org/ws/2004/08/eventing" p1:EventSource="true" dpws:DiscoveryType="p1:ServiceProvider">
        <wsdl:operation name="Activate">
            <wsdl:input message="tns:Activate" wsa:Action="http://standards.ieee.org/downloads/11073/11073-20701-2018/SetService/Activate"/>
            <wsdl:output message="tns:ActivateResponse" wsa:Action="http://standards.ieee.org/downloads/11073/11073-20701-2018/SetService/ActivateResponse"/>
        </wsdl:operation>
        <wsdl:operation name="SetAlertState">
            <wsdl:input message="tns:SetAlertState" wsa:Action="http://standards.ieee.org/downloads/11073/11073-20701-2018/SetService/SetAlertState"/>
            <wsdl:output message="tns:SetAlertStateResponse" wsa:Action="http://standards.ieee.org/downloads/11073/11073-20701-2018/SetService/SetAlertStateResponse"/>
        </wsdl:operation>
        <wsdl:operation name="SetString">
            <wsdl:input message="tns:SetString" wsa:Action="http://standards.ieee.org/downloads/11073/11073-20701-2018/SetService/SetString"/>
            <wsdl:output message="tns:SetStringResponse" wsa:Action="http://standards.ieee.org/downloads/11073/11073-20701-2018/SetService/SetStringResponse"/>
        </wsdl:operation>
        <wsdl:operation name="SetValue">
            <wsdl:input message="tns:SetValue" wsa:Action="http://standards.ieee.org/downloads/11073/11073-20701-2018/SetService/SetValue"/>
            <wsdl:output message="tns:SetValueResponse" wsa:Action="http://standards.ieee.org/downloads/11073/11073-20701-2018/SetService/SetValueResponse"/>
        </wsdl:operation>
        <wsdl:operation name="SetMetricState">
            <wsdl:input message="tns:SetMetricState" wsa:Action="http://standards.ieee.org/downloads/11073/11073-20701-2018/SetService/SetMetricState"/>
            <wsdl:output message="tns:SetMetricStateResponse" wsa:Action="http://standards.ieee.org/downloads/11073/11073-20701-2018/SetService/SetMetricStateResponse"/>
        </wsdl:operation>
        <wsdl:operation name="OperationInvokedReport">
            <wsdl:output message="tns:OperationInvokedReport" wsa:Action="http://standards.ieee.org/downloads/11073/11073-20701-2018/SetService/OperationInvokedReport"/>
        </wsdl:operation>
        <wsp:Policy>
            <dpws:Profile wsp:Optional="true" />
        </wsp:Policy>
    </wsdl:portType>
    <wsdl:binding name="SetServiceBinding" type="tns:SetService">
        <soap:binding style="document" transport="http://schemas.xmlsoap.org/soap/http"/>
        <wsdl:operation name="Activate">
            <soap:operation soapAction="http://standards.ieee.org/downloads/11073/11073-20701-2018/SetService/Activate" style="document"/>
            <wsdl:input><soap:body use="literal"/></wsdl:input>
            <wsdl:output><soap:body use="literal"/></wsdl:output>
        </wsdl:operation>
        <wsdl:operation name="SetAlertState">
            <soap:operation soapAction="http://standards.ieee.org/downloads/11073/11073-20701-2018/SetService/SetAlertState" style="document"/>
            <wsdl:input><soap:body use="literal"/></wsdl:input>
            <wsdl:output><soap:body use="literal"/></wsdl:output>
        </wsdl:operation>
        <wsdl:operation name="SetString">
            <soap:operation soapAction="http://standards.ieee.org/downloads/11073/11073-20701-2018/SetService/SetString" style="document"/>
            <wsdl:input><soap:body use="literal"/></wsdl:input>
            <wsdl:output><soap:body use="literal"/></wsdl:output>
        </wsdl:operation>
        <wsdl:operation name="SetValue">
            <soap:operation soapAction="http://standards.ieee.org/downloads/11073/11073-20701-2018/SetService/SetValue" style="document"/>
            <wsdl:input><soap:body use="literal"/></wsdl:input>
            <wsdl:output><soap:body use="literal"/></wsdl:output>
        </wsdl:operation>
        <wsdl:operation name="SetMetricState">
            <soap:operation soapAction="http://standards.ieee.org/downloads/11073/11073-20701-2018/SetService/SetMetricState" style="document"/>
            <wsdl:input><soap:body use="literal"/></wsdl:input>
            <wsdl:output><soap:body use="literal"/></wsdl:output>
        </wsdl:operation>
        <wsdl:operation name="OperationInvokedReport">
            <soap:operation soapAction="http://standards.ieee.org/downloads/11073/11073-20701-2018/SetService/OperationInvokedReport" style="document"/>
            <wsdl:output><soap:body use="literal"/></wsdl:output>
        </wsdl:operation>                
    </wsdl:binding>
</wsdl:definitions>)");

}
}

#endif
