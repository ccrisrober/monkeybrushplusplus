#include "mbTests.h"
#include <mb/mb.h>

BOOST_AUTO_TEST_CASE( test_clock_construction )
{
	mb::Clock clock;
	BOOST_CHECK_EQUAL( clock.getDeltaTime( ), 0.0 );
	BOOST_CHECK_EQUAL( clock.getAccumTime( ), 0.0 );
}

BOOST_AUTO_TEST_CASE( test_clock_construction_with_delta )
{
	mb::Clock clock ( 0.8 );
	BOOST_CHECK_EQUAL( clock.getDeltaTime( ), 0.8 );
	BOOST_CHECK_EQUAL( clock.getAccumTime( ), 0.0 );
}
/*
BOOST_AUTO_TEST_CASE( test_clock_add )
{
	mb::Clock c1;
	mb::Clock c2( 0.5 );
	BOOST_CHECK_EQUAL( c1.getDeltaTime( ), 0.0 );
	BOOST_CHECK_EQUAL( c1.getAccumTime( ), 0.0 );
	BOOST_CHECK_EQUAL( c1.getDeltaTime( ), 0.5 );
	BOOST_CHECK_EQUAL( c1.getAccumTime( ), 0.0 );

	c1 += c2;
	BOOST_CHECK_EQUAL( c1.getDeltaTime( ), 0.5 );
	BOOST_CHECK_EQUAL( c1.getAccumTime( ), 0.5 );

}
*/
BOOST_AUTO_TEST_CASE( test_clock_tick_example )
{
	mb::Clock clock;
	BOOST_CHECK_EQUAL( clock.getDeltaTime( ), 0.0 );
	BOOST_CHECK_EQUAL( clock.getAccumTime( ), 0.0 );

	/*std::this_thread::sleep_for( std::chrono::milliseconds( 20 ) );
	clock.tick( );
	BOOST_CHECK( 0.020 < clock.getDeltaTime( ) );
	BOOST_CHECK( 0.020 < clock.getAccumTime( ) );

	std::this_thread::sleep_for( std::chrono::milliseconds( 20 ) );
	clock.tick( );
	BOOST_CHECK( 0.020 < clock.getDeltaTime( ) );
	BOOST_CHECK( 0.040 < clock.getAccumTime( ) );*/
}

