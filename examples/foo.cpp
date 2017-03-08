#include <iostream>

#include <mb/mb.h>

#define MB_HEADER_RTTI(X)\
public:\
	static const char* __CLASS_NAME__; \
	virtual const char *getClassName(void) const override { return __CLASS_NAME__; }
#define MB_CPP_RTTI(X)\
	const char* Foo::__CLASS_NAME__ = #X;

namespace mb
{
	class Foo : public RTTI
	{
		MB_HEADER_RTTI(mb::Foo)
	};
	MB_CPP_RTTI(mb::Foo)
}

#include <vector>

using namespace mb;

int main( )
{
	std::vector<int> v;
	v.empty();

  const char* name = "GeomNode";
  mb::DrawablePtr mesh = std::make_shared<mb::Cube>( 5.0f );
  mb::SimpleShadingMaterialPtr material = mb::SimpleShadingMaterial::create( );
  mb::NodePtr node = mb::Node::create( std::string( name ) );
  auto meshRenderer = mb::MeshRenderer::create( mesh, material );

  /*BOOST_CHECK_IS_NULL( node->getComponent<MeshRenderer>( ) );
  BOOST_CHECK_EQUAL( node->getName( ), name );
  BOOST_CHECK_FALSE( node->hasComponent<MeshRenderer>( ) );*/
  node->addComponent( meshRenderer );
  /*BOOST_CHECK_TRUE( node->hasComponent<MeshRenderer>( ) );
  BOOST_CHECK_EQUAL( node->getComponent<MeshRenderer>( ), meshRenderer );*/

	std::cout << "FOO" << std::endl;
	Foo foo;
	std::cout << foo.getClassName( ) << std::endl;
	return 0;
}
