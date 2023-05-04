PROJECT(bombmania)

cmake_minimum_required(VERSION 2.6)

#if you don't want the full compiler output, remove the following line
SET(CMAKE_VERBOSE_MAKEFILE ON)

# Set version
SET(BOMBMANIA_VERSION 0.2)

# Set full name with version
SET(BOMBMANIA_NAME ${PROJECT_NAME})
SET(BOMBMANIA_FULLNAME ${PROJECT_NAME}-0.2)

SET(BOMBMANIA_DATADIR share/${BOMBMANIA_FULLNAME}/)
SET(BOMBMANIA_DATADIR_RELATIVE ../${BOMBMANIA_DATADIR}/)

#Add uninstall target
CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")

#add definitions, compiler switches, etc.
IF(UNIX)
   ADD_DEFINITIONS(-Wall)
ENDIF(UNIX)

IF(WIN32)
   INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/win32/include)
   LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/win32/lib)
ENDIF(WIN32)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)

# Generate config.h
CONFIGURE_FILE(config.h.cmake config.h)
ADD_DEFINITIONS(-D_HAVE_CONFIG)
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR})

add_subdirectory (lib)
add_subdirectory (src)
add_subdirectory (res)

