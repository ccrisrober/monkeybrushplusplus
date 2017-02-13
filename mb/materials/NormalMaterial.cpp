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

#include "NormalMaterial.hpp"

namespace mb
{
  NormalMaterial::NormalMaterial()
  : Material()
  {
    _uniforms["projection"] = new Uniform(Matrix4);
    _uniforms["view"] = new Uniform(Matrix4);
    _uniforms["model"] = new Uniform(Matrix4);

    const char* vsShader =
    R"(#version 330
      layout(location = 0) in vec3 position;
      layout(location = 1) in vec3 normal;
      out vec3 outNormal;
      uniform mat4 projection;
      uniform mat4 view;
      uniform mat4 model;
      void main()
      {
        mat3 normalMatrix = mat3(inverse(transpose(view * model)));
        outNormal = normalize(normalMatrix * normal);
        gl_Position = projection * view * model * vec4(position, 1.0);
      })";
		const char* fsShader =
    R"(#version 330
			in vec3 outNormal;
			out vec4 fragColor;
			void main()
      {
			  fragColor = vec4(normalize(outNormal), 1.0);
			})";
    _program->loadFromText(vsShader, fsShader);
		_program->compileAndLink();
		_program->autocatching();
  }
}
