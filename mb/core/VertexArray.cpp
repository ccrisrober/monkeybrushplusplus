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

#include "VertexArray.hpp"

namespace mb
{
	VertexArray::VertexArray()
	: _handler(0)
	{
		glCreateVertexArrays(1, &this->_handler);
		this->bind();
	}
	VertexArray::VertexArray(unsigned int handler_)
	: _handler(handler_)
	{
		this->bind();
	}
	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &this->_handler);
		this->_handler = 0;
	}
	void VertexArray::bind()
	{
		glBindVertexArray(this->_handler);
	}
	void VertexArray::unbind()
	{
		glBindVertexArray(0);
	}
}