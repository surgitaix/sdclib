#ifndef SCHEMA_BICEPS_MESSAGEMODEL_H
#define SCHEMA_BICEPS_MESSAGEMODEL_H

#include <string>

namespace SCHEMA
{
const std::string SCHEMA_BICEPS_MESSAGEMODEL_NAME("BICEPS_MessageModel.xsd");

const std::string SCHEMA_BICEPS_MESSAGEMODEL_CONTENT = std::string(

		R"(<?xml version="1.0"?>
		<xsd:schema xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:ext="http://standards.ieee.org/downloads/11073/11073-10207-2017/extension" xmlns:pm="http://standards.ieee.org/downloads/11073/11073-10207-2017/participant" xmlns:msg="http://standards.ieee.org/downloads/11073/11073-10207-2017/message" targetNamespace="http://standards.ieee.org/downloads/11073/11073-10207-2017/message" elementFormDefault="qualified" attributeFormDefault="unqualified" xml:lang="en">
			<xsd:import namespace="http://standards.ieee.org/downloads/11073/11073-10207-2017/extension" schemaLocation="ExtensionPoint.xsd"/>
			<xsd:import namespace="http://standards.ieee.org/downloads/11073/11073-10207-2017/participant" schemaLocation="BICEPS_ParticipantModel.xsd"/>
			<xsd:simpleType name="TransactionId">
				<xsd:restriction base="xsd:unsignedInt"/>
			</xsd:simpleType>
			<xsd:simpleType name="InvocationState">
				<xsd:restriction base="xsd:string">
					<xsd:enumeration value="Wait">
					</xsd:enumeration>
					<xsd:enumeration value="Start">
					</xsd:enumeration>
					<xsd:enumeration value="Cnclld">
					</xsd:enumeration>
					<xsd:enumeration value="CnclldMan">
					</xsd:enumeration>
					<xsd:enumeration value="Fin">
					</xsd:enumeration>
					<xsd:enumeration value="FinMod">
					</xsd:enumeration>
					<xsd:enumeration value="Fail">
					</xsd:enumeration>
				</xsd:restriction>
			</xsd:simpleType>
			<xsd:simpleType name="InvocationError">
				<xsd:restriction base="xsd:string">
					<xsd:enumeration value="Unspec">
					</xsd:enumeration>
					<xsd:enumeration value="Unkn">
					</xsd:enumeration>
					<xsd:enumeration value="Inv">
					</xsd:enumeration>
					<xsd:enumeration value="Oth">
					</xsd:enumeration>
				</xsd:restriction>
			</xsd:simpleType>
			<xsd:complexType name="InvocationInfo">
				<xsd:sequence>
					<xsd:element ref="ext:Extension" minOccurs="0"/>
					<xsd:element name="TransactionId" type="msg:TransactionId">
					</xsd:element>
					<xsd:element name="InvocationState" type="msg:InvocationState">
					</xsd:elemen)"
		R"(t>
					<xsd:element name="InvocationError" type="msg:InvocationError" minOccurs="0">
					</xsd:element>
					<xsd:element name="InvocationErrorMessage" type="pm:LocalizedText" minOccurs="0" maxOccurs="unbounded">
					</xsd:element>
				</xsd:sequence>
			</xsd:complexType>
			
			<xsd:complexType name="AbstractGet">
				<xsd:sequence>
					<xsd:element ref="ext:Extension" minOccurs="0"/>
				</xsd:sequence>
			</xsd:complexType>
			<xsd:complexType name="AbstractGetResponse">
				<xsd:sequence>
					<xsd:element ref="ext:Extension" minOccurs="0"/>
				</xsd:sequence>
				<xsd:attributeGroup ref="pm:MdibVersionGroup"/>
			</xsd:complexType>
			<xsd:complexType name="AbstractReportPart">
				<xsd:sequence>
					<xsd:element ref="ext:Extension" minOccurs="0"/>
					<xsd:element name="SourceMds" type="pm:HandleRef" minOccurs="0">
					</xsd:element>
				</xsd:sequence>
			</xsd:complexType>
			<xsd:complexType name="AbstractReport">
				<xsd:sequence>
					<xsd:element ref="ext:Extension" minOccurs="0"/>
				</xsd:sequence>
				<xsd:attributeGroup ref="pm:MdibVersionGroup"/>
			</xsd:complexType>
			<xsd:complexType name="AbstractSet">
				<xsd:sequence>
					<xsd:element ref="ext:Extension" minOccurs="0"/>
					<xsd:element name="OperationHandleRef" type="pm:HandleRef">
					</xsd:element>
				</xsd:sequence>
			</xsd:complexType>
			<xsd:complexType name="AbstractSetResponse">
				<xsd:sequence>
					<xsd:element ref="ext:Extension" minOccurs="0"/>
					<xsd:element name="InvocationInfo" type="msg:InvocationInfo">
					</xsd:element>
				</xsd:sequence>
				<xsd:attributeGroup ref="pm:MdibVersionGroup"/>
			</xsd:complexType>
			
			<xsd:element name="GetMdib">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractGet"/>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="GetMdibResponse">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractGetResponse">
							<xsd:sequence>
								<xsd:element name="Mdib" type="pm:Mdib">
								</xsd:element>
							</xsd:sequence>
						</xsd:ext)"
		R"(ension>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="GetMdDescription">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractGet">
							<xsd:sequence>
								<xsd:element name="HandleRef" type="pm:HandleRef" minOccurs="0" maxOccurs="unbounded">
								</xsd:element>
							</xsd:sequence>
						</xsd:extension>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="GetMdDescriptionResponse">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractGetResponse">
							<xsd:sequence>
								<xsd:element name="MdDescription" type="pm:MdDescription">
								</xsd:element>
							</xsd:sequence>
						</xsd:extension>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="GetMdState">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractGet">
							<xsd:sequence>
								<xsd:element name="HandleRef" type="pm:HandleRef" minOccurs="0" maxOccurs="unbounded">
								</xsd:element>
							</xsd:sequence>
						</xsd:extension>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="GetMdStateResponse">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractGetResponse">
							<xsd:sequence>
								<xsd:element name="MdState" type="pm:MdState">
								</xsd:element>
							</xsd:sequence>
						</xsd:extension>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="GetContextStates">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractGet">
							<xsd:sequence>
								<xsd:element name="HandleRef" type="pm:HandleRef" minOccurs="0" maxOccurs="unbounded">
								</xsd:element>
							</xsd:sequence>
						</xsd:extension>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="GetContextStatesResponse">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractGetResponse">
							<xsd:sequen)"
		R"(ce>
								<xsd:element name="ContextState" type="pm:AbstractContextState" minOccurs="0" maxOccurs="unbounded">
								</xsd:element>
							</xsd:sequence>
						</xsd:extension>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="GetContextStatesByIdentification">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractGet">
							<xsd:sequence>
								<xsd:element name="Identification" type="pm:InstanceIdentifier" minOccurs="0" maxOccurs="unbounded">
								</xsd:element>
							</xsd:sequence>
							<xsd:attribute name="ContextType" type="xsd:QName">
							</xsd:attribute>
						</xsd:extension>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="GetContextStatesByIdentificationResponse">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractGetResponse">
							<xsd:sequence>
								<xsd:element name="ContextState" type="pm:AbstractContextState" minOccurs="0" maxOccurs="unbounded">
								</xsd:element>
							</xsd:sequence>
						</xsd:extension>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="GetContextStatesByFilter">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractGet">
							<xsd:sequence>
								<xsd:element name="Filter" type="xsd:string" minOccurs="0" maxOccurs="unbounded">
								</xsd:element>
							</xsd:sequence>
							<xsd:attribute name="ContextType" type="xsd:QName">
							</xsd:attribute>
						</xsd:extension>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="GetContextStatesByFilterResponse">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractGetResponse">
							<xsd:sequence>
								<xsd:element name="ContextState" type="pm:AbstractContextState" minOccurs="0" maxOccurs="unbounded">
								</xsd:element>
							</xsd:sequence>
						</xsd:extension>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="SetContextSta)"
		R"(te">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractSet">
							<xsd:sequence>
								<xsd:element name="ProposedContextState" type="pm:AbstractContextState" maxOccurs="unbounded">
								</xsd:element>
							</xsd:sequence>
						</xsd:extension>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="SetContextStateResponse">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractSetResponse"/>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:complexType name="AbstractContextReport">
				<xsd:complexContent>
					<xsd:extension base="msg:AbstractReport">
						<xsd:sequence>
							<xsd:element name="ReportPart" minOccurs="0" maxOccurs="unbounded">
								<xsd:complexType>
									<xsd:complexContent>
										<xsd:extension base="msg:AbstractReportPart">
											<xsd:sequence>
												<xsd:element name="ContextState" type="pm:AbstractContextState" minOccurs="0" maxOccurs="unbounded">
												</xsd:element>
											</xsd:sequence>
										</xsd:extension>
									</xsd:complexContent>
								</xsd:complexType>
							</xsd:element>
						</xsd:sequence>
					</xsd:extension>
				</xsd:complexContent>
			</xsd:complexType>
			<xsd:element name="PeriodicContextReport">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractContextReport"/>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="EpisodicContextReport">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractContextReport"/>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			
			<xsd:element name="GetLocalizedText">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractGet">
							<xsd:sequence>
								<xsd:element name="Ref" type="pm:LocalizedTextRef" minOccurs="0" maxOccurs="unbounded">
								</xsd:element>
								<xsd:element name="Version" type="pm:ReferencedVersion" minOccurs="0">
								</xsd:element>
								<)"
		R"(xsd:element name="Lang" type="xsd:language" minOccurs="0" maxOccurs="unbounded">
								</xsd:element>
								<xsd:element name="TextWidth" type="pm:LocalizedTextWidth" minOccurs="0" maxOccurs="unbounded">
								</xsd:element>
								<xsd:element name="NumberOfLines" type="xsd:integer" minOccurs="0" maxOccurs="unbounded">
								</xsd:element>
							</xsd:sequence>
						</xsd:extension>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="GetLocalizedTextResponse">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractGetResponse">
							<xsd:sequence>
								<xsd:element name="Text" type="pm:LocalizedText" minOccurs="0" maxOccurs="unbounded">
								</xsd:element>
							</xsd:sequence>
						</xsd:extension>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="GetSupportedLanguages">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractGet">
							<xsd:sequence/>
						</xsd:extension>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="GetSupportedLanguagesResponse">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractGetResponse">
							<xsd:sequence>
								<xsd:element name="Lang" type="xsd:language" minOccurs="0" maxOccurs="unbounded">
								</xsd:element>
							</xsd:sequence>
						</xsd:extension>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			
			<xsd:complexType name="VersionFrame">
				<xsd:attribute name="Start" type="pm:ReferencedVersion">
				</xsd:attribute>
				<xsd:attribute name="End" type="pm:ReferencedVersion">
				</xsd:attribute>
			</xsd:complexType>
			<xsd:complexType name="TimeFrame">
				<xsd:attribute name="Start" type="pm:Timestamp">
				</xsd:attribute>
				<xsd:attribute name="End" type="pm:Timestamp">
				</xsd:attribute>
			</xsd:complexType>
			<xsd:element name="GetDescriptorsFromArchive">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractGet">
							<xsd:sequen)"
		R"(ce>
								<xsd:element name="DescriptorRevisions" type="msg:VersionFrame" minOccurs="0">
								</xsd:element>
								<xsd:element name="TimeFrame" type="msg:TimeFrame" minOccurs="0">
								</xsd:element>
								<xsd:element name="Handle" type="pm:HandleRef" minOccurs="0" maxOccurs="unbounded">
								</xsd:element>
							</xsd:sequence>
						</xsd:extension>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="GetDescriptorsFromArchiveResponse">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractGetResponse">
							<xsd:sequence>
								<xsd:element name="Descriptor" type="pm:AbstractDescriptor" minOccurs="0" maxOccurs="unbounded">
								</xsd:element>
							</xsd:sequence>
						</xsd:extension>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="GetStatesFromArchive">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractGet">
							<xsd:sequence>
								<xsd:element name="StateRevisions" type="msg:VersionFrame" minOccurs="0">
								</xsd:element>
								<xsd:element name="TimeFrame" type="msg:TimeFrame" minOccurs="0">
								</xsd:element>
								<xsd:element name="Handle" type="pm:HandleRef" minOccurs="0" maxOccurs="unbounded">
								</xsd:element>
							</xsd:sequence>
						</xsd:extension>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="GetStatesFromArchiveResponse">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractGetResponse">
							<xsd:sequence>
								<xsd:element name="State" type="pm:AbstractState" minOccurs="0" maxOccurs="unbounded">
								</xsd:element>
							</xsd:sequence>
						</xsd:extension>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			
			<xsd:element name="SetValue">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractSet">
							<xsd:sequence>
								<xsd:element name="RequestedNumericValue" type="xsd:decimal">
								</xsd:element>
							</xsd:)"
		R"(sequence>
						</xsd:extension>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="SetValueResponse">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractSetResponse"/>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="SetString">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractSet">
							<xsd:sequence>
								<xsd:element name="RequestedStringValue" type="xsd:string">
								</xsd:element>
							</xsd:sequence>
						</xsd:extension>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="SetStringResponse">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractSetResponse"/>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="Activate">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractSet">
							<xsd:sequence>
								<xsd:element name="Argument" minOccurs="0" maxOccurs="unbounded">
									<xsd:complexType>
										<xsd:sequence>
											<xsd:element ref="ext:Extension" minOccurs="0"/>
											<xsd:element name="ArgValue" type="xsd:anySimpleType">
											</xsd:element>
										</xsd:sequence>
									</xsd:complexType>
								</xsd:element>
							</xsd:sequence>
						</xsd:extension>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="ActivateResponse">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractSetResponse"/>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="SetAlertState">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractSet">
							<xsd:sequence>
								<xsd:element name="ProposedAlertState" type="pm:AbstractAlertState">
								</xsd:element>
							</xsd:sequence>
						</xsd:extension>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="SetAlertStateResponse">
				<xsd:complexType>)"
		R"(
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractSetResponse"/>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="SetComponentState">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractSet">
							<xsd:sequence>
								<xsd:element name="ProposedComponentState" type="pm:AbstractDeviceComponentState" maxOccurs="unbounded">
								</xsd:element>
							</xsd:sequence>
						</xsd:extension>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="SetComponentStateResponse">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractSetResponse"/>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="SetMetricState">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractSet">
							<xsd:sequence>
								<xsd:element name="ProposedMetricState" type="pm:AbstractMetricState" maxOccurs="unbounded">
								</xsd:element>
							</xsd:sequence>
						</xsd:extension>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="SetMetricStateResponse">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractSetResponse"/>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="OperationInvokedReport">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractReport">
							<xsd:sequence>
								<xsd:element name="ReportPart" maxOccurs="unbounded">
									<xsd:complexType>
										<xsd:complexContent>
											<xsd:extension base="msg:AbstractReportPart">
												<xsd:sequence>
													<xsd:element name="InvocationInfo" type="msg:InvocationInfo">
													</xsd:element>
													<xsd:element name="InvocationSource" type="pm:InstanceIdentifier">
													</xsd:element>
												</xsd:sequence>
												<xsd:attribute name="OperationHandleRef" type="pm:HandleRef" use="required">
												</xsd:attribute>
											)"
		R"(	<xsd:attribute name="OperationTarget" type="pm:HandleRef">
												</xsd:attribute>
											</xsd:extension>
										</xsd:complexContent>
									</xsd:complexType>
								</xsd:element>
							</xsd:sequence>
						</xsd:extension>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			
			<xsd:element name="GetContainmentTree">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractGet">
							<xsd:sequence>
								<xsd:element name="HandleRef" type="pm:HandleRef" minOccurs="0" maxOccurs="unbounded">
								</xsd:element>
							</xsd:sequence>
						</xsd:extension>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="GetContainmentTreeResponse">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractGetResponse">
							<xsd:sequence>
								<xsd:element name="ContainmentTree" type="pm:ContainmentTree">
								</xsd:element>
							</xsd:sequence>
						</xsd:extension>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="GetDescriptor">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractGet">
							<xsd:sequence>
								<xsd:element name="HandleRef" type="pm:HandleRef" minOccurs="0" maxOccurs="unbounded">
								</xsd:element>
							</xsd:sequence>
						</xsd:extension>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="GetDescriptorResponse">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractGetResponse">
							<xsd:sequence>
								<xsd:element name="Descriptor" type="pm:AbstractDescriptor" minOccurs="0" maxOccurs="unbounded">
								</xsd:element>
							</xsd:sequence>
						</xsd:extension>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			
			
			<xsd:complexType name="AbstractMetricReport">
				<xsd:complexContent>
					<xsd:extension base="msg:AbstractReport">
						<xsd:sequence>
							<xsd:element name="ReportPart" minOccurs="0" maxOccurs="unbounded">
								<xsd:complexTyp)"
		R"(e>
									<xsd:complexContent>
										<xsd:extension base="msg:AbstractReportPart">
											<xsd:sequence>
												<xsd:element name="MetricState" type="pm:AbstractMetricState" minOccurs="0" maxOccurs="unbounded">
												</xsd:element>
											</xsd:sequence>
										</xsd:extension>
									</xsd:complexContent>
								</xsd:complexType>
							</xsd:element>
						</xsd:sequence>
					</xsd:extension>
				</xsd:complexContent>
			</xsd:complexType>
			<xsd:element name="EpisodicMetricReport">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractMetricReport"/>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="PeriodicMetricReport">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractMetricReport"/>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			
			<xsd:complexType name="AbstractComponentReport">
				<xsd:complexContent>
					<xsd:extension base="msg:AbstractReport">
						<xsd:sequence>
							<xsd:element name="ReportPart" minOccurs="0" maxOccurs="unbounded">
								<xsd:complexType>
									<xsd:complexContent>
										<xsd:extension base="msg:AbstractReportPart">
											<xsd:sequence>
												<xsd:element name="ComponentState" type="pm:AbstractDeviceComponentState" minOccurs="0" maxOccurs="unbounded">
												</xsd:element>
											</xsd:sequence>
										</xsd:extension>
									</xsd:complexContent>
								</xsd:complexType>
							</xsd:element>
						</xsd:sequence>
					</xsd:extension>
				</xsd:complexContent>
			</xsd:complexType>
			<xsd:element name="EpisodicComponentReport">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractComponentReport"/>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="PeriodicComponentReport">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractComponentReport"/>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			
			<xsd:complexType name="Abstrac)"
		R"(tAlertReport">
				<xsd:complexContent>
					<xsd:extension base="msg:AbstractReport">
						<xsd:sequence>
							<xsd:element name="ReportPart" minOccurs="0" maxOccurs="unbounded">
								<xsd:complexType>
									<xsd:complexContent>
										<xsd:extension base="msg:AbstractReportPart">
											<xsd:sequence>
												<xsd:element name="AlertState" type="pm:AbstractAlertState" minOccurs="0" maxOccurs="unbounded">
												</xsd:element>
											</xsd:sequence>
										</xsd:extension>
									</xsd:complexContent>
								</xsd:complexType>
							</xsd:element>
						</xsd:sequence>
					</xsd:extension>
				</xsd:complexContent>
			</xsd:complexType>
			<xsd:element name="EpisodicAlertReport">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractAlertReport"/>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="PeriodicAlertReport">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractAlertReport"/>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			
			<xsd:complexType name="AbstractOperationalStateReport">
				<xsd:complexContent>
					<xsd:extension base="msg:AbstractReport">
						<xsd:sequence>
							<xsd:element name="ReportPart" minOccurs="0" maxOccurs="unbounded">
								<xsd:complexType>
									<xsd:complexContent>
										<xsd:extension base="msg:AbstractReportPart">
											<xsd:sequence>
												<xsd:element name="OperationState" type="pm:AbstractOperationState" minOccurs="0" maxOccurs="unbounded">
												</xsd:element>
											</xsd:sequence>
										</xsd:extension>
									</xsd:complexContent>
								</xsd:complexType>
							</xsd:element>
						</xsd:sequence>
					</xsd:extension>
				</xsd:complexContent>
			</xsd:complexType>
			<xsd:element name="EpisodicOperationalStateReport">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractOperationalStateReport"/>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="PeriodicOperatio)"
		R"(nalStateReport">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractOperationalStateReport"/>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			
			<xsd:element name="SystemErrorReport">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractReport">
							<xsd:sequence>
								<xsd:element name="ReportPart" minOccurs="1" maxOccurs="unbounded">
									<xsd:complexType>
										<xsd:complexContent>
											<xsd:extension base="msg:AbstractReportPart">
												<xsd:sequence>
													<xsd:element name="ErrorCode" type="pm:CodedValue">
													</xsd:element>
													<xsd:element name="ErrorInfo" type="pm:LocalizedText" minOccurs="0">
													</xsd:element>
												</xsd:sequence>
											</xsd:extension>
										</xsd:complexContent>
									</xsd:complexType>
								</xsd:element>
							</xsd:sequence>
						</xsd:extension>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			
			<xsd:simpleType name="DescriptionModificationType">
				<xsd:restriction base="xsd:string">
					<xsd:enumeration value="Crt">
					</xsd:enumeration>
					<xsd:enumeration value="Upt">
					</xsd:enumeration>
					<xsd:enumeration value="Del">
					</xsd:enumeration>
				</xsd:restriction>
			</xsd:simpleType>
			<xsd:element name="DescriptionModificationReport">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractReport">
							<xsd:sequence>
								<xsd:element name="ReportPart" maxOccurs="unbounded">
									<xsd:complexType>
										<xsd:complexContent>
											<xsd:extension base="msg:AbstractReportPart">
												<xsd:sequence>
													<xsd:element name="Descriptor" type="pm:AbstractDescriptor" minOccurs="0" maxOccurs="unbounded">
													</xsd:element>
													<xsd:element name="State" type="pm:AbstractState" minOccurs="0" maxOccurs="unbounded">
													</xsd:element>
												</xsd:sequence>
												<xsd:attribute name="ParentDescriptor" type="pm:HandleRef" use="optional">
					)"
		R"(							</xsd:attribute>
												<xsd:attribute name="ModificationType" type="msg:DescriptionModificationType" use="optional">
												</xsd:attribute>
											</xsd:extension>
										</xsd:complexContent>
									</xsd:complexType>
								</xsd:element>
							</xsd:sequence>
						</xsd:extension>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			
			<xsd:element name="WaveformStream">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractReport">
							<xsd:sequence>
								<xsd:element name="State" type="pm:RealTimeSampleArrayMetricState" minOccurs="0" maxOccurs="unbounded">
								</xsd:element>
							</xsd:sequence>
						</xsd:extension>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			<xsd:element name="ObservedValueStream">
				<xsd:complexType>
					<xsd:complexContent>
						<xsd:extension base="msg:AbstractReport">
							<xsd:sequence>
								<xsd:element name="Value" minOccurs="0" maxOccurs="unbounded">
									<xsd:complexType>
										<xsd:sequence>
											<xsd:element name="Value" type="pm:SampleArrayValue" minOccurs="0" maxOccurs="1"/>
										</xsd:sequence>
										<xsd:attribute name="Metric" type="pm:HandleRef" use="required">
										</xsd:attribute>
										<xsd:attribute name="StateVersion" type="pm:VersionCounter" use="optional">
										</xsd:attribute>
									</xsd:complexType>
								</xsd:element>
							</xsd:sequence>
						</xsd:extension>
					</xsd:complexContent>
				</xsd:complexType>
			</xsd:element>
			
			<xsd:simpleType name="RetrievabilityMethod">
				<xsd:restriction base="xsd:string">
					<xsd:enumeration value="Get">
					</xsd:enumeration>
					<xsd:enumeration value="Per">
					</xsd:enumeration>
					<xsd:enumeration value="Ep">
					</xsd:enumeration>
					<xsd:enumeration value="Strm">
					</xsd:enumeration>
				</xsd:restriction>
			</xsd:simpleType>
			<xsd:complexType name="RetrievabilityInfo">
				<xsd:sequence>
					<xsd:sequence>
						<xsd:element ref="ext:Extension" minOccurs="0"/>
					</xsd:sequence>
				</xsd:seque)"
		R"(nce>
				<xsd:attribute name="Method" type="msg:RetrievabilityMethod" use="required">
				</xsd:attribute>
				<xsd:attribute name="UpdatePeriod" type="xsd:duration">
				</xsd:attribute>
			</xsd:complexType>
			<xsd:element name="Retrievability">
				<xsd:complexType>
					<xsd:sequence>
						<xsd:element name="By" type="msg:RetrievabilityInfo" minOccurs="0" maxOccurs="unbounded">
						</xsd:element>
					</xsd:sequence>
				</xsd:complexType>
			</xsd:element>
		</xsd:schema>
		)"
);

}
#endif
