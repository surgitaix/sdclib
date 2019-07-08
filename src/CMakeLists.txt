# Current Target
set( CURRENT_TARGET_NAME SDCLib )
# Add this for better project structure after cmake generation
project(${CURRENT_TARGET_NAME})

# Add an empty target first - FIXME: Why distinguish here. Does PIC flag solve it?
if(WIN32)
	add_library(${CURRENT_TARGET_NAME} STATIC "")
else()
	add_library(${CURRENT_TARGET_NAME} SHARED "")
endif()

message(STATUS "Adding Target ${CURRENT_TARGET_NAME}...")

# Variables for better handling
set(SRC_DIR ${CMAKE_CURRENT_LIST_DIR})
set(INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/../include)

# Better Handling of Public Header Files
set(TARGET_PUBLIC_HEADERS   ${INCLUDE_DIR}/SDCLib/SDCInstance.h
                            ${INCLUDE_DIR}/SDCLib/Prerequisites.h
                            ${INCLUDE_DIR}/SDCLib/Dev/DeviceCharacteristics.h
                            ${INCLUDE_DIR}/SDCLib/Mainpage.h
                            ${INCLUDE_DIR}/SDCLib/Util/DebugOut.h
                            ${INCLUDE_DIR}/SDCLib/Util/Task.h
                            ${INCLUDE_DIR}/SDCLib/SDCLibrary.h
                            # OSELib
                            ${INCLUDE_DIR}/OSELib/DPWS/Types.h
                            ${INCLUDE_DIR}/OSELib/DPWS/MDPWSHostAdapter.h
                            ${INCLUDE_DIR}/OSELib/DPWS/IService.h
                            ${INCLUDE_DIR}/OSELib/DPWS/DPWSDiscoveryClientSocketImpl.h
                            ${INCLUDE_DIR}/OSELib/DPWS/MDPWSDiscoveryClientAdapter.h
                            ${INCLUDE_DIR}/OSELib/DPWS/OperationTraits.h
                            ${INCLUDE_DIR}/OSELib/DPWS/IEventSink.h
                            ${INCLUDE_DIR}/OSELib/DPWS/PingManager.h
                            ${INCLUDE_DIR}/OSELib/DPWS/DPWSHostSocketImpl.h
                            ${INCLUDE_DIR}/OSELib/DPWS/IDevice.h
                            ${INCLUDE_DIR}/OSELib/DPWS/DPWSCommon.h
                            ${INCLUDE_DIR}/OSELib/DPWS/DeviceHandler.h
                            ${INCLUDE_DIR}/OSELib/DPWS/ISubscriptionManager.h
                            ${INCLUDE_DIR}/OSELib/DPWS/SubscriptionClient.h
                            ${INCLUDE_DIR}/OSELib/DPWS/MessageAdapter.h
                            ${INCLUDE_DIR}/OSELib/DPWS/MetadataProvider.h
                            ${INCLUDE_DIR}/OSELib/DPWS/MessagingContext.h
                            ${INCLUDE_DIR}/OSELib/DPWS/MDPWSStreamingAdapter.h
                            ${INCLUDE_DIR}/OSELib/DPWS/DeviceServiceController.h
                            ${INCLUDE_DIR}/OSELib/DPWS/DPWS11Constants.h
                            ${INCLUDE_DIR}/OSELib/DPWS/SubscriptionManager.h
                            ${INCLUDE_DIR}/OSELib/DPWS/DeviceDescription.h
                            ${INCLUDE_DIR}/OSELib/DPWS/ActiveSubscriptions.h
                            ${INCLUDE_DIR}/OSELib/fwd.h
                            ${INCLUDE_DIR}/OSELib/SDC/ServiceManager.h
                            ${INCLUDE_DIR}/OSELib/SDC/DefaultSDCSchemaGrammarProvider.h
                            ${INCLUDE_DIR}/OSELib/SDC/OperationTraits.h
                            ${INCLUDE_DIR}/OSELib/SDC/WaveformReportServiceHandler.h
                            ${INCLUDE_DIR}/OSELib/SDC/IStateEventServiceEventSink.h
                            ${INCLUDE_DIR}/OSELib/SDC/IEventReport.h
                            ${INCLUDE_DIR}/OSELib/SDC/GetServiceHandler.h
                            ${INCLUDE_DIR}/OSELib/SDC/SetServiceHandler.h
                            ${INCLUDE_DIR}/OSELib/SDC/ISetServiceEventSink.h
                            ${INCLUDE_DIR}/OSELib/SDC/SDCConstants.h
                            ${INCLUDE_DIR}/OSELib/SDC/IContextServiceEventSink.h
                            ${INCLUDE_DIR}/OSELib/SDC/SDCEventServiceController.h
                            ${INCLUDE_DIR}/OSELib/SDC/IGetService.h
                            ${INCLUDE_DIR}/OSELib/SDC/IContextService.h
                            ${INCLUDE_DIR}/OSELib/SDC/SDCServiceController.h
                            ${INCLUDE_DIR}/OSELib/SDC/ContextServiceHandler.h
                            ${INCLUDE_DIR}/OSELib/SDC/ISetService.h
                            ${INCLUDE_DIR}/OSELib/SDC/ContextEventSinkHandler.h
                            ${INCLUDE_DIR}/OSELib/SDC/StateEventServiceEventSinkHandler.h
                            ${INCLUDE_DIR}/OSELib/SDC/ReportTraits.h
                            ${INCLUDE_DIR}/OSELib/SDC/IWaveformService.h
                            ${INCLUDE_DIR}/OSELib/SDC/SetServiceEventSinkHandler.h
                            ${INCLUDE_DIR}/OSELib/SDC/EventReportServiceHandler.h
                            ${INCLUDE_DIR}/OSELib/HTTP/Service.h
                            ${INCLUDE_DIR}/OSELib/HTTP/FrontController.h
                            ${INCLUDE_DIR}/OSELib/HTTP/GenericFileHandler.h
                            ${INCLUDE_DIR}/OSELib/HTTP/HTTPSessionManager.h
                            ${INCLUDE_DIR}/OSELib/HTTP/FrontControllerAdapter.h
                            ${INCLUDE_DIR}/OSELib/HTTP/GenericContentHandler.h
                            ${INCLUDE_DIR}/OSELib/HTTP/HTTPClientExchanger.h
                            ${INCLUDE_DIR}/OSELib/HTTP/StaticContentController.h
                            ${INCLUDE_DIR}/OSELib/WSDL/schema.h
                            ${INCLUDE_DIR}/OSELib/WSDL/WSDLLoader.h
                            ${INCLUDE_DIR}/OSELib/Helper/SchemaGrammarProvider.h
                            ${INCLUDE_DIR}/OSELib/Helper/Message.h
                            ${INCLUDE_DIR}/OSELib/Helper/BufferAdapter.h
                            ${INCLUDE_DIR}/OSELib/Helper/WithLogger.h
                            ${INCLUDE_DIR}/OSELib/Helper/AutoRelease.h
                            ${INCLUDE_DIR}/OSELib/Helper/DurationWrapper.h
                            ${INCLUDE_DIR}/OSELib/Helper/XercesDocumentWrapper.h
                            ${INCLUDE_DIR}/OSELib/Helper/XercesUniqueElementByTagNameFilter.h
                            ${INCLUDE_DIR}/OSELib/Helper/XercesParserWrapper.h
                            ${INCLUDE_DIR}/OSELib/Helper/XercesGrammarPoolProvider.h
                            ${INCLUDE_DIR}/OSELib/Helper/StreamReader.h
                            ${INCLUDE_DIR}/OSELib/SOAP/GenericSoapEventCommand.h
                            ${INCLUDE_DIR}/OSELib/SOAP/Command.h
                            ${INCLUDE_DIR}/OSELib/SOAP/HTTPRequestHandlerExceptionTrap.h
                            ${INCLUDE_DIR}/OSELib/SOAP/SubscribeActionCommand.h
                            ${INCLUDE_DIR}/OSELib/SOAP/NormalizedMessageSerializer.h
                            ${INCLUDE_DIR}/OSELib/SOAP/SoapActionCommand.h
                            ${INCLUDE_DIR}/OSELib/SOAP/NormalizeMessageFilter.h
                            ${INCLUDE_DIR}/OSELib/SOAP/NormalizedMessageAdapter.h
                            ${INCLUDE_DIR}/OSELib/SOAP/SoapFaultCommand.h
                            ${INCLUDE_DIR}/OSELib/SOAP/UnsubscribeActionCommand.h
                            ${INCLUDE_DIR}/OSELib/SOAP/SoapHTTPResponseWrapper.h
                            ${INCLUDE_DIR}/OSELib/SOAP/CommonSoapPreprocessing.h
                            ${INCLUDE_DIR}/OSELib/SOAP/GetMetadataActionCommand.h
                            ${INCLUDE_DIR}/OSELib/SOAP/SoapInvoke.h
                            ${INCLUDE_DIR}/OSELib/SOAP/GetActionCommand.h
                            ${INCLUDE_DIR}/OSELib/SOAP/GenericSoapActionCommand.h
                            ${INCLUDE_DIR}/OSELib/SOAP/RenewActionCommand.h
                            ${INCLUDE_DIR}/OSELib/SOAP/GenericSoapInvoke.h
                            # tclap
                            ${INCLUDE_DIR}/tclap/ValueArg.h
                            ${INCLUDE_DIR}/tclap/StdOutput.h
                            ${INCLUDE_DIR}/tclap/VersionVisitor.h
                            ${INCLUDE_DIR}/tclap/UnlabeledValueArg.h
                            ${INCLUDE_DIR}/tclap/SwitchArg.h
                            ${INCLUDE_DIR}/tclap/MultiArg.h
                            ${INCLUDE_DIR}/tclap/UnlabeledMultiArg.h
                            ${INCLUDE_DIR}/tclap/ZshCompletionOutput.h
                            ${INCLUDE_DIR}/tclap/OptionalUnlabeledTracker.h
                            ${INCLUDE_DIR}/tclap/ArgException.h
                            ${INCLUDE_DIR}/tclap/ArgTraits.h
                            ${INCLUDE_DIR}/tclap/CmdLineInterface.h
                            ${INCLUDE_DIR}/tclap/StandardTraits.h
                            ${INCLUDE_DIR}/tclap/CmdLineOutput.h
                            ${INCLUDE_DIR}/tclap/DocBookOutput.h
                            ${INCLUDE_DIR}/tclap/MultiSwitchArg.h
                            ${INCLUDE_DIR}/tclap/XorHandler.h
                            ${INCLUDE_DIR}/tclap/CmdLine.h
                            ${INCLUDE_DIR}/tclap/Visitor.h
                            ${INCLUDE_DIR}/tclap/Arg.h
                            ${INCLUDE_DIR}/tclap/Constraint.h
                            ${INCLUDE_DIR}/tclap/ValuesConstraint.h
                            ${INCLUDE_DIR}/tclap/HelpVisitor.h
                            ${INCLUDE_DIR}/tclap/IgnoreRestVisitor.h
                            # SDCLib
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/SDCProviderMDStateHandler.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/SDCProviderStateHandler.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/SDCConsumerSubscriptionLostHandler.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/SDCProviderComponentStateHandler.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/WorkflowContextState.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/ReferenceRange.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricState.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/DicomTransferCapability.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/CalibrationResult.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/WorkflowContextDescriptor.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/PerformedOrderDetail.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/ScoState.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/MeansContextDescriptor.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/ContainmentTree.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/DicomNetworkAe.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/DicomNetworkConnection.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/SetValueOperationDescriptor.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/SystemContextDescriptor.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/LimitAlertConditionState.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/Measurement.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/PatientContextDescriptor.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/SetStringOperationDescriptor.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/AllowedValue.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/Range.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/EnumStringMetricDescriptor.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/MdsState.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/LocationReference.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/BaseDemographics.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/LocationContextState.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/ClockDescriptor.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/MetaData.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/ChannelState.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/AlertSignalDescriptor.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/OperatorContextState.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/AlertSignalState.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/SetMetricStateOperationState.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/StringMetricDescriptor.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/OrderDetail.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/ChannelDescriptor.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/PatientDemographicsCoreData.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/SetComponentStateOperationState.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/NumericMetricDescriptor.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/MdDescription.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/SampleArrayValue.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/StringMetricValue.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/InstanceIdentifier.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/Translation.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/SetContextStateOperationDescriptor.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/RequestedOrderDetail.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/PatientContextState.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/SystemContextState.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/LimitAlertConditionDescriptor.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/VmdState.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/MdState.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/Relation.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/CodedValue.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/Argument.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/PersonParticipation.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/BatteryState.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/RelatedMeasurement.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/BatteryDescriptor.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/ContainmentTreeEntry.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/ApprovedJurisdictions.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/NumericMetricState.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/MDIB-fwd.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/SetComponentStateOperationDescriptor.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/LocalizedText.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/StringMetricState.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/RemedyInfo.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/CalibrationDocumentation.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/Mdib.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/SimpleTypesMapping.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/Udi.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/WorkflowDetail.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/AlertConditionDescriptor.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/SetAlertStateOperationState.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/CauseInfo.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/Defaults.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/Annotation.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/SystemSignalActivation.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/AlertConditionState.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/ClockState.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/EnsembleContextDescriptor.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/OperatingJurisdiction.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/ApplyAnnotation.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/CalibrationInfo.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/LocationDetail.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/ScoDescriptor.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/MeansContextState.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/OperatorContextDescriptor.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/AllowedValues.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/NeonatalPatientDemographicsCoreData.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/LocationContextDescriptor.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/PersonReference.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/ActivateOperationDescriptor.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/ConvertToCDM.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/ActivateOperationState.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/ClinicalInfo.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/VmdDescriptor.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/DistributionSampleArrayMetricDescriptor.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/AlertSystemDescriptor.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/ImagingProcedure.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/SetValueOperationState.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/MdsDescriptor.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/AlertSystemState.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/SetAlertStateOperationDescriptor.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/EnumStringMetricState.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/DistributionSampleArrayMetricState.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/EnsembleContextState.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/MetricQuality.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/ConvertFromCDM.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/SetStringOperationState.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/SetMetricStateOperationDescriptor.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/SetContextStateOperationState.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/custom/MdibContainer.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/custom/EnsembleContextDescriptor.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/custom/OperationInvocationContext.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/OperationGroup.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/PhysicalConnectorInfo.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/ProductionSpecification.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/NumericMetricValue.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricDescriptor.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/MDIB/DicomDeviceDescriptor.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/SDC-fwd.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/SDCConsumerConnectionLostHandler.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/SDCConsumerMDStateHandler.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/SDCConsumerOperationInvokedHandler.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/FutureInvocationState.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/SDCProviderAdapter.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/SDCProviderAlertConditionStateHandler.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/SDCConsumer.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/SDCProviderActivateOperationHandler.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/SDCConsumerAdapter.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/WSDL/StateEventServiceWSDL.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/WSDL/SetServiceWSDL.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/WSDL/GetServiceWSDL.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/WSDL/WaveformServiceWSDL.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/WSDL/ContextServiceWSDL.h
                            ${INCLUDE_DIR}/SDCLib/Data/SDC/SDCProvider.h
)


# Add the sources to the target
target_sources(${CURRENT_TARGET_NAME}
    PRIVATE
        # Source Files
        # SDCLib
        ${SRC_DIR}/SDCLib/SDCLibrary.cpp
        ${SRC_DIR}/SDCLib/SDCInstance.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/ActivateOperationDescriptor.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/ActivateOperationState.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/AlertConditionDescriptor.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/AlertConditionState.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/AlertSignalDescriptor.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/AlertSignalState.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/AlertSystemDescriptor.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/AlertSystemState.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/AllowedValue.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/AllowedValues.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/Annotation.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/ApplyAnnotation.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/ApprovedJurisdictions.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/Argument.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/BaseDemographics.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/BatteryDescriptor.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/BatteryState.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/CalibrationDocumentation.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/CalibrationInfo.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/CalibrationResult.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/CauseInfo.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/ChannelDescriptor.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/ChannelState.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/ClinicalInfo.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/ClockDescriptor.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/ClockState.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/CodedValue.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/ContainmentTree.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/ContainmentTreeEntry.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/ConvertFromCDM.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/ConvertToCDM.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/Defaults.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/DicomDeviceDescriptor.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/DicomNetworkAe.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/DicomNetworkConnection.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/DicomTransferCapability.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/DistributionSampleArrayMetricDescriptor.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/DistributionSampleArrayMetricState.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/EnsembleContextDescriptor.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/EnsembleContextState.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/EnumStringMetricDescriptor.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/EnumStringMetricState.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/ImagingProcedure.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/InstanceIdentifier.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/LimitAlertConditionDescriptor.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/LimitAlertConditionState.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/LocalizedText.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/LocationContextDescriptor.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/LocationContextState.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/LocationDetail.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/LocationReference.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/MdDescription.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/Mdib.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/MdsDescriptor.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/MdsState.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/MdState.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/MeansContextDescriptor.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/MeansContextState.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/Measurement.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/MetaData.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/MetricQuality.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/NeonatalPatientDemographicsCoreData.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/NumericMetricDescriptor.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/NumericMetricState.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/NumericMetricValue.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/OperatingJurisdiction.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/OperationGroup.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/OperatorContextDescriptor.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/OperatorContextState.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/OrderDetail.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/PatientContextDescriptor.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/PatientContextState.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/PatientDemographicsCoreData.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/PerformedOrderDetail.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/PersonParticipation.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/PersonReference.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/PhysicalConnectorInfo.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/ProductionSpecification.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/Range.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricDescriptor.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricState.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/ReferenceRange.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/RelatedMeasurement.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/Relation.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/RemedyInfo.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/RequestedOrderDetail.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/SampleArrayValue.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/ScoDescriptor.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/ScoState.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/SetAlertStateOperationDescriptor.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/SetAlertStateOperationState.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/SetComponentStateOperationDescriptor.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/SetComponentStateOperationState.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/SetContextStateOperationDescriptor.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/SetContextStateOperationState.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/SetMetricStateOperationDescriptor.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/SetMetricStateOperationState.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/SetStringOperationDescriptor.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/SetStringOperationState.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/SetValueOperationDescriptor.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/SetValueOperationState.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/SimpleTypesMapping.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/StringMetricDescriptor.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/StringMetricState.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/StringMetricValue.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/SystemContextDescriptor.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/SystemContextState.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/SystemSignalActivation.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/Translation.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/Udi.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/VmdDescriptor.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/VmdState.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/WorkflowContextDescriptor.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/WorkflowContextState.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/WorkflowDetail.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/custom/AlertSystemDescriptorCustomImpl.cxx
        #${SRC_DIR}/SDCLib/Data/SDC/MDIB/custom/Base64BinaryCustomImpl.cxx
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/custom/ChannelDescriptorCustomImpl.cxx
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/custom/MdDescriptionCustomImpl.cxx
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/custom/MdibContainer.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/custom/MdStateCustomImpl.cxx
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/custom/OperationInvocationContext.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/MDIB/custom/ScoDescriptorCustomImpl.cxx
        #${SRC_DIR}/SDCLib/Data/SDC/MDIB/AbstractDescriptor.cpp
        #${SRC_DIR}/SDCLib/Data/SDC/MDIB/AbstractMetricDescriptor.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/FutureInvocationState.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/SDCConsumer.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/SDCConsumerOperationInvokedHandler.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/SDCProvider.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/SDCProviderStateHandler.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/SDCConsumerAdapter.cpp
        ${SRC_DIR}/SDCLib/Data/SDC/SDCProviderAdapter.cpp
        ${SRC_DIR}/SDCLib/Dev/DeviceCharacteristics.cpp
        ${SRC_DIR}/SDCLib/Util/DebugOut.cpp
        ${SRC_DIR}/SDCLib/Util/Task.cpp
        #
        # OSELib
        ${SRC_DIR}/OSELib/DPWS/ActiveSubscriptions.cpp
        ${SRC_DIR}/OSELib/DPWS/DeviceDescription.cpp
        ${SRC_DIR}/OSELib/DPWS/DeviceHandler.cpp
        ${SRC_DIR}/OSELib/DPWS/DeviceServiceController.cpp
        ${SRC_DIR}/OSELib/DPWS/MDPWSDiscoveryClientAdapter.cpp
        ${SRC_DIR}/OSELib/DPWS/DPWSCommon.cpp
        ${SRC_DIR}/OSELib/DPWS/DPWSDiscoveryClientSocketImpl.cpp
        ${SRC_DIR}/OSELib/DPWS/MDPWSStreamingAdapter.cpp
        ${SRC_DIR}/OSELib/DPWS/DPWSHostSocketImpl.cpp
        ${SRC_DIR}/OSELib/DPWS/MDPWSHostAdapter.cpp
        ${SRC_DIR}/OSELib/DPWS/MessageAdapter.cpp
        ${SRC_DIR}/OSELib/DPWS/MessagingContext.cpp
        ${SRC_DIR}/OSELib/DPWS/MetadataProvider.cpp
        ${SRC_DIR}/OSELib/DPWS/OperationTraits.cpp
        ${SRC_DIR}/OSELib/DPWS/PingManager.cpp
        ${SRC_DIR}/OSELib/DPWS/SubscriptionClient.cpp
        ${SRC_DIR}/OSELib/DPWS/SubscriptionManager.cpp
        ${SRC_DIR}/OSELib/Helper/BufferAdapter.cpp
        ${SRC_DIR}/OSELib/Helper/DurationWrapper.cpp
        ${SRC_DIR}/OSELib/Helper/Message.cpp
        ${SRC_DIR}/OSELib/Helper/SchemaGrammarProvider.cpp
        ${SRC_DIR}/OSELib/Helper/StreamReader.cpp
        ${SRC_DIR}/OSELib/Helper/WithLogger.cpp
        ${SRC_DIR}/OSELib/Helper/XercesDocumentWrapper.cpp
        ${SRC_DIR}/OSELib/Helper/XercesParserWrapper.cpp
        ${SRC_DIR}/OSELib/Helper/XercesUniqueElementByTagNameFilter.cpp
        ${SRC_DIR}/OSELib/HTTP/FrontControllerAdapter.cpp
        ${SRC_DIR}/OSELib/HTTP/FrontController.cpp
        ${SRC_DIR}/OSELib/HTTP/GenericContentHandler.cpp
        ${SRC_DIR}/OSELib/HTTP/GenericFileHandler.cpp
        ${SRC_DIR}/OSELib/HTTP/HTTPClientExchanger.cpp
        ${SRC_DIR}/OSELib/HTTP/HTTPSessionManager.cpp
        ${SRC_DIR}/OSELib/HTTP/Service.cpp
        ${SRC_DIR}/OSELib/HTTP/StaticContentController.cpp
        ${SRC_DIR}/OSELib/SDC/ContextEventSinkHandler.cpp
        ${SRC_DIR}/OSELib/SDC/ContextServiceHandler.cpp
        ${SRC_DIR}/OSELib/SDC/DefaultSDCSchemaGrammarProvider.cpp
        ${SRC_DIR}/OSELib/SDC/StateEventServiceEventSinkHandler.cpp
        ${SRC_DIR}/OSELib/SDC/EventReportServiceHandler.cpp
        ${SRC_DIR}/OSELib/SDC/GetServiceHandler.cpp
        ${SRC_DIR}/OSELib/SDC/OperationTraits.cpp
        ${SRC_DIR}/OSELib/SDC/ReportTraits.cpp
        ${SRC_DIR}/OSELib/SDC/ServiceManager.cpp
        ${SRC_DIR}/OSELib/SDC/SetServiceHandler.cpp
        ${SRC_DIR}/OSELib/SDC/SetServiceEventSinkHandler.cpp
        ${SRC_DIR}/OSELib/SOAP/CommonSoapPreprocessing.cpp
        ${SRC_DIR}/OSELib/SOAP/GetActionCommand.cpp
        ${SRC_DIR}/OSELib/SOAP/GetMetadataActionCommand.cpp
        ${SRC_DIR}/OSELib/SOAP/HTTPRequestHandlerExceptionTrap.cpp
        ${SRC_DIR}/OSELib/SOAP/NormalizedMessageAdapter.cpp
        ${SRC_DIR}/OSELib/SOAP/NormalizedMessageSerializer.cpp
        ${SRC_DIR}/OSELib/SOAP/NormalizeMessageFilter.cpp
        ${SRC_DIR}/OSELib/SOAP/RenewActionCommand.cpp
        ${SRC_DIR}/OSELib/SOAP/SoapActionCommand.cpp
        ${SRC_DIR}/OSELib/SOAP/SoapFaultCommand.cpp
        ${SRC_DIR}/OSELib/SOAP/SoapHTTPResponseWrapper.cpp
        ${SRC_DIR}/OSELib/SOAP/SoapInvoke.cpp
        ${SRC_DIR}/OSELib/SOAP/SubscribeActionCommand.cpp
        ${SRC_DIR}/OSELib/SOAP/UnsubscribeActionCommand.cpp
        ${SRC_DIR}/OSELib/SDC/WaveformReportServiceHandler.cpp
        ${SRC_DIR}/OSELib/WSDL/WSDLLoader.cpp
        #
        # Add the includes too (for better generation)
        # Private Headers
        ${TARGET_PUBLIC_HEADERS}
        ${INCLUDE_DIR}/config/config.h
    PUBLIC
        ${TARGET_PUBLIC_HEADERS}
)

# Make sure include dirs can be found inside the project
target_include_directories( ${CURRENT_TARGET_NAME} PUBLIC ${SRC_DIR} )
target_include_directories( ${CURRENT_TARGET_NAME} PUBLIC ${PATH_SRC_ROOT} )
target_include_directories( ${CURRENT_TARGET_NAME} PUBLIC ${PATH_INCLUDE_ROOT} )

# Poco
target_compile_definitions( ${CURRENT_TARGET_NAME} PUBLIC POCO_NO_AUTOMATIC_LIBS )
target_compile_definitions( ${CURRENT_TARGET_NAME} PUBLIC Foundation_EXPORTS )
target_compile_definitions( ${CURRENT_TARGET_NAME} PUBLIC Net_EXPORTS )
target_include_directories( ${CURRENT_TARGET_NAME} PUBLIC ${PATH_POCO_INCLUDE})


# Some Definitions -Temp solution
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # enable debug and profiling informations for sprof
    target_compile_options(${CURRENT_TARGET_NAME} -ggdb -g -O0)
endif()


# Packages

# DataModel
target_sources(${CURRENT_TARGET_NAME} PUBLIC $<TARGET_OBJECTS:DataModel>)
# Note: 2nd line for cmake < 3.12
target_include_directories( ${CURRENT_TARGET_NAME} PUBLIC $<TARGET_PROPERTY:DataModel,INTERFACE_INCLUDE_DIRECTORIES>)

# Threads
target_link_libraries(${CURRENT_TARGET_NAME} PUBLIC ${CMAKE_THREAD_LIBS_INIT})
# Xerces
target_link_libraries(${CURRENT_TARGET_NAME} PUBLIC ${XercesLibrary})
# Poco
target_link_libraries(${CURRENT_TARGET_NAME} PUBLIC ${POCO_LIBRARIES})


# build
set_target_properties(  ${CURRENT_TARGET_NAME}
                        PROPERTIES
                        RUNTIME_OUTPUT_DIRECTORY ${PATH_RUNTIME_OUTPUT}
                        LIBRARY_OUTPUT_DIRECTORY ${PATH_LIBRARY_OUTPUT}
                        ARCHIVE_OUTPUT_DIRECTORY ${PATH_ARCHIVE_OUTPUT}
                        DEBUG_POSTFIX ${DEBUG_POSTFIX_OUTPUT}
                        )
# install
install(TARGETS ${CURRENT_TARGET_NAME} CONFIGURATIONS ${CMAKE_BUILD_TYPE}
            RUNTIME DESTINATION ${PATH_INSTALL_RUNTIME}
            LIBRARY DESTINATION ${PATH_INSTALL_LIBRARY}
            ARCHIVE DESTINATION ${PATH_INSTALL_ARCHIVE}
)
install(DIRECTORY ${INCLUDE_DIR}/ DESTINATION ${PATH_INSTALL_INCLUDE}/${CURRENT_TARGET_NAME})

# ...
