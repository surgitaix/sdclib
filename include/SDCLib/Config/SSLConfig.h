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
 *  @file SSLConfig.h
 *  @project SDCLib
 *  @date 02.07.2019
 *  @author baumeister
 *  @copyright (c) SurgiTAIX AG
 *
 */
#ifndef SDCLIB_CONFIG_SSLCONFIG_H
#define SDCLIB_CONFIG_SSLCONFIG_H

#include "Prerequisites.h"
#include "config/config.h"

#include <Poco/Net/Context.h>

namespace SDCLib
{
    namespace Config
    {
        class SSLConfig
        {
        private:

            std::mutex m_mutex;

            // Poco does not allow OpenSSL SSLv23_method(). One Context for Client and one for Server Side.
            std::atomic<bool> m_init = ATOMIC_VAR_INIT(false);
            Poco::Net::Context::Ptr m_context_client = nullptr;
            Poco::Net::Context::Ptr m_context_server = nullptr;

        public:

            // Special Member Functions
            SSLConfig() = default;
            SSLConfig(const SSLConfig& p_obj) = delete;
            SSLConfig(SSLConfig&& p_obj) = delete;
            SSLConfig& operator=(const SSLConfig& p_obj) = delete;
            SSLConfig& operator=(SSLConfig&& p_obj) = delete;
            ~SSLConfig() = default;

            bool init(const Poco::Net::Context::VerificationMode p_modeClient = Poco::Net::Context::VERIFY_RELAXED, const Poco::Net::Context::VerificationMode p_modeServer = Poco::Net::Context::VERIFY_RELAXED);
            bool isInit() const { return m_init; }

            Poco::Net::Context::Ptr getClientContext() const { return m_context_client; }
            Poco::Net::Context::Ptr getServerContext() const { return m_context_server; }

            // Applied to both contexts
            bool addCertificateAuthority(const std::string& p_file, bool p_clientSide = true, bool p_serverSide = true);
            bool useCertificate(const std::string& p_file, bool p_clientSide = true, bool p_serverSide = true);
            bool addChainCertificate(const std::string& p_file, bool p_clientSide = true, bool p_serverSide = true);
            bool useKeyFiles(const std::string& p_publicKey, const std::string& p_privateKey, const std::string& p_pasphrase, bool p_clientSide = true, bool p_serverSide = true);

        private:

            bool _initClientSide(const Poco::Net::Context::VerificationMode p_mode);
            bool _initServerSide(const Poco::Net::Context::VerificationMode p_mode);
        };
    }
}

#endif
