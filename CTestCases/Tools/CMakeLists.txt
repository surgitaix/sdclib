list(APPEND TOOLSSOURCES
./MulticastHandler.cpp
./TestProvider.cpp
./TestConsumer.cpp
./PulseOximeterProvider.cpp
./PulseOximeterConsumer.cpp
)


if(WIN32)
	add_library(Tools STATIC ${TOOLSSOURCES})
else()
	add_library(Tools SHARED ${TOOLSSOURCES})
endif()
#target_include_directories (Tools PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
