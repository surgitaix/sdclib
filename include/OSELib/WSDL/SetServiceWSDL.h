#ifndef OSELIB_WSDL_SETSERVICEWSDL_H
#define OSELIB_WSDL_SETSERVICEWSDL_H

#include "OSELib/SDC/SDCConstants.h"
#include "OSELib/Schema/SchemaBICEPSMessageModel.h"

namespace OSELib
{
namespace WSDL
{

const std::string setServiceWsdl=std::string(R"(<wsdl:definitions xmlns:wsdl=")" + SDC::NS_WSDL + R"(" xmlns:dpws=")" + SDC::NS_DPWS + R"(" xmlns:soap12="http://schemas.xmlsoap.org/wsdl/soap12/" targetNamespace=")" + SDC::NS_WSDL_TARGET_NAMESPACE + R"(" xmlns:tns=")" + SDC::NS_WSDL_TARGET_NAMESPACE + R"(" xmlns:wsp=")" + SDC::WS_POLICY + R"(" xmlns:wsa=")" + SDC::NS_ADDRESSING + R"(" xmlns:wse=")" + SDC::NS_EVENTING + R"(" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:msg=")" + SDC::NS_MESSAGE_MODEL + R"(" xmlns:pm=")" + SDC::NS_DOMAIN_MODEL + R"(">
<wsdl:types>
	<xs:schema targetNamespace=")" + SDC::NS_MESSAGE_MODEL + R"(" xmlns:xs="http://www.w3.org/2001/XMLSchema">
		<xs:include schemaLocation=")" + SCHEMA::SCHEMA_BICEPS_MESSAGEMODEL_NAME + R"("/>
	</xs:schema>
</wsdl:types>
<wsdl:message name=")" + SDC::OP_SET_VALUE_REQUEST + R"(">
	<wsdl:part element="msg:)" + SDC::OP_SET_VALUE_REQUEST + R"(" name="parameters"/>
</wsdl:message>
<wsdl:message name=")" + SDC::OP_SET_VALUE_RESPONSE + R"(">
	<wsdl:part element="msg:)" + SDC::OP_SET_VALUE_RESPONSE + R"(" name="parameters"/>
</wsdl:message>
<wsdl:message name=")" + SDC::OP_SET_STRING_REQUEST + R"(">
	<wsdl:part element="msg:)" + SDC::OP_SET_STRING_REQUEST + R"(" name="parameters"/>
</wsdl:message>
<wsdl:message name=")" + SDC::OP_SET_STRING_RESPONSE + R"(">
	<wsdl:part element="msg:)" + SDC::OP_SET_STRING_RESPONSE + R"(" name="parameters"/>
</wsdl:message>
<wsdl:message name=")" + SDC::OP_ACTIVATE_REQUEST + R"(">
	<wsdl:part element="msg:)" + SDC::OP_ACTIVATE_REQUEST + R"(" name="parameters"/>
</wsdl:message>
<wsdl:message name=")" + SDC::OP_ACTIVATE_RESPONSE + R"(">
	<wsdl:part element="msg:)" + SDC::OP_ACTIVATE_RESPONSE + R"(" name="parameters"/>
</wsdl:message>
<wsdl:message name=")" + SDC::OP_SET_ALERT_STATE_REQUEST + R"(">
	<wsdl:part element="msg:)" + SDC::OP_SET_ALERT_STATE_REQUEST + R"(" name="parameters"/>
</wsdl:message>
<wsdl:message name=")" + SDC::OP_SET_ALERT_STATE_RESPONSE + R"(">
	<wsdl:part element="msg:)" + SDC::OP_SET_ALERT_STATE_RESPONSE + R"(" name="parameters"/>
</wsdl:message>
<wsdl:message name=")" + SDC::OP_SET_COMPONENT_STATE_REQUEST + R"(">
	<wsdl:part element="msg:)" + SDC::OP_SET_COMPONENT_STATE_REQUEST + R"(" name="parameters"/>
</wsdl:message>
<wsdl:message name=")" + SDC::OP_SET_COMPONENT_STATE_RESPONSE + R"(">
	<wsdl:part element="msg:)" + SDC::OP_SET_COMPONENT_STATE_RESPONSE + R"(" name="parameters"/>
</wsdl:message>
<wsdl:message name=")" + SDC::OP_SET_METRIC_STATE_REQUEST + R"(">
	<wsdl:part element="msg:)" + SDC::OP_SET_METRIC_STATE_REQUEST + R"(" name="parameters"/>
</wsdl:message>
<wsdl:message name=")" + SDC::OP_SET_METRIC_STATE_RESPONSE + R"(">
	<wsdl:part element="msg:)" + SDC::OP_SET_METRIC_STATE_RESPONSE + R"(" name="parameters"/>
</wsdl:message>
<wsdl:message name=")" + SDC::OP_OPERATION_INVOKED_REPORT + R"(">
	<wsdl:part element="msg:)" + SDC::OP_OPERATION_INVOKED_REPORT + R"(" name="parameters"/>
</wsdl:message>
<wsdl:portType name=")" + SDC::QNAME_SETSERVICE_PORTTYPE + R"(" wse:EventSource="true" dpws:DiscoveryType="pm:ServiceProvider">
	<wsdl:operation name=")" + SDC::OP_SET_VALUE_REQUEST + R"(">
		<wsdl:input message="tns:)" + SDC::OP_SET_VALUE_REQUEST + R"(" wsa:Action=")" + SDC::ACT_SET_VALUE_REQUEST + R"("/>
		<wsdl:output message="tns:)" + SDC::OP_SET_VALUE_RESPONSE + R"(" wsa:Action=")" + SDC::ACT_SET_VALUE_RESPONSE + R"("/>
	</wsdl:operation>
	<wsdl:operation name=")" + SDC::OP_SET_STRING_REQUEST + R"(">
		<wsdl:input message="tns:)" + SDC::OP_SET_STRING_REQUEST + R"(" wsa:Action=")" + SDC::ACT_SET_STRING_REQUEST + R"("/>
		<wsdl:output message="tns:)" + SDC::OP_SET_STRING_RESPONSE + R"(" wsa:Action=")" + SDC::ACT_SET_STRING_RESPONSE + R"("/>
	</wsdl:operation>
	<wsdl:operation name=")" + SDC::OP_ACTIVATE_REQUEST + R"(">
		<wsdl:input message="tns:)" + SDC::OP_ACTIVATE_REQUEST + R"(" wsa:Action=")" + SDC::ACT_ACTIVATE_REQUEST + R"("/>
		<wsdl:output message="tns:)" + SDC::OP_ACTIVATE_RESPONSE + R"(" wsa:Action=")" + SDC::ACT_ACTIVATE_RESPONSE + R"("/>
	</wsdl:operation>
	<wsdl:operation name=")" + SDC::OP_SET_ALERT_STATE_REQUEST + R"(">
		<wsdl:input message="tns:)" + SDC::OP_SET_ALERT_STATE_REQUEST + R"(" wsa:Action=")" + SDC::ACT_SET_ALERT_STATE_REQUEST + R"("/>
		<wsdl:output message="tns:)" + SDC::OP_SET_ALERT_STATE_RESPONSE + R"(" wsa:Action=")" + SDC::ACT_SET_ALERT_STATE_RESPONSE + R"("/>
	</wsdl:operation>
	<wsdl:operation name=")" + SDC::OP_SET_COMPONENT_STATE_REQUEST + R"(">
		<wsdl:input message="tns:)" + SDC::OP_SET_COMPONENT_STATE_REQUEST + R"(" wsa:Action=")" + SDC::ACT_SET_COMPONENT_STATE_REQUEST + R"("/>
		<wsdl:output message="tns:)" + SDC::OP_SET_COMPONENT_STATE_RESPONSE + R"(" wsa:Action=")" + SDC::ACT_SET_COMPONENT_STATE_RESPONSE + R"("/>
	</wsdl:operation>
	<wsdl:operation name=")" + SDC::OP_SET_METRIC_STATE_REQUEST + R"(">
		<wsdl:input message="tns:)" + SDC::OP_SET_METRIC_STATE_REQUEST + R"(" wsa:Action=")" + SDC::ACT_SET_METRIC_STATE_REQUEST + R"("/>
		<wsdl:output message="tns:)" + SDC::OP_SET_METRIC_STATE_RESPONSE + R"(" wsa:Action=")" + SDC::ACT_SET_METRIC_STATE_RESPONSE + R"("/>
	</wsdl:operation>
	<wsdl:operation name=")" + SDC::OP_OPERATION_INVOKED_REPORT + R"(">
		<wsdl:output message="tns:)" + SDC::OP_OPERATION_INVOKED_REPORT + R"(" wsa:Action=")" + SDC::ACT_OPERATION_INVOKED_REPORT + R"("/>
	</wsdl:operation>
</wsdl:portType>
<wsdl:binding name=")" + SDC::QNAME_SETSERVICE + R"(Binding" type="tns:)" + SDC::QNAME_SETSERVICE_PORTTYPE + R"(">
	<soap12:binding style="document" transport="http://schemas.xmlsoap.org/soap/http"/>
	<wsdl:operation name=")" + SDC::OP_SET_VALUE_REQUEST + R"(">
		<soap12:operation soapAction=")" + SDC::ACT_SET_VALUE_REQUEST + R"(" style="document"/>
		<wsdl:input><soap12:body use="literal"/></wsdl:input>
		<wsdl:output><soap12:body use="literal"/></wsdl:output>
	</wsdl:operation>
	<wsdl:operation name=")" + SDC::OP_SET_STRING_REQUEST + R"(">
		<soap12:operation soapAction=")" + SDC::ACT_SET_STRING_REQUEST + R"(" style="document"/>
		<wsdl:input><soap12:body use="literal"/></wsdl:input>
		<wsdl:output><soap12:body use="literal"/></wsdl:output>
	</wsdl:operation>
	<wsdl:operation name=")" + SDC::OP_ACTIVATE_REQUEST + R"(">
		<soap12:operation soapAction=")" + SDC::ACT_ACTIVATE_REQUEST + R"(" style="document"/>
		<wsdl:input><soap12:body use="literal"/></wsdl:input>
		<wsdl:output><soap12:body use="literal"/></wsdl:output>
	</wsdl:operation>
	<wsdl:operation name=")" + SDC::OP_SET_ALERT_STATE_REQUEST + R"(">
		<soap12:operation soapAction=")" + SDC::ACT_SET_ALERT_STATE_REQUEST + R"(" style="document"/>
		<wsdl:input><soap12:body use="literal"/></wsdl:input>
		<wsdl:output><soap12:body use="literal"/></wsdl:output>
	</wsdl:operation>
	<wsdl:operation name=")" + SDC::OP_SET_COMPONENT_STATE_REQUEST + R"(">
		<soap12:operation soapAction=")" + SDC::ACT_SET_COMPONENT_STATE_REQUEST + R"(" style="document"/>
		<wsdl:input><soap12:body use="literal"/></wsdl:input>
		<wsdl:output><soap12:body use="literal"/></wsdl:output>
	</wsdl:operation>
	<wsdl:operation name=")" + SDC::OP_SET_METRIC_STATE_REQUEST + R"(">
		<soap12:operation soapAction=")" + SDC::ACT_SET_METRIC_STATE_REQUEST + R"(" style="document"/>
		<wsdl:input><soap12:body use="literal"/></wsdl:input>
		<wsdl:output><soap12:body use="literal"/></wsdl:output>
	</wsdl:operation>
	<wsdl:operation name=")" + SDC::OP_OPERATION_INVOKED_REPORT + R"(">
		<soap12:operation soapAction=")" + SDC::ACT_OPERATION_INVOKED_REPORT + R"(" style="document"/>
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
