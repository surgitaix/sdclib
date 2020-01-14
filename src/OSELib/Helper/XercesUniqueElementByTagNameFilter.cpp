/*
 * XercesUniqueElementByTagNameFilter.cpp
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#include "OSELib/Helper/XercesUniqueElementByTagNameFilter.h"
#include "OSELib/Helper/XercesDocumentWrapper.h"

#include <stdexcept>
#include <xercesc/dom/DOM.hpp>

namespace OSELib {
namespace Helper {

XercesUniqueElementByTagNameFilter::XercesUniqueElementByTagNameFilter(const XercesDocumentWrapper & p_document)
: m_document(p_document)
{ }

const xercesc::DOMElement * XercesUniqueElementByTagNameFilter::apply(const std::string & p_ns, const std::string & p_elementName)
{
	XMLCh t_tempNS[100];
	XMLCh t_tempName[100];

	if (p_ns.size() >= 100 || p_elementName.size() >= 100) {
		throw std::runtime_error("Buffer size insufficient");
	}

	using namespace xercesc;

	XMLString::transcode(p_ns.c_str(), t_tempNS, 99);
	XMLString::transcode(p_elementName.c_str(), t_tempName, 99);

	 if (DOMNodeList * filterResults = m_document.getDocument().getElementsByTagNameNS(t_tempNS, t_tempName)) {
		 if (filterResults->getLength() == 1) {
			 return dynamic_cast<const xercesc::DOMElement *>(filterResults->item(0));
		 }
	 }
	 return nullptr;
}

}
}
