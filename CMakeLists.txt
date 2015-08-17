cmake_minimum_required(VERSION 2.8)

project (Jarvis)


include_directories (${CMAKE_CURRENT_SOURCE_DIR}/src)

include (Local.cmake)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")
set (INSTALL_DIR ${CMAKE_SOURCE_DIR}/bin CACHE STRING "Instalation path")

find_package (ZMQ REQUIRED)
if (NOT ZMQ_FOUND)
    message (ERROR "ZMQ not found!")
endif()
include_directories (${ZMQ_INCLUDE_DIR})

list (APPEND ALL_LIBS ${ZMQ_LIBRARIES})

find_package(Boost
  REQUIRED
  COMPONENTS system filesystem
  )
FIND_PACKAGE ( X11 REQUIRED )
IF ( X11_FOUND )
      INCLUDE_DIRECTORIES ( ${X11_INCLUDE_DIR} )
      LINK_LIBRARIES ( ${X11_LIBRARIES} )
      MESSAGE ( STATUS " X11_INCLUDE_DIR: " ${X11_INCLUDE_DIR} )
      MESSAGE ( STATUS " X11_LIBRARIES: " ${X11_LIBRARIES} )
ENDIF ( X11_FOUND )

FIND_PACKAGE ( ALSA REQUIRED )
IF ( ALSA_FOUND )
    INCLUDE_DIRECTORIES ( ${ALSA_INCLUDE_DIR} )
    LINK_LIBRARIES ( ${ALSA_LIBRARIES} )
    MESSAGE ( STATUS " ALSA_INCLUDE_DIR: " ${ALSA_INCLUDE_DIR} )
    MESSAGE ( STATUS " ALSA_LIBRARIES: " ${ALSA_LIBRARIES} )
ENDIF ( ALSA_FOUND )


find_package (Threads)

list (APPEND ALL_LIBS 
    ${Boost_LIBRARIES} 
    ${CMAKE_THREAD_LIBS_INIT}
    ${X11_LIBRARIES} 
    ${ALSA_LIBRARIES} )

if (MSVC)
    add_definitions(/MP)
else()
    add_definitions(-std=c++1y -g -Wall -lpthread )
endif()

add_subdirectory (src)

if (MSVC)
endif ()

install( DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/res" 
         DESTINATION "${INSTALL_DIR}"
)
