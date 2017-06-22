#set(CMAKE_VERBOSE_MAKEFILE ON)
PROJECT (OSCLib)
option(debug "Debug build" ON)
option(crossCompile "Cross compile for arm" OFF)

cmake_minimum_required(VERSION 2.8)
SET(ARCH "x86_64")

if (crossCompile)
    set(CMAKE_C_COMPILER "arm-linux-gnueabihf-gcc")
    set(CMAKE_CXX_COMPILER "arm-linux-gnueabihf-g++")
    SET(ARCH "arm-linux")
endif()

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

INCLUDE_DIRECTORIES("include" "datamodel" "swig" ${XSDCXX_INCLUDE_DIR} ${XERCES_INCLUDE_DIR} ${PTHREAD_INCLUDE_DIR})
LINK_DIRECTORIES(${PTHREAD_LIB_DIR} ${XERCES_LIB_DIR})

# Debug or Release build
if (debug)
    SET(CMAKE_BUILD_TYPE Debug)
    # enable debug and profiling informations for sprof
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -g -O0 -Wall -Wextra")    
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

ADD_DEFINITIONS(-D_POCO_NO_AUTOMATIC_LIBS)
ADD_DEFINITIONS(-D_Foundation_EXPORTS)
ADD_DEFINITIONS(-D_Net_EXPORTS)

IF (${CMAKE_SYSTEM_NAME} MATCHES "Linux") 
    ADD_DEFINITIONS(-D_LINUX)
    set(XERCES_LIB xerces-c)
    set(PTHREAD_LIB pthread)
    set(PYTHON_LIB python2.7)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

IF (${CMAKE_SYSTEM_NAME} MATCHES "Windows") 
    ADD_DEFINITIONS(-D_WIN32)
    if (CMAKE_BUILD_TYPE STREQUAL Debug)
        set(XERCES_LIB xerces-c_3D.lib)
    else ()
        set(XERCES_LIB xerces-c_3.lib)
    endif()
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

set(OSCLibSOURCES
./src/Data/OSCP/MDIB/ActivateOperationDescriptor.cpp
./src/Data/OSCP/MDIB/ActivateOperationState.cpp
./src/Data/OSCP/MDIB/AlertConditionDescriptor.cpp
./src/Data/OSCP/MDIB/AlertConditionReference.cpp
./src/Data/OSCP/MDIB/custom/AlertConditionReferenceCustomImpl.cxx
./src/Data/OSCP/MDIB/AlertConditionState.cpp
./src/Data/OSCP/MDIB/AlertSignalDescriptor.cpp
./src/Data/OSCP/MDIB/AlertSignalState.cpp
./src/Data/OSCP/MDIB/AlertSystemDescriptor.cpp
./src/Data/OSCP/MDIB/custom/AlertSystemDescriptorCustomImpl.cxx
./src/Data/OSCP/MDIB/AlertSystemState.cpp
./src/Data/OSCP/MDIB/AllowedValue.cpp
./src/Data/OSCP/MDIB/ApplyAnnotation.cpp
./src/Data/OSCP/MDIB/Base64Binary.cpp
./src/Data/OSCP/MDIB/BatteryDescriptor.cpp
./src/Data/OSCP/MDIB/custom/Base64BinaryCustomImpl.cxx
./src/Data/OSCP/MDIB/BaseDemographics.cpp
./src/Data/OSCP/MDIB/CauseInfo.cpp
./src/Data/OSCP/MDIB/CalibrationInfo.cpp
./src/Data/OSCP/MDIB/ChannelDescriptor.cpp
./src/Data/OSCP/MDIB/custom/ChannelDescriptorCustomImpl.cxx
./src/Data/OSCP/MDIB/ClinicalInfo.cpp
./src/Data/OSCP/MDIB/ClockDescriptor.cpp
./src/Data/OSCP/MDIB/ClockState.cpp
./src/Data/OSCP/MDIB/CodedValue.cpp
./src/Data/OSCP/MDIB/custom/ConvertFromCDM.cpp
./src/Data/OSCP/MDIB/custom/ConvertToCDM.cpp
./src/Data/OSCP/MDIB/DateTime.cpp
./src/Data/OSCP/MDIB/custom/Defaults.cpp
./src/Data/OSCP/MDIB/DicomDeviceDescriptor.cpp
./src/Data/OSCP/MDIB/DicomNetworkAe.cpp
./src/Data/OSCP/MDIB/DicomNetworkConnection.cpp
./src/Data/OSCP/MDIB/DicomTransferCapability.cpp
./src/Data/OSCP/MDIB/Duration.cpp
./src/Data/OSCP/MDIB/EnsembleContextDescriptor.cpp
./src/Data/OSCP/MDIB/EnsembleContextState.cpp
./src/Data/OSCP/MDIB/custom/EnumMappings.cpp
./src/Data/OSCP/MDIB/EnumStringMetricDescriptor.cpp
./src/Data/OSCP/MDIB/EnumStringMetricState.cpp
./src/Data/OSCP/MDIB/MdsDescriptor.cpp
./src/Data/OSCP/MDIB/MdsState.cpp
./src/Data/OSCP/MDIB/ImagingProcedure.cpp
./src/Data/OSCP/MDIB/InstanceIdentifier.cpp
./src/Data/OSCP/MDIB/Language.cpp
./src/Data/OSCP/MDIB/LimitAlertConditionDescriptor.cpp
./src/Data/OSCP/MDIB/LimitAlertConditionState.cpp
./src/Data/OSCP/MDIB/LocalizedText.cpp
./src/Data/OSCP/MDIB/LocationContextDescriptor.cpp
./src/Data/OSCP/MDIB/LocationContextState.cpp
./src/Data/OSCP/MDIB/LocationDetail.cpp
./src/Data/OSCP/MDIB/LocationReference.cpp
./src/Data/OSCP/MDIB/MdDescription.cpp
./src/Data/OSCP/MDIB/custom/MdDescriptionCustomImpl.cxx
./src/Data/OSCP/MDIB/custom/MDIBContainer.cpp
./src/Data/OSCP/MDIB/MdState.cpp
./src/Data/OSCP/MDIB/custom/MdStateCustomImpl.cxx
./src/Data/OSCP/MDIB/MeansContextDescriptor.cpp
./src/Data/OSCP/MDIB/Measurement.cpp
./src/Data/OSCP/MDIB/MetaData.cpp
./src/Data/OSCP/MDIB/NumericMetricDescriptor.cpp
./src/Data/OSCP/MDIB/NumericMetricState.cpp
./src/Data/OSCP/MDIB/NumericMetricValue.cpp
./src/Data/OSCP/MDIB/custom/OperationInvocationContext.cpp
./src/Data/OSCP/MDIB/OperatorContextDescriptor.cpp
./src/Data/OSCP/MDIB/OperatorContextState.cpp
./src/Data/OSCP/MDIB/Order.cpp
./src/Data/OSCP/MDIB/OrderDetail.cpp
./src/Data/OSCP/MDIB/PatientContextDescriptor.cpp
./src/Data/OSCP/MDIB/PatientContextState.cpp
./src/Data/OSCP/MDIB/PatientDemographicsCoreData.cpp
./src/Data/OSCP/MDIB/PerformedOrderDetail.cpp
./src/Data/OSCP/MDIB/PersonParticipation.cpp
./src/Data/OSCP/MDIB/custom/PersonParticipationCustomImpl.cxx
./src/Data/OSCP/MDIB/PersonReference.cpp
./src/Data/OSCP/MDIB/custom/PersonReferenceCustomImpl.cxx
./src/Data/OSCP/MDIB/ProductionSpecification.cpp
./src/Data/OSCP/MDIB/Range.cpp
./src/Data/OSCP/MDIB/RealTimeSampleArrayMetricDescriptor.cpp
./src/Data/OSCP/MDIB/RealTimeSampleArrayMetricState.cpp
./src/Data/OSCP/MDIB/ReferenceRange.cpp
./src/Data/OSCP/MDIB/ReferencedVersion.cpp
./src/Data/OSCP/MDIB/RelatedMeasurement.cpp
./src/Data/OSCP/MDIB/RemedyInfo.cpp
./src/Data/OSCP/MDIB/RequestedOrderDetail.cpp
./src/Data/OSCP/MDIB/RealTimeValueType.cpp
./src/Data/OSCP/MDIB/custom/RealTimeValueTypeCustomImpl.cxx
./src/Data/OSCP/MDIB/SampleArrayValue.cpp
./src/Data/OSCP/MDIB/ScoDescriptor.cpp
./src/Data/OSCP/MDIB/custom/ScoDescriptorCustomImpl.cxx
./src/Data/OSCP/MDIB/SetAlertStateOperationDescriptor.cpp
./src/Data/OSCP/MDIB/SetAlertStateOperationState.cpp
./src/Data/OSCP/MDIB/SetComponentStateOperationDescriptor.cpp
./src/Data/OSCP/MDIB/SetComponentStateOperationState.cpp
./src/Data/OSCP/MDIB/SetContextStateOperationDescriptor.cpp
./src/Data/OSCP/MDIB/SetContextStateOperationState.cpp
./src/Data/OSCP/MDIB/SetMetricStateOperationDescriptor.cpp
./src/Data/OSCP/MDIB/SetMetricStateOperationState.cpp
./src/Data/OSCP/MDIB/SetStringOperationDescriptor.cpp
./src/Data/OSCP/MDIB/SetValueOperationDescriptor.cpp
./src/Data/OSCP/MDIB/StringMetricDescriptor.cpp
./src/Data/OSCP/MDIB/StringMetricState.cpp
./src/Data/OSCP/MDIB/StringMetricValue.cpp
./src/Data/OSCP/MDIB/SystemContextDescriptor.cpp
./src/Data/OSCP/MDIB/SystemContextState.cpp
./src/Data/OSCP/MDIB/Timestamp.cpp
./src/Data/OSCP/MDIB/TimeZone.cpp
./src/Data/OSCP/MDIB/custom/TimeZoneCustomImpl.cxx
./src/Data/OSCP/MDIB/VersionCounter.cpp
./src/Data/OSCP/MDIB/VmdDescriptor.cpp
./src/Data/OSCP/MDIB/WorkflowContextDescriptor.cpp
./src/Data/OSCP/MDIB/WorkflowContextState.cpp
./src/Data/OSCP/MDIB/WorkflowDetail.cpp
./src/Data/OSCP/FutureInvocationState.cpp
./src/Data/OSCP/OSCPConsumer.cpp
./src/Data/OSCP/OSCPConsumerEventHandler.cpp
./src/Data/OSCP/OSCPProvider.cpp
./src/Data/OSCP/OSCPProviderActivateOperationHandler.cpp
./src/Data/OSCP/OSCPProviderAlertConditionStateHandler.cpp
./src/Data/OSCP/OSCPProviderAlertSignalStateHandler.cpp
./src/Data/OSCP/OSCPProviderAlertSystemStateHandler.cpp
./src/Data/OSCP/OSCPProviderClockStateHandler.cpp
./src/Data/OSCP/OSCPProviderComponentStateHandler.cpp
./src/Data/OSCP/OSCPProviderContextStateHandler.cpp
./src/Data/OSCP/OSCPProviderEnumStringMetricStateHandler.cpp
./src/Data/OSCP/OSCPProviderHydraMDSStateHandler.cpp
./src/Data/OSCP/OSCPProviderLimitAlertConditionStateHandler.cpp
./src/Data/OSCP/OSCPProviderMDStateHandler.cpp
./src/Data/OSCP/OSCPProviderNumericMetricStateHandler.cpp
./src/Data/OSCP/OSCPProviderRealTimeSampleArrayMetricStateHandler.cpp
./src/Data/OSCP/OSCPProviderStringMetricStateHandler.cpp
./src/Data/OSCP/OSELibConsumerAdapter.cpp
./src/Data/OSCP/OSELibProviderAdapter.cpp
./src/Dev/DeviceCharacteristics.cpp
./src/OSCLibrary.cpp
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
./src/OSELib/OSCP/ContextEventSinkHandler.cpp
./src/OSELib/OSCP/ContextServiceHandler.cpp
./src/OSELib/OSCP/DefaultOSCPSchemaGrammarProvider.cpp
./src/OSELib/OSCP/EventReportEventSinkHandler.cpp
./src/OSELib/OSCP/EventReportServiceHandler.cpp
./src/OSELib/OSCP/GetServiceHandler.cpp
./src/OSELib/OSCP/OperationTraits.cpp
./src/OSELib/OSCP/ReportTraits.cpp
./src/OSELib/OSCP/ServiceManager.cpp
./src/OSELib/OSCP/SetServiceHandler.cpp
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
./src/OSELib/OSCP/WaveformReportServiceHandler.cpp
./src/OSELib/WSDL/WSDLBuilder.cpp
./src/Util/DebugOut.cpp
./src/Util/Task.cpp
)

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
./src/Dependencies/Poco/NullStream.cpp
./src/Dependencies/Poco/Mutex.cpp
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


list(APPEND OSCLibSOURCES 
./datamodel/BICEPS_ParticipantModel.cxx
./datamodel/BICEPS_MessageModel.cxx
./datamodel/DICOMDeviceDescription.cxx
./datamodel/eventing.cxx
./datamodel/ExtensionPoint.cxx
./datamodel/MDPWS.cxx
./datamodel/MetadataExchange.cxx
./datamodel/NormalizedMessageModel.cxx
./datamodel/ws-addressing.cxx
./datamodel/wsdd-discovery-1.1-schema-os.cxx
./datamodel/wsdd-dpws-1.1-schema-os.cxx
./datamodel/wsdl-custom.cxx
./datamodel/ws-policy.cxx
./datamodel/ws-streaming.cxx
./datamodel/wsdl-soap-binding.cxx

)


list(APPEND OSCLibSOURCES ${PocoSOURCES})

add_library(OSCLib SHARED ${OSCLibSOURCES})

add_executable(UnitTests
Tests/UnitTests.cpp
Tests/OSCPTests/TestConnectionLost.cpp
Tests/OSCPTests/TestDICOM.cpp
Tests/OSCPTests/TestMultiOSCP.cpp
Tests/OSCPTests/TestSimpleOSCP.cpp
Tests/OSCPTests/TestPeriodicEvents.cpp
Tests/OSCPTests/TestStreamOSCP.cpp
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
Examples/ExampleConsumer.cpp
)

add_executable(ExampleConsumer4SoftICEStreaming
Examples/ExampleConsumer4SoftICEStreaming.cpp
)

add_executable(ExampleProvider4SoftICEStreaming
Examples/ExampleProvider4SoftICEStreaming.cpp
)

add_executable(ExampleProject
Examples/ExampleProject.cpp
)

add_executable(SimpleServiceDiscovery
Examples/SimpleServiceDiscovery.cpp
)

add_executable(MDIBVisualizer
Examples/MDIBVisualizer.cpp
)

add_executable(MDIBDump
Examples/MDIBDump.cpp
)

add_executable(GenericSubscription
Examples/GenericSubscription.cpp
)

add_executable(DPWSDiscoveryClient
Tests/Tools/DPWSDiscoveryClient.cpp
)

add_executable(DPWSDiscoveryListener
Tests/Tools/DPWSDiscoveryListener.cpp
)

add_executable(ClientForUniRostockDevices
Examples/ClientForUniRostockDevices.cpp
)


SET(ADDITIONAL_LIBS "")

target_link_libraries(OSCLib ${PTHREAD_LIB} ${XERCES_LIB} ${ADDITIONAL_LIBS})
target_link_libraries(UnitTests OSCLib ${PTHREAD_LIB} ${XERCES_LIB} ${ADDITIONAL_LIBS})
target_link_libraries(ExampleConsumer OSCLib ${PTHREAD_LIB} ${XERCES_LIB} ${ADDITIONAL_LIBS})
target_link_libraries(ExampleConsumer4SoftICEStreaming OSCLib ${PTHREAD_LIB} ${XERCES_LIB} ${ADDITIONAL_LIBS})
target_link_libraries(ExampleProvider4SoftICEStreaming OSCLib ${PTHREAD_LIB} ${XERCES_LIB} ${ADDITIONAL_LIBS})
target_link_libraries(ExampleProject OSCLib ${PTHREAD_LIB} ${XERCES_LIB} ${ADDITIONAL_LIBS})
target_link_libraries(SimpleServiceDiscovery OSCLib ${PTHREAD_LIB} ${XERCES_LIB} ${ADDITIONAL_LIBS})
target_link_libraries(MDIBDump OSCLib ${PTHREAD_LIB} ${XERCES_LIB} ${ADDITIONAL_LIBS})
target_link_libraries(MDIBVisualizer OSCLib ${PTHREAD_LIB} ${XERCES_LIB} ${ADDITIONAL_LIBS})
target_link_libraries(GenericSubscription OSCLib ${PTHREAD_LIB} ${XERCES_LIB} ${ADDITIONAL_LIBS})
target_link_libraries(DPWSDiscoveryClient OSCLib ${PTHREAD_LIB} ${XERCES_LIB} ${ADDITIONAL_LIBS})
target_link_libraries(DPWSDiscoveryListener OSCLib ${PTHREAD_LIB} ${XERCES_LIB} ${ADDITIONAL_LIBS})
target_link_libraries(ClientForUniRostockDevices OSCLib ${PTHREAD_LIB} ${XERCES_LIB} ${ADDITIONAL_LIBS})
