set( Name MonkeyBrushPlusPlus )
set( NAME MONKEYBRUSHPLUSPLUS )
set( namespace MonkeyBrushPlusPlus )
set( NAMESPACE MONKEYBRUSHPLUSPLUS )
set( INCLUDE_NAME MonkeyBrushPlusPlus )

set( MONKEYBRUSHPLUSPLUS_SOURCES
)

set( MONKEYBRUSHPLUSPLUS_HEADERS
)

include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

set( MONKEYBRUSHPLUSPLUS_LINK_LIBRARIES
	glfw
)

common_application( MonkeyBrushPlusPlus )

