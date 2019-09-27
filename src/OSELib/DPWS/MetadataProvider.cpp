/*
 * MetadataProvider.cpp
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 23.08.2019, baumeister
 *
 */

#include "OSELib/DPWS/MetadataProvider.h"
#include "OSELib/DPWS/DPWS11Constants.h"
#include "OSELib/SDC/SDCConstants.h"
#include "OSELib/Helper/WithLogger.h"

#include "DataModel/MDPWS.hxx"


using namespace OSELib;
using namespace OSELib::DPWS;

const std::string HTTPProtocolPrefix("http://");
const std::string HTTPSProtocolPrefix("https://");

MetadataProvider::MetadataProvider(SDCLib::Dev::DeviceCharacteristics p_deviceCharacteristics)
: m_deviceCharacteristics(p_deviceCharacteristics)
{ }

std::string MetadataProvider::getDeviceServicePath() const {
	return "/Device";
}

std::string MetadataProvider::getGetServicePath() const {
	return std::string("/" + SDC::QNAME_GETSERVICE_PORTTYPE);
}
std::string MetadataProvider::getSetServicePath() const {
	return std::string("/" + SDC::QNAME_SETSERVICE_PORTTYPE);
}
std::string MetadataProvider::getBICEPSServicePath() const {
	return std::string("/" + SDC::QNAME_BICEPSSERVICE);
}

WS::MEX::Metadata MetadataProvider::createDeviceMetadata(const std::string & p_serverAddress, bool p_SSL) const
{
	WS::MEX::Metadata t_result;
	t_result.MetadataSection().push_back(createMetadataSectionThisModel());
	t_result.MetadataSection().push_back(createMetadataSectionThisDevice());
	t_result.MetadataSection().push_back(
		createMetadataSectionRelationship(
			createHostMetadata(p_serverAddress),
			{
					createHostedGetService(p_serverAddress, p_SSL),
					createHostedSetService(p_serverAddress, p_SSL),
					createHostedBICEPSServices(p_serverAddress, p_SSL),
			}
		)
	);
	return t_result;
}

// This *
MetadataProvider::MetadataSection MetadataProvider::createMetadataSectionThisModel() const
{
	ThisModel::ManufacturerType t_manufacturer(m_deviceCharacteristics.getManufacturer());

	ThisModel t_thisModel;
	t_thisModel.Manufacturer().push_back(t_manufacturer);

    for(auto &t_modelName : m_deviceCharacteristics.getModelNames()) {
//		t_thisModel.ModelName().push_back(std::string(t_modelName.first + ":" + t_modelName.second)); // leads to providing two times: en-US
    	t_thisModel.ModelName().push_back(std::string(t_modelName.second));
	}

	MetadataDialect t_dialectThisModel(OSELib::WS_MEX_DIALECT_MODEL);
	MetadataSection t_result(t_dialectThisModel);
	t_result.ThisModel().set(t_thisModel);
	return t_result;
}

MetadataProvider::MetadataSection MetadataProvider::createMetadataSectionThisDevice() const
{
	auto t_friendlyName = m_deviceCharacteristics.getFriendlyNames();
	if(t_friendlyName.empty()) {
		OSELib::Helper::WithLogger(OSELib::Log::BASE).log_critical([]() { return "Friendly Name not set! Setting a default!";});
		t_friendlyName["de-DE"] = "SDCProvider";
	}

	// TODO: maybe add the regarding language tag (first element) of the deviceCharacteristics.
	// note that here no field defined for that purpose
	ThisDevice t_thisDevice;
	for(auto &t_ent1 : t_friendlyName) {
		t_thisDevice.FriendlyName().push_back(t_ent1.second);
	}

	MetadataSection t_result((MetadataDialect(OSELib::WS_MEX_DIALECT_DEVICE)));
	t_result.ThisDevice().set(t_thisDevice);
	return t_result;
}


// Host
MetadataProvider::Host MetadataProvider::createHostMetadata(const std::string &) const
{
	Host t_host(Host::EndpointReferenceType(Host::EndpointReferenceType::AddressType(m_deviceCharacteristics.getEndpointReference())));
	return t_host;
}

// Get Service
MetadataProvider::Hosted MetadataProvider::createHostedGetService(const std::string & p_serverAddress, bool p_SSL) const
{
    auto t_protocol = HTTPSProtocolPrefix; // HTTPS by default
    if(!p_SSL) { t_protocol = HTTPProtocolPrefix; } // If specified else -> Switch to HTTP
	Hosted::EndpointReferenceType t_hostedEPR(Hosted::EndpointReferenceType::AddressType(t_protocol + p_serverAddress + getGetServicePath()));
	Hosted::TypesType tl_hostedTypes;
	tl_hostedTypes.push_back(xml_schema::Qname(SDC::NS_WSDL_TARGET_NAMESPACE, SDC::QNAME_GETSERVICE_PORTTYPE));

	Hosted::ServiceIdType t_hostedServiceId(SDC::QNAME_GETSERVICE);
	Hosted t_hosted(tl_hostedTypes, t_hostedServiceId);
	t_hosted.EndpointReference().push_back(t_hostedEPR);
	return t_hosted;
}
WS::MEX::Metadata MetadataProvider::createGetServiceMetadata(const std::string & p_serverAddress, bool p_SSL) const {
	WS::MEX::Metadata t_result;
	t_result.MetadataSection().push_back(createMetadataSectionWSDLForGetService(p_serverAddress, p_SSL));
	t_result.MetadataSection().push_back(
			createMetadataSectionRelationship(createHostMetadata(p_serverAddress), { createHostedGetService(p_serverAddress, p_SSL) } ));
	return t_result;
}
MetadataProvider::MetadataSection MetadataProvider::createMetadataSectionWSDLForGetService(const std::string & p_serverAddress, bool p_SSL) const {
	MetadataSection metadataSectionWsdl((MetadataDialect(OSELib::WS_MEX_DIALECT_WSDL)));
    auto t_protocol = HTTPSProtocolPrefix; // HTTPS by default
    if(!p_SSL) { t_protocol = HTTPProtocolPrefix; } // If specified else -> Switch to HTTP
	metadataSectionWsdl.Location().set(MetadataLocation(t_protocol + p_serverAddress + getGetServicePath() + "/description.wsdl"));
	return metadataSectionWsdl;
}


// Set Service
MetadataProvider::Hosted MetadataProvider::createHostedSetService(const std::string & p_serverAddress, bool p_SSL) const
{
    auto t_protocol = HTTPSProtocolPrefix; // HTTPS by default
    if(!p_SSL) { t_protocol = HTTPProtocolPrefix; } // If specified else -> Switch to HTTP
	Hosted::EndpointReferenceType t_hostedEPR(Hosted::EndpointReferenceType::AddressType(t_protocol + p_serverAddress + getSetServicePath()));
	Hosted::TypesType tl_hostedTypes;
	tl_hostedTypes.push_back(xml_schema::Qname(SDC::NS_WSDL_TARGET_NAMESPACE, SDC::QNAME_SETSERVICE_PORTTYPE));

	Hosted::ServiceIdType t_hostedServiceId(SDC::QNAME_SETSERVICE);
	Hosted t_hosted(tl_hostedTypes, t_hostedServiceId);
	t_hosted.EndpointReference().push_back(t_hostedEPR);
	return t_hosted;
}
WS::MEX::Metadata MetadataProvider::createSetServiceMetadata(const std::string & p_serverAddress, bool p_SSL) const
{
	WS::MEX::Metadata t_result;
	t_result.MetadataSection().push_back(createMetadataSectionWSDLForSetService(p_serverAddress, p_SSL));
	t_result.MetadataSection().push_back(
		createMetadataSectionRelationship(createHostMetadata(p_serverAddress), { createHostedSetService(p_serverAddress, p_SSL) } ));
	return t_result;
}
MetadataProvider::MetadataSection MetadataProvider::createMetadataSectionWSDLForSetService(const std::string & p_serverAddress, bool p_SSL) const {
	MetadataSection t_metadataSectionWsdl((MetadataDialect(OSELib::WS_MEX_DIALECT_WSDL)));
    auto t_protocol = HTTPSProtocolPrefix; // HTTPS by default
    if(!p_SSL) { t_protocol = HTTPProtocolPrefix; } // If specified else -> Switch to HTTP
    t_metadataSectionWsdl.Location().set(MetadataLocation(t_protocol + p_serverAddress + getSetServicePath() + "/description.wsdl"));
	return t_metadataSectionWsdl;
}


// BICEPS Service
MetadataProvider::Hosted MetadataProvider::createHostedBICEPSServices(const std::string& p_serverAddress, bool p_SSL) const
{
	// According to R0034 Description Event Service, State Event Service, Context Service and Waveform Service
	// must be implemented as ONE hosted service
    auto t_protocol = HTTPSProtocolPrefix; // HTTPS by default
    if(!p_SSL) { t_protocol = HTTPProtocolPrefix; } // If specified else -> Switch to HTTP

	Hosted::TypesType tl_hostedTypes;

	//tl_hostedTypes.push_back(xml_schema::Qname(SDC::NS_WSDL_TARGET_NAMESPACE, SDC::QNAME_DESCRIPTIONEVENTSERVICE)); TODO
	tl_hostedTypes.push_back(xml_schema::Qname(SDC::NS_WSDL_TARGET_NAMESPACE, SDC::QNAME_STATEEVENTSERVICE_PORTTYPE));
	tl_hostedTypes.push_back(xml_schema::Qname(SDC::NS_WSDL_TARGET_NAMESPACE, SDC::QNAME_CONTEXTSERVICE_PORTTYPE));
	tl_hostedTypes.push_back(xml_schema::Qname(SDC::NS_WSDL_TARGET_NAMESPACE, SDC::QNAME_WAVEFORMSERVICE));

	Hosted::ServiceIdType t_hostedServiceId(SDC::QNAME_BICEPSSERVICE);
	Hosted t_hosted(tl_hostedTypes, t_hostedServiceId);
	t_hosted.EndpointReference().push_back(Hosted::EndpointReferenceType (Hosted::EndpointReferenceType::AddressType(t_protocol + p_serverAddress + getBICEPSServicePath())));

	return t_hosted;
}
WS::MEX::Metadata MetadataProvider::createBICEPSServiceMetadata(const std::string & p_serverAddress, bool p_SSL) const {
	WS::MEX::Metadata t_result;
	t_result.MetadataSection().push_back(createMetadataSectionWSDLForBICEPSService(p_serverAddress, p_SSL));
	t_result.MetadataSection().push_back(
			createMetadataSectionRelationship(createHostMetadata(p_serverAddress), { createHostedBICEPSServices(p_serverAddress, p_SSL) } ));
	return t_result;
}
MetadataProvider::MetadataSection MetadataProvider::createMetadataSectionWSDLForBICEPSService(const std::string & p_serverAddress, bool p_SSL) const
{
	MetadataSection t_metadataSectionWsdl((MetadataDialect(OSELib::WS_MEX_DIALECT_WSDL)));
	auto t_protocol = HTTPSProtocolPrefix; // HTTPS by default
	if(!p_SSL) { t_protocol = HTTPProtocolPrefix; } // If specified else -> Switch to HTTP
	t_metadataSectionWsdl.Location().set(MetadataLocation(t_protocol + p_serverAddress + getBICEPSServicePath() + "/description.wsdl"));
	return t_metadataSectionWsdl;
}


MetadataProvider::MetadataSection MetadataProvider::createMetadataSectionRelationship(const Host & p_host, const std::vector<Hosted> & p_hosted) const
{
	Relationship t_relationship(p_host, RelationshipType(OSELib::WS_MEX_REL_HOST));
	for(const auto & t_item : p_hosted) {
		t_relationship.Hosted().push_back(t_item);
	}

	MetadataSection t_metadataSectionRelationship((MetadataDialect(OSELib::WS_MEX_DIALECT_REL)));
	t_metadataSectionRelationship.Relationship().set(t_relationship);
	return t_metadataSectionRelationship;
}




/*
 * Currently unused -> See createMetadataSectionStream for later use in BICEPSService
 * WS::MEX::Metadata MetadataProvider::createStreamServiceMetadata(const std::string & p_serverAddress, const std::set<int> & p_streamingPorts, bool p_SSL) const
{
	WS::MEX::Metadata t_result;
	t_result.MetadataSection().push_back(createMetadataSectionWSDLForBICEPSService(p_serverAddress, p_SSL));
	t_result.MetadataSection().push_back(
			createMetadataSectionRelationship(createHostMetadata(p_serverAddress), { createHostedBICEPSServices(p_serverAddress, p_SSL) } ));  // FIXME: Just a temp workaround...
	t_result.MetadataSection().push_back(createMetadataSectionStream(p_streamingPorts));
	return t_result;
}
MetadataProvider::MetadataSection MetadataProvider::createMetadataSectionStream(const std::set<int> & p_streamingPorts) const
{
	MetadataSection t_metadataSectionStream((MetadataDialect(SDC::WS_MEX_DIALECT_STREAM)));
	t_metadataSectionStream.Identifier(SDC::WS_MEX_ORNET_STREAM_IDENTIFIER);
	StreamDescriptions t_sd(SDC::WS_MEX_ORNET_STREAM_IDENTIFIER);
	MDPWS::StreamTransmissionType t_stt;
	int t_counter(0);
	// only one multicast address is used but multiple ports are possible (but not used in the recommended implementation,
	// since the consumer should distinguish between the sending provider by the From-Field)
	// still more than one port can be used
	for (auto t_it : p_streamingPorts)
	{
		t_counter++;
		t_stt.StreamAddress(SDC::MDPWS_MCAST_ADDR + ":" + std::to_string(t_it));
		StreamType t_st(t_stt,OSELib::SDC::MDPWS_STREAM_TYPE + std::to_string(t_counter),OSELib::SDC::WS_MEX_ORNET_STREAM_TYPE);
		t_sd.StreamType().push_back(t_st);
	}
	t_metadataSectionStream.StreamDescriptions().set(t_sd);
	return t_metadataSectionStream;
}


*/
