#ifndef SCHEMA_DICOMDATAMODEL_H
#define SCHEMA_DICOMDATAMODEL_H

#include "SchemaBICEPSParticipantModel.h"

namespace SCHEMA
{

const std::string SCHEMA_DICOM_DATAMODEL_NAME("DICOMDeviceDescription.xsd");

const std::string SCHEMA_DICOM_DATAMODEL_CONTENT = std::string(R"(<xsd:schema xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:tns="http://dicom-extension-uri/09/08" xmlns:pm="http://standards.ieee.org/downloads/11073/11073-10207-2017/participant" targetNamespace="http://dicom-extension-uri/09/08" elementFormDefault="qualified" attributeFormDefault="unqualified" xml:lang="en">
	<xsd:import namespace="http://standards.ieee.org/downloads/11073/11073-10207-2017/participant" schemaLocation=")" + SCHEMA_BICEPS_PARTICIPANTMODEL_NAME + R"("/>
	<xsd:simpleType name="DicomTransferRole">
		<xsd:annotation>
			<xsd:documentation>Role can be either server (SCP) or client (SCU)</xsd:documentation>
		</xsd:annotation>
		<xsd:restriction base="xsd:string">
			<xsd:enumeration value="Scu">
				<xsd:annotation>
					<xsd:documentation>Client role</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
			<xsd:enumeration value="Scp">
				<xsd:annotation>
					<xsd:documentation>Server role</xsd:documentation>
				</xsd:annotation>
			</xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:complexType name="DicomTransferCapability">
		<xsd:annotation>
			<xsd:documentation> A DICOM transfer capability consists of a SOP class and whether the SOP class is supported as a server (SCP) or client (SCU)</xsd:documentation>
		</xsd:annotation>
		<xsd:sequence>
			<xsd:element name="TransferSyntax" type="xsd:string" maxOccurs="unbounded">
				<xsd:annotation>
					<xsd:documentation>The transfer syntax defines the DICOM encoding used for the transfer of data; this can also include compression of pixel data.</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
		</xsd:sequence>
		<xsd:attribute name="SopClass" type="xsd:string" use="required">
			<xsd:annotation>
				<xsd:documentation>The SOP Class (DICOM service)</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
		<xsd:attribute name="TransferRole" type="tns:DicomTransferRole" use="required">
			<xsd:annotation>
				<xsd:documentation>Role for this service: Client (SCU) or Server (SCP)</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
	</xsd:complexType>
	<xsd:complexType name="DicomNetworkAe">
		<xsd:annotation>
			<xsd:documentation>A Network AE (Application Entity) is a DICOM network communication component that is uniquely known on the DICOM network by its AE Ttile. It refers to a network connection the AE uses for its communication. The AE is marked whether it initiates and/or receives connections (associations). Optionally a free text description is given.</xsd:documentation>
		</xsd:annotation>
		<xsd:sequence>
			<xsd:element name="TransferCapability" type="tns:DicomTransferCapability" maxOccurs="unbounded"/>
			<xsd:choice minOccurs="0" maxOccurs="unbounded">
				<xsd:element name="ApplicationCluster" type="pm:LocalizedText">
					<xsd:annotation>
						<xsd:documentation>Can be used to group DICOM Application Entities into a DICOM Application Clusters</xsd:documentation>
					</xsd:annotation>
				</xsd:element>
				<xsd:element name="SupportedCharacterSet" type="xsd:string">
					<xsd:annotation>
						<xsd:documentation>Character set supported by this Application Entity. All permitted values can be found in part 3 of the DICOM standard (look for "Specific Charcter Set"). Example: Use "ISO_IR 192" for UTF-8.</xsd:documentation>
					</xsd:annotation>
				</xsd:element>
			</xsd:choice>
			<xsd:element name="Description" type="pm:LocalizedText" minOccurs="0" maxOccurs="unbounded">
				<xsd:annotation>
					<xsd:documentation>Free text description of this Application Entity</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
		</xsd:sequence>
		<xsd:attribute name="AeTitle" type="xsd:string" use="required">
			<xsd:annotation>
				<xsd:documentation>The AE Title defines a DICOM networking component uniquely on a network.  Maximally 16 characters (ASCII, only upper case characters and numbers highly recommended)</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
		<xsd:attribute name="NetworkConnectionReference" type="xsd:IDREFS" use="required">
			<xsd:annotation>
				<xsd:documentation>The network connection that this AE uses</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
		<xsd:attribute name="AssociationInitiator" type="xsd:boolean" use="required">
			<xsd:annotation>
				<xsd:documentation>TRUE if  this AE may initiate connection (association) requests , FALSE otherwise</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
		<xsd:attribute name="AssociationAcceptor" type="xsd:boolean" use="required">
			<xsd:annotation>
				<xsd:documentation>TRUE if  this AE may accept connection (association) requests , FALSE otherwise</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
	</xsd:complexType>
	<xsd:complexType name="DicomNetworkConnection">
		<xsd:annotation>
			<xsd:documentation>A DICOM network connection (identified by its ID for reference purposes, especially from the DICOMNetworkAE type), is described by a host name (can be an IP address) and TCP port number.</xsd:documentation>
		</xsd:annotation>
		<xsd:sequence>
			<xsd:element name="TlsCipherSuite" type="xsd:string" minOccurs="0" maxOccurs="unbounded">
				<xsd:annotation>
					<xsd:documentation>TLS Cipher Suites supported by this device. See DICOM standard part 15 for valid values (section on "Secure Transport Connection Profiles").</xsd:documentation>
				</xsd:annotation>
			</xsd:element>
		</xsd:sequence>
		<xsd:attribute name="id" type="xsd:ID" use="required">
			<xsd:annotation>
				<xsd:documentation>Unique ID for this network connections. Referenced by DICOMNetworkAE type in order to bind an AE to a network connection.</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
		<xsd:attribute name="Hostname" type="xsd:string" use="required">
			<xsd:annotation>
				<xsd:documentation>Hostname or IP address</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
		<xsd:attribute name="Port" type="xsd:unsignedShort" use="optional">
			<xsd:annotation>
				<xsd:documentation>TCP-Port</xsd:documentation>
			</xsd:annotation>
		</xsd:attribute>
	</xsd:complexType>
	<xsd:complexType name="DicomDeviceDescriptor">
		<xsd:annotation>
			<xsd:documentation> General description of a DICOM device. Includes basic description of the device which may also be taken over into any DICOM objects created by the device.</xsd:documentation>
		</xsd:annotation>
		<xsd:complexContent>
			<xsd:extension base="pm:AbstractComplexDeviceComponentDescriptor">
				<xsd:sequence>
					<xsd:element name="NetworkAe" type="tns:DicomNetworkAe" maxOccurs="unbounded"/>
					<xsd:element name="NetworkConnection" type="tns:DicomNetworkConnection" maxOccurs="unbounded"/>
					<xsd:choice minOccurs="0" maxOccurs="unbounded">
						<xsd:element name="SoftwareVersion" type="xsd:string"/>
						<xsd:element name="InstitutionName" type="pm:LocalizedText"/>
						<xsd:element name="InstitutionAddress" type="pm:LocalizedText"/>
						<xsd:element name="InstitutionalDepartmentName" type="pm:LocalizedText"/>
						<xsd:element name="PrimaryDeviceType" type="pm:LocalizedText"/>
						<xsd:element name="PublicCertificate" type="xsd:base64Binary"/>
					</xsd:choice>
					<xsd:element name="Description" type="pm:LocalizedText" minOccurs="0" maxOccurs="unbounded">
						<xsd:annotation>
							<xsd:documentation>Free text description of this device</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
					<xsd:element name="StationName" type="pm:LocalizedText" minOccurs="0" maxOccurs="unbounded">
						<xsd:annotation>
							<xsd:documentation>Free text station name, e.g. "High resolution CT 1"</xsd:documentation>
						</xsd:annotation>
					</xsd:element>
				</xsd:sequence>
				<xsd:attribute name="IssuerOfPatientID" type="xsd:string" use="optional">
					<xsd:annotation>
						<xsd:documentation>Issuer of Patient ID as written to the any DICOM objects that are created by this device.</xsd:documentation>
					</xsd:annotation>
				</xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
</xsd:schema>)");

}
#endif
