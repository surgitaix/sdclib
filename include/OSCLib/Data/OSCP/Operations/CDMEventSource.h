/*
 * CDMEpisodicAlertReportSource.h
 *
 *  Created on: 17.02.2015
 *      Author: osclib
 */

#ifndef INCLUDE_OSCLIB_DATA_OSCP_OPERATIONS_CDMEVENTSOURCE_H_
#define INCLUDE_OSCLIB_DATA_OSCP_OPERATIONS_CDMEVENTSOURCE_H_

#include "OSCLib/Data/EventSource.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "OSCLib/Data/OSCP/Operations/OSCPReportTraits.h"
#include "OSCLib/Util/ToString.h"
#include "osdm.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

template<class Traits>
class CDMEventSource : public EventSource {
public:
	CDMEventSource() {
	    setPortType(Traits::PortType());
	    setOutputAction(Traits::Action());
	}
	virtual ~CDMEventSource() {

	}

	void responseReceived(Parameters & ) {
	    // NOOP
	}

	Parameters getParams(const typename Traits::ReportType & report) {
		Parameters fireParams;
		OSCLib::Data::Parameter fireParam("CDMFire", OSCLib::Data::Parameter::Type::CDM);
		fireParam.setValue(CDM::ToString::convert(report));
		fireParams.push_back(fireParam);
		return fireParams;
	}

	void notify(const typename Traits::ReportType & report) {
		Parameters fireParams = getParams(report);
		fire(fireParams);
	}

	void notifyAll(const typename Traits::ReportType & report, const std::string handle) {
		Parameters fireParams = getParams(report);
		mcast(fireParams, handle);
	}

};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

#endif /* INCLUDE_OSCLIB_DATA_OSCP_OPERATIONS_CDMEVENTSOURCE_H_ */
