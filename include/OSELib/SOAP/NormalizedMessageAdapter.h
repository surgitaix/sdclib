/*
 * NormalizedMessageAdapter.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef SOAP_NORMALIZEDMESSAGEADAPTER_H_
#define SOAP_NORMALIZEDMESSAGEADAPTER_H_

#include "OSELib/fwd.h"
#include "OSELib/DPWS/OperationTraits.h"
#include "OSELib/SDC/OperationTraits.h"
#include "OSELib/SDC/ReportTraits.h"

#include "DataModel/NormalizedMessageModel.hxx"

namespace OSELib {
namespace SOAP {

template<class Type>
struct NormalizedMessageAdapter {
	const Type & get(const MESSAGEMODEL::Envelope & message);
	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<Type> source);
	bool present(const MESSAGEMODEL::Envelope & message);
};

template<>
struct NormalizedMessageAdapter<DPWS::SubscribeTraits::Request> {
	const DPWS::SubscribeTraits::Request & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getSubscribe().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<DPWS::SubscribeTraits::Request> source) {
		message.getBody().getSubscribe().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getSubscribe().present();
	}
};

template<>
struct NormalizedMessageAdapter<DPWS::SubscribeTraits::Response> {
	const DPWS::SubscribeTraits::Response & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getSubscribeResponse().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<DPWS::SubscribeTraits::Response> source) {
		message.getBody().getSubscribeResponse().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getSubscribeResponse().present();
	}
};

template<>
struct NormalizedMessageAdapter<DPWS::UnsubscribeTraits::RequestIdentifier> {
	const DPWS::UnsubscribeTraits::RequestIdentifier & get(const MESSAGEMODEL::Envelope & message) {
		return message.getHeader().getIdentifier().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<DPWS::UnsubscribeTraits::RequestIdentifier> source) {
		message.getHeader().getIdentifier().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getHeader().getIdentifier().present();
	}
};

template<>
struct NormalizedMessageAdapter<DPWS::UnsubscribeTraits::Request> {
	const DPWS::UnsubscribeTraits::Request & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getUnsubscribe().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<DPWS::UnsubscribeTraits::Request> source) {
		message.getBody().getUnsubscribe().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getUnsubscribe().present();
	}
};

// used for DPWS::GetTraits::Request
// used for DPWS::UnsubscribeTraits::Response
template<>
struct NormalizedMessageAdapter<MESSAGEMODEL::Body> {
	const MESSAGEMODEL::Body & get(const MESSAGEMODEL::Envelope & message) {
		return  message.getBody();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<MESSAGEMODEL::Body> source) {
		message.setBody(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & ) {
		return false;
	}
};

template<>
struct NormalizedMessageAdapter<DPWS::RenewTraits::Request> {
	const DPWS::RenewTraits::Request & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getRenew().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<DPWS::RenewTraits::Request> source) {
		message.getBody().getRenew().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getRenew().present();
	}
};

template<>
struct NormalizedMessageAdapter<DPWS::RenewTraits::Response> {
	const DPWS::RenewTraits::Response & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getRenewResponse().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<DPWS::RenewTraits::Response> source) {
		message.getBody().getRenewResponse().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getRenewResponse().present();
	}
};

template<>
struct NormalizedMessageAdapter<DPWS::GetStatusTraits::Request> {
	const DPWS::GetStatusTraits::Request & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getGetStatus().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<DPWS::GetStatusTraits::Request> source) {
		message.getBody().getGetStatus().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getGetStatus().present();
	}
};

template<>
struct NormalizedMessageAdapter<DPWS::GetStatusTraits::Response> {
	const DPWS::GetStatusTraits::Response & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getGetStatusResponse().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<DPWS::GetStatusTraits::Response> source) {
		message.getBody().getGetStatusResponse().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getGetStatusResponse().present();
	}
};

template<>
struct NormalizedMessageAdapter<DPWS::ProbeTraits::Request> {
	const DPWS::ProbeTraits::Request & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getProbe().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<DPWS::ProbeTraits::Request> source) {
		message.getBody().getProbe().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getProbe().present();
	}
};

template<>
struct NormalizedMessageAdapter<DPWS::ProbeTraits::Response> {
	const DPWS::ProbeTraits::Response & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getProbeMatches().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<DPWS::ProbeTraits::Response> source) {
		message.getBody().getProbeMatches().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getProbeMatches().present();
	}
};

template<>
struct NormalizedMessageAdapter<DPWS::GetMetadataTraits::Request> {
	const DPWS::GetMetadataTraits::Request & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getGetMetadata().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<DPWS::GetMetadataTraits::Request> source) {
		message.getBody().getGetMetadata().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getGetMetadata().present();
	}
};


// used for DPWS::GetTraits::Response
// used for DPWS::GetMetadataTraits::Response
template<>
struct NormalizedMessageAdapter<WS::MEX::Metadata> {
	const WS::MEX::Metadata & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getMetadata().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<WS::MEX::Metadata> source) {
		message.getBody().getMetadata().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getMetadata().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::GetMDDescriptionTraits::Request> {
	const SDC::GetMDDescriptionTraits::Request & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getGetMdDescription().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::GetMDDescriptionTraits::Request> source) {
		message.getBody().getGetMdDescription().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getGetMdDescription().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::GetMDDescriptionTraits::Response> {
	const SDC::GetMDDescriptionTraits::Response & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getGetMdDescriptionResponse().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::GetMDDescriptionTraits::Response> source) {
		message.getBody().getGetMdDescriptionResponse().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getGetMdDescriptionResponse().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::GetMDIBTraits::Request> {
	const SDC::GetMDIBTraits::Request & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getGetMdib().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::GetMDIBTraits::Request> source) {
		message.getBody().getGetMdib().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getGetMdib().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::GetMDIBTraits::Response> {
	const SDC::GetMDIBTraits::Response & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getGetMdibResponse().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::GetMDIBTraits::Response> source) {
		message.getBody().getGetMdibResponse().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getGetMdibResponse().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::GetMdStateTraits::Request> {
	const SDC::GetMdStateTraits::Request & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getGetMdState().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::GetMdStateTraits::Request> source) {
		message.getBody().getGetMdState().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getGetMdState().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::GetMdStateTraits::Response> {
	const SDC::GetMdStateTraits::Response & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getGetMdStateResponse().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::GetMdStateTraits::Response> source) {
		message.getBody().getGetMdStateResponse().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getGetMdStateResponse().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::GetContextStatesTraits::Request> {
	const SDC::GetContextStatesTraits::Request & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getGetContextStates().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::GetContextStatesTraits::Request> source) {
		message.getBody().getGetContextStates().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getGetContextStates().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::GetContextStatesTraits::Response> {
	const SDC::GetContextStatesTraits::Response & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getGetContextStatesResponse().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::GetContextStatesTraits::Response> source) {
		message.getBody().getGetContextStatesResponse().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getGetContextStatesResponse().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::SetContextStateTraits::Request> {
	const SDC::SetContextStateTraits::Request & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getSetContextState().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::SetContextStateTraits::Request> source) {
		message.getBody().getSetContextState().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getSetContextState().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::SetContextStateTraits::Response> {
	const SDC::SetContextStateTraits::Response & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getSetContextStateResponse().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::SetContextStateTraits::Response> source) {
		message.getBody().getSetContextStateResponse().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getSetContextStateResponse().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::SetAlertStateTraits::Request> {
	const SDC::SetAlertStateTraits::Request & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getSetAlertState().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::SetAlertStateTraits::Request> source) {
		message.getBody().getSetAlertState().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getSetAlertState().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::SetAlertStateTraits::Response> {
	const SDC::SetAlertStateTraits::Response & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getSetAlertStateResponse().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::SetAlertStateTraits::Response> source) {
		message.getBody().getSetAlertStateResponse().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getSetAlertStateResponse().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::SetStringTraits::Request> {
	const SDC::SetStringTraits::Request & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getSetString().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::SetStringTraits::Request> source) {
		message.getBody().getSetString().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getSetString().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::SetStringTraits::Response> {
	const SDC::SetStringTraits::Response & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getSetStringResponse().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::SetStringTraits::Response> source) {
		message.getBody().getSetStringResponse().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getSetStringResponse().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::SetValueTraits::Request> {
	const SDC::SetValueTraits::Request & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getSetValue().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::SetValueTraits::Request> source) {
		message.getBody().getSetValue().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getSetValue().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::SetValueTraits::Response> {
	const SDC::SetValueTraits::Response & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getSetValueResponse().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::SetValueTraits::Response> source) {
		message.getBody().getSetValueResponse().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getSetValueResponse().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::ActivateTraits::Request> {
	const SDC::ActivateTraits::Request & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getActivate().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::ActivateTraits::Request> source) {
		message.getBody().getActivate().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getActivate().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::ActivateTraits::Response> {
	const SDC::ActivateTraits::Response & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getActivateResponse().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::ActivateTraits::Response> source) {
		message.getBody().getActivateResponse().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getActivateResponse().present();
	}
};

// Description Event Service
template<>
struct NormalizedMessageAdapter<SDC::DescriptionModificationReportTraits::ReportType> {
	const SDC::DescriptionModificationReportTraits::ReportType & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getDescriptionModificationReport().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::DescriptionModificationReportTraits::ReportType> source) {
		message.getBody().getDescriptionModificationReport().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getDescriptionModificationReport().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::EpisodicAlertReportTraits::ReportType> {
	const SDC::EpisodicAlertReportTraits::ReportType & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getEpisodicAlertReport().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::EpisodicAlertReportTraits::ReportType> source) {
		message.getBody().getEpisodicAlertReport().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getEpisodicAlertReport().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::EpisodicComponentReportTraits::ReportType> {
	const SDC::EpisodicComponentReportTraits::ReportType & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getEpisodicComponentReport().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::EpisodicComponentReportTraits::ReportType> source) {
		message.getBody().getEpisodicComponentReport().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getEpisodicComponentReport().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::EpisodicContextReportTraits::ReportType> {
	const SDC::EpisodicContextReportTraits::ReportType & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getEpisodicContextReport().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::EpisodicContextReportTraits::ReportType> source) {
		message.getBody().getEpisodicContextReport().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getEpisodicContextReport().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::EpisodicMetricReportTraits::ReportType> {
	const SDC::EpisodicMetricReportTraits::ReportType & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getEpisodicMetricReport().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::EpisodicMetricReportTraits::ReportType> source) {
		message.getBody().getEpisodicMetricReport().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getEpisodicMetricReport().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::EpisodicOperationalStateReportTraits::ReportType> {
	const SDC::EpisodicOperationalStateReportTraits::ReportType & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getEpisodicOperationalStateReport().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::EpisodicOperationalStateReportTraits::ReportType> source) {
		message.getBody().getEpisodicOperationalStateReport().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getEpisodicOperationalStateReport().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::PeriodicAlertReportTraits::ReportType> {
	const SDC::PeriodicAlertReportTraits::ReportType & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getPeriodicAlertReport().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::PeriodicAlertReportTraits::ReportType> source) {
		message.getBody().getPeriodicAlertReport().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getPeriodicAlertReport().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::PeriodicContextReportTraits::ReportType> {
	const SDC::PeriodicContextReportTraits::ReportType & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getPeriodicContextReport().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::PeriodicContextReportTraits::ReportType> source) {
		message.getBody().getPeriodicContextReport().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getPeriodicContextReport().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::PeriodicMetricReportTraits::ReportType> {
	const SDC::PeriodicMetricReportTraits::ReportType & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getPeriodicMetricReport().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::PeriodicMetricReportTraits::ReportType> source) {
		message.getBody().getPeriodicMetricReport().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getPeriodicMetricReport().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::OperationInvokedReportTraits::ReportType> {
	const SDC::OperationInvokedReportTraits::ReportType & get(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getOperationInvokedReport().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::OperationInvokedReportTraits::ReportType> source) {
		message.getBody().getOperationInvokedReport().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.getBody().getOperationInvokedReport().present();
	}
};

} /* namespace SOAP */
} /* namespace OSELib */

#endif /* SOAP_NORMALIZEDMESSAGEADAPTER_H_ */
