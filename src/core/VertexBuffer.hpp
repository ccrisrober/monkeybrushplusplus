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

namespace MB {
	class VertexBuffer {
	public:
		VertexBuffer(unsigned int type)
		{
			// TODO: TYPE Default array_mode
		}
		virtual ~VertexBuffer()
		{
			this->unbind();
			if (this->_handler > 0) 
				glDeleteTextures(1, &this->_handler);
			this->_handler = 0;
		}
		void bind()
		{
			glBindBuffer(this->_type, this->_handler);
		}
		void bufferSubData(int offset, std::vector<float> _data)
		{
			this->bind();
			glBufferSubData(this->_type, offset, _data.size(), _data.data());
		}
		void data(std::vector<float> _data, unsigned int usage = GL_STATIC_DRAW)
		{
			this->bind();
			glBufferData(this->_type, _data.size(), _data.data(), usage);
		}
		std::vector<float> getSubData(int size, int offset = 0)
		{
			this->bind();
			std::vector<float> arrBuffer(size);
			glGetBufferSubData(this->_type, 0, size * sizeof(float), &arrBuffer[0]);
			return arrBuffer;
		}
		void attribDivisor(int position, int length, int divisor, int stride = 0)
		{
			this->bind();
			glEnableVertexAttribArray(position);
			glVertexAttribPointer(position, length, GL_FLOAT, false, length * sizeof(float), 0);
			glVertexAttribDivisor(position, divisor);
		}
		void vertexAttribPointer(int attribLocation, int numElems, 
			unsigned int type, bool normalized = false/*, 
			unsigned int offset = 0*/) {
			this->bind();
			glEnableVertexAttribArray(attribLocation);
			glVertexAttribPointer(
				attribLocation, // Attribute location
				numElems, // Number of elements per attribute
				type, // Type of elements
				normalized,
				numElems * sizeof(float), // Size of an individual vertex
				0 // Offset from the beginning of a single vertex to this attribute
			);
		}
		void render(unsigned int mode, unsigned int size)
		{
			glDrawArrays(mode, 0, size);
		}
		unsigned int getBufferType() const {
			return this->_type;
		}
		unsigned int getBuffer() const {
			return this->_handler;
		}
		void unbind()
		{
			glBindBuffer(this->_type, 0);
		}
	protected:
		unsigned int _handler;
		unsigned int _type;
	};
}

#endif /* __MB_VERTEXBUFFER__ */