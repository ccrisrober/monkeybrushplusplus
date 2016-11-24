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

MB::Engine* engine;
MB::Scene* scene;

void renderFunc(float dt);


MB::PostProcessMaterial* ppm;

int iter;

float offsetX = 0.0f;
float offsetY = 0.0f;

int main(void)
{
    MB::GLContext context(3, 3, 1024, 768, "Quasicrystal demo");

    engine = new MB::Engine(&context, false);
	scene = new MB::Scene();

	iter = 90;

	ppm = new MB::PostProcessMaterial(
		"#version 330\n"
		"out vec4 fragColor;\n"
		"in vec2 uv;\n"
		"vec2 f(vec2 n) {\n"
        "    return vec2("
        "        n.x*n.x*n.x - 3.0*n.x*n.y*n.y - 1.0,"
        "        -n.y*n.y*n.y + 3.0*n.x*n.x*n.y"
        "    );\n"
        "}\n"
        "vec2 df(vec2 n) {\n"
        "    return 3.0 * vec2("
        "        n.x*n.x - n.y*n.y,"
        "        2.0 * n.x * n.y"
        "    );\n"
        "}\n"
        "vec2 cdiv(vec2 a, vec2 b) {\n"
        "    float d = dot(b, b);\n"
        "    if(d == 0.0) return a;\n"
        "    else return vec2("
        "        (a.x*b.x + a.y*b.y) / d,"
        "        (a.y*b.x - a.x*b.y) / d"
        "    );\n"
        "}\n"
        "uniform int iter;\n"
        "uniform vec2 offset;\n"
		"void main(void) {\n"
        "    vec2 z;\n"
        "    z.x = 3.0 * (uv.x - 0.5);\n"
        "    z.y = 2.0 * (uv.y - 0.5);\n"
        "    int i;\n"
        "    for(i = 0; i < iter; ++i) {\n"
        "        vec2 zn = z - cdiv(f(z), df(z)) + vec2(offset);\n"
        "        if(distance(zn, z) < 0.00001) break;\n"
        "        z = zn;\n"
        "    }\n"
        "	 float ans = float(i) / float(iter);\n"
        "    fragColor.rgb = vec3(0.0, ans, ans * 0.5);\n"
        "    fragColor.w = 1.;\n"
        "}\n");
	ppm->addUniform("iter", new MB::Uniform(MB::Integer, iter));
	ppm->addUniform("offset", new MB::Uniform(MB::Vector2, MB::Vect2(offsetX, offsetY)));

	engine->run(renderFunc);
    
	delete(scene);
	delete(engine);

    return 0;
}
void renderFunc(float)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (MB::Input2::KeyPressed(MB::Keyboard::Key::Z))
	{
		iter -= 1;
		ppm->uniform("iter")->value(iter);
	}
	if (MB::Input2::KeyPressed(MB::Keyboard::Key::X))
	{
		iter += 1;
		ppm->uniform("iter")->value(iter);
	}
	if (MB::Input2::KeyPressed(MB::Keyboard::Key::W))
	{
		offsetY += 0.1f;
	}
	if (MB::Input2::KeyPressed(MB::Keyboard::Key::S))
	{
		offsetY -= 0.1f;
	}
	if (MB::Input2::KeySinglePressed(MB::Keyboard::Key::A))
	{
		offsetX -= 0.1f;
	}
	if (MB::Input2::KeySinglePressed(MB::Keyboard::Key::D))
	{
		offsetX += 0.1f;
	}
	ppm->uniform("offset")->value(MB::Vect2(offsetX, offsetY));
	ppm->renderPP();
}
