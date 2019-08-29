/*
 * HTTPClientSessionWrapper.h
 *
 *  Created on: Aug 29, 2019
 *      Author: sebastian
 */

#ifndef INCLUDE_OSELIB_HTTP_HTTPCLIENTSESSIONWRAPPER_H_
#define INCLUDE_OSELIB_HTTP_HTTPCLIENTSESSIONWRAPPER_H_

#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/HTTPResponse.h"


namespace OSELib {
namespace HTTP {

class HTTPClientSessionWrapper : public Poco::Net::HTTPClientSession {
public:

	using HTTPClientSession::HTTPClientSession;
	std::istream& receiveResponse(Poco::Net::HTTPResponse& response) override;

private:
};

}
}


#endif /* INCLUDE_OSELIB_HTTP_HTTPCLIENTSESSIONWRAPPER_H_ */
