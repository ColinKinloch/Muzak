project(libMuzak)
cmake_minimum_required(VERSION 2.6)

add_definitions("-std=c++11 -g")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/")

option(BUILD_SHARED_LIBS "Build Muzak shared library." on)
option(BUILD_STATIC_LIBS "Dont, build Muzak static library." off)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

set(MUZAK_HEADERS
	include/Muzak/Muzak.hh
)
set(MUZAK_SRCS
	${MUZAK_HEADERS}
	src/Muzak.cc
)
include_directories(include)

if(BUILD_SHARED_LIBS)
	add_library(Muzak SHARED ${MUZAK_SRCS})
endif()
if(BUILD_STATIC_LIBS)
	add_library(Muzak_static STATIC ${MUZAK_SRCS})
endif()


add_executable(MuzakTest src/MuzakTest.cc)

target_link_libraries(MuzakTest Muzak)

include(FindPkgConfig)
pkg_search_module(PortAudio REQUIRED portaudio-2.0)

find_package(PortMidi)

if(PortAudio_FOUND)
	include_directories(${PortAudio_INCLUDE_DIR})
	target_link_libraries(MuzakTest ${PortAudio_LIBRARIES})
endif()
if(PORTMIDI_FOUND)
	include_directories(${PORTMIDI_INCLUDE_DIR})
	target_link_libraries(MuzakTest ${PORTMIDI_LIBRARIES})
endif()
