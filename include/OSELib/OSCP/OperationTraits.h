
#ifndef SOAPOPERATIONTRAITS_H_
#define SOAPOPERATIONTRAITS_H_

#include <memory>

#include "OSELib/fwd.h"

namespace OSELib {
namespace OSCP {

struct ActivateTraits {
	typedef CDM::Activate Request;
	typedef CDM::ActivateResponse Response;
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
	typedef CDM::GetContextStates Request;
	typedef CDM::GetContextStatesResponse Response;
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
	typedef CDM::GetMDDescription Request;
	typedef CDM::GetMDDescriptionResponse Response;
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
	typedef CDM::GetMDIB Request;
	typedef CDM::GetMDIBResponse Response;
	typedef IGetService Dispatcher;
	static std::string OperationName();
	static xml_schema::Qname PortType();
	static std::string RequestAction();
	static xml_schema::Qname RequestType();
	static std::string ResponseAction();
	static xml_schema::Qname ResponseType();
	static std::unique_ptr<Response> dispatch(Dispatcher & dispatcher, const Request & request);
};

struct GetMDStateTraits {
	typedef CDM::GetMDState Request;
	typedef CDM::GetMDStateResponse Response;
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
	typedef CDM::SetAlertState Request;
	typedef CDM::SetAlertStateResponse Response;
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
	typedef CDM::SetContextState Request;
	typedef CDM::SetContextStateResponse Response;
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
	typedef CDM::SetString Request;
	typedef CDM::SetStringResponse Response;
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
	typedef CDM::SetValue Request;
	typedef CDM::SetValueResponse Response;
	typedef ISetService Dispatcher;
	static std::string OperationName();
	static xml_schema::Qname PortType();
	static std::string RequestAction();
	static xml_schema::Qname RequestType();
	static std::string ResponseAction();
	static xml_schema::Qname ResponseType();
	static std::unique_ptr<Response> dispatch(Dispatcher & dispatcher, const Request & request);
};




}  // namespace OSCP
} /* namespace OSCLib */
#endif /* SOAPOPERATIONTRAITS_H_ */
