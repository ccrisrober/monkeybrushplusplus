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

mb::PostProcessMaterial *ppm1, *ppm2;

mb::Framebuffer* fbo;

mb::Texture *currentTex, *oldTex;

mb::CustomPingPong<mb::Texture2D*>* customPP;

std::function<void()> cb;

int main(void)
{
	mb::GLContext context(3, 3, 512, 512, "Advention demo");

	mb::TexOptions opts;
	opts.minFilter = GL_NEAREST;
	opts.magFilter = GL_NEAREST;
	opts.type = GL_FLOAT;

	unsigned int ww = context.getWidth();
	unsigned int hh = context.getHeight();

	float h = 2.0f / ww;

	std::vector<float> pixels; // TODO: OPTIMIZE (ww * hh * 4);
	pixels.reserve(ww * hh * 4);
	unsigned int Ro = 0.3f;
	for (unsigned int i = 0; i < ww; ++i)
	{
		for (unsigned int j = 0; j < hh; ++j)
		{
			float x = h * (j - ww / 2.0f), 
				  y = h * (i - hh / 2.0f), 
				  exp = std::exp(-4.0f * (x * x + y * y));
			pixels.push_back(exp * y);
			pixels.push_back(-exp * x);
			pixels.push_back(3.0f * std::exp(-30.0f * 
				((x - Ro) * (x - Ro) + y * y)));
			pixels.push_back(1.0f);
		}
	}

	mb::Texture2D *tex1 = new mb::Texture2D(opts, pixels.data(),
		context.getWidth(), context.getHeight());
	mb::Texture2D *tex2 = new mb::Texture2D(opts, pixels.data(),
		context.getWidth(), context.getHeight());

	customPP = new mb::CustomPingPong<mb::Texture2D*>(tex1, tex2);
	std::vector<mb::Texture*> textures = { tex1, tex2 };
	fbo = new mb::Framebuffer(textures, 
		mb::Vect2(context.getWidth(), context.getHeight()));

	cb = std::function<void()>([&]() {
		customPP->first()->bind(0);
		fbo->bind();
		fbo->replaceTexture(customPP->last(), 0);
	});

	engine = new mb::Engine(&context, false);
	scene = new mb::Scene(engine);

	{
		std::ifstream file(MB_SHADER_FILES_ADVENTION_FIRST_FRAG);
		std::stringstream buffer;
		buffer << file.rdbuf();

		ppm1 = new mb::PostProcessMaterial(buffer.str().c_str());

		ppm1->addUniform("tex", new mb::Uniform(mb::Integer, 0));
	}


	{
		std::ifstream file(MB_SHADER_FILES_ADVENTION_SECOND_FRAG);
		std::stringstream buffer;
		buffer << file.rdbuf();

		ppm2 = new mb::PostProcessMaterial(buffer.str().c_str());

		ppm2->addUniform("tex", new mb::Uniform(mb::Integer, 0));
	}

	currentTex = tex1;
	oldTex = tex2;

	engine->run(renderFunc);

	delete(scene);
	delete(engine);

	return 0;
}

void renderFunc(float)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (unsigned int i = 0; i < 1; ++i)
	{
		customPP->swap(cb);
		ppm1->renderPP();
	}
	fbo->unbind();
	fbo->unbind();

	std::swap(currentTex, oldTex);
	currentTex->bind(0);
	ppm2->renderPP();
}
