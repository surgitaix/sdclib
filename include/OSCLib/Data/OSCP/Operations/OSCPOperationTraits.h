
#ifndef OSCPOPERATIONTRAITS_H_
#define OSCPOPERATIONTRAITS_H_

#include "OSCLib/Data/QName.h"
#include "OSCLib/Data/OSCP/OSCPConstants.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

struct ActivateTraits {
	typedef CDM::Activate Request;
	typedef CDM::ActivateResponse Response;
	static std::string OperationName();
	static Data::QName PortType();
	static std::string RequestAction();
	static Data::QName RequestType();
	static std::string ResponseAction();
	static Data::QName ResponseType();
	static Response dispatch(OSCPProvider & provider, const Request & request);
};

struct GetContextStatesTraits {
	typedef CDM::GetContextStates Request;
	typedef CDM::GetContextStatesResponse Response;
	static std::string OperationName();
	static Data::QName PortType();
	static std::string RequestAction();
	static Data::QName RequestType();
	static std::string ResponseAction();
	static Data::QName ResponseType();
	static Response dispatch(OSCPProvider & provider, const Request & request);
};

struct GetMDDescriptionTraits {
	typedef CDM::GetMDDescription Request;
	typedef CDM::GetMDDescriptionResponse Response;
	static std::string OperationName();
	static Data::QName PortType();
	static std::string RequestAction();
	static Data::QName RequestType();
	static std::string ResponseAction();
	static Data::QName ResponseType();
	static Response dispatch(OSCPProvider & provider, const Request & request);
};

struct GetMDIBTraits {
	typedef CDM::GetMDIB Request;
	typedef CDM::GetMDIBResponse Response;
	static std::string OperationName();
	static Data::QName PortType();
	static std::string RequestAction();
	static Data::QName RequestType();
	static std::string ResponseAction();
	static Data::QName ResponseType();
	static Response dispatch(OSCPProvider & provider, const Request & request);
};

struct GetMDStateTraits {
	typedef CDM::GetMDState Request;
	typedef CDM::GetMDStateResponse Response;
	static std::string OperationName();
	static Data::QName PortType();
	static std::string RequestAction();
	static Data::QName RequestType();
	static std::string ResponseAction();
	static Data::QName ResponseType();
	static Response dispatch(OSCPProvider & provider, const Request & request);
};

struct SetAlertStateTraits {
	typedef CDM::SetAlertState Request;
	typedef CDM::SetAlertStateResponse Response;
	static std::string OperationName();
	static Data::QName PortType();
	static std::string RequestAction();
	static Data::QName RequestType();
	static std::string ResponseAction();
	static Data::QName ResponseType();
	static Response dispatch(OSCPProvider & provider, const Request & request);
};

struct SetContextStateTraits {
	typedef CDM::SetContextState Request;
	typedef CDM::SetContextStateResponse Response;
	static std::string OperationName();
	static Data::QName PortType();
	static std::string RequestAction();
	static Data::QName RequestType();
	static std::string ResponseAction();
	static Data::QName ResponseType();
	static Response dispatch(OSCPProvider & provider, const Request & request);
};

struct SetStringTraits {
	typedef CDM::SetString Request;
	typedef CDM::SetStringResponse Response;
	static std::string OperationName();
	static Data::QName PortType();
	static std::string RequestAction();
	static Data::QName RequestType();
	static std::string ResponseAction();
	static Data::QName ResponseType();
	static Response dispatch(OSCPProvider & provider, const Request & request);
};

struct SetValueTraits {
	typedef CDM::SetValue Request;
	typedef CDM::SetValueResponse Response;
	static std::string OperationName();
	static Data::QName PortType();
	static std::string RequestAction();
	static Data::QName RequestType();
	static std::string ResponseAction();
	static Data::QName ResponseType();
	static Response dispatch(OSCPProvider & provider, const Request & request);
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* OSCPOPERATIONTRAITS_H_ */
