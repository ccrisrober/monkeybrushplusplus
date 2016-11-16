/*
 * Copyright (c) 2016 maldicion069
 *
 * Authors: Cristian Rodríguez Bernal
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

#ifndef __MB_DRAWABLE__
#define __MB_DRAWABLE__

#include "../core/VertexArray.hpp"
#include "../core/VertexBuffer.hpp"

namespace MB
{
	class Drawable
	{
	public:
		Drawable(float side = 1.0f)
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
			_handle.resize(4);
			addElementArray(indices);

			addBufferArray(0, vertices, 3);
			addBufferArray(1, normals, 3);
			addBufferArray(2, texCoords, 2);
		}
		void render()
		{
			this->_vao.bind();
			glDrawElements(GL_TRIANGLES, _indicesLen, GL_UNSIGNED_SHORT, 0);
			this->_vao.unbind();
		}
	protected:
		void addBufferArray(unsigned int attribLocation, const std::vector<float>& data, 
			unsigned int numElems, unsigned int type = GL_STATIC_DRAW)
		{
			VertexBuffer vb(GL_ARRAY_BUFFER);
			vb.data(data, type);
			this->_handle.push_back(vb);
		}
		void addElementArray(const std::vector<unsigned int>& data, 
			unsigned int type = GL_STATIC_DRAW)
		{
			_indicesLen = data.size();
			VertexBuffer vb(GL_ELEMENT_ARRAY_BUFFER);
			vb.data(data, type);
			this->_handle.push_back(vb);
		}
		unsigned int _indicesLen;
		std::vector<VertexBuffer> _handle;
		VertexArray _vao;
	};
}

#endif /* __MB_DRAWABLE__ */