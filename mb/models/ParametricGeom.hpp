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

#ifndef __MB_PARAMETRIC_GEOM__
#define __MB_PARAMETRIC_GEOM__

#include <mb/api.h>

#include "Drawable.hpp"
#include <functional>
#include <vector>
#include "../maths/Vect3.hpp"

namespace mb
{
    class ParametricGeom: public Drawable
    {
    public:
		MB_API
		ParametricGeom(const std::function<mb::Vect3(float, float)>& func, const float& slices, const float& stacks)
		{
			std::vector<Vect3> vertices;
			std::vector<float> normals;
			std::vector<float> uvs;
			std::vector<unsigned int> indices;

			Vect3 evalVect3;
			float u, v;
			unsigned int i, j;

			for (i = 0; i <= stacks; ++i)
			{
				v = (float) i / stacks;
				for (j = 0; j <= slices; ++j)
				{
					u = (float) j / slices;

					evalVect3 = func(u, v);
					vertices.push(evalVect3);
				}
			}

			unsigned int pA, pB, pC, pD;
			float uva, uvb, uvc, uvd;
            // TODO: UVs error :(
			for (i = 0; i < stacks; ++i)
			{
				for (j = 0; j < slices; ++j)
				{
					
				}
			}
		}
    };
}

#endif /* __MB_PARAMETRIC_GEOM__ */
