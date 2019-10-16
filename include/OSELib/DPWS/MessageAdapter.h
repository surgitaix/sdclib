/*
 * MessageAdapter.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 23.08.2019, baumeister
 *
 */

#ifndef OSELIB_DPWS_MESSAGEADAPTER_H_
#define OSELIB_DPWS_MESSAGEADAPTER_H_

#include "OSELib/DPWS/Types.h"

namespace OSELib
{
	namespace DPWS
	{

		struct MessageAdapter {
			template<class Message>
			static AddressType EPRAddress(const Message & p_message);

			template<class Message>
			static MetadataVersionType MetadataVersion(const Message & p_message);

			template<class Message>
			static XAddressesType XAddresses(const Message & p_message) ;

			template<class Message>
			static ScopesType Scopes(const Message & p_message);

			template<class Message>
			static TypesType Types(const Message & p_message);

			static UriType URI(const QName & p_qname);

			static std::string LocalName(const QName & p_qname);
		};
	}
}

#endif
