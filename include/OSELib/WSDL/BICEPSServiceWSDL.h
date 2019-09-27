#ifndef OSELIB_WSDL_BICEPSSERVICEWSDL_H
#define OSELIB_WSDL_BICEPSSERVICEWSDL_H

#include "OSELib/SDC/SDCConstants.h"
#include "OSELib/Schema/SchemaBICEPSMessageModel.h"

namespace OSELib
{
namespace WSDL
{
const std::string BICEPSServiceWsdl=std::string(R"(<wsdl:definitions xmlns:wsdl=")" + SDC::NS_WSDL + R"(" xmlns:dpws=")" + SDC::NS_DPWS + R"(" xmlns:soap12="http://schemas.xmlsoap.org/wsdl/soap12/" targetNamespace=")" + SDC::NS_WSDL_TARGET_NAMESPACE + R"(" xmlns:tns=")" + SDC::NS_WSDL_TARGET_NAMESPACE + R"(" xmlns:wsp=")" + SDC::WS_POLICY + R"(" xmlns:wsa=")" + SDC::NS_ADDRESSING + R"(" xmlns:wse=")" + SDC::NS_EVENTING + R"(" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:mdpws=")" + SDC::NS_MDPWS + R"(" xmlns:msg=")" + SDC::NS_MESSAGE_MODEL + R"(" xmlns:pm=")" + SDC::NS_DOMAIN_MODEL + R"(">
<wsdl:types>
	<xs:schema targetNamespace=")" + SDC::NS_MESSAGE_MODEL + R"(" xmlns:xs="http://www.w3.org/2001/XMLSchema">
		<xs:include schemaLocation=")" + SCHEMA::SCHEMA_BICEPS_MESSAGEMODEL_NAME + R"("/>
	</xs:schema>
</wsdl:types>
<wsdl:message name=")" + SDC::OP_EPISODIC_ALERT_REPORT + R"(">
	<wsdl:part element="msg:)" + SDC::OP_EPISODIC_ALERT_REPORT + R"(" name="parameters"/>
</wsdl:message>
<wsdl:message name=")" + SDC::OP_PERIODIC_ALERT_REPORT + R"(">
	<wsdl:part element="msg:)" + SDC::OP_PERIODIC_ALERT_REPORT + R"(" name="parameters"/>
</wsdl:message>
<wsdl:message name=")" + SDC::OP_EPISODIC_COMPONENT_REPORT + R"(">
	<wsdl:part element="msg:)" + SDC::OP_EPISODIC_COMPONENT_REPORT + R"(" name="parameters"/>
</wsdl:message>
<wsdl:message name=")" + SDC::OP_PERIODIC_COMPONENT_REPORT + R"(">
	<wsdl:part element="msg:)" + SDC::OP_PERIODIC_COMPONENT_REPORT + R"(" name="parameters"/>
</wsdl:message>
<wsdl:message name=")" + SDC::OP_EPISODIC_METRIC_REPORT + R"(">
	<wsdl:part element="msg:)" + SDC::OP_EPISODIC_METRIC_REPORT + R"(" name="parameters"/>
</wsdl:message>
<wsdl:message name=")" + SDC::OP_PERIODIC_METRIC_REPORT + R"(">
	<wsdl:part element="msg:)" + SDC::OP_PERIODIC_METRIC_REPORT + R"(" name="parameters"/>
</wsdl:message>
<wsdl:message name=")" + SDC::OP_EPISODIC_OPERATIONALSTATE_REPORT + R"(">
	<wsdl:part element="msg:)" + SDC::OP_EPISODIC_OPERATIONALSTATE_REPORT + R"(" name="parameters"/>
</wsdl:message>
<wsdl:message name=")" + SDC::OP_PERIODIC_OPERATIONALSTATE_REPORT + R"(">
	<wsdl:part element="msg:)" + SDC::OP_PERIODIC_OPERATIONALSTATE_REPORT + R"(" name="parameters"/>
</wsdl:message>
<wsdl:message name=")" + SDC::OP_SYSTEMERROR_REPORT + R"(">
	<wsdl:part element="msg:)" + SDC::OP_SYSTEMERROR_REPORT + R"(" name="parameters"/>
</wsdl:message>
<wsdl:portType name=")" + SDC::QNAME_STATEEVENTSERVICE_PORTTYPE + R"(" wse:EventSource="true" dpws:DiscoveryType="pm:ServiceProvider">
	<wsdl:operation name=")" + SDC::OP_EPISODIC_ALERT_REPORT + R"(">
		<wsdl:output message="tns:)" + SDC::OP_EPISODIC_ALERT_REPORT + R"(" wsa:Action=")" + SDC::ACT_EPISODIC_ALERT_REPORT + R"("/>
	</wsdl:operation>
	<wsdl:operation name=")" + SDC::OP_PERIODIC_ALERT_REPORT + R"(">
		<wsdl:output message="tns:)" + SDC::OP_PERIODIC_ALERT_REPORT + R"(" wsa:Action=")" + SDC::ACT_PERIODIC_ALERT_REPORT + R"("/>
	</wsdl:operation>
	<wsdl:operation name=")" + SDC::OP_EPISODIC_COMPONENT_REPORT + R"(">
		<wsdl:output message="tns:)" + SDC::OP_EPISODIC_COMPONENT_REPORT + R"(" wsa:Action=")" + SDC::ACT_EPISODIC_COMPONENT_REPORT + R"("/>
	</wsdl:operation>
	<wsdl:operation name=")" + SDC::OP_PERIODIC_COMPONENT_REPORT + R"(">
		<wsdl:output message="tns:)" + SDC::OP_PERIODIC_COMPONENT_REPORT + R"(" wsa:Action=")" + SDC::ACT_PERIODIC_COMPONENT_REPORT + R"("/>
	</wsdl:operation>
	<wsdl:operation name=")" + SDC::OP_EPISODIC_METRIC_REPORT + R"(">
		<wsdl:output message="tns:)" + SDC::OP_EPISODIC_METRIC_REPORT + R"(" wsa:Action=")" + SDC::ACT_EPISODIC_METRIC_REPORT + R"("/>
	</wsdl:operation>
	<wsdl:operation name=")" + SDC::OP_PERIODIC_METRIC_REPORT + R"(">
		<wsdl:output message="tns:)" + SDC::OP_PERIODIC_METRIC_REPORT + R"(" wsa:Action=")" + SDC::ACT_PERIODIC_METRIC_REPORT + R"("/>
	</wsdl:operation>
	<wsdl:operation name=")" + SDC::OP_EPISODIC_OPERATIONALSTATE_REPORT + R"(">
		<wsdl:output message="tns:)" + SDC::OP_EPISODIC_OPERATIONALSTATE_REPORT + R"(" wsa:Action=")" + SDC::ACT_EPISODIC_OPERATIONALSTATE_REPORT + R"("/>
	</wsdl:operation>
	<wsdl:operation name=")" + SDC::OP_PERIODIC_OPERATIONALSTATE_REPORT + R"(">
		<wsdl:output message="tns:)" + SDC::OP_PERIODIC_OPERATIONALSTATE_REPORT + R"(" wsa:Action=")" + SDC::ACT_PERIODIC_OPERATIONALSTATE_REPORT + R"("/>
	</wsdl:operation>
	<wsdl:operation name=")" + SDC::OP_SYSTEMERROR_REPORT + R"(">
		<wsdl:output message="tns:)" + SDC::OP_SYSTEMERROR_REPORT + R"(" wsa:Action=")" + SDC::ACT_SYSTEMERROR_REPORT + R"("/>
	</wsdl:operation>
</wsdl:portType>
<wsdl:binding name=")" + SDC::QNAME_STATEEVENTSERVICE + R"(Binding" type="tns:)" + SDC::QNAME_STATEEVENTSERVICE_PORTTYPE + R"(">
	<soap12:binding transport="http://schemas.xmlsoap.org/soap/http" style="document"/>
	<wsdl:operation name=")" + SDC::OP_EPISODIC_ALERT_REPORT + R"(">
		<soap12:operation soapAction=")" + SDC::ACT_EPISODIC_ALERT_REPORT + R"("/>
		<wsdl:output><soap12:body use="literal"/></wsdl:output>
	</wsdl:operation>
	<wsdl:operation name=")" + SDC::OP_PERIODIC_ALERT_REPORT + R"(">
		<soap12:operation soapAction=")" + SDC::ACT_PERIODIC_ALERT_REPORT + R"("/>
		<wsdl:output><soap12:body use="literal"/></wsdl:output>
	</wsdl:operation>
	<wsdl:operation name=")" + SDC::OP_EPISODIC_COMPONENT_REPORT + R"(">
		<soap12:operation soapAction=")" + SDC::ACT_EPISODIC_COMPONENT_REPORT + R"("/>
		<wsdl:output><soap12:body use="literal"/></wsdl:output>
	</wsdl:operation>
	<wsdl:operation name=")" + SDC::OP_PERIODIC_COMPONENT_REPORT + R"(">
		<soap12:operation soapAction=")" + SDC::ACT_PERIODIC_COMPONENT_REPORT + R"("/>
		<wsdl:output><soap12:body use="literal"/></wsdl:output>
	</wsdl:operation>
	<wsdl:operation name=")" + SDC::OP_EPISODIC_METRIC_REPORT + R"(">
		<soap12:operation soapAction=")" + SDC::ACT_EPISODIC_METRIC_REPORT + R"("/>
		<wsdl:output><soap12:body use="literal"/></wsdl:output>
	</wsdl:operation>
	<wsdl:operation name=")" + SDC::OP_PERIODIC_METRIC_REPORT + R"(">
		<soap12:operation soapAction=")" + SDC::ACT_PERIODIC_METRIC_REPORT + R"("/>
		<wsdl:output><soap12:body use="literal"/></wsdl:output>
	</wsdl:operation>
	<wsdl:operation name=")" + SDC::OP_EPISODIC_OPERATIONALSTATE_REPORT + R"(">
		<soap12:operation soapAction=")" + SDC::ACT_EPISODIC_OPERATIONALSTATE_REPORT + R"("/>
		<wsdl:output><soap12:body use="literal"/></wsdl:output>
	</wsdl:operation>
	<wsdl:operation name=")" + SDC::OP_PERIODIC_OPERATIONALSTATE_REPORT + R"(">
		<soap12:operation soapAction=")" + SDC::ACT_PERIODIC_OPERATIONALSTATE_REPORT + R"("/>
		<wsdl:output><soap12:body use="literal"/></wsdl:output>
	</wsdl:operation>
	<wsdl:operation name=")" + SDC::OP_SYSTEMERROR_REPORT + R"(">
		<soap12:operation soapAction=")" + SDC::ACT_SYSTEMERROR_REPORT + R"("/>
		<wsdl:output><soap12:body use="literal"/></wsdl:output>
	</wsdl:operation>
	<wsp:Policy>
		<dpws:Profile wsp:Optional="true" />
	</wsp:Policy>
</wsdl:binding>
<wsdl:message name=")" + SDC::OP_GET_CONTEXTSTATES_REQUEST + R"(">
	<wsdl:part element="msg:)" + SDC::OP_GET_CONTEXTSTATES_REQUEST + R"(" name="parameters"/>
</wsdl:message>
<wsdl:message name=")" + SDC::OP_GET_CONTEXTSTATES_RESPONSE + R"(">
	<wsdl:part element="msg:)" + SDC::OP_GET_CONTEXTSTATES_RESPONSE + R"(" name="parameters"/>
</wsdl:message>
<wsdl:message name=")" + SDC::OP_SET_CONTEXTSTATE_REQUEST + R"(">
	<wsdl:part element="msg:)" + SDC::OP_SET_CONTEXTSTATE_REQUEST + R"(" name="parameters"/>
</wsdl:message>
<wsdl:message name=")" + SDC::OP_SET_CONTEXTSTATE_RESPONSE + R"(">
	<wsdl:part element="msg:)" + SDC::OP_SET_CONTEXTSTATE_RESPONSE + R"(" name="parameters"/>
</wsdl:message>
<wsdl:message name=")" + SDC::OP_EPISODIC_CONTEXT_REPORT + R"(">
	<wsdl:part element="msg:)" + SDC::OP_EPISODIC_CONTEXT_REPORT + R"(" name="parameters"/>
</wsdl:message>
<wsdl:message name=")" + SDC::OP_PERIODIC_CONTEXT_REPORT + R"(">
	<wsdl:part element="msg:)" + SDC::OP_PERIODIC_CONTEXT_REPORT + R"(" name="parameters"/>
</wsdl:message>
<wsdl:portType name=")" + SDC::QNAME_CONTEXTSERVICE_PORTTYPE + R"(" wse:EventSource="true" dpws:DiscoveryType="pm:ServiceProvider">
	<wsdl:operation name=")" + SDC::OP_GET_CONTEXTSTATES_REQUEST + R"(">
		<wsdl:input message="tns:)" + SDC::OP_GET_CONTEXTSTATES_REQUEST + R"(" wsa:Action=")" + SDC::ACT_GET_CONTEXTSTATES_REQUEST + R"("/>
		<wsdl:output message="tns:)" + SDC::OP_GET_CONTEXTSTATES_RESPONSE + R"(" wsa:Action=")" + SDC::ACT_GET_CONTEXTSTATES_RESPONSE + R"("/>
	</wsdl:operation>
	<wsdl:operation name=")" + SDC::OP_SET_CONTEXTSTATE_REQUEST + R"(">
		<wsdl:input message="tns:)" + SDC::OP_SET_CONTEXTSTATE_REQUEST + R"(" wsa:Action=")" + SDC::ACT_SET_CONTEXTSTATE_REQUEST + R"("/>
		<wsdl:output message="tns:)" + SDC::OP_SET_CONTEXTSTATE_RESPONSE + R"("  wsa:Action=")" + SDC::ACT_SET_CONTEXTSTATE_RESPONSE + R"("/>
	</wsdl:operation>
	<wsdl:operation name=")" + SDC::OP_EPISODIC_CONTEXT_REPORT + R"(">
		<wsdl:output message="tns:)" + SDC::OP_EPISODIC_CONTEXT_REPORT + R"(" wsa:Action=")" + SDC::ACT_EPISODIC_CONTEXT_REPORT + R"("/>
	</wsdl:operation>
	<wsdl:operation name=")" + SDC::OP_PERIODIC_CONTEXT_REPORT + R"(">
		<wsdl:output message="tns:)" + SDC::OP_PERIODIC_CONTEXT_REPORT + R"(" wsa:Action=")" + SDC::ACT_PERIODIC_CONTEXT_REPORT + R"("/>
	</wsdl:operation>
</wsdl:portType>
<wsdl:binding name=")" + SDC::QNAME_CONTEXTSERVICE + R"(Binding" type="tns:)" + SDC::QNAME_CONTEXTSERVICE_PORTTYPE + R"(">
	<soap12:binding transport="http://schemas.xmlsoap.org/soap/http" style="document" />
	<wsdl:operation name=")" + SDC::OP_GET_CONTEXTSTATES_REQUEST + R"(">
		<soap12:operation soapAction=")" + SDC::ACT_GET_CONTEXTSTATES_REQUEST + R"("/>
		<wsdl:input><soap12:body use="literal"/></wsdl:input>
		<wsdl:output><soap12:body use="literal"/></wsdl:output>
	</wsdl:operation>
	<wsdl:operation name=")" + SDC::OP_SET_CONTEXTSTATE_REQUEST + R"(">
		<soap12:operation soapAction=")" + SDC::ACT_SET_CONTEXTSTATE_REQUEST + R"("/>
		<wsdl:input><soap12:body use="literal"/></wsdl:input>
		<wsdl:output><soap12:body use="literal"/></wsdl:output>
	</wsdl:operation>
	<wsdl:operation name=")" + SDC::OP_EPISODIC_CONTEXT_REPORT + R"(">
		<soap12:operation soapAction=")" + SDC::ACT_EPISODIC_CONTEXT_REPORT + R"("/>
		<wsdl:output><soap12:body use="literal"/></wsdl:output>
	</wsdl:operation>
	<wsdl:operation name=")" + SDC::OP_PERIODIC_CONTEXT_REPORT + R"(">
		<soap12:operation soapAction=")" + SDC::ACT_PERIODIC_CONTEXT_REPORT + R"("/>
		<wsdl:output><soap12:body use="literal"/></wsdl:output>
	</wsdl:operation>
	<wsp:Policy>
		<dpws:Profile wsp:Optional="true" />
	</wsp:Policy>
</wsdl:binding>
<wsdl:message name=")" + SDC::NOTIFICATION + R"(">
	<wsdl:part element="msg:)" + SDC::NOTIFICATION + R"(" name="parameters"/>
</wsdl:message>
<wsdl:portType name=")" + SDC::QNAME_WAVEFORMSERVICE_PORTTYPE + R"(" wse:EventSource="true" dpws:DiscoveryType="pm:ServiceProvider">
	<wsdl:operation name=")" + SDC::OP_WAVEFORM_STREAM_REPORT + R"(">
		<wsdl:output message="tns:)" + SDC::NOTIFICATION + R"(" wsa:Action=")" + SDC::ACT_WAVEFORM_STREAM_REPORT + R"("/>
	</wsdl:operation>
</wsdl:portType>
<wsdl:binding name=")" + SDC::QNAME_WAVEFORMSERVICE + R"(Binding" type="tns:)" + SDC::QNAME_WAVEFORMSERVICE_PORTTYPE + R"(">
	<soap12:binding transport="http://schemas.xmlsoap.org/soap/http" style="document" />
	<wsdl:operation name=")" + SDC::OP_WAVEFORM_STREAM_REPORT + R"(">
		<soap12:operation soapAction=")" + SDC::ACT_WAVEFORM_STREAM_REPORT + R"("/>
		<wsdl:output><soap12:body use="literal"/></wsdl:output>
	</wsdl:operation>
	<wsp:Policy>
		<mdpws:StreamSource>
			<mdpws:StreamDescriptions targetNamespace=")" + SDC::NS_SERVICE_DESCRIPTION + R"(/)" + SDC::QNAME_WAVEFORMSERVICE + R"(">
				<mdpws:StreamType actionURI=")" + SDC::NS_SERVICE_DESCRIPTION + R"(/)" + SDC::QNAME_WAVEFORMSERVICE + R"(/)" + SDC::OP_WAVEFORM_STREAM_REPORT + R"(" element="msg:)" + SDC::OP_WAVEFORM_STREAM_REPORT + R"(" id=")" + SDC::OP_WAVEFORM_STREAM_REPORT + R"(" streamType="http://docs.oasis-open.org/ws-dd/soapoverudp/1.1/os/wsdd-soapoverudp-1.1-spec-os.html"/>
			</mdpws:StreamDescriptions>
		</mdpws:StreamSource>
		<dpws:Profile wsp:Optional="true"/>
	</wsp:Policy>
</wsdl:binding>
</wsdl:definitions>)");


}
}

#endif
