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
#include "SDCLib/Data/SDC/MDIB/VmdDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/MdDescription.h"
#include "SDCLib/Data/SDC/MDIB/ScoDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/SetValueOperationDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/SetStringOperationDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/AllowedValue.h"


using namespace std::placeholders;

namespace SDCLib {
namespace Data {
namespace SDC {
namespace ACS {

AbstractConsumer::AbstractConsumer() :
		DiscoveryProvider(nullptr),
		consumer(nullptr),
		connectionLostHandler(nullptr)
{
}

bool AbstractConsumer::discoverDUT() {

	std::cout << "Discovering..." << std::endl;

	    auto t_SDCInstance = createDefaultSDCInstance();

	    if(t_SDCInstance == nullptr)
	    	return false;


		//Discovery of Device under Test
		OSELib::SDC::ServiceManager oscpsm(t_SDCInstance);

		std::unique_ptr<Data::SDC::SDCConsumer> c(oscpsm.discoverEndpointReference(DUTEndpointRef));


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

bool AbstractConsumer::setupMirrorProvider() {
	std::cout << "Setting Up Mirrorprovider" << std::endl;
	auto t_SDCInstanceProvider = std::make_shared<SDCInstance>();		    // Some restriction
	t_SDCInstanceProvider->setIP6enabled(false);
	t_SDCInstanceProvider->setIP4enabled(true);
	// Bind it to interface that matches the internal criteria (usually the first enumerated)
	if(!t_SDCInstanceProvider->bindToDefaultNetworkInterface()) {
		std::cout << "Failed to bind to default network interface! Exit..." << std::endl;
		return false;
	}

	//initialize Mirror Provider which mirrors the behavior of the DUT
	DUTMirrorProvider = std::unique_ptr<MirrorProvider>(new MirrorProvider(t_SDCInstanceProvider));
	DUTMirrorProvider->setEndpointReference(DUTMirrorProviderEndpointRef != "" ? DUTMirrorProviderEndpointRef : "DUTMirrorProvider");
	Dev::DeviceCharacteristics devChar;
	devChar.addFriendlyName("en", "DUTMirrorProvider");
	DUTMirrorProvider->setDeviceCharacteristics(devChar);
	DUTMirrorProvider->setMdDescription(getConsumerStringRepresentationOfMDIB());

	getDUTMDIBCaller = std::make_shared<SDCParticipantGetMDIBCaller>(GET_DUT_MDIB);
	consumer->addParentConsumerToStateHandler(getDUTMDIBCaller.get());
	getDUTMDIBHandler = std::make_shared<SDCProviderStringMetricHandler>(GET_DUT_MDIB);

	getDUTMDIBCallerDesc = std::make_shared<ActivateOperationDescriptor>(GET_DUT_MDIB + ACTIVATE_FOR_GET_OPERATION_ON_DUT_POSTFIX, GET_DUT_MDIB);
	getDUTMDIBDesc = std::make_shared<StringMetricDescriptor>(GET_DUT_MDIB,
		CodedValue(STRING_UNIT),
		MetricCategory::Msrmt,
		MetricAvailability::Intr);
	MdDescription extendedMdDesc = DUTMirrorProvider->getMdDescription();
//
	//Extended MdDescption
	//Channel
	ChannelDescriptor controlDUTChannel(CONTROL_DUT_CHANNEL);

	//VMD
	VmdDescriptor controlDUTVmd(CONTROL_DUT_VMD);

	//MDS

	MdsDescriptor controlDUTMds(CONTROL_DUT_MDS);

	for(auto nms : consumer->getMdib().getMdState().findNumericMetricStates())
	{

		//Check if NumericMetricState is settable
		bool settableState = false;

		for (auto mds : consumer->getMdib().getMdDescription().collectAllMdsDescriptors())
		{
			if(!mds.hasSco())
				continue;
			for(auto setValueOperationDesc : mds.getSco().collectAllSetValueOperationDescriptors())
			{
				if(setValueOperationDesc.getHandle() == (nms.getDescriptorHandle() + "_sco"))
				{
					settableState = true;
				}
			}
		}
		std::shared_ptr<SDCConsumerOperationInvokedHandler> subscribe_ptr(nullptr);
		if(settableState)
		{
			std::cout << nms.getDescriptorHandle() << " is settable" << std::endl;
			auto nmsSetForwarder = std::make_shared<SDCParticipantNumericMetricSetStateForwarder>(nms.getDescriptorHandle());
			numericMetricStateSetForwarder.insert(std::make_pair(nms.getDescriptorHandle(), nmsSetForwarder));
			consumer->addParentConsumerToStateHandler(nmsSetForwarder.get());
			subscribe_ptr = nmsSetForwarder;
		}

		//Creating stateForwarder, which forwards the Device Under Test NumericState from the Abstract Consumer to the MirrorProvider.
		else
		{
			auto nmsForwarder = std::make_shared<SDCParticipantNumericMetricStateForwarder>(nms.getDescriptorHandle());
			numericMetricStateForwarder.insert(std::make_pair(nms.getDescriptorHandle(), nmsForwarder));
			consumer->addParentConsumerToStateHandler(nmsForwarder.get());
			subscribe_ptr = nmsForwarder;
		}

		//Creating GetCaller for NumericMetricState (Activate of this on MirrorProvider side -> Get request of the state on AbstractConsumer side).
		auto nmsGetCaller = std::make_shared<SDCParticipantMDStateGetForwarder<NumericMetricState>>(nms.getDescriptorHandle());
		registeredNumericMetricStateActivateGetCaller.insert(std::make_pair(nms.getDescriptorHandle() + ACTIVATE_FOR_GET_OPERATION_ON_DUT_POSTFIX,
				nmsGetCaller));
		consumer->addParentConsumerToStateHandler(nmsGetCaller.get());

		//Creating Descriptor for the GetCaller and adding it to SCO.
		auto nmsGetCallerDesc = std::make_shared<ActivateOperationDescriptor>(nms.getDescriptorHandle() + ACTIVATE_FOR_GET_OPERATION_ON_DUT_POSTFIX, nms.getDescriptorHandle());
		numericMetricStateActivateGetCallerDescriptors.insert(std::make_pair(nms.getDescriptorHandle() + ACTIVATE_FOR_GET_OPERATION_ON_DUT_POSTFIX,
				nmsGetCallerDesc));
		DUTMirrorProvider->addActivateOperationForDescriptor(*nmsGetCallerDesc, controlDUTMds);

		//Creating SubscribeCaller for NumericMetricState to subscribe to it. Activating the handle -> subscribeState()
		auto nmsSubscribeCaller = std::make_shared<SDCParticipantActivateFunctionCaller>(nms.getDescriptorHandle() + ACTIVATE_FOR_SUBSCRIBE_OPERATION_ON_DUT_POSTFIX,
				[&, subscribe_ptr] () {subscribeState(subscribe_ptr.get());});
		numericMetricStateActivateSubscribeCaller.insert(std::make_pair(nms.getDescriptorHandle() + ACTIVATE_FOR_SUBSCRIBE_OPERATION_ON_DUT_POSTFIX, nmsSubscribeCaller));
		auto nmsSubscribeCallerDesc = std::make_shared<ActivateOperationDescriptor>(nms.getDescriptorHandle() + ACTIVATE_FOR_SUBSCRIBE_OPERATION_ON_DUT_POSTFIX, nms.getDescriptorHandle());
		numericMetricStateSubscribeCallerDescriptors.insert(std::make_pair(nms.getDescriptorHandle() + ACTIVATE_FOR_SUBSCRIBE_OPERATION_ON_DUT_POSTFIX, nmsSubscribeCallerDesc));
		DUTMirrorProvider->addActivateOperationForDescriptor(*nmsSubscribeCallerDesc, controlDUTMds);

		//Creating UnsubscribeCaller for NumericMetricState to unsubscribe from it. Activating the handle -> unsubscribeState()
		auto nmsUnsubscribeCaller = std::make_shared<SDCParticipantActivateFunctionCaller>(nms.getDescriptorHandle() + ACTIVATE_FOR_UNSUBSCRIBE_OPERATION_ON_DUT_POSTFIX,
				[&, subscribe_ptr] () {unsubscribeState(subscribe_ptr.get());});
		numericMetricStateActivateUnsubscribeCaller.insert(std::make_pair(nms.getDescriptorHandle() + ACTIVATE_FOR_UNSUBSCRIBE_OPERATION_ON_DUT_POSTFIX, nmsUnsubscribeCaller));
		auto nmsUnsubscribeCallerDesc = std::make_shared<ActivateOperationDescriptor>(nms.getDescriptorHandle() + ACTIVATE_FOR_UNSUBSCRIBE_OPERATION_ON_DUT_POSTFIX, nms.getDescriptorHandle());
		numericMetricStateUnsubscribeCallerDescriptors.insert(std::make_pair(nms.getDescriptorHandle() + ACTIVATE_FOR_UNSUBSCRIBE_OPERATION_ON_DUT_POSTFIX, nmsUnsubscribeCallerDesc));
		DUTMirrorProvider->addActivateOperationForDescriptor(*nmsUnsubscribeCallerDesc, controlDUTMds);

	}

	for(auto sms : consumer->getMdib().getMdState().findStringMetricStates())
	{
		//Check if NumericMetricState is settable
		bool settableState = false;

		for (auto mds : consumer->getMdib().getMdDescription().collectAllMdsDescriptors())
		{
			if(!mds.hasSco())
				continue;
			for(auto setValueOperationDesc : mds.getSco().collectAllSetStringOperationDescriptors())
			{
				if(setValueOperationDesc.getHandle() == (sms.getDescriptorHandle() + "_sco"))
				{
					settableState = true;
				}
			}
		}
		std::shared_ptr<SDCConsumerOperationInvokedHandler> subscribe_ptr(nullptr);
		if(settableState)
		{
			std::cout << sms.getDescriptorHandle() << " is settable" << std::endl;
			auto smsSetForwarder = std::make_shared<SDCParticipantStringMetricStateSetForwarder>(sms.getDescriptorHandle());
			stringMetricStateSetForwarder.insert(std::make_pair(sms.getDescriptorHandle(), smsSetForwarder));
			consumer->addParentConsumerToStateHandler(smsSetForwarder.get());
			subscribe_ptr = smsSetForwarder;
		}

		//Creating stateForwarder, which forwards the Device Under Test NumericState from the Abstract Consumer to the MirrorProvider.
		else
		{
			auto smsForwarder = std::make_shared<SDCParticipantStringMetricStateForwarder>(sms.getDescriptorHandle());
			stringMetricStateForwarder.insert(std::make_pair(sms.getDescriptorHandle(), smsForwarder));
			consumer->addParentConsumerToStateHandler(smsForwarder.get());
			subscribe_ptr = smsForwarder;
		}


		auto smsGetCaller = std::make_shared<SDCParticipantMDStateGetForwarder<StringMetricState>>(sms.getDescriptorHandle());
		registeredStringMetricStateActivateGetCaller.insert(std::make_pair(sms.getDescriptorHandle() + ACTIVATE_FOR_GET_OPERATION_ON_DUT_POSTFIX,
				smsGetCaller));
		consumer->addParentConsumerToStateHandler(smsGetCaller.get());

		auto smsGetCallerDesc = std::make_shared<ActivateOperationDescriptor>(sms.getDescriptorHandle() + ACTIVATE_FOR_GET_OPERATION_ON_DUT_POSTFIX, sms.getDescriptorHandle());
		stringMetricStateActivateGetCallerDescriptors.insert(std::make_pair(sms.getDescriptorHandle() + ACTIVATE_FOR_GET_OPERATION_ON_DUT_POSTFIX,
				smsGetCallerDesc));
		DUTMirrorProvider->addActivateOperationForDescriptor(*smsGetCallerDesc, controlDUTMds);

		//Creating SubscribeCaller for stringMetricState to subscribe to it. Activating the handle -> subscribeState()
		auto smsSubscribeCaller = std::make_shared<SDCParticipantActivateFunctionCaller>(sms.getDescriptorHandle() + ACTIVATE_FOR_SUBSCRIBE_OPERATION_ON_DUT_POSTFIX,
				[&, subscribe_ptr] () {subscribeState(subscribe_ptr.get());});
		stringMetricStateActivateSubscribeCaller.insert(std::make_pair(sms.getDescriptorHandle() + ACTIVATE_FOR_SUBSCRIBE_OPERATION_ON_DUT_POSTFIX, smsSubscribeCaller));
		auto smsSubscribeCallerDesc = std::make_shared<ActivateOperationDescriptor>(sms.getDescriptorHandle() + ACTIVATE_FOR_SUBSCRIBE_OPERATION_ON_DUT_POSTFIX, sms.getDescriptorHandle());
		stringMetricStateSubscribeCallerDescriptors.insert(std::make_pair(sms.getDescriptorHandle() + ACTIVATE_FOR_SUBSCRIBE_OPERATION_ON_DUT_POSTFIX, smsSubscribeCallerDesc));
		DUTMirrorProvider->addActivateOperationForDescriptor(*smsSubscribeCallerDesc, controlDUTMds);

		//Creating UnsubscribeCaller for stringMetricState to unsubscribe from it. Activating the handle -> unsubscribeState()
		auto smsUnsubscribeCaller = std::make_shared<SDCParticipantActivateFunctionCaller>(sms.getDescriptorHandle() + ACTIVATE_FOR_UNSUBSCRIBE_OPERATION_ON_DUT_POSTFIX,
				[&, subscribe_ptr] () {unsubscribeState(subscribe_ptr.get());});
		stringMetricStateActivateUnsubscribeCaller.insert(std::make_pair(sms.getDescriptorHandle() + ACTIVATE_FOR_UNSUBSCRIBE_OPERATION_ON_DUT_POSTFIX, smsUnsubscribeCaller));
		auto smsUnsubscribeCallerDesc = std::make_shared<ActivateOperationDescriptor>(sms.getDescriptorHandle() + ACTIVATE_FOR_UNSUBSCRIBE_OPERATION_ON_DUT_POSTFIX, sms.getDescriptorHandle());
		stringMetricStateUnsubscribeCallerDescriptors.insert(std::make_pair(sms.getDescriptorHandle() + ACTIVATE_FOR_UNSUBSCRIBE_OPERATION_ON_DUT_POSTFIX, smsUnsubscribeCallerDesc));
		DUTMirrorProvider->addActivateOperationForDescriptor(*smsUnsubscribeCallerDesc, controlDUTMds);
	}

	for(auto rtsams : consumer->getMdib().getMdState().findRealTimeSampleArrayMetricStates())
	{
		auto rtsamsForwarder = std::make_shared<SDCParticipantRealTimeSampleArrayMetricStateForwarder>(rtsams.getDescriptorHandle());
		realTimeSampleArrayMetricStateForwarder.insert(std::make_pair(rtsams.getDescriptorHandle(), rtsamsForwarder));
		auto rtsamsGetCaller = std::make_shared<SDCParticipantMDStateGetForwarder<RealTimeSampleArrayMetricState>>(rtsams.getDescriptorHandle());
		registeredRealTimeSampleArrayMetricStateActivateGetCaller.insert(std::make_pair(rtsams.getDescriptorHandle() + ACTIVATE_FOR_GET_OPERATION_ON_DUT_POSTFIX,
				rtsamsGetCaller));
		consumer->addParentConsumerToStateHandler(rtsamsGetCaller.get());

		auto rtsamsGetCallerDesc = std::make_shared<ActivateOperationDescriptor>(rtsams.getDescriptorHandle() + ACTIVATE_FOR_GET_OPERATION_ON_DUT_POSTFIX, rtsams.getDescriptorHandle());
		realTimeSampleArrayMetricStateActivateGetCallerDescriptors.insert(std::make_pair(rtsams.getDescriptorHandle() + ACTIVATE_FOR_GET_OPERATION_ON_DUT_POSTFIX,
				rtsamsGetCallerDesc));
		DUTMirrorProvider->addActivateOperationForDescriptor(*rtsamsGetCallerDesc, controlDUTMds);
		//Creating SubscribeCaller for stringMetricState to subscribe to it. Activating the handle -> subscribeState()
		auto rtsamsSubscribeCaller = std::make_shared<SDCParticipantActivateFunctionCaller>(rtsams.getDescriptorHandle() + ACTIVATE_FOR_SUBSCRIBE_OPERATION_ON_DUT_POSTFIX,
				[&, rtsamsForwarder] () {subscribeState(rtsamsForwarder.get());});
		realTimeSampleArrayMetricStateActivateSubscribeCaller.insert(std::make_pair(rtsams.getDescriptorHandle() + ACTIVATE_FOR_SUBSCRIBE_OPERATION_ON_DUT_POSTFIX, rtsamsSubscribeCaller));
		auto rtsamsSubscribeCallerDesc = std::make_shared<ActivateOperationDescriptor>(rtsams.getDescriptorHandle() + ACTIVATE_FOR_SUBSCRIBE_OPERATION_ON_DUT_POSTFIX, rtsams.getDescriptorHandle());
		realTimeSampleArrayMetricStateSubscribeCallerDescriptors.insert(std::make_pair(rtsams.getDescriptorHandle() + ACTIVATE_FOR_SUBSCRIBE_OPERATION_ON_DUT_POSTFIX, rtsamsSubscribeCallerDesc));
		DUTMirrorProvider->addActivateOperationForDescriptor(*rtsamsSubscribeCallerDesc, controlDUTMds);

		//Creating UnsubscribeCaller for realTimeSampleArrayMetricState to unsubscribe from it. Activating the handle -> unsubscribeState()
		auto rtsamsUnsubscribeCaller = std::make_shared<SDCParticipantActivateFunctionCaller>(rtsams.getDescriptorHandle() + ACTIVATE_FOR_UNSUBSCRIBE_OPERATION_ON_DUT_POSTFIX,
				[&, rtsamsForwarder] () {unsubscribeState(rtsamsForwarder.get());});
		realTimeSampleArrayMetricStateActivateUnsubscribeCaller.insert(std::make_pair(rtsams.getDescriptorHandle() + ACTIVATE_FOR_UNSUBSCRIBE_OPERATION_ON_DUT_POSTFIX, rtsamsUnsubscribeCaller));
		auto rtsamsUnsubscribeCallerDesc = std::make_shared<ActivateOperationDescriptor>(rtsams.getDescriptorHandle() + ACTIVATE_FOR_UNSUBSCRIBE_OPERATION_ON_DUT_POSTFIX, rtsams.getDescriptorHandle());
		realTimeSampleArrayMetricStateUnsubscribeCallerDescriptors.insert(std::make_pair(rtsams.getDescriptorHandle() + ACTIVATE_FOR_UNSUBSCRIBE_OPERATION_ON_DUT_POSTFIX, rtsamsUnsubscribeCallerDesc));
		DUTMirrorProvider->addActivateOperationForDescriptor(*rtsamsUnsubscribeCallerDesc, controlDUTMds);
	}

	for (auto mds : consumer->getMdib().getMdDescription().collectAllMdsDescriptors())
	{
		if(!mds.hasSco())
			continue;
		for(auto aosdesc : mds.getSco().collectAllActivateOperationDescriptors())
		{
			std::cout << aosdesc.getHandle() << std::endl;
			auto aosForwarder = std::make_shared<SDCParticipantActivateForwarder>(aosdesc.getHandle());
			consumer->addParentConsumerToStateHandler(aosForwarder.get());
			activateForwarder.insert(std::make_pair(aosdesc.getHandle(), aosForwarder));
			DUTMirrorProvider->addActivateOperationForDescriptor(aosdesc, mds);
		}
	}


	controlDUTChannel.addMetric(*getDUTMDIBDesc);


	controlDUTVmd.addChannel(controlDUTChannel);

	controlDUTMds.addVmd(controlDUTVmd);

	DUTMirrorProvider->addActivateOperationForDescriptor(*getDUTMDIBCallerDesc, controlDUTMds);
//
	extendedMdDesc.addMds(controlDUTMds);

	//Add BackBone Control for MessageManipulator
	auto MMMds = getMessageManipulatorControlInterfaceMds();
	extendedMdDesc.addMds(MMMds);

	DUTMirrorProvider->setMdDescription(extendedMdDesc);

//	std::cout << "extendedMd set" << std::endl;
//
	DUTMirrorProvider->addMdStateHandler(getDUTMDIBCaller.get());
	DUTMirrorProvider->addMdStateHandler(getDUTMDIBHandler.get());

	for (auto it : numericMetricStateForwarder)
	{
		DUTMirrorProvider->addMdStateHandler(it.second.get());
	}
	for(auto it : numericMetricStateSetForwarder)
	{
		DUTMirrorProvider->addMdStateHandler(it.second.get());
	}
	for (auto it : registeredNumericMetricStateActivateGetCaller)
	{
		DUTMirrorProvider->addMdStateHandler(it.second.get());
	}
	for(auto it : numericMetricStateActivateSubscribeCaller)
	{
		DUTMirrorProvider->addMdStateHandler(it.second.get());
	}
	for(auto it : numericMetricStateActivateUnsubscribeCaller)
	{
		DUTMirrorProvider->addMdStateHandler(it.second.get());
	}


	for (auto it : stringMetricStateForwarder)
	{
		DUTMirrorProvider->addMdStateHandler(it.second.get());
	}
	for(auto it : stringMetricStateSetForwarder)
	{
		DUTMirrorProvider->addMdStateHandler(it.second.get());
	}
	for (auto it : registeredStringMetricStateActivateGetCaller)
	{
		DUTMirrorProvider->addMdStateHandler(it.second.get());
	}
	for(auto it : stringMetricStateActivateSubscribeCaller)
	{
		DUTMirrorProvider->addMdStateHandler(it.second.get());
	}
	for(auto it : stringMetricStateActivateUnsubscribeCaller)
	{
		DUTMirrorProvider->addMdStateHandler(it.second.get());
	}


	for (auto it : realTimeSampleArrayMetricStateForwarder)
	{
		DUTMirrorProvider->addMdStateHandler(it.second.get());
	}
	for (auto it : registeredRealTimeSampleArrayMetricStateActivateGetCaller)
	{
		DUTMirrorProvider->addMdStateHandler(it.second.get());
	}
	for(auto it : realTimeSampleArrayMetricStateActivateSubscribeCaller)
	{
		DUTMirrorProvider->addMdStateHandler(it.second.get());
	}
	for(auto it : realTimeSampleArrayMetricStateActivateUnsubscribeCaller)
	{
		DUTMirrorProvider->addMdStateHandler(it.second.get());
	}

	for(auto it : activateForwarder)
	{
		DUTMirrorProvider->addMdStateHandler(it.second.get());
	}
	for(auto it : bbTestCaseEnumDescriptors)
	{
		DUTMirrorProvider->createSetOperationForDescriptor<EnumStringMetricDescriptor>(*it.second, MMMds);
	}



//
	//consumer->registerStateEventHandler(getDUTMDIBCaller.get());

	//DiscoveryProvider->shutdown();

	std::cout << "DUT MirrorProvider up and running" << std::endl;

	startMirrorProvider();
	return true;
}

void AbstractConsumer::startMirrorProvider() {
	DUTMirrorProvider->startup();
	DUTMirrorProvider->start();
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
	std::cout << "Setting up DiscoveryProvider!" << std::endl;
	auto t_SDCInstance = createDefaultSDCInstance();
	if(t_SDCInstance != nullptr)
	{
		DiscoveryProvider = std::unique_ptr<MirrorProvider>(new MirrorProvider(t_SDCInstance));
		DiscoveryProvider->setEndpointReference(DEFAULT_ENDPOINTREFERENCE_DISCOVERY_PROVIDER);

		Dev::DeviceCharacteristics devChar;
		devChar.addFriendlyName("en", "SDCLib C DiscoveryProvider");
		devChar.setManufacturer("Lorenz Rosenau");
		devChar.addModelName("en", "sdcDiscoveryProvider");
		DiscoveryProvider->setDeviceCharacteristics(devChar);


		discoverAvailableEndpointReferencesCaller = std::make_shared<SDCParticipantActivateFunctionCaller>(DISCOVER_AVAILABLE_ENDPOINT_REFERENCES,
			[&]() {updateAvailableEndpointReferences();});
		availableEndpointReferencesHandler = std::make_shared<SDCProviderStringMetricHandler>(GET_AVAILABLE_ENDPOINT_REFERENCES);
		setDUTEndpointReferenceCaller = std::make_shared<SDCParticipantStringFunctionCaller>(SET_DEVICE_UNDER_TEST_ENDPOINT_REF,
			[&](std::string EndpointRef) { setDUTEndpointRef(EndpointRef); });
		discoverDUTFunctionCaller = std::make_shared<SDCParticipantActivateFunctionCaller>(DISCOVER_DEVICE_UNDER_TEST,
			[&]() { discoverDUT(); });

		setMirrorProviderEndpointReferenceCaller = std::make_shared<SDCParticipantStringFunctionCaller>(SET_MIRROR_PROVIDER_ENDPOINT_REF,
			[&](std::string EndpointRef) { setMirrorProviderEndpointRef(EndpointRef); });
		setupMirrorProviderCaller = std::make_shared<SDCParticipantActivateFunctionCaller>(SETUP_MIRROR_PROVIDER,
			[&]() { setupMirrorProvider(); });


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
				MetricCategory::Set,
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
		discoveryProviderMDs.addVmd(discoveryProviderVMD);
		DiscoveryProvider->addActivateOperationForDescriptor(*discoverAvailableEndpointReferencesDesc, discoveryProviderMDs);
		DiscoveryProvider->addActivateOperationForDescriptor(*discoverDUTFunctionDesc, discoveryProviderMDs);
		DiscoveryProvider->createSetOperationForDescriptor<StringMetricDescriptor>(*setDUTEndpointReferncesDesc, discoveryProviderMDs);
		DiscoveryProvider->createSetOperationForDescriptor<StringMetricDescriptor>(*setMirrorProviderEndpointReferenceDesc, discoveryProviderMDs);
		DiscoveryProvider->addActivateOperationForDescriptor(*setupMirrorProviderDesc, discoveryProviderMDs);


        // create and add description
		MdDescription discoveryProvidermdDescription;
		discoveryProvidermdDescription.addMdsDescriptor(discoveryProviderMDs);
		auto MMMds = getMessageManipulatorControlInterfaceMds();
		discoveryProvidermdDescription.addMds(MMMds);
		DiscoveryProvider->setMdDescription(discoveryProvidermdDescription);

		for(auto it : bbTestCaseEnumDescriptors)
		{
			DiscoveryProvider->createSetOperationForDescriptor<EnumStringMetricDescriptor>(*it.second, MMMds);
		}



		DiscoveryProvider->addMdStateHandler(discoverAvailableEndpointReferencesCaller.get());
		DiscoveryProvider->addMdStateHandler(availableEndpointReferencesHandler.get());
		DiscoveryProvider->addMdStateHandler(setDUTEndpointReferenceCaller.get());
		DiscoveryProvider->addMdStateHandler(discoverDUTFunctionCaller.get());
		DiscoveryProvider->addMdStateHandler(setMirrorProviderEndpointReferenceCaller.get());
		DiscoveryProvider->addMdStateHandler(setupMirrorProviderCaller.get());


		DiscoveryProvider->startup();
		DiscoveryProvider->start();
		std::cout << "DiscoveryProvider setup" << std::endl;
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
	std::cout << "DUTEndpointRef = " << DUTEndpointRef << std::endl;
}

const std::string& AbstractConsumer::getDUTEndpointRef()
{
	return DUTEndpointRef;
}

void AbstractConsumer::setMirrorProviderEndpointRef(const std::string& EndpointRef)
{
	DUTMirrorProviderEndpointRef = EndpointRef;
	std::cout << "MirrorProviderEndpointRef " <<  DUTMirrorProviderEndpointRef;
}

const std::string& AbstractConsumer::getMirrorProviderEndpointRef()
{
	return DUTMirrorProviderEndpointRef;
}

void AbstractConsumer::updateAvailableEndpointReferences()
{
	std::cout << "updatingAvailableEndpointReferences" << std::endl;
	availableEndpointReferences.clear();

	auto t_SDCInstance = createDefaultSDCInstance();
	if(t_SDCInstance == nullptr)
	{
		std::cout << "Nullptr issue" << std::endl;
		return;
	}
	OSELib::SDC::ServiceManager oscpsm(t_SDCInstance);
	std::cout << "Creating ServiceManager" << std::endl;
	auto availableDevices = oscpsm.discover();
	sleep(2);
	std::cout << availableDevices.size() << std::endl;
	for(auto&& device : availableDevices)
	{
		if (SDCInstance::calcUUIDv5(DEFAULT_ENDPOINTREFERENCE_DISCOVERY_PROVIDER, true) == device->getEndpointReference())
		{
			continue;
		}
		std::cout << device->getEndpointReference() << std::endl;
		availableEndpointReferences.push_back(device->getEndpointReference());
	}
	std::ostringstream oss;
	std::copy(availableEndpointReferences.begin(), availableEndpointReferences.end(),
			  std::ostream_iterator<std::string>(oss, " "));
	availableEndpointReferencesHandler->updateStateValue(oss.str());
}

void AbstractConsumer::subscribeState(SDCConsumerOperationInvokedHandler * handler)
{
	if(handler == nullptr)
	{
		std::cout << "handler is nullptr" << std::endl;
		return;
	}
	std::cout << "registering " << handler->getDescriptorHandle() << std::endl;
	consumer->registerStateEventHandler(handler);
}

void AbstractConsumer::unsubscribeState(SDCConsumerOperationInvokedHandler* handler)
{
	if(handler == nullptr)
	{
		std::cout << "handler is nullptr" << std::endl;
		return;
	}
	consumer->unregisterStateEventHandler(handler);
}

MdsDescriptor AbstractConsumer::getMessageManipulatorControlInterfaceMds()
{
	//Channel
	ChannelDescriptor controlMMChannel(CONTROL_MM_CHANNEL);

	//VMD
	VmdDescriptor controlMMVmd(CONTROL_MM_VMD);

	//MDS
	MdsDescriptor controlMMMds(CONTROL_MM_MDS);

	std::vector<std::string> actionHandles;
	actionHandles.push_back("HELLO");
	actionHandles.push_back("BYE");
	actionHandles.push_back("GET");
	actionHandles.push_back("GET_RESPONSE");
	actionHandles.push_back("GET_METADATA_REQUEST");
	actionHandles.push_back("GET_METADATA_RESPONSE");
	actionHandles.push_back("RESOLVE");
	actionHandles.push_back("RESOLVE_MATCHES");
	actionHandles.push_back("PROBE");
	actionHandles.push_back("PROBE_MATCHES");
	actionHandles.push_back("SUBSCRIBE");
	actionHandles.push_back("SUBSCRIBE_RESPONSE");
	actionHandles.push_back("RENEW");
	actionHandles.push_back("RENEW_RESPONSE");
	actionHandles.push_back("UNSUBSCRIBE");
	actionHandles.push_back("UNSUBSCRIBE_RESPONSE");
	actionHandles.push_back("GETSTATUS");
	actionHandles.push_back("GETSTATUS_RESPONSE");
	actionHandles.push_back("ACTIVATE_REQUEST");
	actionHandles.push_back("ACTIVATE_RESPONSE");
	actionHandles.push_back("GET_CONTEXTSTATES_REQUEST");
	actionHandles.push_back("GET_CONTEXTSTATES_RESPONSE");
	actionHandles.push_back("GET_MDDESCRIPTION_REQUEST");
	actionHandles.push_back("GET_MDDESCRIPTION_RESPONSE");
	actionHandles.push_back("GET_MDIB_REQUEST");
	actionHandles.push_back("GET_MDIB_RESPONSE");
	actionHandles.push_back("GET_MDSTATE_REQUEST");
	actionHandles.push_back("GET_MDSTATE_RESPONSE");
	actionHandles.push_back("SET_ALERT_STATE_REQUEST");
	actionHandles.push_back("SET_ALERT_STATE_RESPONSE");
	actionHandles.push_back("SET_CONTEXT_STATE_REQUEST");
	actionHandles.push_back("SET_CONTEXT_STATE_RESPONSE");
	actionHandles.push_back("SET_STRING_REQUEST");
	actionHandles.push_back("SET_STRING_RESPONSE");
	actionHandles.push_back("DESCRIPTION_MODIFICATION_REPORT");
	actionHandles.push_back("EPISODIC_ALERT_REPORT");
	actionHandles.push_back("PERIODIC_ALERT_REPORT");
	actionHandles.push_back("EPISODIC_CONTEXT_REPORT");
	actionHandles.push_back("PERIODIC_CONTEXT_REPORT");
	actionHandles.push_back("EPISODIC_METRIC_REPORT");
	actionHandles.push_back("PERIODIC_METRIC_REPORT");
	actionHandles.push_back("OPERATION_INVOKED_REPORT");
	actionHandles.push_back("WAVEFORM_STREAM_REPORT");


	for(auto action : actionHandles)
	{
		auto MMControler = std::make_shared<BackBoneTestCaseEnum>(action + MM_BB_CONTROL_ENUM_POSTFIX);
		auto MMControllerDescriptor = std::make_shared<EnumStringMetricDescriptor>(action + MM_BB_CONTROL_ENUM_POSTFIX,
				CodedValue(action + "MM_BB_CONTROL_CODED_ENUM_POSTFIX"),
				MetricCategory::Set,
				MetricAvailability::Cont);
		MMControllerDescriptor->addAllowedValue(AllowedValue(MM_BB_CONTROL_DO_NOTHING));
		MMControllerDescriptor->addAllowedValue(AllowedValue(MM_BB_CONTROL_EMPTY_MESSAGE));
		MMControllerDescriptor->addAllowedValue(AllowedValue(MM_BB_CONTROL_EMPTY_HEADER));
		MMControllerDescriptor->addAllowedValue(AllowedValue(MM_BB_CONTROL_EMPTY_BODY));
		MMControllerDescriptor->addAllowedValue(AllowedValue(MM_BB_CONTROL_RANDOM_MSG_DEFECT));
		bbTestCaseEnumHandles.insert(std::make_pair(action, MMControler));
		bbTestCaseEnumDescriptors.insert(std::make_pair(action, MMControllerDescriptor));
		controlMMChannel.addMetric(*MMControllerDescriptor);
	}


	controlMMVmd.addChannel(controlMMChannel);
//
	controlMMMds.addVmd(controlMMVmd);

	return controlMMMds;
}


} //ACS
} //SDC
} //Data
} //SDCLib

