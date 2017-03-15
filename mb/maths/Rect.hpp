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

#ifndef __MB_RECT__
#define __MB_RECT__

#include <mb/api.h>

#include "Vect4.hpp"

namespace mb
{
	class Rect
	{
	public:
		MB_API
		Rect( void )
		: Rect( 1.0f, 1.0f, 1.0f, 1.0f )
		{
		}
		MB_API
		Rect(const float& x, const float& y, 
			const float& width, const float& height)
		: _data( mb::Vect4( x, y, width, height ) )
		{
		}
		MB_API
		Rect( const Rect &r )
		{
			*this = r;
		}
		Rect &operator=( const Rect &rect )
		{
			memcpy( _data, rect._data, 4 * sizeof( float ) );
			return *this;
		}
		float& x( void ) { return _data.x( ); }
		float& y( void ) { return _data.y( ); }
		float& width( void ) { return _data.z( ); }
		float& height( void ) { return _data.w( ); }

		float x( void ) const { return _data.x( ); }
		float y( void ) const { return _data.y( ); }
		float width( void ) const { return _data.z( ); }
		float height( void ) const { return _data.w( ); }
		mb::Vect2 getCenter( void ) const
        {
            return mb::Vect2(
            	x() + 0.5 * width(),
            	y() + 0.5 * height()
        	);
        }
	protected:
		Vect4 _data;
	};
}

#endif /* __MB_RECT__ */
