#include "SDCLib/SSLHandler.h"

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
using namespace SDCLib::SSL;

using namespace Poco::Net;


SSLHandler::SSLHandler()
{
    
}


SSLHandler::~SSLHandler()
{
    _cleanup();
    
}

void SSLHandler::_cleanup()
{
    // Nothing to cleanup
    if (!isInit()) {
        return;
    }
    
    Poco::Net::uninitializeSSL();
    
    // Lock
    //std::lock_guard<std::mutex> t_lock(m_mutex);

    // ...Cleanup....

}

bool SSLHandler::init()
{
    if (isInit()) {
        return false;
    }
    
    try {
        Poco::Net::initializeSSL();
        Poco::SharedPtr<PrivateKeyPassphraseHandler> pConsoleHandler = new Poco::Net::KeyConsoleHandler(true);
        Poco::SharedPtr<InvalidCertificateHandler> pInvalidCertHandler = new Poco::Net::ConsoleCertificateHandler(true);
        m_context = new Context(Context::SERVER_USE, "userkey.pem", "sdccert.pem", "cacert.pem", Context::VERIFY_STRICT, 9, false, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
        SSLManager::instance().initializeServer(pConsoleHandler, pInvalidCertHandler, m_context);
    }
    catch(...)
    {
        return false;
    }
    
    // Important!
    m_context->enableExtendedCertificateVerification(false);

    m_init = true;
    return true;
}
bool SSLHandler::addCertificateAuthority(const std::string& p_file)
{
    assert(!p_file.empty());
    if(m_context == nullptr) {
        return false;
    }
    
    try {
        m_context->addCertificateAuthority(X509Certificate(p_file));
        return true;
    }
    catch(...)
    {
        return false;
    }
    
    return false;
}
bool SSLHandler::useCertificate(const std::string& p_file)
{
    assert(!p_file.empty());
    if(m_context == nullptr) {
        return false;
    }
    
    try {
        m_context->useCertificate(X509Certificate(p_file));
        return true;
    }
    catch(...)
    {
        return false;
    }
    return false;
}
bool SSLHandler::addChainCertificate(const std::string& p_file)
{
    assert(!p_file.empty());
    if(m_context == nullptr) {
        return false;
    }

    try {
        m_context->addChainCertificate(X509Certificate(p_file));
        return true;
    }
    catch(...)
    {
        return false;
    }
    return false;
}
bool SSLHandler::useKeyFiles(const std::string& p_publicKey, const std::string& p_privateKey, const std::string& p_pasphrase)
{
    if(m_context == nullptr) {
        return false;
    }
    
    try {
        m_context->usePrivateKey(Poco::Crypto::RSAKey(p_publicKey, p_privateKey, p_pasphrase));
        return true;
    }
    catch(...)
    {
        return false;
    }
    return false;
}
