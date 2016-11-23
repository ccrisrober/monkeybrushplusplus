cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(MB VERSION 0.1.0 )
set(MB_VERSION_ABI 1)

# Disable in source building
if( "${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}" )
	message( FATAL "no in source building allowed." )
endif()

list(APPEND CMAKE_MODULE_PATH 
	${PROJECT_SOURCE_DIR}/CMake
	${CMAKE_SOURCE_DIR}/CMake/common)

# Default build type is Debug
if( NOT CMAKE_BUILD_TYPE )
	set( CMAKE_BUILD_TYPE Debug )
endif( NOT CMAKE_BUILD_TYPE )

if ( CMAKE_BUILD_TYPE MATCHES "Debug" )
	add_definitions( -DDEBUG )
endif( )

include(GitExternal)

set(MB_DESCRIPTION "MonkeyBrush++")
set(COMMON_PROJECT_DOMAIN maldicion069)

include(Common)

common_find_package( OpenGL REQUIRED SYSTEM )
common_find_package( GLEW REQUIRED SYSTEM )
common_find_package( Boost COMPONENTS unit_test_framework )
common_find_package( GLFW )
common_find_package(FreeImage REQUIRED SYSTEM)

#set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF)
#set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

list (APPEND MB_DEPENDENT_LIBRARIES OpenGL GLEW GLFW FreeImage)

common_find_package_post()

add_subdirectory(mb)
add_subdirectory(examples)

if(${Boost_FOUND})
	add_subdirectory(tests)
endif()

#set(PROJECT_VERSION_ABI ${${PROJECT_NAME}_VERSION_ABI})

# Allow warnings
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")



#if(WIN32)
#	set(GLEW_INCLUDE_DIR "c:/libs/glew-2.0.0/include")
#	set(GLEW_LIBRARY "c:/libs/glew-2.0.0/lib/Release/Win32/glew32.lib")
#endif()


#set( PROJECT_INCLUDE_NAME MonkeyBrushPlusPlus )


#install( FILES ${PROJECT_BINARY_DIR}/include/MonkeyBrusPlusPlus/defines.h
#	DESTINATION include/MonkeyBrusPlusPlus )
#install( FILES ${PROJECT_BINARY_DIR}/include/MonkeyBrusPlusPlus/defines${SYSTEM}.h
#	DESTINATION include/MonkeyBrusPlusPlus )

# include(CPackConfig)
# include(DoxygenRule)
