/*
 * HelperMethods.h
 *
 *  Created on: Jan 22, 2019
 *      Author: sebastian
 */

#ifndef CTESTCASES_TOOLS_HELPERMETHODS_H_
#define CTESTCASES_TOOLS_HELPERMETHODS_H_

#include "osdm.hxx"
#include "OSELib/DPWS/DPWS11Constants.h"

#include "OSCLib/Data/SDC/SDCProvider.h"
#include "OSCLib/Data/SDC/MDIB/custom/MdibContainer.h"
#include "OSCLib/Data/SDC/MDIB/ConvertToCDM.h"


using namespace SDCLib;
using namespace SDCLib::Data::SDC;

namespace TestTools {

static const std::string getStringRepresentationOfMDIB(const MdibContainer MDIB) {
	MDM::GetMdibResponse MdibResponse(xml_schema::Uri("0"),ConvertToCDM::convert(MDIB));
	MdibResponse.MdibVersion(MDIB.getMdibVersion());
	const xml_schema::Flags xercesFlags(xml_schema::Flags::dont_validate | xml_schema::Flags::no_xml_declaration | xml_schema::Flags::dont_initialize);
	xml_schema::NamespaceInfomap map;
	std::ostringstream providerMdibStringRepresentation;
	CDM::MdibContainer(providerMdibStringRepresentation, MdibResponse.Mdib(), map, OSELib::XML_ENCODING, xercesFlags);
	return providerMdibStringRepresentation.str();
}

template <typename Enumeration>
static auto as_integer(Enumeration const value)
    -> typename std::underlying_type<Enumeration>::type
{
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

} //end namespace TestTools

#endif /* CTESTCASES_TOOLS_HELPERMETHODS_H_ */
