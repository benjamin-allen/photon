project (PHOTON)
cmake_minimum_required(VERSION 3.8)

set(PHOTON_VERSION_MAJOR 0)
set(PHOTON_VERSION_MINOR 1)
set(PHOTON_VERSION_PATCH 0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

option(BuildStatic "BuildStatic" OFF)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

if (UNIX AND NOT APPLE)
	message(STATUS "Generating build files for Linux in ${CMAKE_CURRENT_BINARY_DIR}")
	if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
		if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 7.0)
			message(WARNING "Photon requires support for C++17; GCC version 7 or above is strongly advised.")
		endif()
	else()
		message(WARNING "GCC version 7 or above is advised. Clang and others are not currently supported, however newer versions of Clang may be able to build photon.")
		message(WARNING "Photon's CMakeLists.txt will default to using g++-7 if it is available.")
	endif()
	set(CMAKE_CXX_COMPILER "g++-7")
	add_definitions(-std=c++17)
endif()

if (WIN32)
	message(STATUS "Generating build files for Windows in ${CMAKE_CURRENT_BINARY_DIR}")
	if(NOT ${MSVC_VERSION} EQUAL 1910)
		message(WARNING "Photon requires support for C++17; Visual Studio 2017 (version 15.0) or above is strongly advised.")
	endif()
	add_definitions(/std:c++latest)
endif()


set(PHOTON_LIBRARY_NAME "libphoton-${PHOTON_VERSION_MAJOR}-${PHOTON_VERSION_MINOR}-${PHOTON_VERSION_PATCH}")
set(PHOTON_LIBRARY_NAME_STATIC "libphoton_static-${PHOTON_VERSION_MAJOR}-${PHOTON_VERSION_MINOR}-${PHOTON_VERSION_PATCH}")

set(
	PHOTON_LIBRARY_SOURCES

	src/component.cpp
	src/entitymanager.cpp
	src/system.cpp
)

message(STATUS "Building photon version ")
add_library(${PHOTON_LIBRARY_NAME} SHARED ${PHOTON_LIBRARY_SOURCES})
if(BuildStatic)
	add_library(${PHOTON_LIBRARY_NAME} STATIC ${PHOTON_LIBRARY_SOURCES})
endif()
