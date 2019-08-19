#ifndef SCHEMA_EXTENSIONPOINT_H
#define SCHEMA_EXTENSIONPOINT_H

#include <string>

namespace SCHEMA
{
const std::string SCHEMA_EXTENSIONPOINT_NAME("ExtensionPoint.xsd");

const std::string SCHEMA_EXTENSIONPOINT_CONTENT = std::string(R"(<?xml version="1.0"?>
<xsd:schema xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:tns="http://standards.ieee.org/downloads/11073/11073-10207-2017/extension" targetNamespace="http://standards.ieee.org/downloads/11073/11073-10207-2017/extension" elementFormDefault="qualified" attributeFormDefault="unqualified" xml:lang="en">
	<xsd:element name="Extension" type="tns:ExtensionType"/>
	<xsd:complexType name="ExtensionType">
		<xsd:sequence>
			<xsd:any namespace="##other" processContents="lax" minOccurs="0" maxOccurs="unbounded"/>
		</xsd:sequence>
	</xsd:complexType>
	<xsd:attribute name="MustUnderstand" type="xsd:boolean" default="false"></xsd:attribute>
</xsd:schema>
)");

}
#endif

