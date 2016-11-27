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

#include "Octahedron.hpp"
#include <cmath>

namespace mb
{
	Octahedron::Octahedron(const float& radius, const unsigned int& subdivisions)
	: Polyhedron()
	{
		float a = 1.0f / (2.0f * std::sqrt(2.0f));
        float b = 1.0f / 2.0f;

		std::vector<float> verts = {
               a,  0.0f,  0.0f,
              -a,  0.0f,  0.0f,
             0.0f,    b,  0.0f,
             0.0f,   -b,  0.0f,
             0.0f, 0.0f,   a,
             0.0f, 0.0f,  -a
		};
		std::vector<unsigned int> el = {
            0, 2, 4,
            0, 4, 3,
            0, 3, 5,
            0, 5, 2,
            1, 2, 5,
            1, 5, 3,
            1, 3, 4,
            1, 4, 2
		};
		this->create(verts, el, radius, subdivisions);
	}
}
