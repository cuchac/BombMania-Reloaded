#INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR})
add_library (objectLoader 3dsloader.cpp main.cpp mat_vect.cpp object.cpp texture.cpp loader.cpp)

IF(WIN32)
	TARGET_LINK_LIBRARIES(objectLoader libpng xml )
ENDIF(WIN32)

IF(UNIX)

   find_package(PkgConfig REQUIRED)

   pkg_check_modules(OL_DEPS REQUIRED gl libpng)

   INCLUDE_DIRECTORIES(${OL_DEPS_INCLUDE_DIRS})
   TARGET_LINK_LIBRARIES(objectLoader xml ${OL_DEPS_LIBRARIES})

ENDIF(UNIX)


