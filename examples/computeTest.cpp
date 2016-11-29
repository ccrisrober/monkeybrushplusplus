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

mb::Texture2D * tex;

int main(void)
{
	mb::GLContext context(4, 4, 720, 480, "Compute Test");

	engine = new mb::Engine(&context, false);
	scene = new mb::Scene(engine);

	{
		std::ifstream file(MB_SHADER_FILES_PASSTHROUGHT);
		std::stringstream buffer;
		buffer << file.rdbuf();

		ppm = new mb::PostProcessMaterial(buffer.str().c_str());

		ppm->addUniform("tex", new mb::Uniform(mb::Integer, 0));
	}
	{
		computeProg = new mb::Program();
		std::ifstream file(MB_SHADER_FILES_TEST_COMPUTESHADER);
		std::stringstream buffer;
		buffer << file.rdbuf();
		computeProg->loadComputeShaderFromText(buffer.str());
		computeProg->compileAndLink();
		computeProg->autocatching();
	}

	mb::TexOptions options;
	options.wrapS = GL_CLAMP_TO_EDGE;
	options.wrapT = GL_CLAMP_TO_EDGE;
	options.minFilter = GL_NEAREST;
	options.magFilter = GL_NEAREST;
	options.internalFormat = GL_R32F;
	options.format = GL_RED;
	options.type = GL_FLOAT;

	tex = new mb::Texture2D(options, 512, 512);
	tex->bindImageTexture(0, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_R32F);

	engine->run(renderFunc);

	delete(scene);
	delete(engine);

	return 0;
}

unsigned int frame = 0;
void renderFunc(float)
{
	frame = (frame + 1) % static_cast<int>(200 * mb::Mathf::PI);

	computeProg->sendUniformf("roll", static_cast<float>(frame) * 0.01f);
	computeProg->use();
	computeProg->launchComputeWork(512/16, 512/16, 1);
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);	// TODO: Try GL_TEXTURE_UPDATE_BARRIER_BIT
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	ppm->renderPP();
}
