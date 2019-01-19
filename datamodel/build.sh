#!/bin/bash
################################################################################
#
# Author: Fabian Baumeister, TODO
#
# Helper script for xsdcxx
#
################################################################################


# Name of the folder
DIRNAME=generated

# Cleanup
echo "Cleanup..."
rm -rf $DIRNAME

# Create the new dir
echo "Creating new Folder..."
mkdir $DIRNAME

# Switch to xsd dir
cd ./xsd/

echo "Generating!"
# if not xsd 4.0 is installed but xsd 3.3: call xsdcxx instead
xsdcxx cxx-tree \
    --output-dir ../$DIRNAME \
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
	--namespace-map http://standards.ieee.org/downloads/11073/11073-10207-2017/participant=CDM \
	--namespace-map http://standards.ieee.org/downloads/11073/11073-10207-2017/extension=EXT \
	--namespace-map http://standards.ieee.org/downloads/11073/11073-10207-2017/message=MDM \
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
	--namespace-map http://standards.ieee.org/downloads/11073/11073-20702-2016=MDPWS \
	--namespace-map http://www.w3.org/ns/ws-policy=WS::POLICY \
	--namespace-map http://www.w3.org/2003/05/soap-envelope=MESSAGEMODEL \
	\
	--namespace-map http://dicom-extension-uri/09/08=CDM \
	ExtensionPoint.xsd BICEPS_ParticipantModel.xsd BICEPS_MessageModel.xsd \
	ws-addressing.xsd MetadataExchange.xsd wsdd-dpws-1.1-schema-os.xsd wsdd-discovery-1.1-schema-os.xsd \
	wsdl-custom.xsd wsdl-soap-binding.xsd \
	MDPWS.xsd \
	eventing.xsd \
	ws-policy.xsd ws-streaming.xsd \
	NormalizedMessageModel.xsd \
	DICOMDeviceDescription.xsd

	
	
# tmp solution
cd ..

cp osdm.hxx $DIRNAME/osdm.hxx
cp osdm-fwd.hxx $DIRNAME/osdm-fwd.hxx

