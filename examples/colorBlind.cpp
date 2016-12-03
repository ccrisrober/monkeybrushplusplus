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
#include <assetsFiles.h>
#include <shaderFiles.h>

mb::Engine* engine;
mb::Scene* scene;

void renderFunc(float dt);

mb::PostProcessMaterial* ppm;

int main(void)
{
	mb::GLContext context(3, 3, 1024, 768, "Color Blind demo");

	engine = new mb::Engine(&context, false);
	scene = new mb::Scene(engine);

	std::ifstream file(MB_SHADER_FILES_COLOR_BLIND_FRAG);
	std::stringstream buffer;
	buffer << file.rdbuf();

	ppm = new mb::PostProcessMaterial(buffer.str().c_str());

	mb::TexOptions opts;
	mb::Texture* tex = new mb::Texture2D(opts, MB_TEXTURE_ASSETS + std::string("/Dundus_Square.jpg"));

	ppm->addUniform("tex", new mb::Uniform(mb::TextureSampler, tex));
	ppm->addUniform("mode", new mb::Uniform(mb::Integer, 0));

	engine->run(renderFunc);

	delete(scene);
	delete(engine);

	return 0;
}

void renderFunc(float)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (mb::Input::isKeyClicked(mb::Keyboard::Key::Num1))
	{
		ppm->uniform("mode")->value(0);
	}
	else if (mb::Input::isKeyClicked(mb::Keyboard::Key::Num2))
	{
		ppm->uniform("mode")->value(1);
	}
	if (mb::Input::isKeyClicked(mb::Keyboard::Key::Num3))
	{
		ppm->uniform("mode")->value(2);
	}
	else if (mb::Input::isKeyClicked(mb::Keyboard::Key::Num4))
	{
		ppm->uniform("mode")->value(3);
	}
	ppm->renderPP();
}
