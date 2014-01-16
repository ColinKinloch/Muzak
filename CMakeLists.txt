project(Muzak)
cmake_minimum_required(VERSION 2.6)

add_definitions("-std=c++11 -g")

option(BUILD_SHARED_LIBS "Build Muzak shared library." on)
option(BUILD_STATIC_LIBS "Dont, build Muzak static library." off)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

set(MUZAK_HEADERS
	
)
set(MUZAK_SRC
	${MUZAK_HEADERS}
)

if(BUILD_SHARED_LIBS)
	add_library(Muzak SHARED ${MUZAK_SRCS})
endif()
if(BUILD_STATIC_LIBS)
	add_library(Muzak_static STATIC ${MUZAK_SRCS})
endif()

include_directories(include)

add_executable(MuzakTest src/MuzakTest.cc)

include(FindPkgConfig)
pkg_search_module(PortAudio REQUIRED portaudio-2.0)

if(PortAudio_FOUND)
	include_directories(${PortAudio_INCLUDE_DIR})
	target_link_libraries(MuzakTest ${PortAudio_LIBRARIES})
endif()
if(PortMidi_FOUND)
	include_directories(${PortMidi_INCLUDE_DIR})
	target_link_libraries(MuzakTest ${PortMidi_LIBRARIES})
endif()
