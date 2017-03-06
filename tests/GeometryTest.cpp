#include "mbTests.h"
#include <mb/mb.h>

BOOST_AUTO_TEST_CASE( test_geometry_material )
{
	const char* name = "GeomNode";
	auto mesh = mb::Cube::create( 1.0f );
	auto material = mb::SimpleShadingMaterial::create( );
	auto node = mb::Node::create( std::string( name ) );
	auto meshRenderer = mb::MeshRenderer::create( mesh, material );

	BOOST_CHECK_IS_NULL( node->getComponent<MeshRenderer>( ) );
	BOOST_CHECK_EQUAL( node->getName( ), name );
	BOOST_CHECK_FALSE( node->hasComponent<MeshRenderer>( ) );
	node->addComponent( meshRenderer );
	BOOST_CHECK_TRUE( node->hasComponent<MeshRenderer>( ) );
	BOOST_CHECK_EQUAL( node->getComponent<MeshRenderer>( ), meshRenderer );
}