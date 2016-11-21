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

#ifndef __MB_CUBE__
#define __MB_CUBE__

#include <mb/api.h>

#include "Drawable.hpp"

namespace MB
{
    class Cube: public Drawable
    {
    public:
        MB_API
        Cube(float side = 1.0f)
        : Drawable()
        {
            float side2 = side / 2.0f;
            // Vertices
			std::vector<float> vertices = {
                // Front
                -side2, -side2, side2,
                side2, -side2, side2,
                side2,  side2, side2,
                -side2,  side2, side2,
                // Right
                side2, -side2, side2,
                side2, -side2, -side2,
                side2,  side2, -side2,
                side2,  side2, side2,
                // Back
                -side2, -side2, -side2,
                -side2,  side2, -side2,
                side2,  side2, -side2,
                side2, -side2, -side2,
                // Left
                -side2, -side2, side2,
                -side2,  side2, side2,
                -side2,  side2, -side2,
                -side2, -side2, -side2,
                // Bottom
                -side2, -side2, side2,
                -side2, -side2, -side2,
                side2, -side2, -side2,
                side2, -side2, side2,
                // Top
                -side2,  side2, side2,
                side2,  side2, side2,
                side2,  side2, -side2,
                -side2,  side2, -side2
            };
            // Normals
            std::vector<float> normals = {
                // Front
                0.0, 0.0, 1.0,
                0.0, 0.0, 1.0,
                0.0, 0.0, 1.0,
                0.0, 0.0, 1.0,
                // Right
                1.0, 0.0, 0.0,
                1.0, 0.0, 0.0,
                1.0, 0.0, 0.0,
                1.0, 0.0, 0.0,
                // Back
                0.0, 0.0, -1.0,
                0.0, 0.0, -1.0,
                0.0, 0.0, -1.0,
                0.0, 0.0, -1.0,
                // Left
                -1.0, 0.0, 0.0,
                -1.0, 0.0, 0.0,
                -1.0, 0.0, 0.0,
                -1.0, 0.0, 0.0,
                // Bottom
                0.0, -1.0, 0.0,
                0.0, -1.0, 0.0,
                0.0, -1.0, 0.0,
                0.0, -1.0, 0.0,
                // Top
                0.0, 1.0, 0.0,
                0.0, 1.0, 0.0,
                0.0, 1.0, 0.0,
                0.0, 1.0, 0.0
            };
            // TexCoords
            std::vector<float> texCoords = {
                // Front
                0.0, 0.0,
                1.0, 0.0,
                1.0, 1.0,
                0.0, 1.0,
                // Right
                0.0, 0.0,
                1.0, 0.0,
                1.0, 1.0,
                0.0, 1.0,
                // Back
                0.0, 0.0,
                1.0, 0.0,
                1.0, 1.0,
                0.0, 1.0,
                // Left
                0.0, 0.0,
                1.0, 0.0,
                1.0, 1.0,
                0.0, 1.0,
                // Bottom
                0.0, 0.0,
                1.0, 0.0,
                1.0, 1.0,
                0.0, 1.0,
                // Top
                0.0, 0.0,
                1.0, 0.0,
                1.0, 1.0,
                0.0, 1.0
            };
            // TexCoords
            std::vector<unsigned int> indices = {
                0, 1, 2, 0, 2, 3,
                4, 5, 6, 4, 6, 7,
                8, 9, 10, 8, 10, 11,
                12, 13, 14, 12, 14, 15,
                16, 17, 18, 16, 18, 19,
                20, 21, 22, 20, 22, 23
            };

            _vao = new VertexArray();
			_vao->bind();

				addBufferArray(0, vertices, 3, GL_STATIC_DRAW);
				addBufferArray(1, normals, 3, GL_STATIC_DRAW);
				addBufferArray(2, texCoords, 2, GL_STATIC_DRAW);
				std::vector<unsigned int> data = indices;
				unsigned int type = GL_STATIC_DRAW;
				//addElementArray(data, type);

				VertexBuffer vbIndices(GL_ELEMENT_ARRAY_BUFFER);
				vbIndices.data(data, type);
				_indicesLen = data.size();
				this->_handle.push_back(vbIndices);

            _vao->unbind();
        }
    };
}

#endif /* __MB_CUBE__ */
