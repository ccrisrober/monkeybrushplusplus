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

MB::Engine* engine;
MB::Scene* scene;

void renderFunc(float dt);

MB::Node* mbCube;
MB::RotateComponent* r;

int main(void)
{
    MB::GLContext context(3, 3, 1024, 768, "Hello MB");

    engine = new MB::Engine(&context, false);
	scene = new MB::Scene();

	MB::Cube* cube = new MB::Cube(1.0f);

	MB::SimpleShadingMaterial material;
	material.uniform("color")->value(MB::Vect3(MB::Color3::Blue));

	mbCube = new MB::Node(std::string("cube"));
	mbCube->addComponent(new MB::MeshRenderer(cube, &material));
	mbCube->addComponent(new MB::MoveComponent());
	r = new MB::RotateComponent(MB::Axis::x);
	mbCube->addComponent(r);

	scene->root()->addChild(mbCube);

	engine->run(renderFunc);
    
	delete(scene);
	delete(engine);

    return 0;
}

void renderFunc(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene->camera->update(dt);
	if (MB::Input::isKeyPressed(GLFW_KEY_ESCAPE))
	{
		engine->close();
		return;
	}
	if (MB::Input::isKeyClicked(GLFW_KEY_X))
	{
		r->setAxis(MB::Axis::x);
		//mbCube->getComponent<MB::RotateComponent>()->setAxis(MB::Axis::x);
	}
	else if (MB::Input::isKeyClicked(GLFW_KEY_Y))
	{
		r->setAxis(MB::Axis::y);
		//mbCube->getComponent<MB::RotateComponent>()->setAxis(MB::Axis::y);
	}
	else if (MB::Input::isKeyClicked(GLFW_KEY_Z))
	{
		r->setAxis(MB::Axis::z);
		//mbCube->getComponent<MB::RotateComponent>()->setAxis(MB::Axis::z);
	}
	scene->render(dt);
}
