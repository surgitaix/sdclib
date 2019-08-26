/*
 * Types.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef OSELIB_DPWS_TYPES_H_
#define OSELIB_DPWS_TYPES_H_

#include "DataModel/wsdd-discovery-1.1-schema-os-fwd.hxx"
#include "DataModel/BICEPS_MessageModel-fwd.hxx"

namespace OSELib {
namespace DPWS {

typedef xml_schema::Uri UriType;
typedef UriType XAddressType;
typedef ::WS::DISCOVERY::UriListType XAddressesType;
typedef UriType ScopeType;
typedef ::WS::DISCOVERY::UriListType ScopesType;
typedef xml_schema::Qname QName;
typedef QName TypeType;
typedef ::WS::DISCOVERY::QNameListType TypesType;

typedef WS::ADDRESSING::AttributedURIType AddressType;
typedef WS::ADDRESSING::EndpointReferenceType EndpointReferenceType;
typedef unsigned int MetadataVersionType;
typedef WS::DISCOVERY::ProbeType ProbeType;
typedef WS::DISCOVERY::ResolveType ResolveType;
typedef WS::DISCOVERY::ByeType ByeType;
typedef WS::DISCOVERY::HelloType HelloType;
typedef WS::DISCOVERY::ProbeMatchType ProbeMatchType;
typedef WS::DISCOVERY::ResolveMatchType ResolveMatchType;
typedef MDM::WaveformStream WaveformStreamType;

class ByeNotificationDispatcher {
protected:
	ByeNotificationDispatcher() = default;
	virtual ~ByeNotificationDispatcher() = default;

public:
	virtual void dispatch(const ByeType & notification) = 0;
};

class HelloNotificationDispatcher {
protected:
	HelloNotificationDispatcher() = default;
	virtual ~HelloNotificationDispatcher() = default;

public:
	virtual void dispatch(const HelloType & notification) = 0;
};

class ProbeNotificationDispatcher {
protected:
	ProbeNotificationDispatcher() = default;
	virtual ~ProbeNotificationDispatcher() = default;

public:
	virtual std::vector<ProbeMatchType> dispatch(const ProbeType & filter) = 0;
};

class ProbeMatchNotificationDispatcher {
protected:
	ProbeMatchNotificationDispatcher() = default;
	virtual ~ProbeMatchNotificationDispatcher() = default;

public:
	virtual void dispatch(const ProbeMatchType & notification) = 0;
};

class ResolveNotificationDispatcher {
protected:
	ResolveNotificationDispatcher() = default;
	virtual ~ResolveNotificationDispatcher() = default;

public:
	virtual std::unique_ptr<ResolveMatchType> dispatch(const ResolveType & filter) = 0;
};

class ResolveMatchNotificationDispatcher {
protected:
	ResolveMatchNotificationDispatcher() = default;
	virtual ~ResolveMatchNotificationDispatcher() = default;

public:
	virtual void dispatch(const ResolveMatchType & notification) = 0;
};


// callback interface between SDCConsumerAdapter and DPWSStreamingClientSocketImpl (and thus the Poco reactor framework)
class StreamNotificationDispatcher {
protected:
	StreamNotificationDispatcher() = default;
	virtual ~StreamNotificationDispatcher() = default;

public:
	virtual void dispatch(const WaveformStreamType & notification) = 0;
};

// callback interface between SDCConsumerAdapter and SDCConsumerAdapter
class StreamNotificationDispatcherAdapterInterface {
protected:
	StreamNotificationDispatcherAdapterInterface() = default;
	virtual ~StreamNotificationDispatcherAdapterInterface() = default;

public:
	virtual void dispatchStream(const StreamNotificationDispatcher & notification) = 0;
};

}
}

#endif /* OSELIB_DPWS_TYPES_H_ */
