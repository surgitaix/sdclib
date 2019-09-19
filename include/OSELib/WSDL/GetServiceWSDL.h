#ifndef OSELIB_WSDL_GETSERVICEWSDL_H
#define OSELIB_WSDL_GETSERVICEWSDL_H

#include <string>

namespace OSELib
{
namespace WSDL
{

const std::string getServiceWsdl=std::string(
R"(<wsdl:definitions xmlns:wsdl="http://schemas.xmlsoap.org/wsdl/" xmlns:wsp="http://www.w3.org/ns/ws-policy" targetNamespace="http://standards.ieee.org/downloads/11073/11073-20701-2018" xmlns:soap="http://schemas.xmlsoap.org/wsdl/soap/" xmlns:tns="http://standards.ieee.org/downloads/11073/11073-20701-2018" xmlns:wsa="http://www.w3.org/2005/08/addressing" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:mm="http://standards.ieee.org/downloads/11073/11073-10207-2017/message" xmlns:dpws="http://docs.oasis-open.org/ws-dd/ns/dpws/2009/01">
    <wsdl:types>
        <xs:schema targetNamespace="http://standards.ieee.org/downloads/11073/11073-10207-2017/message" xmlns:xs="http://www.w3.org/2001/XMLSchema">
            <xs:include schemaLocation="BICEPS_MessageModel.xsd"/>
        </xs:schema>
    </wsdl:types>
    <wsdl:message name="GetMdDescription">
        <wsdl:part element="mm:GetMdDescription" name="parameters"/>
    </wsdl:message>
    <wsdl:message name="GetMdDescriptionResponse">
        <wsdl:part element="mm:GetMdDescriptionResponse" name="parameters"/>
    </wsdl:message>
    <wsdl:message name="GetMdib">
        <wsdl:part element="mm:GetMdib" name="parameters"/>
    </wsdl:message>
    <wsdl:message name="GetMdibResponse">
        <wsdl:part element="mm:GetMdibResponse" name="parameters"/>
    </wsdl:message>
    <wsdl:message name="GetMdState">
        <wsdl:part element="mm:GetMdState" name="parameters"/>
    </wsdl:message>
    <wsdl:message name="GetMdStateResponse">
        <wsdl:part element="mm:GetMdStateResponse" name="parameters"/>
    </wsdl:message>
    <wsdl:portType name="GetService" xmlns:p1="http://schemas.xmlsoap.org/ws/2004/08/eventing" dpws:DiscoveryType="p1:ServiceProvider">
        <wsdl:operation name="GetMdDescription">
            <wsdl:input message="tns:GetMdDescription" wsa:Action="http://standards.ieee.org/downloads/11073/11073-20701-2018/GetService/GetMdDescription"/>
            <wsdl:output message="tns:GetMdDescriptionResponse" wsa:Action="http://standards.ieee.org/downloads/11073/11073-20701-2018/GetService/GetMdDescriptionResponse"/>
        </wsdl:operation>
        <wsdl:operation name="GetMdib">
            <wsdl:input message="tns:GetMdib" wsa:Action="http://standards.ieee.org/downloads/11073/11073-20701-2018/GetService/GetMdib"/>
            <wsdl:output message="tns:GetMdibResponse" wsa:Action="http://standards.ieee.org/downloads/11073/11073-20701-2018/GetService/GetMdibResponse"/>
        </wsdl:operation>
        <wsdl:operation name="GetMdState">
            <wsdl:input message="tns:GetMdState" wsa:Action="http://standards.ieee.org/downloads/11073/11073-20701-2018/GetService/GetMdState"/>
            <wsdl:output message="tns:GetMdStateResponse" wsa:Action="http://standards.ieee.org/downloads/11073/11073-20701-2018/GetService/GetMdStateResponse"/>
        </wsdl:operation>
        <wsp:Policy>
            <dpws:Profile wsp:Optional="true"/>
        </wsp:Policy>
    </wsdl:portType>
    <wsdl:binding name="GetServiceBinding" type="tns:GetService">
        <soap:binding style="document" transport="http://schemas.xmlsoap.org/soap/http"/>
        <wsdl:operation name="GetMdDescription">
            <soap:operation soapAction="http://standards.ieee.org/downloads/11073/11073-20701-2018/GetService/GetMdDescription" style="document"/>
            <wsdl:input><soap:body use="literal"/></wsdl:input>
            <wsdl:output><soap:body use="literal"/></wsdl:output>
        </wsdl:operation>
        <wsdl:operation name="GetMdib">
            <soap:operation soapAction="http://standards.ieee.org/downloads/11073/11073-20701-2018/GetService/GetMdib" style="document"/>
            <wsdl:input><soap:body use="literal"/></wsdl:input>
            <wsdl:output><soap:body use="literal"/></wsdl:output>
        </wsdl:operation>
        <wsdl:operation name="GetMdState">
            <soap:operation soapAction="http://standards.ieee.org/downloads/11073/11073-20701-2018/GetService/GetMdState" style="document"/>
            <wsdl:input><soap:body use="literal"/></wsdl:input>
            <wsdl:output><soap:body use="literal"/></wsdl:output>
        </wsdl:operation>
    </wsdl:binding>
</wsdl:definitions>)");

}
}

#endif
