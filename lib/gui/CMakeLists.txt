
add_library (module_gui cegui.cpp callbacks.cpp mainmenu.cpp window.cpp loading.cpp ingameMenu.cpp newGame.cpp messageBox.cpp)

IF(WIN32)
   TARGET_LINK_LIBRARIES(module_gui opengl32 glu32)	
   INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/win32/include)
   LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/win32/lib)
#  ISTALL(FILES ${CMAKE_SOURCE_DIR}/win32/lib/glut32.dll DESTINATION "")
#  INSTALL(FILES ${CMAKE_SOURCE_DIR}/win32/lib/libpng13.dll DESTINATION "")
#  INSTALL(FILES ${CMAKE_SOURCE_DIR}/win32/lib/zlib1.dll DESTINATION "")
ENDIF(WIN32)

IF(UNIX)

   find_package(GLUT REQUIRED)

   find_package(PkgConfig REQUIRED)

   pkg_check_modules(GUI_DEPS REQUIRED gl glu CEGUI-0 CEGUI-0-OPENGL)

   INCLUDE_DIRECTORIES(${GUI_DEPS_INCLUDE_DIRS} ${GLUT_INCLUDE_DIR})
   
   TARGET_LINK_LIBRARIES(module_gui objectLoader ${GUI_DEPS_LIBRARIES} ${GLUT_LIBRARIES})
ENDIF(UNIX)



#TARGET_LINK_LIBRARIES(module_gui objectLoader)
