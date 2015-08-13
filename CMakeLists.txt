cmake_minimum_required(VERSION 3.1)

project (Jarvis)


include_directories (${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/src)

include (Local.cmake)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")
set (INSTALL_DIR ${CMAKE_SOURCE_DIR}/bin CACHE STRING "Instalation path")

find_package (ZMQ REQUIRED)
if (NOT SDL2_FOUND)
    message (ERROR "ZMQ not found!")
endif()
include_directories (${ZMQ_INCLUDE_DIR})

if (MSVC)
    add_definitions(/MP)
else()
    add_definitions(-std=c++1z -g -Wall)
endif()

add_subdirectory (src)

if (MSVC)
"    install(
"        DIRECTORY "${SDL2DIR}/lib/win32/"
"        DESTINATION "${INSTALL_DIR}"
"        FILES_MATCHING PATTERN "*.dll"
"    )
endif ()
install( DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/res" 
         DESTINATION "${INSTALL_DIR}"
)
