/*
 * CommonSoapPreprocessing.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#ifndef OSELIB_SOAP_COMMONSOAPPREPROCESSING_H_
#define OSELIB_SOAP_COMMONSOAPPREPROCESSING_H_

#include "OSELib/fwd.h"
#include "OSELib/Helper/WithLogger.h"

#include "OSELib/Helper/Message.h"
#include "OSELib/Helper/XercesDocumentWrapper.h"

#include "NormalizedMessageModel.hxx"

namespace OSELib
{
	namespace SOAP
	{
		class CommonSoapPreprocessing : public OSELib::Helper::WithLogger
		{
		private:
			Helper::XercesGrammarPoolProvider & m_grammarProvider;

		public:

			// fixme move all exception definitions to a common file so the are not scattered around the classes
			// fixme catch all exceptions in the HTTPRequestHandlerExceptionTrap appropriately (use inheritance of exceptions)
			class SoapFaultException : public std::exception {
			};

			CommonSoapPreprocessing(Helper::XercesGrammarPoolProvider & p_grammarProvider);
			// Special Member Functions
			CommonSoapPreprocessing(const CommonSoapPreprocessing& p_obj) = default;
			CommonSoapPreprocessing(CommonSoapPreprocessing&& p_obj) = default;
			CommonSoapPreprocessing& operator=(const CommonSoapPreprocessing& p_obj) = default;
			CommonSoapPreprocessing& operator=(CommonSoapPreprocessing&& p_obj) = default;
			~CommonSoapPreprocessing() = default;

			void parse(std::istream & p_request);
			void parse(const std::string & p_request);

			std::unique_ptr<const Helper::Message> rawMessage = nullptr;
			std::unique_ptr<const Helper::XercesDocumentWrapper> xercesDocument = nullptr;
			std::unique_ptr<MESSAGEMODEL::Envelope> normalizedMessage = nullptr;

		private:
			void commonParsing();

		};
	}
}

#endif
