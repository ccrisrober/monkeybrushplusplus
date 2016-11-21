include_directories(
	${PROJECT_BINARY_DIR}/include
	${PROJECT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
)

set( MBHELLOWORLD_HEADERS )
set( MBHELLOWORLD_SOURCES helloWorld.cpp )
set( MBHELLOWORLD_LINK_LIBRARIES
	MB
)

common_application( mbHelloWorld )


set( MBHELLOSCENEGRAPH_HEADERS )
set( MBHELLOSCENEGRAPH_SOURCES helloSceneGraph.cpp )
set( MBHELLOSCENEGRAPH_LINK_LIBRARIES
	MB
)

common_application( mbHelloSceneGraph )



set( MBCUBES_HEADERS )
set( MBCUBES_SOURCES cubes.cpp )
set( MBCUBES_LINK_LIBRARIES
	MB
)

common_application( mbCubes )



set( MBCUBES2_HEADERS )
set( MBCUBES2_SOURCES cubes2.cpp )
set( MBCUBES2_LINK_LIBRARIES
	MB
)

common_application( mbCubes2 )




set( MBQUASICRYSTAL_HEADERS )
set( MBQUASICRYSTAL_SOURCES quasicrystal.cpp )
set( MBQUASICRYSTAL_LINK_LIBRARIES
	MB
)

common_application( mbQuasicrystal )



set( MBNEWTONFRACTAL_HEADERS )
set( MBNEWTONFRACTAL_SOURCES newtonFractal.cpp )
set( MBNEWTONFRACTAL_LINK_LIBRARIES
	MB
)

common_application( mbNewtonFractal )




set( MBBROWNIAN_HEADERS )
set( MBBROWNIAN_SOURCES brownian.cpp )
set( MBBROWNIAN_LINK_LIBRARIES
	MB
)

common_application( mbBrownian )
