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

mb::Scene* scene;

void renderFunc(float dt);

mb::PostProcessMaterial* ppm;
mb::Program* computeProg;

int main(void)
{
	mb::GLContext context(4, 4, 720, 480, "Ray Tracing CS");

	auto engine = new mb::Engine(&context, false);
  scene = new mb::Scene(engine, new mb::SimpleCamera(mb::Vect3(0.2f, 0.18f, 8.44f)));

  mb::TexOptions options;
  options.wrapS = mb::ctes::WrapMode::Clamp2Edge;
  options.wrapT = mb::ctes::WrapMode::Clamp2Edge;
  options.minFilter = mb::ctes::TextureFilter::Linear;
  options.magFilter = mb::ctes::TextureFilter::Linear;
  options.internalFormat = GL_RGBA32F;
  options.format = GL_RGBA;
  options.type = GL_FLOAT;

  mb::Texture* tex = new mb::Texture2D(options, 512, 512);

  std::string passthrought = mb::os::readFile(MB_SHADER_FILES + std::string("/passthrought.frag"));

	ppm = new mb::PostProcessMaterial(passthrought.c_str());

	ppm->addUniform("tex", new mb::Uniform(mb::TextureSampler, tex));


	computeProg = new mb::Program();
  std::string raytracingcs = mb::os::readFile(MB_SHADER_FILES + std::string("/rayTracing.cs"));
	computeProg->loadComputeShaderFromText(raytracingcs);
	computeProg->compileAndLink();
	computeProg->autocatching();


	((mb::Texture2D*)tex)->bindImageTexture(0, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);

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
	computeProg->sendUniform2v("size", mb::Vect2(512.0f, 512.0f)._values);
	computeProg->launchComputeWork(512, 512, 1);
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ppm->renderPP();
}
