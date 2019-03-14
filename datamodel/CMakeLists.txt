# Current Module
set( CURRENT_MODULE_NAME DataModel )
# Add this for better project structure after cmake generation
project(${CURRENT_MODULE_NAME})

message(STATUS "Adding Module ${CURRENT_MODULE_NAME}...")

# Variables for better handling
set(GEN_DIR_NAME generated)
set(XSD_DIR_NAME xsd)

set(GEN_DIR ${CMAKE_CURRENT_LIST_DIR}/${GEN_DIR_NAME}/)
set(XSD_DIR ${CMAKE_CURRENT_LIST_DIR}/${XSD_DIR_NAME}/)

set(SCRIPT_DIR ${CMAKE_CURRENT_LIST_DIR})

# Add Empty Library of type OBJECT
add_library(${CURRENT_MODULE_NAME} OBJECT "")


# Better Handling of Public Header Files
set(MODULE_PUBLIC_HEADERS       ${GEN_DIR}/BICEPS_MessageModel.hxx
                                ${GEN_DIR}/BICEPS_ParticipantModel.hxx
                                ${GEN_DIR}/DICOMDeviceDescription.hxx
                                ${GEN_DIR}/eventing.hxx
                                ${GEN_DIR}/ExtensionPoint.hxx
                                ${GEN_DIR}/MDPWS.hxx
                                ${GEN_DIR}/MetadataExchange.hxx
                                ${GEN_DIR}/NormalizedMessageModel.hxx
                                ${GEN_DIR}/ws-addressing.hxx
                                ${GEN_DIR}/ws-policy.hxx
                                ${GEN_DIR}/ws-streaming.hxx
                                ${GEN_DIR}/wsdd-discovery-1.1-schema-os.hxx
                                ${GEN_DIR}/wsdd-dpws-1.1-schema-os.hxx
                                ${GEN_DIR}/wsdl-custom.hxx
                                ${GEN_DIR}/wsdl-soap-binding.hxx
                                # FWD
                                ${GEN_DIR}/BICEPS_MessageModel-fwd.hxx
                                ${GEN_DIR}/BICEPS_ParticipantModel-fwd.hxx
                                ${GEN_DIR}/DICOMDeviceDescription-fwd.hxx
                                ${GEN_DIR}/eventing-fwd.hxx
                                ${GEN_DIR}/ExtensionPoint-fwd.hxx
                                ${GEN_DIR}/MDPWS-fwd.hxx
                                ${GEN_DIR}/MetadataExchange-fwd.hxx
                                ${GEN_DIR}/NormalizedMessageModel-fwd.hxx
                                ${GEN_DIR}/ws-addressing-fwd.hxx
                                ${GEN_DIR}/ws-policy-fwd.hxx
                                ${GEN_DIR}/ws-streaming-fwd.hxx
                                ${GEN_DIR}/wsdd-discovery-1.1-schema-os-fwd.hxx
                                ${GEN_DIR}/wsdd-dpws-1.1-schema-os-fwd.hxx
                                ${GEN_DIR}/wsdl-custom-fwd.hxx
                                ${GEN_DIR}/wsdl-soap-binding-fwd.hxx
                                
                                # OSDM
                                ${GEN_DIR}/osdm.hxx
                                ${GEN_DIR}/osdm-fwd.hxx
                                
)

# Add the sources to the target
target_sources(${CURRENT_MODULE_NAME}
        PRIVATE
        # Source Files
        ${GEN_DIR}/BICEPS_MessageModel.cxx
        ${GEN_DIR}/BICEPS_ParticipantModel.cxx
        ${GEN_DIR}/DICOMDeviceDescription.cxx
        ${GEN_DIR}/eventing.cxx
        ${GEN_DIR}/ExtensionPoint.cxx
        ${GEN_DIR}/MDPWS.cxx
        ${GEN_DIR}/MetadataExchange.cxx
        ${GEN_DIR}/NormalizedMessageModel.cxx
        ${GEN_DIR}/ws-addressing.cxx
        ${GEN_DIR}/ws-policy.cxx
        ${GEN_DIR}/ws-streaming.cxx
        ${GEN_DIR}/wsdd-discovery-1.1-schema-os.cxx
        ${GEN_DIR}/wsdd-dpws-1.1-schema-os.cxx
        ${GEN_DIR}/wsdl-custom.cxx
        ${GEN_DIR}/wsdl-soap-binding.cxx
        # Add the includes too (for better generation)
        # Public Headers
        ${MODULE_PUBLIC_HEADERS}
        # Private Headers
        #
    PUBLIC
        ${MODULE_PUBLIC_HEADERS}
)

# Some includes
target_include_directories( ${CURRENT_MODULE_NAME} PUBLIC ${GEN_DIR} )












