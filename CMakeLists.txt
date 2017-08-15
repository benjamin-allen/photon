project (PHOTON)
cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

if (UNIX AND NOT APPLE)
	set(LINUX TRUE)
endif()

if(LINUX)
	add_definitions(-DBUILDING_ON_LINUX)
	message([STATUS] "Using <experimental/any>")
	set(CMAKE_CXX_COMPILER "g++-7")
endif()

set(PHOTON_LIBRARY_NAME "photon")
set(PHOTON_LIBRARY_NAME_STATIC "static_photon")

ADD_DEFINITIONS(
	-std=c++17
)
set(CMAKE_CXX_FLAGS "-std=c++17")

set(
	PHOTON_LIBRARY_SOURCES

	src/component.cpp
	src/entitymanager.cpp
	src/system.cpp
)

add_library(${PHOTON_LIBRARY_NAME} SHARED ${PHOTON_LIBRARY_SOURCES})
add_library(${PHOTON_LIBRARY_NAME_STATIC} STATIC ${PHOTON_LIBRARY_SOURCES})
