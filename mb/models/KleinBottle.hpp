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

#ifndef __MB_KLEIN_BOTTLE__
#define __MB_KLEIN_BOTTLE__

#include <mb/api.h>

#include "ParametricGeom.hpp"

namespace mb
{
	class KleinBottle : public ParametricGeom
	{
	public:
		MB_API
		KleinBottle( const unsigned int& slices, const unsigned int& stacks )
		: ParametricGeom( KleinBottle::parametricFunction, slices, stacks)
		{

		}
	protected:
		static mb::Vect3 parametricFunction( float u_, float v_ )
		{
			float v = 1.0f - u_;
			float u = v_;
		    float x0 = 3.0f * cos( u ) * ( 1.0f + sin( u ) ) + ( 2.0f * ( 1.0f - cos( u ) / 2.0f ) ) * cos( u ) * cos( v );
		    float y0 = 8.0f * sin( u ) + ( 2.0f * ( 1.0f - cos( u ) / 2.0f ) ) * sin( u ) * cos( v );
		    float x1 = 3.0f * cos( u ) * ( 1.0f + sin( u ) ) + ( 2.0f * ( 1.0f - cos( u ) / 2.0f ) ) * cos( v + Mathf::PI );
		    float y1 = 8.0f * sin( u );

		    mb::Vect3 res(
		    	( u < Mathf::PI ?  x0 :  x1),// * _scale,
		    	( u < Mathf::PI ? -y0 : -y1),// * _scale,
		    	( -2.0f * ( 1.0f - cos( u ) / 2.0f ) ) * sin( v )// * _scale
	    	);
	    	return res;
		}
	};
}

#endif /* __MB_KLEIN_BOTTLE__ */
