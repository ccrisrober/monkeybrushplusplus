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
mb::Program* computeProg;

mb::Texture * tex;

int main(void)
{
	mb::GLContext context(4, 4, 720, 480, "Ray Tracing CS");

	engine = new mb::Engine(&context, false);
	scene = new mb::Scene(engine);

	mb::TexOptions options;
	options.wrapS = mb::ctes::WrapMode::Clamp2Edge;
	options.wrapT = mb::ctes::WrapMode::Clamp2Edge;
	options.minFilter = mb::ctes::TextureFilter::Linear;
	options.magFilter = mb::ctes::TextureFilter::Linear;
	options.internalFormat = GL_RGBA8;
	options.format = GL_RGBA;
	options.type = GL_FLOAT;

	tex = new mb::Texture2D(options, 512, 512);
	((mb::Texture2D*)tex)->bindImageTexture(0, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8);

	{
		std::ifstream file(MB_SHADER_FILES + std::string("/passthrought.frag"));
		std::stringstream buffer;
		buffer << file.rdbuf();

		ppm = new mb::PostProcessMaterial(buffer.str().c_str());

		ppm->addUniform("tex", new mb::Uniform(mb::TextureSampler, tex));
	}
	{
		computeProg = new mb::Program();
		std::ifstream file(MB_SHADER_FILES + std::string("/renderToTexture.cs"));
		std::stringstream buffer;
		buffer << file.rdbuf();
		computeProg->loadComputeShaderFromText(buffer.str());
		computeProg->compileAndLink();
		computeProg->autocatching();
	}

	engine->run(renderFunc);

	delete(scene);
	delete(engine);

	return 0;
}

float globalTime = 0.0f;

void renderFunc(float dt)
{
	globalTime += dt;
	computeProg->use();
	computeProg->launchComputeWork(512/32, 512/32, 1);
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	ppm->renderPP();
}
