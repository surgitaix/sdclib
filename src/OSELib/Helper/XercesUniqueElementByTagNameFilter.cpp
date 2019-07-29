/*
 * XercesUniqueElementByTagNameFilter.cpp
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#include <stdexcept>

#include "OSELib/Helper/XercesDocumentWrapper.h"
#include "OSELib/Helper/XercesUniqueElementByTagNameFilter.h"

#include <xercesc/dom/DOM.hpp>

namespace OSELib {
namespace Helper {

XercesUniqueElementByTagNameFilter::XercesUniqueElementByTagNameFilter(const XercesDocumentWrapper & document) :
	_document(document)
{
}

const xercesc::DOMElement * XercesUniqueElementByTagNameFilter::apply(const std::string & ns, const std::string & elementName) {
	XMLCh tempNS[100];
	XMLCh tempName[100];

	if (ns.size() >= 100 || elementName.size() >= 100) {
		throw std::runtime_error("Buffer size insufficient");
	}

	using namespace xercesc;

	XMLString::transcode(ns.c_str(), tempNS, 99);
	XMLString::transcode(elementName.c_str(), tempName, 99);

	 if (DOMNodeList * filterResults = _document.getDocument().getElementsByTagNameNS(tempNS, tempName)) {
		 if (filterResults->getLength() == 1) {
			 return dynamic_cast<const xercesc::DOMElement *>(filterResults->item(0));
		 }
	 }

	 return nullptr;
}

} /* namespace Helper */
} /* namespace OSELib */
