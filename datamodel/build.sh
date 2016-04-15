xsdcxx cxx-tree \
	--std c++11 \
	--show-sloc \
	--type-naming ucc \
	--generate-polymorphic \
	--polymorphic-type-all \
	--generate-forward \
	--generate-serialization \
	--hxx-suffix ".hxx" \
	--cxx-suffix ".cxx" \
	--ixx-suffix ".ixx" \
	--namespace-map http://extension-point-uri/15/03=CDM \
	--namespace-map http://domain-model-uri/15/04=CDM \
	--namespace-map http://message-model-uri/15/04=CDM \
	\
	--namespace-map http://www.w3.org/2005/08/addressing=WS::ADDRESSING \
	--namespace-map http://schemas.xmlsoap.org/ws/2004/09/mex=WS::MEX \
	--namespace-map http://docs.oasis-open.org/ws-dd/ns/dpws/2009/01=WS::DPWS \
	--namespace-map http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01=WS::DISCOVERY \
	\
	--namespace-map http://schemas.xmlsoap.org/wsdl/=WS::WSDL \
	--namespace-map http://schemas.xmlsoap.org/wsdl/soap12/=WS::WSDL::SOAP_BINDING \
	\
	--namespace-map http://schemas.xmlsoap.org/ws/2004/08/eventing=WS::EVENTING \
	\
	--namespace-map http://standardized.namespace.org/ws-streaming=WS::STREAMING \
	--namespace-map http://www.w3.org/ns/ws-policy=WS::POLICY \
	--namespace-map http://www.w3.org/2003/05/soap-envelope=MESSAGEMODEL \
	ExtensionPoint.xsd BICEPS_DomainModel.xsd BICEPS_MessageModel.xsd \
	ws-addressing.xsd MetadataExchange.xsd wsdd-dpws-1.1-schema-os.xsd wsdd-discovery-1.1-schema-os.xsd \
	wsdl-custom.xsd wsdl-soap-binding.xsd \
	eventing.xsd \
	ws-policy.xsd ws-streaming.xsd \
	NormalizedMessageModel.xsd

