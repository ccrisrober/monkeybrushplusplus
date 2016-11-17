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

#ifndef __MB_SIMPLE_SHADING_MATERIAL__
#define __MB_SIMPLE_SHADING_MATERIAL__

#include "Material.hpp"
#include "Uniform.hpp"

namespace MB
{
    class SimpleShadingMaterial: public Material
    {
    public:
        SimpleShadingMaterial()
        : Material()
        {
            _uniforms["projection"] = new Uniform(Matrix4);
            _uniforms["view"] = new Uniform(Matrix4);
            _uniforms["model"] = new Uniform(Matrix4);
            _uniforms["color"] = new Uniform(Vector3, Vect3(1.0f, 1.0f, 1.0f));

            const char* vsShader = "#version 330\n"
                                   "layout(location = 0) in vec3 position;\n"
                                   "\n"
                                   "uniform mat4 projection;\n"
                                   "uniform mat4 view;\n"
                                   "uniform mat4 model;\n"
                                   "\n"
                                   "void main()\n"
                                   "{\n"
                                   "    gl_Position = projection * view * model * vec4(position, 1.0);\n"
                                   "}\n";
            const char* fsShader = "#version 330\n"
                                   "uniform vec3 color;\n"
                                   "out vec4 fragColor;\n"
                                   ""
                                   "void main()\n"
                                   "{\n"
                                   "    fragColor = vec4(color, 1.0f);\n"
                                   "}\n";
            _program.loadFromText(vsShader, fsShader);
            _program.compileAndLink();
            _program.addUniform("projection");
            _program.addUniform("view");
            _program.addUniform("model");
            _program.addUniform("color");
        }
    };
}

#endif /* __MB_SIMPLE_SHADING_MATERIAL__ */
