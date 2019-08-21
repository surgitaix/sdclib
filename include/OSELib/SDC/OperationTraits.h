
#ifndef OSELIB_SDC_OPERATIONTRAITS_H_
#define OSELIB_SDC_OPERATIONTRAITS_H_

#include <memory>

#include "OSELib/fwd.h"

namespace OSELib {
namespace SDC {

struct ActivateTraits {
	typedef MDM::Activate Request;
	typedef MDM::ActivateResponse Response;
	typedef ISetService Dispatcher;
	static std::string OperationName();
	static xml_schema::Qname PortType();
	static std::string RequestAction();
	static xml_schema::Qname RequestType();
	static std::string ResponseAction();
	static xml_schema::Qname ResponseType();
	static std::unique_ptr<Response> dispatch(Dispatcher & dispatcher, const Request & request);
};

struct GetContextStatesTraits {
	typedef MDM::GetContextStates Request;
	typedef MDM::GetContextStatesResponse Response;
	typedef IContextService Dispatcher;
	static std::string OperationName();
	static xml_schema::Qname PortType();
	static std::string RequestAction();
	static xml_schema::Qname RequestType();
	static std::string ResponseAction();
	static xml_schema::Qname ResponseType();
	static std::unique_ptr<Response> dispatch(Dispatcher & dispatcher, const Request & request);
};

struct GetMDDescriptionTraits {
	typedef MDM::GetMdDescription Request;
	typedef MDM::GetMdDescriptionResponse Response;
	typedef IGetService Dispatcher;
	static std::string OperationName();
	static xml_schema::Qname PortType();
	static std::string RequestAction();
	static xml_schema::Qname RequestType();
	static std::string ResponseAction();
	static xml_schema::Qname ResponseType();
	static std::unique_ptr<Response> dispatch(Dispatcher & dispatcher, const Request & request);
};

struct GetMDIBTraits {
	typedef MDM::GetMdib Request;
	typedef MDM::GetMdibResponse Response;
	typedef IGetService Dispatcher;
	static std::string OperationName();
	static xml_schema::Qname PortType();
	static std::string RequestAction();
	static xml_schema::Qname RequestType();
	static std::string ResponseAction();
	static xml_schema::Qname ResponseType();
	static std::unique_ptr<Response> dispatch(Dispatcher & dispatcher, const Request & request);
};

struct GetMdStateTraits {
	typedef MDM::GetMdState Request;
	typedef MDM::GetMdStateResponse Response;
	typedef IGetService Dispatcher;
	static std::string OperationName();
	static xml_schema::Qname PortType();
	static std::string RequestAction();
	static xml_schema::Qname RequestType();
	static std::string ResponseAction();
	static xml_schema::Qname ResponseType();
	static std::unique_ptr<Response> dispatch(Dispatcher & dispatcher, const Request & request);
};

struct SetAlertStateTraits {
	typedef MDM::SetAlertState Request;
	typedef MDM::SetAlertStateResponse Response;
	typedef ISetService Dispatcher;
	static std::string OperationName();
	static xml_schema::Qname PortType();
	static std::string RequestAction();
	static xml_schema::Qname RequestType();
	static std::string ResponseAction();
	static xml_schema::Qname ResponseType();
	static std::unique_ptr<Response> dispatch(Dispatcher & dispatcher, const Request & request);
};

struct SetContextStateTraits {
	typedef MDM::SetContextState Request;
	typedef MDM::SetContextStateResponse Response;
	typedef IContextService Dispatcher;
	static std::string OperationName();
	static xml_schema::Qname PortType();
	static std::string RequestAction();
	static xml_schema::Qname RequestType();
	static std::string ResponseAction();
	static xml_schema::Qname ResponseType();
	static std::unique_ptr<Response> dispatch(Dispatcher & dispatcher, const Request & request);
};

struct SetStringTraits {
	typedef MDM::SetString Request;
	typedef MDM::SetStringResponse Response;
	typedef ISetService Dispatcher;
	static std::string OperationName();
	static xml_schema::Qname PortType();
	static std::string RequestAction();
	static xml_schema::Qname RequestType();
	static std::string ResponseAction();
	static xml_schema::Qname ResponseType();
	static std::unique_ptr<Response> dispatch(Dispatcher & dispatcher, const Request & request);
};

struct SetValueTraits {
	typedef MDM::SetValue Request;
	typedef MDM::SetValueResponse Response;
	typedef ISetService Dispatcher;
	static std::string OperationName();
	static xml_schema::Qname PortType();
	static std::string RequestAction();
	static xml_schema::Qname RequestType();
	static std::string ResponseAction();
	static xml_schema::Qname ResponseType();
	static std::unique_ptr<Response> dispatch(Dispatcher & dispatcher, const Request & request);
};




}
}
#endif
