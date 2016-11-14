set( Name MonkeyBrushPlusPlus )
set( NAME MONKEYBRUSHPLUSPLUS )
set( namespace MonkeyBrushPlusPlus )
set( NAMESPACE MONKEYBRUSHPLUSPLUS )
set( INCLUDE_NAME MonkeyBrushPlusPlus )

set( MONKEYBRUSHPLUSPLUS_SOURCES
    Texture.cpp
)

set( MONKEYBRUSHPLUSPLUS_HEADERS
    Texture.hpp
)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
)

set( MONKEYBRUSHPLUSPLUS_LINK_LIBRARIES
    glfw
)

common_application( MonkeyBrushPlusPlus )
