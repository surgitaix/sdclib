/* Prerequisites of SDCLib
 *
 * (c)2019 Fabian Baumeister
 *
 *
 */
#ifndef SDCLIB_PREREQUISITES_H
#define SDCLIB_PREREQUISITES_H

// Config
#include "config/config.h"

// Just some stdandard header
#include <memory>
#include <vector>
#include <chrono>

// Some using "shortcuts"
// Note: Define these to have some cleaner code, easier handling with smart pointers, predeclaration of classes etc.
// Expand as need arises


// ## SDCLib
namespace SDCLib
{
    using SDCPort = unsigned short;

    // Some using for better handling
    class SDCInstance;
    using SDCInstance_shared_ptr = std::shared_ptr<SDCInstance>;

    using TimePoint = std::chrono::system_clock::time_point;
    using Duration_s = std::chrono::seconds;

    using StringVector = std::vector <std::string>;

    namespace Config
    {
        class SDCConfig;
        using SDCConfig_shared_ptr = std::shared_ptr<SDCConfig>;

        class NetworkConfig;
        using NetworkConfig_shared_ptr = std::shared_ptr<NetworkConfig>;

        class SSLConfig;
        using SSLConfig_shared_ptr = std::shared_ptr<SSLConfig>;
    }
    // Just a few helpers
    namespace Data {
            namespace SDC {

                class SDCConsumer;
                using SDCConsumer_unique_ptr = std::unique_ptr<SDCConsumer>;
                using ConsumerList_unique = std::vector<std::unique_ptr<SDCConsumer>>;

                class SDCProvider;
                using SDCProvider_shared_ptr = std::shared_ptr<SDCProvider>;

                class SDCProviderStateHandler;

                class ChannelDescriptor;
                using ChannelDescriptor_shared_ptr = std::shared_ptr<ChannelDescriptor>;
                class VmdDescriptor;
                using VmdDescriptor_shared_ptr = std::shared_ptr<VmdDescriptor>;
                class MdsDescriptor;
                using MdsDescriptor_shared_ptr = std::shared_ptr<MdsDescriptor>;

                class NumericMetricDescriptor;
                using NumericMetricDescriptor_shared_ptr = std::shared_ptr<NumericMetricDescriptor>;

                class StringMetricDescriptor;
                using StringMetricDescriptor_shared_ptr = std::shared_ptr<StringMetricDescriptor>;

                class EnumStringMetricDescriptor;
                using EnumStringMetricDescriptor_shared_ptr = std::shared_ptr<EnumStringMetricDescriptor>;

                class ActivateOperationDescriptor;
                using ActivateOperationDescriptor_shared_ptr = std::shared_ptr<ActivateOperationDescriptor>;

            }
    }
}
namespace OSELib
{
    namespace SDC
    {
        class ServiceManager;
        using ServiceManager_shared_ptr = std::shared_ptr<ServiceManager>;
    }
}

#endif
