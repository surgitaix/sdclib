# Configure Examples

message(STATUS "### Configuring Examples...")

# Add all bins/libs
add_executable(ExampleProject "")
add_executable(ExampleProvider "")
add_executable(ExampleConsumer "")
add_executable(ExampleConsumer4SoftICEStreaming "")
add_executable(ExampleCachedProvider "")
add_executable(MDIBVisualizer "")
add_executable(AbstractConsumerSimulator "")


# include
include(ExampleProject/CMakeLists.txt)
include(ExampleConsumer/CMakeLists.txt)
include(ExampleProvider/CMakeLists.txt)
include(ExampleConsumer4SoftICEStreaming/CMakeLists.txt)
include(ExampleCachedProvider/CMakeLists.txt)
include(MDIBVisualizer/CMakeLists.txt)
include(AbstractConsumerSimulator/CMakeLists.txt)
