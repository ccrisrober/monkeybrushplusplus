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

int main(void)
{
	mb::GLContext context(3, 3, 1024, 768, "Hello mb");

    engine = new mb::Engine(&context, false);
	scene = new mb::Scene(engine);

	mb::Cube* model = new mb::Cube(1.0f);

	mb::SimpleShadingMaterial material;
	material.uniform("color")->value(mb::Vect3(mb::Color3::Blue));


	float speed = 20.0f;


	mb::Node *solarSystemNode = new mb::Node(std::string("solarSystemNode"));
	solarSystemNode->transform().position().z(-5.0f);

	mb::Node *earthOrbitNode = new mb::Node(std::string("earthOrbitNode"));
	earthOrbitNode->transform().position().set(5.0f, 0.0f, 0.0f);
	earthOrbitNode->addComponent(new mb::RotateComponent(mb::Axis::y, speed * 0.01f, true));

	mb::Node *moonOrbitNode = new mb::Node(std::string("moonOrbitNode"));
	moonOrbitNode->transform().position().set(2.0f, 0.0f, 0.0f);
	moonOrbitNode->addComponent(new mb::RotateComponent(mb::Axis::y, speed * 0.01f, true));

	mb::Node *sunNode = new mb::Node(std::string("sun"));
	sunNode->setMesh(new mb::MeshRenderer(model, &material));
	sunNode->transform().scale().set(5.0f, 5.0f, 5.0f);
	sunNode->addComponent(new mb::RotateComponent(mb::Axis::y, speed * 0.005f, true));

	mb::Node *earthNode = new mb::Node(std::string("earth"));
	earthNode->setMesh(new mb::MeshRenderer(model, &material));
	earthNode->transform().scale().set(2.0f, 2.0f, 2.0f);
	earthNode->addComponent(new mb::RotateComponent(mb::Axis::y, speed * 0.05f, true));

	mb::Node *moonNode = new mb::Node(std::string("moon"));
	moonNode->setMesh(new mb::MeshRenderer(model, &material));
	moonNode->transform().scale().set(0.4f, 0.4f, 0.4f);
	moonNode->addComponent(new mb::RotateComponent(mb::Axis::y, speed * -0.01f, true));

	solarSystemNode->addChild(sunNode);
	solarSystemNode->addChild(earthOrbitNode);
	earthOrbitNode->addChild(earthNode);
	earthOrbitNode->addChild(moonOrbitNode);
	moonOrbitNode->addChild(moonNode);
	
	scene->root()->addChild(solarSystemNode);

	engine->run(renderFunc);
    
	delete(scene);
	delete(engine);

    return 0;
}

void renderFunc(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene->camera->update(dt);
	if (mb::Input::isKeyPressed(mb::Keyboard::Key::Esc))
	{
		engine->close();
		return;
	}
	//engine->state()->culling.setStatus(false);
	//engine->state()->setPolygonMode(GL_LINE);
	scene->render(dt);
}
