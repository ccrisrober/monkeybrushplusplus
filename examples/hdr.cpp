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

float exposure;

int main(void)
{
	mb::GLContext context(3, 3, 1024, 768, "Kaleidoscope demo");

	engine = new mb::Engine(&context, false);
	scene = new mb::Scene(engine);

	std::ifstream file(MB_SHADER_FILES_HDR_FRAG);
	std::stringstream buffer;
	buffer << file.rdbuf();

	ppm = new mb::PostProcessMaterial(buffer.str().c_str());

	exposure = 10.5f;

	mb::TexOptions opts;
	mb::Texture* tex = new mb::Texture2D(opts, MB_TEXTURE_ASSETS + std::string("/memorial.png"));

	ppm->addUniform("exposure", new mb::Uniform(mb::Float, exposure));
	ppm->addUniform("tex", new mb::Uniform(mb::TextureSampler, tex));

	engine->run(renderFunc);

	delete(scene);
	delete(engine);

	return 0;
}

bool play = true;

void renderFunc(float)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (mb::Input::isKeyClicked(mb::Keyboard::Key::Space))
	{
		play = !play;
	}
	if (mb::Input::isKeyPressed(mb::Keyboard::Key::Z))
	{
		exposure -= 0.1f;
		ppm->uniform("exposure")->value(exposure);
		std::cout << exposure << std::endl;
	}
	else if (mb::Input::isKeyPressed(mb::Keyboard::Key::X))
	{
		exposure += 0.1f;
		ppm->uniform("exposure")->value(exposure);
		std::cout << exposure << std::endl;
	}
	ppm->renderPP();
}
