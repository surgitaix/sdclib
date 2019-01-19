/* Prerequisites of SDCLib
 *
 * (c)2018 Fabian Baumeister
 *
 *
 */
#ifndef SDCLIBRARY_SDCLIB_PREREQUISITES_H
#define SDCLIBRARY_SDCLIB_PREREQUISITES_H

// Config
#include "config/config.h"
#include <memory>
#include <vector>
// Note: Define these to have some cleaner code, easier handling with smart pointers, predeclaration of classes etc.
// Expand as need arises


// ##SessionLib
namespace SDCLib
{
    // Some using for better handling
    class SDCInstance;
    using SDCInstancePtr = std::shared_ptr<SDCInstance>;


    namespace Data {
            namespace SDC {
                class SDCConsumer;
                using ConsumerPtrList = std::vector<std::unique_ptr<SDCConsumer> >;
            }
    }

}



#endif
