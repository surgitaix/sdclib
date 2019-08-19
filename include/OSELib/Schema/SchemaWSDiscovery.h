#ifndef SCHEMA_WSDISCOVERY_H
#define SCHEMA_WSDISCOVERY_H

#include <string.h>

namespace SCHEMA
{
const static std::string SCHEMA_WSDISCOVERY_NAME("wsdd-discovery-1.1-schema-os.xsd");

const static std::string SCHEMA_WSDISCOVERY_CONTENT = std::string(R"(<?xml version="1.0"?>
<xs:schema xmlns:tns="http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01" xmlns:wsa="http://www.w3.org/2005/08/addressing" xmlns:xs="http://www.w3.org/2001/XMLSchema" targetNamespace="http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01" elementFormDefault="qualified" blockDefault="#all">
  <xs:import namespace="http://www.w3.org/2005/08/addressing" schemaLocation="ws-addressing.xsd"/>
  <xs:element name="Hello" type="tns:HelloType"/>
  <xs:complexType name="HelloType">
    <xs:sequence>
      <xs:element ref="wsa:EndpointReference"/>
      <xs:element ref="tns:Types" minOccurs="0"/>
      <xs:element ref="tns:Scopes" minOccurs="0"/>
      <xs:element ref="tns:XAddrs" minOccurs="0"/>
      <xs:element ref="tns:MetadataVersion"/>
      <xs:any namespace="##other" processContents="lax" minOccurs="0" maxOccurs="unbounded"/>
    </xs:sequence>
    <xs:anyAttribute namespace="##other" processContents="lax"/>
  </xs:complexType>
  <xs:element name="Bye" type="tns:ByeType"/>
  <xs:complexType name="ByeType">
    <xs:sequence>
      <xs:element ref="wsa:EndpointReference"/>
      <xs:element ref="tns:Types" minOccurs="0"/>
      <xs:element ref="tns:Scopes" minOccurs="0"/>
      <xs:element ref="tns:XAddrs" minOccurs="0"/>
      <xs:element ref="tns:MetadataVersion" minOccurs="0"/>
      <xs:any namespace="##other" processContents="lax" minOccurs="0" maxOccurs="unbounded"/>
    </xs:sequence>
    <xs:anyAttribute namespace="##other" processContents="lax"/>
  </xs:complexType>
  <xs:element name="Probe" type="tns:ProbeType"/>
  <xs:complexType name="ProbeType">
    <xs:sequence>
      <xs:element ref="tns:Types" minOccurs="0"/>
      <xs:element ref="tns:Scopes" minOccurs="0"/>
      <xs:any namespace="##other" processContents="lax" minOccurs="0" maxOccurs="unbounded"/>
    </xs:sequence>
    <xs:anyAttribute namespace="##other" processContents="lax"/>
  </xs:complexType>
  <xs:element name="ProbeMatches" type="tns:ProbeMatchesType"/>
  <xs:complexT)"
R"(ype name="ProbeMatchesType">
    <xs:sequence>
      <xs:element name="ProbeMatch" type="tns:ProbeMatchType" minOccurs="0" maxOccurs="unbounded">
      </xs:element>
      <xs:any namespace="##other" processContents="lax" minOccurs="0" maxOccurs="unbounded"/>
    </xs:sequence>
    <xs:anyAttribute namespace="##other" processContents="lax"/>
  </xs:complexType>
  <xs:complexType name="ProbeMatchType">
    <xs:sequence>
      <xs:element ref="wsa:EndpointReference"/>
      <xs:element ref="tns:Types" minOccurs="0"/>
      <xs:element ref="tns:Scopes" minOccurs="0"/>
      <xs:element ref="tns:XAddrs" minOccurs="0"/>
      <xs:element ref="tns:MetadataVersion"/>
      <xs:any namespace="##other" processContents="lax" minOccurs="0" maxOccurs="unbounded"/>
    </xs:sequence>
    <xs:anyAttribute namespace="##other" processContents="lax"/>
  </xs:complexType>
  <xs:element name="Resolve" type="tns:ResolveType"/>
  <xs:complexType name="ResolveType">
    <xs:sequence>
      <xs:element ref="wsa:EndpointReference"/>
      <xs:any namespace="##other" processContents="lax" minOccurs="0" maxOccurs="unbounded"/>
    </xs:sequence>
    <xs:anyAttribute namespace="##other" processContents="lax"/>
  </xs:complexType>
  <xs:element name="ResolveMatches" type="tns:ResolveMatchesType"/>
  <xs:complexType name="ResolveMatchesType">
    <xs:sequence>
      <xs:element name="ResolveMatch" type="tns:ResolveMatchType" minOccurs="0"/>
      <xs:any namespace="##other" processContents="lax" minOccurs="0" maxOccurs="unbounded"/>
    </xs:sequence>
    <xs:anyAttribute namespace="##other" processContents="lax"/>
  </xs:complexType>
  <xs:complexType name="ResolveMatchType">
    <xs:sequence>
      <xs:element ref="wsa:EndpointReference"/>
      <xs:element ref="tns:Types" minOccurs="0"/>
      <xs:element ref="tns:Scopes" minOccurs="0"/>
      <xs:element ref="tns:XAddrs" minOccurs="0"/>
      <xs:element ref="tns:MetadataVersion"/>
      <xs:any namespace="##other" processContents="lax" min)"
R"(Occurs="0" maxOccurs="unbounded"/>
    </xs:sequence>
    <xs:anyAttribute namespace="##other" processContents="lax"/>
  </xs:complexType>
  <xs:element name="Types" type="tns:QNameListType"/>
  <xs:simpleType name="QNameListType">
    <xs:list itemType="xs:QName"/>
  </xs:simpleType>
  <xs:element name="Scopes" type="tns:ScopesType"/>
  <xs:complexType name="ScopesType">
    <xs:simpleContent>
      <xs:extension base="tns:UriListType">
        <xs:attribute name="MatchBy" type="xs:anyURI"/>
        <xs:anyAttribute namespace="##other" processContents="lax"/>
      </xs:extension>
    </xs:simpleContent>
  </xs:complexType>
  <xs:element name="XAddrs" type="tns:UriListType"/>
  <xs:simpleType name="UriListType">
    <xs:list itemType="xs:anyURI"/>
  </xs:simpleType>
  <xs:element name="MetadataVersion" type="xs:unsignedInt"/>
  <xs:simpleType name="FaultCodeType">
	<xs:restriction base="xs:QName">
	  <xs:enumeration value="tns:MatchingRuleNotSupported"/>
	</xs:restriction>
  </xs:simpleType>
  <xs:simpleType name="FaultCodeOpenType">
    <xs:union memberTypes="tns:FaultCodeType xs:QName"/>
  </xs:simpleType>
  <xs:element name="SupportedMatchingRules" type="tns:UriListType"/>
  <xs:attribute name="Id" type="xs:ID"/>
  <xs:element name="Security" type="tns:SecurityType"/>
  <xs:complexType name="SecurityType">
    <xs:sequence>
      <xs:element ref="tns:Sig" minOccurs="0"/>
    </xs:sequence>
    <xs:anyAttribute namespace="##other" processContents="lax"/>
  </xs:complexType>
  <xs:element name="Sig" type="tns:SigType"/>
  <xs:complexType name="SigType">
    <xs:sequence>
      <xs:any namespace="##other" processContents="lax" minOccurs="0" maxOccurs="unbounded"/>
    </xs:sequence>
    <xs:attribute name="Scheme" type="xs:anyURI" use="required"/>
    <xs:attribute name="KeyId" type="xs:base64Binary"/>
    <xs:attribute name="Refs" type="xs:IDREFS" use="required"/>
    <xs:attribute name="Sig" type="xs:base64Binary" use="required"/>
    <xs:anyAttribute namespace=")"
R"(##other" processContents="lax"/>
  </xs:complexType>
  <xs:element name="AppSequence" type="tns:AppSequenceType"/>
  <xs:complexType name="AppSequenceType">
    <xs:complexContent>
      <xs:restriction base="xs:anyType">
        <xs:attribute name="InstanceId" type="xs:unsignedInt" use="required"/>
        <xs:attribute name="SequenceId" type="xs:anyURI"/>
        <xs:attribute name="MessageNumber" type="xs:unsignedInt" use="required"/>
        <xs:anyAttribute namespace="##other" processContents="lax"/>
      </xs:restriction>
    </xs:complexContent>
  </xs:complexType>
</xs:schema>
)");

}
#endif
