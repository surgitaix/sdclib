/*
 * AbstractConsumer.cpp
 *
 *  Created on: Jul 23, 2019
 *      Author: rosenau
 */

#include "AbstractConsumer.h"
#include "SDCLib/Util/DebugOut.h"

#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"
#include "SDCLib/Data/SDC/MDIB/MetricQuality.h"
#include "SDCLib/Data/SDC/MDIB/SimpleTypesMapping.h"



using namespace std::placeholders;

namespace SDCLib {
namespace Data {
namespace SDC {
namespace ACS {

class MyConnectionLostHandler : public Data::SDC::SDCConsumerConnectionLostHandler {
public:
	MyConnectionLostHandler(Data::SDC::SDCConsumer & consumer) : consumer(consumer) {
	}
	void onConnectionLost() override {
		std::cerr << "Connection lost, disconnecting... ";
		consumer.disconnect();
		std::cerr << "disconnected." << std::endl;
	}
private:
	Data::SDC::SDCConsumer & consumer;
};

AbstractConsumer::AbstractConsumer() :
		DUTMirrorProvider(nullptr),
		consumer(nullptr),
		connectionLostHandler(nullptr)
		{
}

bool AbstractConsumer::discoverDUT(const std::string& deviceEPR) {

	 // Create a new SDCInstance (no flag will auto init) for Consumer
	    auto t_SDCInstance = std::make_shared<SDCInstance>();
		// Some restriction
		t_SDCInstance->setIP6enabled(false);
		t_SDCInstance->setIP4enabled(true);
		// Bind it to interface that matches the internal criteria (usually the first enumerated)
		if(!t_SDCInstance->bindToDefaultNetworkInterface()) {
			Util::DebugOut(Util::DebugOut::Default, "AbstractConsumer") << "Failed to bind to default network interface! Exit..." << std::endl;
			return false;
		}


		//Discovery of Device under Test
		OSELib::SDC::ServiceManager oscpsm(t_SDCInstance);

		std::unique_ptr<Data::SDC::SDCConsumer> c(oscpsm.discoverEndpointReference(deviceEPR));


		try {
			if (c != nullptr) {
				consumer = std::move(c);
				return true;
			}
			else {
				Util::DebugOut(Util::DebugOut::Default, "AbstractConsumer") << "Discovery failed."; //Not debug out but inform orchestrator
				return false;
			}
		} catch (std::exception & e) {
		Util::DebugOut(Util::DebugOut::Default, "AbstractConsumer") << "Exception: " << e.what() << std::endl; //Not debug out but inform orchestrator
			return false;
		}
}

bool AbstractConsumer::setupMirrorProvider(const std::string& MirrorProviderEndpointReference) {
	auto t_SDCInstanceProvider = std::make_shared<SDCInstance>();		    // Some restriction
	t_SDCInstanceProvider->setIP6enabled(false);
	t_SDCInstanceProvider->setIP4enabled(true);
	// Bind it to interface that matches the internal criteria (usually the first enumerated)
	if(!t_SDCInstanceProvider->bindToDefaultNetworkInterface()) {
		std::cout << "Failed to bind to default network interface! Exit..." << std::endl;
		return false;
	}

	//initialize Mirror Provider which mirrors the behavior of the DUT
	MirrorProvider mirrorProvider(t_SDCInstanceProvider);
	mirrorProvider.setEndpointReference(DUTMirrorProviderEndpointRef != "" ? DUTMirrorProviderEndpointRef : "DUTMirrorProvider");
	Dev::DeviceCharacteristics devChar;
	devChar.addFriendlyName("en", "DUTMirrorProvider");
	mirrorProvider.setDeviceCharacteristics(devChar);
	mirrorProvider.setMdDescription(getConsumerStringRepresentationOfMDIB());
	startMirrorProvider();
	return true;
}

void AbstractConsumer::startMirrorProvider() {
	DUTMirrorProvider->startup();
	DUTMirrorProvider->start();
}

bool AbstractConsumer::addSubscriptionHandler(HandleRef descriptionHandler) {
	return false;
}

bool AbstractConsumer::addSetHandler(HandleRef descriptionHandler) {
	return false;
}

bool AbstractConsumer::addGetHandler(HandleRef descriptionHandler) {
	return false;
}

const std::string AbstractConsumer::getConsumerStringRepresentationOfMDIB() {
	return getStringRepresentationOfMDIB(consumer->getMdib());
}

const std::string AbstractConsumer::getMirrorProviderStringRepresentationOfMDIB() {
	return getStringRepresentationOfMDIB(DUTMirrorProvider->getMdib());
}

const std::string AbstractConsumer::getStringRepresentationOfMDIB(const MdibContainer MDIB) {
	MDM::GetMdibResponse MdibResponse(xml_schema::Uri("0"),ConvertToCDM::convert(MDIB));
	MdibResponse.MdibVersion(MDIB.getMdibVersion());
	const xml_schema::Flags xercesFlags(xml_schema::Flags::dont_validate | xml_schema::Flags::no_xml_declaration | xml_schema::Flags::dont_initialize);
	xml_schema::NamespaceInfomap map;
	std::ostringstream providerMdibStringRepresentation;
	CDM::MdibContainer(providerMdibStringRepresentation, MdibResponse.Mdib(), map, OSELib::XML_ENCODING, xercesFlags);
	return providerMdibStringRepresentation.str();
}

void AbstractConsumer::setupDiscoveryProvider()
{
	auto t_SDCInstance = createDefaultSDCInstance();
	if(t_SDCInstance != nullptr)
	{
		DUTMirrorProvider = std::unique_ptr<MirrorProvider>(new MirrorProvider(t_SDCInstance));
		DUTMirrorProvider->setEndpointReference(DEFAULT_ENDPOINTREFERENCE_DISCOVERY_PROVIDER);


		discoverAvailableEndpointReferencesCaller = std::make_shared<SDCParticipantActivateFunctionCaller>(DISCOVER_AVAILABLE_ENDPOINT_REFERENCES,
			std::bind(&AbstractConsumer::updateAvailableEndpointReferences, this));
		availableEndpointReferencesHandler = std::make_shared<SDCParticipantStringMetricHandler>(GET_AVAILABLE_ENDPOINT_REFERENCES);
		setDUTEndpointReferenceCaller = std::make_shared<SDCParticipantStringFunctionCaller>(SET_DEVICE_UNDER_TEST_ENDPOINT_REF,
			std::bind(&AbstractConsumer::setDUTEndpointRef, this, _1));
		discoverDUTFunctionCaller = std::make_shared<SDCParticipantActivateFunctionCaller>(DISCOVER_DEVICE_UNDER_TEST,
			std::bind(&AbstractConsumer::discoverDUT, this));

		setMirrorProviderEndpointReferenceCaller = std::make_shared<SDCParticipantStringFunctionCaller>(SET_MIRROR_PROVIDER_ENDPOINT_REF,
			std::bind(&AbstractConsumer::setMirrorProviderEndpointRef, this, _1));

		discoverAvailableEndpointReferencesDesc = std::make_shared<ActivateOperationDescriptor>(DISCOVER_AVAILABLE_ENDPOINT_REFERENCES, GET_AVAILABLE_ENDPOINT_REFERENCES);
		availableEndpointReferencesDesc = std::make_shared<StringMetricDescriptor>(GET_AVAILABLE_ENDPOINT_REFERENCES,
				CodedValue(STRING_UNIT),
				MetricCategory::Msrmt,
				MetricAvailability::Intr);

		setDUTEndpointReferncesDesc = std::make_shared<StringMetricDescriptor>(SET_DEVICE_UNDER_TEST_ENDPOINT_REF,
				CodedValue(STRING_UNIT),
				MetricCategory::Set,
				MetricAvailability::Cont);
		discoverDUTFunctionDesc = std::make_shared<ActivateOperationDescriptor>(DISCOVER_DEVICE_UNDER_TEST, SET_DEVICE_UNDER_TEST_ENDPOINT_REF);

		setMirrorProviderEndpointReferenceDesc = std::make_shared<StringMetricDescriptor>(SET_MIRROR_PROVIDER_ENDPOINT_REF,
				CodedValue(STRING_UNIT),
				MetricCategory::Msrmt,
				MetricAvailability::Cont);
		setupMirrorProviderDesc = std::make_shared<ActivateOperationDescriptor>(SETUP_MIRROR_PROVIDER, SET_MIRROR_PROVIDER_ENDPOINT_REF);


		//Channel
		ChannelDescriptor discoveryProviderChannel(DISCOVERY_PROVIDER_CHANNEL);
		discoveryProviderChannel.addMetric(*availableEndpointReferencesDesc);
		discoveryProviderChannel.addMetric(*setDUTEndpointReferncesDesc);
		discoveryProviderChannel.addMetric(*setMirrorProviderEndpointReferenceDesc);
		discoveryProviderChannel.setSafetyClassification(SafetyClassification::Inf);

		//VMD
		VmdDescriptor discoveryProviderVMD(DISCOVERY_PROVIDER_VMD);
		discoveryProviderVMD.addChannel(discoveryProviderChannel);

		MdsDescriptor discoveryProviderMDs(DISCOVERY_PROVIDER_MDS);
		discoveryProviderMDs.createSetOperationForDescriptor(DISCOVER_AVAILABLE_ENDPOINT_REFERENCES);



		DUTMirrorProvider->addMdStateHandler(setDUTEndpointReferenceCaller.get());
		DUTMirrorProvider->addMdStateHandler(discoverAvailableEndpointReferencesCaller.get());
		DUTMirrorProvider->addMdStateHandler(setMirrorProviderEndpointReferenceCaller.get());
		DUTMirrorProvider->addMdStateHandler(availableEndpointReferencesHandler.get());


		DUTMirrorProvider->startup();
		DUTMirrorProvider->start();
	}
}

SDCInstance_shared_ptr AbstractConsumer::createDefaultSDCInstance() {
    auto t_SDCInstance = std::make_shared<SDCInstance>();
    t_SDCInstance->setIP6enabled(false);
	t_SDCInstance->setIP4enabled(true);
	// Bind it to interface that matches the internal criteria (usually the first enumerated)
	if(!t_SDCInstance->bindToDefaultNetworkInterface()) {
		std::cout << "Failed to bind to default network interface! Exit..." << std::endl;
		return nullptr;
	}
	return t_SDCInstance;
}

void AbstractConsumer::setDUTEndpointRef(const std::string& EndpointRef)
{
	DUTEndpointRef = EndpointRef;
}

const std::string& AbstractConsumer::getDUTEndpointRef()
{
	return DUTEndpointRef;
}

void AbstractConsumer::setMirrorProviderEndpointRef(const std::string& EndpointRef)
{
	DUTMirrorProviderEndpointRef = EndpointRef;
}

const std::string& AbstractConsumer::getMirrorProviderEndpointRef()
{
	return DUTMirrorProviderEndpointRef;
}

void AbstractConsumer::updateAvailableEndpointReferences()
{
	availableEndpointReferences.clear();
	OSELib::SDC::ServiceManager oscpsm(createDefaultSDCInstance());
	auto availableDevices = oscpsm.discover();
	for(auto&& device : availableDevices)
	{
		availableEndpointReferences.push_back(device->getEndpointReference());
	}
}



} //ACS
} //SDC
} //Data
} //SDCLib

