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

#include "Tetrahedron.hpp"

namespace mb
{
	Tetrahedron::Tetrahedron(const float& radius, const unsigned int& subdivisions)
	: Polyhedron()
	{
		std::vector<float> verts = {
			 1.0f,  1.0f,  1.0f,
      -1.0f, -1.0f,  1.0f,
      -1.0f,  1.0f, -1.0f,
       1.0f, -1.0f, -1.0f
		};
		std::vector<unsigned int> el = {
      2,  1,  0,
      0,  3,  2,
      1,  3,  0,
      2,  3,  1
		};
		this->create(verts, el, radius, subdivisions);
	}
}
