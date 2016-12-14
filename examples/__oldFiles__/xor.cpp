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

#include <iostream>
#include <mb/mb.h>

mb::Engine* engine;
mb::Scene* scene;

void renderFunc( float dt );

mb::PostProcessMaterial* ppm;

int main(void)
{
    mb::GLContext context(3, 3, 1024, 768, "XOR demo");

    engine = new mb::Engine(&context, false);
    scene = new mb::Scene(engine);

    ppm = new mb::PostProcessMaterial(
        "#version 330\n"
        "out vec4 fragColor;\n"
        "uniform float iGlobalTime;\n"
        "uniform bool useColor;\n"
        "in vec2 uv;\n"
        "void main( void ) {\n"
        "    vec2 p = -1. + 2. * uv;\n"
        "    float t = iGlobalTime * 0.5;\n"
        "    vec2 off1 = vec2(0.5 * cos(5.0 * t), 0.5 * sin(3.0 * t));\n"
        "    vec2 off2 = vec2(0.6 * sin(3.0 * t), 0.4 * cos(2.0 * t));\n"
        "    // Cartesian equation\n"
        "    float r1 = sqrt(dot(p - off1, p - off1));\n"
        "    float r2 = sqrt(dot(p - off2, p - off2));\n"
        "    bool t1 = mod(r1, 0.2) > 0.1;\n"
        "    bool t2 = mod(r2, 0.2) > 0.1;\n"
        "    // XOR time\n"
        "    float c = 0.0;\n"
        "    if (t1) c = 1.0;\n"
        "    if (t2) c = 1.0;\n"
        "    if ((t1) && (t2)) c = 0.0;\n"
        "    if(useColor)"
        "       fragColor = vec4(vec3(c),1.0);\n"
        "    else\n"
        "       fragColor = vec4(t1, t2, 0.0, 1.0);\n"
        "}\n");

    ppm->addUniform("iGlobalTime", new mb::Uniform(mb::Float, 0.0f));
    ppm->addUniform("useColor", new mb::Uniform(mb::Boolean, true));

    engine->run(renderFunc);

    delete(scene);
    delete(engine);

    return 0;
}

float globalTime = 0.0f;
void renderFunc( float dt )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    globalTime += dt;
    ppm->uniform("iGlobalTime")->value(globalTime);
    if (mb::Input::isKeyPressed(mb::Keyboard::Key::Z))
    {
        ppm->uniform("useColor")->value(false);
    }
    else if (mb::Input::isKeyPressed(mb::Keyboard::Key::X))
    {
        ppm->uniform("useColor")->value(true);
    }
    ppm->renderPP();
}
