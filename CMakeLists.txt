project (PHOTON)
cmake_minimum_required(VERSION 3.8)

set(PHOTON_VERSION_MAJOR 0)
set(PHOTON_VERSION_MINOR 1)
set(PHOTON_VERSION_PATCH 0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

if (UNIX AND NOT APPLE)
	message(STATUS "Generating build files for Linux in ${CMAKE_CURRENT_BINARY_DIR}")
	set(CMAKE_CXX_COMPILER "g++-7")
	add_definitions(-std=c++17)
endif()

if (WIN32)
	message(STATUS "Generating build files for Windows in ${CMAKE_CURRENT_BINARY_DIR}")
	if(NOT ${MSVC_VERSION} GREATER_EQUAL 1900)
		message(WARNING "Photon requires support for C++17; Visual Studio 2017 (version 15.0) or above is strongly advised.")
	endif()
	add_definitions(/std:c++latest)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)


set(PHOTON_LIBRARY_NAME "libphoton-${PHOTON_VERSION_MAJOR}-${PHOTON_VERSION_MINOR}-${PHOTON_VERSION_PATCH}")

set(
	PHOTON_LIBRARY_SOURCES

	src/component.cpp
	src/entitymanager.cpp
	src/system.cpp
)

if(WIN32)
	set(
		PHOTON_LIBRARY_INCLUDES

		include/component.hpp
		include/entitymanager.hpp
		include/system.hpp
		include/photon.hpp
		include/template_component.ipp
		include/template_entitymanager.ipp
		include/template_system.ipp
		include/nontemplate_entitymanager.ipp
	)
else()
	set(PHOTON_LIBRARY_INCLUDES)
endif()

message(STATUS "Building Photon version ${PHOTON_VERSION_MAJOR}.${PHOTON_VERSION_MINOR}.${PHOTON_VERSION_PATCH}")
add_library(${PHOTON_LIBRARY_NAME} STATIC ${PHOTON_LIBRARY_SOURCES} ${PHOTON_LIBRARY_INCLUDES})
