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

#include "PostProcess.hpp"

namespace mb
{
	PostProcess::PostProcess()
	{
		std::vector<float> positions = {
			-1.0f, -1.0f,
			+1.0f, -1.0f,
			-1.0f, +1.0f,
			+1.0f, +1.0f
		};
		_vao = new VertexArray();
		_vbo = new VertexBuffer(GL_ARRAY_BUFFER);
		_vbo->data(positions, GL_STATIC_DRAW);
		_vbo->vertexAttribPointer(0, 2, GL_FLOAT);
		_vao->unbind();
	}
	void PostProcess::bind()
	{
		_vao->bind();
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		_vao->unbind();
	}
}
