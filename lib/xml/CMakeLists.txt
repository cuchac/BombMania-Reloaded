INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include/xml)
add_definitions(-DTIXML_USE_STL)
add_library (xml xml.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp)



