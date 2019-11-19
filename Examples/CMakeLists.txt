# Configure Examples

message(STATUS "### Configuring Examples...")

# Add all bins/libs
add_subdirectory(ExampleCachedProvider)
add_subdirectory(ExampleConsumer)
add_subdirectory(ExampleConsumer4SoftICEStreaming)
add_subdirectory(ExampleProject)
add_subdirectory(ExampleProvider)
add_subdirectory(MDIBVisualizer)

if(SDC_ADVANCED_EXAMPLES)
    add_subdirectory(PulseOximeterProvider)
endif()

# SSL
add_subdirectory(SSL)
