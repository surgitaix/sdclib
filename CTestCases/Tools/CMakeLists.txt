list(APPEND TOOLSSOURCES
./MulticastHandler.cpp
./TestSOAPMessageProvider.cpp
./TestSOAPMessageProviderAdapter.cpp
#./TestSOAPMessageSocketImpl.cpp
#./TestSOAPMessageHostAdapter.cpp
)

if(WIN32)
	add_library(Tools STATIC ${TOOLSSOURCES})
else()
	add_library(Tools SHARED ${TOOLSSOURCES})
endif()
#target_include_directories (Tools PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
