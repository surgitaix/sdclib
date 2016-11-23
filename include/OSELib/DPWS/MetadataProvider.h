/*
 * MetadataProvider.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef DPWS_METADATAPROVIDER_H_
#define DPWS_METADATAPROVIDER_H_

#include "OSELib/fwd.h"

namespace OSELib {
namespace DPWS {

class MetadataProvider {
public:
	// todo make dpws ThisDevice/ThisModel metadata configurable
	MetadataProvider();

	std::string getDeviceServicePath() const;
	std::string getEventReportServicePath() const;
	std::string getGetServicePath() const;
	std::string getPHIServicePath() const;
	std::string getSetServicePath() const;
	std::string getWaveformStreamServicePath() const;

	WS::MEX::Metadata createDeviceMetadata(const std::string & serverAddress) const;
	WS::MEX::Metadata createContextServiceMetadata(const std::string & serverAddress) const;
	WS::MEX::Metadata createGetServiceMetadata(const std::string & serverAddress) const;
	WS::MEX::Metadata createSetServiceMetadata(const std::string & serverAddress) const;
	WS::MEX::Metadata createEventServiceMetadata(const std::string & serverAddress) const;
	WS::MEX::Metadata createStreamServiceMetadata(const std::string & serverAddress, const std::set<int> & streamingPorts) const;

private:
	using StreamDescriptions = MDPWS::StreamDescriptions; //????
	using StreamType = MDPWS::StreamTypeType;
//	using TargetNamespace = WS::STREAMING::TStreamDescriptions::TargetNamespaceOptional; // ?
	using MetadataSection = WS::MEX::MetadataSection;
	using MetadataDialect = WS::MEX::MetadataSection::DialectType;
	using MetadataLocation = WS::MEX::MetadataSection::LocationType;
	using Relationship = WS::MEX::MetadataSection::RelationshipType;
	using RelationshipType = WS::MEX::MetadataSection::RelationshipType::TypeType;
	using ThisDevice =  WS::MEX::MetadataSection::ThisDeviceType;
	using ThisModel =  WS::MEX::MetadataSection::ThisModelType;
	using Host = WS::MEX::MetadataSection::RelationshipType::HostType;
	using Hosted = WS::MEX::MetadataSection::RelationshipType::HostedType;

	MetadataSection createMetadataSectionThisModel() const;
	MetadataSection createMetadataSectionThisDevice() const;
	MetadataSection createMetadataSectionWSDLForContextService(const std::string & serverAddress) const;
	MetadataSection createMetadataSectionWSDLForEventReportService(const std::string & serverAddress) const;
	MetadataSection createMetadataSectionStream(const std::set<int> & streamingPorts) const;
	MetadataSection createMetadataSectionWSDLForWaveformReportService(const std::string & serverAddress) const;
	MetadataSection createMetadataSectionWSDLForGetService(const std::string & serverAddress) const;
	MetadataSection createMetadataSectionWSDLForSetService(const std::string & serverAddress) const;
	MetadataSection createMetadataSectionRelationship(const Host & host, const std::vector<Hosted> & hosted) const;

	Host createHostMetadata(const std::string & serverAddress) const;

	Hosted createHostedContextService(const std::string & serverAddress) const;
	Hosted createHostedEventReportService(const std::string & serverAddress) const;
	Hosted createHostedStreamReportService(const std::string & serverAddress) const;
	Hosted createHostedGetService(const std::string & serverAddress) const;
	Hosted createHostedSetService(const std::string & serverAddress) const;
};

} /* namespace DPWS */
} /* namespace OSELib */

#endif /* DPWS_METADATAPROVIDER_H_ */
