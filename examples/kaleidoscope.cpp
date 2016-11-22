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

MB::Engine* engine;
MB::Scene* scene;

void renderFunc(float dt);

MB::PostProcessMaterial* ppm;

float sides, angle;

int main(void)
{
	MB::GLContext context(3, 3, 1024, 768, "Kaleidoscope demo");

	engine = new MB::Engine(&context, false);
	scene = new MB::Scene();

	std::ifstream file(MB_SHADER_FILES_KALEIDOSCOPE_FRAG);
	std::stringstream buffer;
	buffer << file.rdbuf();

	ppm = new MB::PostProcessMaterial(buffer.str().c_str());

	sides = 5.0f;
	angle = 121.0f;

	ppm->addUniform("iGlobalTime", new MB::Uniform(MB::Float, 0.0f));
	ppm->addUniform("sides", new MB::Uniform(MB::Float, sides));
	ppm->addUniform("angle", new MB::Uniform(MB::Float, angle));

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
	if (MB::Input::isKeyClicked(GLFW_KEY_Z))
	{
		sides -= 1.0f;
		ppm->uniform("sides")->value(sides);
	}
	else if (MB::Input::isKeyClicked(GLFW_KEY_X))
	{
		sides += 1.0f;
		ppm->uniform("sides")->value(sides);
	}
	if (MB::Input::isKeyClicked(GLFW_KEY_A))
	{
		angle -= 1.0f;
		ppm->uniform("angle")->value(angle);
	}
	else if (MB::Input::isKeyClicked(GLFW_KEY_S))
	{
		angle += 1.0f;
		ppm->uniform("angle")->value(angle);
	}
	ppm->renderPP();
}