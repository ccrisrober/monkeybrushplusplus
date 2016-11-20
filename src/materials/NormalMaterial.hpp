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

#ifndef __MB_NORMAL_MATERIAL__
#define __MB_NORMAL_MATERIAL__

#include "Material.hpp"
#include "Uniform.hpp"

namespace MB
{
    class NormalMaterial: public Material
    {
    public:
        NormalMaterial()
        : Material()
        {
            _uniforms["projection"] = new Uniform(Matrix4);
            _uniforms["view"] = new Uniform(Matrix4);
            _uniforms["model"] = new Uniform(Matrix4);
			_uniforms["color"] = new Uniform(Vector3, Vect3(1.0f, 1.0f, 1.0f));		// TODO: UNUSED (REMOVE!)
			_uniforms["viewPos"] = new Uniform(Vector3);							// TODO: UNUSED (REMOVE!)

			const char* vsShader = "#version 330\n"
				"layout(location = 0) in vec3 position;"
				"layout(location = 1) in vec3 normal;"
				"out vec3 outNormal;"
				"uniform mat4 projection;"
				"uniform mat4 view;"
				"uniform mat4 model;"
				"void main() {"
                "    mat3 normalMatrix = mat3(inverse(transpose(view * model)));"
                "    outNormal = normalize(normalMatrix * normal);"
                "    gl_Position = projection * view * model * vec4(position, 1.0);"
				"}";
			const char* fsShader = "#version 330\n"
				"in vec3 outNormal;"
				"out vec4 fragColor;"
				"void main() {"
				"	fragColor = vec4(normalize(outNormal), 1.0);"
				"}";
            _program.loadFromText(vsShader, fsShader);
			_program.compileAndLink();
			_program.autocatching();
        }
    };
}

#endif /* __MB_NORMAL_MATERIAL__ */
