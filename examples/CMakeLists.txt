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


  set( MBPIXELIZATION_HEADERS )
  set( MBPIXELIZATION_SOURCES pixelization.cpp )
  set( MBPIXELIZATION_LINK_LIBRARIES
    mb
  )
  common_application( mbPixelization )


  set( MBTEST1_HEADERS )
  set( MBTEST1_SOURCES test1.cpp )
  set( MBTEST1_LINK_LIBRARIES
    mb
  )
  common_application( mbTest1 )


  set( MBCOLORBLIND_HEADERS )
  set( MBCOLORBLIND_SOURCES colorBlind.cpp )
  set( MBCOLORBLIND_LINK_LIBRARIES
    mb
  )
  common_application( mbColorBlind )


  set( MBSKETCHRENDERING_HEADERS )
  set( MBSKETCHRENDERING_SOURCES sketchRendering.cpp )
  set( MBSKETCHRENDERING_LINK_LIBRARIES
    mb
  )
  common_application( mbSketchRendering )


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


  set( MBHELLOMESHARGS_HEADERS )
  set( MBHELLOMESHARGS_SOURCES helloMeshArgs.cpp )
  set( MBHELLOMESHARGS_LINK_LIBRARIES
    mb
  )
  common_application( mbHelloMeshArgs )


  set( MBHELLOMESH_HEADERS )
  set( MBHELLOMESH_SOURCES helloMesh.cpp )
  set( MBHELLOMESH_LINK_LIBRARIES
    mb
  )
  common_application( mbHelloMesh )


  set( MBSPHERICALHARMONICS_HEADERS )
  set( MBSPHERICALHARMONICS_SOURCES sphericalHarmonics.cpp )
  set( MBSPHERICALHARMONICS_LINK_LIBRARIES
    mb
  )
  common_application( mbSphericalHarmonics )


  set( MBBROWNIAN_HEADERS )
  set( MBBROWNIAN_SOURCES brownian.cpp )
  set( MBBROWNIAN_LINK_LIBRARIES
    mb
  )
  common_application( mbBrownian )


  set( MBALIENTEXTURE_HEADERS )
  set( MBALIENTEXTURE_SOURCES alienTexture.cpp )
  set( MBALIENTEXTURE_LINK_LIBRARIES
    mb
  )
  common_application( mbAlienTexture )


  set( MBHATCHINGTEXTURE_HEADERS )
  set( MBHATCHINGTEXTURE_SOURCES hatchingTexture.cpp )
  set( MBHATCHINGTEXTURE_LINK_LIBRARIES
    mb
  )
  common_application( mbHatchingTexture )


  set( MBHATCHING3DTEXTURE_HEADERS )
  set( MBHATCHING3DTEXTURE_SOURCES hatching3DTexture.cpp )
  set( MBHATCHING3DTEXTURE_LINK_LIBRARIES
    mb
  )
  common_application( mbHatching3DTexture )


  set( MBTURBULENCETEXTURE_HEADERS )
  set( MBTURBULENCETEXTURE_SOURCES turbulenceTexture.cpp )
  set( MBTURBULENCETEXTURE_LINK_LIBRARIES
    mb
  )
  common_application( mbTurbulenceTexture )


  set( MBGRANITETEXTURE_HEADERS )
  set( MBGRANITETEXTURE_SOURCES graniteTexture.cpp )
  set( MBGRANITETEXTURE_LINK_LIBRARIES
    mb
  )
  common_application( mbGraniteTexture )


  set( MBTOONSHADING_HEADERS )
  set( MBTOONSHADING_SOURCES toonShading.cpp )
  set( MBTOONSHADING_LINK_LIBRARIES
    mb
  )
  common_application( mbToonShading )


  set( MBEXPLOSION_HEADERS )
  set( MBEXPLOSION_SOURCES explosion.cpp )
  set( MBEXPLOSION_LINK_LIBRARIES
    mb
  )
  common_application( mbExplosion )


  set( MBHEIGHTMAP_HEADERS )
  set( MBHEIGHTMAP_SOURCES heightmap.cpp )
  set( MBHEIGHTMAP_LINK_LIBRARIES
    mb
  )
  common_application( mbHeightmap )


  set( MBNORMALMAPPING_HEADERS )
  set( MBNORMALMAPPING_SOURCES normalMapping.cpp )
  set( MBNORMALMAPPING_LINK_LIBRARIES
    mb
  )
  common_application( mbNormalMapping )


  set( MBRAYTRACINGCS_HEADERS )
  set( MBRAYTRACINGCS_SOURCES rayTracingCS.cpp )
  set( MBRAYTRACINGCS_LINK_LIBRARIES
    mb
  )
  common_application( mbRayTracingCS )


  set( MBHELLOWORLD_HEADERS )
  set( MBHELLOWORLD_SOURCES helloWorld.cpp )
  set( MBHELLOWORLD_LINK_LIBRARIES
    mb
  )
  common_application( mbHelloWorld )


  set( MBNORMALINTERPOLATION_HEADERS )
  set( MBNORMALINTERPOLATION_SOURCES normalInterpolation.cpp )
  set( MBNORMALINTERPOLATION_LINK_LIBRARIES
    mb
  )
  common_application( mbNormalInterpolation )


  set( MBTEXSWAP_HEADERS )
  set( MBTEXSWAP_SOURCES texSwap.cpp )
  set( MBTEXSWAP_LINK_LIBRARIES
    mb
  )
  common_application( mbTexSwap )


  set( MBALPHATEXTURES_HEADERS )
  set( MBALPHATEXTURES_SOURCES alphaTextures.cpp )
  set( MBALPHATEXTURES_LINK_LIBRARIES
    mb
  )
  common_application( mbAlphaTextures )


  set( MBHELLOTEXTURE_HEADERS )
  set( MBHELLOTEXTURE_SOURCES helloTexture.cpp )
  set( MBHELLOTEXTURE_LINK_LIBRARIES
    mb
  )
  common_application( mbHelloTexture )


  set( MBRANDOMCUBE_HEADERS )
  set( MBRANDOMCUBE_SOURCES randomCube.cpp )
  set( MBRANDOMCUBE_LINK_LIBRARIES
    mb
  )
  common_application( mbRandomCube )


  set( MBORBITPIVOT_HEADERS )
  set( MBORBITPIVOT_SOURCES orbitPivot.cpp )
  set( MBORBITPIVOT_LINK_LIBRARIES
    mb
  )
  common_application( mbOrbitPivot )


  ##set( MBHEIGHTMAPTESSELATION_HEADERS )
  ##set( MBHEIGHTMAPTESSELATION_SOURCES heightmapTesselation.cpp )
  ##set( MBHEIGHTMAPTESSELATION_LINK_LIBRARIES
  ##  mb
  ##)
  ##common_application( mbHeightmapTesselation )



  ##set( MBIMAGEPROCESSING_HEADERS )
  ##set( MBIMAGEPROCESSING_SOURCES imageProcessing.cpp )
  ##set( MBIMAGEPROCESSING_LINK_LIBRARIES
  ##  mb
  ##)
  ##common_application( mbImageProcessing )


  ##set( MBRENDERTOTEXTURECS_HEADERS )
  ##set( MBRENDERTOTEXTURECS_SOURCES renderToTextureCS.cpp )
  ##set( MBRENDERTOTEXTURECS_LINK_LIBRARIES
  ##  mb
  ##)
  ##common_application( mbRenderToTextureCS )


  ##set( MBCOLORBLIND_HEADERS )
  ##set( MBCOLORBLIND_SOURCES colorBlind.cpp )
  ##set( MBCOLORBLIND_LINK_LIBRARIES
  ##  mb
  ##)
  ##common_application( mbColorBlind )


  set( MBKUWAHARAFILTER_HEADERS )
  set( MBKUWAHARAFILTER_SOURCES kuwaharaFilter.cpp )
  set( MBKUWAHARAFILTER_LINK_LIBRARIES
    mb
  )
  common_application( mbKuwaharaFilter )


  set( MBKALEIDOSCOPE_HEADERS )
  set( MBKALEIDOSCOPE_SOURCES kaleidoscope.cpp )
  set( MBKALEIDOSCOPE_LINK_LIBRARIES
    mb
  )
  common_application( mbKaleidoscope )

  set( MBCUBES_HEADERS )
  set( MBCUBES_SOURCES cubes.cpp )
  set( MBCUBES_LINK_LIBRARIES
    mb
  )
  common_application( mbCubes )

  set( MBQUASICRYSTAL_HEADERS )
  set( MBQUASICRYSTAL_SOURCES quasicrystal.cpp )
  set( MBQUASICRYSTAL_LINK_LIBRARIES
    mb
  )
  common_application( mbQuasicrystal )


  set( MBSCENEGRAPH_HEADERS )
  set( MBSCENEGRAPH_SOURCES sceneGraph.cpp )
  set( MBSCENEGRAPH_LINK_LIBRARIES
    mb
  )
  common_application( mbSceneGraph )




  ##set( MBCUBEHIERARCHY_HEADERS )
  ##set( MBCUBEHIERARCHY_SOURCES cubeHierarchy.cpp )
  ##set( MBCUBEHIERARCHY_LINK_LIBRARIES
  ##  mb
  ##)
  ##common_application( mbCubeHierarchy )


  ##set( MBBUFFERINSTANCING_HEADERS )
  ##set( MBBUFFERINSTANCING_SOURCES bufferInstancing.cpp )
  ##set( MBBUFFERINSTANCING_LINK_LIBRARIES
  ##  mb
  ##)
  ##common_application( mbBufferInstancing )


  ##set( MBSHADERSUBROUTINE_HEADERS )
  ##set( MBSHADERSUBROUTINE_SOURCES shaderSubroutine.cpp )
  ##set( MBSHADERSUBROUTINE_LINK_LIBRARIES
  ##  mb
  ##)
  ##common_application( mbShaderSubroutine )
endif()






##set( MBHEIGHTMAPEARTH_HEADERS )
##set( MBHEIGHTMAPEARTH_SOURCES heightmapEarth.cpp )
##set( MBHEIGHTMAPEARTH_LINK_LIBRARIES
##  mb
##)
##common_application( mbHeightmapEarth )





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
##set( MBNEWTONFRACTAL_HEADERS )
##set( MBNEWTONFRACTAL_SOURCES newtonFractal.cpp )
##set( MBNEWTONFRACTAL_LINK_LIBRARIES
##	mb
##)
##
##common_application( mbNewtonFractal )
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
