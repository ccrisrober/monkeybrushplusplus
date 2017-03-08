#include "mbTests.h"
#include <mb/mb.h>

BOOST_AUTO_TEST_CASE( test_clock_construction )
{
	Clock clock;
	BOOST_CHECK_EQUAL( clock.getDeltaTime( ), 0.0 );
	BOOST_CHECK_EQUAL( clock.getAccumTime( ), 0.0 );
}

BOOST_AUTO_TEST_CASE( test_clock_construction_with_delta )
{
	Clock clock ( 0.8 );
	BOOST_CHECK_EQUAL( clock.getDeltaTime( ), 0.8 );
	BOOST_CHECK_EQUAL( clock.getAccumTime( ), 0.0 );
}

BOOST_AUTO_TEST_CASE( test_clock_add )
{
	Clock c1;
	Clock c2( 0.5 );
	BOOST_CHECK_EQUAL( c1.getDeltaTime( ), 0.0 );
	BOOST_CHECK_EQUAL( c1.getAccumTime( ), 0.0 );
	BOOST_CHECK_EQUAL( c1.getDeltaTime( ), 0.5 );
	BOOST_CHECK_EQUAL( c1.getAccumTime( ), 0.0 );

	c1 += c2;
	BOOST_CHECK_EQUAL( c1.getDeltaTime( ), 0.5 );
	BOOST_CHECK_EQUAL( c1.getAccumTime( ), 0.5 );

}

BOOST_AUTO_TEST_CASE( test_clock_tick_example )
{
	Clock clock;
	BOOST_CHECK_EQUAL( clock.getDeltaTime( ), 0.0 );
	BOOST_CHECK_EQUAL( clock.getAccumTime( ), 0.0 );

	std::this_thread::sleep_for( std::chrono::milliseconds( 20 ) );
	clock.tick( );
	BOOST_CHECK( 0.020 < c.getDeltaTime( ) );
	BOOST_CHECK( 0.020 < c.getAccumTime( ) );

	std::this_thread::sleep_for( std::chrono::milliseconds( 20 ) );
	clock.tick( );
	BOOST_CHECK( 0.020 < c.getDeltaTime( ) );
	BOOST_CHECK( 0.040 < c.getAccumTime( ) );
}