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

#include <vector>

class Uniforms
{
public:
  void operator <<( std::string name )
  {
    us.push_back( name );
  }
public:
  std::vector<std::string> us;
};


int main( )
{

	std::cout << "FOO" << std::endl;
	Foo foo;
	std::cout << foo.getClassName( ) << std::endl;

  std::vector<std::pair<const char*, mb::Uniform*> > uniforms = {
    std::make_pair( "projection", new mb::Uniform( mb::Matrix4 ) ),
    std::make_pair( "view", new mb::Uniform( mb::Matrix4 ) ),
    std::make_pair( "model", new mb::Uniform( mb::Matrix4 ) ),
    std::make_pair( "viewPos", new mb::Uniform( mb::Vector3 ) )
  };

  //INTEGRAR SOPORTE PARA UNIFORM LIST Y CONCATENAR <<

  mb::UniformsList ulist;
  ulist << std::make_pair( "projection", new mb::Uniform( mb::Matrix4 ) )
    << std::make_pair( "view", new mb::Uniform( mb::Matrix4 ) );
  ulist << std::make_pair( "model", new mb::Uniform( mb::Matrix4 ) );
  ulist << std::make_pair( "viewPos", new mb::Uniform( mb::Vector3 ) );

	return 0;
}
