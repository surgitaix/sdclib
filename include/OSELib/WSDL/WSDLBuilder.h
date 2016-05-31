/*
 * WSDLBuilder.h
 *
 *  Created on: 31.07.2015
 *      Author: roehser
 */

#ifndef DEV_OSCP_WSDLBUILDER_H_
#define DEV_OSCP_WSDLBUILDER_H_

#include <memory>

#include "wsdl-custom-fwd.hxx"
#include "wsdl-soap-binding-fwd.hxx"
#include "ws-addressing-fwd.hxx"

namespace OSELib {
namespace WSDL {

class WSDLBuilder {
public:
	WSDLBuilder(const std::string & targetNamespace, const std::string & portType);
	virtual ~WSDLBuilder();

	std::string serialize();

	void addStreamType(const std::string & targetNs, const std::string & actionURI, const std::string & type, const std::string & id);
	void addOperation(const std::string & operationName, const xml_schema::Qname & request, const xml_schema::Qname & response, const std::string & requestAction, const std::string & responseAction);
	void addNotification(const std::string & notificationName, const xml_schema::Qname & notification, const std::string & action);

private:
	void definePrefixMapping(const std::string & prefix, const std::string & ns);
	void addMessage(const xml_schema::Qname & qname);

	const std::string messageSnippet_;
	const std::string parametersSnippet_;
	std::unique_ptr<WS::WSDL::TDefinitions> wsdl;
	std::unique_ptr<WS::WSDL::TPortType> portType_;
	std::unique_ptr<WS::WSDL::TBinding> binding_;
	xml_schema::NamespaceInfomap map;
	const std::string targetNamespace_;
};

template<class TraitClass>
class WSDLBuilderTraitAdapter {
public:
	WSDLBuilderTraitAdapter(WSDLBuilder & builder) {
		// use template meta programming to resolve between different trait types.
		// notification traits and operation traits are structurally different,
		// but this adapter supports both types
		adapt<TraitClass>(builder, nullptr);
	}
private:
	template<class T>
	void adapt(WSDLBuilder & builder, typename T::Request * ) {
		builder.addOperation(
			TraitClass::OperationName(),
			TraitClass::RequestType(),
			TraitClass::ResponseType(),
			TraitClass::RequestAction(),
			TraitClass::ResponseAction());
	}

	template<class T>
	void adapt(WSDLBuilder & builder, typename T::ReportType * ) {
		builder.addNotification(
				TraitClass::NotificationName(),
				TraitClass::MessageType(),
				TraitClass::Action());
	}
};

}
} /* namespace OSCLib */

#endif /* DEV_OSCP_WSDLBUILDER_H_ */
