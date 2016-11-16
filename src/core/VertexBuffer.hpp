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

#ifndef __MB_VERTEXBUFFER__
#define __MB_VERTEXBUFFER__

#include <GL/glew.h>
#include <vector>

namespace MB
{
	class VertexBuffer
	{
	public:
		VertexBuffer(unsigned int type = GL_ARRAY_BUFFER);
		virtual ~VertexBuffer();
		void bind();
		void bufferSubData(int offset, std::vector<float> _data);
		void data(std::vector<float> _data, unsigned int usage = GL_STATIC_DRAW);
		std::vector<float> getSubData(int size, int offset = 0);
		void attribDivisor(int position, int length, int divisor, int stride = 0);
		void vertexAttribPointer(int attribLocation, int numElems,
			unsigned int type, bool normalized = false/*,
			unsigned int offset = 0*/);
		void render(unsigned int mode, unsigned int size);
		unsigned int getBufferType() const;
		unsigned int getBuffer() const;
		void unbind();
	protected:
		unsigned int _handler;
		unsigned int _type;
	};
}

#endif /* __MB_VERTEXBUFFER__ */