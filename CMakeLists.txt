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
# - CAN be omitted in linux, if all dependencies are installed on the system using 'make install'
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
./src/Cli/Client.cpp
./src/Comm/AbstractBinding.cpp
./src/Comm/Binding.cpp
./src/Comm/CommunicationManager.cpp
./src/Comm/DatagramSocketManager.cpp
./src/Comm/DefaultNetworkInterface.cpp
./src/Comm/HTTPClientExchanger.cpp
./src/Comm/DPWS/DPWS11CommunicationManager.cpp
./src/Comm/DPWS/DPWS11Message.cpp
./src/Comm/DPWS/DPWS11MessageXMLBuilder.cpp
./src/Comm/DPWS/DPWS11MessageXMLParser.cpp
./src/Comm/DPWS/DPWS11MetadataSoapParserHandler.cpp
./src/Comm/DPWS/DPWS11SoapParserHandler.cpp
./src/Comm/DPWS/DPWS11WaveformStreamActionHandler.cpp
./src/Comm/DPWS/DPWS11WSDLBuilder.cpp
./src/Comm/DPWS/DPWS11WSDLParser.cpp
./src/Comm/DPWS/XMLParser.cpp
./src/Comm/IPBinding.cpp
./src/Comm/Message.cpp
./src/Comm/MulticastCallback.cpp
./src/Comm/MulticastSocketManager.cpp
./src/Comm/NetworkInterface.cpp
./src/Comm/PendingMessage.cpp
./src/Comm/Soap/SoapBody.cpp
./src/Comm/Soap/SoapEnvelope.cpp
./src/Comm/Soap/SoapHeader.cpp
./src/Comm/Soap/XMLEntity.cpp
./src/Comm/UnicastCallback.cpp
./src/Data/EventSink.cpp
./src/Data/EventSource.cpp
./src/Data/Operation.cpp
./src/Data/OperationHelpers.cpp
./src/Data/OSCP/MDIB/ActivateOperationDescriptor.cpp
./src/Data/OSCP/MDIB/AlertConditionDescriptor.cpp
./src/Data/OSCP/MDIB/AlertConditionReference.cpp
./src/Data/OSCP/MDIB/AlertConditionReferenceCustomImpl.cxx
./src/Data/OSCP/MDIB/AlertConditionState.cpp
./src/Data/OSCP/MDIB/AlertSignalDescriptor.cpp
./src/Data/OSCP/MDIB/AlertSignalState.cpp
./src/Data/OSCP/MDIB/AlertSystemDescriptor.cpp
./src/Data/OSCP/MDIB/AlertSystemDescriptorCustomImpl.cxx
./src/Data/OSCP/MDIB/AlertSystemState.cpp
./src/Data/OSCP/MDIB/Annotation.cpp
./src/Data/OSCP/MDIB/Base64Binary.cpp
./src/Data/OSCP/MDIB/Base64BinaryCustomImpl.cxx
./src/Data/OSCP/MDIB/BaseDemographics.cpp
./src/Data/OSCP/MDIB/CauseInfo.cpp
./src/Data/OSCP/MDIB/CalibrationInfo.cpp
./src/Data/OSCP/MDIB/ChannelDescriptor.cpp
./src/Data/OSCP/MDIB/ChannelDescriptorCustomImpl.cxx
./src/Data/OSCP/MDIB/ClinicalInfo.cpp
./src/Data/OSCP/MDIB/ClockDescriptor.cpp
./src/Data/OSCP/MDIB/ClockState.cpp
./src/Data/OSCP/MDIB/CodedValue.cpp
./src/Data/OSCP/MDIB/ComponentState.cpp
./src/Data/OSCP/MDIB/ConvertFromCDM.cpp
./src/Data/OSCP/MDIB/ConvertToCDM.cpp
./src/Data/OSCP/MDIB/DateTime.cpp
./src/Data/OSCP/MDIB/Defaults.cpp
./src/Data/OSCP/MDIB/DICOMDeviceDescriptor.cpp
./src/Data/OSCP/MDIB/DICOMNetworkAE.cpp
./src/Data/OSCP/MDIB/DICOMNetworkConnection.cpp
./src/Data/OSCP/MDIB/DICOMTransferCapability.cpp
./src/Data/OSCP/MDIB/Duration.cpp
./src/Data/OSCP/MDIB/EnsembleContextDescriptor.cpp
./src/Data/OSCP/MDIB/EnsembleContextState.cpp
./src/Data/OSCP/MDIB/EnumMappings.cpp
./src/Data/OSCP/MDIB/EnumNomenRef.cpp
./src/Data/OSCP/MDIB/EnumStringMetricDescriptor.cpp
./src/Data/OSCP/MDIB/EnumStringMetricState.cpp
./src/Data/OSCP/MDIB/HydraMDSDescriptor.cpp
./src/Data/OSCP/MDIB/HydraMDSState.cpp
./src/Data/OSCP/MDIB/ImagingProcedure.cpp
./src/Data/OSCP/MDIB/InstanceIdentifier.cpp
./src/Data/OSCP/MDIB/Language.cpp
./src/Data/OSCP/MDIB/LimitAlertConditionDescriptor.cpp
./src/Data/OSCP/MDIB/LimitAlertConditionState.cpp
./src/Data/OSCP/MDIB/LocalizedText.cpp
./src/Data/OSCP/MDIB/LocationContextDescriptor.cpp
./src/Data/OSCP/MDIB/LocationContextState.cpp
./src/Data/OSCP/MDIB/MDDescription.cpp
./src/Data/OSCP/MDIB/MDDescriptionCustomImpl.cxx
./src/Data/OSCP/MDIB/MDIBContainer.cpp
./src/Data/OSCP/MDIB/MDState.cpp
./src/Data/OSCP/MDIB/MDStateCustomImpl.cxx
./src/Data/OSCP/MDIB/Measure.cpp
./src/Data/OSCP/MDIB/MeasurementState.cpp
./src/Data/OSCP/MDIB/NumericMetricDescriptor.cpp
./src/Data/OSCP/MDIB/NumericMetricState.cpp
./src/Data/OSCP/MDIB/NumericMetricValue.cpp
./src/Data/OSCP/MDIB/OperationState.cpp
./src/Data/OSCP/MDIB/OperationInvocationContext.cpp
./src/Data/OSCP/MDIB/OperatorContextDescriptor.cpp
./src/Data/OSCP/MDIB/OperatorContextState.cpp
./src/Data/OSCP/MDIB/Order.cpp
./src/Data/OSCP/MDIB/OrderDetail.cpp
./src/Data/OSCP/MDIB/PatientContextDescriptor.cpp
./src/Data/OSCP/MDIB/PatientContextState.cpp
./src/Data/OSCP/MDIB/PatientDemographicsCoreData.cpp
./src/Data/OSCP/MDIB/PersonParticipation.cpp
./src/Data/OSCP/MDIB/PersonParticipationCustomImpl.cxx
./src/Data/OSCP/MDIB/PersonReference.cpp
./src/Data/OSCP/MDIB/PersonReferenceCustomImpl.cxx
./src/Data/OSCP/MDIB/ProductionSpecification.cpp
./src/Data/OSCP/MDIB/Range.cpp
./src/Data/OSCP/MDIB/RealTimeSampleArrayMetricDescriptor.cpp
./src/Data/OSCP/MDIB/RealTimeSampleArrayMetricState.cpp
./src/Data/OSCP/MDIB/RealTimeSampleArrayValue.cpp
./src/Data/OSCP/MDIB/RemedyInfo.cpp
./src/Data/OSCP/MDIB/ReferencedVersion.cpp
./src/Data/OSCP/MDIB/RTValueType.cpp
./src/Data/OSCP/MDIB/RTValueTypeCustomImpl.cxx
./src/Data/OSCP/MDIB/SampleIndex.cpp
./src/Data/OSCP/MDIB/SCODescriptor.cpp
./src/Data/OSCP/MDIB/SCODescriptorCustomImpl.cxx
./src/Data/OSCP/MDIB/SetAlertStateOperationDescriptor.cpp
./src/Data/OSCP/MDIB/SetContextOperationDescriptor.cpp
./src/Data/OSCP/MDIB/SetRangeOperationDescriptor.cpp
./src/Data/OSCP/MDIB/SetStringOperationDescriptor.cpp
./src/Data/OSCP/MDIB/SetValueOperationDescriptor.cpp
./src/Data/OSCP/MDIB/StringMetricDescriptor.cpp
./src/Data/OSCP/MDIB/StringMetricState.cpp
./src/Data/OSCP/MDIB/StringMetricValue.cpp
./src/Data/OSCP/MDIB/SystemContext.cpp
./src/Data/OSCP/MDIB/SystemMetaData.cpp
./src/Data/OSCP/MDIB/Timestamp.cpp
./src/Data/OSCP/MDIB/TimeZone.cpp
./src/Data/OSCP/MDIB/TimeZoneCustomImpl.cxx
./src/Data/OSCP/MDIB/VersionCounter.cpp
./src/Data/OSCP/MDIB/VMDDescriptor.cpp
./src/Data/OSCP/MDIB/WorkflowContextDescriptor.cpp
./src/Data/OSCP/MDIB/WorkflowContextState.cpp
./src/Data/OSCP/Operations/OSCPOperationTraits.cpp
./src/Data/OSCP/Operations/OSCPReportTraits.cpp
./src/Data/OSCP/FutureInvocationState.cpp
./src/Data/OSCP/OSCPCachedProvider.cpp
./src/Data/OSCP/OSCPConsumer.cpp
./src/Data/OSCP/OSCPConsumerEventHandler.cpp
./src/Data/OSCP/OSCPPingManager.cpp
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
./src/Data/OSCP/OSCPServiceManager.cpp
./src/Data/OSCP/OSCPSubscriptionManager.cpp
./src/Data/Parameter.cpp
./src/Data/QName.cpp
./src/Data/RemoteOperation.cpp
./src/Data/Subscription.cpp
./src/Data/SubscriptionVector.cpp
./src/Dev/DeviceCharacteristics.cpp
./src/Dev/Device.cpp
./src/Dev/EndpointReference.cpp
./src/Dev/Entity.cpp
./src/Dev/OSCP/CDMContextService.cpp
./src/Dev/OSCP/CDMEvtService.cpp
./src/Dev/OSCP/CDMGetService.cpp
./src/Dev/OSCP/CDMSetService.cpp
./src/Dev/OSCP/CDMWavService.cpp
./src/Dev/OSCP/OSCPDevice.cpp
./src/Dev/OSCP/WSDLBuilder.cpp
./src/Dev/Service.cpp
./src/OSCLibrary.cpp
./src/Util/DebugOut.cpp
./src/Util/DefaultUUIDGenerator.cpp
./src/Util/FromString.cpp
./src/Util/Helpers.cpp
./src/Util/Task.cpp
./src/Util/ToString.cpp
./src/Util/TypeConversion.cpp
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
./src/Dependencies/Poco/Clock.cpp
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
./src/Dependencies/Poco/FPEnvironment.cpp
./src/Dependencies/Poco/Latin1Encoding.cpp
./src/Dependencies/Poco/Latin2Encoding.cpp
./src/Dependencies/Poco/Latin9Encoding.cpp
./src/Dependencies/Poco/LocalDateTime.cpp
./src/Dependencies/Poco/MD4Engine.cpp
./src/Dependencies/Poco/MD5Engine.cpp
./src/Dependencies/Poco/MemoryPool.cpp
./src/Dependencies/Poco/MemoryStream.cpp
./src/Dependencies/Poco/NullStream.cpp
./src/Dependencies/Poco/Mutex.cpp
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


list(APPEND OSCLibSOURCES ./datamodel/BICEPS_DomainModel.cxx)
list(APPEND OSCLibSOURCES ./datamodel/BICEPS_MessageModel.cxx)
list(APPEND OSCLibSOURCES ./datamodel/DICOMDeviceDescription.cxx)
list(APPEND OSCLibSOURCES ./datamodel/ExtensionPoint.cxx)
list(APPEND OSCLibSOURCES ./datamodel/wsdl-custom.cxx)
list(APPEND OSCLibSOURCES ./datamodel/wsdl-soap-binding.cxx)
list(APPEND OSCLibSOURCES ./datamodel/ws-addressing.cxx)
list(APPEND OSCLibSOURCES ./datamodel/ws-policy.cxx)
list(APPEND OSCLibSOURCES ./datamodel/ws-streaming.cxx)
list(APPEND OSCLibSOURCES ./datamodel/eventing.cxx)
list(APPEND OSCLibSOURCES ./datamodel/wsdd-discovery-1.1-schema-os.cxx)
list(APPEND OSCLibSOURCES ./datamodel/MessageModel-Discovery.cxx)


list(APPEND OSCLibSOURCES ${PocoSOURCES})

add_library(OSCLib SHARED ${OSCLibSOURCES})

add_executable(UnitTests
Tests/UnitTests.cpp
Tests/IntegrationTests/TestStress.cpp
Tests/Unittests/TestBinding.cpp
Tests/IntegrationTests/TestEventing.cpp
Tests/IntegrationTests/TestDiscovery.cpp
Tests/Unittests/TestIPBinding.cpp
Tests/IntegrationTests/TestCreateWSDL.cpp
Tests/OSCPTests/TestConnectionLost.cpp
Tests/OSCPTests/TestDICOM.cpp
Tests/OSCPTests/TestMultiOSCP.cpp
Tests/OSCPTests/TestSimpleOSCP.cpp
Tests/OSCPTests/TestPeriodicEvents.cpp
Tests/OSCPTests/TestStreamOSCP.cpp
Tests/IntegrationTests/TestAutobinding.cpp
Tests/IntegrationTests/TestComplexTypes.cpp
Tests/IntegrationTests/TestServiceInvoke.cpp
Tests/Unittests/TestUUIDGenerator.cpp
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
target_link_libraries(ExampleProject OSCLib ${PTHREAD_LIB} ${XERCES_LIB} ${ADDITIONAL_LIBS})
target_link_libraries(SimpleServiceDiscovery OSCLib ${PTHREAD_LIB} ${XERCES_LIB} ${ADDITIONAL_LIBS})
target_link_libraries(MDIBDump OSCLib ${PTHREAD_LIB} ${XERCES_LIB} ${ADDITIONAL_LIBS})
target_link_libraries(MDIBVisualizer OSCLib ${PTHREAD_LIB} ${XERCES_LIB} ${ADDITIONAL_LIBS})
target_link_libraries(GenericSubscription OSCLib ${PTHREAD_LIB} ${XERCES_LIB} ${ADDITIONAL_LIBS})
target_link_libraries(DPWSDiscoveryClient OSCLib ${PTHREAD_LIB} ${XERCES_LIB} ${ADDITIONAL_LIBS})
target_link_libraries(DPWSDiscoveryListener OSCLib ${PTHREAD_LIB} ${XERCES_LIB} ${ADDITIONAL_LIBS})
target_link_libraries(ClientForUniRostockDevices OSCLib ${PTHREAD_LIB} ${XERCES_LIB} ${ADDITIONAL_LIBS})