#include "SDCLib/SSLHandler.h"

#include "SDCLib/SDCInstance.h"

#include <Poco/StreamCopier.h>
#include <Poco/URI.h>
#include <Poco/Exception.h>
#include <Poco/SharedPtr.h>
#include <Poco/Net/SSLManager.h>
#include <Poco/Net/KeyConsoleHandler.h>
#include <Poco/Net/ConsoleCertificateHandler.h>
#include <Poco/Crypto/X509Certificate.h>

#include <iostream>

using namespace SDCLib;
using namespace SDCLib::SSL;

using namespace Poco::Net;

SSLHandler::SSLHandler()
{
    Poco::Net::initializeSSL();
}


SSLHandler::~SSLHandler()
{
    _cleanup();
    Poco::Net::uninitializeSSL();
}

void SSLHandler::_cleanup()
{
    // Nothing to cleanup
    if (!isInit()) {
        return;
    }
    // Lock
    //std::lock_guard<std::mutex> t_lock(m_mutex);

    // ...Cleanup....

}

bool SSLHandler::init()
{
    if (isInit()) {
        return false;
    }
    
    int t_depth = 9;
    
    Poco::SharedPtr<InvalidCertificateHandler> ptrCert = new ConsoleCertificateHandler(false);
    m_context = new Context(Poco::Net::Context::SERVER_USE,
                                          "/home/fabian/SurgiTAIX/SDC/devicelib/build/bin/",
                                          Context::VERIFY_STRICT,
                                          t_depth,
                                          false);
    
    m_context->usePrivateKey(X509Certificate("privkey.pem"));
    m_context->addChainCertificate(X509Certificate("testleafcert.pem"));
    m_context->useCertificate(X509Certificate("testroot.pem"));
    
    
    SSLManager::instance().initializeServer(0, ptrCert, m_context);
    
    // ...

    m_init = true;
    return true;
}
