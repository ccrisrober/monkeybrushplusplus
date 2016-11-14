project(MonkeyBrushPlusPlus)
cmake_minimum_required(VERSION 3.1)
project(MonkeyBrushPlusPlus VERSION 0.1.0 )
set(MonkeyBrushPlusPlus_VERSION_ABI 1)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake
  ${CMAKE_SOURCE_DIR}/CMake/common)

include(GitExternal)

set(COMMON_PROJECT_DOMAIN maldicion069)
set(MONKEYBRUSHPLUSPLUS_DESCRIPTION "MonkeyBrushPlusPlus")
set(PROJECT_VERSION_ABI ${${PROJECT_NAME}_VERSION_ABI})

include(Common)

# Allow warnings
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")
set(MONKEYBRUSHPLUSPLUS_LIBRARIES )

if(WIN32)
	set(GLEW_INCLUDE_DIR "C:/Users/maldicion069/Documents/glew-2.0.0/include")
	set(GLEW_LIBRARY "C:/Users/maldicion069/Documents/glew-2.0.0/lib/Release/x64")
endif()

common_find_package(GLEW REQUIRED SYSTEM)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

common_find_package(glfw)

common_find_package_post()

set (MONKEYBRUSHPLUSPLUS_DEPENDENT_LIBRARIES glew glfw)

add_subdirectory(src)

include(CPackConfig)
#include(DoxygenRule)
