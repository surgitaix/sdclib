#include "SDCLib/Config/SSLConfig.h"

#include "SDCLib/SDCInstance.h"
#include "config/config.h"

#include <Poco/SharedPtr.h>
#include <Poco/Net/SSLManager.h>
#include <Poco/Net/KeyFileHandler.h>
#include <Poco/Net/RejectCertificateHandler.h>
#include <Poco/Net/PrivateKeyPassphraseHandler.h>
#include <Poco/Crypto/X509Certificate.h>
#include <Poco/Net/SSLException.h>

// IDEA: Maybe add to an abstraction layer, to enable other SSL implementations such as Wolf or Boring
#include <openssl/ssl.h>
#include <openssl/crypto.h>



#include <iostream>

using namespace SDCLib;
using namespace SDCLib::Config;

SSLConfig::SSLConfig(const SSLConfig& p_obj) 
{
	m_init = p_obj.isInit();
	m_context_client = p_obj.m_context_client;
	m_context_server = p_obj.m_context_server;
}

bool SSLConfig::init(const Poco::Net::Context::VerificationMode p_modeClient, const Poco::Net::Context::VerificationMode p_modeServer)
{
    if (isInit()) {
        return false;
    }

    if(!openSSLVersionCheck()) {
    	return false;
    }

    // Init All SSL related Handlers
    Poco::Net::initializeSSL();

    try {
        if(!_initClientSide(p_modeClient)) { return false; }
        if(!_initServerSide(p_modeServer)) { return false; }
    }
    catch(...)
    {
        return false;
    }

    // Lock
    std::lock_guard<std::mutex> t_lock(m_mutex);

    // Important!
    m_context_client->enableExtendedCertificateVerification(false);
    m_context_server->enableExtendedCertificateVerification(false);

    m_init = true;
    return true;
}

bool SSLConfig::_initClientSide(const Poco::Net::Context::VerificationMode p_mode)
{
    try {
        Poco::SharedPtr<Poco::Net::PrivateKeyPassphraseHandler> t_privateHandler = new Poco::Net::KeyFileHandler(false);
        Poco::SharedPtr<Poco::Net::InvalidCertificateHandler> t_invalidCertHandler = new Poco::Net::RejectCertificateHandler(false);
        m_context_client = new Poco::Net::Context(Poco::Net::Context::TLSV1_2_CLIENT_USE, "","","", p_mode, 9, false, CIPHERSTRING);

        // Workarounds, Migitations and Countermeasures
        // Enable all built-in workarounds
        SSL_CTX_set_options(m_context_client->sslContext(), SSL_OP_ALL);

        // Disable everything except TLS 1.2 and higher
        SSL_CTX_set_options(m_context_client->sslContext(), SSL_OP_NO_SSLv2);
        SSL_CTX_set_options(m_context_client->sslContext(), SSL_OP_NO_SSLv3);
        SSL_CTX_set_options(m_context_client->sslContext(), SSL_OP_NO_TLSv1);
        SSL_CTX_set_options(m_context_client->sslContext(), SSL_OP_NO_TLSv1_1);

        // Disable compression
        SSL_CTX_set_options(m_context_client->sslContext(), SSL_OP_NO_COMPRESSION);

        Poco::Net::SSLManager::instance().initializeClient(t_privateHandler, t_invalidCertHandler, m_context_client);
        return true;
    }
    catch(...) {
        std::cout << "SSLHandler: Failed to init Server Side!" << std::endl;
    }
    return false;
}
bool SSLConfig::_initServerSide(const Poco::Net::Context::VerificationMode p_mode)
{
    try {
        Poco::SharedPtr<Poco::Net::PrivateKeyPassphraseHandler> t_privateHandler = new Poco::Net::KeyFileHandler(true);
        Poco::SharedPtr<Poco::Net::InvalidCertificateHandler> t_invalidCertHandler = new Poco::Net::RejectCertificateHandler(true);
        m_context_server = new Poco::Net::Context(Poco::Net::Context::TLSV1_2_SERVER_USE, "","","", p_mode, 9, false, CIPHERSTRING);

        // Workarounds, migitations and countermeasures
        // Enable all built-in workarounds
        SSL_CTX_set_options(m_context_server->sslContext(), SSL_OP_ALL);

        // Disable everything except TLS 1.2 and higher
        SSL_CTX_set_options(m_context_server->sslContext(), SSL_OP_NO_SSLv2);
        SSL_CTX_set_options(m_context_server->sslContext(), SSL_OP_NO_SSLv3);
        SSL_CTX_set_options(m_context_server->sslContext(), SSL_OP_NO_TLSv1);
        SSL_CTX_set_options(m_context_server->sslContext(), SSL_OP_NO_TLSv1_1);

        // Disable compression. Only has to be configured on server side
        SSL_CTX_set_options(m_context_client->sslContext(), SSL_OP_NO_COMPRESSION);

        // Start a new session on renegotiation, preventing Triple Handshake and Renegotiation Attack (server only)
        SSL_CTX_set_options(m_context_server->sslContext(), SSL_OP_NO_SESSION_RESUMPTION_ON_RENEGOTIATION);

        Poco::Net::SSLManager::instance().initializeServer(t_privateHandler, t_invalidCertHandler, m_context_server);
        return true;
    }
    catch(...) {
        std::cout << "SSLHandler: Failed to init Server Side!" << std::endl;
    }
    return false;
}

bool SSLConfig::addCertificateAuthority(const std::string& p_file, bool p_clientSide, bool p_serverSide)
{
    assert(!p_file.empty());
    if(!isInit()) {
        return false;
    }
    // Lock
    std::lock_guard<std::mutex> t_lock(m_mutex);
    try {
        if(p_clientSide) { m_context_client->addCertificateAuthority(Poco::Net::X509Certificate(p_file)); }
        if(p_serverSide) { m_context_server->addCertificateAuthority(Poco::Net::X509Certificate(p_file)); }
        return true;
    }
    catch(...)
    {
        return false;
    }
    return false;
}
bool SSLConfig::useCertificate(const std::string& p_file, bool p_clientSide, bool p_serverSide)
{
    assert(!p_file.empty());
    if(!isInit()) {
        return false;
    }
    // Lock
    std::lock_guard<std::mutex> t_lock(m_mutex);
    try {
        if(p_clientSide) { m_context_client->useCertificate(Poco::Net::X509Certificate(p_file)); }
        if(p_serverSide) { m_context_server->useCertificate(Poco::Net::X509Certificate(p_file)); }
        return true;
    }
    catch(...)
    {
        return false;
    }
    return false;
}
bool SSLConfig::addChainCertificate(const std::string& p_file, bool p_clientSide, bool p_serverSide)
{
    assert(!p_file.empty());
    if(!isInit()) {
        return false;
    }
    // Lock
    std::lock_guard<std::mutex> t_lock(m_mutex);
    try {
        if(p_clientSide) { m_context_client->addChainCertificate(Poco::Net::X509Certificate(p_file)); }
        if(p_serverSide) { m_context_server->addChainCertificate(Poco::Net::X509Certificate(p_file)); }
        return true;
    }
    catch(...)
    {
        return false;
    }
    return false;
}
bool SSLConfig::useKeyFiles(const std::string& p_publicKey, const std::string& p_privateKey, const std::string& p_pasphrase, bool p_clientSide, bool p_serverSide)
{
    if(!isInit()) {
        return false;
    }
    // Lock
    std::lock_guard<std::mutex> t_lock(m_mutex);
    try {
        if(p_clientSide) { m_context_client->usePrivateKey(Poco::Crypto::RSAKey(p_publicKey, p_privateKey, p_pasphrase)); }
        if(p_serverSide) { m_context_server->usePrivateKey(Poco::Crypto::RSAKey(p_publicKey, p_privateKey, p_pasphrase)); }
        return true;
    }
    catch(Poco::Net::SSLContextException& e)
    {
    	std::cout << "SSLContextException in useKeyFiles: " << e.message() << "\n";
    	std::cout << "Hint: Call useKeyFiles after adding the chain Certificate via useCertificate.\n";
    	std::cout << "      To add multiple certificates call useCertificate(...); useKeyFiles(...); pairwise." << std::endl;
        return false;
    }
    catch(...)
    {
        return false;
    }
    return false;
}

bool SSLConfig::openSSLVersionCheck()
{
	/*
	 * Returns the current version as unsigned long int.
	 * Format:
	 * -
	 */
	unsigned long t_openSSLVersion = OpenSSL_version_num();

	const unsigned long t_majorBitmask =  0b11110000000000000000000000000000;
	const unsigned long t_minorBitmask =  0b00001111111100000000000000000000;
	const unsigned long t_fixBitmask =    0b00000000000011111111000000000000;
	const unsigned long t_patchBitmask =  0b00000000000000000000111111110000;
	const unsigned long t_statusBitmask = 0b00000000000000000000000000001111;

	unsigned long t_majorVersion = (t_openSSLVersion & t_majorBitmask) >> 28;
	unsigned long t_minorVersion = (t_openSSLVersion & t_minorBitmask) >> 20;
	unsigned long t_fixVersion = (t_openSSLVersion & t_fixBitmask ) >> 12;
	unsigned long t_patchVersion = (t_openSSLVersion & t_patchBitmask) >> 4;
	unsigned long t_status = (t_openSSLVersion & t_statusBitmask);

	bool t_versionCheckResult = false;

	if(t_majorVersion > SDC_MINIMAL_OPENSSL_VERSION_MAJOR)
	{
		t_versionCheckResult = true;
	}
	else if(t_majorVersion == SDC_MINIMAL_OPENSSL_VERSION_MAJOR)
	{
		// Proceed to next layer
		if(t_minorVersion > SDC_MINIMAL_OPENSSL_VERSION_MINOR)
		{
			t_versionCheckResult = true;
		}
		else if(t_minorVersion == SDC_MINIMAL_OPENSSL_VERSION_MINOR)
		{
			// Proceed to next layer
			if(t_fixVersion > SDC_MINIMAL_OPENSSL_VERSION_FIX)
			{
				t_versionCheckResult = true;
			}
			else if(t_fixVersion == SDC_MINIMAL_OPENSSL_VERSION_FIX)
			{
				// Proceed to next layer
				// Here we check, if it is greater or equal
				if(t_patchVersion >= SDC_MINIMAL_OPENSSL_VERSION_PATCH)
				{
					t_versionCheckResult = true;
				}
			}
		}
	}

	// Evaluate
	if(!t_versionCheckResult)
	{
		std::cout << "SSLHandler: Version check failed. SDCLib requires OpenSSL version "
				  << std::to_string(SDC_MINIMAL_OPENSSL_VERSION_MAJOR) << "."
				  << std::to_string(SDC_MINIMAL_OPENSSL_VERSION_MINOR) << "."
				  << std::to_string(SDC_MINIMAL_OPENSSL_VERSION_FIX) << " "
				  << std::to_string(SDC_MINIMAL_OPENSSL_VERSION_PATCH)
			      << std::endl;
		return false;
	}

	// Status nibble indicates the status of the installed OpenSSL version. 0: Development, 1-14: Beta, 15: Release
	// If a version other than release is used, issue a warning.
	if(t_status != 15)
	{
		std::cout << "SSLHandler: Warning! You are not using a release version of OpenSSl. Consider to update to the latest version!" << std::endl;
	}

	return true;
}
