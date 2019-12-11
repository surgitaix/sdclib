/**
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  *
  */

/**
 *  @file SDCLibrary.h
 *  @project SDCLib
 *  @date 24.08.2011
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 *
 */

#ifndef SDCLIB_SDCLIBRARY_H_
#define SDCLIB_SDCLIBRARY_H_

#include <atomic>
#include <memory>
#include <string>
#include <mutex>

#include "OSELib/fwd.h"
#include "OSELib/Helper/WithLogger.h"

namespace SDCLib
{
    class SDCLibrary final : public OSELib::Helper::WithLogger
    {
    private:

        std::atomic<bool> m_initialized{false};

    public:

        // Special Member Functions
        SDCLibrary();
        SDCLibrary(const SDCLibrary& p_obj) = delete;
        SDCLibrary(SDCLibrary&& p_obj) = delete;
        SDCLibrary& operator=(const SDCLibrary& p_obj) = delete;
        SDCLibrary& operator=(SDCLibrary&& p_obj) = delete;
        ~SDCLibrary();

        static SDCLibrary& getInstance();

        /**
        * Startup framework.
        *
        * @param debugLevel The debug output level.
        */
        void startup(OSELib::LogLevel p_debugLevel = OSELib::LogLevel::Error);

        /**
        * Shutdown framework.
        *
        */
        void shutdown() { }

        bool isInitialized() const
        {
        	return m_initialized;
        }
    };

}

#endif
