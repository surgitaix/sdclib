/*
 * MessageAdapter.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef DPWS_MESSAGEADAPTER_H_
#define DPWS_MESSAGEADAPTER_H_

#include "OSELib/DPWS/Types.h"

namespace OSELib {
namespace DPWS {

struct MessageAdapter {
	template<class Message>
	static AddressType EPRAddress(const Message & message);

	template<class Message>
	static MetadataVersionType MetadataVersion(const Message & message);

	template<class Message>
	static XAddressesType XAddresses(const Message & message) ;

	template<class Message>
	static ScopesType Scopes(const Message & message);

	template<class Message>
	static TypesType Types(const Message & message);

	static UriType URI(const QName & qname);

	static std::string LocalName(const QName & qname);
};

} /* namespace DPWS */
} /* namespace OSELib */

#endif /* DPWS_MESSAGEADAPTER_H_ */
