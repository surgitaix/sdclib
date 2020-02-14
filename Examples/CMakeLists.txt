# Configure Examples

message(STATUS "### Configuring Examples...")

# Add all bins/libs
add_subdirectory(ReferenceProvider)
add_subdirectory(ReferenceConsumer)
add_subdirectory(MDIBVisualizer)

if(SDC_ADVANCED_EXAMPLES)
    add_subdirectory(PulseOximeterProvider)
endif()

