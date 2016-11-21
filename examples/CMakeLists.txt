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
