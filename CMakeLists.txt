project(MonkeyBrushPlusPlus)
cmake_minimum_required(VERSION 3.1)
project(MonkeyBrushPlusPlus VERSION 0.1.0 )
set(MonkeyBrushPlusPlus_VERSION_ABI 1)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake
  ${CMAKE_SOURCE_DIR}/CMake/common)

include(GitExternal)

set(PROJECT_VERSION_ABI ${${PROJECT_NAME}_VERSION_ABI})

# Allow warnings
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")

include(Common)

set(COMMON_PROJECT_DOMAIN maldicion069)
set(MONKEYBRUSHPLUSPLUS_DESCRIPTION "MonkeyBrush++")

#if(WIN32)
#	set(GLEW_INCLUDE_DIR "c:/libs/glew-2.0.0/include")
#	set(GLEW_LIBRARY "c:/libs/glew-2.0.0/lib/Release/Win32/glew32.lib")
#endif()

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

common_find_package( OpenGL REQUIRED SYSTEM )
common_find_package( GLEW REQUIRED SYSTEM )
common_find_package( Boost COMPONENTS unit_test_framework )

list (APPEND MONKEYBRUSHPLUSPLUS_DEPENDENT_LIBRARIES OpenGL GLEW glfw)

common_find_package_post()

set( PROJECT_INCLUDE_NAME MonkeyBrushPlusPlus )

add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(tests)

install( FILES ${PROJECT_BINARY_DIR}/include/MonkeyBrusPlusPlus/defines.h
  DESTINATION include/MonkeyBrusPlusPlus )
install( FILES ${PROJECT_BINARY_DIR}/include/MonkeyBrusPlusPlus/defines${SYSTEM}.h
  DESTINATION include/MonkeyBrusPlusPlus )

include(CPackConfig)
#include(DoxygenRule)
