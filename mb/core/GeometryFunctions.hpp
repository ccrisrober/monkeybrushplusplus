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

#ifndef __MB_GEOMETRY_FUNCTIONS__
#define __MB_GEOMETRY_FUNCTIONS__

#include "../maths/Vect3.hpp"

namespace MB
{
	namespace GeometryFunctions
	{
		Vect3 triangleCentroid(const Vect3& v1,
			const Vect3& v2, const Vect3& v3)
		{
			float
				t0 = v1.x(),
				t1 = v2.x(),
				t2 = v3.x();
			float x = (t0 + t1 + t2) / 3.0f;
			t0 = v1.y();
			t1 = v2.y();
			t2 = v3.y();
			float y = (t0 + t1 + t2) / 3.0f;
			t0 = v1.z(),
			t1 = v2.z();
			t2 = v3.z();
			float z = (t0 + t1 + t2) / 3.0f;
			
			return Vect3(x, y, z);
		}
	};
}

#endif /* __MB_GEOMETRY_FUNCTIONS__ */
