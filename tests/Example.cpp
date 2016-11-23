#include "mbTests.h"
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

BOOST_AUTO_TEST_CASE ( test_lights_repeated )
{
	MB::GLContext context(3, 3, 1024, 768, "Hello MB");

	auto scene = new MB::Scene();

	MB::Light* l1 = new MB::PointLight();
	scene->addLight(l1);
	BOOST_CHECK(scene->lights().size() == 1);
	scene->addLight(l1);
	BOOST_CHECK(scene->lights().size() == 1);
	MB::Light* l2 = new MB::PointLight();
	scene->addLight(l2);
	BOOST_CHECK(scene->lights().size() == 2);
	scene->addLight(l1);
	BOOST_CHECK(scene->lights().size() == 2);
}