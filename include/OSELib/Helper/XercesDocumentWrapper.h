/*
 * XercesDocumentWrapper.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 10.06.2022, baumeister
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
            std::unique_ptr<xercesc::DOMDocument, DocumentDeleter> m_document{nullptr};

        public:
            XercesDocumentWrapper() = delete;  // Private Constructor via static create member function
            ~XercesDocumentWrapper() = default;

            static std::unique_ptr<XercesDocumentWrapper> create(const Message&);
            static std::unique_ptr<XercesDocumentWrapper> create(const Message&, const XercesGrammarPoolProvider&);

            const xercesc::DOMDocument& getDocument() const;

        private:
            XercesDocumentWrapper(std::unique_ptr<xercesc::DOMDocument, DocumentDeleter>);

            static std::unique_ptr<xercesc::DOMDocument, DocumentDeleter> parseAndValidate(const std::string& p_source,
                                                                                           const XercesGrammarPoolProvider&);
        };
    }  // namespace Helper
}  // namespace OSELib

#endif
