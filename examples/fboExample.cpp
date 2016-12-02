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

mb::PostProcessMaterial *ppm;

mb::Framebuffer* fbo;
mb::Texture2D *tex;

float amount = 0.5f;

int main(void)
{
	mb::GLContext context(3, 3, 512, 512, "Advention demo");

	mb::TexOptions opts;
	opts.minFilter = GL_NEAREST;
	opts.magFilter = GL_NEAREST;
	opts.type = GL_FLOAT;
	opts.format = GL_RGB;
	opts.internalFormat = GL_RGB;

	tex = new mb::Texture2D(opts, context.getWidth(), context.getHeight());
	
	std::vector<mb::Texture*> textures = { tex };
	fbo = new mb::Framebuffer(textures, mb::Vect2(context.getWidth(), context.getHeight()), true);
	
	engine = new mb::Engine(&context, false);
	scene = new mb::Scene(engine);

	{
		std::ifstream file(MB_SHADER_FILES + std::string("/dreamVision.frag"));
		std::stringstream buffer;
		buffer << file.rdbuf();

		ppm = new mb::PostProcessMaterial(buffer.str().c_str());

		ppm->addUniform("tex", new mb::Uniform(mb::Integer, 0));
		ppm->addUniform("amount", new mb::Uniform(mb::Float, amount));
	}
	
	mb::Cube* model = new mb::Cube(1.0f);
	mb::SimpleShadingMaterial material;
	material.uniform("color")->value(mb::Vect3(mb::Color3::Blue));

	for (int i = -2; i < 2; ++i)
	{
		mb::Node* mbModel = new mb::Node(std::string("model"));
		mbModel->setMesh(new mb::MeshRenderer(model, &material));
		mbModel->addComponent(new mb::MoveComponent());
		mbModel->addComponent(new mb::RotateComponent(mb::Axis::x));

		mbModel->getComponent<mb::RotateComponent>()->setRotate(true);

		mbModel->transform().position().set(i * 1.0f, i * 1.0f, 0.0f);
		std::cout << mbModel->transform().position().x() << std::endl;
		scene->root()->addChild(mbModel);
	}
	
	std::cout << "NODES: " << scene->root()->getNumChildren() << std::endl;
	
	engine->run(renderFunc);

	delete(scene);
	delete(engine);

	return 0;
}

void renderFunc(float dt)
{
	scene->mainCamera->update(dt);

	if (mb::Input::isKeyPressed(mb::Keyboard::Key::N))
	{
		amount -= 0.0025f;
		amount = amount < 0.0f ? 0.0f : amount;
		ppm->uniform("amount")->value(amount);
	}
	else if (mb::Input::isKeyPressed(mb::Keyboard::Key::M))
	{
		amount += 0.0025f;
		amount = amount > 1.0f ? 1.0f : amount;
		ppm->uniform("amount")->value(amount);
	}

	fbo->bind();
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	scene->render(dt);
	fbo->unbind();
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	fbo->onlyBindTextures();
	ppm->renderPP();
}
