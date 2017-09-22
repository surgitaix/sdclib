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
struct NormalizedMessageAdapter<OSCP::GetMDDescriptionTraits::Request> {
	const OSCP::GetMDDescriptionTraits::Request & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().getMdDescription().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<OSCP::GetMDDescriptionTraits::Request> source) {
		message.Body().getMdDescription().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().getMdDescription().present();
	}
};

template<>
struct NormalizedMessageAdapter<OSCP::GetMDDescriptionTraits::Response> {
	const OSCP::GetMDDescriptionTraits::Response & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().GetMDDescriptionResponse().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<OSCP::GetMDDescriptionTraits::Response> source) {
		message.Body().GetMDDescriptionResponse().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().GetMDDescriptionResponse().present();
	}
};

template<>
struct NormalizedMessageAdapter<OSCP::GetMDIBTraits::Request> {
	const OSCP::GetMDIBTraits::Request & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().GetMDIB().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<OSCP::GetMDIBTraits::Request> source) {
		message.Body().GetMDIB().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().GetMDIB().present();
	}
};

template<>
struct NormalizedMessageAdapter<OSCP::GetMDIBTraits::Response> {
	const OSCP::GetMDIBTraits::Response & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().GetMDIBResponse().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<OSCP::GetMDIBTraits::Response> source) {
		message.Body().GetMDIBResponse().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().GetMDIBResponse().present();
	}
};

template<>
struct NormalizedMessageAdapter<OSCP::GetMDStateTraits::Request> {
	const OSCP::GetMDStateTraits::Request & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().GetMDState().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<OSCP::GetMDStateTraits::Request> source) {
		message.Body().GetMDState().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().GetMDState().present();
	}
};

template<>
struct NormalizedMessageAdapter<OSCP::GetMDStateTraits::Response> {
	const OSCP::GetMDStateTraits::Response & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().GetMDStateResponse().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<OSCP::GetMDStateTraits::Response> source) {
		message.Body().GetMDStateResponse().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().GetMDStateResponse().present();
	}
};

template<>
struct NormalizedMessageAdapter<OSCP::GetContextStatesTraits::Request> {
	const OSCP::GetContextStatesTraits::Request & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().GetContextStates().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<OSCP::GetContextStatesTraits::Request> source) {
		message.Body().GetContextStates().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().GetContextStates().present();
	}
};

template<>
struct NormalizedMessageAdapter<OSCP::GetContextStatesTraits::Response> {
	const OSCP::GetContextStatesTraits::Response & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().GetContextStatesResponse().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<OSCP::GetContextStatesTraits::Response> source) {
		message.Body().GetContextStatesResponse().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().GetContextStatesResponse().present();
	}
};

template<>
struct NormalizedMessageAdapter<OSCP::SetContextStateTraits::Request> {
	const OSCP::SetContextStateTraits::Request & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().SetContextState().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<OSCP::SetContextStateTraits::Request> source) {
		message.Body().SetContextState().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().SetContextState().present();
	}
};

template<>
struct NormalizedMessageAdapter<OSCP::SetContextStateTraits::Response> {
	const OSCP::SetContextStateTraits::Response & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().SetContextStateResponse().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<OSCP::SetContextStateTraits::Response> source) {
		message.Body().SetContextStateResponse().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().SetContextStateResponse().present();
	}
};

template<>
struct NormalizedMessageAdapter<OSCP::SetAlertStateTraits::Request> {
	const OSCP::SetAlertStateTraits::Request & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().SetAlertState().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<OSCP::SetAlertStateTraits::Request> source) {
		message.Body().SetAlertState().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().SetAlertState().present();
	}
};

template<>
struct NormalizedMessageAdapter<OSCP::SetAlertStateTraits::Response> {
	const OSCP::SetAlertStateTraits::Response & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().SetAlertStateResponse().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<OSCP::SetAlertStateTraits::Response> source) {
		message.Body().SetAlertStateResponse().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().SetAlertStateResponse().present();
	}
};

template<>
struct NormalizedMessageAdapter<OSCP::SetStringTraits::Request> {
	const OSCP::SetStringTraits::Request & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().SetString().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<OSCP::SetStringTraits::Request> source) {
		message.Body().SetString().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().SetString().present();
	}
};

template<>
struct NormalizedMessageAdapter<OSCP::SetStringTraits::Response> {
	const OSCP::SetStringTraits::Response & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().SetStringResponse().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<OSCP::SetStringTraits::Response> source) {
		message.Body().SetStringResponse().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().SetStringResponse().present();
	}
};

template<>
struct NormalizedMessageAdapter<OSCP::SetValueTraits::Request> {
	const OSCP::SetValueTraits::Request & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().SetValue().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<OSCP::SetValueTraits::Request> source) {
		message.Body().SetValue().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().SetValue().present();
	}
};

template<>
struct NormalizedMessageAdapter<OSCP::SetValueTraits::Response> {
	const OSCP::SetValueTraits::Response & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().SetValueResponse().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<OSCP::SetValueTraits::Response> source) {
		message.Body().SetValueResponse().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().SetValueResponse().present();
	}
};

template<>
struct NormalizedMessageAdapter<OSCP::ActivateTraits::Request> {
	const OSCP::ActivateTraits::Request & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().Activate().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<OSCP::ActivateTraits::Request> source) {
		message.Body().Activate().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().Activate().present();
	}
};

template<>
struct NormalizedMessageAdapter<OSCP::ActivateTraits::Response> {
	const OSCP::ActivateTraits::Response & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().ActivateResponse().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<OSCP::ActivateTraits::Response> source) {
		message.Body().ActivateResponse().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().ActivateResponse().present();
	}
};




template<>
struct NormalizedMessageAdapter<OSCP::EpisodicAlertReportTraits::ReportType> {
	const OSCP::EpisodicAlertReportTraits::ReportType & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().EpisodicAlertReport().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<OSCP::EpisodicAlertReportTraits::ReportType> source) {
		message.Body().EpisodicAlertReport().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().EpisodicAlertReport().present();
	}
};

template<>
struct NormalizedMessageAdapter<OSCP::EpisodicContextChangedReportTraits::ReportType> {
	const OSCP::EpisodicContextChangedReportTraits::ReportType & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().EpisodicContextChangedReport().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<OSCP::EpisodicContextChangedReportTraits::ReportType> source) {
		message.Body().EpisodicContextChangedReport().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().EpisodicContextChangedReport().present();
	}
};

template<>
struct NormalizedMessageAdapter<OSCP::EpisodicMetricReportTraits::ReportType> {
	const OSCP::EpisodicMetricReportTraits::ReportType & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().EpisodicMetricReport().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<OSCP::EpisodicMetricReportTraits::ReportType> source) {
		message.Body().EpisodicMetricReport().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().EpisodicMetricReport().present();
	}
};

template<>
struct NormalizedMessageAdapter<OSCP::PeriodicAlertReportTraits::ReportType> {
	const OSCP::PeriodicAlertReportTraits::ReportType & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().PeriodicAlertReport().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<OSCP::PeriodicAlertReportTraits::ReportType> source) {
		message.Body().PeriodicAlertReport().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().PeriodicAlertReport().present();
	}
};

template<>
struct NormalizedMessageAdapter<OSCP::PeriodicContextChangedReportTraits::ReportType> {
	const OSCP::PeriodicContextChangedReportTraits::ReportType & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().PeriodicContextChangedReport().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<OSCP::PeriodicContextChangedReportTraits::ReportType> source) {
		message.Body().PeriodicContextChangedReport().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().PeriodicContextChangedReport().present();
	}
};

template<>
struct NormalizedMessageAdapter<OSCP::PeriodicMetricReportTraits::ReportType> {
	const OSCP::PeriodicMetricReportTraits::ReportType & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().PeriodicMetricReport().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<OSCP::PeriodicMetricReportTraits::ReportType> source) {
		message.Body().PeriodicMetricReport().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().PeriodicMetricReport().present();
	}
};

template<>
struct NormalizedMessageAdapter<OSCP::OperationInvokedReportTraits::ReportType> {
	const OSCP::OperationInvokedReportTraits::ReportType & get(const MESSAGEMODEL::Envelope & message) {
		return message.Body().OperationInvokedReport().get();
	}

	void set(MESSAGEMODEL::Envelope & message, std::unique_ptr<OSCP::OperationInvokedReportTraits::ReportType> source) {
		message.Body().OperationInvokedReport().set(std::move(source));
	}

	bool present(const MESSAGEMODEL::Envelope & message) {
		return message.Body().OperationInvokedReport().present();
	}
};

} /* namespace SOAP */
} /* namespace OSELib */

#endif /* SOAP_NORMALIZEDMESSAGEADAPTER_H_ */
