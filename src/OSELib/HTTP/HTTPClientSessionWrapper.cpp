/*
 * HTTPClientSessionWrapper.cpp
 *
 *  Created on: Aug 29, 2019
 *      Author: rosenau
 */

#include "OSELib/HTTP/HTTPClientSessionWrapper.h"
#include "OSELib/TCP/TCPBroadcastServerHandler.h"
#include "Poco/Net/HTTPHeaderStream.h"
#include "Poco/Net/HTTPStream.h"
#include "Poco/Net/HTTPFixedLengthStream.h"
#include "Poco/Net/HTTPChunkedStream.h"
#include "Poco/Exception.h"

using namespace Poco::Net;


namespace OSELib {
namespace HTTP {

std::istream& HTTPClientSessionWrapper::receiveResponse(HTTPResponse& response)
{
	flushRequest();
	if (!_responseReceived)
	{
		do
		{
			response.clear();
			HTTPHeaderInputStream his(*this);
			try
			{
				response.read(his);
			}
			catch (Poco::Exception&)
			{
				close();
				if (networkException())
					networkException()->rethrow();
				else
					throw;
				throw;
			}
		}
		while (response.getStatus() == HTTPResponse::HTTP_CONTINUE);
	}

	_mustReconnect = getKeepAlive() && !response.getKeepAlive();

	if (!_expectResponseBody || response.getStatus() < 200 || response.getStatus() == HTTPResponse::HTTP_NO_CONTENT || response.getStatus() == HTTPResponse::HTTP_NOT_MODIFIED)
		_pResponseStream = new HTTPFixedLengthInputStream(*this, 0);
	else if (response.getChunkedTransferEncoding())
		_pResponseStream = new HTTPChunkedInputStream(*this);
	else if (response.hasContentLength())
#if defined(POCO_HAVE_INT64)
		_pResponseStream = new HTTPFixedLengthInputStream(*this, response.getContentLength64());
#else
		_pResponseStream = new HTTPFixedLengthInputStream(*this, response.getContentLength());
#endif
	else
		_pResponseStream = new HTTPInputStream(*this);

	if(Network::TCPBroadcastServerHandler::getInstance("127.0.0.1", 8000)->isStarted())
	{
	    std::ostringstream ss;
	    ss << _pResponseStream->rdbuf();
	    std::string requestString = ss.str();
	    if(requestString != "")
			Network::TCPBroadcastServerHandler::getInstance("127.0.0.1", 5000)->broadcastMessage(requestString);
	    std::cout << "SENDING HERE!!!! THIS WORKS GREAT!!!!!" << std::endl;
		_hackyStream = new std::istringstream(requestString);
		return *_hackyStream;

	}
	return *_pResponseStream;
}

}
}

