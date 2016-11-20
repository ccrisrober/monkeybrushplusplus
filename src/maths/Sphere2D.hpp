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

#ifndef __MB_SPHERE2D__
#define __MB_SPHERE2D__

#include "Vect2.hpp"

namespace MB
{
	class Sphere2D
	{
	public:
		Sphere2D(const Vect2& center, const float& radius);
		bool containtsPoint(const Vect2& p);
		bool intersectsSphere(const Sphere2D& s);
	protected:
		Vect2 _center;
		float _radius;
	};
}

#endif /* __MB_SPHERE2D__ */
