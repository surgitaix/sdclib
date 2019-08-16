#ifndef SCHEMA_PARTICIPANTMODEL_H
#define SCHEMA_PARTICIPANTMODEL_H

#include <string>

namespace SCHEMA
{
const std::string SCHEMA_BICEPS_PARTICIPANTMODEL_NAME("BICEPS_ParticipantModel.xsd");

const std::string SCHEMA_BICEPS_PARTICIPANTMODEL_CONTENT = std::string(
R"(<?xml version="1.0"?>
<xsd:schema xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:ext="http://standards.ieee.org/downloads/11073/11073-10207-2017/extension" xmlns:pm="http://standards.ieee.org/downloads/11073/11073-10207-2017/participant" targetNamespace="http://standards.ieee.org/downloads/11073/11073-10207-2017/participant" elementFormDefault="qualified" attributeFormDefault="unqualified" xml:lang="en">
	<xsd:import namespace="http://standards.ieee.org/downloads/11073/11073-10207-2017/extension" schemaLocation="ExtensionPoint.xsd"/>
	<xsd:complexType name="Mdib">
			<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="MdDescription" type="pm:MdDescription" minOccurs="0"/>
			<xsd:element name="MdState" type="pm:MdState" minOccurs="0"/>
		</xsd:sequence>
		<xsd:attributeGroup ref="pm:MdibVersionGroup"/>
	</xsd:complexType>
	<xsd:complexType name="MdDescription">
			<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="Mds" type="pm:MdsDescriptor" minOccurs="0" maxOccurs="unbounded"></xsd:element>
		</xsd:sequence>
		<xsd:attribute name="DescriptionVersion" type="pm:VersionCounter" use="optional"></xsd:attribute>
	</xsd:complexType>
	<xsd:complexType name="MdState">
			<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="State" type="pm:AbstractState" minOccurs="0" maxOccurs="unbounded"></xsd:element>
		</xsd:sequence>
		<xsd:attribute name="StateVersion" type="pm:VersionCounter" use="optional"></xsd:attribute>
	</xsd:complexType>
	<xsd:simpleType name="MeasurementValidity">
			<xsd:restriction base="xsd:string">
			<xsd:enumeration value="Vld"></xsd:enumeration>
			<xsd:enumeration value="Vldated"></xsd:enumeration>
			<xsd:enumeration value="Ong"></xsd:enumeration>
			<xsd:enumeration value="Qst"></xsd:enumeration>
			<xsd:enumeration value="Calib"></xsd:enumeration>
			<xsd:enumeration value="Inv"></xsd:enumeration>
			<xsd:enumeration value="Oflw"></xsd:)"
R"(enumeration>
			<xsd:enumeration value="Uflw"></xsd:enumeration>
			<xsd:enumeration value="NA"></xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:simpleType name="Timestamp">
			<xsd:restriction base="xsd:unsignedLong"/>
	</xsd:simpleType>
	<xsd:simpleType name="VersionCounter">
			<xsd:restriction base="xsd:unsignedLong"/>
	</xsd:simpleType>
	<xsd:simpleType name="ReferencedVersion">
			<xsd:restriction base="pm:VersionCounter"/>
	</xsd:simpleType>
	<xsd:attributeGroup name="MdibVersionGroup">
			<xsd:attribute name="MdibVersion" type="pm:VersionCounter" use="optional"></xsd:attribute>
		<xsd:attribute name="SequenceId" type="xsd:anyURI" use="required"></xsd:attribute>
		<xsd:attribute name="InstanceId" type="xsd:unsignedLong"></xsd:attribute>
	</xsd:attributeGroup>
	<xsd:simpleType name="CodeIdentifier">
			<xsd:restriction base="xsd:string">
			<xsd:minLength value="1"/>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:simpleType name="SymbolicCodeName">
			<xsd:restriction base="xsd:string">
			<xsd:minLength value="1"/>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:simpleType name="LocalizedTextRef">
			<xsd:restriction base="xsd:string">
			<xsd:minLength value="1"/>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:simpleType name="LocalizedTextContent">
			<xsd:restriction base="xsd:string">
			<xsd:minLength value="0"/>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:simpleType name="LocalizedTextWidth">
			<xsd:restriction base="xsd:string">
			<xsd:enumeration value="xs"></xsd:enumeration>
			<xsd:enumeration value="s"></xsd:enumeration>
			<xsd:enumeration value="m"></xsd:enumeration>
			<xsd:enumeration value="l"></xsd:enumeration>
			<xsd:enumeration value="xl"></xsd:enumeration>
			<xsd:enumeration value="xxl"></xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:complexType name="LocalizedText">
			<xsd:simpleContent>
			<xsd:extension base="pm:LocalizedTextContent">
				<xsd:attribute name="Ref" type="pm:LocalizedTextRef"></xsd:attr)"
R"(ibute>
				<xsd:attribute name="Lang" type="xsd:language"></xsd:attribute>
				<xsd:attribute name="Version" type="pm:ReferencedVersion"></xsd:attribute>
				<xsd:attribute name="TextWidth" type="pm:LocalizedTextWidth"></xsd:attribute>
			</xsd:extension>
		</xsd:simpleContent>
	</xsd:complexType>
	<xsd:complexType name="CodedValue">
			<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="CodingSystemName" type="pm:LocalizedText" minOccurs="0" maxOccurs="unbounded"></xsd:element>
			<xsd:element name="ConceptDescription" type="pm:LocalizedText" minOccurs="0" maxOccurs="unbounded"></xsd:element>
			<xsd:element name="Translation" minOccurs="0" maxOccurs="unbounded">
				<xsd:complexType>
					<xsd:sequence>
						<xsd:element ref="ext:Extension" minOccurs="0"/>
					</xsd:sequence>
					<xsd:attribute name="Code" type="pm:CodeIdentifier" use="required"></xsd:attribute>
					<xsd:attribute name="CodingSystem" type="xsd:anyURI"></xsd:attribute>
					<xsd:attribute name="CodingSystemVersion" type="xsd:string"></xsd:attribute>
				</xsd:complexType>
			</xsd:element>
		</xsd:sequence>
		<xsd:attribute name="Code" type="pm:CodeIdentifier" use="required"></xsd:attribute>
		<xsd:attribute name="CodingSystem" type="xsd:anyURI"></xsd:attribute>
		<xsd:attribute name="CodingSystemVersion" type="xsd:string"></xsd:attribute>
		<xsd:attribute name="SymbolicCodeName" type="pm:SymbolicCodeName"></xsd:attribute>
	</xsd:complexType>
	<xsd:complexType name="InstanceIdentifier">
		<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="Type" type="pm:CodedValue" minOccurs="0"></xsd:element>
			<xsd:element name="IdentifierName" type="pm:LocalizedText" minOccurs="0" maxOccurs="unbounded"></xsd:element>
		</xsd:sequence>
		<xsd:attribute name="Root">
			<xsd:simpleType>
				<xsd:restriction base="xsd:anyURI">
					<xsd:minLength value="1"/>
				</xsd:restriction>
			</xsd:simpleType>
		</xsd:attribute>
		<xsd:attr)"
R"(ibute name="Extension" use="optional">
			<xsd:simpleType>
				<xsd:restriction base="xsd:string">
					<xsd:minLength value="1"/>
				</xsd:restriction>
			</xsd:simpleType>
		</xsd:attribute>
	</xsd:complexType>
	<xsd:complexType name="Range">
		<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
		</xsd:sequence>
		<xsd:attribute name="Lower" type="xsd:decimal" use="optional"></xsd:attribute>
		<xsd:attribute name="Upper" type="xsd:decimal" use="optional"></xsd:attribute>
		<xsd:attribute name="StepWidth" type="xsd:decimal" use="optional"></xsd:attribute>
		<xsd:attribute name="RelativeAccuracy" type="xsd:decimal" use="optional"></xsd:attribute>
		<xsd:attribute name="AbsoluteAccuracy" type="xsd:decimal" use="optional"></xsd:attribute>
	</xsd:complexType>
	<xsd:complexType name="Measurement">
			<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="MeasurementUnit" type="pm:CodedValue"></xsd:element>
		</xsd:sequence>
		<xsd:attribute name="MeasuredValue" type="xsd:decimal" use="required"></xsd:attribute>
	</xsd:complexType>
	<xsd:simpleType name="SafetyClassification">
			<xsd:restriction base="xsd:string">
			<xsd:enumeration value="Inf"></xsd:enumeration>
			<xsd:enumeration value="MedA"></xsd:enumeration>
			<xsd:enumeration value="MedB"></xsd:enumeration>
			<xsd:enumeration value="MedC"></xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:simpleType name="ComponentActivation">
			<xsd:restriction base="xsd:string">
			<xsd:enumeration value="On"></xsd:enumeration>
			<xsd:enumeration value="NotRdy"></xsd:enumeration>
			<xsd:enumeration value="StndBy"></xsd:enumeration>
			<xsd:enumeration value="Off"></xsd:enumeration>
			<xsd:enumeration value="Shtdn"></xsd:enumeration>
			<xsd:enumeration value="Fail"></xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:complexType name="ApprovedJurisdictions">
			<xsd:sequence>
			<xsd:element name="ApprovedJurisdi)"
R"(ction" type="pm:InstanceIdentifier" minOccurs="0" maxOccurs="unbounded"></xsd:element>
		</xsd:sequence>
	</xsd:complexType>
	<xsd:complexType name="OperatingJurisdiction">
			<xsd:complexContent>
			<xsd:extension base="pm:InstanceIdentifier"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:simpleType name="Handle">
			<xsd:restriction base="xsd:string">
			<xsd:minLength value="1"/>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:simpleType name="HandleRef">
			<xsd:restriction base="xsd:string">
			<xsd:minLength value="1"/>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:complexType name="PhysicalConnectorInfo">
			<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="Label" type="pm:LocalizedText" minOccurs="0" maxOccurs="unbounded"></xsd:element>
		</xsd:sequence>
		<xsd:attribute name="Number" type="xsd:int">
				</xsd:attribute>
	</xsd:complexType>
	<xsd:complexType name="AbstractDescriptor">
			<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="Type" type="pm:CodedValue" minOccurs="0"></xsd:element>
		</xsd:sequence>
		<xsd:attribute name="Handle" type="pm:Handle" use="required"></xsd:attribute>
		<xsd:attribute name="DescriptorVersion" type="pm:VersionCounter" use="optional"></xsd:attribute>
		<xsd:attribute name="SafetyClassification" type="pm:SafetyClassification" use="optional"></xsd:attribute>
	</xsd:complexType>
	<xsd:complexType name="AbstractState">
			<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
		</xsd:sequence>
		<xsd:attribute name="StateVersion" type="pm:VersionCounter"></xsd:attribute>
		<xsd:attribute name="DescriptorHandle" type="pm:HandleRef" use="required"></xsd:attribute>
		<xsd:attribute name="DescriptorVersion" type="pm:ReferencedVersion"></xsd:attribute>
	</xsd:complexType>
	<xsd:complexType name="AbstractMultiState">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractState">
				<xsd:sequence>
					<xsd:e)"
R"(lement name="Category" type="pm:CodedValue" minOccurs="0"></xsd:element>
				</xsd:sequence>
				<xsd:attribute name="Handle" type="pm:Handle" use="required"></xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="AbstractDeviceComponentDescriptor">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractDescriptor">
				<xsd:sequence>
					<xsd:element name="ProductionSpecification" minOccurs="0" maxOccurs="unbounded">
						<xsd:complexType>
							<xsd:sequence>
								<xsd:element name="SpecType" type="pm:CodedValue"></xsd:element>>
								<xsd:element name="ProductionSpec" type="xsd:string"></xsd:element>>
								<xsd:element name="ComponentId" type="pm:InstanceIdentifier" minOccurs="0"></xsd:element>>
							</xsd:sequence>
						</xsd:complexType>
					</xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="AbstractComplexDeviceComponentDescriptor">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractDeviceComponentDescriptor">
				<xsd:sequence>
					<xsd:element name="AlertSystem" type="pm:AlertSystemDescriptor" minOccurs="0"></xsd:element>
					<xsd:element name="Sco" type="pm:ScoDescriptor" minOccurs="0"></xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:simpleType name="CalibrationState">
			<xsd:restriction base="xsd:string">
			<xsd:enumeration value="No"></xsd:enumeration>
			<xsd:enumeration value="Req"></xsd:enumeration>
			<xsd:enumeration value="Run"></xsd:enumeration>
			<xsd:enumeration value="Cal"></xsd:enumeration>
			<xsd:enumeration value="Oth"></xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:simpleType name="CalibrationType">
			<xsd:restriction base="xsd:string">
			<xsd:enumeration value="Offset"></xsd:enumeration>
			<xsd:enumeration value="Gain"></xsd:enumeration>
			<xsd:enumeration value="TP"></xsd:enumeration>
			<xsd:enumeration value="U)"
R"(nspec"></xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:complexType name="CalibrationInfo">
			<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="CalibrationDocumentation" minOccurs="0" maxOccurs="unbounded">
				<xsd:complexType>
					<xsd:sequence>
						<xsd:element name="Documentation" type="pm:LocalizedText" minOccurs="0" maxOccurs="unbounded"></xsd:element>
						<xsd:element name="CalibrationResult" minOccurs="0" maxOccurs="unbounded">
							<xsd:complexType>
								<xsd:sequence>
									<xsd:element name="Code" type="pm:CodedValue">></xsd:element>
									<xsd:element name="Value" type="pm:Measurement">></xsd:element>
								</xsd:sequence>
							</xsd:complexType></xsd:element>
					</xsd:sequence>
				</xsd:complexType>
			</xsd:element>
		</xsd:sequence>
		<xsd:attribute name="ComponentCalibrationState" type="pm:CalibrationState"></xsd:attribute>
		<xsd:attribute name="Type" type="pm:CalibrationType" use="optional"></xsd:attribute>
		<xsd:attribute name="Time" type="pm:Timestamp" use="optional"></xsd:attribute>
	</xsd:complexType>
	<xsd:complexType name="AbstractDeviceComponentState">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractState">
				<xsd:sequence>
					<xsd:element name="CalibrationInfo" type="pm:CalibrationInfo" minOccurs="0"></xsd:element>
					<xsd:element name="NextCalibration" type="pm:CalibrationInfo" minOccurs="0"></xsd:element>
					<xsd:element name="PhysicalConnector" type="pm:PhysicalConnectorInfo" minOccurs="0"></xsd:element>
				</xsd:sequence>
				<xsd:attribute name="ActivationState" type="pm:ComponentActivation"></xsd:attribute>
				<xsd:attribute name="OperatingHours" type="xsd:unsignedInt"></xsd:attribute>
				<xsd:attribute name="OperatingCycles" type="xsd:int"></xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="AbstractComplexDeviceComponentState">
			<xsd:complexCo)"
R"(ntent>
			<xsd:extension base="pm:AbstractDeviceComponentState"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="MdsDescriptor">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractComplexDeviceComponentDescriptor">
				<xsd:sequence>
					<xsd:element name="MetaData" minOccurs="0">
						<xsd:complexType>
							<xsd:sequence>
								<xsd:element ref="ext:Extension" minOccurs="0"/>
								<xsd:element name="Udi" minOccurs="0" maxOccurs="unbounded">
								<xsd:complexType>
										<xsd:sequence>
											<xsd:element ref="ext:Extension" minOccurs="0"/>
											<xsd:element name="DeviceIdentifier" type="xsd:string">></xsd:element>
											<xsd:element name="HumanReadableForm" type="xsd:string">></xsd:element>
											<xsd:element name="Issuer" type="pm:InstanceIdentifier">></xsd:element>
											<xsd:element name="Jurisdiction" type="pm:InstanceIdentifier" minOccurs="0">></xsd:element>
										</xsd:sequence>
									</xsd:complexType>
								</xsd:element>
								<xsd:element name="LotNumber" type="xsd:string" minOccurs="0"></xsd:element>>
								<xsd:element name="Manufacturer" type="pm:LocalizedText" minOccurs="0" maxOccurs="unbounded"></xsd:element>>
								<xsd:element name="ManufactureDate" type="xsd:dateTime" minOccurs="0"></xsd:element>>
								<xsd:element name="ExpirationDate" type="xsd:dateTime" minOccurs="0"></xsd:element>>
								<xsd:element name="ModelName" type="pm:LocalizedText" minOccurs="0" maxOccurs="unbounded"></xsd:element>>
								<xsd:element name="ModelNumber" type="xsd:string" minOccurs="0"></xsd:element>>
								<xsd:element name="SerialNumber" type="xsd:string" minOccurs="0" maxOccurs="unbounded"></xsd:element>>
							</xsd:sequence>
						</xsd:complexType>
					</xsd:element>
					<xsd:element name="SystemContext" type="pm:SystemContextDescriptor" minOccurs="0"></xsd:element>
					<xsd:element name="Clock" type="pm:ClockDescriptor" minOccurs="0"></xsd:element>
				)"
R"(	<xsd:element name="Battery" type="pm:BatteryDescriptor" minOccurs="0" maxOccurs="unbounded"></xsd:element>
					<xsd:element name="ApprovedJurisdictions" type="pm:ApprovedJurisdictions" minOccurs="0"></xsd:element>
					<xsd:element name="Vmd" type="pm:VmdDescriptor" minOccurs="0" maxOccurs="unbounded"></xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:simpleType name="MdsOperatingMode">
			<xsd:restriction base="xsd:string">
			<xsd:enumeration value="Nml"></xsd:enumeration>
			<xsd:enumeration value="Dmo"></xsd:enumeration>
			<xsd:enumeration value="Srv"></xsd:enumeration>
			<xsd:enumeration value="Mtn"></xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:complexType name="MdsState">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractComplexDeviceComponentState">
				<xsd:sequence>
					<xsd:element name="OperatingJurisdiction" type="pm:OperatingJurisdiction" minOccurs="0"></xsd:element>
				</xsd:sequence>
				<xsd:attribute name="Lang" type="xsd:language"></xsd:attribute>
				<xsd:attribute name="OperatingMode" type="pm:MdsOperatingMode" use="optional"></xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="VmdDescriptor">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractComplexDeviceComponentDescriptor">
				<xsd:sequence>
					<xsd:element name="ApprovedJurisdictions" type="pm:ApprovedJurisdictions" minOccurs="0"></xsd:element>
					<xsd:element name="Channel" type="pm:ChannelDescriptor" minOccurs="0" maxOccurs="unbounded"></xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="VmdState">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractComplexDeviceComponentState">
				<xsd:sequence>
					<xsd:element name="OperatingJurisdiction" type="pm:OperatingJurisdiction" minOccurs="0"></xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexConten)"
R"(t>
	</xsd:complexType>
	<xsd:complexType name="ChannelDescriptor">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractDeviceComponentDescriptor">
				<xsd:sequence>
					<xsd:element name="Metric" type="pm:AbstractMetricDescriptor" minOccurs="0" maxOccurs="unbounded"></xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="ChannelState">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractDeviceComponentState"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="AbstractAlertDescriptor">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractDescriptor"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="AbstractAlertState">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractState">
				<xsd:attribute name="ActivationState" type="pm:AlertActivation" use="required"></xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
		<xsd:simpleType name="AlertActivation">
			<xsd:restriction base="xsd:string">
			<xsd:enumeration value="On"></xsd:enumeration>
			<xsd:enumeration value="Off"></xsd:enumeration>
			<xsd:enumeration value="Psd"></xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:complexType name="SystemSignalActivation">
		<xsd:attribute name="Manifestation" type="pm:AlertSignalManifestation" use="required"></xsd:attribute>
		<xsd:attribute name="State" type="pm:AlertActivation" use="required"></xsd:attribute>
	</xsd:complexType>
	<xsd:complexType name="AlertSystemDescriptor">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractAlertDescriptor">
				<xsd:sequence>
					<xsd:element name="AlertCondition" type="pm:AlertConditionDescriptor" minOccurs="0" maxOccurs="unbounded"></xsd:element>
					<xsd:element name="AlertSignal" type="pm:AlertSignalDescriptor" minOccurs="0" maxOccurs="unbounded"></xsd:element>
				</xsd:sequence>
				<xsd:attribute name="MaxPhysiologicalParallelAlarms" type)"
R"(="xsd:unsignedInt"></xsd:attribute>
				<xsd:attribute name="MaxTechnicalParallelAlarms" type="xsd:unsignedInt"></xsd:attribute>
				<xsd:attribute name="SelfCheckPeriod" type="xsd:duration"></xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="AlertSystemState">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractAlertState">
				<xsd:sequence>
					<xsd:element name="SystemSignalActivation" type="pm:SystemSignalActivation" minOccurs="0" maxOccurs="unbounded"></xsd:element>
				</xsd:sequence>
				<xsd:attribute name="LastSelfCheck" type="pm:Timestamp"></xsd:attribute>
				<xsd:attribute name="SelfCheckCount" type="xsd:long"></xsd:attribute>
				<xsd:attribute name="PresentPhysiologicalAlarmConditions" type="pm:AlertConditionReference"></xsd:attribute>
				<xsd:attribute name="PresentTechnicalAlarmConditions" type="pm:AlertConditionReference"></xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="CauseInfo">
			<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="RemedyInfo" type="pm:RemedyInfo" minOccurs="0"></xsd:element>
			<xsd:element name="Description" type="pm:LocalizedText" minOccurs="0" maxOccurs="unbounded"></xsd:element>
		</xsd:sequence>
	</xsd:complexType>
	<xsd:complexType name="RemedyInfo">
			<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="Description" type="pm:LocalizedText" minOccurs="0" maxOccurs="unbounded"></xsd:element>
		</xsd:sequence>
	</xsd:complexType>
	<xsd:simpleType name="AlertConditionKind">
			<xsd:restriction base="xsd:string">
			<xsd:enumeration value="Phy"></xsd:enumeration>
			<xsd:enumeration value="Tec"></xsd:enumeration>
			<xsd:enumeration value="Oth"></xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:simpleType name="AlertConditionPriority">
			<xsd:restriction base="xsd:string">
			<xsd:enumeration value="Lo"></xsd:enumeration>)"
R"(
			<xsd:enumeration value="Me"></xsd:enumeration>
			<xsd:enumeration value="Hi"></xsd:enumeration>
			<xsd:enumeration value="None"></xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:complexType name="AlertConditionDescriptor">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractAlertDescriptor">
				<xsd:sequence>
					<xsd:element name="Source" type="pm:HandleRef" minOccurs="0" maxOccurs="unbounded"></xsd:element>
					<xsd:element name="CauseInfo" type="pm:CauseInfo" minOccurs="0" maxOccurs="unbounded"></xsd:element>
				</xsd:sequence>
				<xsd:attribute name="Kind" type="pm:AlertConditionKind" use="required"></xsd:attribute>
				<xsd:attribute name="Priority" type="pm:AlertConditionPriority" use="required"></xsd:attribute>
				<xsd:attribute name="DefaultConditionGenerationDelay" type="xsd:duration"></xsd:attribute>
				<xsd:attribute name="CanEscalate">
									<xsd:simpleType>
						<xsd:restriction base="pm:AlertConditionPriority">
							<xsd:enumeration value="Lo"></xsd:enumeration>
							<xsd:enumeration value="Me"></xsd:enumeration>
							<xsd:enumeration value="Hi"></xsd:enumeration>
						</xsd:restriction>
					</xsd:simpleType>
				</xsd:attribute>
				<xsd:attribute name="CanDeescalate">
					<xsd:simpleType>
						<xsd:restriction base="pm:AlertConditionPriority">
							<xsd:enumeration value="Me"></xsd:enumeration>
							<xsd:enumeration value="Lo"></xsd:enumeration>
							<xsd:enumeration value="None"></xsd:enumeration>
						</xsd:restriction>
					</xsd:simpleType>
				</xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:simpleType name="AlertConditionReference">
			<xsd:list itemType="pm:HandleRef"/>
	</xsd:simpleType>
	<xsd:complexType name="AlertConditionState">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractAlertState">
				<xsd:attribute name="ActualConditionGenerationDelay" type="xsd:duration"></xsd:attribute>
				<xsd:attribute name="ActualPriority" type="pm:A)"
R"(lertConditionPriority"></xsd:attribute>
				<xsd:attribute name="Rank" type="xsd:int"></xsd:attribute>
				<xsd:attribute name="Presence" type="xsd:boolean"></xsd:attribute>
				<xsd:attribute name="DeterminationTime" type="pm:Timestamp"></xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="LimitAlertConditionDescriptor">
			<xsd:complexContent>
			<xsd:extension base="pm:AlertConditionDescriptor">
				<xsd:sequence>
					<xsd:element name="MaxLimits" type="pm:Range"></xsd:element>
				</xsd:sequence>
				<xsd:attribute name="AutoLimitSupported" type="xsd:boolean"></xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:simpleType name="AlertConditionMonitoredLimits">
			<xsd:restriction base="xsd:string">
			<xsd:enumeration value="All"></xsd:enumeration>
			<xsd:enumeration value="LoOff"></xsd:enumeration>
			<xsd:enumeration value="HiOff"></xsd:enumeration>
			<xsd:enumeration value="None"></xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:complexType name="LimitAlertConditionState">
			<xsd:complexContent>
			<xsd:extension base="pm:AlertConditionState">
				<xsd:sequence>
					<xsd:element name="Limits" type="pm:Range"></xsd:element>
				</xsd:sequence>
				<xsd:attribute name="MonitoredAlertLimits" type="pm:AlertConditionMonitoredLimits" use="required"></xsd:attribute>
				<xsd:attribute name="AutoLimitActivationState" type="pm:AlertActivation" use="optional"></xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:simpleType name="AlertSignalManifestation">
			<xsd:restriction base="xsd:string">
			<xsd:enumeration value="Aud"></xsd:enumeration>
			<xsd:enumeration value="Vis"></xsd:enumeration>
			<xsd:enumeration value="Tan"></xsd:enumeration>
			<xsd:enumeration value="Oth"></xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:complexType name="AlertSignalDescriptor">
			<xsd:complexContent>
			<xsd:extension base="pm:Abst)"
R"(ractAlertDescriptor">
				<xsd:attribute name="ConditionSignaled" type="pm:HandleRef"></xsd:attribute>
				<xsd:attribute name="Manifestation" type="pm:AlertSignalManifestation" use="required"></xsd:attribute>
				<xsd:attribute name="Latching" type="xsd:boolean" use="required"></xsd:attribute>
				<xsd:attribute name="DefaultSignalGenerationDelay" type="xsd:duration"></xsd:attribute>
				<xsd:attribute name="MinSignalGenerationDelay" type="xsd:duration"></xsd:attribute>
				<xsd:attribute name="MaxSignalGenerationDelay" type="xsd:duration"></xsd:attribute>
				<xsd:attribute name="SignalDelegationSupported" type="xsd:boolean"></xsd:attribute>
				<xsd:attribute name="AcknowledgementSupported" type="xsd:boolean" use="optional"></xsd:attribute>
				<xsd:attribute name="AcknowledgeTimeout" type="xsd:duration" use="optional"></xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:simpleType name="AlertSignalPresence">
			<xsd:restriction base="xsd:string">
			<xsd:enumeration value="On"></xsd:enumeration>
			<xsd:enumeration value="Off"></xsd:enumeration>
			<xsd:enumeration value="Latch"></xsd:enumeration>
			<xsd:enumeration value="Ack"></xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:simpleType name="AlertSignalPrimaryLocation">
			<xsd:restriction base="xsd:string">
			<xsd:enumeration value="Loc"></xsd:enumeration>
			<xsd:enumeration value="Rem"></xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:complexType name="AlertSignalState">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractAlertState">
				<xsd:attribute name="ActualSignalGenerationDelay" type="xsd:duration"></xsd:attribute>
				<xsd:attribute name="Presence" type="pm:AlertSignalPresence" use="optional"></xsd:attribute>
				<xsd:attribute name="Location" type="pm:AlertSignalPrimaryLocation" use="optional"></xsd:attribute>
				<xsd:attribute name="Slot" type="xsd:unsignedInt" use="optional"></xsd:attribute>
			</xsd:extension>
		</xsd:co)"
R"(mplexContent>
	</xsd:complexType>
	<xsd:simpleType name="QualityIndicator">
			<xsd:restriction base="xsd:decimal">
			<xsd:minInclusive value="0">
						</xsd:minInclusive>
			<xsd:maxInclusive value="1">
						</xsd:maxInclusive>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:simpleType name="GenerationMode">
			<xsd:restriction base="xsd:string">
			<xsd:enumeration value="Real"></xsd:enumeration>
			<xsd:enumeration value="Test"></xsd:enumeration>
			<xsd:enumeration value="Demo"></xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:complexType name="AbstractMetricValue">
			<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="MetricQuality">
							<xsd:complexType>
					<xsd:sequence>
						<xsd:element ref="ext:Extension" minOccurs="0"/>
					</xsd:sequence>
					<xsd:attribute name="Validity" type="pm:MeasurementValidity" use="required"></xsd:attribute>
					<xsd:attribute name="Mode" type="pm:GenerationMode"></xsd:attribute>
					<xsd:attribute name="Qi" type="pm:QualityIndicator"></xsd:attribute>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="Annotation" minOccurs="0" maxOccurs="unbounded">
							<xsd:complexType>
					<xsd:sequence>
						<xsd:element ref="ext:Extension" minOccurs="0"/>
						<xsd:element name="Type" type="pm:CodedValue"></xsd:element>
					</xsd:sequence>
				</xsd:complexType>
			</xsd:element>
		</xsd:sequence>
		<xsd:attribute name="StartTime" type="pm:Timestamp" use="optional"></xsd:attribute>
		<xsd:attribute name="StopTime" type="pm:Timestamp" use="optional"></xsd:attribute>
		<xsd:attribute name="DeterminationTime" type="pm:Timestamp" use="optional"></xsd:attribute>
	</xsd:complexType>
	<xsd:complexType name="NumericMetricValue">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractMetricValue">
				<xsd:attribute name="Value" type="xsd:decimal" use="optional"></xsd:attribute>
			</xsd:extension>
		</xs)"
R"(d:complexContent>
	</xsd:complexType>
	<xsd:complexType name="StringMetricValue">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractMetricValue">
				<xsd:attribute name="Value" type="xsd:string" use="optional"></xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:simpleType name="RealTimeValueType">
			<xsd:list itemType="xsd:decimal"/>
	</xsd:simpleType>
	<xsd:complexType name="SampleArrayValue">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractMetricValue">
				<xsd:sequence>
					<xsd:element name="ApplyAnnotation" minOccurs="0" maxOccurs="unbounded">
						<xsd:complexType>
							<xsd:attribute name="AnnotationIndex" type="xsd:unsignedInt" use="required"></xsd:attribute>
							<xsd:attribute name="SampleIndex" type="xsd:unsignedInt" use="required"></xsd:attribute>
						</xsd:complexType>
					</xsd:element>
				</xsd:sequence>
				<xsd:attribute name="Samples" type="pm:RealTimeValueType"></xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:simpleType name="MetricCategory">
			<xsd:restriction base="xsd:string">
			<xsd:enumeration value="Unspec"></xsd:enumeration>
			<xsd:enumeration value="Msrmt"></xsd:enumeration>
			<xsd:enumeration value="Clc"></xsd:enumeration>
			<xsd:enumeration value="Set"></xsd:enumeration>
			<xsd:enumeration value="Preset"></xsd:enumeration>
			<xsd:enumeration value="Rcmm"></xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:simpleType name="DerivationMethod">
			<xsd:restriction base="xsd:string">
			<xsd:enumeration value="Auto"></xsd:enumeration>
			<xsd:enumeration value="Man"></xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:simpleType name="MetricAvailability">
			<xsd:restriction base="xsd:string">
			<xsd:enumeration value="Intr"></xsd:enumeration>
			<xsd:enumeration value="Cont"></xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:simpleType name="EntryRef">
			<xsd:list itemType="pm:HandleRe)"
R"(f"/>
	</xsd:simpleType>
	<xsd:complexType name="AbstractMetricDescriptor">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractDescriptor">
				<xsd:sequence>
					<xsd:element name="Unit" type="pm:CodedValue"></xsd:element>
					<xsd:element name="BodySite" type="pm:CodedValue" minOccurs="0" maxOccurs="unbounded"></xsd:element>
					<xsd:element name="Relation" minOccurs="0" maxOccurs="unbounded">
											<xsd:complexType>
							<xsd:sequence>
								<xsd:element ref="ext:Extension" minOccurs="0"/>
								<xsd:element name="Code" type="pm:CodedValue" minOccurs="0"></xsd:element>>
								<xsd:element name="Identification" type="pm:InstanceIdentifier" minOccurs="0"></xsd:element>>
							</xsd:sequence>
							<xsd:attribute name="Kind" use="required">
															<xsd:simpleType>
									<xsd:restriction base="xsd:string">
										<xsd:enumeration value="Rcm"></xsd:enumeration>
										<xsd:enumeration value="PS"></xsd:enumeration>
										<xsd:enumeration value="SST"></xsd:enumeration>
										<xsd:enumeration value="ECE"></xsd:enumeration>
										<xsd:enumeration value="DCE"></xsd:enumeration>
										<xsd:enumeration value="Oth"></xsd:enumeration>
									</xsd:restriction>
								</xsd:simpleType>
							</xsd:attribute>
							<xsd:attribute name="Entries" type="pm:EntryRef" use="required"></xsd:attribute>
						</xsd:complexType>
					</xsd:element>
				</xsd:sequence>
				<xsd:attribute name="MetricCategory" type="pm:MetricCategory" use="required"></xsd:attribute>
				<xsd:attribute name="DerivationMethod" type="pm:DerivationMethod"></xsd:attribute>
				<xsd:attribute name="MetricAvailability" type="pm:MetricAvailability" use="required"></xsd:attribute>
				<xsd:attribute name="MaxMeasurementTime" type="xsd:duration" use="optional"></xsd:attribute>
				<xsd:attribute name="MaxDelayTime" type="xsd:duration" use="optional"></xsd:attribute>
				<xsd:attribute name="DeterminationPeriod" type="xsd:duration" use="optional"></xsd:att)"
R"(ribute>
				<xsd:attribute name="LifeTimePeriod" type="xsd:duration" use="optional"></xsd:attribute>
				<xsd:attribute name="ActivationDuration" type="xsd:duration" use="optional"></xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="AbstractMetricState">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractState">
				<xsd:sequence>
					<xsd:element name="BodySite" type="pm:CodedValue" minOccurs="0" maxOccurs="unbounded"></xsd:element>
					<xsd:element name="PhysicalConnector" type="pm:PhysicalConnectorInfo" minOccurs="0"></xsd:element>
				</xsd:sequence>
				<xsd:attribute name="ActivationState" type="pm:ComponentActivation"></xsd:attribute>
				<xsd:attribute name="ActiveDeterminationPeriod" type="xsd:duration"></xsd:attribute>
				<xsd:attribute name="LifeTimePeriod" type="xsd:duration" use="optional"></xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="NumericMetricDescriptor">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractMetricDescriptor">
				<xsd:sequence>
					<xsd:element name="TechnicalRange" type="pm:Range" minOccurs="0" maxOccurs="unbounded"></xsd:element>
				</xsd:sequence>
				<xsd:attribute name="Resolution" type="xsd:decimal" use="required"></xsd:attribute>
				<xsd:attribute name="AveragingPeriod" type="xsd:duration"></xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="NumericMetricState">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractMetricState">
				<xsd:sequence>
					<xsd:element name="MetricValue" type="pm:NumericMetricValue" minOccurs="0"></xsd:element>
					<xsd:element name="PhysiologicalRange" type="pm:Range" minOccurs="0" maxOccurs="unbounded"></xsd:element>
				</xsd:sequence>
				<xsd:attribute name="ActiveAveragingPeriod" type="xsd:duration" use="optional"></xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:com)"
R"(plexType name="StringMetricDescriptor">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractMetricDescriptor"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="StringMetricState">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractMetricState">
				<xsd:sequence>
					<xsd:element name="MetricValue" type="pm:StringMetricValue" minOccurs="0"></xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="EnumStringMetricDescriptor">
			<xsd:complexContent>
			<xsd:extension base="pm:StringMetricDescriptor">
				<xsd:sequence>
					<xsd:element name="AllowedValue" maxOccurs="unbounded">
											<xsd:complexType>
							<xsd:sequence>
								<xsd:element name="Value" type="xsd:string"></xsd:element>>
								<xsd:element name="Type" type="pm:CodedValue" minOccurs="0"></xsd:element>>
								<xsd:element name="Identification" type="pm:InstanceIdentifier" minOccurs="0"></xsd:element>>
								<xsd:element name="Characteristic" type="pm:Measurement" minOccurs="0"></xsd:element>>
							</xsd:sequence>
						</xsd:complexType>
					</xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="EnumStringMetricState">
			<xsd:complexContent>
			<xsd:extension base="pm:StringMetricState"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="RealTimeSampleArrayMetricDescriptor">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractMetricDescriptor">
				<xsd:sequence>
					<xsd:element name="TechnicalRange" type="pm:Range" minOccurs="0" maxOccurs="unbounded"></xsd:element>
				</xsd:sequence>
				<xsd:attribute name="Resolution" type="xsd:decimal" use="required"></xsd:attribute>
				<xsd:attribute name="SamplePeriod" type="xsd:duration" use="required"></xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="RealTimeSampleArrayMetricState">
			<xsd:comp)"
R"(lexContent>
			<xsd:extension base="pm:AbstractMetricState">
				<xsd:sequence>
					<xsd:element name="MetricValue" type="pm:SampleArrayValue" minOccurs="0"></xsd:element>
					<xsd:element name="PhysiologicalRange" type="pm:Range" minOccurs="0" maxOccurs="unbounded"></xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="DistributionSampleArrayMetricDescriptor">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractMetricDescriptor">
				<xsd:sequence>
					<xsd:element name="TechnicalRange" type="pm:Range" minOccurs="0" maxOccurs="unbounded"></xsd:element>
					<xsd:element name="DomainUnit" type="pm:CodedValue"></xsd:element>
					<xsd:element name="DistributionRange" type="pm:Range"></xsd:element>
				</xsd:sequence>
				<xsd:attribute name="Resolution" type="xsd:decimal" use="required"></xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="DistributionSampleArrayMetricState">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractMetricState">
				<xsd:sequence>
					<xsd:element name="MetricValue" type="pm:SampleArrayValue" minOccurs="0"></xsd:element>
					<xsd:element name="PhysiologicalRange" type="pm:Range" minOccurs="0" maxOccurs="unbounded"></xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:simpleType name="OperationRef">
			<xsd:list itemType="pm:HandleRef"/>
	</xsd:simpleType>
	<xsd:complexType name="ScoDescriptor">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractDeviceComponentDescriptor">
				<xsd:sequence>
					<xsd:element name="Operation" type="pm:AbstractOperationDescriptor" minOccurs="0" maxOccurs="unbounded"></xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="ScoState">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractDeviceComponentState">
				<xsd:sequence>
					<xsd:element)"
R"( name="OperationGroup" minOccurs="0" maxOccurs="unbounded">
											<xsd:complexType>
							<xsd:sequence>
								<xsd:element ref="ext:Extension" minOccurs="0"/>
								<xsd:element name="Type" type="pm:CodedValue"></xsd:element>>
							</xsd:sequence>
							<xsd:attribute name="OperatingMode" type="pm:OperatingMode"></xsd:attribute>
							<xsd:attribute name="Operations" type="pm:OperationRef"></xsd:attribute>
						</xsd:complexType>
					</xsd:element>
				</xsd:sequence>
				<xsd:attribute name="InvocationRequested" type="pm:OperationRef"></xsd:attribute>
				<xsd:attribute name="InvocationRequired" type="pm:OperationRef"></xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="AbstractOperationDescriptor">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractDescriptor">
				<xsd:attribute name="OperationTarget" type="pm:HandleRef" use="required"></xsd:attribute>
				<xsd:attribute name="MaxTimeToFinish" type="xsd:duration"></xsd:attribute>
				<xsd:attribute name="InvocationEffectiveTimeout" type="xsd:duration"></xsd:attribute>
				<xsd:attribute name="Retriggerable" type="xsd:boolean"></xsd:attribute>
				<xsd:attribute name="AccessLevel">
									<xsd:simpleType>
						<xsd:restriction base="xsd:string">
							<xsd:enumeration value="Usr"></xsd:enumeration>
							<xsd:enumeration value="CSUsr"></xsd:enumeration>
							<xsd:enumeration value="RO"></xsd:enumeration>
							<xsd:enumeration value="SP"></xsd:enumeration>
							<xsd:enumeration value="Oth"></xsd:enumeration>
						</xsd:restriction>
					</xsd:simpleType>
				</xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="AbstractSetStateOperationDescriptor">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractOperationDescriptor">
				<xsd:sequence>
					<xsd:element name="ModifiableData" type="xsd:string" minOccurs="0" maxOccurs="unbounded"></xsd:element>
				</xsd:sequence>
			<)"
R"(/xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:simpleType name="OperatingMode">
			<xsd:restriction base="xsd:string">
			<xsd:enumeration value="Dis"></xsd:enumeration>
			<xsd:enumeration value="En"></xsd:enumeration>
			<xsd:enumeration value="NA"></xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:complexType name="AbstractOperationState">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractState">
				<xsd:attribute name="OperatingMode" type="pm:OperatingMode" use="required"></xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="SetValueOperationDescriptor">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractOperationDescriptor"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="SetValueOperationState">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractOperationState">
				<xsd:sequence>
					<xsd:element name="AllowedRange" type="pm:Range" minOccurs="0" maxOccurs="unbounded"></xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="SetStringOperationDescriptor">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractOperationDescriptor">
				<xsd:attribute name="MaxLength" type="xsd:unsignedLong" use="optional"></xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="SetStringOperationState">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractOperationState">
				<xsd:sequence>
					<xsd:element name="AllowedValues" minOccurs="0">
						<xsd:complexType>
							<xsd:sequence>
								<xsd:element name="Value" type="xsd:string" minOccurs="1" maxOccurs="unbounded"></xsd:element>>
							</xsd:sequence>
						</xsd:complexType>
					</xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="ActivateOperationDescriptor">
			<xsd:complexContent>
			<xsd:ext)"
R"(ension base="pm:AbstractSetStateOperationDescriptor">
				<xsd:sequence>
					<xsd:element name="Argument" minOccurs="0" maxOccurs="unbounded">
						<xsd:complexType>
							<xsd:sequence>
								<xsd:element name="ArgName" type="pm:CodedValue"></xsd:element>>
								<xsd:element name="Arg" type="xsd:QName"></xsd:element>>
							</xsd:sequence>
						</xsd:complexType>
					</xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="ActivateOperationState">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractOperationState"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="SetContextStateOperationDescriptor">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractSetStateOperationDescriptor"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="SetContextStateOperationState">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractOperationState"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="SetMetricStateOperationDescriptor">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractSetStateOperationDescriptor"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="SetMetricStateOperationState">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractOperationState"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="SetComponentStateOperationDescriptor">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractSetStateOperationDescriptor"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="SetComponentStateOperationState">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractOperationState"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="SetAlertStateOperationDescriptor">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractSetStateOperationDescriptor"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="SetAlertStateOp)"
R"(erationState">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractOperationState"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:simpleType name="TimeZone">
			<xsd:restriction base="xsd:string"/>
	</xsd:simpleType>
	<xsd:complexType name="ClockDescriptor">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractDeviceComponentDescriptor">
				<xsd:sequence>
					<xsd:element name="TimeProtocol" type="pm:CodedValue" minOccurs="0" maxOccurs="unbounded"></xsd:element>
				</xsd:sequence>
				<xsd:attribute name="Resolution" type="xsd:duration"></xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="ClockState">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractDeviceComponentState">
				<xsd:sequence>
					<xsd:element name="ActiveSyncProtocol" type="pm:CodedValue" minOccurs="0"></xsd:element>
					<xsd:element name="ReferenceSource" type="xsd:string" minOccurs="0" maxOccurs="unbounded"></xsd:element>
				</xsd:sequence>
				<xsd:attribute name="DateAndTime" type="pm:Timestamp"></xsd:attribute>
				<xsd:attribute name="RemoteSync" type="xsd:boolean" use="required"></xsd:attribute>
				<xsd:attribute name="Accuracy" type="xsd:decimal" use="optional"></xsd:attribute>
				<xsd:attribute name="LastSet" type="pm:Timestamp"></xsd:attribute>
				<xsd:attribute name="TimeZone" type="pm:TimeZone" use="optional"></xsd:attribute>
				<xsd:attribute name="CriticalUse" type="xsd:boolean" use="optional"></xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="BatteryDescriptor">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractDeviceComponentDescriptor">
				<xsd:sequence>
					<xsd:element name="CapacityFullCharge" type="pm:Measurement" minOccurs="0"></xsd:element>
					<xsd:element name="CapacitySpecified" type="pm:Measurement" minOccurs="0"></xsd:element>
					<xsd:element name="VoltageSpecified" type="pm:Measurement" minOccurs="0"></xsd:element>
		)"
R"(		</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="BatteryState">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractDeviceComponentState">
				<xsd:sequence>
					<xsd:element name="CapacityRemaining" type="pm:Measurement" minOccurs="0"></xsd:element>
					<xsd:element name="Voltage" type="pm:Measurement" minOccurs="0"></xsd:element>
					<xsd:element name="Current" type="pm:Measurement" minOccurs="0"></xsd:element>
					<xsd:element name="Temperature" type="pm:Measurement" minOccurs="0"></xsd:element>
					<xsd:element name="RemainingBatteryTime" type="pm:Measurement" minOccurs="0"></xsd:element>
				</xsd:sequence>
				<xsd:attribute name="ChargeStatus">
					<xsd:simpleType>
						<xsd:restriction base="xsd:string">
							<xsd:enumeration value="Ful"></xsd:enumeration>
							<xsd:enumeration value="ChB"></xsd:enumeration>
							<xsd:enumeration value="DisChB"></xsd:enumeration>
							<xsd:enumeration value="DEB"></xsd:enumeration>
						</xsd:restriction>
					</xsd:simpleType>
				</xsd:attribute>
				<xsd:attribute name="ChargeCycles" type="xsd:unsignedInt"></xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="SystemContextDescriptor">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractDeviceComponentDescriptor">
				<xsd:sequence>
					<xsd:element name="PatientContext" type="pm:PatientContextDescriptor" minOccurs="0"></xsd:element>
					<xsd:element name="LocationContext" type="pm:LocationContextDescriptor" minOccurs="0"></xsd:element>
					<xsd:element name="EnsembleContext" type="pm:EnsembleContextDescriptor" minOccurs="0" maxOccurs="unbounded"></xsd:element>
					<xsd:element name="OperatorContext" type="pm:OperatorContextDescriptor" minOccurs="0" maxOccurs="unbounded"></xsd:element>
					<xsd:element name="WorkflowContext" type="pm:WorkflowContextDescriptor" minOccurs="0" maxOccurs="unbounded"></xsd:element>
					<xsd:element name)"
R"(="MeansContext" type="pm:MeansContextDescriptor" minOccurs="0" maxOccurs="unbounded"></xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="SystemContextState">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractDeviceComponentState"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="AbstractContextDescriptor">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractDescriptor"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:simpleType name="ContextAssociation">
			<xsd:restriction base="xsd:string">
			<xsd:enumeration value="No"></xsd:enumeration>
			<xsd:enumeration value="Pre"></xsd:enumeration>
			<xsd:enumeration value="Assoc"></xsd:enumeration>
			<xsd:enumeration value="Dis"></xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:complexType name="AbstractContextState">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractMultiState">
				<xsd:sequence>
					<xsd:element name="Validator" type="pm:InstanceIdentifier" minOccurs="0" maxOccurs="unbounded"></xsd:element>
					<xsd:element name="Identification" type="pm:InstanceIdentifier" minOccurs="0" maxOccurs="unbounded"></xsd:element>
				</xsd:sequence>
				<xsd:attribute name="ContextAssociation" type="pm:ContextAssociation"></xsd:attribute>
				<xsd:attribute name="BindingMdibVersion" type="pm:ReferencedVersion" use="optional"></xsd:attribute>
				<xsd:attribute name="UnbindingMdibVersion" type="pm:ReferencedVersion"></xsd:attribute>
				<xsd:attribute name="BindingStartTime" type="pm:Timestamp"></xsd:attribute>
				<xsd:attribute name="BindingEndTime" type="pm:Timestamp"></xsd:attribute>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="BaseDemographics">
			<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="Givenname" type="xsd:string" minOccurs="0"></xsd:element>
			<xsd:element name="Middlename" type="xsd:string")"
R"( minOccurs="0" maxOccurs="unbounded"></xsd:element>
			<xsd:element name="Familyname" type="xsd:string" minOccurs="0"></xsd:element>
			<xsd:element name="Birthname" type="xsd:string" minOccurs="0"></xsd:element>
			<xsd:element name="Title" type="xsd:string" minOccurs="0"></xsd:element>
		</xsd:sequence>
	</xsd:complexType>
	<xsd:complexType name="PersonReference">
			<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="Identification" type="pm:InstanceIdentifier" maxOccurs="unbounded"></xsd:element>
			<xsd:element name="Name" type="pm:BaseDemographics" minOccurs="0"></xsd:element>
		</xsd:sequence>
	</xsd:complexType>
	<xsd:complexType name="LocationDetail">
			<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
		</xsd:sequence>
		<xsd:attribute name="PoC" type="xsd:string" use="optional"></xsd:attribute>
		<xsd:attribute name="Room" type="xsd:string" use="optional"></xsd:attribute>
		<xsd:attribute name="Bed" type="xsd:string" use="optional"></xsd:attribute>
		<xsd:attribute name="Facility" type="xsd:string" use="optional"></xsd:attribute>
		<xsd:attribute name="Building" type="xsd:string" use="optional"></xsd:attribute>
		<xsd:attribute name="Floor" type="xsd:string" use="optional"></xsd:attribute>
	</xsd:complexType>
	<xsd:complexType name="PatientContextDescriptor">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractContextDescriptor"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:simpleType name="Sex">
			<xsd:restriction base="xsd:string">
			<xsd:enumeration value="Unspec"></xsd:enumeration>
			<xsd:enumeration value="M"></xsd:enumeration>
			<xsd:enumeration value="F"></xsd:enumeration>
			<xsd:enumeration value="Unkn"></xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:simpleType name="PatientType">
			<xsd:restriction base="xsd:string">
			<xsd:enumeration value="Unspec"></xsd:enumeration>
			<xsd:enumeration value="Ad"></xsd:enumeration>
			<xsd:)"
R"(enumeration value="Ado"></xsd:enumeration>
			<xsd:enumeration value="Ped"></xsd:enumeration>
			<xsd:enumeration value="Inf"></xsd:enumeration>
			<xsd:enumeration value="Neo"></xsd:enumeration>
			<xsd:enumeration value="Oth"></xsd:enumeration>
		</xsd:restriction>
	</xsd:simpleType>
	<xsd:complexType name="PatientDemographicsCoreData">
			<xsd:complexContent>
			<xsd:extension base="pm:BaseDemographics">
				<xsd:sequence>
					<xsd:element name="Sex" type="pm:Sex" minOccurs="0"></xsd:element>
					<xsd:element name="PatientType" type="pm:PatientType" minOccurs="0"></xsd:element>
					<xsd:element name="DateOfBirth" minOccurs="0">
						<xsd:simpleType>
							<xsd:union memberTypes="xsd:dateTime xsd:date xsd:gYearMonth xsd:gYear"/>
						</xsd:simpleType>
					</xsd:element>
					<xsd:element name="Height" type="pm:Measurement" minOccurs="0"></xsd:element>
					<xsd:element name="Weight" type="pm:Measurement" minOccurs="0"></xsd:element>
					<xsd:element name="Race" type="pm:CodedValue" minOccurs="0"></xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="NeonatalPatientDemographicsCoreData">
			<xsd:complexContent>
			<xsd:extension base="pm:PatientDemographicsCoreData">
				<xsd:sequence>
					<xsd:element name="GestationalAge" type="pm:Measurement" minOccurs="0"></xsd:element>
					<xsd:element name="BirthLength" type="pm:Measurement" minOccurs="0"></xsd:element>
					<xsd:element name="BirthWeight" type="pm:Measurement" minOccurs="0"></xsd:element>
					<xsd:element name="HeadCircumference" type="pm:Measurement" minOccurs="0"></xsd:element>
					<xsd:element name="Mother" type="pm:PersonReference" minOccurs="0"></xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="PatientContextState">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractContextState">
				<xsd:sequence>
					<xsd:element name="CoreData" type="pm:Pati)"
R"(entDemographicsCoreData" minOccurs="0"/>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="LocationContextDescriptor">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractContextDescriptor"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="LocationContextState">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractContextState">
				<xsd:sequence>
					<xsd:element name="LocationDetail" type="pm:LocationDetail" minOccurs="0"></xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="WorkflowContextDescriptor">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractContextDescriptor"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="ClinicalInfo">
			<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="Type" type="pm:CodedValue" minOccurs="0"></xsd:element>
			<xsd:element name="Code" type="pm:CodedValue" minOccurs="0"></xsd:element>
			<xsd:element name="Criticality" minOccurs="0">
							<xsd:simpleType>
					<xsd:restriction base="xsd:string">
						<xsd:enumeration value="Lo">
												</xsd:enumeration>
						<xsd:enumeration value="Hi">
												</xsd:enumeration>
					</xsd:restriction>
				</xsd:simpleType>
			</xsd:element>
			<xsd:element name="Description" type="pm:LocalizedText" minOccurs="0" maxOccurs="unbounded"></xsd:element>
			<xsd:element name="RelatedMeasurement" minOccurs="0" maxOccurs="unbounded">
							<xsd:complexType>
					<xsd:sequence>
						<xsd:element name="Value" type="pm:Measurement">
												</xsd:element>
						<xsd:element name="ReferenceRange" minOccurs="0" maxOccurs="unbounded">
													<xsd:complexType>
								<xsd:sequence>
									<xsd:element name="Range" type="pm:Range">></xsd:element>
									<xsd:element name="Meaning" type="pm:CodedValue" minOccurs="0">></xsd:element>
								</xsd:sequence>
		)"
R"(					</xsd:complexType></xsd:element>
					</xsd:sequence>
					<xsd:attribute name="Validity" type="pm:MeasurementValidity">
										</xsd:attribute>
				</xsd:complexType>
			</xsd:element>
		</xsd:sequence>
	</xsd:complexType>
	<xsd:complexType name="ImagingProcedure">
			<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="AccessionIdentifier" type="pm:InstanceIdentifier"></xsd:element>
			<xsd:element name="RequestedProcedureId" type="pm:InstanceIdentifier"></xsd:element>
			<xsd:element name="StudyInstanceUid" type="pm:InstanceIdentifier"></xsd:element>
			<xsd:element name="ScheduledProcedureStepId" type="pm:InstanceIdentifier"></xsd:element>
			<xsd:element name="Modality" type="pm:CodedValue" minOccurs="0"></xsd:element>
			<xsd:element name="ProtocolCode" type="pm:CodedValue" minOccurs="0"></xsd:element>
		</xsd:sequence>
	</xsd:complexType>
	<xsd:complexType name="LocationReference">
			<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="Identification" type="pm:InstanceIdentifier" maxOccurs="unbounded"></xsd:element>
			<xsd:element name="LocationDetail" type="pm:LocationDetail" minOccurs="0"></xsd:element>
		</xsd:sequence>
	</xsd:complexType>
	<xsd:complexType name="OrderDetail">
			<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="Start" type="xsd:dateTime" minOccurs="0"></xsd:element>
			<xsd:element name="End" type="xsd:dateTime" minOccurs="0"></xsd:element>
			<xsd:element name="Performer" type="pm:PersonParticipation" minOccurs="0" maxOccurs="unbounded"></xsd:element>
			<xsd:element name="Service" type="pm:CodedValue" minOccurs="0" maxOccurs="unbounded"></xsd:element>
			<xsd:element name="ImagingProcedure" type="pm:ImagingProcedure" minOccurs="0" maxOccurs="unbounded"></xsd:element>
		</xsd:sequence>
	</xsd:complexType>
	<xsd:complexType name="PersonParticipation">
			<xsd:complexContent>
			<xsd:extension base="pm:PersonReference">
)"
R"(				<xsd:sequence>
					<xsd:element name="Role" type="pm:CodedValue" minOccurs="0" maxOccurs="unbounded"></xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="WorkflowContextState">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractContextState">
				<xsd:sequence>
					<xsd:element name="WorkflowDetail" minOccurs="0">
											<xsd:complexType>
							<xsd:sequence>
								<xsd:element ref="ext:Extension" minOccurs="0"/>
								<xsd:element name="Patient" type="pm:PersonReference"></xsd:element>>
								<xsd:element name="AssignedLocation" type="pm:LocationReference" minOccurs="0"></xsd:element>>
								<xsd:element name="VisitNumber" type="pm:InstanceIdentifier" minOccurs="0"></xsd:element>>
								<xsd:element name="DangerCode" type="pm:CodedValue" minOccurs="0" maxOccurs="unbounded"></xsd:element>>
								<xsd:element name="RelevantClinicalInfo" type="pm:ClinicalInfo" minOccurs="0" maxOccurs="unbounded"></xsd:element>>
								<xsd:element name="RequestedOrderDetail" minOccurs="0">
																	<xsd:complexType>
										<xsd:complexContent>
											<xsd:extension base="pm:OrderDetail">
												<xsd:sequence>
													<xsd:element name="ReferringPhysician" type="pm:PersonReference" minOccurs="0">
																										</xsd:element>
													<xsd:element name="RequestingPhysician" type="pm:PersonReference" minOccurs="0">
																										</xsd:element>
													<xsd:element name="PlacerOrderNumber" type="pm:InstanceIdentifier">
																										</xsd:element>
												</xsd:sequence>
											</xsd:extension>
										</xsd:complexContent>
									</xsd:complexType>
								</xsd:element>
								<xsd:element name="PerformedOrderDetail" minOccurs="0">
																	<xsd:complexType>
										<xsd:complexContent>
											<xsd:extension base="pm:OrderDetail">
												<xsd:sequence>
													<xsd:element name="Fi)"
R"(llerOrderNumber" type="pm:InstanceIdentifier" minOccurs="0">
																										</xsd:element>
													<xsd:element name="ResultingClinicalInfo" type="pm:ClinicalInfo" minOccurs="0" maxOccurs="unbounded">
																										</xsd:element>
												</xsd:sequence>
											</xsd:extension>
										</xsd:complexContent>
									</xsd:complexType>
								</xsd:element>
							</xsd:sequence>
						</xsd:complexType>
					</xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="OperatorContextDescriptor">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractContextDescriptor"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="OperatorContextState">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractContextState">
				<xsd:sequence>
					<xsd:element name="OperatorDetails" type="pm:BaseDemographics" minOccurs="0"></xsd:element>
				</xsd:sequence>
			</xsd:extension>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="MeansContextDescriptor">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractContextDescriptor"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="MeansContextState">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractContextState"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="EnsembleContextDescriptor">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractContextDescriptor"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:complexType name="EnsembleContextState">
			<xsd:complexContent>
			<xsd:extension base="pm:AbstractContextState"/>
		</xsd:complexContent>
	</xsd:complexType>
	<xsd:attributeGroup name="ContainmentTreeInfo">
			<xsd:attribute name="HandleRef" type="pm:HandleRef" use="optional">
				</xsd:attribute>
		<xsd:attribute name="ParentHandleRef" type="pm:HandleRef" use="optional">
				</xsd:attribute>
		<xsd:attribute name="EntryType" type)"
R"(="xsd:QName" use="optional">
				</xsd:attribute>
		<xsd:attribute name="ChildrenCount" type="xsd:int" use="optional">
				</xsd:attribute>
	</xsd:attributeGroup>
	<xsd:complexType name="ContainmentTree">
			<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="Entry" type="pm:ContainmentTreeEntry" minOccurs="0" maxOccurs="unbounded"></xsd:element>
		</xsd:sequence>
		<xsd:attributeGroup ref="pm:ContainmentTreeInfo"/>
	</xsd:complexType>
	<xsd:complexType name="ContainmentTreeEntry">
			<xsd:sequence>
			<xsd:element ref="ext:Extension" minOccurs="0"/>
			<xsd:element name="Type" type="pm:CodedValue" minOccurs="0"></xsd:element>
		</xsd:sequence>
		<xsd:attributeGroup ref="pm:ContainmentTreeInfo"/>
	</xsd:complexType>
	<xsd:element name="MdibContainer" type="pm:Mdib"/>
</xsd:schema>
)"
);

}
#endif
