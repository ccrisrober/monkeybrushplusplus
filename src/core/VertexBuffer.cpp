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

#include "VertexBuffer.hpp"

namespace MB
{
	VertexBuffer::VertexBuffer(unsigned int type)
	{
		// TODO: TYPE Default array_mode
	}
	VertexBuffer::~VertexBuffer()
	{
		this->unbind();
		if (this->_handler > 0)
			glDeleteTextures(1, &this->_handler);
		this->_handler = 0;
	}
	void VertexBuffer::bind()
	{
		glBindBuffer(this->_type, this->_handler);
	}
	void VertexBuffer::bufferSubData(int offset, std::vector<float> _data)
	{
		this->bind();
		glBufferSubData(this->_type, offset, _data.size(), _data.data());
	}
	void VertexBuffer::data(std::vector<float> _data, unsigned int usage)
	{
		this->bind();
		glBufferData(this->_type, _data.size(), _data.data(), usage);
	}
	std::vector<float> VertexBuffer::getSubData(int size, int offset)
	{
		this->bind();
		std::vector<float> arrBuffer(size);
		glGetBufferSubData(this->_type, 0, size * sizeof(float), &arrBuffer[0]);
		return arrBuffer;
	}
	void VertexBuffer::attribDivisor(int position, int length, int divisor, int stride)
	{
		this->bind();
		glEnableVertexAttribArray(position);
		glVertexAttribPointer(position, length, GL_FLOAT, false, length * sizeof(float), 0);
		glVertexAttribDivisor(position, divisor);
	}
	void VertexBuffer::vertexAttribPointer(int attribLocation, int numElems,
		unsigned int type, bool normalized/*,
												  unsigned int offset = 0*/)
	{
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
	void VertexBuffer::render(unsigned int mode, unsigned int size)
	{
		glDrawArrays(mode, 0, size);
	}
	unsigned int VertexBuffer::getBufferType() const
	{
		return this->_type;
	}
	unsigned int VertexBuffer::getBuffer() const
	{
		return this->_handler;
	}
	void VertexBuffer::unbind()
	{
		glBindBuffer(this->_type, 0);
	}
}