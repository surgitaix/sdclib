/*
 * SoapHTTPResponseWrapper.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef SOAP_SOAPHTTPRESPONSEWRAPPER_H_
#define SOAP_SOAPHTTPRESPONSEWRAPPER_H_

#include "Poco/Net/HTTPServerResponse.h"

#include "OSELib/Helper/WithLogger.h"

namespace OSELib {
namespace SOAP {

class SoapHTTPResponseWrapper : public OSELib::Helper::WithLogger
{
public:
	using HTTPStatus = Poco::Net::HTTPServerResponse::HTTPStatus;

	SoapHTTPResponseWrapper(
			Poco::Net::HTTPServerResponse & httpResponse,
			HTTPStatus httpStatus = HTTPStatus::HTTP_OK);

	void send(const std::string & content);

private:
	Poco::Net::HTTPServerResponse & _httpResponse;
	const HTTPStatus _httpStatus;
};

} /* namespace SOAP */
} /* namespace OSELib */

#endif /* SOAP_SOAPHTTPRESPONSEWRAPPER_H_ */
