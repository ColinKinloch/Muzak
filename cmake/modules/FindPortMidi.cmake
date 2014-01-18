# - Try to find PortMidi
# Once done, this will define
#
#  PORTMIDI_FOUND - system has PortMidi
#  PORTMIDI_INCLUDE_DIRS - the PortMidi include directories
#  PORTMIDI_LIBRARIES - link these to use PortMidi
#  PORTMIDI_VERSION - detected version of PortMidi
#
# See documentation on how to write CMake scripts at
# http://www.cmake.org/Wiki/CMake:How_To_Find_Libraries

find_path(PORTMIDI_INCLUDE_DIR portmidi.h)
find_library(PORTMIDI_LIBRARY NAMES portmidi libportmidi)

set(PORTMIDI_LIBRARIES ${PORTMIDI_LIBRARY})
set(PORTMIDI_INCLUDE_DIRS ${PORTMIDI_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(PORTMIDI DEFAULT_MSG
																PORTMIDI_LIBRARY PORTMIDI_INCLUDE_DIR)

mark_as_advanced(PORTMIDI_INCLUDE_DIR PORTMIDI_LIBRARY)