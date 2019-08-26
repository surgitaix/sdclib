/*
 * MetadataProvider.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 23.08.2019, baumeister
 *
 */

#ifndef OSELIB_DPWS_METADATAPROVIDER_H_
#define OSELIB_DPWS_METADATAPROVIDER_H_

#include "OSELib/fwd.h"
#include "SDCLib/Dev/DeviceCharacteristics.h"

#include "MetadataExchange.hxx"

namespace OSELib
{
	namespace DPWS
	{
		class MetadataProvider
		{
		private:

			SDCLib::Dev::DeviceCharacteristics m_deviceCharacteristics;

		public:
			MetadataProvider(SDCLib::Dev::DeviceCharacteristics p_deviceCharacteristics);
			// Special Member Functions
			MetadataProvider(const MetadataProvider& p_obj) = default;
			MetadataProvider(MetadataProvider&& p_obj) = default;
			MetadataProvider& operator=(const MetadataProvider& p_obj) = default;
			MetadataProvider& operator=(MetadataProvider&& p_obj) = default;
			~MetadataProvider() = default;


			std::string getDeviceServicePath() const;
			std::string getStateEventReportServicePath() const;
			std::string getGetServicePath() const;
			std::string getContextServicePath() const;
			std::string getSetServicePath() const;
			std::string getWaveformServicePath() const;

			WS::MEX::Metadata createDeviceMetadata(const std::string & p_serverAddress, bool p_SSL) const;
			WS::MEX::Metadata createContextServiceMetadata(const std::string & p_serverAddress, bool p_SSL) const;
			WS::MEX::Metadata createGetServiceMetadata(const std::string & p_serverAddress, bool p_SSL) const;
			WS::MEX::Metadata createSetServiceMetadata(const std::string & p_serverAddress, bool p_SSL) const;
			WS::MEX::Metadata createEventServiceMetadata(const std::string & p_serverAddress, bool p_SSL) const;
			WS::MEX::Metadata createStreamServiceMetadata(const std::string & p_serverAddress, const std::set<int> & streamingPorts, bool p_SSL) const;

		private:

			using StreamDescriptions = MDPWS::StreamDescriptionsType;
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
			MetadataSection createMetadataSectionWSDLForContextService(const std::string & p_serverAddress, bool p_SSL) const;
			MetadataSection createMetadataSectionWSDLForEventReportService(const std::string & p_serverAddress, bool p_SSL) const;
			MetadataSection createMetadataSectionStream(const std::set<int> & p_streamingPorts) const;
			MetadataSection createMetadataSectionWSDLForWaveformReportService(const std::string & p_serverAddress, bool p_SSL) const;
			MetadataSection createMetadataSectionWSDLForGetService(const std::string & p_serverAddress, bool p_SSL) const;
			MetadataSection createMetadataSectionWSDLForSetService(const std::string & p_serverAddress, bool p_SSL) const;
			MetadataSection createMetadataSectionRelationship(const Host & p_host, const std::vector<Hosted> & hosted) const;

			Host createHostMetadata(const std::string & p_serverAddress) const;

			Hosted createHostedContextService(const std::string & p_serverAddress, bool p_SSL) const;
			Hosted createHostedEventReportService(const std::string & p_serverAddress, bool p_SSL) const;
			Hosted createHostedStreamReportService(const std::string & p_serverAddress, bool p_SSL) const;
			Hosted createHostedGetService(const std::string & p_serverAddress, bool p_SSL) const;
			Hosted createHostedSetService(const std::string & p_serverAddress, bool p_SSL) const;
		};
	}
}

#endif
