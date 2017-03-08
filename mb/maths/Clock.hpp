/*
* Copyright (c) 2016 maldicion069
*
* Authors: Cristian Rodríguez Bernal <ccrisrober@gmail.com>
*
* This file is part of MonkeyBrushPlusPlus <https://github.com/maldicion069/monkeybrushplusplus>
*
* This library is free software; you can redistribute it and/or modify it under
* the terms of the GNU Lesser General Public License version 3.0 as published
* by the Free Software Foundation.
*
* This library is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
* FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
* details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this library; if not, write to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*
*/

#ifndef __MB_CLOCK__
#define __MB_CLOCK__

#include <functional>
#include <mb/api.h>

namespace mb
{
	class Clock
	{
	public:
		MB_API
		Clock( void );
		MB_API
		explicit Clock( double deltaTime );
		MB_API
		Clock( const Clock &c );
		MB_API
		~Clock( void );
		MB_API
		Clock &operator=( const Clock &other );

		MB_API
		void reset( void );
		MB_API
		void tick( void );

		MB_API
		double getCurrentTime( void ) const
		{
			return _currentTime;
		}
		MB_API
		void setCurrentTime( double value )
		{
			_currentTime = value;
		}

		MB_API
		double getLastTime( void ) const
		{
			return _lastTime;
		}
		MB_API
		void setLastTime( double value )
		{
			_lastTime = value;
		}

		MB_API
		double getDeltaTime( void ) const {
			return _deltaTime;
		}
		MB_API
		void setDeltaTime( double value ) {
			_deltaTime = value;
		}
        
		MB_API
        double getAccumTime( void ) const {
        	return _accumTime;
        }
		MB_API
        void setAccumTime( double value ) {
        	_accumTime = value;
        }

	private:
		double _currentTime;
		double _lastTime;
		double _deltaTime;
        double _accumTime;

	public:
		typedef std::function< void( void ) > TimeoutCallback;
		//using TimeoutCallback = std::function< void( void ) >;
		MB_API
		void setTimeout( TimeoutCallback const &callback, 
			double timeout, bool repeat = false );

	private:
		TimeoutCallback _timeoutCallback;
		double _timeout;
		bool _repeat;

	public:
		/**
		   Ticks the clock by a fixed delta time
		   As a side effect, _accumTime gets incremented by the new
		   _deltaTime. Callbacks get executed if timeout is over
		 */
		MB_API
		Clock &operator+=( double delta );

		/**
		   Ticks the clock by another clock's delta time
		   As a side effect, _accumTime gets incremented by the new
		   _deltaTime. Callbacks get executed if timeout is over
		 */
		MB_API
		Clock &operator+=( const Clock &other );

	private:
		void onTick( void );
	};

}

#endif /* __MB_CLOCK__ */