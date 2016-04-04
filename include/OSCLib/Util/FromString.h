/*
 * FromString.h
 *
 *  Created on: 13.10.2014
 *      Author: roehser
 */

#ifndef FROMSTRING_H_
#define FROMSTRING_H_

#include "OSCLib/Data/OSCP/OSCPConstants.h"
#include "OSCLib/Util/DebugOut.h"
#include "osdm-fwd.hxx"

#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLUniDefs.hpp> 

#include <memory>
#include <string>

namespace OSCLib {
	class OSCLibrary;
}

namespace CDM {

class FromString {
	friend class OSCLib::OSCLibrary;
public:
	FromString();
	virtual ~FromString();

	template <class ReturnType>
	static std::unique_ptr<ReturnType> validateAndConvert(const std::string & source) {
		try {
			std::unique_ptr<xercesc::DOMDocument, DocDeleter> doc (parseAndValidate(source));
			if (doc == nullptr) {
				return nullptr;
			} else {
				return FromString::convert<ReturnType>(*doc);
			}
		} catch (...) {
			OSCLib::Util::DebugOut(OSCLib::Util::DebugOut::Error, std::cout, "FromString") << "Parsing failed with unknown error." << std::endl;
		}
		return nullptr;
	}

private:
	struct DocDeleter {
		void operator()(xercesc::DOMDocument* d) { d->release(); }
	};

	struct ParserDeleter {
		void operator()(xercesc::DOMLSParser* b) { b->release(); }
	};

	static xercesc::DOMLSParser * createParser();

	static std::unique_ptr<xercesc::DOMDocument, DocDeleter> parseAndValidate(const std::string & source);

	template <class ReturnType>
	static std::unique_ptr<ReturnType> convert(const xercesc::DOMDocument & source);
};

} /* namespace OSCLib */

#endif /* FROMSTRING_H_ */
