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

#include "PostProcessMaterial.hpp"

namespace mb
{
	PostProcessMaterial::PostProcessMaterial(const char* fsShader_)
		: Material()
	{
		const char* vsShader =
      R"(#version 330
			layout(location = 0) in vec3 vertPosition;
			out vec2 uv;
			void main(void)
      {
			  uv = vec2(vertPosition.xy * 0.5) + vec2(0.5);
			  gl_Position = vec4(vertPosition, 1.0);
			})";
		const char* fsShader;
		if (fsShader_)
		{
			fsShader = fsShader_;
		}
		else
		{
			fsShader =
				R"(#version 330
				uniform vec3 color;
				out vec4 fragColor;
				in vec2 uv;
				void main()
				{
			    fragColor = vec4(uv, 0.0, 1.0);
				})";
		}

		_program->loadFromText(vsShader, fsShader);
		_program->compileAndLink();
		_program->autocatching();

		_pp = new PostProcess();
	}
	void PostProcessMaterial::renderPP()
	{
		this->use();
		this->_pp->bind();
	}
}
