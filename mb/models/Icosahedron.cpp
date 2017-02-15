/*
 * Copyright (c) 2016 maldicion069
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

#include "Icosahedron.hpp"
#include <cmath>

namespace mb
{
	Icosahedron::Icosahedron(const float& radius, const unsigned int& subdivisions)
	: Polyhedron()
	{
		float t = (1.0f + std::sqrt(5.0f)) / 2.0f;

		std::vector<float> verts = {
			-1.0f,  t,  0.0f,
			 1.0f,  t,  0.0f,
			-1.0f, -t,  0.0f,
			 1.0f, -t,  0.0f,

			 0.0f, -1.0f,  t,
			 0.0f,  1.0f,  t,
			 0.0f, -1.0f, -t,
			 0.0f,  1.0f, -t,

			 t,  0.0f, -1.0f,
			 t,  0.0f,  1.0f,
			-t,  0.0f, -1.0f,
			-t,  0.0f,  1.0f
		};
		std::vector<unsigned int> el = {
			 0, 11,   5,
			 0,  5,   1,
			 0,  1,   7,
			 0,  7,  10,
			 0, 10,  11,
			 1,  5,   9,
			 5, 11,   4,
			11, 10,   2,
			10,  7,   6,
			 7,  1,   8,
			 3,  9,   4,
			 3,  4,   2,
			 3,  2,   6,
			 3,  6,   8,
			 3,  8,   9,
			 4,  9,   5,
			 2,  4,  11,
			 6,  2,  10,
			 8,  6,   7,
			 9,  8,   1
		};
		this->_createPolyhedron(verts, el, radius, subdivisions);
	}
}
