#include "mbTests.h"
#include <mb/mb.h>

BOOST_AUTO_TEST_CASE( test_example )
{
	BOOST_CHECK((1 + 1) == 2);
}

BOOST_AUTO_TEST_CASE ( test_cube_indices_len )
{
    // mb::GLContext context(3, 3, 1024, 768, "Hello mb");
	// mb::Cube* cube = new mb::Cube(1.0f);
	// BOOST_CHECK(cube->indicesLen( ) == (6 * 6));
}

BOOST_AUTO_TEST_CASE ( test_lights_repeated )
{
	/*mb::GLContext context(4, 3, 1024, 768, "Hello MB");

	auto engine = std::make_shared<mb::Engine>(&context);
  	auto scene = std::make_shared<mb::Scene>(engine,
    new mb::SimpleCamera(mb::Vect3(0.2f, 0.18f, 8.44f)));

	mb::Light* l1 = new mb::PointLight();
	scene->addLight(l1);
	BOOST_CHECK(scene->lights().size() == 1);
	scene->addLight(l1);
	BOOST_CHECK(scene->lights().size() == 1);
	mb::Light* l2 = new mb::PointLight();
	scene->addLight(l2);
	BOOST_CHECK(scene->lights().size() == 2);
	scene->addLight(l1);
	BOOST_CHECK(scene->lights().size() == 2);*/
}
