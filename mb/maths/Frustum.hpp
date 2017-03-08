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

#ifndef __MB_FRUSTUM__
#define __MB_FRUSTUM__

#include <mb/api.h>
#include "Mat4.hpp"

#include <string.h>

namespace mb
{
	class Frustum
	{
	private:
		enum {
			FRUSTUM_R_MIN = 0,
			FRUSTUM_R_MAX = 1,
			FRUSTUM_U_MIN = 2,
			FRUSTUM_U_MAX = 3,
			FRUSTUM_D_MIN = 4,
			FRUSTUM_D_MAX = 5,
		};
	public:
		MB_API
		Frustum( void );
		MB_API
		Frustum(
			float rMin, float rMax,
			float uMin, float uMax,
			float dMin, float dMax );
		MB_API
		Frustum( float fov, float aspect, float near, float far );
		MB_API
		Frustum( const Frustum &f );
		MB_API
		virtual ~Frustum( void );
		MB_API
		bool operator==( const Frustum &frustum ) const
		{
			return memcmp( _data, frustum._data, 6 * sizeof( float ) ) == 0;
		}
		MB_API
		bool operator!=( const Frustum &frustum ) const
		{
			return memcmp( _data, frustum._data, 6 * sizeof( float ) );
		}
		MB_API
		float getRMin( void ) const { return _data[ FRUSTUM_R_MIN ]; }
		MB_API
		float getRMax( void ) const { return _data[ FRUSTUM_R_MAX ]; }
		MB_API
		float getUMin( void ) const { return _data[ FRUSTUM_U_MIN ]; }
		MB_API
		float getUMax( void ) const { return _data[ FRUSTUM_U_MAX ]; }
		MB_API
		float getDMin( void ) const { return _data[ FRUSTUM_D_MIN ]; }
		MB_API
		float getDMax( void ) const { return _data[ FRUSTUM_D_MAX ]; }

		MB_API
    float computeFOV( void ) const
    {
      return getUMax() / getDMin();
    }

		MB_API
		float computeAspect( void ) const
		{
			return getRMax() / getUMax();
		}

		MB_API
    float computeLinearDepth( void ) const
    {
      return getDMax() - getDMin();
    }

		MB_API
		mb::Mat4 computeProjectionMatrix( void ) const
		{
      float n = getDMin();
      float f = getDMax();
      float r = getRMax();
      float l = getRMin();
      float t = getUMax();
      float b = getUMin();

      std::vector<float> projMatrix(16);
      projMatrix[ 0 ] = 2.0f * n / ( r - l );
      projMatrix[ 1 ] = 0.0f;
      projMatrix[ 2 ] = 0.0f;
      projMatrix[ 3 ] = 0.0f;

      projMatrix[ 4 ] = 0.0f;
      projMatrix[ 5 ] = 2.0f * n / ( t - b );
      projMatrix[ 6 ] = 0.0f;
      projMatrix[ 7 ] = 0.0f;

      projMatrix[ 8 ] = ( r + l ) / ( r - l );
      projMatrix[ 9 ] = ( t + b ) / ( t - b );
      projMatrix[ 10 ] = -( f + n ) / ( f - n );
      projMatrix[ 11 ] = -1.0f;

      projMatrix[ 12 ] = 0.0f;
      projMatrix[ 13 ] = 0.0f;
      projMatrix[ 14 ] = -( 2.0f * f * n ) / ( f - n );
      projMatrix[ 15 ] = 0.0f;

			return mb::Mat4(projMatrix);
		}

		MB_API
		mb::Mat4 computeOrthographicMatrix(void) const
    {
      float near = getDMin();
      float far = getDMax();
      float fov = getRMax() / getUMax();
			float right = fov;
			float left = -fov;
			float top = 1.0f;
			float bottom = -1.0f;

			std::vector<float> ortoMatrix(16);
      ortoMatrix[ 0 ] = ( 2.0f / ( right - left ) );
      ortoMatrix[ 1 ] = 0.0f;
      ortoMatrix[ 2 ] = 0.0f;
      ortoMatrix[ 3 ] = -( right + left ) / ( right - left );

      ortoMatrix[ 4 ] = 0.0f;
      ortoMatrix[ 5 ] = ( 2.0f / ( top - bottom ) );
      ortoMatrix[ 6 ] = - ( top + bottom ) / ( top - bottom );
      ortoMatrix[ 7 ] = 0.0f;

      ortoMatrix[ 8 ] = 0.0f;
      ortoMatrix[ 9 ] = 0.0f;
      ortoMatrix[ 10 ] = ( -2.0f / ( far - near ) );
      ortoMatrix[ 11 ] = ( far + near ) / ( far - near );

      ortoMatrix[ 12 ] = 0.0f;
      ortoMatrix[ 13 ] = 0.0f;
      ortoMatrix[ 14 ] = 0.0f;
      ortoMatrix[ 15 ] = 1.0f;

			return mb::Mat4( ortoMatrix );
		}
	private:
		float _data[ 6 ];
	};
}

#endif /* __MB_FRUSTUM__ */
