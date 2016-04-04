/*
 * ToString.h
 *
 *  Created on: 13.10.2014
 *      Author: roehser
 */

#ifndef TOSTRING_H_
#define TOSTRING_H_

#include <string>
#include "osdm-fwd.hxx"

namespace CDM {

class ToString {
public:
	ToString();
	virtual ~ToString();

	static std::string convert(const int i);
	static std::string convert(const double d);
	static std::string convert(const CDM::WaveformStream & obj);
	static std::string convert(const CDM::Activate & obj);
	static std::string convert(const CDM::ActivateResponse & obj);
	static std::string convert(const CDM::EpisodicAlertReport & obj);
	static std::string convert(const CDM::EpisodicContextChangedReport & obj);
	static std::string convert(const CDM::EpisodicMetricReport & obj);
	static std::string convert(const CDM::GetContextStatesResponse & obj);
	static std::string convert(const CDM::GetMDDescription & obj);
	static std::string convert(const CDM::GetMDDescriptionResponse & obj);
	static std::string convert(const CDM::GetMDIB & obj);
	static std::string convert(const CDM::GetMDIBResponse & obj);
	static std::string convert(const CDM::GetMDState & obj);
	static std::string convert(const CDM::GetMDStateResponse & obj);
	static std::string convert(const CDM::MDIB & obj);
	static std::string convert(const CDM::MDSCreatedReport & obj);
	static std::string convert(const CDM::MDSDeletedReport & obj);
	static std::string convert(const CDM::ObjectCreatedReport & obj);
	static std::string convert(const CDM::ObjectDeletedReport & obj);
	static std::string convert(const CDM::OperationalStateChangedReport & obj);
	static std::string convert(const CDM::OperationCreatedReport & obj);
	static std::string convert(const CDM::OperationDeletedReport & obj);
	static std::string convert(const CDM::OperationInvokedReport & obj);
	static std::string convert(const CDM::PeriodicAlertReport & obj);
	static std::string convert(const CDM::PeriodicContextChangedReport & obj);
	static std::string convert(const CDM::PeriodicMetricReport & obj);
	static std::string convert(const CDM::SetAlertState & obj);
	static std::string convert(const CDM::SetAlertStateResponse & obj);
	static std::string convert(const CDM::SetContextState & obj);
	static std::string convert(const CDM::SetContextStateResponse & obj);
	static std::string convert(const CDM::SetString & obj);
	static std::string convert(const CDM::SetStringResponse & obj);
	static std::string convert(const CDM::SetValue & obj);
	static std::string convert(const CDM::SetValueResponse & obj);
	static std::string convert(const CDM::SystemErrorReport & obj);
};

}

#endif /* TOSTRING_H_ */
