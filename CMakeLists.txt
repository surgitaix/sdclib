#set(CMAKE_VERBOSE_MAKEFILE ON)
PROJECT (SDCLib)
option(debug "Debug build" ON)
option(crossCompile "Cross compile for arm" OFF)

cmake_minimum_required(VERSION 2.8)
SET(ARCH "x86_64")

if (crossCompile)
    set(CMAKE_C_COMPILER "arm-linux-gnueabihf-gcc")
    set(CMAKE_CXX_COMPILER "arm-linux-gnueabihf-g++")
    SET(ARCH "arm-linux")
endif()

# define output directories for binaries
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Configure paths for your environment 
# - CAN be omitted in linux, if all dependencies (except pthread) are installed on the system using 'make install'
# - MUST be specified for ARM cross-compilation!
# Includes
SET(XERCES_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/../xerces/include" CACHE PATH "Path to XERCES-C includes")
SET(PTHREAD_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/../pthread/include" CACHE PATH "Path to PTHREAD includes")
SET(XSDCXX_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/../xsd/include" CACHE PATH "Path to XSDCXX includes")

# Libraries
SET(PTHREAD_LIB_DIR "${PROJECT_SOURCE_DIR}/../pthread/lib/" CACHE PATH "Path to PTHREAD libraries.")
SET(XERCES_LIB_DIR "${PROJECT_SOURCE_DIR}/../xerces/lib/" CACHE PATH "Path to XERCES-C libraries.")

INCLUDE_DIRECTORIES("include" "datamodel" "datamodel/generated" ${XSDCXX_INCLUDE_DIR} ${XERCES_INCLUDE_DIR} ${PTHREAD_INCLUDE_DIR})
LINK_DIRECTORIES(${PTHREAD_LIB_DIR} ${XERCES_LIB_DIR} ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

# Debug or Release build
if (debug)
    SET(CMAKE_BUILD_TYPE Debug)
    if(NOT WIN32)
        # enable debug and profiling informations for sprof
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -g -O0 -Wall -Wextra")    
    endif()
else()
    SET(CMAKE_BUILD_TYPE Release)
endif()

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
	message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()


IF (${CMAKE_SYSTEM_NAME} MATCHES "Linux") 
    ADD_DEFINITIONS(-D_POCO_NO_AUTOMATIC_LIBS)
    ADD_DEFINITIONS(-D_Foundation_EXPORTS)
    ADD_DEFINITIONS(-D_Net_EXPORTS)

    ADD_DEFINITIONS(-D_LINUX)
    ADD_DEFINITIONS(-Dlinux)
    # constexpr macro / checking for C++11 is done above allready
    add_definitions(-DCONSTEXPR_MACRO=constexpr)

    set(XERCES_LIB xerces-c)
    set(PTHREAD_LIB pthread)
    set(PYTHON_LIB python2.7)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

IF (${CMAKE_SYSTEM_NAME} MATCHES "Windows") 
    ADD_DEFINITIONS(-DPOCO_NO_AUTOMATIC_LIBS)
    ADD_DEFINITIONS(-DFoundation_EXPORTS)
    ADD_DEFINITIONS(-DNet_EXPORTS)

    ADD_DEFINITIONS(-D_WIN32)
    if (CMAKE_BUILD_TYPE STREQUAL Debug)
        set(XERCES_LIB xerces-c_3D)
    else ()
        set(XERCES_LIB xerces-c_3)
    endif()

    # define preprocessor macros for Visual Studio: no CONSTEXPR_MACRO before VS15
    MESSAGE( STATUS "MSVS compiler version: " ${CMAKE_CXX_COMPILER_VERSION} )
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.00)
        add_definitions(-DCONSTEXPR_MACRO= )
    else()
        add_definitions(-DCONSTEXPR_MACRO=constexpr)
    endif()
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

set(SDCLibSOURCES

./src/OSCLib/SDCLibrary.cpp
./src/OSCLib/SDCLibrary2.cpp
./src/OSCLib/SDCInstance.cpp
./src/OSCLib/Data/SDC/MDIB/ActivateOperationDescriptor.cpp
./src/OSCLib/Data/SDC/MDIB/ActivateOperationState.cpp
./src/OSCLib/Data/SDC/MDIB/AlertConditionDescriptor.cpp
./src/OSCLib/Data/SDC/MDIB/AlertConditionState.cpp
./src/OSCLib/Data/SDC/MDIB/AlertSignalDescriptor.cpp
./src/OSCLib/Data/SDC/MDIB/AlertSignalState.cpp
./src/OSCLib/Data/SDC/MDIB/AlertSystemDescriptor.cpp
./src/OSCLib/Data/SDC/MDIB/AlertSystemState.cpp
./src/OSCLib/Data/SDC/MDIB/AllowedValue.cpp
./src/OSCLib/Data/SDC/MDIB/AllowedValues.cpp
./src/OSCLib/Data/SDC/MDIB/Annotation.cpp
./src/OSCLib/Data/SDC/MDIB/ApplyAnnotation.cpp
./src/OSCLib/Data/SDC/MDIB/ApprovedJurisdictions.cpp
./src/OSCLib/Data/SDC/MDIB/Argument.cpp
./src/OSCLib/Data/SDC/MDIB/BaseDemographics.cpp
./src/OSCLib/Data/SDC/MDIB/BatteryDescriptor.cpp
./src/OSCLib/Data/SDC/MDIB/BatteryState.cpp
./src/OSCLib/Data/SDC/MDIB/CalibrationDocumentation.cpp
./src/OSCLib/Data/SDC/MDIB/CalibrationInfo.cpp
./src/OSCLib/Data/SDC/MDIB/CalibrationResult.cpp
./src/OSCLib/Data/SDC/MDIB/CauseInfo.cpp
./src/OSCLib/Data/SDC/MDIB/ChannelDescriptor.cpp
./src/OSCLib/Data/SDC/MDIB/ChannelState.cpp
./src/OSCLib/Data/SDC/MDIB/ClinicalInfo.cpp
./src/OSCLib/Data/SDC/MDIB/ClockDescriptor.cpp
./src/OSCLib/Data/SDC/MDIB/ClockState.cpp
./src/OSCLib/Data/SDC/MDIB/CodedValue.cpp
./src/OSCLib/Data/SDC/MDIB/ContainmentTree.cpp
./src/OSCLib/Data/SDC/MDIB/ContainmentTreeEntry.cpp
./src/OSCLib/Data/SDC/MDIB/ConvertFromCDM.cpp
./src/OSCLib/Data/SDC/MDIB/ConvertToCDM.cpp
./src/OSCLib/Data/SDC/MDIB/Defaults.cpp
./src/OSCLib/Data/SDC/MDIB/DicomDeviceDescriptor.cpp
./src/OSCLib/Data/SDC/MDIB/DicomNetworkAe.cpp
./src/OSCLib/Data/SDC/MDIB/DicomNetworkConnection.cpp
./src/OSCLib/Data/SDC/MDIB/DicomTransferCapability.cpp
./src/OSCLib/Data/SDC/MDIB/DistributionSampleArrayMetricDescriptor.cpp
./src/OSCLib/Data/SDC/MDIB/DistributionSampleArrayMetricState.cpp
./src/OSCLib/Data/SDC/MDIB/EnsembleContextDescriptor.cpp
./src/OSCLib/Data/SDC/MDIB/EnsembleContextState.cpp
./src/OSCLib/Data/SDC/MDIB/EnumStringMetricDescriptor.cpp
./src/OSCLib/Data/SDC/MDIB/EnumStringMetricState.cpp
./src/OSCLib/Data/SDC/MDIB/ImagingProcedure.cpp
./src/OSCLib/Data/SDC/MDIB/InstanceIdentifier.cpp
./src/OSCLib/Data/SDC/MDIB/LimitAlertConditionDescriptor.cpp
./src/OSCLib/Data/SDC/MDIB/LimitAlertConditionState.cpp
./src/OSCLib/Data/SDC/MDIB/LocalizedText.cpp
./src/OSCLib/Data/SDC/MDIB/LocationContextDescriptor.cpp
./src/OSCLib/Data/SDC/MDIB/LocationContextState.cpp
./src/OSCLib/Data/SDC/MDIB/LocationDetail.cpp
./src/OSCLib/Data/SDC/MDIB/LocationReference.cpp
./src/OSCLib/Data/SDC/MDIB/MdDescription.cpp
./src/OSCLib/Data/SDC/MDIB/Mdib.cpp
./src/OSCLib/Data/SDC/MDIB/MdsDescriptor.cpp
./src/OSCLib/Data/SDC/MDIB/MdsState.cpp
./src/OSCLib/Data/SDC/MDIB/MdState.cpp
./src/OSCLib/Data/SDC/MDIB/MeansContextDescriptor.cpp
./src/OSCLib/Data/SDC/MDIB/MeansContextState.cpp
./src/OSCLib/Data/SDC/MDIB/Measurement.cpp
./src/OSCLib/Data/SDC/MDIB/MetaData.cpp
./src/OSCLib/Data/SDC/MDIB/MetricQuality.cpp
./src/OSCLib/Data/SDC/MDIB/NeonatalPatientDemographicsCoreData.cpp
./src/OSCLib/Data/SDC/MDIB/NumericMetricDescriptor.cpp
./src/OSCLib/Data/SDC/MDIB/NumericMetricState.cpp
./src/OSCLib/Data/SDC/MDIB/NumericMetricValue.cpp
./src/OSCLib/Data/SDC/MDIB/OperatingJurisdiction.cpp
./src/OSCLib/Data/SDC/MDIB/OperationGroup.cpp
./src/OSCLib/Data/SDC/MDIB/OperatorContextDescriptor.cpp
./src/OSCLib/Data/SDC/MDIB/OperatorContextState.cpp
./src/OSCLib/Data/SDC/MDIB/OrderDetail.cpp
./src/OSCLib/Data/SDC/MDIB/PatientContextDescriptor.cpp
./src/OSCLib/Data/SDC/MDIB/PatientContextState.cpp
./src/OSCLib/Data/SDC/MDIB/PatientDemographicsCoreData.cpp
./src/OSCLib/Data/SDC/MDIB/PerformedOrderDetail.cpp
./src/OSCLib/Data/SDC/MDIB/PersonParticipation.cpp
./src/OSCLib/Data/SDC/MDIB/PersonReference.cpp
./src/OSCLib/Data/SDC/MDIB/PhysicalConnectorInfo.cpp
./src/OSCLib/Data/SDC/MDIB/ProductionSpecification.cpp
./src/OSCLib/Data/SDC/MDIB/Range.cpp
./src/OSCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricDescriptor.cpp
./src/OSCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricState.cpp
./src/OSCLib/Data/SDC/MDIB/ReferenceRange.cpp
./src/OSCLib/Data/SDC/MDIB/RelatedMeasurement.cpp
./src/OSCLib/Data/SDC/MDIB/Relation.cpp
./src/OSCLib/Data/SDC/MDIB/RemedyInfo.cpp
./src/OSCLib/Data/SDC/MDIB/RequestedOrderDetail.cpp
./src/OSCLib/Data/SDC/MDIB/SampleArrayValue.cpp
./src/OSCLib/Data/SDC/MDIB/ScoDescriptor.cpp
./src/OSCLib/Data/SDC/MDIB/ScoState.cpp
./src/OSCLib/Data/SDC/MDIB/SetAlertStateOperationDescriptor.cpp
./src/OSCLib/Data/SDC/MDIB/SetAlertStateOperationState.cpp
./src/OSCLib/Data/SDC/MDIB/SetComponentStateOperationDescriptor.cpp
./src/OSCLib/Data/SDC/MDIB/SetComponentStateOperationState.cpp
./src/OSCLib/Data/SDC/MDIB/SetContextStateOperationDescriptor.cpp
./src/OSCLib/Data/SDC/MDIB/SetContextStateOperationState.cpp
./src/OSCLib/Data/SDC/MDIB/SetMetricStateOperationDescriptor.cpp
./src/OSCLib/Data/SDC/MDIB/SetMetricStateOperationState.cpp
./src/OSCLib/Data/SDC/MDIB/SetStringOperationDescriptor.cpp
./src/OSCLib/Data/SDC/MDIB/SetStringOperationState.cpp
./src/OSCLib/Data/SDC/MDIB/SetValueOperationDescriptor.cpp
./src/OSCLib/Data/SDC/MDIB/SetValueOperationState.cpp
./src/OSCLib/Data/SDC/MDIB/SimpleTypesMapping.cpp
./src/OSCLib/Data/SDC/MDIB/StringMetricDescriptor.cpp
./src/OSCLib/Data/SDC/MDIB/StringMetricState.cpp
./src/OSCLib/Data/SDC/MDIB/StringMetricValue.cpp
./src/OSCLib/Data/SDC/MDIB/SystemContextDescriptor.cpp
./src/OSCLib/Data/SDC/MDIB/SystemContextState.cpp
./src/OSCLib/Data/SDC/MDIB/SystemSignalActivation.cpp
./src/OSCLib/Data/SDC/MDIB/Translation.cpp
./src/OSCLib/Data/SDC/MDIB/Udi.cpp
./src/OSCLib/Data/SDC/MDIB/VmdDescriptor.cpp
./src/OSCLib/Data/SDC/MDIB/VmdState.cpp
./src/OSCLib/Data/SDC/MDIB/WorkflowContextDescriptor.cpp
./src/OSCLib/Data/SDC/MDIB/WorkflowContextState.cpp
./src/OSCLib/Data/SDC/MDIB/WorkflowDetail.cpp
./src/OSCLib/Data/SDC/MDIB/custom/AlertSystemDescriptorCustomImpl.cxx
#./src/OSCLib/Data/SDC/MDIB/custom/Base64BinaryCustomImpl.cxx
./src/OSCLib/Data/SDC/MDIB/custom/ChannelDescriptorCustomImpl.cxx
./src/OSCLib/Data/SDC/MDIB/custom/MdDescriptionCustomImpl.cxx
./src/OSCLib/Data/SDC/MDIB/custom/MdibContainer.cpp
./src/OSCLib/Data/SDC/MDIB/custom/MdStateCustomImpl.cxx
./src/OSCLib/Data/SDC/MDIB/custom/OperationInvocationContext.cpp
./src/OSCLib/Data/SDC/MDIB/custom/ScoDescriptorCustomImpl.cxx
#./src/OSCLib/Data/SDC/MDIB/AbstractDescriptor.cpp
#./src/OSCLib/Data/SDC/MDIB/AbstractMetricDescriptor.cpp
./src/OSCLib/Data/SDC/FutureInvocationState.cpp
./src/OSCLib/Data/SDC/MDPWSTransportLayerConfiguration.cpp
./src/OSCLib/Data/SDC/SDCConsumer.cpp
./src/OSCLib/Data/SDC/SDCConsumerOperationInvokedHandler.cpp
./src/OSCLib/Data/SDC/SDCProvider.cpp
./src/OSCLib/Data/SDC/SDCProviderStateHandler.cpp
./src/OSCLib/Data/SDC/SDCConsumerAdapter.cpp
./src/OSCLib/Data/SDC/SDCProviderAdapter.cpp
./src/OSCLib/Dev/DeviceCharacteristics.cpp
./src/OSCLib/Util/DebugOut.cpp
./src/OSCLib/Util/Task.cpp
# OSELib
./src/OSELib/DPWS/ActiveSubscriptions.cpp
./src/OSELib/DPWS/DeviceDescription.cpp
./src/OSELib/DPWS/DeviceHandler.cpp
./src/OSELib/DPWS/DeviceServiceController.cpp
./src/OSELib/DPWS/MDPWSDiscoveryClientAdapter.cpp
./src/OSELib/DPWS/DPWSCommon.cpp
./src/OSELib/DPWS/DPWSDiscoveryClientSocketImpl.cpp
./src/OSELib/DPWS/MDPWSStreamingAdapter.cpp
./src/OSELib/DPWS/DPWSHostSocketImpl.cpp
./src/OSELib/DPWS/MDPWSHostAdapter.cpp
./src/OSELib/DPWS/MessageAdapter.cpp
./src/OSELib/DPWS/MessagingContext.cpp
./src/OSELib/DPWS/MetadataProvider.cpp
./src/OSELib/DPWS/OperationTraits.cpp
./src/OSELib/DPWS/PingManager.cpp
./src/OSELib/DPWS/SubscriptionClient.cpp
./src/OSELib/DPWS/SubscriptionManager.cpp
./src/OSELib/Helper/BufferAdapter.cpp
./src/OSELib/Helper/DurationWrapper.cpp
./src/OSELib/Helper/Message.cpp
./src/OSELib/Helper/SchemaGrammarProvider.cpp
./src/OSELib/Helper/StreamReader.cpp
./src/OSELib/Helper/WithLogger.cpp
./src/OSELib/Helper/XercesDocumentWrapper.cpp
./src/OSELib/Helper/XercesGrammarPoolProvider.cpp
./src/OSELib/Helper/XercesParserWrapper.cpp
./src/OSELib/Helper/XercesUniqueElementByTagNameFilter.cpp
./src/OSELib/HTTP/FrontControllerAdapter.cpp
./src/OSELib/HTTP/FrontController.cpp
./src/OSELib/HTTP/GenericContentHandler.cpp
./src/OSELib/HTTP/GenericFileHandler.cpp
./src/OSELib/HTTP/HTTPClientExchanger.cpp
./src/OSELib/HTTP/HTTPSessionManager.cpp
./src/OSELib/HTTP/Service.cpp
./src/OSELib/HTTP/StaticContentController.cpp
./src/OSELib/SDC/ContextEventSinkHandler.cpp
./src/OSELib/SDC/ContextServiceHandler.cpp
./src/OSELib/SDC/DefaultOSCPSchemaGrammarProvider.cpp
./src/OSELib/SDC/EventReportEventSinkHandler.cpp
./src/OSELib/SDC/EventReportServiceHandler.cpp
./src/OSELib/SDC/GetServiceHandler.cpp
./src/OSELib/SDC/OperationTraits.cpp
./src/OSELib/SDC/ReportTraits.cpp
./src/OSELib/SDC/ServiceManager.cpp
./src/OSELib/SDC/SetServiceHandler.cpp
./src/OSELib/SOAP/CommonSoapPreprocessing.cpp
./src/OSELib/SOAP/GetActionCommand.cpp
./src/OSELib/SOAP/GetMetadataActionCommand.cpp
./src/OSELib/SOAP/HTTPRequestHandlerExceptionTrap.cpp
./src/OSELib/SOAP/NormalizedMessageAdapter.cpp
./src/OSELib/SOAP/NormalizedMessageSerializer.cpp
./src/OSELib/SOAP/NormalizeMessageFilter.cpp
./src/OSELib/SOAP/RenewActionCommand.cpp
./src/OSELib/SOAP/SoapActionCommand.cpp
./src/OSELib/SOAP/SoapFaultCommand.cpp
./src/OSELib/SOAP/SoapHTTPResponseWrapper.cpp
./src/OSELib/SOAP/SoapInvoke.cpp
./src/OSELib/SOAP/SubscribeActionCommand.cpp
./src/OSELib/SOAP/UnsubscribeActionCommand.cpp
./src/OSELib/SDC/WaveformReportServiceHandler.cpp
./src/OSELib/WSDL/WSDLBuilder.cpp
)
 
# using POCO 1.4
set(PocoSOURCES 
./src/Dependencies/Poco/AbstractObserver.cpp
./src/Dependencies/Poco/Ascii.cpp
./src/Dependencies/Poco/ASCIIEncoding.cpp
./src/Dependencies/Poco/AtomicCounter.cpp
./src/Dependencies/Poco/Base64Decoder.cpp
./src/Dependencies/Poco/Base64Encoder.cpp
./src/Dependencies/Poco/BinaryReader.cpp
./src/Dependencies/Poco/BinaryWriter.cpp
./src/Dependencies/Poco/Bugcheck.cpp
./src/Dependencies/Poco/ByteOrder.cpp
./src/Dependencies/Poco/Channel.cpp
./src/Dependencies/Poco/Clock.cpp
./src/Dependencies/Poco/Configurable.cpp
./src/Dependencies/Poco/ConsoleChannel.cpp
./src/Dependencies/Poco/CountingStream.cpp
./src/Dependencies/Poco/DateTime.cpp
./src/Dependencies/Poco/DateTimeFormat.cpp
./src/Dependencies/Poco/DateTimeFormatter.cpp
./src/Dependencies/Poco/DateTimeParser.cpp
./src/Dependencies/Poco/Debugger.cpp
./src/Dependencies/Poco/DigestEngine.cpp
./src/Dependencies/Poco/DirectoryIterator.cpp
./src/Dependencies/Poco/DirectoryIteratorStrategy.cpp
./src/Dependencies/Poco/Environment.cpp
./src/Dependencies/Poco/Error.cpp
./src/Dependencies/Poco/ErrorHandler.cpp
./src/Dependencies/Poco/Event.cpp

./src/Dependencies/Poco/NamedEvent.cpp

./src/Dependencies/Poco/Exception.cpp
./src/Dependencies/Poco/File.cpp
./src/Dependencies/Poco/FileStream.cpp
./src/Dependencies/Poco/FileStreamFactory.cpp
./src/Dependencies/Poco/Format.cpp
./src/Dependencies/Poco/Formatter.cpp
./src/Dependencies/Poco/FormattingChannel.cpp
./src/Dependencies/Poco/FPEnvironment.cpp
./src/Dependencies/Poco/Latin1Encoding.cpp
./src/Dependencies/Poco/Latin2Encoding.cpp
./src/Dependencies/Poco/Latin9Encoding.cpp
./src/Dependencies/Poco/LocalDateTime.cpp
./src/Dependencies/Poco/LogFile.cpp
./src/Dependencies/Poco/Logger.cpp
./src/Dependencies/Poco/LoggingRegistry.cpp
./src/Dependencies/Poco/MD4Engine.cpp
./src/Dependencies/Poco/MD5Engine.cpp
./src/Dependencies/Poco/MemoryPool.cpp
./src/Dependencies/Poco/MemoryStream.cpp
./src/Dependencies/Poco/Message.cpp
./src/Dependencies/Poco/Mutex.cpp
./src/Dependencies/Poco/NullStream.cpp
./src/Dependencies/Poco/PatternFormatter.cpp
./src/Dependencies/Poco/Pipe.cpp
./src/Dependencies/Poco/PipeImpl.cpp
./src/Dependencies/Poco/Process.cpp
./src/Dependencies/Poco/SimpleFileChannel.cpp
./src/Dependencies/Poco/SplitterChannel.cpp
./src/Dependencies/Poco/StreamCopier.cpp
./src/Dependencies/Poco/URIStreamFactory.cpp
./src/Dependencies/Poco/URIStreamOpener.cpp
./src/Dependencies/Poco/Net/DatagramSocket.cpp
./src/Dependencies/Poco/Net/DatagramSocketImpl.cpp
./src/Dependencies/Poco/Net/DNS.cpp
./src/Dependencies/Poco/Net/HostEntry.cpp
./src/Dependencies/Poco/Net/HTTPBasicCredentials.cpp
./src/Dependencies/Poco/Net/HTTPBufferAllocator.cpp
./src/Dependencies/Poco/Net/HTTPChunkedStream.cpp
./src/Dependencies/Poco/Net/HTTPClientSession.cpp
./src/Dependencies/Poco/Net/HTTPCookie.cpp
./src/Dependencies/Poco/Net/HTTPFixedLengthStream.cpp
./src/Dependencies/Poco/Net/HTTPHeaderStream.cpp
./src/Dependencies/Poco/Net/HTTPRequest.cpp
./src/Dependencies/Poco/Net/HTTPSession.cpp
./src/Dependencies/Poco/Net/HTTPMessage.cpp
./src/Dependencies/Poco/Net/HTTPResponse.cpp
./src/Dependencies/Poco/Net/HTTPStream.cpp
./src/Dependencies/Poco/Net/HTTPAuthenticationParams.cpp
./src/Dependencies/Poco/Net/HTTPCredentials.cpp
./src/Dependencies/Poco/Net/HTTPDigestCredentials.cpp
./src/Dependencies/Poco/Net/HTTPIOStream.cpp
./src/Dependencies/Poco/Net/HTTPRequestHandler.cpp
./src/Dependencies/Poco/Net/HTTPRequestHandlerFactory.cpp
./src/Dependencies/Poco/Net/HTTPServer.cpp
./src/Dependencies/Poco/Net/HTTPServerConnection.cpp
./src/Dependencies/Poco/Net/HTTPServerConnectionFactory.cpp
./src/Dependencies/Poco/Net/HTTPServerParams.cpp
./src/Dependencies/Poco/Net/HTTPServerRequest.cpp
./src/Dependencies/Poco/Net/HTTPServerRequestImpl.cpp
./src/Dependencies/Poco/Net/HTTPServerResponse.cpp
./src/Dependencies/Poco/Net/HTTPServerResponseImpl.cpp
./src/Dependencies/Poco/Net/HTTPServerSession.cpp
./src/Dependencies/Poco/Net/HTTPSessionFactory.cpp
./src/Dependencies/Poco/Net/HTTPSessionInstantiator.cpp
./src/Dependencies/Poco/Net/HTTPStreamFactory.cpp
./src/Dependencies/Poco/Net/TCPServer.cpp
./src/Dependencies/Poco/Net/TCPServerConnection.cpp
./src/Dependencies/Poco/Net/TCPServerConnectionFactory.cpp
./src/Dependencies/Poco/Net/TCPServerDispatcher.cpp
./src/Dependencies/Poco/Net/TCPServerParams.cpp
./src/Dependencies/Poco/Net/IPAddress.cpp
./src/Dependencies/Poco/Net/IPAddressImpl.cpp
./src/Dependencies/Poco/Net/MediaType.cpp
./src/Dependencies/Poco/Net/MessageHeader.cpp
./src/Dependencies/Poco/Net/MulticastSocket.cpp
./src/Dependencies/Poco/Net/NameValueCollection.cpp
./src/Dependencies/Poco/Net/Net.cpp
./src/Dependencies/Poco/Net/NetException.cpp
./src/Dependencies/Poco/Net/NetworkInterface.cpp
./src/Dependencies/Poco/Net/RawSocket.cpp
./src/Dependencies/Poco/Net/RawSocketImpl.cpp
./src/Dependencies/Poco/Net/ServerSocket.cpp
./src/Dependencies/Poco/Net/ServerSocketImpl.cpp
./src/Dependencies/Poco/Net/SocketAddress.cpp
./src/Dependencies/Poco/Net/SocketAddressImpl.cpp
./src/Dependencies/Poco/Net/Socket.cpp
./src/Dependencies/Poco/Net/SocketImpl.cpp
./src/Dependencies/Poco/Net/SocketNotification.cpp
./src/Dependencies/Poco/Net/SocketNotifier.cpp
./src/Dependencies/Poco/Net/SocketReactor.cpp
./src/Dependencies/Poco/Net/SocketStream.cpp
./src/Dependencies/Poco/Net/StreamSocket.cpp
./src/Dependencies/Poco/Net/StreamSocketImpl.cpp
./src/Dependencies/Poco/NotificationCenter.cpp
./src/Dependencies/Poco/Notification.cpp
./src/Dependencies/Poco/NotificationQueue.cpp
./src/Dependencies/Poco/NumberFormatter.cpp
./src/Dependencies/Poco/NumberParser.cpp
./src/Dependencies/Poco/NumericString.cpp
./src/Dependencies/Poco/Path.cpp
./src/Dependencies/Poco/pcre_byte_order.c
./src/Dependencies/Poco/pcre_chartables.c
./src/Dependencies/Poco/pcre_compile.c
./src/Dependencies/Poco/pcre_config.c
./src/Dependencies/Poco/pcre_dfa_exec.c
./src/Dependencies/Poco/pcre_exec.c
./src/Dependencies/Poco/pcre_fullinfo.c
./src/Dependencies/Poco/pcre_get.c
./src/Dependencies/Poco/pcre_globals.c
./src/Dependencies/Poco/pcre_jit_compile.c
./src/Dependencies/Poco/pcre_maketables.c
./src/Dependencies/Poco/pcre_newline.c
./src/Dependencies/Poco/pcre_ord2utf8.c
./src/Dependencies/Poco/pcre_refcount.c
./src/Dependencies/Poco/pcre_string_utils.c
./src/Dependencies/Poco/pcre_study.c
./src/Dependencies/Poco/pcre_tables.c
./src/Dependencies/Poco/pcre_ucd.c
./src/Dependencies/Poco/pcre_valid_utf8.c
./src/Dependencies/Poco/pcre_version.c
./src/Dependencies/Poco/pcre_xclass.c
./src/Dependencies/Poco/Random.cpp
./src/Dependencies/Poco/RandomStream.cpp
./src/Dependencies/Poco/RefCountedObject.cpp
./src/Dependencies/Poco/RegularExpression.cpp
./src/Dependencies/Poco/Runnable.cpp
./src/Dependencies/Poco/RWLock.cpp
./src/Dependencies/Poco/SHA1Engine.cpp
./src/Dependencies/Poco/SignalHandler.cpp
./src/Dependencies/Poco/String.cpp
./src/Dependencies/Poco/StringTokenizer.cpp
./src/Dependencies/Poco/TextBufferIterator.cpp
./src/Dependencies/Poco/TextConverter.cpp
./src/Dependencies/Poco/TextEncoding.cpp
./src/Dependencies/Poco/TextIterator.cpp
./src/Dependencies/Poco/Thread.cpp
./src/Dependencies/Poco/ThreadLocal.cpp
./src/Dependencies/Poco/ThreadPool.cpp
./src/Dependencies/Poco/TimedNotificationQueue.cpp
./src/Dependencies/Poco/Timespan.cpp
./src/Dependencies/Poco/Timestamp.cpp
./src/Dependencies/Poco/Timezone.cpp
./src/Dependencies/Poco/UnicodeConverter.cpp
./src/Dependencies/Poco/Unicode.cpp
./src/Dependencies/Poco/URI.cpp
./src/Dependencies/Poco/UTF16Encoding.cpp
./src/Dependencies/Poco/UTF32Encoding.cpp
./src/Dependencies/Poco/UTF8Encoding.cpp
./src/Dependencies/Poco/UTF8String.cpp
./src/Dependencies/Poco/UUID.cpp
./src/Dependencies/Poco/UUIDGenerator.cpp
./src/Dependencies/Poco/Windows1250Encoding.cpp
./src/Dependencies/Poco/Windows1251Encoding.cpp
./src/Dependencies/Poco/Windows1252Encoding.cpp
)


list(APPEND SDCLibSOURCES 
./datamodel/generated/BICEPS_ParticipantModel.cxx
./datamodel/generated/BICEPS_MessageModel.cxx
./datamodel/generated/DICOMDeviceDescription.cxx
./datamodel/generated/eventing.cxx
./datamodel/generated/ExtensionPoint.cxx
./datamodel/generated/MDPWS.cxx
./datamodel/generated/MetadataExchange.cxx
./datamodel/generated/NormalizedMessageModel.cxx
./datamodel/generated/ws-addressing.cxx
./datamodel/generated/wsdd-discovery-1.1-schema-os.cxx
./datamodel/generated/wsdd-dpws-1.1-schema-os.cxx
./datamodel/generated/wsdl-custom.cxx
./datamodel/generated/ws-policy.cxx
./datamodel/generated/ws-streaming.cxx
./datamodel/generated/wsdl-soap-binding.cxx
)


list(APPEND SDCLibSOURCES ${PocoSOURCES})


if(WIN32)
	add_library(SDCLib STATIC ${SDCLibSOURCES})
else()
	add_library(SDCLib SHARED ${SDCLibSOURCES})
endif()

add_executable(UnitTests
Tests/UnitTests.cpp
Tests/SDCTests/TestConnectionLost.cpp
#Tests/SDCTests/TestDICOM.cpp
Tests/SDCTests/TestMultiSDC.cpp
#Tests/SDCTests/TestMultiStates.cpp
Tests/SDCTests/TestSimpleSDC.cpp
Tests/SDCTests/TestPeriodicEvents.cpp
Tests/SDCTests/TestStreamSDC.cpp
Tests/UnitTest++/src/Test.cpp
Tests/UnitTest++/src/TestList.cpp
Tests/UnitTest++/src/TestRunner.cpp
Tests/UnitTest++/src/CurrentTest.cpp
Tests/UnitTest++/src/TestDetails.cpp
Tests/UnitTest++/src/TestResults.cpp
Tests/UnitTest++/src/ReportAssert.cpp
Tests/UnitTest++/src/TestReporter.cpp
Tests/UnitTest++/src/TimeConstraint.cpp
Tests/UnitTest++/src/AssertException.cpp
Tests/UnitTest++/src/MemoryOutStream.cpp
Tests/UnitTest++/src/XmlTestReporter.cpp
Tests/UnitTest++/src/DeferredTestResult.cpp
Tests/UnitTest++/src/TestReporterStdout.cpp
Tests/UnitTest++/src/DeferredTestReporter.cpp
Tests/UnitTest++/src/Posix/TimeHelpers.cpp
Tests/UnitTest++/src/Win32/TimeHelpers.cpp
Tests/UnitTest++/src/Posix/SignalTranslator.cpp
)


add_executable(ExampleConsumer
Examples/ExampleConsumer/ExampleConsumer.cpp
)

add_executable(ExampleProject
Examples/ExampleProject/ExampleProject.cpp
)

add_executable(ExampleProvider
Examples/ExampleProvider/ExampleProvider.cpp
)

add_executable(ExampleConsumer4SoftICEStreaming
Examples/ExampleConsumer4SoftICEStreaming/ExampleConsumer4SoftICEStreaming.cpp
)

add_executable(ExampleCachedProvider
Examples/ExampleCachedProvider/ExampleCachedProvider.cpp
)

#add_executable(SimpleServiceDiscovery
#Examples/SimpleServiceDiscovery.cpp
#)

add_executable(MDIBVisualizer
Examples/MDIBVisualizer/MDIBVisualizer.cpp
)

#add_executable(MDIBDump
#Examples/MDIBDump.cpp
#)

#add_executable(GenericSubscription
#Examples/GenericSubscription.cpp
#)

#add_executable(DPWSDiscoveryClient
#Tests/Tools/DPWSDiscoveryClient.cpp
#)

#add_executable(DPWSDiscoveryListener
#Tests/Tools/DPWSDiscoveryListener.cpp
#)

#add_executable(ClientForUniRostockDevices
#Examples/ClientForUniRostockDevices.cpp
#)


if(WIN32)
	SET(ADDITIONAL_LIBS "iphlpapi" "ws2_32")
else()
	SET(ADDITIONAL_LIBS "")
endif()

target_link_libraries(SDCLib ${PTHREAD_LIB} ${XERCES_LIB} ${ADDITIONAL_LIBS})
target_link_libraries(UnitTests SDCLib ${PTHREAD_LIB} ${XERCES_LIB} ${ADDITIONAL_LIBS})
target_link_libraries(ExampleConsumer SDCLib ${PTHREAD_LIB} ${XERCES_LIB} ${ADDITIONAL_LIBS})
target_link_libraries(ExampleConsumer4SoftICEStreaming SDCLib ${PTHREAD_LIB} ${XERCES_LIB} ${ADDITIONAL_LIBS})
target_link_libraries(ExampleProvider SDCLib ${PTHREAD_LIB} ${XERCES_LIB} ${ADDITIONAL_LIBS})
target_link_libraries(ExampleCachedProvider SDCLib ${PTHREAD_LIB} ${XERCES_LIB} ${ADDITIONAL_LIBS})
target_link_libraries(ExampleProject SDCLib ${PTHREAD_LIB} ${XERCES_LIB} ${ADDITIONAL_LIBS})
#target_link_libraries(SimpleServiceDiscovery SDCLib ${PTHREAD_LIB} ${XERCES_LIB} ${ADDITIONAL_LIBS})
#target_link_libraries(MDIBDump SDCLib ${PTHREAD_LIB} ${XERCES_LIB} ${ADDITIONAL_LIBS})
target_link_libraries(MDIBVisualizer SDCLib ${PTHREAD_LIB} ${XERCES_LIB} ${ADDITIONAL_LIBS})
#target_link_libraries(GenericSubscription SDCLib ${PTHREAD_LIB} ${XERCES_LIB} ${ADDITIONAL_LIBS})
#target_link_libraries(DPWSDiscoveryClient SDCLib ${PTHREAD_LIB} ${XERCES_LIB} ${ADDITIONAL_LIBS})
#target_link_libraries(DPWSDiscoveryListener SDCLib ${PTHREAD_LIB} ${XERCES_LIB} ${ADDITIONAL_LIBS})
#target_link_libraries(ClientForUniRostockDevices SDCLib ${PTHREAD_LIB} ${XERCES_LIB} ${ADDITIONAL_LIBS})

