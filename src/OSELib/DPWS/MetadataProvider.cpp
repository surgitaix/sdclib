/*
 * MetadataProvider.cpp
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#include <OSELib/OSCP/OSCPConstants.h>
#include "MetadataExchange.hxx"
#include "MDPWS.hxx"

#include "OSELib/DPWS/DPWS11Constants.h"
#include "OSELib/DPWS/MetadataProvider.h"

namespace OSELib {
namespace DPWS {

const std::string HTTPProtocolPrefix("http://");

MetadataProvider::MetadataProvider() {
}

std::string MetadataProvider::getDeviceServicePath() const {
	return "/Device";
}

std::string MetadataProvider::getEventReportServicePath() const {
	return "/EventReport";
}

std::string MetadataProvider::getGetServicePath() const {
	return "/GetService";
}

std::string MetadataProvider::getPHIServicePath() const {
	return "/PHI";
}

std::string MetadataProvider::getSetServicePath() const {
	return "/SetService";
}

std::string MetadataProvider::getWaveformStreamServicePath() const {
	return "/WaveformEventReport";
}

WS::MEX::Metadata MetadataProvider::createDeviceMetadata(const std::string & serverAddress) const {
	WS::MEX::Metadata result;
	result.MetadataSection().push_back(createMetadataSectionThisModel());
	result.MetadataSection().push_back(createMetadataSectionThisDevice());
	result.MetadataSection().push_back(
		createMetadataSectionRelationship(
			createHostMetadata(serverAddress),
			{
					createHostedContextService(serverAddress),
					createHostedGetService(serverAddress),
					createHostedEventReportService(serverAddress),
					createHostedSetService(serverAddress),
					createHostedStreamReportService(serverAddress),
			}
		)
	);
	return result;
}

WS::MEX::Metadata MetadataProvider::createContextServiceMetadata(const std::string & serverAddress) const {
	WS::MEX::Metadata result;
	result.MetadataSection().push_back(createMetadataSectionWSDLForContextService(serverAddress));
	result.MetadataSection().push_back(
			createMetadataSectionRelationship(createHostMetadata(serverAddress), { createHostedContextService(serverAddress) } ));
	return result;
}

WS::MEX::Metadata MetadataProvider::createGetServiceMetadata(const std::string & serverAddress) const {
	WS::MEX::Metadata result;
	result.MetadataSection().push_back(createMetadataSectionWSDLForGetService(serverAddress));
	result.MetadataSection().push_back(
			createMetadataSectionRelationship(createHostMetadata(serverAddress), { createHostedGetService(serverAddress) } ));
	return result;
}

WS::MEX::Metadata MetadataProvider::createSetServiceMetadata(const std::string & serverAddress) const {
	WS::MEX::Metadata result;
	result.MetadataSection().push_back(createMetadataSectionWSDLForSetService(serverAddress));
	result.MetadataSection().push_back(
		createMetadataSectionRelationship(createHostMetadata(serverAddress), { createHostedSetService(serverAddress) } ));
	return result;
}

WS::MEX::Metadata MetadataProvider::createEventServiceMetadata(const std::string & serverAddress) const {
	WS::MEX::Metadata result;
	result.MetadataSection().push_back(createMetadataSectionWSDLForEventReportService(serverAddress));
	result.MetadataSection().push_back(
			createMetadataSectionRelationship(createHostMetadata(serverAddress), { createHostedEventReportService(serverAddress) } ));
	return result;
}

WS::MEX::Metadata MetadataProvider::createStreamServiceMetadata(const std::string & serverAddress, const std::set<int> & streamingPorts) const {
	WS::MEX::Metadata result;
	result.MetadataSection().push_back(createMetadataSectionWSDLForWaveformReportService(serverAddress));
	result.MetadataSection().push_back(
			createMetadataSectionRelationship(createHostMetadata(serverAddress), { createHostedStreamReportService(serverAddress) } ));
	result.MetadataSection().push_back(createMetadataSectionStream(streamingPorts));
	return result;
}

MetadataProvider::MetadataSection MetadataProvider::createMetadataSectionThisModel() const {
	ThisModel::ManufacturerType manufacturer("TestManufacturer");

	ThisModel thisModel;
	thisModel.Manufacturer().push_back(manufacturer);

	MetadataDialect dialectThisModel(OSELib::WS_MEX_DIALECT_MODEL);
	MetadataSection result(dialectThisModel);
	result.ThisModel().set(thisModel);
	return result;
}

MetadataProvider::MetadataSection MetadataProvider::createMetadataSectionThisDevice() const {
	ThisDevice::FriendlyNameType friendlyName("FriendlyName");

	ThisDevice thisDevice;
	thisDevice.FriendlyName().push_back(friendlyName);

	MetadataSection result((MetadataDialect(OSELib::WS_MEX_DIALECT_DEVICE)));
	result.ThisDevice().set(thisDevice);
	return result;
}

MetadataProvider::MetadataSection MetadataProvider::createMetadataSectionWSDLForContextService(const std::string & serverAddress) const {
	MetadataSection metadataSectionWsdl((MetadataDialect(OSELib::WS_MEX_DIALECT_WSDL)));
	metadataSectionWsdl.Location().set(MetadataLocation(HTTPProtocolPrefix + serverAddress + getPHIServicePath() + "/description.wsdl"));
	return metadataSectionWsdl;
}

MetadataProvider::MetadataSection MetadataProvider::createMetadataSectionWSDLForEventReportService(const std::string & serverAddress) const {
	MetadataSection metadataSectionWsdl((MetadataDialect(OSELib::WS_MEX_DIALECT_WSDL)));
	metadataSectionWsdl.Location().set(MetadataLocation(HTTPProtocolPrefix + serverAddress + getEventReportServicePath() + "/description.wsdl"));
	return metadataSectionWsdl;
}

MetadataProvider::MetadataSection MetadataProvider::createMetadataSectionWSDLForWaveformReportService(const std::string & serverAddress) const {
	MetadataSection metadataSectionWsdl((MetadataDialect(OSELib::WS_MEX_DIALECT_WSDL)));
	metadataSectionWsdl.Location().set(MetadataLocation(HTTPProtocolPrefix + serverAddress + getWaveformStreamServicePath() + "/description.wsdl"));
	return metadataSectionWsdl;
}

MetadataProvider::MetadataSection MetadataProvider::createMetadataSectionStream(const std::set<int> & streamingPorts) const {
	MetadataSection metadataSectionStream((MetadataDialect(OSELib::WS_MEX_DIALECT_STREAM)));
	metadataSectionStream.Identifier("http://message-model-uri/15/04/WaveformStreamService");
	StreamDescriptions sd(OSCP::WS_MEX_ORNET_STREAM_IDENTIFIER);
	MDPWS::StreamTransmissionType stt;
	//TODO add udp address here
	stt.StreamAddress("udp_adress");
	StreamType st(stt,"WaveformStream",OSELib::OSCP::WS_MEX_ORNET_STREAM_TYPE);
	xml_schema::Uri action(OSCP::ACTION_ORNET_STREAM);
	st.ActionUri(action);
	sd.StreamType().push_back(st);
	metadataSectionStream.StreamDescriptions().set(sd);
	return metadataSectionStream;
}

MetadataProvider::MetadataSection MetadataProvider::createMetadataSectionWSDLForGetService(const std::string & serverAddress) const {
	MetadataSection metadataSectionWsdl((MetadataDialect(OSELib::WS_MEX_DIALECT_WSDL)));
	metadataSectionWsdl.Location().set(MetadataLocation(HTTPProtocolPrefix + serverAddress + getGetServicePath() + "/description.wsdl"));
	return metadataSectionWsdl;
}

MetadataProvider::MetadataSection MetadataProvider::createMetadataSectionWSDLForSetService(const std::string & serverAddress) const {
	MetadataSection metadataSectionWsdl((MetadataDialect(OSELib::WS_MEX_DIALECT_WSDL)));
	metadataSectionWsdl.Location().set(MetadataLocation(HTTPProtocolPrefix + serverAddress + getSetServicePath() + "/description.wsdl"));
	return metadataSectionWsdl;
}

MetadataProvider::MetadataSection MetadataProvider::createMetadataSectionRelationship(const Host & host, const std::vector<Hosted> & hosted) const {
	Relationship relationship(host, RelationshipType(OSELib::WS_MEX_REL_HOST));
	for(const auto & item : hosted) {
		relationship.Hosted().push_back(item);
	}

	MetadataSection metadataSectionRelationship((MetadataDialect(OSELib::WS_MEX_DIALECT_REL)));
	metadataSectionRelationship.Relationship().set(relationship);
	return metadataSectionRelationship;
}

MetadataProvider::Host MetadataProvider::createHostMetadata(const std::string & serverAddress) const {
	Host::EndpointReferenceType::AddressType hostEPRAddress(HTTPProtocolPrefix + serverAddress + getDeviceServicePath());
	Host::EndpointReferenceType hostEPR(hostEPRAddress);
	Host host(hostEPR);
	return host;
}

MetadataProvider::Hosted MetadataProvider::createHostedContextService(const std::string & serverAddress) const {
	Hosted::EndpointReferenceType::AddressType hostedEPRAddress(HTTPProtocolPrefix + serverAddress + getPHIServicePath());
	Hosted::EndpointReferenceType hostedEPR(hostedEPRAddress);
	Hosted::TypesType hostedTypes;
	hostedTypes.push_back(xml_schema::Qname(OSCP::NS_WSDL_TARGET_NAMESPACE, OSCP::QNAME_CONTEXTSERVICE_PORTTYPE));

	Hosted::ServiceIdType hostedServiceId("PHI");
	Hosted hosted(hostedTypes, hostedServiceId);
	hosted.EndpointReference().push_back(hostedEPR);
	return hosted;
}

MetadataProvider::Hosted MetadataProvider::createHostedGetService(const std::string & serverAddress) const {
	Hosted::EndpointReferenceType::AddressType hostedEPRAddress(HTTPProtocolPrefix + serverAddress + getGetServicePath());
	Hosted::EndpointReferenceType hostedEPR(hostedEPRAddress);
	Hosted::TypesType hostedTypes;
	hostedTypes.push_back(xml_schema::Qname(OSCP::NS_WSDL_TARGET_NAMESPACE, OSCP::QNAME_GETSERVICE_PORTTYPE));

	Hosted::ServiceIdType hostedServiceId("GetService");
	Hosted hosted(hostedTypes, hostedServiceId);
	hosted.EndpointReference().push_back(hostedEPR);
	return hosted;
}

MetadataProvider::Hosted MetadataProvider::createHostedEventReportService(const std::string & serverAddress) const {
	Hosted::EndpointReferenceType::AddressType hostedEPRAddress(HTTPProtocolPrefix + serverAddress + getEventReportServicePath());
	Hosted::EndpointReferenceType hostedEPR(hostedEPRAddress);
	Hosted::TypesType hostedTypes;
	hostedTypes.push_back(xml_schema::Qname(OSCP::NS_WSDL_TARGET_NAMESPACE, OSCP::QNAME_REPORTSERVICE_PORTTYPE));

	Hosted::ServiceIdType hostedServiceId("EventReport");
	Hosted hosted(hostedTypes, hostedServiceId);
	hosted.EndpointReference().push_back(hostedEPR);
	return hosted;
}

MetadataProvider::Hosted MetadataProvider::createHostedStreamReportService(const std::string & serverAddress) const {
	Hosted::EndpointReferenceType::AddressType hostedEPRAddress(HTTPProtocolPrefix + serverAddress + getWaveformStreamServicePath());
	Hosted::EndpointReferenceType hostedEPR(hostedEPRAddress);
	Hosted::TypesType hostedTypes;
	hostedTypes.push_back(xml_schema::Qname(OSCP::NS_WSDL_TARGET_NAMESPACE, OSCP::QNAME_STREAMSERVICE_PORTTYPE));

	Hosted::ServiceIdType hostedServiceId("WaveformEventReport");
	Hosted hosted(hostedTypes, hostedServiceId);
	hosted.EndpointReference().push_back(hostedEPR);
	return hosted;
}

MetadataProvider::Hosted MetadataProvider::createHostedSetService(const std::string & serverAddress) const {
	Hosted::EndpointReferenceType::AddressType hostedEPRAddress(HTTPProtocolPrefix + serverAddress + getSetServicePath());
	Hosted::EndpointReferenceType hostedEPR(hostedEPRAddress);
	Hosted::TypesType hostedTypes;
	hostedTypes.push_back(xml_schema::Qname(OSCP::NS_WSDL_TARGET_NAMESPACE, OSCP::QNAME_SETSERVICE_PORTTYPE));

	Hosted::ServiceIdType hostedServiceId("SetService");
	Hosted hosted(hostedTypes, hostedServiceId);
	hosted.EndpointReference().push_back(hostedEPR);
	return hosted;
}

} /* namespace DPWS */
} /* namespace OSELib */
