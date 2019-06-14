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


# Better Handling of Public Header Files
set(TARGET_PUBLIC_HEADERS   "")


# Add the sources to the target
target_sources(${CURRENT_TARGET_NAME}
    PRIVATE
        # Source Files
        # SDCLib
        ${SRC_DIR}/SDCLib/SDCLibrary.cpp
        ${SRC_DIR}/SDCLib/SDCLibrary2.cpp
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
        # Public Headers
        #${TARGET_PUBLIC_HEADERS}
    #PUBLIC
        #${TARGET_PUBLIC_HEADERS}
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

# ...
