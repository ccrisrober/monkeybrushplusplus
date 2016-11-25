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

MB::PostProcessMaterial *ppm1, *ppm2;

MB::Framebuffer* fbo;

MB::Texture *currentTex, *oldTex;

/*MB::CustomPingPong<MB::Texture*>* customPP;

std::function<void()> cppCallback([]() {

});*/

int main(void)
{
	MB::GLContext context(3, 3, 512, 512, "Advention demo");

	MB::TexOptions opts;
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

	MB::Texture2D *tex1 = new MB::Texture2D(opts, pixels.data(),
		context.getWidth(), context.getHeight());
	MB::Texture2D *tex2 = new MB::Texture2D(opts, pixels.data(),
		context.getWidth(), context.getHeight());

	//customPP = new MB::CustomPingPong<MB::Texture*>(tex1, tex2);
	std::vector<MB::Texture*> textures = { tex1, tex2 };
	fbo = new MB::Framebuffer(textures, 
		MB::Vect2(context.getWidth(), context.getHeight()));

	engine = new MB::Engine(&context, false);
	scene = new MB::Scene(engine);

	{
		std::ifstream file(MB_SHADER_FILES_ADVENTION_FIRST_FRAG);
		std::stringstream buffer;
		buffer << file.rdbuf();

		ppm1 = new MB::PostProcessMaterial(buffer.str().c_str());

		ppm1->addUniform("tex", new MB::Uniform(MB::Integer, 0));
	}


	{
		std::ifstream file(MB_SHADER_FILES_ADVENTION_SECOND_FRAG);
		std::stringstream buffer;
		buffer << file.rdbuf();

		ppm2 = new MB::PostProcessMaterial(buffer.str().c_str());

		ppm2->addUniform("tex", new MB::Uniform(MB::Integer, 0));
	}

	currentTex = tex1;
	oldTex = tex2;

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

	currentTex->bind(0);
	fbo->bind();
	fbo->replaceTexture(oldTex, 0);
	ppm1->renderPP();
	fbo->unbind();

	std::swap(currentTex, oldTex);

	currentTex->bind(0);
	ppm2->renderPP();
}
