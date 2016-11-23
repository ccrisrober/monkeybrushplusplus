include_directories(
	${PROJECT_BINARY_DIR}/include
	${PROJECT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
)

configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/shaderFiles.h.in
	${CMAKE_CURRENT_BINARY_DIR}/shaderFiles.h )

configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/assetsFiles.h.in
	${CMAKE_CURRENT_BINARY_DIR}/assetsFiles.h )

set( MBHELLOWORLD_HEADERS )
set( MBHELLOWORLD_SOURCES helloWorld.cpp )
set( MBHELLOWORLD_LINK_LIBRARIES
	MB
)

common_application( mbHelloWorld )



set( MBHELLOTEXTURE_HEADERS )
set( MBHELLOTEXTURE_SOURCES helloTexture.cpp )
set( MBHELLOTEXTURE_LINK_LIBRARIES
	MB
)

common_application( mbHelloTexture )


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




set( MBXOR_HEADERS )
set( MBXOR_SOURCES xor.cpp )
set( MBXOR_LINK_LIBRARIES
	MB
)

common_application( mbXor )


set( MBADVENTION_HEADERS )
set( MBADVENTION_SOURCES advention.cpp )
set( MBADVENTION_LINK_LIBRARIES
	MB
)

common_application( mbAdvention )




set( MBMANGA_HEADERS )
set( MBMANGA_SOURCES manga.cpp )
set( MBMANGA_LINK_LIBRARIES
	MB
)

common_application( mbManga )




set( MBEXPLOSION_HEADERS )
set( MBEXPLOSION_SOURCES explosion.cpp )
set( MBEXPLOSION_LINK_LIBRARIES
	MB
)

common_application( mbExplosion )




set( MBFRACTALWORLD_HEADERS )
set( MBFRACTALWORLD_SOURCES fractalWorld.cpp )
set( MBFRACTALWORLD_LINK_LIBRARIES
	MB
)

common_application( mbFractalWorld )



set( MBKALEIDOSCOPE_HEADERS )
set( MBKALEIDOSCOPE_SOURCES kaleidoscope.cpp )
set( MBKALEIDOSCOPE_LINK_LIBRARIES
	MB
)

common_application( mbKaleidoscope )

