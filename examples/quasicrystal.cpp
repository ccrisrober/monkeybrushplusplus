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
float ratio;

int main(void)
{
    MB::GLContext context(3, 3, 1024, 768, "Quasicrystal demo");

    engine = new MB::Engine(&context, false);
	scene = new MB::Scene();

	ratio = 10.5f;

	ppm = new MB::PostProcessMaterial(
		"#version 330\n"
        "#define PI 3.14159\n"
		"out vec4 fragColor;\n"
		"uniform float iGlobalTime;\n"
		"uniform float ratio;\n"
		"in vec2 uv;\n"
		"void main(void) {"
        "    float step = PI / ratio;"
        "    float s, c, value, idx;"
        "    float ans = 0.0;"
        "    vec2 uvv = (uv - 0.5) * 150.;   /* Center radius */"
        "    for (idx = 0.; idx < 20.; ++idx)"
        "	 {"
        "        if (idx < ratio) {"
        "            value = idx * step;"
        "            s = sin(value);"
        "            c = cos(value);"
        "            ans += (cos(c * uvv.x + s * uvv.y + iGlobalTime) + 1.) / 5.;"
        "        }"
        "    }"
        "    float v = mod(ans, 1.);"
        "    float k = ans - v;"
        "    ans = (mod(abs(k), 2.)) <= 0.0001 ? v : 1. - v;"
        "    fragColor.rgb = vec3(0.0, ans, ans * 0.5);\n"
        "    fragColor.w = 1.;"
        "}\n");

	ppm->addUniform("iGlobalTime", new MB::Uniform(MB::Float));
	ppm->addUniform("ratio", new MB::Uniform(MB::Float, ratio));

	engine->run(renderFunc);
    
	delete(scene);
	delete(engine);

    return 0;
}

float globalTime = 0.0f;
void renderFunc(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	globalTime += dt;
	ppm->uniform("iGlobalTime")->value(globalTime * 2.5f);
	if (MB::Input2::isKeyPressed(MB::Keyboard::Key::Z))
	{
		ratio -= 0.1f;
		ppm->uniform("ratio")->value(ratio);
	}
	else if (MB::Input2::isKeyPressed(MB::Keyboard::Key::X))
	{
		ratio += 0.1f;
		ppm->uniform("ratio")->value(ratio);
	}
	ppm->renderPP();
}
