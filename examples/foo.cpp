#include <iostream>

namespace mb
{
	class RTTI
	{
	protected:
		RTTI( void ) { }

	public:
		virtual ~RTTI( void ) { }
		virtual const char *getClassName( void ) const = 0;
	};

}

#define MB_HEADER_RTTI(X)\
public:\
	static const const char* __CLASS_NAME__; \
	virtual const char *getClassName(void) const override { return __CLASS_NAME__; }
#define MB_CPP_RTTI(X)\
	const const char* Foo::__CLASS_NAME__ = #X;

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

	std::cout << "FOO" << std::endl;
	Foo foo;
	std::cout << foo.getClassName( ) << std::endl;
	return 0;
}