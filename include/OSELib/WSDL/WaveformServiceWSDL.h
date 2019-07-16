#ifndef SDCLIB_WSDL_WAVEFORMSERVICEWSDL_H
#define SDCLIB_WSDL_WAVEFORMSERVICEWSDL_H

#include <string.h>

const std::string waveformServiceWsdl=R"(<wsdl:definitions xmlns:wsdl="http://schemas.xmlsoap.org/wsdl/" targetNamespace="http://standards.ieee.org/downloads/11073/11073-20701-2018" xmlns:soap="http://schemas.xmlsoap.org/wsdl/soap/" xmlns:tns="http://standards.ieee.org/downloads/11073/11073-20701-2018" xmlns:wsa="http://www.w3.org/2005/08/addressing" xmlns:wsp="http://www.w3.org/ns/ws-policy" xmlns:wsstm="http://standardized.namespace.org/ws-streaming" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:mm="http://standards.ieee.org/downloads/11073/11073-10207-2017/message">
    <wsdl:types>
        <xs:schema targetNamespace="http://standards.ieee.org/downloads/11073/11073-10207-2017/message" xmlns:xs="http://www.w3.org/2001/XMLSchema">
            <xs:include schemaLocation="BICEPS_MessageModel.xsd"/>
        </xs:schema>
    </wsdl:types>
    <wsdl:message name="Notification">
        <wsdl:part element="mm:Notification" name="parameters"/>
    </wsdl:message>
    <wsdl:portType name="WaveformService" xmlns:p1="http://schemas.xmlsoap.org/ws/2004/08/eventing" p1:EventSource="true">
        <wsdl:operation name="WaveformStream">
            <wsdl:output message="tns:Notification" wsa:Action="http://standards.ieee.org/downloads/11073/11073-20701-2018/WaveformService/WaveformStream"/>
        </wsdl:operation>
        <wsp:Policy>
            <wsstm:StreamSource>
                <wsstm:StreamDescriptions targetNamespace="http://standards.ieee.org/downloads/11073/11073-20701-2018/WaveformService">
                    <wsstm:streamType actionURI="http://standards.ieee.org/downloads/11073/11073-20701-2018/WaveformService/WaveformStream" element="mm:WaveformStream" id="WaveformStream" streamType="http://docs.oasis-open.org/ws-dd/soapoverudp/1.1/os/wsdd-soapoverudp-1.1-spec-os.html"/>
                </wsstm:StreamDescriptions>
            </wsstm:StreamSource>
        </wsp:Policy>
    </wsdl:portType>
    <wsdl:binding name="WaveformServiceBinding" type="tns:WaveformService" xmlns:p1="http://schemas.xmlsoap.org/wsdl/soap12/">
        <p1:binding style="document" transport="http://schemas.xmlsoap.org/soap/http"/>
        <wsdl:operation name="WaveformStream">
            <p1:operation soapAction="http://standards.ieee.org/downloads/11073/11073-20701-2018/WaveformService/WaveformStream" style="document"/>
            <wsdl:output>
                <p1:body use="literal"/>
            </wsdl:output>
        </wsdl:operation>
    </wsdl:binding>
</wsdl:definitions>
)";

#endif
