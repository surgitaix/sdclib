#include "OSELib/HTTP/HTTPRequestHandlerFactory.h"

using namespace OSELib;
using namespace OSELib::HTTP;

HTTPRequestHandlerFactory::HTTPRequestHandlerFactory(Poco::Net::HTTPRequestHandlerFactory* p_factory)
: m_factory(p_factory)
{

}
