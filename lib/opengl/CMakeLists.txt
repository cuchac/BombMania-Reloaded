
add_library (module_opengl draw.cpp opengl.cpp control.cpp objects.cpp playerOpengl.cpp gameOpengl.cpp worldOpengl.cpp)

IF(WIN32)
   TARGET_LINK_LIBRARIES(module_opengl opengl32 glu32)	
   LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/win32/lib)
   INSTALL(FILES ${CMAKE_SOURCE_DIR}/win32/lib/glut32.dll DESTINATION "")
   INSTALL(FILES ${CMAKE_SOURCE_DIR}/win32/lib/libpng13.dll DESTINATION "")
   INSTALL(FILES ${CMAKE_SOURCE_DIR}/win32/lib/zlib1.dll DESTINATION "")
ENDIF(WIN32)

IF(UNIX)
   find_package(GLUT REQUIRED)

   find_package(PkgConfig REQUIRED)
   
   set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
   set(THREADS_PREFER_PTHREAD_FLAG TRUE)
   find_package(Threads REQUIRED)

   pkg_check_modules(GL_DEPS REQUIRED gl glu CEGUI-0)

   INCLUDE_DIRECTORIES(${GL_DEPS_INCLUDE_DIRS} ${GLUT_INCLUDE_DIR})
   TARGET_LINK_LIBRARIES(module_opengl ${GL_DEPS_LIBRARIES} ${GLUT_LIBRARIES} Threads::Threads)
ENDIF(UNIX)



TARGET_LINK_LIBRARIES(module_opengl objectLoader module_gui)
