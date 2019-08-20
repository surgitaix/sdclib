#ifndef SCHEMA_WSEVENTING_H
#define SCHEMA_WSEVENTING_H

#include <string>

namespace SCHEMA
{
const std::string SCHEMA_WSEVENTING_NAME("eventing.xsd");

const std::string SCHEMA_WSEVENTING_CONTENT = std::string(
		R"(<?xml version="1.0"?>
		<xs:schema xmlns:tns="http://schemas.xmlsoap.org/ws/2004/08/eventing" xmlns:wsa="http://www.w3.org/2005/08/addressing" xmlns:xs="http://www.w3.org/2001/XMLSchema" targetNamespace="http://schemas.xmlsoap.org/ws/2004/08/eventing" elementFormDefault="qualified" blockDefault="#all">
		  
		  <xs:import namespace="http://www.w3.org/2005/08/addressing" schemaLocation="ws-addressing.xsd"/>

		  <xs:complexType name="DeliveryType">
		    <xs:sequence>
		      <xs:element ref="tns:NotifyTo"/>
		      <xs:any namespace="##other" processContents="lax" minOccurs="0" maxOccurs="unbounded"/>
		    </xs:sequence>
		    <xs:attribute name="Mode" type="xs:anyURI" use="optional"/>
		    <xs:anyAttribute namespace="##other" processContents="lax"/>
		  </xs:complexType>

		  <xs:element name="NotifyTo" type="wsa:EndpointReferenceType"/>

		  <xs:simpleType name="NonNegativeDurationType">
		    <xs:restriction base="xs:duration">
		      <xs:minInclusive value="P0Y0M0DT0H0M0S"/>
		    </xs:restriction>
		  </xs:simpleType>

		  <xs:simpleType name="ExpirationType">
		      <xs:union memberTypes="xs:dateTime tns:NonNegativeDurationType"/>
		  </xs:simpleType>

		  <xs:simpleType name="ActionList">
		  	<xs:list itemType="xs:anyURI"/>
		  </xs:simpleType>

		  <xs:complexType name="FilterType">
		  	<xs:simpleContent>
		  		<xs:extension base="tns:ActionList">
		  		    <xs:attribute name="Dialect" type="xs:anyURI" use="optional" default="http://docs.oasis-open.org/ws-dd/ns/dpws/2009/01/Action"/>
		    		<xs:anyAttribute namespace="##other" processContents="lax"/>
		    	</xs:extension>
		  	</xs:simpleContent>
		  </xs:complexType>

		  <xs:complexType name="LanguageSpecificStringType">
		    <xs:simpleContent>
		      <xs:extension base="xs:string">
		        <xs:attribute name="lang" type="xs:string"/>
		        <xs:anyAttribute namespace="##other" processContents="lax"/>
		      </xs:extension>
		    </xs:simpleContent>
		  </xs:complexType>

		  
		  <xs:element name="Subscribe">
		    <xs:complexType>
		      <xs:sequence>
		        <xs:eleme)"
		R"(nt name="EndTo" type="wsa:EndpointReferenceType" minOccurs="0"/>
		        <xs:element name="Delivery" type="tns:DeliveryType"/>
		        <xs:element name="Expires" type="tns:ExpirationType" minOccurs="0"/>
		        <xs:element name="Filter" type="tns:FilterType" minOccurs="0"/>
		        <xs:any namespace="##other" processContents="lax" minOccurs="0" maxOccurs="unbounded"/>
		      </xs:sequence>
		      <xs:anyAttribute namespace="##other" processContents="lax"/>
		    </xs:complexType>
		  </xs:element>

		 <xs:element name="Identifier">
		 	<xs:complexType>
		 		<xs:simpleContent>
		 			<xs:extension base="xs:anyURI">
		 				<xs:attribute ref="wsa:IsReferenceParameter" use="optional"/>
		 			</xs:extension>
		 		</xs:simpleContent>
		 	</xs:complexType>
		 </xs:element>
		 
		  
		  <xs:element name="SubscribeResponse">
		    <xs:complexType>
		      <xs:sequence>
			  <xs:element name="SubscriptionManager" type="wsa:EndpointReferenceType"/>
		        <xs:element name="Expires" type="tns:ExpirationType"/>
		        <xs:any namespace="##other" processContents="lax" minOccurs="0" maxOccurs="unbounded"/>
		      </xs:sequence>
		      <xs:anyAttribute namespace="##other" processContents="lax"/>
		    </xs:complexType>
		  </xs:element>

		  
		  <xs:element name="SupportedDialect" type="xs:anyURI"/>

		  
		  <xs:element name="SupportedDeliveryMode" type="xs:anyURI"/>

		  
		  <xs:element name="Renew">
		    <xs:complexType>
		      <xs:sequence>
		        <xs:element name="Expires" type="tns:ExpirationType" minOccurs="0"/>
		        <xs:any namespace="##other" processContents="lax" minOccurs="0" maxOccurs="unbounded"/>
		      </xs:sequence>
		      <xs:anyAttribute namespace="##other" processContents="lax"/>
		    </xs:complexType>
		  </xs:element>

		  
		  <xs:element name="RenewResponse">
		    <xs:complexType>
		      <xs:sequence>
		        <xs:element name="Expires" type="tns:ExpirationType" minOccurs="0"/>
		        <xs:any namespace="##other" processContents="lax" minOccurs="0" maxOccurs="unbounded"/>
		      </xs:sequence>
		      <xs:anyAttribute na)"
		R"(mespace="##other" processContents="lax"/>
		    </xs:complexType>
		  </xs:element>

		  
		  <xs:element name="GetStatus">
		    <xs:complexType>
		      <xs:sequence>
		        <xs:any namespace="##other" processContents="lax" minOccurs="0" maxOccurs="unbounded"/>
		      </xs:sequence>
		      <xs:anyAttribute namespace="##other" processContents="lax"/>
		    </xs:complexType>
		  </xs:element>

		  
		  <xs:element name="GetStatusResponse">
		    <xs:complexType>
		      <xs:sequence>
		        <xs:element name="Expires" type="tns:ExpirationType" minOccurs="0"/>
		        <xs:any namespace="##other" processContents="lax" minOccurs="0" maxOccurs="unbounded"/>
		      </xs:sequence>
		      <xs:anyAttribute namespace="##other" processContents="lax"/>
		    </xs:complexType>
		  </xs:element>

		  <xs:element name="Unsubscribe">
		    <xs:complexType>
		      <xs:sequence>
		        <xs:any namespace="##other" processContents="lax" minOccurs="0" maxOccurs="unbounded"/>
		      </xs:sequence>
		      <xs:anyAttribute namespace="##other" processContents="lax"/>
		    </xs:complexType>
		  </xs:element>

		  
		  <xs:element name="SubscriptionEnd">
		    <xs:complexType>
		      <xs:sequence>
		        <xs:element name="SubscriptionManager" type="wsa:EndpointReferenceType"/>
		        <xs:element name="Status" type="tns:OpenSubscriptionEndCodeType"/>
		        <xs:element name="Reason" type="tns:LanguageSpecificStringType" minOccurs="0" maxOccurs="unbounded"/>
		        <xs:any namespace="##other" processContents="lax" minOccurs="0" maxOccurs="unbounded"/>
		      </xs:sequence>
		      <xs:anyAttribute namespace="##other" processContents="lax"/>
		    </xs:complexType>
		  </xs:element>

		  <xs:simpleType name="SubscriptionEndCodeType">
		    <xs:restriction base="xs:anyURI">
		      <xs:enumeration value="http://schemas.xmlsoap.org/ws/2004/08/eventing/DeliveryFailure"/>
		      <xs:enumeration value="http://schemas.xmlsoap.org/ws/2004/08/eventing/SourceShuttingDown"/>
		      <xs:enumeration value="http://schemas.xmlsoap.org/ws/2004/08/eventing/Sou)"
		R"(rceCancelling"/>
		    </xs:restriction>
		  </xs:simpleType>

		  <xs:simpleType name="OpenSubscriptionEndCodeType">
		    <xs:union memberTypes="tns:SubscriptionEndCodeType xs:anyURI"/>
		  </xs:simpleType>

		  <xs:attribute name="EventSource" type="xs:boolean"/>
		</xs:schema>
		)"
);

}
#endif

