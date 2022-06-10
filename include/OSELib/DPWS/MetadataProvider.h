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

#include "DataModel/MetadataExchange.hxx"

namespace OSELib
{
    namespace DPWS
    {
        class MetadataProvider
        {
        private:
            const SDCLib::Dev::DeviceCharacteristics m_deviceCharacteristics;

        public:
            MetadataProvider(const SDCLib::Dev::DeviceCharacteristics p_deviceCharacteristics);
            ~MetadataProvider() = default;


            std::string getDeviceServicePath() const;

            std::string getGetServicePath() const;
            std::string getSetServicePath() const;

            std::string getBICEPSServicePath() const;

            WS::MEX::Metadata createDeviceMetadata(const std::string& p_serverAddress, bool p_SSL) const;
            WS::MEX::Metadata createGetServiceMetadata(const std::string& p_serverAddress, bool p_SSL) const;
            WS::MEX::Metadata createSetServiceMetadata(const std::string& p_serverAddress, bool p_SSL) const;
            WS::MEX::Metadata createBICEPSServiceMetadata(const std::string& p_serverAddress, bool p_SSL) const;

        private:
            using StreamDescriptions = MDPWS::StreamDescriptionsType;
            using StreamType = MDPWS::StreamTypeType;
            //	using TargetNamespace = WS::STREAMING::TStreamDescriptions::TargetNamespaceOptional; // ?
            using MetadataSection = WS::MEX::MetadataSection;
            using MetadataDialect = WS::MEX::MetadataSection::DialectType;
            using MetadataLocation = WS::MEX::MetadataSection::LocationType;
            using Relationship = WS::MEX::MetadataSection::RelationshipType;
            using RelationshipType = WS::MEX::MetadataSection::RelationshipType::TypeType;
            using ThisDevice = WS::MEX::MetadataSection::ThisDeviceType;
            using ThisModel = WS::MEX::MetadataSection::ThisModelType;
            using Host = WS::MEX::MetadataSection::RelationshipType::HostType;
            using Hosted = WS::MEX::MetadataSection::RelationshipType::HostedType;

            MetadataSection createMetadataSectionThisModel() const;
            MetadataSection createMetadataSectionThisDevice() const;

            MetadataSection createMetadataSectionRelationship(const Host& p_host, const std::vector<Hosted>& hosted) const;

            Host createHostMetadata(const std::string& p_serverAddress) const;

            Hosted createHostedGetService(const std::string& p_serverAddress, bool p_SSL) const;
            MetadataSection createMetadataSectionWSDLForGetService(const std::string& p_serverAddress, bool p_SSL) const;

            Hosted createHostedSetService(const std::string& p_serverAddress, bool p_SSL) const;
            MetadataSection createMetadataSectionWSDLForSetService(const std::string& p_serverAddress, bool p_SSL) const;

            Hosted createHostedBICEPSServices(const std::string& p_serverAddress, bool p_SSL) const;
            MetadataSection createMetadataSectionWSDLForBICEPSService(const std::string& p_serverAddress, bool p_SSL) const;


            //MetadataSection createMetadataSectionStream(const std::set<int> & p_streamingPorts) const;
        };
    }  // namespace DPWS
}  // namespace OSELib

#endif
