/*
 * NormalizedMessageAdapter.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef SOAP_NORMALIZEDMESSAGEADAPTER_H_
#define SOAP_NORMALIZEDMESSAGEADAPTER_H_

#include "NormalizedMessageModel.hxx"

#include "OSELib/fwd.h"
#include "OSELib/DPWS/OperationTraits.h"
#include "OSELib/OSCP/OperationTraits.h"
#include "OSELib/OSCP/ReportTraits.h"

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
		return message.Body().Subscribe().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<DPWS::SubscribeTraits::Request> source) {
		message.Body().Subscribe().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().Subscribe().present();
	}
};

template<>
struct NormalizedMessageAdapter<DPWS::SubscribeTraits::Response> {
	const DPWS::SubscribeTraits::Response & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().SubscribeResponse().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<DPWS::SubscribeTraits::Response> source) {
		message.Body().SubscribeResponse().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().SubscribeResponse().present();
	}
};

template<>
struct NormalizedMessageAdapter<DPWS::UnsubscribeTraits::RequestIdentifier> {
	const DPWS::UnsubscribeTraits::RequestIdentifier & get(const MESSAGEMODEL::Envelope & message) {
		return message.Header().Identifier().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<DPWS::UnsubscribeTraits::RequestIdentifier> source) {
		message.Header().Identifier().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Header().Identifier().present();
	}
};

template<>
struct NormalizedMessageAdapter<DPWS::UnsubscribeTraits::Request> {
	const DPWS::UnsubscribeTraits::Request & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().Unsubscribe().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<DPWS::UnsubscribeTraits::Request> source) {
		message.Body().Unsubscribe().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().Unsubscribe().present();
	}
};

// used for DPWS::GetTraits::Request
// used for DPWS::UnsubscribeTraits::Response
template<>
struct NormalizedMessageAdapter<MESSAGEMODEL::Body> {
	const MESSAGEMODEL::Body & get(const MESSAGEMODEL::Envelope & message) {
		return  message.Body();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<MESSAGEMODEL::Body> source) {
		message.Body(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & ) {
		return false;
	}
};

template<>
struct NormalizedMessageAdapter<DPWS::RenewTraits::Request> {
	const DPWS::RenewTraits::Request & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().Renew().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<DPWS::RenewTraits::Request> source) {
		message.Body().Renew().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().Renew().present();
	}
};

template<>
struct NormalizedMessageAdapter<DPWS::RenewTraits::Response> {
	const DPWS::RenewTraits::Response & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().RenewResponse().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<DPWS::RenewTraits::Response> source) {
		message.Body().RenewResponse().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().RenewResponse().present();
	}
};

template<>
struct NormalizedMessageAdapter<DPWS::ProbeTraits::Request> {
	const DPWS::ProbeTraits::Request & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().Probe().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<DPWS::ProbeTraits::Request> source) {
		message.Body().Probe().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().Probe().present();
	}
};

template<>
struct NormalizedMessageAdapter<DPWS::ProbeTraits::Response> {
	const DPWS::ProbeTraits::Response & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().ProbeMatches().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<DPWS::ProbeTraits::Response> source) {
		message.Body().ProbeMatches().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().ProbeMatches().present();
	}
};

template<>
struct NormalizedMessageAdapter<DPWS::GetMetadataTraits::Request> {
	const DPWS::GetMetadataTraits::Request & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().GetMetadata().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<DPWS::GetMetadataTraits::Request> source) {
		message.Body().GetMetadata().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().GetMetadata().present();
	}
};


// used for DPWS::GetTraits::Response
// used for DPWS::GetMetadataTraits::Response
template<>
struct NormalizedMessageAdapter<WS::MEX::Metadata> {
	const WS::MEX::Metadata & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().Metadata().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<WS::MEX::Metadata> source) {
		message.Body().Metadata().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().Metadata().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::GetMDDescriptionTraits::Request> {
	const SDC::GetMDDescriptionTraits::Request & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().GetMdDescription().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::GetMDDescriptionTraits::Request> source) {
		message.Body().GetMdDescription().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().GetMdDescription().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::GetMDDescriptionTraits::Response> {
	const SDC::GetMDDescriptionTraits::Response & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().GetMdDescriptionResponse().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::GetMDDescriptionTraits::Response> source) {
		message.Body().GetMdDescriptionResponse().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().GetMdDescriptionResponse().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::GetMDIBTraits::Request> {
	const SDC::GetMDIBTraits::Request & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().GetMdib().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::GetMDIBTraits::Request> source) {
		message.Body().GetMdib().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().GetMdib().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::GetMDIBTraits::Response> {
	const SDC::GetMDIBTraits::Response & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().GetMdibResponse().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::GetMDIBTraits::Response> source) {
		message.Body().GetMdibResponse().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().GetMdibResponse().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::GetMdStateTraits::Request> {
	const SDC::GetMdStateTraits::Request & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().GetMdState().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::GetMdStateTraits::Request> source) {
		message.Body().GetMdState().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().GetMdState().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::GetMdStateTraits::Response> {
	const SDC::GetMdStateTraits::Response & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().GetMdStateResponse().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::GetMdStateTraits::Response> source) {
		message.Body().GetMdStateResponse().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().GetMdStateResponse().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::GetContextStatesTraits::Request> {
	const SDC::GetContextStatesTraits::Request & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().GetContextStates().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::GetContextStatesTraits::Request> source) {
		message.Body().GetContextStates().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().GetContextStates().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::GetContextStatesTraits::Response> {
	const SDC::GetContextStatesTraits::Response & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().GetContextStatesResponse().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::GetContextStatesTraits::Response> source) {
		message.Body().GetContextStatesResponse().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().GetContextStatesResponse().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::SetContextStateTraits::Request> {
	const SDC::SetContextStateTraits::Request & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().SetContextState().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::SetContextStateTraits::Request> source) {
		message.Body().SetContextState().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().SetContextState().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::SetContextStateTraits::Response> {
	const SDC::SetContextStateTraits::Response & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().SetContextStateResponse().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::SetContextStateTraits::Response> source) {
		message.Body().SetContextStateResponse().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().SetContextStateResponse().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::SetAlertStateTraits::Request> {
	const SDC::SetAlertStateTraits::Request & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().SetAlertState().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::SetAlertStateTraits::Request> source) {
		message.Body().SetAlertState().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().SetAlertState().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::SetAlertStateTraits::Response> {
	const SDC::SetAlertStateTraits::Response & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().SetAlertStateResponse().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::SetAlertStateTraits::Response> source) {
		message.Body().SetAlertStateResponse().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().SetAlertStateResponse().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::SetStringTraits::Request> {
	const SDC::SetStringTraits::Request & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().SetString().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::SetStringTraits::Request> source) {
		message.Body().SetString().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().SetString().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::SetStringTraits::Response> {
	const SDC::SetStringTraits::Response & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().SetStringResponse().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::SetStringTraits::Response> source) {
		message.Body().SetStringResponse().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().SetStringResponse().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::SetValueTraits::Request> {
	const SDC::SetValueTraits::Request & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().SetValue().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::SetValueTraits::Request> source) {
		message.Body().SetValue().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().SetValue().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::SetValueTraits::Response> {
	const SDC::SetValueTraits::Response & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().SetValueResponse().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::SetValueTraits::Response> source) {
		message.Body().SetValueResponse().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().SetValueResponse().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::ActivateTraits::Request> {
	const SDC::ActivateTraits::Request & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().Activate().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::ActivateTraits::Request> source) {
		message.Body().Activate().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().Activate().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::ActivateTraits::Response> {
	const SDC::ActivateTraits::Response & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().ActivateResponse().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::ActivateTraits::Response> source) {
		message.Body().ActivateResponse().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().ActivateResponse().present();
	}
};




template<>
struct NormalizedMessageAdapter<SDC::EpisodicAlertReportTraits::ReportType> {
	const SDC::EpisodicAlertReportTraits::ReportType & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().EpisodicAlertReport().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::EpisodicAlertReportTraits::ReportType> source) {
		message.Body().EpisodicAlertReport().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().EpisodicAlertReport().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::EpisodicContextChangedReportTraits::ReportType> {
	const SDC::EpisodicContextChangedReportTraits::ReportType & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().EpisodicContextReport().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::EpisodicContextChangedReportTraits::ReportType> source) {
		message.Body().EpisodicContextReport().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().EpisodicContextReport().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::EpisodicMetricReportTraits::ReportType> {
	const SDC::EpisodicMetricReportTraits::ReportType & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().EpisodicMetricReport().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::EpisodicMetricReportTraits::ReportType> source) {
		message.Body().EpisodicMetricReport().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().EpisodicMetricReport().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::PeriodicAlertReportTraits::ReportType> {
	const SDC::PeriodicAlertReportTraits::ReportType & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().PeriodicAlertReport().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::PeriodicAlertReportTraits::ReportType> source) {
		message.Body().PeriodicAlertReport().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().PeriodicAlertReport().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::PeriodicContextChangedReportTraits::ReportType> {
	const SDC::PeriodicContextChangedReportTraits::ReportType & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().PeriodicContextReport().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::PeriodicContextChangedReportTraits::ReportType> source) {
		message.Body().PeriodicContextReport().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().PeriodicContextReport().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::PeriodicMetricReportTraits::ReportType> {
	const SDC::PeriodicMetricReportTraits::ReportType & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().PeriodicMetricReport().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::PeriodicMetricReportTraits::ReportType> source) {
		message.Body().PeriodicMetricReport().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().PeriodicMetricReport().present();
	}
};

template<>
struct NormalizedMessageAdapter<SDC::OperationInvokedReportTraits::ReportType> {
	const SDC::OperationInvokedReportTraits::ReportType & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().OperationInvokedReport().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<SDC::OperationInvokedReportTraits::ReportType> source) {
		message.Body().OperationInvokedReport().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().OperationInvokedReport().present();
	}
};

} /* namespace SOAP */
} /* namespace OSELib */

#endif /* SOAP_NORMALIZEDMESSAGEADAPTER_H_ */
