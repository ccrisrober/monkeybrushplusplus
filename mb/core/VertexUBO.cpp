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

#include "VertexUBO.hpp"

namespace mb
{
	VertexUBO::VertexUBO(const Program& prog, const char* name, 
		unsigned int blockBindIdx)
		: _index(blockBindIdx)
		, _name(name)
	{
		glCreateBuffers(1, &_handler);
		unsigned int p = prog.program();
		auto index = glGetUniformBlockIndex(p, name);
		glUniformBlockBinding(p, index, blockBindIdx);
	}
	VertexUBO::~VertexUBO()
	{
		glDeleteBuffers(1, &_handler);
	}
	void VertexUBO::bind()
	{
		glBindBuffer(GL_UNIFORM_BUFFER, this->_handler);
	}
	void VertexUBO::update(const std::vector<float>& data)
	{
		this->bind();
		glBufferData(GL_UNIFORM_BUFFER, data.size() * sizeof(GL_FLOAT), &data[0], GL_STATIC_DRAW);
		this->unbind();
		glBindBufferBase(GL_UNIFORM_BUFFER, _index, _handler);
	}
	void VertexUBO::unbind()
	{
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}
