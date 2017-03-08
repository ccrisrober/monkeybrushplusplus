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

#include "Frustum.hpp"
#include "Mathf.hpp"

namespace mb
{
	Frustum::Frustum( void )
	{
	}
	Frustum::Frustum(
		float rMin, float rMax,
		float uMin, float uMax,
		float dMin, float dMax )
	{
		_data[ FRUSTUM_R_MIN ] = rMin;
		_data[ FRUSTUM_R_MAX ] = rMax;
		_data[ FRUSTUM_U_MIN ] = uMin;
		_data[ FRUSTUM_U_MAX ] = uMax;
		_data[ FRUSTUM_D_MIN ] = dMin;
		_data[ FRUSTUM_D_MAX ] = dMax;
	}
	Frustum::Frustum( float fov, float aspect, float near, float far )
	{
		float halfAngleRadians = Mathf::degToRad( 0.5f * fov );

		_data[ FRUSTUM_U_MAX ] = near * tan( halfAngleRadians );
		_data[ FRUSTUM_R_MAX ] = aspect * _data[ FRUSTUM_U_MAX ];
		_data[ FRUSTUM_U_MIN ] = -_data[ FRUSTUM_U_MAX ];
		_data[ FRUSTUM_R_MIN ] = -_data[ FRUSTUM_R_MAX ];
		_data[ FRUSTUM_D_MIN ] = near;
		_data[ FRUSTUM_D_MAX ] = far;
	}
	Frustum::Frustum( const Frustum &frustum )
	{
		memcmp( _data, frustum._data, 6 * sizeof( float ) );
	}
	Frustum::~Frustum( void )
	{
	}
}
