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
MB::Program* computeProg;

MB::Texture2D * tex;

int main(void)
{
	MB::GLContext context(4, 4, 720, 480, "Ray Tracing CS");

	engine = new MB::Engine(&context, false);
	scene = new MB::Scene(engine);

	{
		std::ifstream file(MB_SHADER_FILES_PASSTHROUGHT);
		std::stringstream buffer;
		buffer << file.rdbuf();

		ppm = new MB::PostProcessMaterial(buffer.str().c_str());

		ppm->addUniform("tex", new MB::Uniform(MB::Integer, 0));
	}
	{
		computeProg = new MB::Program();
		std::ifstream file(MB_SHADER_FILES_RAYTRACING_COMPUTESHADER);
		std::stringstream buffer;
		buffer << file.rdbuf();
		computeProg->loadComputeShaderFromText(buffer.str());
		computeProg->compileAndLink();
		computeProg->autocatching();
	}

	MB::TexOptions options;
	options.wrapS = GL_CLAMP_TO_EDGE;
	options.wrapT = GL_CLAMP_TO_EDGE;
	options.minFilter = GL_LINEAR;
	options.magFilter = GL_LINEAR;
	options.internalFormat = GL_RGBA32F;
	options.format = GL_RGBA;
	options.type = GL_FLOAT;

	tex = new MB::Texture2D(options, 512, 512);
	tex->bindImageTexture(0, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);

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
	computeProg->sendUniformf("time", globalTime);
	computeProg->sendUniform2v("size", MB::Vect2(512.0f, 512.0f)._values);
	computeProg->launchComputeWork(512, 512, 1);
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	ppm->renderPP();
}
