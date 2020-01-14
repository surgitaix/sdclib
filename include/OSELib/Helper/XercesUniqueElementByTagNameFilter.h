/*
 * XercesUniqueElementByTagNameFilter.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#ifndef OSELIB_HELPER_XERCESUNIQUEELEMENTBYTAGNAMEFILTER_H_
#define OSELIB_HELPER_XERCESUNIQUEELEMENTBYTAGNAMEFILTER_H_

#include "OSELib/fwd.h"

#include <string>

namespace XERCES_CPP_NAMESPACE
{
    class DOMElement;
}

namespace OSELib
{
	namespace Helper
	{
		class XercesUniqueElementByTagNameFilter
		{
		private:
			const XercesDocumentWrapper & m_document;

		public:
			XercesUniqueElementByTagNameFilter(const XercesDocumentWrapper & p_document);

			const xercesc::DOMElement * apply(const std::string & p_ns, const std::string & p_elementName);
		};
	}
}

#endif
