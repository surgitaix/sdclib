#ifndef SCHEMA_DICOMDATAMODEL_H
#define SCHEMA_DICOMDATAMODEL_H

#include "SchemaBICEPSParticipantModel.h"

namespace SCHEMA
{

const static std::string SCHEMA_DICOM_DATAMODEL_NAME("DICOMDeviceDescription.xsd");

const static std::string SCHEMA_DICOM_DATAMODEL_CONTENT = std::string(R"(<?xml version="1.0"?>
<xsd:schema xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:tns="http://dicom-extension-uri/09/08" xmlns:pm="http://standards.ieee.org/downloads/11073/11073-10207-2017/participant" targetNamespace="http://dicom-extension-uri/09/08" elementFormDefault="qualified" attributeFormDefault="unqualified" xml:lang="en">
	<xsd:import namespace="http://standards.ieee.org/downloads/11073/11073-10207-2017/participant" schemaLocation="BICEPS_ParticipantModel.xsd"/>
	<xsd:simpleType name="DicomTransferRole">
		<xsd:restriction base="xsd:string">
			<xsd:enumeration value="Scu"/>
			<xsd:enumeration value="Scp"/>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:complexType name="DicomTransferCapability">
		<xsd:sequence>
			<xsd:element name="TransferSyntax" type="xsd:string" maxOccurs="unbounded"/>
		</xsd:sequence>
		<xsd:attribute name="SopClass" type="xsd:string" use="required"/>
		<xsd:attribute name="TransferRole" type="tns:DicomTransferRole" use="required"/>
	</xsd:complexType>
	<xsd:complexType name="DicomNetworkAe">
		<xsd:sequence>
			<xsd:element name="TransferCapability" type="tns:DicomTransferCapability" maxOccurs="unbounded"/>
			<xsd:choice minOccurs="0" maxOccurs="unbounded">
				<xsd:element name="ApplicationCluster" type="pm:LocalizedText"/>
				<xsd:element name="SupportedCharacterSet" type="xsd:string"/>
			</xsd:choice>
			<xsd:element name="Description" type="pm:LocalizedText" minOccurs="0" maxOccurs="unbounded"/>
		</xsd:sequence>
		<xsd:attribute name="AeTitle" type="xsd:string" use="required"/>
		<xsd:attribute name="NetworkConnectionReference" type="xsd:IDREFS" use="required"/>
		<xsd:attribute name="AssociationInitiator" type="xsd:boolean" use="required"/>
		<xsd:attribute name="AssociationAcceptor" type="xsd:boolean" use="required"/>
	</xsd:complexType>
	<xsd:complexType name="DicomNetworkConnection">
		<xsd:sequence>
			<xsd:element name="TlsCipherSuite" type="xsd:string" minOccurs="0" maxOccurs="unbounded"/>
		</xsd:sequence>
		<x)"
R"(sd:attribute name="id" type="xsd:ID" use="required"/>
		<xsd:attribute name="Hostname" type="xsd:string" use="required"/>
		<xsd:attribute name="Port" type="xsd:unsignedShort" use="optional"/>
	</xsd:complexType>
	<xsd:complexType name="DicomDeviceDescriptor">
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
					<xsd:element name="Description" type="pm:LocalizedText" minOccurs="0" maxOccurs="unbounded"/>
					<xsd:element name="StationName" type="pm:LocalizedText" minOccurs="0" maxOccurs="unbounded"/>
				</xsd:sequence>
				<xsd:attribute name="IssuerOfPatientID" type="xsd:string" use="optional"/>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
</xsd:schema>
)");

}
#endif
