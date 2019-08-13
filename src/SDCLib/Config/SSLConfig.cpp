#include "SDCLib/Config/SSLConfig.h"

#include "SDCLib/SDCInstance.h"

#include <Poco/StreamCopier.h>
#include <Poco/URI.h>
#include <Poco/Exception.h>
#include <Poco/SharedPtr.h>
#include <Poco/Net/SSLManager.h>
#include <Poco/Net/KeyConsoleHandler.h>
#include <Poco/Net/ConsoleCertificateHandler.h>
#include <Poco/Net/PrivateKeyPassphraseHandler.h>
#include <Poco/Crypto/X509Certificate.h>
#include <Poco/Net/SSLException.h>

#include <iostream>

using namespace SDCLib;
using namespace SDCLib::Config;

using namespace Poco::Net;


bool SSLConfig::init(const Poco::Net::Context::VerificationMode p_modeClient, const Poco::Net::Context::VerificationMode p_modeServer)
{
    if (isInit()) {
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
        Poco::SharedPtr<PrivateKeyPassphraseHandler> pConsoleHandler = new Poco::Net::KeyConsoleHandler(false);
        Poco::SharedPtr<InvalidCertificateHandler> pInvalidCertHandler = new Poco::Net::ConsoleCertificateHandler(false);
        m_context_client = new Context(Context::TLSV1_2_CLIENT_USE, "","","", p_mode, 9, false, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");

        SSLManager::instance().initializeClient(pConsoleHandler, pInvalidCertHandler, m_context_client);
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
        Poco::SharedPtr<PrivateKeyPassphraseHandler> pConsoleHandler = new Poco::Net::KeyConsoleHandler(true);
        Poco::SharedPtr<InvalidCertificateHandler> pInvalidCertHandler = new Poco::Net::ConsoleCertificateHandler(true);
        m_context_server = new Context(Context::TLSV1_2_SERVER_USE, "","","", p_mode, 9, false, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");

        SSLManager::instance().initializeServer(pConsoleHandler, pInvalidCertHandler, m_context_server);
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
    catch(...)
    {
        return false;
    }
    return false;
}
