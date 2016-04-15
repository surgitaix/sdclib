/*
 * XercesDocumentWrapper.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef HELPER_XERCESDOCUMENTWRAPPER_H_
#define HELPER_XERCESDOCUMENTWRAPPER_H_

#include <memory>

#include <xercesc/dom/DOM.hpp>

#include "OSELib/fwd.h"
#include "OSELib/Helper/AutoRelease.h"

namespace OSELib {
namespace Helper {

class XercesDocumentWrapper {
public:
	static std::unique_ptr<XercesDocumentWrapper> create(const Message & msg);
	static std::unique_ptr<XercesDocumentWrapper> create(const Message & msg, const XercesGrammarPoolProvider & grammarPoolProvider);

	const xercesc::DOMDocument & getDocument() const;

private:
	using DocumentDeleter = AutoRelease<xercesc::DOMDocument>;

	XercesDocumentWrapper() = delete;
	XercesDocumentWrapper(std::unique_ptr<xercesc::DOMDocument, DocumentDeleter> document);

	static std::unique_ptr<xercesc::DOMDocument, DocumentDeleter> parseAndValidate(const std::string & source, const XercesGrammarPoolProvider & grammarPoolProvider);

	std::unique_ptr<xercesc::DOMDocument, DocumentDeleter> _document;
};

} /* namespace Helper */
} /* namespace OSELib */

#endif /* HELPER_XERCESDOCUMENTWRAPPER_H_ */
