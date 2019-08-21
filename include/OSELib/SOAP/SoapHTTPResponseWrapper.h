/*
 * SoapHTTPResponseWrapper.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#ifndef OSELIB_SOAP_SOAPHTTPRESPONSEWRAPPER_H_
#define OSELIB_SOAP_SOAPHTTPRESPONSEWRAPPER_H_

#include "OSELib/fwd.h"
#include "OSELib/Helper/WithLogger.h"

#include <Poco/Net/HTTPResponse.h>

namespace OSELib
{
	namespace SOAP
	{
		class SoapHTTPResponseWrapper : public OSELib::Helper::WithLogger
		{
		public:
			using HTTPStatus = Poco::Net::HTTPResponse::HTTPStatus;
		private:
			Poco::Net::HTTPServerResponse & m_httpResponse;

			const HTTPStatus m_httpStatus;
		public:

			SoapHTTPResponseWrapper(Poco::Net::HTTPServerResponse & p_httpResponse, HTTPStatus p_httpStatus = HTTPStatus::HTTP_OK);
			// Special Member Functions
			SoapHTTPResponseWrapper(const SoapHTTPResponseWrapper& p_obj) = default;
			SoapHTTPResponseWrapper(SoapHTTPResponseWrapper&& p_obj) = default;
			SoapHTTPResponseWrapper& operator=(const SoapHTTPResponseWrapper& p_obj) = default;
			SoapHTTPResponseWrapper& operator=(SoapHTTPResponseWrapper&& p_obj) = default;
			~SoapHTTPResponseWrapper() = default;

			void send(const std::string & p_content);
		};
	}
}

#endif
