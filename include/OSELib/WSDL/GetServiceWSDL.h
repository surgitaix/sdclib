#ifndef OSELIB_WSDL_GETSERVICEWSDL_H
#define OSELIB_WSDL_GETSERVICEWSDL_H

#include "OSELib/SDC/SDCConstants.h"
#include "OSELib/Schema/SchemaBICEPSMessageModel.h"

namespace OSELib
{
namespace WSDL
{

const std::string getServiceWsdl=std::string(R"(<wsdl:definitions xmlns:wsdl=")" + SDC::NS_WSDL + R"(" xmlns:dpws=")" + SDC::NS_DPWS + R"(" xmlns:soap12="http://schemas.xmlsoap.org/wsdl/soap12/" targetNamespace=")" + SDC::NS_WSDL_TARGET_NAMESPACE + R"(" xmlns:tns=")" + SDC::NS_WSDL_TARGET_NAMESPACE + R"(" xmlns:wsp=")" + SDC::WS_POLICY + R"(" xmlns:wsa=")" + SDC::NS_ADDRESSING + R"(" xmlns:wse=")" + SDC::NS_EVENTING + R"(" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:msg=")" + SDC::NS_MESSAGE_MODEL + R"(" xmlns:pm=")" + SDC::NS_DOMAIN_MODEL + R"(">
<wsdl:types>
	<xs:schema targetNamespace=")" + SDC::NS_MESSAGE_MODEL + R"(" xmlns:xs="http://www.w3.org/2001/XMLSchema">
		<xs:include schemaLocation=")" + SCHEMA::SCHEMA_BICEPS_MESSAGEMODEL_NAME + R"("/>
	</xs:schema>
</wsdl:types>
<wsdl:message name=")" + SDC::OP_GET_MDIB_REQUEST + R"(">
	<wsdl:part element="msg:)" + SDC::OP_GET_MDIB_REQUEST + R"(" name="parameters"/>
</wsdl:message>
<wsdl:message name=")" + SDC::OP_GET_MDIB_RESPONSE+ R"(">
	<wsdl:part element="msg:)" + SDC::OP_GET_MDIB_RESPONSE + R"(" name="parameters"/>
</wsdl:message>
<wsdl:message name=")" + SDC::OP_GET_MDDESCRIPTION_REQUEST + R"(">
	<wsdl:part element="msg:)" + SDC::OP_GET_MDDESCRIPTION_REQUEST + R"(" name="parameters"/>
</wsdl:message>
<wsdl:message name=")" + SDC::OP_GET_MDDESCRIPTION_RESPONSE + R"(">
	<wsdl:part element="msg:)" + SDC::OP_GET_MDDESCRIPTION_RESPONSE + R"(" name="parameters"/>
</wsdl:message>
<wsdl:message name=")" + SDC::OP_GET_MDSTATE_REQUEST + R"(">
	<wsdl:part element="msg:)" + SDC::OP_GET_MDSTATE_REQUEST + R"(" name="parameters"/>
</wsdl:message>
<wsdl:message name=")" + SDC::OP_GET_MDSTATE_RESPONSE + R"(">
	<wsdl:part element="msg:)" + SDC::OP_GET_MDSTATE_RESPONSE + R"(" name="parameters"/>
</wsdl:message>
<wsdl:portType name=")" + SDC::QNAME_GETSERVICE_PORTTYPE + R"(" dpws:DiscoveryType="pm:ServiceProvider">
	<wsdl:operation name=")" + SDC::OP_GET_MDIB_REQUEST + R"(">
		<wsdl:input message="tns:)" + SDC::OP_GET_MDIB_REQUEST + R"(" wsa:Action=")" + SDC::ACT_GET_MDIB_REQUEST + R"("/>
		<wsdl:output message="tns:)" + SDC::OP_GET_MDIB_RESPONSE + R"(" wsa:Action=")" + SDC::ACT_GET_MDIB_RESPONSE + R"("/>
	</wsdl:operation>
	<wsdl:operation name=")" + SDC::OP_GET_MDDESCRIPTION_REQUEST + R"(">
		<wsdl:input message="tns:)" + SDC::OP_GET_MDDESCRIPTION_REQUEST + R"(" wsa:Action=")" + SDC::ACT_GET_MDDESCRIPTION_REQUEST + R"("/>
		<wsdl:output message="tns:)" + SDC::OP_GET_MDDESCRIPTION_RESPONSE + R"(" wsa:Action=")" + SDC::ACT_GET_MDDESCRIPTION_RESPONSE + R"("/>
	</wsdl:operation>
	<wsdl:operation name=")" + SDC::OP_GET_MDSTATE_REQUEST + R"(">
		<wsdl:input message="tns:)" + SDC::OP_GET_MDSTATE_REQUEST + R"(" wsa:Action=")" + SDC::ACT_GET_MDSTATE_REQUEST + R"("/>
		<wsdl:output message="tns:)" + SDC::OP_GET_MDSTATE_RESPONSE + R"(" wsa:Action=")" + SDC::ACT_GET_MDSTATE_RESPONSE + R"("/>
	</wsdl:operation>
</wsdl:portType>
<wsdl:binding name=")" + SDC::QNAME_GETSERVICE + R"(Binding" type="tns:)" + SDC::QNAME_GETSERVICE_PORTTYPE + R"(">
	<soap12:binding style="document" transport="http://schemas.xmlsoap.org/soap/http"/>
	<wsdl:operation name=")" + SDC::OP_GET_MDIB_REQUEST + R"(">
		<soap12:operation soapAction=")" + SDC::ACT_GET_MDIB_REQUEST + R"(" style="document"/>
		<wsdl:input><soap12:body use="literal"/></wsdl:input>
		<wsdl:output><soap12:body use="literal"/></wsdl:output>
	</wsdl:operation>
	<wsdl:operation name=")" + SDC::OP_GET_MDDESCRIPTION_REQUEST + R"(">
		<soap12:operation soapAction=")" + SDC::ACT_GET_MDDESCRIPTION_REQUEST + R"(" style="document"/>
		<wsdl:input><soap12:body use="literal"/></wsdl:input>
		<wsdl:output><soap12:body use="literal"/></wsdl:output>
	</wsdl:operation>
	<wsdl:operation name=")" + SDC::OP_GET_MDSTATE_REQUEST + R"(">
		<soap12:operation soapAction=")" + SDC::ACT_GET_MDSTATE_REQUEST + R"(" style="document"/>
		<wsdl:input><soap12:body use="literal"/></wsdl:input>
		<wsdl:output><soap12:body use="literal"/></wsdl:output>
	</wsdl:operation>
	<wsp:Policy>
		<dpws:Profile wsp:Optional="true" />
	</wsp:Policy>
</wsdl:binding>
</wsdl:definitions>)");

}
}

#endif
