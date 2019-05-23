/* Prerequisites of SDCLib
 *
 * (c)2019 Fabian Baumeister
 *
 *
 */
#ifndef SDCLIBRARY_SDCLIB_PREREQUISITES_H
#define SDCLIBRARY_SDCLIB_PREREQUISITES_H

// Config
#include "config/config.h"

// Just throw in all the standard headers
#include <memory>
#include <utility>
#include <future>
#include <vector>
#include <map>
#include <unordered_map>
#include <thread>
#include <string>
#include <chrono>
#include <algorithm>
#include <functional>
#include <fstream>
#include <assert.h>
#include <mutex>
#include <deque>
#include <atomic>
#include <list>



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
