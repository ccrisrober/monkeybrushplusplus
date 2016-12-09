if( MB_WITH_EXAMPLES )

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


##set( MBHELLOWORLD_HEADERS )
##set( MBHELLOWORLD_SOURCES helloWorld.cpp )
##set( MBHELLOWORLD_LINK_LIBRARIES
##	mb
##)
##common_application( mbHelloWorld )


##set( MBRANDOMCUBE_HEADERS )
##set( MBRANDOMCUBE_SOURCES randomCube.cpp )
##set( MBRANDOMCUBE_LINK_LIBRARIES
##  mb
##)
##common_application( mbRandomCube )


##set( MBTEXSWAP_HEADERS )
##set( MBTEXSWAP_SOURCES texSwap.cpp )
##set( MBTEXSWAP_LINK_LIBRARIES
##	mb
##)
##common_application( mbTexSwap )


##set( MBBROWNIAN_HEADERS )
##set( MBBROWNIAN_SOURCES brownian.cpp )
##set( MBBROWNIAN_LINK_LIBRARIES
##  mb
##)
##common_application( mbBrownian )


##set( MBSPHERICALHARMONICS_HEADERS )
##set( MBSPHERICALHARMONICS_SOURCES sphericalHarmonics.cpp )
##set( MBSPHERICALHARMONICS_LINK_LIBRARIES
##  mb
##)
##common_application( mbSphericalHarmonics )


##set( MBHELLOMESH_HEADERS )
##set( MBHELLOMESH_SOURCES helloMesh.cpp )
##set( MBHELLOMESH_LINK_LIBRARIES
##  mb
##)
##common_application( mbHelloMesh )


##set( MBALIENTEXTURE_HEADERS )
##set( MBALIENTEXTURE_SOURCES alienTexture.cpp )
##set( MBALIENTEXTURE_LINK_LIBRARIES
##  mb
##)
##common_application( mbAlienTexture )


##set( MBNORMALINTERPOLATION_HEADERS )
##set( MBNORMALINTERPOLATION_SOURCES normalInterpolation.cpp )
##set( MBNORMALINTERPOLATION_LINK_LIBRARIES
##  mb
##)
##common_application( mbNormalInterpolation )


##set( MBTOONSHADING_HEADERS )
##set( MBTOONSHADING_SOURCES toonShading.cpp )
##set( MBTOONSHADING_LINK_LIBRARIES
##  mb
##)
##common_application( mbToonShading )


##set( MBCUBES_HEADERS )
##set( MBCUBES_SOURCES cubes.cpp )
##set( MBCUBES_LINK_LIBRARIES
##  mb
##)
##common_application( mbCubes )


##set( MBHEIGHTMAP_HEADERS )
##set( MBHEIGHTMAP_SOURCES heightmap.cpp )
##set( MBHEIGHTMAP_LINK_LIBRARIES
##  mb
##)
##common_application( mbHeightmap )


##set( MBORBITPIVOT_HEADERS )
##set( MBORBITPIVOT_SOURCES orbitPivot.cpp )
##set( MBORBITPIVOT_LINK_LIBRARIES
##  mb
##)
##common_application( mbOrbitPivot )


##set( MBEXPLOSION_HEADERS )
##set( MBEXPLOSION_SOURCES explosion.cpp )
##set( MBEXPLOSION_LINK_LIBRARIES
##  mb
##)
##common_application( mbExplosion )


##set( MBSCENEGRAPH_HEADERS )
##set( MBSCENEGRAPH_SOURCES sceneGraph.cpp )
##set( MBSCENEGRAPH_LINK_LIBRARIES
##  mb
##)
##common_application( mbSceneGraph )


##set( MBALPHATEXTURES_HEADERS )
##set( MBALPHATEXTURES_SOURCES alphaTextures.cpp )
##set( MBALPHATEXTURES_LINK_LIBRARIES
##  mb
##)
##common_application( mbAlphaTextures )


  set( MBTRIANGLETESSELATION_HEADERS )
  set( MBTRIANGLETESSELATION_SOURCES triangleTesselation.cpp )
  set( MBTRIANGLETESSELATION_LINK_LIBRARIES
    mb
  )
  common_application( mbTriangleTesselation )


  set( MBPHONGTESSELATION_HEADERS )
  set( MBPHONGTESSELATION_SOURCES phongTesselation.cpp )
  set( MBPHONGTESSELATION_LINK_LIBRARIES
    mb
  )
  common_application( mbPhongTesselation )
endif()






##set( MBHEIGHTMAPEARTH_HEADERS )
##set( MBHEIGHTMAPEARTH_SOURCES heightmapEarth.cpp )
##set( MBHEIGHTMAPEARTH_LINK_LIBRARIES
##  mb
##)
##common_application( mbHeightmapEarth )



##
##
##set( MBHELLOTEXTURE_HEADERS )
##set( MBHELLOTEXTURE_SOURCES helloTexture.cpp )
##set( MBHELLOTEXTURE_LINK_LIBRARIES
##	mb
##)
##common_application( mbHelloTexture )
##
##
##set( MBQUASICRYSTAL_HEADERS )
##set( MBQUASICRYSTAL_SOURCES quasicrystal.cpp )
##set( MBQUASICRYSTAL_LINK_LIBRARIES
##	mb
##)
##common_application( mbQuasicrystal )
##
##
##
##
##set( MBXOR_HEADERS )
##set( MBXOR_SOURCES xor.cpp )
##set( MBXOR_LINK_LIBRARIES
##	mb
##)
##common_application( mbXor )
##
##
##set( MBMANGA_HEADERS )
##set( MBMANGA_SOURCES manga.cpp )
##set( MBMANGA_LINK_LIBRARIES
##	mb
##)
##common_application( mbManga )
##
##
##set( MBFRACTALWORLD_HEADERS )
##set( MBFRACTALWORLD_SOURCES fractalWorld.cpp )
##set( MBFRACTALWORLD_LINK_LIBRARIES
##	mb
##)
##common_application( mbFractalWorld )
##
##
##
##
##
##
##set( MBTURBULENCETEXTURE_HEADERS )
##set( MBTURBULENCETEXTURE_SOURCES turbulenceTexture.cpp )
##set( MBTURBULENCETEXTURE_LINK_LIBRARIES
##	mb
##)
##common_application( mbTurbulenceTexture )
##
##
##set( MBIMAGEPROCESSING_HEADERS )
##set( MBIMAGEPROCESSING_SOURCES imageProcessing.cpp )
##set( MBIMAGEPROCESSING_LINK_LIBRARIES
##	mb
##)
##common_application( mbImageProcessing )
##
##
##set( MBKUWAHARAFILTER_HEADERS )
##set( MBKUWAHARAFILTER_SOURCES kuwaharaFilter.cpp )
##set( MBKUWAHARAFILTER_LINK_LIBRARIES
##	mb
##)
##common_application( mbKuwaharaFilter )
##
##
##set( MBNORMALMAPPING_HEADERS )
##set( MBNORMALMAPPING_SOURCES normalMapping.cpp )
##set( MBNORMALMAPPING_LINK_LIBRARIES
##	mb
##)
##common_application( mbNormalMapping )
##
##
##set( MBNEWTONFRACTAL_HEADERS )
##set( MBNEWTONFRACTAL_SOURCES newtonFractal.cpp )
##set( MBNEWTONFRACTAL_LINK_LIBRARIES
##	mb
##)
##
##common_application( mbNewtonFractal )
##
##
##set( MBKALEIDOSCOPE_HEADERS )
##set( MBKALEIDOSCOPE_SOURCES kaleidoscope.cpp )
##set( MBKALEIDOSCOPE_LINK_LIBRARIES
##	mb
##)
##
##common_application( mbKaleidoscope )
##
##
##set( MBCOLORBLIND_HEADERS )
##set( MBCOLORBLIND_SOURCES colorBlind.cpp )
##set( MBCOLORBLIND_LINK_LIBRARIES
##	mb
##)
##
##common_application( mbColorBlind )
##
##
##if(${Rapidjson_FOUND})
##	set( MBJSONSCENE_HEADERS )
##	set( MBJSONSCENE_SOURCES jsonScene.cpp )
##	set( MBJSONSCENE_LINK_LIBRARIES
##		mb
##	    ${RAPIDJSON_LIBRARIES}
##	)
##
##	common_application( mbJsonScene )
##endif()
##
##
##set( MBHDR_HEADERS )
##set( MBHDR_SOURCES hdr.cpp )
##set( MBHDR_LINK_LIBRARIES
##	mb
##)
##common_application( mbHDR )
##
##
##set( MBFBOEXAMPLE_HEADERS )
##set( MBFBOEXAMPLE_SOURCES fboExample.cpp )
##set( MBFBOEXAMPLE_LINK_LIBRARIES
##	mb
##)
##common_application( mbFBOExample )
