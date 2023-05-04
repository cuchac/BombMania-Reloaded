ADD_EXECUTABLE(bombmania settings.cpp support.cpp bombmania.cpp player.cpp game.cpp world.cpp controls.cpp)

IF(WIN32)
   LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}\\win32\\lib)
ENDIF(WIN32)

IF(UNIX)
   TARGET_LINK_LIBRARIES(bombmania)
ENDIF(UNIX)

TARGET_LINK_LIBRARIES(bombmania module_opengl)
INSTALL(TARGETS bombmania DESTINATION bin)

