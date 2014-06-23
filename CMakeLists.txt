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
  include/Muzak/Node.hh
  include/Muzak/Mixer.hh
  include/Muzak/Midi.hh
  include/Muzak/Generator.hh
  include/Muzak/gens/Sine.hh
  include/Muzak/Instrument.hh
)
set(MUZAK_SRCS
  ${MUZAK_HEADERS}
  src/Node.cc
  src/Mixer.cc
  src/Midi.cc
  src/Generator.cc
  src/gens/Sine.cc
  src/Instrument.cc
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
pkg_search_module(PORTAUDIO REQUIRED portaudio-2.0)

find_package(PortMidi)

if(PORTAUDIO_FOUND)
  include_directories(${PORTAUDIO_INCLUDE_DIR})
  target_link_libraries(MuzakTest ${PORTAUDIO_LIBRARIES})
endif()
if(PORTMIDI_FOUND)
  include_directories(${PORTMIDI_INCLUDE_DIR})
  target_link_libraries(MuzakTest ${PORTMIDI_LIBRARIES})
endif()
