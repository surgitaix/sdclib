/*
 * XercesDocumentWrapper.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#ifndef OSELIB_HELPER_XERCESDOCUMENTWRAPPER_H_
#define OSELIB_HELPER_XERCESDOCUMENTWRAPPER_H_

#include "OSELib/fwd.h"
#include "OSELib/Helper/AutoRelease.h"

#include <memory>

#include <xercesc/dom/DOM.hpp>

namespace OSELib
{
	namespace Helper
	{
		class XercesDocumentWrapper
		{
		private:
			using DocumentDeleter = AutoRelease<xercesc::DOMDocument>;
			std::unique_ptr<xercesc::DOMDocument, DocumentDeleter> m_document = nullptr;

		public:

			XercesDocumentWrapper() = delete; // Note: Private Constructor via static create member function
			// Special Member Functions
			XercesDocumentWrapper(const XercesDocumentWrapper& p_obj) = default;
			XercesDocumentWrapper(XercesDocumentWrapper&& p_obj) = default;
			XercesDocumentWrapper& operator=(const XercesDocumentWrapper& p_obj) = default;
			XercesDocumentWrapper& operator=(XercesDocumentWrapper&& p_obj) = default;
			~XercesDocumentWrapper() = default;

			static std::unique_ptr<XercesDocumentWrapper> create(const Message & p_msg);
			static std::unique_ptr<XercesDocumentWrapper> create(const Message & p_msg, const XercesGrammarPoolProvider & p_grammarPoolProvider);

			const xercesc::DOMDocument & getDocument() const;

		private:

			XercesDocumentWrapper(std::unique_ptr<xercesc::DOMDocument, DocumentDeleter> p_document);

			static std::unique_ptr<xercesc::DOMDocument, DocumentDeleter> parseAndValidate(const std::string & p_source, const XercesGrammarPoolProvider & p_grammarPoolProvider);

		};
	}
}

#endif
