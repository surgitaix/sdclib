#ifndef SCHEMA_SOAPMESSAGE_H
#define SCHEMA_SOAPMESSAGE_H

#include <string>

namespace SCHEMA
{
const std::string SCHEMA_SOAPMESSAGE_NAME("GenericSoapMessage.xsd");

const std::string SCHEMA_SOAPMESSAGE_CONTENT = std::string(R"(<?xml version="1.0"?>
<xs:schema xmlns:xs="http://www.w3.org/2001/XMLSchema" targetNamespace="http://www.w3.org/2003/05/soap-envelope" elementFormDefault="qualified" attributeFormDefault="unqualified" xml:lang="en">
	<xs:element name="Envelope">
		<xs:complexType>
			<xs:sequence>
				<xs:element name="Header">
					<xs:complexType>
						<xs:sequence maxOccurs="unbounded">
							<xs:any namespace="##any" processContents="strict"/>
						</xs:sequence>
					</xs:complexType>
				</xs:element>
				<xs:element name="Body">
					<xs:complexType>
						<xs:sequence>
							<xs:any namespace="##any" processContents="lax" minOccurs="0"/>
						</xs:sequence>
					</xs:complexType>
				</xs:element>
			</xs:sequence>
		</xs:complexType>
	</xs:element>
</xs:schema>)");

}
#endif
