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

mb::Engine* engine;
mb::Scene* scene;

void renderFunc(float dt);

#include <ctime>

float mathRandom()
{
	return ((float)rand() / (RAND_MAX));
}

void randomCube()
{
	mb::SimpleShadingMaterial* material;
	mb::Cube* model;

	float size = std::ceil(mathRandom() * 3.0f);
	model = new mb::Cube(1.0f * size);

	material = new mb::SimpleShadingMaterial();

	material->uniform("color")->value(mb::Vect3(
		mb::Color3::createFromHex(mathRandom() * 0xffffff)));

	// Add cube
	mb::Node* mbModel = new mb::Node(std::string("cube-" + std::to_string(scene->root()->getNumChildren())));
	mbModel->setMesh(new mb::MeshRenderer(model, material));
	/*switch ((rand() % 3 + 1))
	{
	case 1:
		mbModel->addComponent(new mb::RotateComponent(mb::Axis::x));
		break;
	case 2:
		mbModel->addComponent(new mb::RotateComponent(mb::Axis::y));
		break;
	case 3:
		mbModel->addComponent(new mb::RotateComponent(mb::Axis::z));
		break;
	}
	mbModel->getComponent<mb::RotateComponent>()->setRotate(true);*/

	mbModel->transform().position().x(-15.0f + std::round((mathRandom() * 50.0f)));
	mbModel->transform().position().y(std::round(mathRandom() * 5.0f));
	mbModel->transform().position().z(-10.0f + std::round(mathRandom() * 50.0f));

	scene->root()->addChild(mbModel);
	//return mbModel;
}

int main(void)
{
	srand((unsigned int)time(NULL));

	mb::GLContext context(4, 4, 1024, 768, "Hello mb");

    engine = new mb::Engine(&context, false);
	scene = new mb::Scene(engine);

	for (unsigned int i = 0; i < 150; ++i)
	{
		randomCube();
	}

	engine->run(renderFunc);
    
	delete(scene);
	delete(engine);

    return 0;
}

float rotSpeed = 0.25f;

void renderFunc(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene->camera->update(dt);

	scene->root()->traverse([=](mb::Node* n)
	{
		if (n->getMesh() != nullptr)
		{
			n->transform().rotation().x(n->transform().rotation().x() + rotSpeed * dt);
			n->transform().rotation().y(n->transform().rotation().y() + rotSpeed * dt);
			n->transform().rotation().z(n->transform().rotation().z() + rotSpeed * dt);
		}
	});

	if (mb::Input::isKeyClicked(mb::Keyboard::Key::Esc))
	{
		engine->close();
		return;
	}
	if (mb::Input::isKeyPressed(mb::Keyboard::Key::O))
	{
		// Rem cube
		unsigned int maxCubes = scene->root()->getNumChildren();
		std::cout << "Total: " << maxCubes << std::endl;
		if (maxCubes > 1)
		{
			scene->root()->removeChild(0u);
		}
	}
	if (mb::Input::isKeyPressed(mb::Keyboard::Key::P))
	{
		randomCube();
	}
	if (mb::Input::isKeyClicked(mb::Keyboard::Key::M))
	{
		scene->root()->traverse([](mb::Node* n)
		{
			std::cout << n->name() << std::endl;
		});
	}
	scene->render(dt);
}
