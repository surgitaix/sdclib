/*
 * SDCConsumerAdapter.h
 *
 *  Created on: 10.12.2015
 *      Author: matthias
 */

#ifndef DATA_OSCP_SDCCONSUMERADAPTER_H_
#define DATA_OSCP_SDCCONSUMERADAPTER_H_

#include "Poco/Mutex.h"

#include "SDC-fwd.h"
#include "OSELib/fwd.h"
#include "OSELib/DPWS/DeviceDescription.h"
#include "OSELib/OSCP/DefaultOSCPSchemaGrammarProvider.h"
#include "OSELib/DPWS/Types.h"

#include "OSELib/Helper/WithLogger.h"

// todo: maybe just fwd..
#include "OSELib/DPWS/MDPWSStreamingAdapter.h"



namespace OSCLib {
namespace Data {
namespace SDC {

class SDCConsumerAdapter :
		public OSELib::DPWS::StreamNotificationDispatcher,
		public OSELib::WithLogger
{
public:
	SDCConsumerAdapter(SDCConsumer & consumer, const unsigned int port, const OSELib::DPWS::DeviceDescription & deviceDescription);
	virtual ~SDCConsumerAdapter();

	void start();
	void stop();

	std::unique_ptr<MDM::GetMdDescriptionResponse> invoke(const MDM::GetMdDescription & request);
	std::unique_ptr<MDM::GetMdibResponse> invoke(const MDM::GetMdib & request);
	std::unique_ptr<MDM::GetMdStateResponse> invoke(const MDM::GetMdState & request);

	std::unique_ptr<MDM::ActivateResponse> invoke(const MDM::Activate & request);
	std::unique_ptr<MDM::SetAlertStateResponse> invoke(const MDM::SetAlertState & request);
	std::unique_ptr<MDM::SetValueResponse> invoke(const MDM::SetValue & request);
	std::unique_ptr<MDM::SetStringResponse> invoke(const MDM::SetString & request);

	std::unique_ptr<MDM::SetContextStateResponse> invoke(const MDM::SetContextState & request);

	void subscribeEvents();
	void unsubscribeEvents();



private:

	// callback from _streamClientSocketImpl
	virtual void dispatch(const OSELib::DPWS::WaveformStreamType & notification) override;

	// Variables
	template<class TraitsType>
	std::unique_ptr<typename TraitsType::Response> invokeImpl(const typename TraitsType::Request & request, const Poco::URI & requestURI);

	template<class TraitsType>
	std::unique_ptr<typename TraitsType::Response> invokeImplWithEventSubscription(const typename TraitsType::Request & request, const Poco::URI & requestURI);

	template<class RequestType>
	Poco::URI getRequestURIFromDeviceDescription(const RequestType & request);

	SDCConsumer & _consumer;

	mutable Poco::Mutex mutex;
	std::unique_ptr<Poco::ThreadPool> _threadPool;

	const unsigned int _port;
	const OSELib::DPWS::DeviceDescription _deviceDescription;
	OSELib::SDC::DefaultOSCPSchemaGrammarProvider _grammarProvider;
	std::unique_ptr<Poco::Net::HTTPServer> _httpServer;
//	std::unique_ptr<OSELib::DPWS::Impl::DPWSStreamingClientSocketImpl> _streamClientSocketImpl;
	OSELib::DPWS::Impl::MDPWSStreamingAdapter _streamClientSocketImpl;
	std::unique_ptr<OSELib::DPWS::SubscriptionClient> _subscriptionClient;
	std::unique_ptr<OSELib::DPWS::PingManager> _pingManager;
};

}
}
} /* namespace OSELib */

#endif /* DATA_OSCP_SDCCONSUMERADAPTER_H_ */
