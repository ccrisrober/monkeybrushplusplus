include_directories( ${CMAKE_BINARY_DIR}/include )
include_directories( ${PROJECT_SOURCE_DIR} )

if(BOOST_FOUND)
	set(TEST_LIBRARIES
		${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
		MB
	)
	include(CommonCTest)
endif()