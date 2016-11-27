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
#include <shaderFiles.h>

mb::Engine* engine;
mb::Scene* scene;

void renderFunc(float dt);

mb::PostProcessMaterial* ppm;

int main(void)
{
	mb::GLContext context(3, 3, 1024, 768, "Fractal world demo");

	engine = new mb::Engine(&context, false);
	scene = new mb::Scene(engine);

	std::ifstream file(MB_SHADER_FILES_FRACTALWORLD_FRAG);
	std::stringstream buffer;
	buffer << file.rdbuf();

	ppm = new mb::PostProcessMaterial(buffer.str().c_str());

	ppm->addUniform("iGlobalTime", new mb::Uniform(mb::Float, 0.0f));

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
	ppm->uniform("iGlobalTime")->value(globalTime);
	ppm->renderPP();
}
