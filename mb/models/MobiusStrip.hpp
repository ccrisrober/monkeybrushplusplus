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

#ifndef __MB_MOBIUS_STRIP__
#define __MB_MOBIUS_STRIP__

#include <mb/api.h>

#include "ParametricGeom.hpp"

namespace mb
{
	class MobiusStrip : public ParametricGeom
	{
	public:
		MB_API
		MobiusStrip( const unsigned int& slices, const unsigned int& stacks )
		: ParametricGeom( MobiusStrip::parametricFunction, slices, stacks)
		{

		}
	protected:
		static mb::Vect3 parametricFunction( float u, float v )
		{
			float major = 1.25f;
		    float a = 0.125f;
		    float b = 0.5f;
		    float phi = u / 2.0f;
		    
		    // general equation for an ellipse where phi is the angle
		    // between the major axis and the x axis
		    float x = a * cos( v ) * cos( phi ) - b * sin( v ) * sin( phi );
		    float y = a * cos( v ) * sin( phi ) + b * sin( v ) * cos( phi );

		    mb::Vect3 res(
		    	( major + x ) * cos( u ),// * _scale,
		    	( major + x ) * sin( u ),// * _scale,
		    	y// * _scale
	    	);
	    	return res;
		}
	};
}

#endif /* __MB_MOBIUS_STRIP__ */
