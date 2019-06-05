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
 *  @file SSLHandler.h
 *  @project SDCLib
 *  @date 14.02.2019
 *  @author baumeister
 *  @copyright (c) SurgiTAIX AG
 *
 */
#ifndef SDCLIB_SSL_SSLHANDLER_H
#define SDCLIB_SSL_SSLHANDLER_H

#include "Prerequisites.h"
#include "config/config.h"


namespace Poco {
    namespace Net {
        class Context;
    }
}

namespace SDCLib
{
    namespace SSL
    {
        class SSLHandler
        {
        private:

            std::atomic<bool> m_init = ATOMIC_VAR_INIT(false);
        
            Poco::Net::Context* m_context = nullptr;

        public:

            SSLHandler();

            // Special Member Functions
            SSLHandler(const SSLHandler& p_obj) = delete;
            SSLHandler(SSLHandler&& p_obj) = delete;
            SSLHandler& operator=(const SSLHandler& p_obj) = delete;
            SSLHandler& operator=(SSLHandler&& p_obj) = delete;
            ~SSLHandler();

            bool init();
            bool isInit() const { return m_init; }
            
            Poco::Net::Context* getContext() { return m_context; }
            
            bool addCertificateAuthority(const std::string& p_file);
            bool useCertificate(const std::string& p_file);
            bool useKeyFiles(const std::string& p_publicKey, const std::string& p_privateKey, const std::string& p_pasphrase);

        private:

            void _cleanup();

        };
    }
}

#endif
