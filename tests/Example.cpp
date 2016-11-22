#include "mbTests.h"
// #include "../src/core/GLContext.hpp"
// #include "../src/models/Cube.hpp"
#include <mb/mb.h>

BOOST_AUTO_TEST_CASE( test_example )
{
	BOOST_CHECK((1 + 1) == 2);
}

BOOST_AUTO_TEST_CASE ( test_cube_indices_len )
{
    // MB::GLContext context(3, 3, 1024, 768, "Hello MB");
	// MB::Cube* cube = new MB::Cube(1.0f);
	// BOOST_CHECK(cube->indicesLen( ) == (6 * 6));
}