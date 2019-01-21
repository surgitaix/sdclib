/*
 * DPWSClient.h
 *
 *  Created on: 11.12.2015
 *      Author: matthias
 */

#ifndef OSELIB_DPWS_DPWSCLIENT_H_
#define OSELIB_DPWS_DPWSCLIENT_H_

#include <mutex>
#include <tuple>

#include "OSELib/fwd.h"
#include "OSELib/DPWS/Types.h"

namespace OSELib {
namespace DPWS {

struct ByeCallback {
	virtual ~ByeCallback() = default;
	virtual void bye(const ByeType & notification) = 0;
};

struct HelloCallback {
	virtual ~HelloCallback() = default;
	virtual void hello(const HelloType & notification) = 0;
};

struct ProbeMatchCallback {
	virtual ~ProbeMatchCallback() = default;
	virtual void probeMatch(const ProbeMatchType & notification) = 0;
};

struct ResolveMatchCallback {
	virtual ~ResolveMatchCallback() = default;
	virtual void resolveMatch(const ResolveMatchType & notification) = 0;
};

class MDPWSDiscoveryClientAdapter :
		public ByeNotificationDispatcher,
		public HelloNotificationDispatcher,
		public ProbeMatchNotificationDispatcher,
		public ResolveMatchNotificationDispatcher
{
public:
	MDPWSDiscoveryClientAdapter();
	virtual ~MDPWSDiscoveryClientAdapter();

	void addProbeMatchEventHandler(const ProbeType & filter, ProbeMatchCallback & callback);
	void removeProbeMatchEventHandler(ProbeMatchCallback & callback);

	void addResolveMatchEventHandler(const ResolveType & filter, ResolveMatchCallback & callback);
	void removeResolveMatchEventHandler(ResolveMatchCallback & callback);

	void addHelloEventHandler(HelloCallback & callback);
	void removeHelloEventHandler(HelloCallback & callback);

	void addByeEventHandler(ByeCallback & callback);
	void removeByeEventHandler(ByeCallback & callback);

private:
	void dispatch(const ProbeMatchType & notification) override;
	void dispatch(const ResolveMatchType & notification) override;
	void dispatch(const ByeType & notification) override;
	void dispatch(const HelloType & notification) override;

	typedef std::tuple<ProbeType, ProbeMatchCallback *> ProbeMatchHandler;
	typedef std::tuple<ResolveType, ResolveMatchCallback *> ResolveMatchHandler;
	std::vector<ProbeMatchHandler> _probeMatchHandlers;
	std::vector<ResolveMatchHandler> _resolveMatchHandlers;
	std::vector<HelloCallback*> _helloHandlers;
	std::vector<ByeCallback*> _byeHandlers;

	mutable std::mutex _mutex;

	std::unique_ptr<Impl::DPWSDiscoveryClientSocketImpl> _impl;
};

} /* namespace DPWS */
} /* namespace OSELib */

#endif /* OSELIB_DPWS_DPWSCLIENT_H_ */
