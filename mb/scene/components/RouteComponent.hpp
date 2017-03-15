/*
 * Copyright (c) 2017 maldicion069
 *
 * Authors: Cristian Rodríguez Bernal <ccrisrober@gmail.com>
 *
 * This file is part of MonkeyBrushPlusPlus
 * <https://github.com/maldicion069/monkeybrushplusplus>
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

#ifndef __MB_ROUTE_COMPONENT__
#define __MB_ROUTE_COMPONENT__

#include <mb/api.h>

#include "Component.hpp"
#include "../../maths/Curves.hpp"

namespace mb
{

  class RouteComponent: public Component
  {
  public:
		MB_API
		RouteComponent( const std::vector< mb::Vect3>& waypoints, /*mb::Curves3D::CurveType type, */bool loop = false )
		: Component( )
		, _waypoints( waypoints )
		//, _type ( type )
		, _loop ( loop )
		, _next( 0 )
		{

		}
		MB_API
		mb::Vect3 nextWayPoint( void )
		{
			return _waypoints.at( next );
		}
		MB_API
		void AdvanceToNext( void )
		{
			unsigned int wsize = waypoints.size( );
			if ( _loop )
			{                
				_next = ( _next + 1 ) % wsize;
			}
			else
			{
				if ( _next != wsize - 1 )
				{
					++_next;
				}
			}
		}
		MB_API
		bool isLast( void )
		{
			return ( next == _waypoints.size( ) - 1 );
		}
		MB_SYNTHESIZE_WRITEONLY(mb::Curves3D::CurveType, _type, Type);
		MB_SYNTHESIZE_WRITEONLY(bool, _loop, Loop);
	protected:
		std::vector< mb::Vect3 > _waypoints;
		unsigned int _next;
  };
}

#endif /* __MB_ROUTE_COMPONENT__ */
