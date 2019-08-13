/*
 * XercesUniqueElementByTagNameFilter.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef HELPER_XERCESUNIQUEELEMENTBYTAGNAMEFILTER_H_
#define HELPER_XERCESUNIQUEELEMENTBYTAGNAMEFILTER_H_

#include <string>

#include "OSELib/fwd.h"

namespace XERCES_CPP_NAMESPACE
{
    class DOMElement;
}

namespace OSELib {
namespace Helper {

class XercesUniqueElementByTagNameFilter {
public:
	XercesUniqueElementByTagNameFilter(const XercesDocumentWrapper & document);

	const xercesc::DOMElement * apply(const std::string & ns, const std::string & elementName);

private:
	const XercesDocumentWrapper & _document;
};

} /* namespace Helper */
} /* namespace OSELib */

#endif /* HELPER_XERCESUNIQUEELEMENTBYTAGNAMEFILTER_H_ */
